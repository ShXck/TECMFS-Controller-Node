#ifndef NETWORKHANDLER_H_
#define NETWORKHANDLER_H_
#include <SFML/Network.hpp>
#include "Reader.h"
#include <iostream>
#include <string>
#include <vector>
#include "../Util.h"

#define PORT 7500

namespace network {

class Network_Handler {
public:
	Network_Handler();
	void start();
	void send( std::string msg, int socket );
	const int users_connected() const;
	virtual ~Network_Handler();
private:
	sf::TcpListener m_listener;
	sf::SocketSelector m_selector;
	Reader m_reader;
	std::vector<sf::TcpSocket*> m_users;
};

} /* namespace network */

#endif /* NETWORKHANDLER_H_ */
