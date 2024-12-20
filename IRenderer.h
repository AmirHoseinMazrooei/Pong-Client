#pragma once
#include "GameObject.h"

class IRenderer: public Component {
public:
    virtual ~IRenderer() = default;
    virtual void Draw() = 0;
};