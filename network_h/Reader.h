#ifndef NETWORK_H_READER_H_
#define NETWORK_H_READER_H_
#include <iostream>
#include <string>
#include <SFML/Network.hpp>

namespace network {

class Reader {
public:
	Reader();
	void read( std::string msg, sf::TcpSocket* user );
	virtual ~Reader();
private:
	std::string process_msg( std::string msg );
};

} /* namespace network */

#endif /* NETWORK_H_READER_H_ */
