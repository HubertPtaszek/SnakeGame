#include "FrameTimer.h"

using namespace std::chrono; /*! < przeste� nazw zawierajaca zegar */

/**
* Konstruktor FrameTimer ustawia obecny czas ramki 
*/
FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

/**
* Funkcja Mark przestawia znacznik czau i oblicza jego r�znic� od ostatniego jej wywowo�ania.
*
* \return r�nice czasu ktory min��.
*/
float FrameTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}
