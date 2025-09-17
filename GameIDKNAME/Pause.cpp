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
	Color color_pause(255,255,255,255);
	float text_correction = windowsize.y / 32 * 5;

	// Background
	background.setFillColor(Color::White);
	background.setSize(windowsize);
	background.setPosition({ 0,0 });

	// Shaders
	backgroundShader.loadFromFile("Shaders/menubackground.frag", Shader::Type::Fragment);
	backgroundShader.setUniform("resolution", windowsize);

	// Pause text
	pause_text.emplace(*font);
	pause_text->setCharacterSize(windowsize.x / 10);
	pause_text->setFillColor(color_pause);
	pause_text->setString("Paused");
	pause_text->setOrigin({pause_text->getGlobalBounds().size.x / 2, (pause_text->getGlobalBounds().size.x / 2) });
	pause_text->setPosition({ windowsize.x / 2, windowsize.y / 2 + text_correction });
}

void Pause::Pause_Update(Vector2f mousepos, Vector2f windowsize)
{

}

void Pause::Pause_Render(RenderWindow* window)
{
	window->draw(background, &backgroundShader);
	window->draw(*pause_text);
}
