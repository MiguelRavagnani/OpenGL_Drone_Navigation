# Projects Settings
cmake_minimum_required(VERSION 3.1)

project (opengl-drone-navigation)

# The main executable
add_executable(
    opengl-drone-navigation
    main.cpp
    vendor/glfw/deps/glad.c
    src/core/game.cpp
    src/core/game_object.cpp
    src/core/game_screen.cpp
    src/core/resource_manager.cpp
    src/shading/shader.cpp
    src/shading/texture.cpp
    src/renderer/sprite_renderer.cpp
    src/renderer/sprite_sheet_renderer.cpp
    src/physics/screen_colision.cpp
    src/physics/math_utils.cpp
    src/physics/model.cpp
    src/physics/physics_handler.cpp
)

target_link_libraries(opengl-drone-navigation PUBLIC "-s USE_GLFW=3")
target_link_libraries(opengl-drone-navigation PUBLIC "-s USE_WEBGL2=1")
target_link_libraries(opengl-drone-navigation PUBLIC "-s WASM=1")

foreach(file "index.html" "run_webassembly.py")
configure_file(src/web/${file} ${file})
endforeach(file)

foreach(file 
    "bg_1.png"
    "bg_2.png"
    "button_automatic.png"
    "button_manual.png"
    "button_menu_close.png"
    "button_menu.png"
    "drone_frame.png"
    "drone_still.png"
    "waypoint_1.png"
    )
configure_file(textures/${file} ${file} ${file} ${file} ${file} ${file} ${file} ${file} ${file})
endforeach(file)

foreach(file "src/shaders/sprite.frag" "src/shaders/sprite.vs")
configure_file(${file} ${file})
endforeach(file)

set_property(TARGET opengl-drone-navigation APPEND_STRING PROPERTY LINK_FLAGS
"--preload-file ${CMAKE_CURRENT_BINARY_DIR}/src/shaders/@/src/shaders/")

# set_property(TARGET opengl-drone-navigation PROPERTY CXX_STANDARD 11)
# target_compile_options(opengl-drone-navigation PRIVATE -Wall)

# add_definitions(-DGLEW_STATIC)
# add_subdirectory(vendor/glfw EXCLUDE_FROM_ALL)
# add_subdirectory(vendor/glew EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glm EXCLUDE_FROM_ALL)

target_link_libraries(
    opengl-drone-navigation
    PRIVATE glm
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/config/config.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/src/config/config.hpp
)

SET(CMAKE_EXECUTABLE_SUFFIX ".js")

target_include_directories(opengl-drone-navigation
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src

    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/core

    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/shading
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/shading

    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/utility
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/utility

    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/renderer

    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/physics
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/physics

    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/third_party/Glad/src
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/third_party/Glad/src

    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/deps
)
