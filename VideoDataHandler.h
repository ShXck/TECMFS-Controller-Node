#ifndef VIDEODATAHANDLER_H_
#define VIDEODATAHANDLER_H_
#include <string>
#include <iostream>
#include <vector>

typedef std::vector<std::string> strings;

struct Video_Data_Container {
	std::string video_id;
	std::string video_name;
	strings disks_used;
	strings blocks_used;
	Video_Data_Container( std::string id, std::string v_name ) : video_id( id ), video_name( v_name ) {}
};

typedef std::vector<Video_Data_Container> Data;

class Video_Data_Handler {
public:
	Video_Data_Handler();
	void add_video_data( std::string v_id, std::string v_name );
	void set_disks_used( std::string v_id, strings used );
	void set_blocks_used( std::string v_id, strings used );
	void increment_video_order( int times );
	void reset_order();
	int& order();
	virtual ~Video_Data_Handler();
private:
	Data m_data;
	int order_ctr;
};

#endif /* VIDEODATAHANDLER_H_ */
