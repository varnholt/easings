#include <functional>
#include <vector>

#include "easings.h"
#include "plot.h"


int main(int /*argc*/, char* /*argv*/[])
{
   std::vector<Plot::Function> funcs = {
      {Easings::easeInSine<float>,       "easeInSine"},
      {Easings::easeInCubic<float>,      "easeInCubic"},
      {Easings::easeInQuint<float>,      "easeInQuint"},
      {Easings::easeInCirc<float>,       "easeInCirc"},
      {Easings::easeInElastic<float>,    "easeInElastic"},

      {Easings::easeOutSine<float>,      "easeOutSine"},
      {Easings::easeOutCubic<float>,     "easeOutCubic"},
      {Easings::easeOutQuint<float>,     "easeOutQuint"},
      {Easings::easeOutCirc<float>,      "easeOutCirc"},
      {Easings::easeOutElastic<float>,   "easeOutElastic"},

      {Easings::easeInOutSine<float>,    "easeInOutSine"},
      {Easings::easeInOutCubic<float>,   "easeInOutCubic"},
      {Easings::easeInOutQuint<float>,   "easeInOutQuint"},
      {Easings::easeInOutCirc<float>,    "easeInOutCirc"},
      {Easings::easeInOutElastic<float>, "easeInOutElastic"},

      {Easings::easeInQuad<float>,       "easeInQuad"},
      {Easings::easeInQuart<float>,      "easeInQuart"},
      {Easings::easeInExpo<float>,       "easeInExpo"},
      {Easings::easeInBack<float>,       "easeInBack"},
      {Easings::easeInBounce<float>,     "easeInBounce"},

      {Easings::easeOutBack<float>,      "easeOutBack"},
      {Easings::easeOutQuad<float>,      "easeOutQuad"},
      {Easings::easeOutQuart<float>,     "easeOutQuart"},
      {Easings::easeOutExpo<float>,      "easeOutExpo"},
      {Easings::easeOutBounce<float>,    "easeOutBounce"},

      {Easings::easeInOutQuad<float>,    "easeInOutQuad"},
      {Easings::easeInOutQuart<float>,   "easeInOutQuart"},
      {Easings::easeInOutExpo<float>,    "easeInOutExpo"},
      {Easings::easeInOutBack<float>,    "easeInOutBack"},
      {Easings::easeInOutBounce<float>,  "easeInOutBounce"},
   };

   for (const auto& f : funcs)
   {
      Plot p;
      p.update(f);
      p.draw();
   }

   return 0;
}

