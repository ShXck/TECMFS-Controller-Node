#include "NetworkHandler.h"

namespace network {

Network_Handler::Network_Handler() {
	m_listener.listen( PORT );
	m_selector.add( m_listener );
}

void Network_Handler::start() {

	std::cout << "Server Running" << std::endl;

	while ( true ) {
		if( m_selector.wait() ) {
			if( m_selector.isReady( m_listener ) ) {
				sf::TcpSocket *_socket = new sf::TcpSocket;
				m_listener.accept( *_socket );
				m_users.push_back( _socket );
				m_selector.add( *_socket );
				std::cout << "New client online" << std::endl;
			} else {
				for( unsigned int i = 0; i < m_users.size(); i++ ) {
					if( m_selector.isReady( *m_users[i] ) ){
						sf::Packet _packet;
						if( m_users[i]->receive( _packet ) == sf::Socket::Done ) {
							std::string _msg;
							if( _packet >> _msg ) m_reader.read( _msg, m_users[i] );
						}
					}
				}
			}
		}
	}
	for( std::vector<sf::TcpSocket*>::iterator it = m_users.begin(); it != m_users.end(); it++ ) {
		delete *it;
	}
}

void Network_Handler::send( std::string msg, int socket ) {
	if( socket < m_users.size() ) {
		std::string compressed_msg = util::compress( msg, Z_BEST_COMPRESSION );
		sf::Packet _packet;
		if( _packet << compressed_msg ) m_users[socket]->send( _packet );
	}
}

const int Network_Handler::users_connected() const {
	return m_users.size();
}

Network_Handler::~Network_Handler() { }

} /* namespace network */
