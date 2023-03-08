cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

project(Renderer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(main
  ${PROJECT_SOURCE_DIR}/src/main.c
  ${PROJECT_SOURCE_DIR}/src/scaffold.h
  ${PROJECT_SOURCE_DIR}/src/scaffold.c
  ${PROJECT_SOURCE_DIR}/glad/src/glad.c
  ${PROJECT_SOURCE_DIR}/src/object.h
  ${PROJECT_SOURCE_DIR}/src/object.c
  ${PROJECT_SOURCE_DIR}/src/uniforms.h)

set(cglm "" CACHE PATH "CGLM source dir")

target_compile_options(main PRIVATE -Wno-error)


add_subdirectory("${PROJECT_SOURCE_DIR}/glfw")
add_subdirectory("${PROJECT_SOURCE_DIR}/cglm")
add_subdirectory("${PROJECT_SOURCE_DIR}/assimp")

string(REPLACE " -Werror=array-bounds" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

target_include_directories(
  main
  PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/glad/include"
  "${OPENGL_INCLUDE_DIRS}"
  "${assimp_INCLUDE_DIRS}")


target_link_libraries(main PUBLIC glfw)
target_link_libraries(main PRIVATE cglm)
target_link_libraries(main PUBLIC ${assimp_LIBRARIES})
target_link_libraries(main PUBLIC OpenGL::GL)

