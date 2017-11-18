#include "ControllerNode.h"

Controller_Node::Controller_Node() : disk_handler( DISK_NUMBER ) {
	for( int i = 0; i < DISK_NUMBER; i++ ) {
		disk_handler.add_disk( i );
	}
	run();
}

void Controller_Node::run() {

	std::thread t( [this](){
		std::string _action;
		while( true ) {
			std::cout << "SELECCIONE LA ACCIÓN A REALIZAR" << "\n\t 1. Indexar carpeta con videos."
					<< "\n\t 2. Cargar Video." << "\n\t 3. Reproducir Video."  << std::endl;
			std::getline( std::cin, _action );
			int int_action = std::stoi( _action );
			switch( int_action ) {
				case 1: {
					index_folder( "/home/marcelo/Desktop/TECMFS_Folder" );
					break;
				}
				case 2: {

					std::string _frame;
					std::cout << "Select -1 to load the whole video or select an specific Frame:";
					std::getline( std::cin, _frame );
					std::cout << std::endl;

					std::string _video;
					std::cout << "Name of the video:";
					std::getline( std::cin, _video );
					std::cout << std::endl;

					retrieve( _video, std::stoi( _frame ) );
					break;
				}
				case 3: {
					create_video();
					break;
				}
			}
		}
	});
	t.detach();

	net_handler.start();
}

void Controller_Node::index_folder( std::string folder ) {

	path p( folder );
	for( auto i = directory_iterator( p ); i != directory_iterator(); i++ ) {
		if( !is_directory( i->path() ) ) {
			split_video( i->path().filename().string(), folder );
		} else {
			continue;
		}
	}
}

void Controller_Node::split_video( std::string video_name, std::string folder ) {

	VideoCapture v_cap( folder + "/" + video_name );

	Frames total_frames;

	v_cap.set( CV_CAP_PROP_POS_FRAMES, 0 );
	double frame_count = v_cap.get( CV_CAP_PROP_FRAME_COUNT );

	int frm_ctr = 0;

	while( frm_ctr < frame_count ) {
		Mat _frame;
		v_cap >> _frame;
		total_frames.push_back( _frame );
		frm_ctr++;
	}

	v_cap.release();

	set_data( total_frames, video_name );
}

Bytes Controller_Node::mat_to_byte( Mat img ) {
	int _size = img.total() * img.elemSize();
	Bytes img_bytes( _size );
	img_bytes.assign( img.datastart, img.dataend );
	return img_bytes;
}

Mat Controller_Node::bytes_to_mat( Bytes bytes, int w, int h ) {
	Mat _img = Mat( h, w, CV_8UC3, bytes.data() ).clone();
	return _img;
}

std::string Controller_Node::byte_to_bit( byte source ) {
	std::bitset<8> bits_aux( source );
	std::string bits = bits_aux.to_string();
	return bits;
}

byte Controller_Node::bit_to_byte( std::string bit ) {
	std::bitset<8> _byte( bit );
	byte _result = ( _byte.to_ulong() & 0xFF );
	return _result;
}

void Controller_Node::set_data( Frames frames, std::string video_name ) {

	std::string video_id = util::create_random_key( 4 );

	data_handler.add_video_data( video_id, video_name, frames[0].cols, frames[0].rows, frames.size() );

	std::string _result = "";

	int mat_ctr = 0;
	for( auto& frm : frames ) {
		Bytes _bytes = mat_to_byte( frm );
		m_render.push_back( Render_Data( _bytes, mat_ctr, video_id ) );
		for( byte _byte : _bytes ) {
			_result += _byte;
		}
		distribute_data( video_id, _result, mat_ctr++ );
		_result.clear();
		std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );
	}
}

