![gameplay](https://github.com/wldfngrs/chrome-dinosaur-2d/blob/main/Assets/gameplay.gif)

# Dino Saur
A 2D colorful reimagining of the chrome dinosaur offline game for Desktop.

## Gameplay
Guide a pixelated Tyrannosaurus rex across a side-scrolling swamp, avoiding  obstacles to achieve a higher score. If that sounds or looks familiar, it is! It's the classic chrome offline game with a colorful and vibrant twist!

## Installing, Compiling
Clone this repository onto your local machine using the following command:

```$ git clone git@github.com:wldfngrs/chrome-dinosaur-2d.git```

After cloning the repository, navigate to the project directory:

```$ cd chrome-dinosaur-2d```

[Download](https://cmake.org/download/) and install ``cmake`` to compile the application in your preferred build system.

#### Visual Studio 17 2022

The following commands generate and build the application project using the Visual Studio build system:

```
$ mkdir build_vs
$ cd build_vs
$ cmake .. -G "Visual Studio 17 2022"
$ cmake --build . --config Debug
```

#### Makefiles

The following commands generate and build the application project using Makefiles:

```
$ mkdir build_make
$ cd build_make
$ cmake .. -G "Unix Makefiles" ..
$ make
```

For what it's worth, the project directory contains all of it's dependencies (SDL2, SDL2_image, SDL2_mixer, SDL2_ttf)so, you can get right to checking the project out, without much configuration trouble!

Do not forget to copy the ``.dll`` files and `./Assets` directory from the project root directory to the folder containing your binary  after compiling and linking!

### Web
Dino Saur is browser compatible on both Desktops and Smartphones: https://wldfngrs.itch.io/dino-saur

I had to heavily refactor the existing application to workaround emscripten's single main event loop handler. Here's a seperate repository for the web application project: https://github.com/wldfngrs/chrome-dinosaur-2d-web.

## Contributing
Pull requests are welcome! For major refactors, please open an issue first to discuss what you would like to improve. Feel free to create a fork of this repository or use the code for any other non-commercial purposes.
