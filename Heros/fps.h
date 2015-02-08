#include <ctime>

class Fps
{
private:
	time_t starttime;
	bool first = true;
	int frames = 0;
	float fps = 0.0f;
public:
	Fps();
	void Update();
	int GetFps();
};