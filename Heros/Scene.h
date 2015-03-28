#pragma once

#include <Windows.h>
#include "Keys.h"


class Scene {
public:
    virtual ~Scene(){}
    virtual void start() = 0;
    virtual void update(double, Keys) = 0;
    virtual void render(HDC graphics) = 0;
};