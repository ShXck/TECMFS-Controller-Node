#include "VideoDataHandler.h"

Video_Data_Handler::Video_Data_Handler() : order_ctr( 0 ) { }

void Video_Data_Handler::add_video_data( std::string v_id, std::string v_name, int dim_x, int dim_y, int frames ) {
	m_data.push_back( Video_Data_Container( v_id, v_name, dim_x, dim_y, frames ) );
}

std::string Video_Data_Handler::get_id( std::string v_name ) {

	for( auto& vid : m_data ) {
		if( vid.video_name == v_name ) return vid.video_id;
	}

	return "";
}

int Video_Data_Handler::frames_of( std::string v_name ) {

	for( auto& video : m_data ) {
		if( video.video_name == v_name ) {
			return video._frames;
		}
	}
	return NOT_FOUND;
}

void Video_Data_Handler::increment_video_order( int times ) {
	order_ctr += times;
}

int& Video_Data_Handler::order() {
	return order_ctr;
}

void Video_Data_Handler::reset_order() {
	order_ctr = 0;
}

Video_Data_Handler::~Video_Data_Handler() { }

