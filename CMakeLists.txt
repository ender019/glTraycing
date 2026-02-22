cmake_minimum_required(VERSION 3.10)
set(project "glmTest")
project(${project} C)

# Путь к glfw3
set(glfw3_DIR "/home/kirill/files/CppProjects/libs/glfw/build_static/install/lib/cmake/glfw3/")
set(cglm_DIR "/home/kirill/files/CppProjects/libs/cglm/build_static/install/lib/cmake/cglm/")
set(glad_DIR "/home/kirill/files/CppProjects/libs/glad/install")
set(project_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Находим библиотеку
find_package(glfw3 CONFIG REQUIRED)
if(NOT glfw3_FOUND)
    message(FATAL_ERROR "glfw3 library not found!")
endif()

find_package(cglm CONFIG REQUIRED)
if(NOT cglm_FOUND)
    message(FATAL_ERROR "cglm library not found!")
endif()

message(STATUS "Founding glfw3: ${glfw3_FOUND}")
message(STATUS "glfw3 version: ${glfw3_VERSION}")
message(STATUS "Founding cglm: ${cglm_FOUND}")
message(STATUS "cglm version: ${cglm_VERSION}")

# Простой тест
file(GLOB GLAD ${glad_DIR}/src/gl.c)
message(STATUS "GLAD ${GLAD}")
add_library(glad STATIC ${GLAD})
target_include_directories(glad PRIVATE ${glad_DIR}/include)

set(SOURCES 
    main.c
    src/base/init.c
    src/base/context/context.c
    src/base/graphics/graphic_context.c
    src/base/graphics/base_graphic.c
    src/base/graphics/polygon/polygon_context.c
    src/base/graphics/polygon/polygon_graphic.c
    src/base/window/glfw_window.c
)

set(HEADERS 
    src/base/init.h
    src/base/context/context.h
    src/base/graphics/graphic_context.h
    src/base/graphics/base_graphic.h
    src/base/graphics/polygon/polygon_context.h
    src/base/graphics/polygon/polygon_graphic.h
    src/base/window/window.h
)

add_executable(${project} ${SOURCES} ${HEADERS})
target_include_directories(${project} PRIVATE ${glad_DIR}/include ${project_DIR})
target_link_libraries(${project} PRIVATE cglm::cglm glfw glad)

