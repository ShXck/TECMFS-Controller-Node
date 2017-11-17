#ifndef VIDEODATAHANDLER_H_
#define VIDEODATAHANDLER_H_
#include <string>
#include <iostream>
#include <vector>

#define NOT_FOUND 0

typedef std::vector<std::string> strings;

struct Video_Data_Container {
	std::string video_id;
	std::string video_name;
	unsigned int dim_x;
	unsigned int dim_y;
	unsigned int _frames;
	Video_Data_Container( std::string id, std::string v_name, int x, int y, int frames ) : video_id( id ), video_name( v_name ), dim_x( x ), dim_y( y ), _frames( frames ) {}
};

typedef std::vector<Video_Data_Container> Data;

class Video_Data_Handler {
public:
	Video_Data_Handler();
	void add_video_data( std::string v_id, std::string v_name, int dim_x, int dim_y , int frames );
	void increment_video_order( int times );
	std::string get_id( std::string v_name );
	int frames_of( std::string v_name );
	void reset_order();
	int& order();
	int& disk();
	void restart_disk_ctr();
	void increment_disk_ctr();
	virtual ~Video_Data_Handler();
private:
	Data m_data;
	int order_ctr;
	int disk_ctr;
};

#endif /* VIDEODATAHANDLER_H_ */
