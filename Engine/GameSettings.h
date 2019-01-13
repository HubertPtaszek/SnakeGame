#pragma once
#include <string>

/*!
* @brief Klasa obs�uguj�ca ustawienia gry tj. nazwa, pr�dko��, ilo�� bonus�w itd.
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