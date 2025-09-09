#include "Menu.h"

Menu::Menu(Vector2f windowsize)
{
	mousepressed = false;
	startpressed = false;
	loadpressed = false;
	creditspressed = false;
	Menu_Init(windowsize);
	shaderClock.restart();
}

Menu::~Menu()
{

}

void Menu::Menu_Init(Vector2f windowsize)
{
	// Spacing for buttons
	float spacing = windowsize.y / 15;

	// Font
	if (!font.openFromFile("Fonts/PixeloidSans.ttf"))
	{
		std::cout << "Error: Can't load Font! -> Menu_Init" << std::endl;
	}

	// Colors
	dark_gray_color = new Color(96, 96, 96, 255);
	light_gray_color = new Color(150, 150, 150, 255);
	blue_green_color = new Color(0, 50, 80, 255);

	// Background
	background.setFillColor(Color::White);
	background.setSize(windowsize);
	background.setPosition({ 0,0 });

	// Shaders
	backgroundShader.loadFromFile("Shaders/menubackground.frag", Shader::Type::Fragment);
	backgroundShader.setUniform("resolution", windowsize);

	// Start Button
	startbutton.setFillColor(*light_gray_color);
	startbutton.setOutlineThickness(windowsize.x / 1000);
	startbutton.setOutlineColor(*dark_gray_color);
	startbutton.setSize({ windowsize.x / 10, windowsize.y / 20 });
	startbutton.setOrigin({ startbutton.getSize().x / 2, startbutton.getSize().y / 2 });
	startbutton.setPosition({ windowsize.x / 2,windowsize.y / 2 });

	// Load Button
	loadbutton.setFillColor(*light_gray_color);
	loadbutton.setOutlineThickness(windowsize.x / 1000);
	loadbutton.setOutlineColor(*dark_gray_color);
	loadbutton.setSize({ windowsize.x / 10, windowsize.y / 20 });
	loadbutton.setOrigin({ loadbutton.getSize().x / 2, loadbutton.getSize().y / 2 });
	loadbutton.setPosition({ windowsize.x / 2,(windowsize.y / 2) + spacing });

	// Credits Button
	creditsbutton.setFillColor(*light_gray_color);
	creditsbutton.setOutlineThickness(windowsize.x / 1000);
	creditsbutton.setOutlineColor(*dark_gray_color);
	creditsbutton.setSize({ windowsize.x / 10, windowsize.y / 20 });
	creditsbutton.setOrigin({ creditsbutton.getSize().x / 2, creditsbutton.getSize().y / 2 });
	creditsbutton.setPosition({ windowsize.x / 2,loadbutton.getPosition().y + spacing});

	// Start Button Text
	start_text.emplace(font);
	start_text->setCharacterSize(windowsize.x / 40);
	start_text->setFillColor(*dark_gray_color);
	start_text->setString("Start");
	start_text->setOrigin({ start_text->getGlobalBounds().size.x / 2, start_text->getGlobalBounds().size.y / 2 });
	start_text->setPosition({ windowsize.x / 2, (windowsize.y / 2) - (windowsize.y/90)});

	// Load Button Text
	load_text.emplace(font);
	load_text->setCharacterSize(windowsize.x / 40);
	load_text->setFillColor(*dark_gray_color);
	load_text->setString("Load");
	load_text->setOrigin({ load_text->getGlobalBounds().size.x / 2, load_text->getGlobalBounds().size.y / 2 });
	load_text->setPosition({ windowsize.x / 2, start_text->getPosition().y + spacing});

	// Credits Button Text
	credits_text.emplace(font);
	credits_text->setCharacterSize(windowsize.x / 40);
	credits_text->setFillColor(*dark_gray_color);
	credits_text->setString("Credits");
	credits_text->setOrigin({ credits_text->getGlobalBounds().size.x / 2, credits_text->getGlobalBounds().size.y / 2 });
	credits_text->setPosition({ windowsize.x / 2, load_text->getPosition().y + spacing});

	// Header Text
	header_text.emplace(font);
	header_text->setCharacterSize(windowsize.x / 20);
	header_text->setFillColor(*dark_gray_color);
	header_text->setString("Tower Defence By Y.K.");
	header_text->setOrigin({ header_text->getGlobalBounds().size.x / 2, header_text->getGlobalBounds().size.y / 2 });
	header_text->setPosition({ windowsize.x/2, windowsize.y/15 });

}

void Menu::Menu_LoadCredits()
{

}

void Menu::Menu_Update(Vector2f mousepos, Vector2f windowsize, bool* inMenu, bool* loadGame)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (!mousepressed)
		{
			mousepressed = true;
			if (startbutton.getGlobalBounds().contains(mousepos))
			{
				startbutton.setOutlineColor(*blue_green_color);
				start_text->setFillColor(*blue_green_color);
				startpressed = true;
			}
			if (loadbutton.getGlobalBounds().contains(mousepos))
			{
				loadbutton.setOutlineColor(*blue_green_color);
				load_text->setFillColor(*blue_green_color);
				loadpressed = true;
			}
			if (creditsbutton.getGlobalBounds().contains(mousepos))
			{
				creditsbutton.setOutlineColor(*blue_green_color);
				credits_text->setFillColor(*blue_green_color);
				creditspressed = true;
			}
		}
	}
	else
	{
		if (startbutton.getGlobalBounds().contains(mousepos) && startpressed)
		{
			*inMenu = false;
		}
		if (loadbutton.getGlobalBounds().contains(mousepos) && loadpressed)
		{
			*loadGame = true;
		}
		if (creditsbutton.getGlobalBounds().contains(mousepos) && creditspressed)
		{
			Menu_LoadCredits();
		}

		startbutton.setOutlineColor(*dark_gray_color);
		start_text->setFillColor(*dark_gray_color);
		loadbutton.setOutlineColor(*dark_gray_color);
		load_text->setFillColor(*dark_gray_color);
		creditsbutton.setOutlineColor(*dark_gray_color);
		credits_text->setFillColor(*dark_gray_color);

		creditspressed = false;
		loadpressed = false;
		startpressed = false;
		mousepressed = false;
	}
}

void Menu::Menu_Render(RenderWindow* window)
{
	window->draw(background,&backgroundShader);
	window->draw(startbutton);
	window->draw(loadbutton);
	window->draw(creditsbutton);
	window->draw(*header_text);
	window->draw(*start_text);
	window->draw(*load_text);
	window->draw(*credits_text);
}
