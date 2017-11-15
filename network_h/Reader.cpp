#include "Reader.h"

namespace network {

Reader::Reader() { }

Processed_Tmp Reader::read( sf::Packet packet, sf::TcpSocket* user ) {

	std::string _bytes;
	std::string dec_msg;

	if( packet >> _bytes >> dec_msg ) {

		std::cout << dec_msg << std::endl;

		int _instruction = JHandler::get_value( dec_msg.c_str(), "instruction" ).GetInt();

		if( _instruction != 4 ) {

			std::string vid_id = JHandler::get_value( dec_msg.c_str(), "id").GetString();

			int _mat = JHandler::get_value( dec_msg.c_str(), "mat" ).GetInt();

			int _order = JHandler::get_value( dec_msg.c_str(), "order" ).GetInt();

			return Processed_Tmp( vid_id, _bytes, _instruction, _mat, _order );
		} else {
			return Processed_Tmp( _instruction );
		}
	}

	return Processed_Tmp();
}

Reader::~Reader() { }

} /* namespace network */
