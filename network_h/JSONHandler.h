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

	str build_video_data( str video_id, str bits, int instruction, int chunk_order, int mat_number  );  // {id,data,instruction,order,mat}

	str build_video_data( str video_id, int instruction, int chunk_order, int mat_number  );

	str build_instruction_msg( int instruction ); // {instruction}

	str build_retrv_msg( int instruction, int mat_number, std::string video_id ); // {instruction,mat,id}

	rapidjson::Value& get_value( c_char json, c_char json_key );
}

