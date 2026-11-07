#include <tinyeasings/tinyeasings.hpp>
#include <iomanip>
#include <iostream>
int main() {
    std::cout << std::setprecision(17);
    for(auto curve:tinyeasings::all_curves) for(int i=0;i<=100;++i) {
        const double x=i/100.0;
        std::cout << static_cast<int>(curve) << ' ' << x << ' ' << tinyeasings::ease(curve,x) << ' ' << tinyeasings::ease(curve,static_cast<float>(x)) << '\n';
    }
}
