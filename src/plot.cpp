#include "plot.h"

#include <functional>
#include <iostream>
#include <iomanip>
#include <optional>

static constexpr auto width = 48;
static constexpr auto height = 16;

float plot_f[width * height];


void Plot::draw()
{
   std::cout << _func._name << ":" << std::endl;

   for (auto y = 0; y < height; y++)
   {
      std::cout << "|";

      for (auto x = 0; x < width; x++)
      {
         std::cout << ((plot_f[x + y * width] == 1) ? "x" : " ");
      }

      std::cout << std::endl;
   }

   std::cout << "+";
   for (auto x = 0; x < width; x++)
   {
      std::cout << "-";
   }

   std::cout << std::endl << std::endl;
}


void putPixel(int32_t x, int32_t y)
{
   plot_f[x + y * width] = 1;
}


void bresenham(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
   auto dx = x2 - x1;
   auto dy = y2 - y1;

   auto ix = (dx > 0) - (dx < 0);
   auto iy = (dy > 0) - (dy < 0);

   dx = abs(dx) << 1;
   dy = abs(dy) << 1;

   putPixel(x1, y1);

   if (dx >= dy)
   {
      auto error = dy - (dx >> 1);

      while (x1 != x2)
      {
         if ((error >= 0) && (error || (ix > 0)))
         {
            error -= dx;
            y1 += iy;
         }

         error += dy;
         x1 += ix;

         putPixel(x1, y1);
      }
   }
   else
   {
      auto error = dx - (dy >> 1);

      while (y1 != y2)
      {
         if ((error >= 0) && (error || (iy > 0)))
         {
            error -= dy;
            x1 += ix;
         }

         error += dx;
         y1 += iy;

         putPixel(x1, y1);
      }
   }
}


void Plot::update(const Plot::Function& func)
{
   _func = func;

   memset(plot_f, 0, width * height * sizeof(float));

   std::optional<int32_t> px;
   std::optional<int32_t> py;

   for (auto x_scaled = 0; x_scaled < width; x_scaled++)
   {
      const auto x = x_scaled / static_cast<float>(width);
      const auto y = func._func(x);
      const auto y_scaled = height - y * height;

      if (px.has_value())
      {
         bresenham(px.value(), py.value(), x_scaled, static_cast<int32_t>(y_scaled));
      }

      px = static_cast<int32_t>(x_scaled);
      py = static_cast<int32_t>(y_scaled);

      // std::cout
      //    << std::fixed
      //    << std::setprecision(4)
      //    << x << " | " << y
      //    << std::endl;
   }
}

