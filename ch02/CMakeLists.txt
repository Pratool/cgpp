cmake_minimum_required(VERSION 3.10)

find_package(FreeGLUT REQUIRED)

add_executable(test
    ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

target_link_libraries(test
    FreeGLUT::freeglut)

install(TARGETS test
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
