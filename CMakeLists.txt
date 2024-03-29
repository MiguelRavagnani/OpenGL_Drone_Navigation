# Projects Settings
cmake_minimum_required(VERSION 3.1)

project (opengl-drone-navigation)

# The main executable
add_executable(
    opengl-drone-navigation
    main.cpp
    vendor/glfw/deps/glad.c
    src/core/application.cpp
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
    "textures/bg_2.png"
    "textures/button_automatic.png"
    "textures/button_manual.png"
    "textures/button_menu_close.png"
    "textures/button_menu.png"
    "textures/drone_frame.png"
    "textures/drone_still.png"
    "textures/waypoint_1.png"
    )
configure_file(${file} ${file} ${file} ${file} ${file} ${file} ${file} ${file} COPYONLY)
endforeach(file)

foreach(file "src/shaders/sprite.frag" "src/shaders/sprite.vs")
configure_file(${file} ${file})
endforeach(file)

set_property(TARGET opengl-drone-navigation APPEND_STRING PROPERTY LINK_FLAGS
"--preload-file ${CMAKE_CURRENT_BINARY_DIR}/src/shaders/@/src/shaders/ --preload-file ${CMAKE_CURRENT_BINARY_DIR}/textures/@/textures/ --use-preload-plugins -sNO_DISABLE_EXCEPTION_CATCHING")

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
