#include "DiskStatusHandler.h"

Disk_Status_Handler::Disk_Status_Handler( unsigned int disk_count ) {
	m_disks.reserve( disk_count );
}

void Disk_Status_Handler::add_disk( std::string id, unsigned int blocks ) {
	m_disks.push_back( Disk( id, blocks ) );
}

bool Disk_Status_Handler::is_full( std::string id ) {

	for( auto& curr_disk : m_disks ) {
		if( curr_disk.disk_id == id ) {
			if( curr_disk._status == NOT_FULL_STAT ) return false;
			else return true;
			break;
		}
	}
	return false;
}

Disk_Status_Handler::~Disk_Status_Handler() { }

