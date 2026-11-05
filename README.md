# easings

[![CI](https://github.com/varnholt/easings/actions/workflows/ci.yml/badge.svg)](https://github.com/varnholt/easings/actions/workflows/ci.yml)

Easing functions for C++23 in a single header, following the formulas from
[easings.net](https://easings.net).

- one header, no dependencies: copy `include/easings/easings.hpp` into your project
- or use it as a CMake library: `add_subdirectory`, `FetchContent` or `find_package`
- `constexpr` and `noexcept`, works with `float`, `double` and `long double`
- every curve returns exactly 0 at x = 0 and exactly 1 at x = 1
- select a curve at runtime with the `easings::Curve` enum

## Usage

```cpp
#include <easings/easings.hpp>

// x is expected in [0, 1]
const float y = easings::easeOutBounce(0.5f);

// constant-evaluated where the math allows it
static_assert(easings::easeInOutCubic(0.5) == 0.5);

// runtime selection, e.g. from a UI or a config file
const auto curve = easings::Curve::InOutElastic;
const double z = easings::ease(curve, 0.25);
std::println("{}: {}", easings::name(curve), z);

for (const auto c : easings::all_curves) { /* ... */ }
```

Inputs are not clamped. The back and elastic curves deliberately go outside
[0, 1] partway through the animation.

## API

Everything lives in namespace `easings`.

| | |
|---|---|
| `T easeIn<Family>(T x)`<br>`T easeOut<Family>(T x)`<br>`T easeInOut<Family>(T x)` | one function per curve; `Family` is `Sine`, `Quad`, `Cubic`, `Quart`, `Quint`, `Expo`, `Circ`, `Back`, `Elastic` or `Bounce`; `T` is any `std::floating_point` |
| `enum class Curve` | `InSine`, `OutSine`, `InOutSine`, ... `InOutBounce` (30 values) |
| `T ease(Curve curve, T x)` | evaluates the selected curve; an out-of-range `Curve` value falls back to linear |
| `std::string_view name(Curve curve)` | e.g. `"easeOutBounce"`; empty for an out-of-range value |
| `all_curves`, `curve_count` | all `Curve` values in declaration order, e.g. to fill a combo box |

## Upgrading from 1.x

| 1.x | 2.x |
|---|---|
| `#include "easings.h"` | `#include <easings/easings.hpp>` |
| `Easings::easeInSine<float>(x)` | `easings::easeInSine(x)` (the template argument is deduced) |
| any arithmetic `T` | `float`, `double` or `long double` only |
| qmake project | CMake target `easings::easings` |

## Integration

The header needs C++23. CI builds it with GCC 14, Clang 18 and MSVC; the header alone
also works with GCC 13. The tests and the example use `<print>`, so they need GCC 14,
Clang 18 with libstdc++ 14, or Visual Studio 2022 17.7 or newer.

### Single header

Copy `include/easings/easings.hpp`, then `#include "easings.hpp"`.

### CMake FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(easings GIT_REPOSITORY https://github.com/varnholt/easings.git GIT_TAG main)
FetchContent_MakeAvailable(easings)

target_link_libraries(my_app PRIVATE easings::easings)
```

### CMake add_subdirectory

```cmake
add_subdirectory(external/easings)
target_link_libraries(my_app PRIVATE easings::easings)
```

### Installed package

```sh
cmake -S . -B build
cmake --install build --prefix /some/prefix
```

```cmake
find_package(easings 2 REQUIRED)
target_link_libraries(my_app PRIVATE easings::easings)
```

The tests and the example build only when easings is the top-level project.
Use `EASINGS_BUILD_TESTS`, `EASINGS_BUILD_EXAMPLES` and `EASINGS_INSTALL` to override that.

## Building the tests and the plot example

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build
./build/examples/easings_plot easeOutBounce
```

```
easeOutBounce
1 |. . . . . . . . . . .** . . . . . . . . . *** . . . ********
  |                    ** *                ***  ********
  |                    *   **             **
  |                   *      **        ****
  |                  **        *********
  |                 **
  |                 *
  |                *
  |               **
  |              **
  |             **
  |            **
  |           **
  |         ***
  |        **
  |      ***
  |   ****
0 |****. . . . . . . . . . . . . . . . . . . . . . . . . . . .
  +------------------------------------------------------------
```

## Curves

| | in | out | in/out |
|---|---|---|---|
| **Sine** | ![easeInSine](doc/0_easeInSine.png) | ![easeOutSine](doc/5_easeOutSine.png) | ![easeInOutSine](doc/10_easeInOutSine.png) |
| **Quad** | ![easeInQuad](doc/15_easeInQuad.png) | ![easeOutQuad](doc/21_easeOutQuad.png) | ![easeInOutQuad](doc/25_easeInOutQuad.png) |
| **Cubic** | ![easeInCubic](doc/1_easeInCubic.png) | ![easeOutCubic](doc/6_easeOutCubic.png) | ![easeInOutCubic](doc/11_easeInOutCubic.png) |
| **Quart** | ![easeInQuart](doc/16_easeInQuart.png) | ![easeOutQuart](doc/22_easeOutQuart.png) | ![easeInOutQuart](doc/26_easeInOutQuart.png) |
| **Quint** | ![easeInQuint](doc/2_easeInQuint.png) | ![easeOutQuint](doc/7_easeOutQuint.png) | ![easeInOutQuint](doc/12_easeInOutQuint.png) |
| **Expo** | ![easeInExpo](doc/17_easeInExpo.png) | ![easeOutExpo](doc/23_easeOutExpo.png) | ![easeInOutExpo](doc/27_easeInOutExpo.png) |
| **Circ** | ![easeInCirc](doc/3_easeInCirc.png) | ![easeOutCirc](doc/8_easeOutCirc.png) | ![easeInOutCirc](doc/13_easeInOutCirc.png) |
| **Back** | ![easeInBack](doc/18_easeInBack.png) | ![easeOutBack](doc/20_easeOutBack.png) | ![easeInOutBack](doc/28_easeInOutBack.png) |
| **Elastic** | ![easeInElastic](doc/4_easeInElastic.png) | ![easeOutElastic](doc/9_easeOutElastic.png) | ![easeInOutElastic](doc/14_easeInOutElastic.png) |
| **Bounce** | ![easeInBounce](doc/19_easeInBounce.png) | ![easeOutBounce](doc/24_easeOutBounce.png) | ![easeInOutBounce](doc/29_easeInOutBounce.png) |

## License

[CC0 1.0](LICENSE)
