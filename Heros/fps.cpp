/**
 * Fps.cpp
 * Defines the Fps class.
 */

#include "Fps.h"

Fps::Fps() :deltaSum_(0)
{

}

void Fps::update(double delta)
{
	frames_++;
    deltaSum_ += delta;
}

int Fps::fps()
{
    if (deltaSum_>= 0.25)
	{
        fps_ = (double)frames_ / deltaSum_;
		frames_ = 0;
        deltaSum_ = 0;
	}

	return (int)fps_;
}