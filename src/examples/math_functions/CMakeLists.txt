# compile this common file first
add_library(function_minimizer STATIC function_minimizer_ga.cpp)

# complile rest of the demos
add_executable(cross_in_tray_demo cross_in_tray_func_demo.cpp)
add_executable(mccormick_demo mccormick_func_demo.cpp)
add_executable(schaffer_n4_demo schaffer_n4_func_demo.cpp)

target_link_libraries(cross_in_tray_demo function_minimizer)
target_link_libraries(mccormick_demo function_minimizer)
target_link_libraries(schaffer_n4_demo function_minimizer)