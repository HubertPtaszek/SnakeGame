#include "Frame.h"
#include "Snake.h"
#include <assert.h>

Frame::Frame(const GameSettings& settings, Graphics& gfx)
	:
	dimension(settings.GetTileSize()),
	width(settings.GetFrameWidth()),
	height(settings.GetFrameHeight()),
	contents(width * height, CellContents::Empty),
	gfx(gfx)
{
}

void Frame::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = x + frameWidth + framePadding;
	const int off_y = y + frameWidth + framePadding;

	gfx.DrawRectDim(loc.x * dimension + off_x + cellPadding, loc.y * dimension + off_y + cellPadding, dimension - cellPadding * 2, dimension - cellPadding * 2, c);
}

int Frame::GetGridWidth() const
{
	return width;
}

int Frame::GetGridHeight() const
{
	return height;
}

bool Frame::IsInsideFrame(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

Frame::CellContents Frame::GetContents(const Location& loc) const
{
	return contents[loc.y * width + loc.x];
}

void Frame::ConsumeContents(const Location& loc)
{
	assert(GetContents(loc) == CellContents::Food || GetContents(loc) == CellContents::Poison);
	contents[loc.y * width + loc.x] = CellContents::Empty;
}

void Frame::SpawnContents(std::mt19937 & rng, const Snake & snake, CellContents contentsType)
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

void Frame::DrawFrame()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (frameWidth + framePadding) * 2 + height * dimension;
	const int right = left + (frameWidth + framePadding) * 2 + width * dimension;
	gfx.DrawRect(left, top, right, top + frameWidth, frameColor); // góra
	gfx.DrawRect(left, bottom - frameWidth, right, bottom, frameColor); // dó³
	gfx.DrawRect(right - frameWidth, top + frameWidth, right, bottom - frameWidth, frameColor); // prawo 
	gfx.DrawRect(left, top + frameWidth, left + frameWidth, bottom - frameWidth, frameColor); // lewo
}

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
