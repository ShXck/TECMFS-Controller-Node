#include "VideoDataHandler.h"

Video_Data_Handler::Video_Data_Handler() { }

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

Video_Data_Handler::~Video_Data_Handler() { }

