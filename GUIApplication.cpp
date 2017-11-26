
#include "GUIApplication.h"

GUI_Application::GUI_Application() {
	set_window();
	set_rects();
	set_text();
}

void GUI_Application::run() {

	std::thread t( [this](){
		m_controller.run();
	});
	t.detach();

	while( m_window.isOpen() ) {
		sf::Event _event;

		while( m_window.pollEvent( _event ) ) {
			handle_input( _event );
		}

		m_window.clear( sf::Color::White );
		draw();
		m_window.display();
	}
}

void GUI_Application::set_text() {

	if( !m_font.loadFromFile( "assets/droid.ttf" ) ) {
		std::cout << "ERROR OPENING FONT" << std::endl;
	}

	std::string buttons_caps[] = { "Index folder", "Load Video", "Play Video", "", "" };

	for( int i = 0; i < MENU_ITEMS; i++ ) {
		m_text[i].setFont( m_font );
		m_text[i].setString( buttons_caps[i] );
		m_text[i].setCharacterSize( 30 );
		m_text[i].setFillColor( sf::Color::White );
		m_text[i].setStyle( sf::Text::Bold );
		m_text[i].setPosition( sf::Vector2f( m_buttons[i].getPosition().x + 25, m_buttons[i].getPosition().y + 5 ) );
	}

	m_text[MENU_ITEMS - 2].setFillColor( sf::Color::Black );
	m_text[MENU_ITEMS - 1].setFillColor( sf::Color::Black );

	m_text[MENU_ITEMS - 1].setPosition( sf::Vector2f( 25, 450 ) );
}

void GUI_Application::set_rects() {

	int _pos = 170;
	int _distance = 70;

	for( int i = 0; i < MENU_ITEMS - 1; i++ ) {
		m_buttons.emplace_back( sf::Vector2f( 250, 50 ) );
		m_buttons[i].setFillColor( sf::Color::Black );
		m_buttons[i].setPosition( 50, _pos );
		_pos += _distance;
	}

	m_buttons[MENU_ITEMS - 2].setFillColor( sf::Color( 222, 223, 224 ) );

	m_rect_logo.setFillColor( sf::Color::White );
	m_rect_logo.setSize( sf::Vector2f( 350, 100 ) );
	m_rect_logo.setPosition( sf::Vector2f( 20, 20 ) );
	if( !m_logo.loadFromFile( "assets/mfs3.png") ) std::cout << "ERROR LOADING IMG" << std::endl;
	m_rect_logo.setTexture( &m_logo );
}

void GUI_Application::set_window() {
	m_window.create( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "TECMFS - Controller Node", sf::Style::Close );
}

void GUI_Application::draw() {

	m_window.draw( m_rect_logo );

	for( auto rect : m_buttons ) m_window.draw( rect );

	for( int i = 0; i < MENU_ITEMS; i++ ) m_window.draw( m_text[i] );
}

void GUI_Application::check_button_clicked( sf::Vector2f pos ) {

	if( m_buttons[0].getGlobalBounds().contains( pos ) ) {
		m_controller.index_folder( "/home/marcelo/Desktop/TECMFS_Folder" );

	} else if( m_buttons[1].getGlobalBounds().contains( pos ) ) {
		std::string video_name = m_text[MENU_ITEMS - 2].getString();
		bool video_exists = m_controller.video_exist( video_name );
		if( video_exists ) {
			m_controller.retrieve( video_name );
			m_input.clear();
			m_text[MENU_ITEMS - 2].setString( m_input );
		} else {
			set_action_msg( "Video Not Found" );
		}

	} else if( m_buttons[2].getGlobalBounds().contains( pos ) ) {
		m_controller.create_video();
		//m_controller.play_video();
	}
}

void GUI_Application::set_action_msg( std::string msg ) {
	m_text[MENU_ITEMS - 1].setString( msg );
}

void GUI_Application::handle_input( const sf::Event& event ) {

	switch( event.type ) {
		case sf::Event::Closed: {
			m_window.close();
			break;
		}
		case sf::Event::MouseButtonReleased: {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition( m_window );
			sf::Vector2f mouse_pos_f( static_cast<float>( mouse_pos.x ), static_cast<float>( mouse_pos.y ) );
			check_button_clicked( mouse_pos_f );
			break;
		}
		case sf::Event::EventType::KeyReleased: {
			switch( event.key.code ) {
				case sf::Keyboard::A: {
					m_input += "a";
					break;
				}
				case sf::Keyboard::B: {
					m_input += "b";
					break;
				}
				case sf::Keyboard::C: {
					m_input += "c";
					break;
				}
				case sf::Keyboard::D: {
					m_input += "d";
					break;
				}
				case sf::Keyboard::E: {
					m_input += "b";
					break;
				}
				case sf::Keyboard::F: {
					m_input += "f";
					break;
				}
				case sf::Keyboard::G: {
					m_input += "g";
					break;
				}
				case sf::Keyboard::H: {
					m_input += "h";
					break;
				}
				case sf::Keyboard::I: {
					m_input += "i";
					break;
				}
				case sf::Keyboard::J: {
					m_input += "j";
					break;
				}
				case sf::Keyboard::K: {
					m_input += "k";
					break;
				}
				case sf::Keyboard::L: {
					m_input += "l";
					break;
				}
				case sf::Keyboard::M: {
					m_input += "m";
					break;
				}
				case sf::Keyboard::N: {
					m_input += "n";
					break;
				}
				case sf::Keyboard::O: {
					m_input += "o";
					break;
				}
				case sf::Keyboard::P: {
					m_input += "p";
					break;
				}
				case sf::Keyboard::Q: {
					m_input += "q";
					break;
				}
				case sf::Keyboard::R: {
					m_input += "r";
					break;
				}
				case sf::Keyboard::S: {
					m_input += "s";
					break;
				}
				case sf::Keyboard::T: {
					m_input += "t";
					break;
				}
				case sf::Keyboard::U: {
					m_input += "u";
					break;
				}
				case sf::Keyboard::V: {
					m_input += "v";
					break;
				}
				case sf::Keyboard::W: {
					m_input += "w";
					break;
				}
				case sf::Keyboard::X: {
					m_input += "x";
					break;
				}
				case sf::Keyboard::Y: {
					m_input += "y";
					break;
				}
				case sf::Keyboard::Z: {
					m_input += "z";
					break;
				}
				case sf::Keyboard::Period: {
					m_input += ".";
					break;
				}
				case sf::Keyboard::Num4:
				case sf::Keyboard::Numpad4: {
					m_input += "4";
					break;
				}
				case sf::Keyboard::Return: {
					is_ready = true;
				}
				case sf::Keyboard::BackSpace: {
					m_input.pop_back();
					break;
				}
			}
			m_text[MENU_ITEMS - 2].setString( m_input );
		}
	}
}

GUI_Application::~GUI_Application() { }

