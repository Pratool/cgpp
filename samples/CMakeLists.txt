cmake_minimum_required(VERSION 3.10)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(sample
    ${CMAKE_CURRENT_SOURCE_DIR}/sample.cpp)

target_link_libraries(sample
    OpenGL::GL
    GLUT::GLUT
    Eigen3::Eigen
    GLEW)

install(TARGETS sample
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.fs ${CMAKE_INSTALL_PREFIX}/bin/shader.fs
    COPYONLY)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.vs ${CMAKE_INSTALL_PREFIX}/bin/shader.vs
    COPYONLY)
