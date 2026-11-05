#include <easings/easings.hpp>

int main()
{
   return easings::easeOutBounce(1.0) == 1.0 ? 0 : 1;
}
