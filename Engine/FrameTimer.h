#pragma once
#include <chrono>

/**
* Klasa odpowiadaj¹ca za obs³ugê czasu w grze.
*/
class FrameTimer
{
public:
	FrameTimer();
	float Mark();
private:
	std::chrono::steady_clock::time_point last;
};