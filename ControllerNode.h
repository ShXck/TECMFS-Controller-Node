#ifndef CONTROLLERNODE_H_
#define CONTROLLERNODE_H_
#include "CERobot.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/videoio.hpp>
#include <thread>
#include <bitset>
#include <sys/types.h>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include "Util.h"
#include "VideoDataHandler.h"
#include "DiskStatusHandler.h"
#include "network_h/JSONHandler.h"
#include "network_h/NetworkHandler.h"

#define DISK_NUMBER 2
#define MAX_BLOCKS 10

using namespace cv;
using namespace boost::filesystem;

typedef unsigned char byte;
typedef std::vector<std::string> Strings;
typedef std::vector<byte> Bytes;
typedef std::vector<Mat> Frames;

enum class Instruction {
	STORE_INSTR = 1,
	RETRV_INSTR = 2
};

class Controller_Node {
public:
	Controller_Node();
	void run();
	void index_folder( std::string folder );
	virtual ~Controller_Node();
private:
	void split_video( std::string video_name, std::string folder );
	Bytes mat_to_byte( Mat img );
	Mat bytes_to_mat( Bytes bytes, int w, int h );
	std::string byte_to_bit( byte source );
	byte bit_to_byte( std::string bit );
	void set_data( Frames frames, std::string video_name );
	void distribute_data( std::string video_id, std::string result );
private:
	network::Network_Handler net_handler;
	Video_Data_Handler data_handler;
	Disk_Status_Handler disk_handler;
};

#endif /* CONTROLLERNODE_H_ */
