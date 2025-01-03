add_executable(vector2d vector_test.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/vector2d.hpp)
add_executable(rectangle rectangle_test.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/rect.hpp)

target_link_libraries(vector2d PRIVATE Catch2::Catch2WithMain)
target_link_libraries(rectangle PRIVATE Catch2::Catch2WithMain)