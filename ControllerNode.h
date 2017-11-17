#ifndef CONTROLLERNODE_H_
#define CONTROLLERNODE_H_
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/videoio.hpp>
#include <thread>
#include <bitset>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include "Util.h"
#include "VideoDataHandler.h"
#include "DiskStatusHandler.h"
#include "network_h/JSONHandler.h"
#include "network_h/NetworkHandler.h"
#include "network_h/Instructions.h"
#include <algorithm>

#define DISK_NUMBER 3
#define MAX_BLOCKS 6

using namespace cv;
using namespace boost::filesystem;

typedef unsigned char byte;
typedef std::vector<std::string> Strings;
typedef std::vector<byte> Bytes;
typedef std::vector<Mat> Frames;

struct Render_Data {
	Bytes _bytes;
	int _mat;
	std::string _video;
	Render_Data( Bytes bytes, int mat, std::string id ) : _bytes( bytes ), _mat( mat ), _video( id ) { }
};

typedef std::vector<Render_Data> Video_Render;

class Controller_Node {
public:
	Controller_Node();
	void run();
	virtual ~Controller_Node();
private:
	void index_folder( std::string folder );
	void split_video( std::string video_name, std::string folder );
	Bytes mat_to_byte( Mat img );
	Mat bytes_to_mat( Bytes bytes, int w, int h );
	std::string byte_to_bit( byte source );
	byte bit_to_byte( std::string bit );
	void set_data( Frames frames, std::string video_name );
	void distribute_data( std::string video_id, std::string result, int mat_number );
	void retrieve( std::string video_name, int mat_number = -1 );
	Strings split_mat( std::string bytes );
	void wait_for_retrieve();
	void process_segment();
	void render( Bytes& mat_bytes, int mat );
	void create_video();
private:
	network::Network_Handler net_handler;
	Video_Data_Handler data_handler;
	Disk_Status_Handler disk_handler;
	Video_Render m_render;
	Frames m_video;
};

#endif /* CONTROLLERNODE_H_ */
