#include "Plant.h"

Plant::Plant(Environment& environment, float startX, float startY)
    : x(startX)
    , y(startY)
    , environment(environment)
{
}