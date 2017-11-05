#ifndef DISKSTATUSHANDLER_H_
#define DISKSTATUSHANDLER_H_
#include <string>
#include <iostream>
#include <vector>

#define NOT_FULL_STAT 0
#define FULL_STAT 1
#define DOWN_STAT 2

struct Disk{
	unsigned int _status;
	unsigned int blocks_left;
	std::string disk_id;
	Disk( std::string id, unsigned int blocks ) : _status( NOT_FULL_STAT ), blocks_left( blocks ), disk_id( id ) {}
};

typedef std::vector<Disk> Disk_Collection;

class Disk_Status_Handler {
public:
	Disk_Status_Handler( unsigned int disk_count );
	bool is_full( std::string disk_id );
	void add_disk( std::string id, unsigned int blocks );
	virtual ~Disk_Status_Handler();
private:
	Disk_Collection m_disks;
};

#endif /* DISKSTATUSHANDLER_H_ */
