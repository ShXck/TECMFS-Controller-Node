
#include "ProcessedTmp.h"

Processed_Tmp::Processed_Tmp( std::string video_id, std::string data, int instruction, int mat, int order ) :
vid_id( video_id ), _data( data ), _instruction( instruction ), _mat( mat ), _order( order ) { }

Processed_Tmp::Processed_Tmp( int instr ) : _instruction( instr ) { }

Processed_Tmp::Processed_Tmp() { }

void Processed_Tmp::delete_data() {
	_data.clear();
}

bool Processed_Tmp::operator <( const Processed_Tmp& tmp ) {
	return _order < tmp._order;
}

Processed_Tmp::~Processed_Tmp() { }

