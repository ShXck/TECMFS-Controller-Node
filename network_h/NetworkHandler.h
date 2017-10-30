#ifndef NETWORKHANDLER_H_
#define NETWORKHANDLER_H_
#include <SFML/Network.hpp>
#include "Reader.h"
#include <iostream>
#include <string>
#include <vector>

#define PORT 8000

namespace network {

class Network_Handler {
public:
	Network_Handler();
	void start();
	virtual ~Network_Handler();
private:
	sf::TcpListener m_listener;
	sf::SocketSelector m_selector;
	Reader m_reader;
	std::vector<sf::TcpSocket*> m_users;
};

} /* namespace network */

#endif /* NETWORKHANDLER_H_ */
