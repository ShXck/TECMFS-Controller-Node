#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <vector>

typedef rapidjson::Document::AllocatorType& Alloc;
typedef rapidjson::Writer< rapidjson::StringBuffer > Writer;
typedef rapidjson::Document Doc;
typedef std::vector<std::string> Strings;
typedef std::string str;

namespace JHandler {

	str build_video_data( str video_id, str bits, int instruction );


}

