add_executable(easings_test easings_test.cpp)
target_link_libraries(easings_test PRIVATE easings::easings easings_warnings)
add_test(NAME easings_test COMMAND easings_test)

add_test(NAME easings_plot_runs COMMAND easings_plot easeOutBounce easeInOutElastic)
if(NOT TARGET easings_plot)
   set_tests_properties(easings_plot_runs PROPERTIES DISABLED TRUE)
endif()
