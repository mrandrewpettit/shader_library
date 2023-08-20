# SHADER LIBRARY
This repository contains the `osl` source code for shaders I have developed for personal use. Additionally, the repository includes the make and python3 based build system, influenced by [Laika's Shader Library](https://github.com/LaikaStudios/shading-library.git).

## Dependencies
- `make`
- `python3`
- [Renderman 25](https://rmanwiki.pixar.com/display/REN25/RenderMan+25+Documentation)

With alterations to the `make` system, other applications could still make use of the `osl` source code.

## Install Library
1. Download this repository

2. Set these environment variables:
- PIXAR_ROOT
- RMAN_VERSION
- RMANTREE

It's easiest to install these in `~/.bash_aliases`. An example of this looks like:
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
export RMAN_SHADERPATH=${HOME}/dev/shader_library/bin/renderman-${RMAN_VERSION}:${HOME}/dev/shader_library/bin/general"
export RFM_SITE_PATH=${HOME}/dev/shader_library/bin
```
Again, make sure to run `source ~/.bash_aliases` after writing environment variables to file.

> NOTE: if you are setting the env variables in WSL but need to access them in windows, then add an additional command in `~/.bash_aliases` to share the variables across operating systems:
```
export WSLENV=$WSLENV:PIXAR_ROOT/p:RMAN_VERSION:RMANTREE/p:RMAN_SHADERPATH/p:RFM_SITE_PATH/p
```
> To access the variables in windows you must start a wsl terminal and then access windows through `cmd.exe`

## Additional Information

### Library Structure
This shader library supports shaders that are renderer specific and generally supported. For this reason, it is important 
where shaders are placed in the `src` directory. Renderer specific shaders should be placed within a folder that is 
specific to the renderer, i.e. `src/osl/renderman`. Generally supported
 shaders can be placed in `src/osl/general`.

 > NOTE: Therefore, renderers will generally need an environment variable that 
points to both the general and their renderer specific bin folder. This is why `RMAN_SHADERPATH` requires two paths.

### Environment
- `RFM_SITE_PATH` dir maya looks at for oso files at startup

### NodeID
Renderman for Maya requires any shader to have a unique `rfm_nodeid` in its metadata. By default Maya has set aside 
node IDs 0 - 0x7ffff for local use.

These IDs will normally suffice, but bugs would appear if on the off chance someone installs APOSL and is already using 
node IDs 0 - 0x7ffff. To be safe, I have registered a node ID block with maya, and APOSL uses node IDs
0x0013cb80 - 0x0013cbff. 

- See [Node IDs](./NODE_IDS.md) for a breakdown of this shader libraries node IDs
- Visit [Autodesk Website](https://mayaid.autodesk.io/) for more clarification on node IDs

### APOSL Macros 
It is difficult to implement reusable code within OSL syntax. To combat this APOSL leverages macros when defining shader
 parameters. This lets devs update many shaders by updating a single macro. The downfall of this method is code 
 readability becomes a bit ambiguous; though I feel the pros outweigh the cons in this case.

It is recommended that new devs familiarize themselves with macros found in `src/lib/params.h`, `src/lib/float.h`, and 
`src/lib/color.h` to better understand shader parameter code in APOSL.

## License
Apache License 2.0

## TODO
- maya versioning system
- maya node icon
- houdinni support

## Shader Development Steps
- Set parameters
- Check widgets reflect desired outcome
- Set widget interaction (isconnected, etc)
- Define parameter operations
- Test within houdini using ```oslTest```
