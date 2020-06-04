# pgl (pre-alpha stage)

pgl is a C++ program that uses SDL + OpenGL to abstract drawing shapes.

It is not ready to use (yet) and in active development.

## Building

This project requires `SDL2` and `glm` packages to be installed in order to build. Install them with package manager from your distribution.

Now clone and build:
```
$ git clone https://github.com/vSLG/pgl.git
$ cd pgl
$ make build -j$(nproc)
```

The final binary will be located at `bin/main`.

## Running

This project requires `SDL2` package to be installed in order to run final binary.

After building, you can run the final binary in 2 ways:
```
$ ./bin/main
```
or
```
$ make run
```

## License
[LGPL-3.0](https://www.gnu.org/licenses/lgpl-3.0.en.html)