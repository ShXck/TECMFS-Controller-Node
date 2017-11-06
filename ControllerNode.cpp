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
			std::cout << "SELECCIONE LA ACCIÓN A REALIZAR" << "\n\t 1. Indexar carpeta con videos." << std::endl;
			std::getline( std::cin, _action );
			int int_action = std::stoi( _action );
			switch( int_action ) {
				case 1: {
					index_folder( "/home/marcelo/Desktop/TECMFS_Folder" );
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

	//Determina la representación binaria de todos los frames y los combina.
	for( auto& frm : frames ) {
		Bytes _bytes = mat_to_byte( frm );
		for( auto& _byte : _bytes ) {
			_result += byte_to_bit( _byte );
		}
	}
	distribute_data( video_id, _result );
}

void Controller_Node::distribute_data( std::string video_id, std::string result ) {

	int break_point = result.length() / 2 * net_handler.users_connected(); // En lugar de usuarios conectados debe ser DISK_NUMBER, esto es solo para pruebas.
	int _from = 0;
	int _to = 100;
	int chunk_order = 1;

	for( int i = 0; i < net_handler.users_connected(); i++ ) {
		std::string sub_str = result.substr( _from, _to );
		std::string raw_msg = JHandler::build_video_data( video_id, sub_str, (int)Instruction::STORE_INSTR, chunk_order );
		net_handler.send( raw_msg, i );

	}
}

Controller_Node::~Controller_Node() { }

