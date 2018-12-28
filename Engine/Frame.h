#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>
#include "GameSettings.h"
#include <vector>

using namespace std;

class Frame
{
	static constexpr Color frameColor = Colors::Gray;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = { 64,8,64 };
	static constexpr Color foodColor = Colors::Red;
	int dimension;
	static constexpr int cellPadding = 1;
	int width;
	int height;
	static constexpr int frameWidth = 4;
	static constexpr int framePadding = 2;
	static constexpr int x = 70;
	static constexpr int y = 50;
	Graphics& gfx; /*!< Wska�nik na klas�  opisuj�cej wygl�d graficzny "Graphics". */
public:
	enum class CellContents /*!< Typ generyczny "CellContents" okre�laj�cy typ danej kom�rki (trucizna, jedzenie itd). */
	{
		Empty,
		Obstacle,
		Food,
		Poison
	};
	Frame(const GameSettings& settings, Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideFrame(const Location& loc) const;
	CellContents GetContents(const Location& loc) const;
	void ConsumeContents(const Location& loc);
	void SpawnContents(mt19937& rng, const class Snake& snake, CellContents contents);
	void DrawFrame();
	void DrawCells();
private:
	vector<CellContents> contents;  /*!< Klasa vector zawieraj�ca obiekty typu generycznego "CellContents". */
};