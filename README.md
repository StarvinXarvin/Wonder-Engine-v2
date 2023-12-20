# WonderEngine v2
Wonder Engine v2 is a 3D Game Engine with basic Mesh and texture-loading functionality forked from the original Wonder Engine by users PauFusco and StarvinXarvin.
## Functionalities
Wonder Engine comes with 3 default meshes and some basic textures you can import at any time, by just dragging and dropping them on the editor.
You can also load your own meshes and textures from any place on your drive. Beware these have to be compatible with the Mesh in which you are applying them.
## Camera
Wonder Engine also has a camera, controllable with kb&m:
- WASD: movement
- WASD(while RMB): FPS-like movement
- Shift: Double movement speed
- RMB: look around
- Alt + LMB: rotate around
- F: look at 0, 0, 0 position
- F(while Object selected): look at selected Object
## UI
Wonder Engine uses ImGui as the UI library.
Different UI windows are used to display the state of the engine.
### Hierarchy
Here Objects are displayed and can be selected in order to change their variables.
### Console
The engine and editor display the actions that they execute here.
### Inspector
The different variables of the components of the selected object are shown here.
### Configuration
You are able to check the different engine and system variables as well as change some of them:
- Change window size directly or through some presets
- See the application framerate graph
- Check the library versions and system hardware (CPU cores and cache; GPU name, drivers, and vendor; VRAM size, usage, and availability).
### Top Menu
Finally there is a top menu bar where you have the option to toggle these windows, as well as show the default ImGui Demo Window;
the option to access this project's GitHub repository directly and toggle the About window, in which you can check this engine creators' GitHub; and also links to
the websites of all the libraries we used.

As a side note, the inspector window lets you see the selected Object with a default blank checker texture, see the normals of all vertices and faces, as well as
check the number of vertices and faces, and the path of the selected mesh, as the size and the path of the texture attributed to it.
## Libraries
The libraries used for this project are:
- [SDL](https://wiki.libsdl.org/)
- [OpenGL](https://www.opengl.org/)
- [ImGui](https://imgui-test.readthedocs.io/)
- [Assimp](https://assimp-docs.readthedocs.io/)
- [DevIL](https://openil.sourceforge.net/)
- [GLEW](https://glew.sourceforge.net/)
- [GLM](https://glm.g-truc.net/0.9.5/index.html)
- [jsoncpp](https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html)

Vcpkg was used as a library manager for this project

## Models
The default extra meshes were taken from the following sources:
- [Sword](https://free3d.com/3d-model/sting-sword-128810.html "Sting Sword")
- [M16 Rifle](https://sketchfab.com/3d-models/m16-assault-rifle-339d0f7b21024387853dd926a5d51b50 "M16 Assault Rifle")

# V2 ADDITIONS

- Mesh Importer that also allows for saving and loading several meshes at once (by StarvinXarvin)
- Assets window inspector in the menu tab (by StarvinXarvin)
