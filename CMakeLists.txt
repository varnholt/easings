cmake_minimum_required(VERSION 3.21)

project(
   easings
   VERSION 2.0.0
   DESCRIPTION "Easing functions for C++23, single header"
   HOMEPAGE_URL "https://github.com/varnholt/easings"
   LANGUAGES CXX
)

option(EASINGS_BUILD_EXAMPLES "Build the ASCII plot example" ${PROJECT_IS_TOP_LEVEL})
option(EASINGS_BUILD_TESTS "Build the tests" ${PROJECT_IS_TOP_LEVEL})
option(EASINGS_INSTALL "Generate the install target" ${PROJECT_IS_TOP_LEVEL})

include(GNUInstallDirs)

add_library(easings INTERFACE)
add_library(easings::easings ALIAS easings)

target_include_directories(
   easings INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(easings INTERFACE cxx_std_23)

if(EASINGS_BUILD_EXAMPLES OR EASINGS_BUILD_TESTS)
   add_library(easings_warnings INTERFACE)
   if(MSVC)
      target_compile_options(easings_warnings INTERFACE /W4 /WX /permissive- /utf-8)
   else()
      target_compile_options(easings_warnings INTERFACE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
   endif()
endif()

if(EASINGS_BUILD_EXAMPLES)
   add_subdirectory(examples)
endif()

if(EASINGS_BUILD_TESTS)
   enable_testing()
   add_subdirectory(tests)
endif()

if(EASINGS_INSTALL)
   include(CMakePackageConfigHelpers)

   install(TARGETS easings EXPORT easingsTargets)
   install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
   install(
      EXPORT easingsTargets
      NAMESPACE easings::
      FILE easingsConfig.cmake
      DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/easings
   )

   write_basic_package_version_file(
      ${PROJECT_BINARY_DIR}/easingsConfigVersion.cmake COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT
   )
   install(FILES ${PROJECT_BINARY_DIR}/easingsConfigVersion.cmake DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/easings)
endif()
