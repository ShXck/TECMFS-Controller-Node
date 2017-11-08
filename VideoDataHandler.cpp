#include "VideoDataHandler.h"

Video_Data_Handler::Video_Data_Handler() : order_ctr( 0 ) { }

void Video_Data_Handler::add_video_data( std::string v_id, std::string v_name ) {
	m_data.push_back( Video_Data_Container( v_id, v_name ) );
}

void Video_Data_Handler::set_blocks_used( std::string v_id, strings used ) {
	for( auto& vid : m_data ) {
		if( vid.video_id == v_id ) {
			vid.blocks_used.clear();
			vid.blocks_used.assign( used.begin(), used.end() );
			break;
		}
	}
}

void Video_Data_Handler::set_disks_used( std::string v_id, strings used ) {
	for( auto& vid : m_data ) {
		if( vid.video_id == v_id ) {
			vid.disks_used.clear();
			vid.disks_used.assign( used.begin(), used.end() );
			break;
		}
	}
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

