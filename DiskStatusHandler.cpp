#include "DiskStatusHandler.h"

Disk_Status_Handler::Disk_Status_Handler( unsigned int disk_count ) {
	m_disks.reserve( disk_count );
}

void Disk_Status_Handler::add_disk( int id, unsigned int blocks ) {
	m_disks.push_back( Disk( id, blocks ) );
}

void Disk_Status_Handler::add_registry( int mat, int disk ) {
	m_registries.push_back( Disk_Registry( mat, disk ) );
}

int Disk_Status_Handler::get_disk( int mat ) {

	for( auto& reg : m_registries ) {
		if( reg._mat == mat ) return reg._disk;
	}
	return -1;
}

Disk_Status_Handler::~Disk_Status_Handler() { }

