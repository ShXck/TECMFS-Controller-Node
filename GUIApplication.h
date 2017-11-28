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
	/**
	 * Inicia la ejecución de la GUI.
	 */
	void run();
	virtual ~GUI_Application();
private:
	/**
	 * Asigna valores a los textos.
	 */
	void set_text();
	/**
	 * Asigna las propiedades a los botones.
	 */
	void set_rects();
	/**
	 * Prepara la ventana de la interfaz.
	 */
	void set_window();
	/**
	 * Dibuja los items en la ventana.
	 */
	void draw();
	/**
	 * Maneja cualquier evento.
	 * @param event el evento.
	 */
	void handle_input( const sf::Event& event );
	/**
	 * Verifica que botón se tocó.
	 * @param pos la posición del mouse.
	 */
	void check_button_clicked( sf::Vector2f pos );
	/**
	 * Pone un mensaje en la ventana.
	 * @param msg el mensaje.
	 */
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
