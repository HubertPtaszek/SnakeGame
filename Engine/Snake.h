#pragma once
#include "Frame.h"
#include <vector>

using namespace std;

/**
* Klasa Snake zawiera w sobie klasê odpowidaj¹c¹ za cia³o wê¿a, a tak¿e funkcjê obs³uguj¹ce zachowania w grze wê¿a.
*/
class Snake
{
	class Segment
	{
		Location loc;
		Color c;
	public:
		Segment(const Location& loc);
		Segment(Color c);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Frame& brd) const;
		const Location& GetLocation() const;
	};
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nBodyColors = 4;
	static constexpr Color bodyColors[nBodyColors] = {
		{ 10,100,32 },
		{ 10,130,48 },
		{ 18,160,48 },
		{ 10,130,48 }
	};
	vector<Segment> segments;
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void GrowAndMoveBy(const Location& delta_loc);
	void Draw(Frame& brd) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
	int GetLength() const;
};