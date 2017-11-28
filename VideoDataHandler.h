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
	double _fps;
	Video_Data_Container( std::string id, std::string v_name, int x, int y, int frames, double fps ) : video_id( id ), video_name( v_name ), dim_x( x ), dim_y( y ), _frames( frames ), _fps( fps ) {}
};

typedef std::vector<Video_Data_Container> Data;

class Video_Data_Handler {
public:
	Video_Data_Handler();
	/**
	 * Añade información de un video.
	 * @param v_id la id del video.
	 * @param v_name el nombre del video.
	 * @param dim_x el ancho del video.
	 * @param dim_y el alto del video.
	 * @param frames el número de frames.
	 * @param fps los fps del video.
	 */
	void add_video_data( std::string v_id, std::string v_name, int dim_x, int dim_y , int frames, double fps );
	/**
	 * Incrementa el orden del video.
	 * @param times el número de incrementos.
	 */
	void increment_video_order( int times );
	/**
	 * Obtiene la id de un video.
	 * @param v_name el nombre del video.
	 * @return la id del video.
	 */
	std::string get_id( std::string v_name );
	/**
	 * Obtiene el número de frames de un video.
	 * @param v_name el nombre del video.
	 * @return el númerp de frames.
	 */
	int frames_of( std::string v_name );
	/**
	 * Obtiene los fps de un video.
	 * @param v_name el nombre del video.
	 * @return los fps.
	 */
	double fps_of( std::string v_name );
	/**
	 * Reinicia el orden de video.
	 */
	void reset_order();
	/**
	 * Retorna el orden que se lleva de los frames de un video.
	 * @return el orden de los frames.
	 */
	int& order();
	/**
	 * @return el contador de discos.
	 */
	int& disk();
	/**
	 * Reinicia el contador de discos.
	 */
	void restart_disk_ctr();
	/**
	 * Incrementa el contador de discos.
	 */
	void increment_disk_ctr();
	virtual ~Video_Data_Handler();
private:
	Data m_data;
	int order_ctr;
	int disk_ctr;
};

#endif /* VIDEODATAHANDLER_H_ */
