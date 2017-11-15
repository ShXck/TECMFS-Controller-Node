
#include "JSONHandler.h"

namespace JHandler {

	str build_video_data( str video_id, str bits, int instruction, int chunk_order, int mat_number  ) {
		JDoc _doc;
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
		_doc.AddMember( "mat", mat_number, _alloc );

		rapidjson::StringBuffer str_buffer;
		Writer _writer( str_buffer );
		_doc.Accept( _writer );

		return str_buffer.GetString();
	}

	str build_video_data( str video_id, int instruction, int chunk_order, int mat_number  ) {
		JDoc _doc;
		_doc.SetObject();
		Alloc _alloc = _doc.GetAllocator();

		{
			rapidjson::Value str_id;
			str_id.SetString( video_id.c_str(), _alloc );
			_doc.AddMember( "id", str_id, _alloc );
		}

		_doc.AddMember( "instruction", instruction, _alloc );
		_doc.AddMember( "order", chunk_order, _alloc );
		_doc.AddMember( "mat", mat_number, _alloc );

		rapidjson::StringBuffer str_buffer;
		Writer _writer( str_buffer );
		_doc.Accept( _writer );

		return str_buffer.GetString();
	}

	str build_instruction_msg( int instruction ) {
		JDoc _doc;
		_doc.SetObject();
		Alloc _alloc = _doc.GetAllocator();

		_doc.AddMember( "instruction", instruction, _alloc );

		rapidjson::StringBuffer str_buffer;
		Writer _writer( str_buffer );
		_doc.Accept( _writer );

		return str_buffer.GetString();
	}

	str build_retrv_msg( int instruction, int mat_number, std::string video_id ) {
		JDoc _doc;
		_doc.SetObject();
		Alloc _alloc = _doc.GetAllocator();

		{
			rapidjson::Value data_val;
			data_val.SetString( video_id.c_str(), _alloc );
			_doc.AddMember( "id", data_val, _alloc );
		}

		_doc.AddMember( "instruction", instruction, _alloc );
		_doc.AddMember( "mat", mat_number, _alloc );

		rapidjson::StringBuffer str_buffer;
		Writer _writer( str_buffer );
		_doc.Accept( _writer );

		return str_buffer.GetString();
	}

	rapidjson::Value& get_value( c_char json, c_char json_key ) {

		JDoc _doc;
		_doc.Parse( json );

		Alloc _alloc = _doc.GetAllocator();

		rapidjson::Value str_key;
		str_key.SetString( json_key, _alloc );

		rapidjson::Value& _val = _doc[ str_key ];

		return _val;
	}
}
