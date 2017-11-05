#ifndef VIDEODATAHANDLER_H_
#define VIDEODATAHANDLER_H_
#include <string>
#include <iostream>
#include <vector>

typedef std::vector<std::string> strings;

struct Video_Data_Container {
	std::string video_id;
	strings disks_used;
	strings blocks_used;
	Video_Data_Container( std::string id ) : video_id( id ) {}
};

typedef std::vector<Video_Data_Container> Data;

class Video_Data_Handler {
public:
	Video_Data_Handler();
	void add_video_data( std::string v_id );
	void set_disks_used( std::string v_id, strings used );
	void set_blocks_used( std::string v_id, strings used );
	virtual ~Video_Data_Handler();
private:
	Data m_data;
};

#endif /* VIDEODATAHANDLER_H_ */
