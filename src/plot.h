#pragma once

#include <cstdint>
#include <functional>

namespace Plot
{
void update(std::function<float(float)> func);
void draw();
}
