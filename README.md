# Shear2D
2D game engine for C/C++

## Prerequisites
* Pike https://pike.lysator.liu.se/

## Installation
```
git clone https://github.com/zeroxthreef/Shear2D.git --recursive
cd Shear2D
```

if using linux -
``sudo ./install.pike``

if using windows
``pike install.pike`` TODO (make this work on window at all)

## Use
The shear2d.pike script makes a new workspace for each project where you tell it to. This is the reason why the build process doesn't use cmake.

After initializing the workspace folder, to compile your game, just run ``shear2d.pike build`` (if you installed it where PATH can see it). This will output a binary that contains everything including assets (if passed the command to include them) into /bin of your root workspace.

## Features
* Modular (lots of core features are modules you can disable or modify)
* Chipmunk2D physics
* (future)openmpt module support.
* TMX mapping
* layer system with paralaxing
* command system that stores variables
* Wren scripting

## TODO
* add more commands to do things like use other compilers for other targets than the host system (emscripten aswell)
* add commands to not make single binary output if data gets large enough
* add commands to not statically compile SDL2
* add module register functions for Wren/the engine to call


Uses SDL2, stb_image.h, Vec, Map, Wren, cmixer, tmx, librg, and chipmunk in the lib/ directory. Their respective licenses apply
(Note, I will append applicable licenses here to correctly follow license guidelines, but this is a WIP project)
(I will also redo this section and provide a link to each library used)

## License
MIT