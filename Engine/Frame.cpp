#include "Frame.h"
#include "Snake.h"
#include <assert.h>

Frame::Frame(const GameSettings& settings, Graphics& gfx) : dimension(settings.GetTileSize()), width(settings.GetFrameWidth()), height(settings.GetFrameHeight()), contents(width * height, CellContents::Empty), gfx(gfx)
{ }

/**
 * Funkcja "rysuje" pojedyncza kom�rk�.
 * Pobiera dwie warto�ci wska�nik na klas� Location oraz klas� Color.
 *
 * \param[in] \& loc wspo�rz�dne gdzie narysowa� kom�rk�.
 * \param[in] c kolor rysowanej kom�rki.
 */
void Frame::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);	/*!< sprawdza podane wyrazenie czy jest r�ne od zera (prawdziwe). Je�li nie � program zostanie zatrzymany, podane zostanie miejsce b��du i wyra�enie kt�re spowodowa�o b��d */
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = x + frameWidth + framePadding;
	const int off_y = y + frameWidth + framePadding;

	gfx.DrawRectDim(loc.x * dimension + off_x + cellPadding, loc.y * dimension + off_y + cellPadding, dimension - cellPadding * 2, dimension - cellPadding * 2, c); /*!
																																									* Funkcja rysuje kom�rk� o podanych wsp�rz�dnych i kolorze.
																																									*/
}

/**
 * Funkcja pobiera szeroko�� Grid-a (w tym prztpadku obszaru roboczego).
 *
 * \return liczb� typu int odpowiadaj�c� szeroko�ci.
 */
int Frame::GetGridWidth() const
{
	return width;
}

/**
 * Funkcja pobiera wysoko�� Grid-a (w tym prztpadku obszaru roboczego).
 *
 * \return liczb� typu int odpowiadaj�c� wysoko�ci.
 */
int Frame::GetGridHeight() const
{
	return height;
}


/**
 * Funkcja sprawdza czy wsp�rz�dne s� wewn�trz ramki.
 *
 * \return prawde jezeli tak w inym wypadku fa�sz.
 */
bool Frame::IsInsideFrame(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}


/**
 * Funkcja sprawdza kontekst kom�rki.
 *
 * \return kontekst (typ komorki owoc, pusta itd.).
 */
Frame::CellContents Frame::GetContents(const Location& loc) const
{
	return contents[loc.y * width + loc.x];
}

/**
 * Funkcja zmienia kontekst kom�rki.
 */
void Frame::ConsumeContents(const Location& loc)
{
	assert(GetContents(loc) == CellContents::Food || GetContents(loc) == CellContents::Poison);
	contents[loc.y * width + loc.x] = CellContents::Empty;
}

/**
 * Funkcja tworzy kom�rk� z kontekstem.
 *
 * \param[in] \& rng losowe wspo�rz�dne (mt19937 - struktura zawarta we frameworku).
 * \param[in] \& snake klasa zawieraj�ca parametry w�a.
 * \param[in] contentsType typ generyczny okre�laj�cy kontekst jaki utworzy�.
 *
 */
void Frame::SpawnContents(mt19937 & rng, const Snake & snake, CellContents contentsType)
{
	uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || GetContents(newLoc) != CellContents::Empty);

	contents[newLoc.y * width + newLoc.x] = contentsType;
}

/**
 * Funkcja "rysuje" ramk� gry i nie zwraca nic.
 */
void Frame::DrawFrame()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (frameWidth + framePadding) * 2 + height * dimension;
	const int right = left + (frameWidth + framePadding) * 2 + width * dimension;
	gfx.DrawRect(left, top, right, top + frameWidth, frameColor); // g�ra
	gfx.DrawRect(left, bottom - frameWidth, right, bottom, frameColor); // d�
	gfx.DrawRect(right - frameWidth, top + frameWidth, right, bottom - frameWidth, frameColor); // prawo 
	gfx.DrawRect(left, top + frameWidth, left + frameWidth, bottom - frameWidth, frameColor); // lewo
}

/**
 * Funkcja "rysuje" kom�rki zale�nie od pobranego kontekstu.
 */
void Frame::DrawCells()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			switch (GetContents({ x,y }))
			{
			case Frame::CellContents::Obstacle:
				DrawCell({ x,y }, obstacleColor);
				break;
			case Frame::CellContents::Food:
				DrawCell({ x,y }, foodColor);
				break;
			case Frame::CellContents::Poison:
				DrawCell({ x,y }, poisonColor);
				break;
			}
		}
	}
}
