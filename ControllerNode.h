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

struct Tmp_Data {
	std::string curr_vid;
	double curr_vid_fps;

	void reset() {
		curr_vid.clear();
		curr_vid_fps = 0.0;
	}
};

typedef std::vector<Render_Data> Video_Render;

class Controller_Node {
public:
	Controller_Node();
	/**
	 * Inicia la ejecución del controller.
	 */
	void run();

	/**
	 * Indexa el folder con videos.
	 * @param folder el path del folder.
	 */
	void index_folder( std::string folder );
	/**
	 * Recupera los datos de un video de los discos.
	 * @param video_name el nombre del video.
	 * @param mat_number el número de imagen que se quiere.
	 */
	void retrieve( std::string video_name, int mat_number = -1 );
	/**
	 * Construye el video con los datos recuperados de los discos.
	 */
	void create_video();
	/**
	 * Reproduce el video creado. [NOT TESTED]
	 */
	void play_video();
	/**
	 * Verifica que haya un registro de un video deseado.
	 * @param name el nombre del video.
	 * @return si existe o no.
	 */
	bool video_exist( std::string name );
	virtual ~Controller_Node();
private:
	/**
	 * Divide un video en frames.
	 * @param video_name el nombre del video.
	 * @param folder el path del video.
	 */
	void split_video( std::string video_name, std::string folder );
	/**
	 * Convierte una imagen en bytes.
	 * @param img la imagen.
	 * @return la representación en bytes de la imagen.
	 */
	Bytes mat_to_byte( Mat img );
	/**
	 * Convierte bytes en una imagen.
	 * @param bytes los bytes de la imagen.
	 * @param w el ancho de la imagen.
	 * @param h la altura de la imagen.
	 * @return la imagen hecha a partir de los bytes.
	 */
	Mat bytes_to_mat( Bytes bytes, int w, int h );
	/**
	 * Convierte bytes en bits binarios.
	 * @param source el byte.
	 * @return la representación binaria del byte.
	 */
	std::string byte_to_bit( byte source );
	/**
	 * Convierte binario a bytes.
	 * @param bit el binario de 8 bits.
	 * @return el byte construido con el binario.
	 */
	byte bit_to_byte( std::string bit );
	/**
	 * Construye la información de un registro de video.
	 * @param frames el número de frames del video.
	 * @param video_name el nombre del video.
	 * @param fps los fps del video.
	 */
	void set_data( Frames frames, std::string video_name, double fps );
	/**
	 * Distribuye los datos en los discos.
	 * @param video_id la id del video.
	 * @param result los bytes de una imagen.
	 * @param mat_number el número de frame.
	 */
	void distribute_data( std::string video_id, std::string result, int mat_number );
	/**
	 * Descompone los bytes de una imagen en partes para ser distribuidas.
	 * @param bytes la representación de bytes de una imagen.
	 * @return las partes en se dividieron los bytes.
	 */
	Strings split_mat( std::string bytes );
	/**
	 * ESpera la respuesta de uno de los discos.
	 */
	void wait_for_retrieve();
	/**
	 * Procesa un frame recuperado de un disco.
	 */
	void process_segment();
	/**
	 * Renderiza los bytes recuperados de los frames.
	 * @param mat_bytes los bytes recuperados.
	 * @param mat el número de mat.
	 */
	void render( Bytes& mat_bytes, int mat, std::string vid_id );
private:
	network::Network_Handler net_handler;
	Video_Data_Handler data_handler;
	Disk_Status_Handler disk_handler;
	Video_Render m_render;
	Frames m_video;
	Tmp_Data m_tmp;
};

#endif /* CONTROLLERNODE_H_ */
