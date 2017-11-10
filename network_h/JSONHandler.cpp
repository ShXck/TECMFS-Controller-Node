
#include "JSONHandler.h"

namespace JHandler {

	str build_video_data( str video_id, str bits, int instruction, int chunk_order ) {
		Doc _doc;
		_doc.SetObject();
		Alloc _alloc = _doc.GetAllocator();

		{
			rapidjson::Value str_id;
			str_id.SetString( video_id.c_str(), _alloc );
			_doc.AddMember( "id", str_id, _alloc );
		}

		{
			rapidjson::Value str_data;
			str_data.SetString( bits.c_str(), _alloc );
			_doc.AddMember( "data", str_data, _alloc );
		}

		_doc.AddMember( "instruction", instruction, _alloc );
		_doc.AddMember( "order", chunk_order, _alloc );

		rapidjson::StringBuffer str_buffer;
		Writer _writer( str_buffer );
		_doc.Accept( _writer );

		return str_buffer.GetString();
	}

	str build_instruction_msg( int instruction ) {
		Doc _doc;
		_doc.SetObject();
		Alloc _alloc = _doc.GetAllocator();

		_doc.AddMember( "instruction", instruction, _alloc );

		rapidjson::StringBuffer str_buffer;
		Writer _writer( str_buffer );
		_doc.Accept( _writer );

		return str_buffer.GetString();
	}

}
