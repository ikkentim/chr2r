#pragma once

#include <ctime>

class Fps
{
private:
	time_t starttime;
	bool first = true;
	int frames = 0;
	double fps = 0.0;
public:
	Fps();
	void Update();
	int GetFps();
};