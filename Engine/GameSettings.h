#pragma once
#include <string>

/**
* Klasa obs³ugujaca ustawienia gry tj nazwa, predkosc, ilosc bonusow itd.
*/
class GameSettings
{
	int tileSize;
	int frameWidth;
	int frameHeight;
	int nPoison;
	int nFood;
	float speedupRate;
public:
	GameSettings(const std::string& filename);
	int GetTileSize() const;
	int GetFrameWidth() const;
	int GetFrameHeight() const;
	int GetPoisonAmount() const;
	int GetFoodAmount() const;
	float GetSpeedupRate() const;
};