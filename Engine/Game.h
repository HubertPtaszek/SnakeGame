#pragma once
#include "Keyboard.h"
#include "Graphics.h"
#include "Frame.h"
#include "Snake.h"
#include "Font.h"
#include <random>
#include "SoundEffect.h"
#include "FrameTimer.h"

using namespace std;

/**
* Klasa Game jest g³ówn¹ klas¹ aplikacji, obs³uguje funkcjonalnoœci, wygl¹d oraz dzwiêki.
*/
class Game
{
	void ComposeFrame();
	void UpdateModel();
	MainWindow& wnd;
	Graphics gfx;
	GameSettings settings = "settings.txt";
	Frame brd;

	static constexpr Color textColor = Colors::White;
	Font font = "Fixedsys16x28.bmp";

	Snake snake;
	Location delta_loc = { 1,0 };
	mt19937 rng;
	FrameTimer ft;
	SoundEffect sfxEat = SoundEffect({ L"Sounds\\Eat.wav" });
	SoundEffect sfxSlither = SoundEffect({ L"Sounds\\Slither0.wav",L"Sounds\\Slither1.wav",L"Sounds\\Slither2.wav" });
	static constexpr float snekMovePeriodMin = 0.040f;
	static constexpr float snekMovePeriodSpeedup = 0.15f;
	int nPoison;
	int nFood;
	float snakeMovePeriod = 0.4f;
	float snakeMoveCounter = 0.0f;
	float snakeSpeedupFactor;
	bool gameIsOver = false;
	bool gameIsStarted = false;
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
};