void Controller_Node::distribute_data( std::string video_id, std::string result, int mat_number  ) {

	Strings _chunks = split_mat( result );

    int& disk_ctr = data_handler.disk();
    int& chunk_order = data_handler.order();
    for( unsigned int i = 0; i < _chunks.size(); i++ ) {
    	if( disk_ctr == DISK_NUMBER ) data_handler.restart_disk_ctr();
    	std::string data_chunk = JHandler::build_video_data( video_id, (int)Instruction::COLLECT_INSTR, chunk_order, mat_number );
    	net_handler.send( _chunks[i], data_chunk, disk_ctr );
    	disk_handler.add_registry( mat_number, disk_ctr );
    	data_handler.increment_video_order( 1 );
    }
    net_handler.send( JHandler::build_instruction_msg( (int)Instruction::STORE_INSTR ), disk_ctr );
    data_handler.increment_disk_ctr();
}

void Controller_Node::retrieve( std::string video_name, int mat_number ) {

	std::string video_id = data_handler.get_id( video_name );

	if( mat_number != -1 ) {
		for( int i = 0; i < DISK_NUMBER; i++ ) {
			std::string retrv_msg = JHandler::build_retrv_msg( (int)Instruction::RETRV_INSTR, mat_number, video_id );
			int _disk = disk_handler.get_disk( mat_number );
			net_handler.send( retrv_msg, _disk );
		}
	} else {
		int _frames = data_handler.frames_of( video_name );

		for( int j = 0; j < _frames; j++ ) {
			std::string retrv_msg = JHandler::build_retrv_msg( (int)Instruction::RETRV_INSTR, j, video_id );
			int _disk = disk_handler.get_disk( j );
			if( _disk != 2 ) { // TODO: DELETE THE IF // TESTING PURPOSES
				net_handler.send( retrv_msg, _disk );
				wait_for_retrieve();
			}
		}
	}
}

void Controller_Node::wait_for_retrieve() {
	while( !net_handler.request_data()->can_join ) { }
	process_segment();
}

Strings Controller_Node::split_mat( std::string bytes ) {

	int _parts =  DISK_NUMBER * 6;
	Strings _chunks;
	_chunks.reserve( _parts );
	int _lenght = bytes.length();

	// Divide el string de bytes en pedazos.
    int _at, _pre = 0, i;
    for( _pre = i = 0; i < _parts; i++ ) {
        _at = ( _lenght + _lenght * i ) / _parts;
        _chunks.push_back( bytes.substr( _pre, _at - _pre ) );
        _pre = _at;
    }

    return _chunks;
}

void Controller_Node::process_segment() {

	std::vector<Processed_Tmp> _parts = net_handler.request_data()->request_result;
	Frames _frames;

	std::string bytes_result;

	for( auto& tmp : _parts ) {
		bytes_result += tmp._data;
	}

	const char* c_result = bytes_result.c_str();

	Bytes _bytes;
	for( unsigned int i = 0; i < bytes_result.length(); i++ ) {
		_bytes.push_back( c_result[i] );
	}

	render( _bytes, _parts[0]._mat );

	Mat _mat = bytes_to_mat( _bytes, 480, 480 );

	m_video.push_back( _mat );

	std::cout << "FRAMES: " <<  m_video.size() << std::endl;

	net_handler.switch_data_state( false );
	net_handler.clean_data_response();
}

void Controller_Node::create_video() {

	std::cout << m_video.size() << std::endl;

	VideoWriter output_vid;

	int _width = m_video[0].cols;
	int _height = m_video[0].rows;
	int _codec = CV_FOURCC( 'M', 'J', 'P', 'G' );
	Size _size( _width, _height );

	output_vid.open( "video.avi", _codec, 30, _size, true );

	for( auto frm : m_video ) {
		output_vid.write( frm );
	}

	m_video.clear();

}

void Controller_Node::render( Bytes& mat_bytes, int mat ) {

	Bytes rendr_bytes;

	for( auto& rd : m_render ) {
		if( rd._mat == mat  ) {
			rendr_bytes = rd._bytes;
		}
	}

	mat_bytes.assign( rendr_bytes.begin(), rendr_bytes.end() );
}

Controller_Node::~Controller_Node() { }

