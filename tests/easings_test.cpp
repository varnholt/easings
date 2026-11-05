#include <easings/easings.hpp>

#include <cmath>
#include <print>
#include <set>
#include <source_location>
#include <string_view>

using namespace easings;

// compile-time checks for the curves that need no <cmath>
static_assert(easeInQuad(0.5) == 0.25);
static_assert(easeOutCubic(0.5f) == 0.875f);
static_assert(easeInOutQuint(1.0) == 1.0);
static_assert(easeOutBounce(0.5) == 0.765625);
static_assert(easeInOutBounce(0.0) == 0.0);
static_assert(easeInBack(1.0) == 1.0);
static_assert(ease(Curve::InQuart, 0.5) == 0.0625);
static_assert(name(Curve::InOutElastic) == "easeInOutElastic");
static_assert(all_curves.size() == 30);
static_assert(noexcept(easeInSine(0.5f)));
static_assert(easeInOutCubic(0.5) == 0.5);  // README example

namespace
{

int failures = 0;

void check(bool ok, std::string_view what, const std::source_location& where = std::source_location::current())
{
   if (!ok)
   {
      ++failures;
      std::println(stderr, "{}:{}: FAILED: {}", where.file_name(), where.line(), what);
   }
}

bool near(double a, double b, double eps = 1e-12)
{
   return std::abs(a - b) <= eps;
}

struct Family
{
   Curve in;
   Curve out;
   Curve in_out;
};

constexpr std::array families{
    Family{Curve::InSine, Curve::OutSine, Curve::InOutSine},
    Family{Curve::InQuad, Curve::OutQuad, Curve::InOutQuad},
    Family{Curve::InCubic, Curve::OutCubic, Curve::InOutCubic},
    Family{Curve::InQuart, Curve::OutQuart, Curve::InOutQuart},
    Family{Curve::InQuint, Curve::OutQuint, Curve::InOutQuint},
    Family{Curve::InExpo, Curve::OutExpo, Curve::InOutExpo},
    Family{Curve::InCirc, Curve::OutCirc, Curve::InOutCirc},
    Family{Curve::InBack, Curve::OutBack, Curve::InOutBack},
    Family{Curve::InElastic, Curve::OutElastic, Curve::InOutElastic},
    Family{Curve::InBounce, Curve::OutBounce, Curve::InOutBounce},
};

void test_endpoints()
{
   for (const auto curve : all_curves)
   {
      check(ease(curve, 0.0) == 0.0 || near(ease(curve, 0.0), 0.0), name(curve));
      check(near(ease(curve, 1.0), 1.0), name(curve));
      check(near(ease(curve, 0.0f), 0.0f, 1e-6), name(curve));
      check(near(ease(curve, 1.0f), 1.0f, 1e-6), name(curve));
   }
}

void test_symmetry()
{
   // out(x) == 1 - in(1 - x), and in_out is in/out squeezed into each half.
   // easings.net gives back and elastic in_out their own overshoot and period,
   // so those two only get the first check.
   for (const auto& [in, out, in_out] : families)
   {
      for (int i = 0; i <= 100; ++i)
      {
         const double x = i / 100.0;
         check(near(ease(out, x), 1.0 - ease(in, 1.0 - x), 1e-9), name(out));

         if (in == Curve::InBack || in == Curve::InElastic)
         {
            continue;
         }

         const double expected = x < 0.5 ? ease(in, 2.0 * x) * 0.5 : 0.5 + ease(out, 2.0 * x - 1.0) * 0.5;
         check(near(ease(in_out, x), expected, 1e-9), name(in_out));
      }
   }
}

void test_float_matches_double()
{
   for (const auto curve : all_curves)
   {
      for (int i = 0; i <= 100; ++i)
      {
         const double x = i / 100.0;
         check(near(ease(curve, static_cast<float>(x)), ease(curve, x), 1e-5), name(curve));
      }
   }
}

void test_reference_values()
{
   // spot values from the easings.net formulas
   check(near(easeInSine(0.5), 1.0 - std::cos(std::numbers::pi / 4.0)), "easeInSine");
   check(near(easeInExpo(0.5), 1.0 / 32.0), "easeInExpo");
   check(near(easeOutCirc(0.5), std::sqrt(0.75)), "easeOutCirc");
   check(near(easeInBack(0.5), 2.70158 * 0.125 - 1.70158 * 0.25), "easeInBack");
   check(near(easeOutElastic(0.5), std::exp2(-5.0) * std::sin(4.25 * 2.0 * std::numbers::pi / 3.0) + 1.0),
         "easeOutElastic");
   check(easeOutBack(0.5) > 1.0, "easeOutBack overshoots");
   check(easeInElastic(0.9) < 0.0, "easeInElastic undershoots");
}

void test_runtime_selection()
{
   std::set<std::string_view> names;
   for (const auto curve : all_curves)
   {
      check(!name(curve).empty(), "name");
      names.insert(name(curve));
   }
   check(names.size() == curve_count, "names are unique");

   const auto bogus = static_cast<Curve>(200);
   check(name(bogus).empty(), "bogus name");
   check(ease(bogus, 0.3) == 0.3, "bogus curve is linear");
}

}  // namespace

int main()
{
   test_endpoints();
   test_symmetry();
   test_float_matches_double();
   test_reference_values();
   test_runtime_selection();

   if (failures > 0)
   {
      std::println(stderr, "{} check(s) failed", failures);
      return 1;
   }

   std::println("all checks passed");
   return 0;
}
