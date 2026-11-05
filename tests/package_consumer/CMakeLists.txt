# Builds against an installed tinyeasings to check find_package works.
#   cmake --install <build> --prefix <prefix>
#   cmake -S tests/package_consumer -B <out> -DCMAKE_PREFIX_PATH=<prefix>
cmake_minimum_required(VERSION 3.21)
project(tinyeasings_package_consumer LANGUAGES CXX)

find_package(tinyeasings 2 REQUIRED)

add_executable(consumer main.cpp)
target_link_libraries(consumer PRIVATE tinyeasings::tinyeasings)
