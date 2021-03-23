# Glfix
A C library for using Opengl (does not handle windowing)

# C++ Supports
- Context

# C Supports
- Context
- Vertex and Geometry shaders
- Vertex Layout
- 2D Textures || jpg and png
- Vertex Buffer (wraps Vertex Array)
- Index Buffer

# To Do
- Frame Buffer
- Compute Shader
- Tile Maps
- Font Loading
- Text Rendering
- Example Projects

# Sources
- [Cherno's Game Engine Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
- [Learn Opengl](https://learnopengl.com/)

# Docs
Both C and C++ API can be found in the wiki. C_ will mark the C version. Cpp_ will mark the C++ version.

# Building
Git clone the repo and it's submodules `git clone --recurse-submodules https://github.com/SeanMott/Glfix.git` <br>
<br>

### Building a Static C Lib
To build Glfix as a C lib rename the `premake5C.lua` file to `premake5.lua`. This lib can be used with C++ the headers support C++ compiling.

### Building a Static C++ Lib
To build Glfix as a C++ lib rename the `premake5Cpp.lua` file to `premake5.lua`.
