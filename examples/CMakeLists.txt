add_executable(easings_plot plot.cpp)
target_link_libraries(easings_plot PRIVATE easings::easings easings_warnings)
