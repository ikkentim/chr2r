#include <ctime>
#include "fps.h"

Fps::Fps() :lastframetime_(time(0))
{

}

void Fps::Update()
{
	frames_++;
}

int Fps::GetFps()
{
	time_t currenttime = time(0);

	if (currenttime - lastframetime_ > 0.25)
	{
		fps_ = (double)frames_ / (currenttime - lastframetime_);
		frames_ = 0;
		lastframetime_ = currenttime;
	}

	return (int)fps_;
}