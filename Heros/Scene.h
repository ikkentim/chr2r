#include <Windows.h>
#include "Keys.h"

#pragma once

class Scene {
public:
    virtual void Update(double, Keys) = 0;
    virtual void Render(double) = 0;
};