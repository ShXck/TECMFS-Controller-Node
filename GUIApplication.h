#ifndef GUIAPPLICATION_H_
#define GUIAPPLICATION_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "ControllerNode.h"
#include <thread>

#define MENU_ITEMS 5
#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 500

class GUI_Application {
public:
	GUI_Application();
	void run();
	virtual ~GUI_Application();
private:
	void set_text();
	void set_rects();
	void set_window();
	void draw();
	void handle_input( const sf::Event& event );
	void check_button_clicked( sf::Vector2f pos );
	void set_action_msg( std::string msg );
private:
	Controller_Node m_controller;
	sf::RenderWindow m_window;
	sf::Text m_text[MENU_ITEMS];
	sf::Font m_font;
	std::vector<sf::RectangleShape> m_buttons;
	sf::RectangleShape m_rect_logo;
	sf::Texture m_logo;
	std::string m_input;
	bool is_ready = false;
};

#endif /* GUIAPPLICATION_H_ */
