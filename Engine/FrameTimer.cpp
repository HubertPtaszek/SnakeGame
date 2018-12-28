#include "FrameTimer.h"

using namespace std::chrono; /*! < przesteñ nazw zawierajaca zegar */

/**
* Konstruktor FrameTimer ustawia obecny czas ramki 
*/
FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

/**
* Funkcja Mark przestawia znacznik czau i oblicza jego róznicê od ostatniego jej wywowo³ania.
*
* \return ró¿nice czasu ktory min¹³.
*/
float FrameTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}
