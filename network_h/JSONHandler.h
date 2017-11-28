#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <vector>

typedef rapidjson::Document::AllocatorType& Alloc;
typedef rapidjson::Writer< rapidjson::StringBuffer > Writer;
typedef rapidjson::Document JDoc;
typedef std::vector<std::string> Strings;
typedef std::string str;
typedef const char* c_char;

namespace JHandler {

	/**
	 * Construye el mensaje para guardar información de un video.
	 * @param video_id la id del video.
	 * @param bits los bits del video.
	 * @param instruction la instruccion.
	 * @param chunk_order el orden del frame.
	 * @param mat_number el númer de frame.
	 * @return el mensaje JSON construido.
	 */
	str build_video_data( str video_id, str bits, int instruction, int chunk_order, int mat_number  );  // {id,data,instruction,order,mat}

	str build_video_data( str video_id, int instruction, int chunk_order, int mat_number  );

	/**
	 * Construye un mensaje con una instrucción.
	 * @param instruction la instrucción.
	 * @return el mensaje JSON construido.
	 */
	str build_instruction_msg( int instruction ); // {instruction}

	/**
	 * Construye un mensaje de recuperación de datos.
	 * @param instruction la instrucción.
	 * @param mat_number el número de frame.
	 * @param video_id la id del video.
	 * @return el mensaje JSON construido.
	 */
	str build_retrv_msg( int instruction, int mat_number, std::string video_id ); // {instruction,mat,id}

	/**
	 * Obtiene un valor de un JSON.
	 * @param json el mensaje.
	 * @param json_key la key del valor.
	 * @return el valor que corresponde a la key.
	 */
	rapidjson::Value& get_value( c_char json, c_char json_key );
}

