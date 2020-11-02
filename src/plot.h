#pragma once

#include <cstdint>
#include <functional>

struct Plot
{
   struct Function{
      std::function<float(float)> _func;
      std::string _name;
   };

   void update(const Function& func);
   void draw();

   Function _func;
};
