#pragma once
#include "Graphics.h"

using namespace std;

/**
*  Klasa SpriteCodex s³u¿y do obs³ugi napisów graficznych w grze.
*/
class SpriteCodex
{
public:
	static void DrawGameOver(int x, int y, Graphics& gfx);
	static void DrawTitle(int x, int y, Graphics& gfx);
};