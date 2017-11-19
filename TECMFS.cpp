#include <iostream>
#include "ControllerNode.h"
#include "network_h/NetworkHandler.h"
#include "GUIApplication.h"

int main() {

	//network::Network_Handler net_handler;
	//net_handler.start();

	//Controller_Node _controller;
	//_controller.run();

	GUI_Application gui_app;
	gui_app.run();


	return 0;
}
