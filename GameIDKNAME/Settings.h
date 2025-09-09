#pragma once
#include <iostream>
#include <sstream> 
#include "math.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Settings
{
private:
	Font font;

	RectangleShape taskbar;
	RectangleShape quitButton;
	RectangleShape pauseButton;
	RectangleShape extra1Button;
	RectangleShape extra2Button;

	std::optional<Text> quit_text;
	std::optional<Text> pause_text;

	bool mousepressed;
	bool pausepressed;
	bool quitpressed;

	Color* color1;
	Color* color2;

public:
	

	Settings(Vector2f windowsize);
	~Settings();

	void Settings_Init(Vector2f windowsize);

	void Settings_Update(Vector2f windowsize, Vector2f mousepos, bool* paused);
	void Settings_Render(RenderWindow* window);
};

