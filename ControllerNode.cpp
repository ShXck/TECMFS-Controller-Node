#include "ControllerNode.h"

Controller_Node::Controller_Node() : disk_handler( DISK_NUMBER ) {
	for( int i = 0; i < DISK_NUMBER; i++ ) {
		disk_handler.add_disk( util::create_random_key( 4 ), MAX_BLOCKS );
	}
}

void Controller_Node::run() {
	std::thread handler_thread( [this]() {
		net_handler.start();
	});
	handler_thread.detach();
}

Strings Controller_Node::index_folder( std::string folder ) {

	Strings _tmp;

	path p( folder );
	for( auto i = directory_iterator( p ); i != directory_iterator(); i++ ) {
		if( !is_directory( i->path() ) ) {
			std::cout << i->path().filename().string() << std::endl;
			split_video( i->path().filename().string(), folder );
		} else {
			continue;
		}
	}

	return _tmp;
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
		//imwrite( "dest/img" + std::to_string( name_ctr ) + ".jpg", _frame );
		total_frames.push_back( _frame );
		frm_ctr++;
	}
	v_cap.release();

	set_data( total_frames );
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

void Controller_Node::set_data( Frames frames ) {

	data_handler.add_video_data( util::create_random_key( 4 ) );

	std::string _result = "";

	for( auto& frm : frames ) {
		Bytes _bytes = mat_to_byte( frm );
		for( auto& _byte : _bytes ) {
			_result += byte_to_bit( _byte );
		}
	}
}

Controller_Node::~Controller_Node() { }

