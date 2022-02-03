# OpenGL Drone Navigation

This game is an implementation of a drone simulation. At present time, only basic systems as movement and rotation have been implemented, but soon, a physiscs engine and multi-variable control system will be added.

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
