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
	Processed_Tmp read( sf::Packet packet, sf::TcpSocket* user );
	virtual ~Reader();
private:
	std::string process_msg( std::string msg );
};

} /* namespace network */

#endif /* NETWORK_H_READER_H_ */
