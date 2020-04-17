find_package(microjson CONFIG REQUIRED)
find_package(GTest REQUIRED)

add_executable(microjson_test main.cpp)
target_link_libraries(microjson_test microjson gtest_main gtest)
