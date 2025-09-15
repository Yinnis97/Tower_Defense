#include "Settings.h"

Settings::Settings(Vector2f windowsize)
{
	mousepressed = false;
	pausepressed = false;
	quitpressed = false;
	savepressed = false;
	temppressed = false;
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
	isPressedcolor = new Color(0, 150, 0, 255);
	outlineColor = new Color(120, 120, 120, 255);
	buttonColor = new Color(80, 80, 80, 255);
	barcolor = new Color(100, 100, 100, 255);

	Vector2f buttonSize = { (windowsize.x / 10), (windowsize.y / 32) };
	float outlineSize = (windowsize.x / 1000);

	// Taskbar
	taskbar.setFillColor(*barcolor);
	taskbar.setPosition({ 0.f,0.f });
	taskbar.setSize({ windowsize.x, (windowsize.y / 32) + (2 * outlineSize) });

	// Quit Button
	quitButton.setPosition({ (windowsize.x - (windowsize.x / 10)) - outlineSize, outlineSize });
	quitButton.setFillColor(*buttonColor);
	quitButton.setSize(buttonSize);
	quitButton.setOutlineColor(*outlineColor);
	quitButton.setOutlineThickness(outlineSize);

	// Pause Button
	pauseButton.setPosition({ quitButton.getPosition().x - quitButton.getSize().x, outlineSize });
	pauseButton.setFillColor(*buttonColor);
	pauseButton.setSize(buttonSize);
	pauseButton.setOutlineColor(*outlineColor);
	pauseButton.setOutlineThickness(outlineSize);

	// Extra Button Left
	tempButton.setPosition({ outlineSize, outlineSize });
	tempButton.setFillColor(*buttonColor);
	tempButton.setSize(buttonSize);
	tempButton.setOutlineColor(*outlineColor);
	tempButton.setOutlineThickness(outlineSize);

	// Save Button
	saveButton.setPosition({ tempButton.getPosition().x + tempButton.getSize().x, outlineSize });
	saveButton.setFillColor(*buttonColor);
	saveButton.setSize(buttonSize);
	saveButton.setOutlineColor(*outlineColor);
	saveButton.setOutlineThickness(outlineSize);

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

	// Save text
	save_text.emplace(font);
	save_text->setCharacterSize(windowsize.x / 80);
	save_text->setString("Save");
	save_text->setOrigin({ save_text->getGlobalBounds().size.x / 2, save_text->getGlobalBounds().size.y / 2 });
	save_text->setPosition({ saveButton.getGlobalBounds().getCenter().x, saveButton.getGlobalBounds().getCenter().y - (saveButton.getSize().y / 5) });

	// Temp text
	temp_text.emplace(font);
	temp_text->setCharacterSize(windowsize.x / 80);
	temp_text->setString("Temp");
	temp_text->setOrigin({ temp_text->getGlobalBounds().size.x / 2, temp_text->getGlobalBounds().size.y / 2 });
	temp_text->setPosition({ tempButton.getGlobalBounds().getCenter().x, tempButton.getGlobalBounds().getCenter().y - (tempButton.getSize().y / 5) });
}

void Settings::Settings_Update(Vector2f windowsize, Vector2f mousepos, bool* paused, bool* save, bool* quit)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (!mousepressed)
		{
			mousepressed = true;
			if (pauseButton.getGlobalBounds().contains(mousepos))
			{
				pauseButton.setOutlineColor(*isPressedcolor);
				pause_text->setFillColor(*isPressedcolor);
				pausepressed = true;
			}
			if (quitButton.getGlobalBounds().contains(mousepos))
			{
				quitButton.setOutlineColor(*isPressedcolor);
				quit_text->setFillColor(*isPressedcolor);
				quitpressed = true;
			}
			if (saveButton.getGlobalBounds().contains(mousepos))
			{
				saveButton.setOutlineColor(*isPressedcolor);
				save_text->setFillColor(*isPressedcolor);
				savepressed = true;
			}
			if (tempButton.getGlobalBounds().contains(mousepos))
			{
				tempButton.setOutlineColor(*isPressedcolor);
				temp_text->setFillColor(*isPressedcolor);
				temppressed = true;
			}
		}
	}
	else
	{
		if (pauseButton.getGlobalBounds().contains(mousepos) && pausepressed)
		{
			*paused = !(*paused);
		}
		if (quitButton.getGlobalBounds().contains(mousepos) && quitpressed)
		{
			*quit = true;
		}
		if (saveButton.getGlobalBounds().contains(mousepos) && savepressed)
		{
			*save = true;
		}
		if (tempButton.getGlobalBounds().contains(mousepos) && temppressed)
		{
			std::cout << "temp\n";
		}

		pauseButton.setOutlineColor(*outlineColor);
		pause_text->setFillColor(*outlineColor);
		quitButton.setOutlineColor(*outlineColor);
		quit_text->setFillColor(*outlineColor);
		saveButton.setOutlineColor(*outlineColor);
		save_text->setFillColor(*outlineColor);
		tempButton.setOutlineColor(*outlineColor);
		temp_text->setFillColor(*outlineColor);

		pausepressed = false;
		quitpressed = false;
		savepressed = false;
		temppressed = false;
		mousepressed = false;
	}
}

void Settings::Settings_Render(RenderWindow* window)
{
	window->draw(taskbar);

	if (savepressed)
	{
		window->draw(tempButton);
		window->draw(saveButton);
	}
	else
	{
		window->draw(saveButton);
		window->draw(tempButton);
	}
	

	if (pausepressed)
	{
		window->draw(quitButton);
		window->draw(pauseButton);
	}
	else
	{
		window->draw(pauseButton);
		window->draw(quitButton);
	}

	window->draw(*temp_text);
	window->draw(*save_text);
	window->draw(*pause_text);
	window->draw(*quit_text);
}
