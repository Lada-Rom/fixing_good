add_executable(vector2d vector_test.cpp)
add_executable(rectangle rectangle_test.cpp)

target_link_libraries(vector2d  PRIVATE Catch2::Catch2WithMain)
target_link_libraries(rectangle PRIVATE Catch2::Catch2WithMain)