#pragma once
#include <chrono>

/*!
* @brief Klasa odpowiadaj�ca za obs�ug� czasu w grze.
*/
class FrameTimer
{
public:
	FrameTimer();
	float Mark();
private:
	std::chrono::steady_clock::time_point last;
};