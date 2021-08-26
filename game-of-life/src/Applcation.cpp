#include "Application.h"

/// <summary>
/// Application constructor.
/// </summary>
Application::Application() : m_window{ sf::VideoMode{ Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 32 }, "Conway's Game of Life", sf::Style::Default }
{
	// Allocate memory for arrays
	m_output = new int [Globals::WORLD_WIDTH * Globals::WORLD_HEIGHT];
	m_state = new int[Globals::WORLD_WIDTH * Globals::WORLD_HEIGHT];

	// Set all values in arrays to zero
	for (int i = 0; i < Globals::WORLD_WIDTH * Globals::WORLD_HEIGHT; ++i)
	{
		m_output[i] = 0;
		m_state[i] = 0;
	}

	// Load app font
	m_font.loadFromMemory(Globals::DEFAULT_FONT, (size_t)75864 * sizeof(uint8_t));

	// Initialise startup cells
	for (int i = 0; i < Globals::WORLD_WIDTH * Globals::WORLD_HEIGHT; i++)
	{
		m_state[i] = rand() % 2;
	}		

	// Initialise render texture
	m_renderTexture.create(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
}

/// <summary>
/// Application destructor.
/// </summary>
Application::~Application()
{
	delete[] m_output;
	delete[] m_state;
}

/// <summary>
/// Run.
/// </summary>
void Application::run()
{
	sf::Clock f_clock;
	sf::Time f_timeSinceLastUpdate = sf::Time::Zero;
	sf::Time f_timePerFrame = sf::seconds(1.f / 60.f);

	while (m_window.isOpen() && !m_exitGame)
	{
		processEvents();
		f_timeSinceLastUpdate += f_clock.restart();

		while (f_timeSinceLastUpdate > f_timePerFrame)
		{
			f_timeSinceLastUpdate -= f_timePerFrame;
			processEvents();
			update();
			draw();
		}
	}
}

/// <summary>
/// Process events.
/// </summary>
void Application::processEvents()
{
	sf::Event f_event;

	while (m_window.pollEvent(f_event))
	{
		if (sf::Event::Closed == f_event.type)
		{
			m_window.close();
		}

		if (sf::Event::KeyPressed == f_event.type)
		{
			if (sf::Keyboard::Escape == f_event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update.
/// </summary>
void Application::update()
{
	// Store output state
	for (int i = 0; i < Globals::WORLD_WIDTH * Globals::WORLD_HEIGHT; i++)
	{
		m_output[i] = m_state[i];
	}

	for (int x = 1; x < Globals::WORLD_WIDTH - 1; x++)
	{
		for (int y = 1; y < Globals::WORLD_HEIGHT - 1; y++)
		{
			int f_neighbours = cell(x - 1, y - 1) + cell(x - 0, y - 1) + cell(x + 1, y - 1) +
							   cell(x - 1, y + 0) +			 0		   + cell(x + 1, y + 0) +
							   cell(x - 1, y + 1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);

			// Set cell state
			if (cell(x, y) == 1)
			{
				m_state[y * Globals::WORLD_WIDTH + x] = f_neighbours == 2 || f_neighbours == 3;
			}				
			else
			{
				m_state[y * Globals::WORLD_WIDTH + x] = f_neighbours == 3;
			}

			// Set pixel colour
			if (cell(x, y) == 1)
			{
				m_pixelGrid.setPixel(x, y, sf::Color::Green);
			}				
			else
			{
				m_pixelGrid.setPixel(x, y, sf::Color::Black);
			}				
		}
	}

	drawString(Globals::SCREEN_WIDTH - 265, Globals::SCREEN_HEIGHT - 30, "CONWAY'S GAME OF LIFE", sf::Color::White);

	m_renderTexture.display();
}

/// <summary>
/// Draw.
/// </summary>
void Application::draw()
{
	m_window.clear();

	sf::Sprite f_pixelGridSprite(m_pixelGrid.getPixelBuffer());
	f_pixelGridSprite.scale(sf::Vector2f(4, 4));

	sf::Sprite f_renderTextureSprite(m_renderTexture.getTexture());
	
	m_window.draw(f_pixelGridSprite);
	m_window.draw(f_renderTextureSprite);

	m_window.display();	
}

/// <summary>
/// Access 1D array using 2D coordinates.
/// </summary>
/// <param name="t_x">The X position.</param>
/// <param name="t_y">The Y position.</param>
/// <returns>The value of the specified cell.</returns>
int Application::cell(int t_x, int t_y)
{
	return m_output[t_y * Globals::WORLD_WIDTH + t_x];
}

/// <summary>
/// Draws a string to a given position.
/// </summary>
/// <param name="t_x">The X position.</param>
/// <param name="t_y">The Y position.</param>
/// <param name="t_string">The string to draw.</param>
/// <param name="t_colour">The colour of the string.</param>
/// <param name="t_size">The character size (default value of 20).</param>
void Application::drawString(int t_x, int t_y, std::string t_string, sf::Color t_colour, int t_size)
{
	sf::Text f_text;

	f_text.setCharacterSize(t_size);
	f_text.setFont(m_font);
	f_text.setString(t_string);
	f_text.setPosition(t_x, t_y);
	f_text.setFillColor(t_colour);

	m_renderTexture.draw(f_text);
}

