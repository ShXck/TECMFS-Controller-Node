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
							Processed_Tmp resp_result = m_reader.read( _packet, m_users[i] );
							if( resp_result._instruction != (int)Instruction::JOIN_INSTR ) {
								m_container.request_result.push_back( resp_result );
							} else  {
								switch_data_state( true );
							}
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
		std::string a = util::compress( "NONE", Z_BEST_COMPRESSION );
		sf::Packet _packet;
		if( _packet << a << compressed_msg ) m_users[socket]->send( _packet );
	}
}

void Network_Handler::send( std::string bytes, std::string msg, int socket ) {
	if( socket < m_users.size() ) {
		std::string compressed_msg = util::compress( msg, Z_BEST_COMPRESSION );
		std::string compressed_bytes = util::compress( bytes, Z_BEST_COMPRESSION );
		sf::Packet _packet;
		if( _packet << compressed_bytes << compressed_msg ) m_users[socket]->send( _packet );
	}
}

void Network_Handler::switch_data_state(  bool state ) {
	m_container.can_join = state;
}

void Network_Handler::clean_data_response() {
	m_container.request_result.clear();
}

const int Network_Handler::users_connected() const {
	return m_users.size();
}

void Network_Handler::clean_data() {
	m_container.request_result.clear();
}

Response_Data_Container* Network_Handler::request_data() {
	return &m_container;
}

Network_Handler::~Network_Handler() { }

} /* namespace network */
