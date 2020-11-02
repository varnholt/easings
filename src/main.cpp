#include <functional>
#include <vector>

#include "easings.h"
#include "plot.h"


int main(int /*argc*/, char* /*argv*/[])
{
   std::vector<std::function<float(float)>> funcs = {
      Easings::easeInSine<float>,
      Easings::easeInCubic<float>,
      Easings::easeInQuint<float>,
      Easings::easeInCirc<float>,
      Easings::easeInElastic<float>,

      Easings::easeOutSine<float>,
      Easings::easeOutCubic<float>,
      Easings::easeOutQuint<float>,
      Easings::easeOutCirc<float>,
      Easings::easeOutElastic<float>,

      Easings::easeInOutSine<float>,
      Easings::easeInOutCubic<float>,
      Easings::easeInOutQuint<float>,
      Easings::easeInOutCirc<float>,
      Easings::easeInOutElastic<float>,

      Easings::easeInQuad<float>,
      Easings::easeInQuart<float>,
      Easings::easeInExpo<float>,
      Easings::easeInBack<float>,
      Easings::easeInBounce<float>,

      Easings::easeOutBack<float>,
      Easings::easeOutQuad<float>,
      Easings::easeOutQuart<float>,
      Easings::easeOutExpo<float>,
      Easings::easeOutBounce<float>,

      Easings::easeInOutQuad<float>,
      Easings::easeInOutQuart<float>,
      Easings::easeInOutExpo<float>,
      Easings::easeInOutBack<float>,
      Easings::easeInOutBounce<float>,
   };

   for (const auto& f : funcs)
   {
      Plot::update(f);
      Plot::draw();
   }

   return 0;
}

