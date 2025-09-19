#pragma once
#include "main.hpp"

class Devourable {
    public:
        Devourable(float sat);
        void devour(Actor * owner, Actor * devourer);
    private:
        float saturation;
};