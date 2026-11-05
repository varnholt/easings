// easings.hpp - easing functions for C++23, single header
//
// https://github.com/varnholt/easings
// Formulas follow https://easings.net
//
// SPDX-License-Identifier: CC0-1.0
//
// All functions map x in [0, 1] to y, with f(0) == 0 and f(1) == 1.
// Back and elastic curves overshoot [0, 1] on the way. Inputs outside
// [0, 1] are not clamped; clamp before calling if that can happen.

#pragma once

#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <numbers>
#include <string_view>
#include <utility>

#define EASINGS_VERSION_MAJOR 2
#define EASINGS_VERSION_MINOR 0
#define EASINGS_VERSION_PATCH 0

namespace easings
{

namespace detail
{

template <std::floating_point T>
inline constexpr T back_c1 = static_cast<T>(1.70158);

template <std::floating_point T>
inline constexpr T back_c2 = back_c1<T> * static_cast<T>(1.525);

template <std::floating_point T>
inline constexpr T elastic_c4 = T{2} * std::numbers::pi_v<T> / T{3};

template <std::floating_point T>
inline constexpr T elastic_c5 = T{2} * std::numbers::pi_v<T> / T{4.5};

}  // namespace detail

// sine

template <std::floating_point T>
[[nodiscard]] constexpr T easeInSine(T x) noexcept
{
   return T{1} - std::cos(x * std::numbers::pi_v<T> * T{0.5});
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutSine(T x) noexcept
{
   return std::sin(x * std::numbers::pi_v<T> * T{0.5});
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutSine(T x) noexcept
{
   return (T{1} - std::cos(std::numbers::pi_v<T> * x)) * T{0.5};
}

// quad

template <std::floating_point T>
[[nodiscard]] constexpr T easeInQuad(T x) noexcept
{
   return x * x;
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutQuad(T x) noexcept
{
   const T u = T{1} - x;
   return T{1} - u * u;
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutQuad(T x) noexcept
{
   if (x < T{0.5})
   {
      return T{2} * x * x;
   }

   const T u = T{2} - T{2} * x;
   return T{1} - u * u * T{0.5};
}

// cubic

template <std::floating_point T>
[[nodiscard]] constexpr T easeInCubic(T x) noexcept
{
   return x * x * x;
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutCubic(T x) noexcept
{
   const T u = T{1} - x;
   return T{1} - u * u * u;
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutCubic(T x) noexcept
{
   if (x < T{0.5})
   {
      return T{4} * x * x * x;
   }

   const T u = T{2} - T{2} * x;
   return T{1} - u * u * u * T{0.5};
}

// quart

template <std::floating_point T>
[[nodiscard]] constexpr T easeInQuart(T x) noexcept
{
   return x * x * x * x;
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutQuart(T x) noexcept
{
   const T u = T{1} - x;
   return T{1} - u * u * u * u;
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutQuart(T x) noexcept
{
   if (x < T{0.5})
   {
      return T{8} * x * x * x * x;
   }

   const T u = T{2} - T{2} * x;
   return T{1} - u * u * u * u * T{0.5};
}

// quint

template <std::floating_point T>
[[nodiscard]] constexpr T easeInQuint(T x) noexcept
{
   return x * x * x * x * x;
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutQuint(T x) noexcept
{
   const T u = T{1} - x;
   return T{1} - u * u * u * u * u;
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutQuint(T x) noexcept
{
   if (x < T{0.5})
   {
      return T{16} * x * x * x * x * x;
   }

   const T u = T{2} - T{2} * x;
   return T{1} - u * u * u * u * u * T{0.5};
}

// expo

template <std::floating_point T>
[[nodiscard]] constexpr T easeInExpo(T x) noexcept
{
   return x == T{0} ? T{0} : std::exp2(T{10} * x - T{10});
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutExpo(T x) noexcept
{
   return x == T{1} ? T{1} : T{1} - std::exp2(T{-10} * x);
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutExpo(T x) noexcept
{
   if (x == T{0} || x == T{1})
   {
      return x;
   }

   if (x < T{0.5})
   {
      return std::exp2(T{20} * x - T{10}) * T{0.5};
   }

   return (T{2} - std::exp2(T{10} - T{20} * x)) * T{0.5};
}

// circ

template <std::floating_point T>
[[nodiscard]] constexpr T easeInCirc(T x) noexcept
{
   return T{1} - std::sqrt(T{1} - x * x);
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutCirc(T x) noexcept
{
   const T u = x - T{1};
   return std::sqrt(T{1} - u * u);
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutCirc(T x) noexcept
{
   if (x < T{0.5})
   {
      const T u = T{2} * x;
      return (T{1} - std::sqrt(T{1} - u * u)) * T{0.5};
   }

   const T u = T{2} - T{2} * x;
   return (std::sqrt(T{1} - u * u) + T{1}) * T{0.5};
}

// back

template <std::floating_point T>
[[nodiscard]] constexpr T easeInBack(T x) noexcept
{
   // c3 x^3 - c1 x^2, arranged so that f(1) is exactly 1
   return x * x * (x + detail::back_c1<T> * (x - T{1}));
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutBack(T x) noexcept
{
   const T u = x - T{1};
   // 1 + c3 u^3 + c1 u^2, arranged so that f(0) is exactly 0
   return T{1} + u * u * (u + detail::back_c1<T> * (u + T{1}));
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutBack(T x) noexcept
{
   constexpr T c2 = detail::back_c2<T>;

   if (x < T{0.5})
   {
      const T u = T{2} * x;
      return u * u * (u + c2 * (u - T{1})) * T{0.5};
   }

   const T u = T{2} * x - T{2};
   return (u * u * (u + c2 * (u + T{1})) + T{2}) * T{0.5};
}

// elastic

template <std::floating_point T>
[[nodiscard]] constexpr T easeInElastic(T x) noexcept
{
   if (x == T{0} || x == T{1})
   {
      return x;
   }

   return -std::exp2(T{10} * x - T{10}) * std::sin((T{10} * x - T{10.75}) * detail::elastic_c4<T>);
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutElastic(T x) noexcept
{
   if (x == T{0} || x == T{1})
   {
      return x;
   }

   return std::exp2(T{-10} * x) * std::sin((T{10} * x - T{0.75}) * detail::elastic_c4<T>) + T{1};
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutElastic(T x) noexcept
{
   if (x == T{0} || x == T{1})
   {
      return x;
   }

   const T s = std::sin((T{20} * x - T{11.125}) * detail::elastic_c5<T>);

   if (x < T{0.5})
   {
      return -std::exp2(T{20} * x - T{10}) * s * T{0.5};
   }

   return std::exp2(T{10} - T{20} * x) * s * T{0.5} + T{1};
}

// bounce

template <std::floating_point T>
[[nodiscard]] constexpr T easeOutBounce(T x) noexcept
{
   constexpr T n1 = T{7.5625};
   constexpr T d1 = T{2.75};

   if (x < T{1} / d1)
   {
      return n1 * x * x;
   }

   if (x < T{2} / d1)
   {
      x -= T{1.5} / d1;
      return n1 * x * x + T{0.75};
   }

   if (x < T{2.5} / d1)
   {
      x -= T{2.25} / d1;
      return n1 * x * x + T{0.9375};
   }

   x -= T{2.625} / d1;
   return n1 * x * x + T{0.984375};
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInBounce(T x) noexcept
{
   return T{1} - easeOutBounce(T{1} - x);
}

template <std::floating_point T>
[[nodiscard]] constexpr T easeInOutBounce(T x) noexcept
{
   if (x < T{0.5})
   {
      return (T{1} - easeOutBounce(T{1} - T{2} * x)) * T{0.5};
   }

   return (T{1} + easeOutBounce(T{2} * x - T{1})) * T{0.5};
}

// runtime selection, e.g. for curves picked in a UI or read from a config file.
// Out-of-range values (cast from bad input) give an empty name and a linear curve.

enum class Curve : std::uint8_t
{
   InSine,
   OutSine,
   InOutSine,
   InQuad,
   OutQuad,
   InOutQuad,
   InCubic,
   OutCubic,
   InOutCubic,
   InQuart,
   OutQuart,
   InOutQuart,
   InQuint,
   OutQuint,
   InOutQuint,
   InExpo,
   OutExpo,
   InOutExpo,
   InCirc,
   OutCirc,
   InOutCirc,
   InBack,
   OutBack,
   InOutBack,
   InElastic,
   OutElastic,
   InOutElastic,
   InBounce,
   OutBounce,
   InOutBounce,
};

inline constexpr std::size_t curve_count = std::to_underlying(Curve::InOutBounce) + 1;

inline constexpr std::array<Curve, curve_count> all_curves = []
{
   std::array<Curve, curve_count> curves{};
   for (std::size_t i = 0; i < curve_count; ++i)
   {
      curves[i] = static_cast<Curve>(i);
   }
   return curves;
}();

[[nodiscard]] constexpr std::string_view name(Curve curve) noexcept
{
   constexpr std::array<std::string_view, curve_count> names{
       "easeInSine",    "easeOutSine",    "easeInOutSine",    "easeInQuad",   "easeOutQuad",   "easeInOutQuad",
       "easeInCubic",   "easeOutCubic",   "easeInOutCubic",   "easeInQuart",  "easeOutQuart",  "easeInOutQuart",
       "easeInQuint",   "easeOutQuint",   "easeInOutQuint",   "easeInExpo",   "easeOutExpo",   "easeInOutExpo",
       "easeInCirc",    "easeOutCirc",    "easeInOutCirc",    "easeInBack",   "easeOutBack",   "easeInOutBack",
       "easeInElastic", "easeOutElastic", "easeInOutElastic", "easeInBounce", "easeOutBounce", "easeInOutBounce",
   };

   const auto index = std::to_underlying(curve);
   return index < curve_count ? names[index] : std::string_view{};
}

template <std::floating_point T>
[[nodiscard]] constexpr T ease(Curve curve, T x) noexcept
{
   switch (curve)
   {
      case Curve::InSine: return easeInSine(x);
      case Curve::OutSine: return easeOutSine(x);
      case Curve::InOutSine: return easeInOutSine(x);
      case Curve::InQuad: return easeInQuad(x);
      case Curve::OutQuad: return easeOutQuad(x);
      case Curve::InOutQuad: return easeInOutQuad(x);
      case Curve::InCubic: return easeInCubic(x);
      case Curve::OutCubic: return easeOutCubic(x);
      case Curve::InOutCubic: return easeInOutCubic(x);
      case Curve::InQuart: return easeInQuart(x);
      case Curve::OutQuart: return easeOutQuart(x);
      case Curve::InOutQuart: return easeInOutQuart(x);
      case Curve::InQuint: return easeInQuint(x);
      case Curve::OutQuint: return easeOutQuint(x);
      case Curve::InOutQuint: return easeInOutQuint(x);
      case Curve::InExpo: return easeInExpo(x);
      case Curve::OutExpo: return easeOutExpo(x);
      case Curve::InOutExpo: return easeInOutExpo(x);
      case Curve::InCirc: return easeInCirc(x);
      case Curve::OutCirc: return easeOutCirc(x);
      case Curve::InOutCirc: return easeInOutCirc(x);
      case Curve::InBack: return easeInBack(x);
      case Curve::OutBack: return easeOutBack(x);
      case Curve::InOutBack: return easeInOutBack(x);
      case Curve::InElastic: return easeInElastic(x);
      case Curve::OutElastic: return easeOutElastic(x);
      case Curve::InOutElastic: return easeInOutElastic(x);
      case Curve::InBounce: return easeInBounce(x);
      case Curve::OutBounce: return easeOutBounce(x);
      case Curve::InOutBounce: return easeInOutBounce(x);
   }

   // a value cast from an out-of-range integer: fall back to linear
   return x;
}

}  // namespace easings
