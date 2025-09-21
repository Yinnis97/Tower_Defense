#pragma once
#include "Globals.h"

class Pause
{
private:
	RectangleShape background;

	Shader backgroundShader;

	std::optional<Text> pause_text;

public:
	Pause(Vector2f windowsize, Font* font);
	~Pause();

	void Pause_Init(Vector2f windowsize, Font* font);

	void Pause_Update(Vector2f mousepos, Vector2f windowsize);
	void Pause_Render(RenderWindow* window);
};

