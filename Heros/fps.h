#pragma once

class Fps
{
private:
	double deltaSum_;
	int frames_ = 0;
	double fps_ = 0.0;
public:
	Fps();
	void update(double delta);
	int fps();
};