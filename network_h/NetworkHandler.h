#ifndef NETWORKHANDLER_H_
#define NETWORKHANDLER_H_
#include <SFML/Network.hpp>
#include "Reader.h"
#include <iostream>
#include <string>
#include <vector>
#include "../Util.h"
#include "ProcessedTmp.h"
#include "Instructions.h"

#define PORT 7500

namespace network {

typedef std::vector<Processed_Tmp> Response_Data;

struct Response_Data_Container {
	Response_Data request_result;
	bool can_join;
	Response_Data_Container( ) : can_join( false ) {}
};

class Network_Handler {
public:
	Network_Handler();
	void start();
	void send( std::string msg, int socket );
	void send( std::string bytes, std::string msg, int socket );
	void clean_data();
	const int users_connected() const;
	Response_Data_Container* request_data();
	void switch_data_state( bool state );
	void clean_data_response();
	virtual ~Network_Handler();
private:
	sf::TcpListener m_listener;
	sf::SocketSelector m_selector;
	Reader m_reader;
	std::vector<sf::TcpSocket*> m_users;
	Response_Data_Container m_container;
};

} /* namespace network */

#endif /* NETWORKHANDLER_H_ */
