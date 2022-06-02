# OpenGL Drone Navigation

This game is an implementation of a drone simulation. At present time, only basic systems as movement and rotation have been implemented, but soon, a physiscs engine and multi-variable control system will be added.

## Clone this repository

Either clone it recursively, or update the submodules

```console
git clone --recursive git@github.com:MiguelRavagnani/OpenGL_Drone_Navigation.git
```

or

```console
git submodule init
git submodule update
```

## Dependencies

OpenGL, GLM and GLEW are already integrated as submodules. Donwload remaining deś:

```console
sudo apt-get install cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

## Building the game

Create build folder

```console
mkdir build
cd build
```
Build the project
```console
cmake ..
make
```
Run it
```console
./game
```

## About the project

This game is an implementation of a drone simulation. At present time, only basic systems as movement and rotation have been implemented, but soon, a physiscs engine and multi-variable control system will be added.

The code was developed using the OpenGL API, and the core base of the project (renderer, shaders and resource managers) was built after the documentation in [learn onpengl](https://learnopengl.com/), by JoeyDeVries. The sprites, sprite animation renderer, game controls, phyisics engine and control system were developed by me.
