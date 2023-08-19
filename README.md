# SHADER LIBRARY
This repository contains the `osl` source code for shaders I have developed for personal use. Additionally, the repository includes the make and python3 based build system, influenced by [Laika's Shader Library](https://github.com/LaikaStudios/shading-library.git).

## Dependencies
- `make`
- `python3`
- [Renderman 25](https://rmanwiki.pixar.com/display/REN25/RenderMan+25+Documentation)

With alterations to the `make` system, other applications could still make use of the `osl` source code.

## Quick Start
1. Download this repository

2. Set these environment variables:
- PIXAR_ROOT
- RMAN_VERSION
- RMANTREE

It's easiest to install these in `~/.bash_aliases`. An example of this may be:
```
export PIXAR_ROOT="/mnt/c/Program Files/Pixar"
export RMAN_VERSION=25.2
export RMANTREE=$PIXAR_ROOT/RenderManProServer-$RMAN_VERSION
```
Make sure to run `source ~/.bash_aliases` after writing environment variables to file.

3. `cd` into the downloaded repository

4. You can use tha `make` command to build the shaders. Alternatively, you can `cd` into `src/osl` and run `make` to only build osl shaders.

Additionally, you can run `make help` or `make clean` on any Makefile to use their respective functionalities.

5. After building the shaders, there is one more environment variable you need to set so the built shaders can be found by RenderMan:
- RMAN_SHADERPATH

If you downloaded this repository to `${HOME}/shader_library` then you will want to add something like this to `~/.bash_aliases`:
```
export RMAN_SHADERPATH="${HOME}/shader_library/bin/Renderman-${RMAN_VERSION}"
export RFM_SITE_PATH=$RMANTREE
```
Again, make sure to run `source ~/.bash_aliases` after writing environment variables to file.

> NOTE: if you are setting the env variables in WSL but need to access them in windows, then add an additional command in `~/.bash_aliases` to share the variables across operating systems:
```
export WSLENV=$WSLENV:PIXAR_ROOT/p:RMAN_VERSION:RMANTREE/p:RMAN_SHADERPATH/p:RFM_SITE_PATH/p
```
> To access the variables in windows you must start a wsl terminal and then access windows through `cmd.exe`
