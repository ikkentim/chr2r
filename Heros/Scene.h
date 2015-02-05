#include <Windows.h>
#include "Keys.h"

#pragma once

class Scene {
public:
    virtual void Update(float, Keys) = 0;
};