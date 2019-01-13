#pragma once

#include "Graphics.h"
#include "Surface.h"
#include "Vec2.h"
/*!
* @brief Klasa obs³uguj¹ca czcionki (na bazie bit mapy) zmodyfikowana na potrzeby naszej aplikacji.
*/
class Font
{
	RectI MapGlyphRect(char c) const;
	Surface surface;
	int glyphWidth;
	int glyphHeight;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	Color chroma;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
public:
	Font(const string& filename, Color chroma = Colors::White);
	void DrawTextSub(const string& text, const Vei2& pos, Color color, Graphics& gfx) const;
};
