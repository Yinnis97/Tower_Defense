#pragma once
#include <iostream>
#include <sstream> 
#include "math.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Pause
{
private:
	RectangleShape background;

	Shader backgroundShader;

	std::optional<Text> pause_text;
	Font font;

public:
	Pause(Vector2f windowsize);
	~Pause();

	void Pause_Init(Vector2f windowsize);

	void Pause_Update(Vector2f mousepos, Vector2f windowsize);
	void Pause_Render(RenderWindow* window);
};

