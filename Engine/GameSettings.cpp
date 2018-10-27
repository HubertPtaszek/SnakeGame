#include "GameSettings.h"
#include <fstream>

using namespace std;

GameSettings::GameSettings(const string& filename)
{
	fstream in(filename);
	for (string line; getline(in, line); )
	{
		if (line == "[Tile Size]")
		{
			in >> tileSize;
		}
		else if (line == "[Frame Dimensions]")
		{
			in >> frameWidth >> frameHeight;
		}
		else if (line == "[Poison Amount]")
		{
			in >> nPoison;
		}
		else if (line == "[Food Amount]")
		{
			in >> nFood;
		}
		else if (line == "[Speedup Rate]")
		{
			in >> speedupRate;
		}
		else if (line.empty())
		{

		}
		else
		{
			throw runtime_error("Runtime error in line: " + line);
		}
	}
}

int GameSettings::GetTileSize() const
{
	return tileSize;
}

int GameSettings::GetFrameWidth() const
{
	return frameWidth;
}

int GameSettings::GetFrameHeight() const
{
	return frameHeight;
}

int GameSettings::GetPoisonAmount() const
{
	return nPoison;
}

int GameSettings::GetFoodAmount() const
{
	return nFood;
}

float GameSettings::GetSpeedupRate() const
{
	return speedupRate;
}
