#include <iostream>
#include "ControllerNode.h"
#include "network_h/NetworkHandler.h"
#include <thread>

int main() {

	//network::Network_Handler net_handler;
	//net_handler.start();

	Controller_Node _controller;
	_controller.run();


	return 0;
}
