#pragma once

#include <limits>
#include <math.h>
#include <type_traits>
#include <utility>


// https://easings.net/#


namespace Easings
{

static constexpr auto EPSILON = std::numeric_limits<double>::epsilon();

// compare with epsilon
template<class T>
bool fuzzyCompare(T x, T y)
{
   return abs(x - y) < EPSILON;
}


// ease in
template<class T>
constexpr auto easeInSine(T x)
{
   return static_cast<T>(1.0 - cos((x * M_PI) / 2.0));
}

template<class T>
constexpr auto easeInCubic(T x)
{
   return x * x * x;
}

template<class T>
constexpr auto easeInQuint(T x)
{
   return x * x * x * x * x;
}

template<class T>
constexpr auto easeInCirc(T x)
{
   return static_cast<T>(1.0 - sqrt(1.0 - pow(x, 2.0)));
}

template<class T>
constexpr auto easeInElastic(T x)
{
   constexpr auto c4 = (2 * M_PI) / 3;

   return
      static_cast<T>(
         fuzzyCompare(x, T{0.0})
            ? 0.0
            : fuzzyCompare(x, T{1.0})
               ? 1.0
               : (-pow(2.0, 10.0 * x - 10.0) * sin((x * 10.0 - 10.75) * c4))
      );
}


// ease out
template<class T>
constexpr auto easeOutSine(T x)
{
   return static_cast<T>(sin((x * M_PI) * 0.5));
}

template<class T>
constexpr auto easeOutCubic(T x)
{
   return static_cast<T>(1.0 - pow(1.0 - x, 3.0));
}

template<class T>
constexpr auto easeOutQuint(T x)
{
   return static_cast<T>(1.0 - pow(1.0 - x, 5.0));
}

template<class T>
constexpr auto easeOutCirc(T x)
{
   return static_cast<T>(sqrt(1.0 - pow(x - 1.0, 2.0)));
}

template<class T>
constexpr auto easeOutElastic(T x)
{
   constexpr auto c4 = (2.0 * M_PI) / 3.0;

   return static_cast<T>(
      fuzzyCompare(x, T{0.0})
         ? 0.0
         : fuzzyCompare(x, T{1.0})
            ? 1.0
            : pow(2.0, -10.0 * x) * sin((x * 10.0 - 0.75) * c4) + 1.0
   );
}


// ease in/out
template<class T>
constexpr auto easeInOutSine(T x)
{
   return static_cast<T>(-(cos(M_PI * x) - 1.0) * 0.5);
}

template<class T>
constexpr auto easeInOutCubic(T x)
{
   return static_cast<T>(
      (x < 0.5)
         ? (4.0 * x * x * x)
         : (1.0 - pow(-2.0 * x + 2.0, 3.0) * 0.5)
   );
}

template<class T>
constexpr auto easeInOutQuint(T x)
{
   return static_cast<T>(
      (x < 0.5)
         ? (16.0 * x * x * x * x * x)
         : (1.0 - pow(-2.0 * x + 2.0, 5.0) * 0.5)
   );
}

template<class T>
constexpr auto easeInOutCirc(T x)
{
   return static_cast<T>(
      (x < 0.5)
         ? ((1.0 - sqrt(1.0 - pow(2.0 * x, 2.0))) * 0.5)
         : ((sqrt(1.0 - pow(-2.0 * x + 2.0, 2.0)) + 1.0) * 0.5)
   );
}

template<class T>
constexpr auto easeInOutElastic(T x)
{
   constexpr auto c5 = (2 * M_PI) / 4.5;

   return static_cast<T>(
      fuzzyCompare(x, T{0.0})
         ? 0.0
         : fuzzyCompare(x, T{1.0})
            ? 1.0
            : (x < 0.5)
              ? (-(pow(2.0,  20.0 * x - 10.0) * sin((20.0 * x - 11.125) * c5)) * 0.5)
              : ( (pow(2.0, -20.0 * x + 10.0) * sin((20.0 * x - 11.125) * c5)) * 0.5 + 1.0)
      );
}


// ease in
template<class T>
constexpr auto easeInQuad(T x)
{
   return x * x;
}

template<class T>
constexpr auto easeInQuart(T x)
{
   return x * x * x * x;
}

template<class T>
constexpr auto easeInExpo(T x)
{
   return static_cast<T>(
      fuzzyCompare(x, T{0.0})
         ? 0.0
         : pow(2.0, 10.0 * x - 10.0)
      );
}

template<class T>
constexpr auto easeInBack(T x)
{
   constexpr auto c1 = 1.70158;
   constexpr auto c3 = c1 + 1.0;
   return static_cast<T>(c3 * x * x * x - c1 * x * x);
}

template<class T>
constexpr auto easeInBounce(T x)
{
   return static_cast<T>(1.0 - easeOutBounce(1.0 - x));
}


// ease out

template<class T>
constexpr auto easeOutBack(T x)
{
   constexpr auto c1 = 1.70158;
   constexpr auto c3 = c1 + 1.0;

   return static_cast<T>(1.0 + c3 * pow(x - 1.0, 3.0) + c1 * pow(x - 1.0, 2.0));
}

template<class T>
constexpr auto easeOutQuad(T x)
{
   return static_cast<T>(1.0 - (1.0 - x) * (1.0 - x));
}

template<class T>
constexpr auto easeOutQuart(T x)
{
   return static_cast<T>(1.0 - pow(1.0 - x, 4.0));
}

template<class T>
constexpr auto easeOutExpo(T x)
{
   return static_cast<T>(
      fuzzyCompare(x, T{1.0})
         ? 1.0
         : (1.0 - pow(2.0, -10.0 * x))
      );
}

template<class T>
constexpr auto easeOutBounce(T x)
{
   constexpr T n1 = 7.5625;
   constexpr T d1 = 2.75;

   if (x < 1.0 / d1)
   {
      return n1 * x * x;
   }
   else if (x < 2.0 / d1)
   {
      return n1 * (x -= T{1.5} / d1) * x + T{0.75};
   }
   else if (x < 2.5 / d1)
   {
      return n1 * (x -= T{2.25} / d1) * x + T{0.9375};
   }
   else
   {
      return n1 * (x -= T{2.625} / d1) * x + T{0.984375};
   }
}


// ease in/out

template<class T>
constexpr auto easeInOutQuad(T x)
{
   return static_cast<T>(
      (x < 0.5)
         ? (2.0 * x * x)
         : (1.0 - pow(-2.0 * x + 2.0, 2.0) / 2.0)
   );
}

template<class T>
constexpr auto easeInOutQuart(T x)
{
   return static_cast<T>(
      (x < 0.5)
         ? (8.0 * x * x * x * x)
         : (1.0 - pow(-2.0 * x + 2.0, 4.0) / 2.0)
   );
}

template<class T>
constexpr auto easeInOutExpo(T x)
{
   return static_cast<T>(
      fuzzyCompare(x, static_cast<T>(0.0))
         ? 0.0
         : fuzzyCompare(x, static_cast<T>(1.0))
            ? 1.0
            : (x < 0.5)
               ? (pow(2.0, 20.0 * x - 10.0) / 2.0)
               : ((2.0 - pow(2.0, -20 * x + 10.0)) / 2.0)
      );
}

template<class T>
constexpr auto easeInOutBack(T x)
{
   constexpr auto c1 = 1.70158;
   constexpr auto c2 = c1 * 1.525;

   return static_cast<T>(
      (x < 0.5)
         ? (pow(2.0 * x, 2.0) * ((c2 + 1.0) * 2.0 * x - c2)) * 0.5
         : (pow(2.0 * x - 2.0, 2.0) * ((c2 + 1.0) * (x * 2.0 - 2.0) + c2) + 2.0) * 0.5
   );
}

template<class T>
constexpr auto easeInOutBounce(T x)
{
   return static_cast<T>(
      (x < 0.5)
         ? (1.0 - easeOutBounce(1.0 - 2.0 * x)) / 2.0
         : (1.0 + easeOutBounce(2.0 * x - 1.0)) / 2.0
   );
}

}

