cmake_minimum_required(VERSION 3.21)

project(
   tinyeasings
   VERSION 2.0.0
   DESCRIPTION "Easing functions for C++23, single header"
   HOMEPAGE_URL "https://github.com/varnholt/tinyeasings"
   LANGUAGES CXX
)

option(TINYEASINGS_BUILD_EXAMPLES "Build the ASCII plot example" ${PROJECT_IS_TOP_LEVEL})
option(TINYEASINGS_BUILD_TESTS "Build the tests" ${PROJECT_IS_TOP_LEVEL})
option(TINYEASINGS_INSTALL "Generate the install target" ${PROJECT_IS_TOP_LEVEL})

include(GNUInstallDirs)

add_library(tinyeasings INTERFACE)
add_library(tinyeasings::tinyeasings ALIAS tinyeasings)

target_include_directories(
   tinyeasings INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(tinyeasings INTERFACE cxx_std_23)

if(TINYEASINGS_BUILD_EXAMPLES OR TINYEASINGS_BUILD_TESTS)
   add_library(tinyeasings_warnings INTERFACE)
   if(MSVC)
      target_compile_options(tinyeasings_warnings INTERFACE /W4 /WX /permissive- /utf-8)
   else()
      target_compile_options(tinyeasings_warnings INTERFACE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
   endif()
endif()

if(TINYEASINGS_BUILD_EXAMPLES)
   add_subdirectory(examples)
endif()

if(TINYEASINGS_BUILD_TESTS)
   enable_testing()
   add_subdirectory(tests)
endif()

if(TINYEASINGS_INSTALL)
   include(CMakePackageConfigHelpers)

   install(TARGETS tinyeasings EXPORT tinyeasingsTargets)
   install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
   install(
      EXPORT tinyeasingsTargets
      NAMESPACE tinyeasings::
      FILE tinyeasingsConfig.cmake
      DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/tinyeasings
   )

   write_basic_package_version_file(
      ${PROJECT_BINARY_DIR}/tinyeasingsConfigVersion.cmake COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT
   )
   install(FILES ${PROJECT_BINARY_DIR}/tinyeasingsConfigVersion.cmake DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/tinyeasings)
endif()
