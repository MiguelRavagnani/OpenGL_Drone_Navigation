cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(game VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

find_package(glm REQUIRED)
message(STATUS "glm included at ${glm_INCLUDE_DIR}")

find_package(GLEW REQUIRED)
message(STATUS "GLEW included at ${GLEW_INCLUDE_DIR}")

find_package(glfw3 REQUIRED)
message(STATUS "Found glfw3 in ${glfw3_INCLUDE_DIR}")


set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} ${glm_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS})

set(LOCAL_INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/core"
    "${CMAKE_SOURCE_DIR}/src/shading"
    "${CMAKE_SOURCE_DIR}/src/utility"
    "${CMAKE_SOURCE_DIR}/src/renderer"
    "${CMAKE_SOURCE_DIR}/src/third_party/Glad/src")

set(LIBRARIES ${OPENGL_LIBRARIES} ${glm_LIBRARIES} ${GLEW_LIBRARIES} ${glfw3_LIBRARIES})

include_directories(${INCLUDE_DIRS} ${LOCAL_INCLUDE_DIRS})

set(SOURCE_FILES 
    main.cpp
    src/third_party/Glad/src/glad.c
    src/core/game.cpp
    src/core/game_object.cpp
    src/core/game_screen.cpp
    src/core/resource_manager.cpp
    src/shading/shader.cpp
    src/shading/texture.cpp
    src/renderer/sprite_renderer.cpp)

add_executable(game ${SOURCE_FILES} )

target_link_libraries(game ${LIBRARIES} glfw)

target_include_directories(game PRIVATE ${LOCAL_INCLUDE_DIRS})