#pragma once
#include "Globals.h"
#include "Player.h"

class Settings
{
private:

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
	

	Settings(Vector2f windowsize, Font* font);
	~Settings();

	void Settings_Init(Vector2f windowsize, Font* font);

	void Settings_Update(Vector2f windowsize, Vector2f mousepos, bool* paused, bool* save, bool* quit);
	void Settings_Render(RenderWindow* window);
};

