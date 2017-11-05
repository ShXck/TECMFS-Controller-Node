#ifndef CEROBOT_H_
#define CEROBOT_H_
#include <iostream>
#include <string>

class CE_Robot {
public:
	CE_Robot();
	void index_folder( std::string path );
	void find_video( std::string video_name ); // Maybe make it return the video so I can pass it over as parameter to play_video( video name ).
	void play_video( std::string video_name );
	virtual ~CE_Robot();
};

#endif /* CEROBOT_H_ */
