/**
 * Fps.h
 * Declares the Fps class.
 */
#pragma once

// Represents an fps counter
class Fps
{
public:
    // Default constructor
	Fps();

    // Updates for the specified delta time
	void update(double delta);

    // Gets the update count last second
	int fps();

private:
	double deltaSum_;
	int frames_ = 0;
	double fps_ = 0.0;
};