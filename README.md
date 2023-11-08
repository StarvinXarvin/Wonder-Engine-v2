# WonderEngine
Wonder Engine is a 3D Game Engine with basic Mesh and Texture loading functionality.
## Functionality
Wonder Engine comes with 3 default meshes and some basic textures you can import at any time, by just dragging and dropping them on the editor.
You can also load your own meshes and textures from any place of your drive. Beware theose have to be compatible with the Mesh in which you are applying them.
### Camera
Wonder Engine also has a camera, controllable with kb&m:
- WASD: movement
- WASD(while RMB): FPS-like movement
- Shift: Double movement speed
- RMB: look around
- Alt + LMB: rotate around
- F: look at 0, 0, 0 position
- F(while Object selected): look at selected Object
### UI
Wonder Engine uses ImGui as the UI library.
Different UI windows are used to display the state of the engine, such as the object hierarchy in which you select Objects in order to change their variables,
a console in which the engine and editor display the actions that execute, the inspector in which you can see the different variables of the components of the
selected object, a configuration window where you can check different engine and system variables as well as change some of them: change window size directly or
through some presets, see the application framerate graph, check the library versions and system hardware (CPU cores and cache; GPU name, drivers and vendor;
VRAM size, usage and available). Finally there is a top menu bar where you have the option to toggle these windows, as well as show the default ImGui Demo Window,
the option to access this project's GitHub repository directly and toggle the About window, in which you can check this engine creators' GitHub and also links to
the websites of all the libraries we used.

As a sidenote, the inspector window lets you see the selected Object with a default blank checker texture, see the normals of all vertices and faces, as well as
check the number of vertices and faces, and the path of the selected mesh, also the size and the path of the texture atributed to it.

The default extra meshes where taken from the following sources:
- [Sword](https://free3d.com/3d-model/sting-sword-128810.html "Sting Sword")
