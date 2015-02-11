#pragma once

#include <ctime>

class Fps
{
private:
	time_t lastframetime_;
	int frames_ = 0;
	double fps_ = 0.0;
public:
	Fps();
	void Update();
	int GetFps();
};