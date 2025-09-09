#include "Settings.h"

Settings::Settings(Vector2f windowsize)
{
	mousepressed = false;
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
	color1 = new Color(100, 0, 0, 255);
	color2 = new Color(150, 0, 0, 255);

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
	pauseButton.setPosition({ quitButton.getPosition().x - quitButton.getSize().x, outlineSize });
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

	// Pause text
	pause_text.emplace(font);
	pause_text->setCharacterSize(windowsize.x / 80);
	pause_text->setString("Pause");
	pause_text->setOrigin({pause_text->getGlobalBounds().size.x/2, pause_text->getGlobalBounds().size.y/2});
	pause_text->setPosition({ pauseButton.getGlobalBounds().getCenter().x, pauseButton.getGlobalBounds().getCenter().y - (pauseButton.getSize().y/5)});

	// Quit text
	quit_text.emplace(font);
	quit_text->setCharacterSize(windowsize.x / 80);
	quit_text->setString("Quit");
	quit_text->setOrigin({ quit_text->getGlobalBounds().size.x / 2, quit_text->getGlobalBounds().size.y / 2 });
	quit_text->setPosition({ quitButton.getGlobalBounds().getCenter().x, quitButton.getGlobalBounds().getCenter().y - (quitButton.getSize().y / 5) });

}

void Settings::Settings_Update(Vector2f windowsize, Vector2f mousepos, bool* paused)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (!mousepressed)
		{
			mousepressed = true;
			if (pauseButton.getGlobalBounds().contains(mousepos))
			{
				pauseButton.setOutlineColor(*color1);
				pause_text->setFillColor(*color1);
				pausepressed = true;
			}
			if (quitButton.getGlobalBounds().contains(mousepos))
			{
				quitButton.setOutlineColor(*color1);
				quit_text->setFillColor(*color1);
				quitpressed = true;
			}
		}
	}
	else
	{
		if (pauseButton.getGlobalBounds().contains(mousepos) && pausepressed)
		{
			*paused = true;
		}
		if (quitButton.getGlobalBounds().contains(mousepos) && quitpressed)
		{
			std::cout << "quit\n";
		}

		pauseButton.setOutlineColor(*color2);
		pause_text->setFillColor(*color2);
		quitButton.setOutlineColor(*color2);
		quit_text->setFillColor(*color2);

		pausepressed = false;
		quitpressed = false;
		mousepressed = false;
	}
}

void Settings::Settings_Render(RenderWindow* window)
{
	window->draw(taskbar);
	window->draw(extra1Button);
	window->draw(extra2Button);
	window->draw(pauseButton);
	window->draw(quitButton);
	window->draw(*pause_text);
	window->draw(*quit_text);
}
