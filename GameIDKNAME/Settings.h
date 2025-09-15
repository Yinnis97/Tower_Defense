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
	RectangleShape tempButton;
	RectangleShape saveButton;

	std::optional<Text> quit_text;
	std::optional<Text> pause_text;
	std::optional<Text> save_text;
	std::optional<Text> temp_text;

	bool mousepressed;
	bool pausepressed;
	bool quitpressed;
	bool savepressed;
	bool temppressed;

	Color* isPressedcolor;
	Color* outlineColor;
	Color* buttonColor;
	Color* barcolor;

public:
	

	Settings(Vector2f windowsize);
	~Settings();

	void Settings_Init(Vector2f windowsize);

	void Settings_Update(Vector2f windowsize, Vector2f mousepos, bool* paused);
	void Settings_Render(RenderWindow* window);
};

