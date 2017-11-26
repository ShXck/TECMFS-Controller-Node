#include "VideoDataHandler.h"

Video_Data_Handler::Video_Data_Handler() : order_ctr( 0 ), disk_ctr( 0 ) { }

void Video_Data_Handler::add_video_data( std::string v_id, std::string v_name, int dim_x, int dim_y, int frames, double fps ) {
	m_data.push_back( Video_Data_Container( v_id, v_name, dim_x, dim_y, frames, fps ) );
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

double Video_Data_Handler::fps_of( std::string v_name ) {
	for( auto& video : m_data ) {
		if( video.video_name == v_name ) {
			return video._fps;
		}
	}
	return (double)NOT_FOUND;
}

void Video_Data_Handler::increment_video_order( int times ) {
	order_ctr += times;
}

int& Video_Data_Handler::order() {
	return order_ctr;
}

int& Video_Data_Handler::disk() {
	return disk_ctr;
}

void Video_Data_Handler::reset_order() {
	order_ctr = 0;
}

void Video_Data_Handler::restart_disk_ctr() {
	disk_ctr = 0;
}

void Video_Data_Handler::increment_disk_ctr() {
	disk_ctr++;
}

Video_Data_Handler::~Video_Data_Handler() { }

