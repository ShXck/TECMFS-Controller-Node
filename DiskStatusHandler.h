#ifndef DISKSTATUSHANDLER_H_
#define DISKSTATUSHANDLER_H_
#include <string>
#include <iostream>
#include <vector>

#define NOT_FULL_STAT 0
#define FULL_STAT 1
#define DOWN_STAT 2

struct Disk {
	unsigned int _status;
	unsigned int blocks_left;
	unsigned int disk_id;
	Disk( int disk, unsigned int blocks ) : _status( NOT_FULL_STAT ), blocks_left( blocks ), disk_id( disk ) {}
};

struct Disk_Registry {
	int _mat;
	int _disk;
	Disk_Registry( int mat, int disk ) : _mat( mat ), _disk( disk ) { }
};

typedef std::vector<Disk> Disk_Collection;
typedef std::vector<Disk_Registry> Registries;

class Disk_Status_Handler {
public:
	Disk_Status_Handler( unsigned int disk_count );
	/**
	 * Agrega un nuevo disco al RAID.
	 * @param id la id del disco.
	 * @param blocks la cantidad de bloques del disco.
	 */
	void add_disk( int id, unsigned int blocks = 6 );
	/**
	 * Agrega un registro nuevo.
	 * @param mat el frame.
	 * @param disk el disco donde se ubica el frame.
	 */
	void add_registry( int mat, int disk );
	/**
	 * Obtiene el numero de disco donde se ubica cierto frame.
	 * @param mat el número de frame.
	 * @return el disco donde se ubica.
	 */
	int get_disk( int mat );
	void print_reg();
	virtual ~Disk_Status_Handler();
private:
	Disk_Collection m_disks;
	Registries m_registries;
};

#endif /* DISKSTATUSHANDLER_H_ */
