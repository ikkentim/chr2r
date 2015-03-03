#pragma once

#include <Windows.h>
#include "Keys.h"


class Scene {
public:
	virtual ~Scene(){};
	virtual void Start(){};
    virtual void Update(double, Keys) = 0;
    virtual void Render(double, HDC graphics) = 0;
};