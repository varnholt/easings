#include <tinyeasings/tinyeasings.hpp>

int main()
{
   return tinyeasings::easeOutBounce(1.0) == 1.0 ? 0 : 1;
}
