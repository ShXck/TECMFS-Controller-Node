#include <iostream>
#include "ControllerNode.h"
#include "network_h/NetworkHandler.h"
#include <thread>

int main() {

	//network::Network_Handler net_handler;
	//net_handler.start();

	Controller_Node _controller;
	_controller.run();


	/*std::thread t([&_controller]() {
		std::string _action;
		while( true ) {
			std::cout << "SELECCIONE LA ACCIÓN A REALIZAR" << "\n\t 1. Indexar carpeta con videos." << std::endl;
			std::getline( std::cin, _action );
			int int_action = std::stoi( _action );
			switch( int_action ) {
				case 1: {
					_controller.index_folder( "/home/marcelo/Desktop/TECMFS_Folder" );
					break;
				}
			}
		}
	});
	t.detach();*/

	return 0;
}
