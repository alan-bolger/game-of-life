#ifndef APPLICATION_H
#define APPLICATION_H

#include "Globals.h"
#include "PixelGrid.h"

#include <SFML/Graphics.hpp>
#include <cstdint>

class Application
{
public:
	Application();
	~Application();
	void run();

private:
	sf::RenderWindow m_window;
	sf::Font m_font;
	bool m_exitGame{ false };
	int *m_output;
	int *m_state;
	PixelGrid m_pixelGrid{ Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT };
	sf::RenderTexture m_renderTexture;

	void processEvents();
	void update();
	void draw();
	int cell(int t_x, int t_y);
	void drawString(int t_x, int t_y, std::string t_string, sf::Color t_colour, int t_size = 20);
};

#endif // !APPLICATION_H