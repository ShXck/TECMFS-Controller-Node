#include "ControllerNode.h"

Controller_Node::Controller_Node() : disk_handler( DISK_NUMBER ) {
	for( int i = 0; i < DISK_NUMBER; i++ ) {
		disk_handler.add_disk( util::create_random_key( 4 ), MAX_BLOCKS );
	}
	run();
}

void Controller_Node::run() {

	std::thread t( [this](){
		std::string _action;
		while( true ) {
			std::cout << "SELECCIONE LA ACCIÓN A REALIZAR" << "\n\t 1. Indexar carpeta con videos."
					<< "\n\t 2. Cargar Video." << std::endl;
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

	data_handler.add_video_data( video_id, video_name );

	std::string _result = "";

	int mat_ctr = 0;
	for( auto& frm : frames ) {
		Bytes _bytes = mat_to_byte( frm );
		og = _bytes;
		for( byte _byte : _bytes ) {
			_result += _byte;
		}
		distribute_data( video_id, _result, mat_ctr++ );
		_result.clear();
		break;
	}
}

void Controller_Node::distribute_data( std::string video_id, std::string result, int mat_number  ) {

	Strings _chunks = split_mat( result );

	std::cout << _chunks.size() <<  " " << _chunks[1].length() << std::endl;

    int disk_ctr = 0;
    int& chunk_order = data_handler.order();
    for( unsigned int i = 0; i < _chunks.size(); i++ ) {
    	std::string chunk_1 = JHandler::build_video_data( video_id, (int)Instruction::COLLECT_INSTR, chunk_order, mat_number );
    	//net_handler.send( _chunks[i], chunk_1, disk_ctr );
    	net_handler.send( _chunks[i], chunk_1, 0 );
    	data_handler.increment_video_order( 1 );
    	disk_ctr++;
    	if( disk_ctr == DISK_NUMBER ) disk_ctr = 0;
    }

    for( int i = 0; i < DISK_NUMBER; i++ ) {
    	net_handler.send( JHandler::build_instruction_msg( (int)Instruction::STORE_INSTR ), i );
    }
}

void Controller_Node::retrieve( std::string video_name, int mat_number ) {

	std::string video_id = data_handler.get_id( video_name );

	for( int i = 0; i < DISK_NUMBER; i++ ) {
		std::string retrv_msg = JHandler::build_retrv_msg( (int)Instruction::RETRV_INSTR, mat_number, video_id );
		net_handler.send( retrv_msg, i );
	}

	wait_for_retrieve();
}

void Controller_Node::wait_for_retrieve() {
	std::thread retrv_thrd( [this](){
		while( !net_handler.request_data()->can_join ) { }
		join_video();
	});
	retrv_thrd.detach();
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

void Controller_Node::join_video() {

	std::vector<Processed_Tmp> _parts = net_handler.request_data()->request_result;
	Frames _frames;

	std::string bytes_result;

	for( auto& tmp : _parts ) {
		bytes_result += tmp._data;
	}

	unsigned char* c_result = (unsigned char*)bytes_result.c_str();


	Bytes _bytes;
	for( unsigned int i = 0; i < bytes_result.length(); i++ ) {
		_bytes.push_back( c_result[i] );
	}

	Mat _mat = bytes_to_mat( _bytes, 480, 480 );

	std::cout << "Showing img" << std::endl;

	namedWindow("TEST WINDOW", WINDOW_AUTOSIZE);
	imshow("TEST WINDOW", _mat );
	waitKey(0);
}

Controller_Node::~Controller_Node() { }

