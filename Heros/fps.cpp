#include <ctime>
#include "fps.h"

Fps::Fps() :starttime(time(0))
{

}

void Fps::Update()
{
	frames++;
}

int Fps::GetFps()
{
	time_t timepassed = time(0);

	if (timepassed - starttime > 0.25)
	{
        fps = (double)frames / (timepassed - starttime);
		frames = 0;
		starttime = timepassed;
	}

	return fps;
}