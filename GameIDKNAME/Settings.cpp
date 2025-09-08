#include "Settings.h"

Settings::Settings(Vector2f windowsize)
{
	Settings_Init(windowsize);
}

Settings::~Settings()
{
}

void Settings::Settings_Init(Vector2f windowsize)
{
	if (!font.openFromFile("Fonts/PixeloidSans.ttf"))
	{
		std::cout << "Error: Can't load Font! -> Settings_Init" << std::endl;
	}

	Color color(100, 100, 100, 255);

	Vector2f buttonSize = { (windowsize.x / 10), (windowsize.y / 32) };

	// Taskbar
	taskbar.setFillColor(color);
	taskbar.setPosition({ 0.f,0.f });
	taskbar.setSize({ windowsize.x, (windowsize.y / 32) });
	
	// Quit Button
	quitButton.setPosition({ windowsize.x - (windowsize.x / 10),0.f });
	quitButton.setSize(buttonSize);
	// Pause Button
	pauseButton.setPosition({ windowsize.x - ((windowsize.x / 10)*2),0.f });
	pauseButton.setSize(buttonSize);

	// Shader Buttons
	if (!buttonShader.loadFromFile("Shaders/buttonShader.frag", Shader::Type::Fragment))
	{
		std::cout << "Error shader -> settings.cpp" << std::endl;
	}

	buttonShader.setUniform("resolution", buttonSize);
}

void Settings::Settings_Update(Vector2f windowsize)
{

}

void Settings::Settings_Render(RenderWindow* window)
{
	window->draw(taskbar);
	window->draw(pauseButton, &buttonShader);
	window->draw(quitButton, &buttonShader);
}
