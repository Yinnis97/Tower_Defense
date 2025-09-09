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
	Color outlineColor(150, 0, 0, 255);
	Color buttonColor(0, 50, 100, 255);

	Vector2f buttonSize = { (windowsize.x / 10), (windowsize.y / 32) };
	float outlineSize = (windowsize.x / 1000);

	// Taskbar
	taskbar.setFillColor(color);
	taskbar.setPosition({ 0.f,0.f });
	taskbar.setSize({ windowsize.x, (windowsize.y / 32) + (2 * outlineSize) });
	
	// Quit Button
	quitButton.setPosition({ (windowsize.x - (windowsize.x / 10)) - outlineSize, outlineSize });
	quitButton.setFillColor(buttonColor);
	quitButton.setSize(buttonSize);
	quitButton.setOutlineColor(outlineColor);
	quitButton.setOutlineThickness(outlineSize);

	// Pause Button
	pauseButton.setPosition({ quitButton.getPosition().x - quitButton.getSize().x, outlineSize});
	pauseButton.setFillColor(buttonColor);
	pauseButton.setSize(buttonSize);
	pauseButton.setOutlineColor(outlineColor);
	pauseButton.setOutlineThickness(outlineSize);

	// Extra Button Left
	extra1Button.setPosition({ outlineSize, outlineSize });
	extra1Button.setFillColor(buttonColor);
	extra1Button.setSize(buttonSize);
	extra1Button.setOutlineColor(outlineColor);
	extra1Button.setOutlineThickness(outlineSize);

	// Extra Button Left 2
	extra2Button.setPosition({ extra1Button.getPosition().x + extra1Button.getSize().x, outlineSize });
	extra2Button.setFillColor(buttonColor);
	extra2Button.setSize(buttonSize);
	extra2Button.setOutlineColor(outlineColor);
	extra2Button.setOutlineThickness(outlineSize);

}

void Settings::Settings_Update(Vector2f windowsize)
{

}

void Settings::Settings_Render(RenderWindow* window)
{
	window->draw(taskbar);
	window->draw(extra1Button);
	window->draw(extra2Button);
	window->draw(pauseButton);
	window->draw(quitButton);
}
