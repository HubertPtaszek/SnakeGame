#pragma once
#include "Graphics.h"

using namespace std;

/**
*  Klasa SpriteCodex s�u�y do obs�ugi napis�w graficznych w grze.
*/
class SpriteCodex
{
public:
	static void DrawGameOver(int x, int y, Graphics& gfx);
	static void DrawTitle(int x, int y, Graphics& gfx);
};