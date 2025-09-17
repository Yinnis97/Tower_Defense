#pragma once
#include <iostream>
#include <sstream> 
#include "math.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu
{
private:

	bool mousepressed;

	std::optional<Text> header_text;
	std::optional<Text> load_text;
	std::optional<Text> credits_text;
	std::optional<Text> start_text;

	RectangleShape background;
	RectangleShape startbutton;
	RectangleShape loadbutton;
	RectangleShape creditsbutton;

	Shader backgroundShader;

	Clock shaderClock;

	Color* blue_green_color;
	Color* dark_gray_color;
	Color* light_gray_color;

	bool startpressed;
	bool loadpressed;
	bool creditspressed;

public:
	Menu(Vector2f windowsize, Font* font);
	~Menu();

	void Menu_Init(Vector2f windowsize, Font* font);
	
	void Menu_LoadCredits();

	void Menu_Update(Vector2f mousepos, Vector2f windowsize, bool* inMenu, bool* loadGame);
	void Menu_Render(RenderWindow* window);
};

