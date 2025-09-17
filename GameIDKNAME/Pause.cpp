#include "Pause.h"

Pause::Pause(Vector2f windowsize, Font* font)
{
	Pause_Init(windowsize, font);
}

Pause::~Pause()
{

}

void Pause::Pause_Init(Vector2f windowsize, Font* font)
{
	// Background
	background.setFillColor(Color::White);
	background.setSize(windowsize);
	background.setPosition({ 0,0 });

	// Shaders
	backgroundShader.loadFromFile("Shaders/menubackground.frag", Shader::Type::Fragment);
	backgroundShader.setUniform("resolution", windowsize);
}

void Pause::Pause_Update(Vector2f mousepos, Vector2f windowsize)
{

}

void Pause::Pause_Render(RenderWindow* window)
{
	window->draw(background, &backgroundShader);
}
