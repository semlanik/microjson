find_package(microjson CONFIG REQUIRED)
add_executable(microjson_test main.cpp)
target_link_libraries(microjson_test microjson gtest_main gtest)
add_test(NAME microjson_test COMMAND microjson_test)
