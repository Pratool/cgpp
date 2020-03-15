cmake_minimum_required(VERSION 3.10)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(test
    ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

target_link_libraries(test
    OpenGL::GL
    GLUT::GLUT)

install(TARGETS test
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
