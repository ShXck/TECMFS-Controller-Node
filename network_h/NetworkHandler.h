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
	/**
	 * Inicia la ejecución.
	 */
	void start();
	/**
	 * Envía información a un socket.
	 * @param msg el mensaje.
	 * @param socket la posición del socket.
	 */
	void send( std::string msg, int socket );
	/**
	 * Envía información a un socket que incluye bytes.
	 * @param bytes los bytes.
	 * @param msg el mensaje.
	 * @param socket la posición del socket.
	 */
	void send( std::string bytes, std::string msg, int socket );
	/**
	 * Reinicia la información del Response Data Container.
	 */
	const int users_connected() const;
	/**
	 * @return El contenedor con los datos de la respuesta.
	 */
	Response_Data_Container* request_data();
	/**
	 * Cambia el estado de respuesta.
	 * @param state el estado.
	 */
	void switch_data_state( bool state );
	/**
	 *
	 */
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
