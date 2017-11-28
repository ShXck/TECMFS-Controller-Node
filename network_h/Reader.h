#ifndef NETWORK_H_READER_H_
#define NETWORK_H_READER_H_
#include <iostream>
#include <string>
#include <SFML/Network.hpp>
#include "JSONHandler.h"
#include "ProcessedTmp.h"
#include "Instructions.h"

namespace network {

class Reader {
public:
	Reader();
	/**
	 * Lee los datos provenientes de los discos.
	 * @param packet el packet con la información.
	 * @param user el socket emisor.
	 * @return un contenedor con la información recuperada.
	 */
	Processed_Tmp read( sf::Packet packet, sf::TcpSocket* user );
	virtual ~Reader();
private:
	std::string process_msg( std::string msg );
};

} /* namespace network */

#endif /* NETWORK_H_READER_H_ */
