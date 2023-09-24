# SwarmSim Pathfinding

Live simulation of adaptable pathfinding, modelled loosely on the pheromone-based movements of ant colonies.

![GitHub top language](https://img.shields.io/github/languages/top/nem-gdev/swarm-pathfinding-sim?style=for-the-badge&color=rgb(222%2C%2084%2C%20132))
![CodeFactor Grade](https://img.shields.io/codefactor/grade/github/nem-gdev/swarm-pathfinding-sim?style=for-the-badge&color=77%2C%20255%2C%200)
![GitHub](https://img.shields.io/github/license/nem-gdev/swarm-pathfinding-sim?style=for-the-badge&color=critical)





![SwarmSim Demo Gif](Demo.gif) 


## Usage

The swarm agents (ants) will attempt to find a path between the Home & the Food.
You may place multiple of these, and block the path or make a maze with the walls.

*A large set of variables define the characteristics of the colony and program settings.*
*Currently there are multiple ready-made presets that can be picked to initialize the simulation.*

_**Depending on your CPU you may get lower framerates on bigger presets, which will decrease the stability of the simulation.**_

**You can either download and run the executable (Windows), or compile the project yourself (any platform) explained in the next section.**
1. Download & Run <a href="https://github.com/Nem-GDev/swarm-pathfinding-sim/releases/tag/v2.0" target="_blank">`swarm-pathfinding-sim.exe`</a>
2. Commandline UI will guide you through choosing a theme & preset.
3. Simulation Will start automatically.


## Controls

Controls are also mentioned in the commandline UI. For reference:

| Key  | Action |
| ------------- |:-------------:|
| `LMB`    |Draw on map (Pick a brush first)|
| `H`      | Home (brush)     |
| `F`      | Food (brush)     |
| `W`      | Wall (brush)     |
| `C`      | Remove (brush)   |
| `S`      | Show paths       |
| `A`      | Show ants        |



## Compiling yourself

To compile the C++ project you need:

* A C++ compiler installed (`GCC` recommended)
* CMake installed & setup on your system
* <a href="https://vcpkg.io/en/" target="_blank">`vcpkg`</a> installed & setup on your system
* `sfml:x64-windows` library (or corresponding 64bit to your platform) installed on vcpkg

Finally modify the `CMakePresets.json` file in the root of the repository;
`"toolchainFile": "%ADDRESS%"`

Where `%ADDRESS%` is the address to the `vcpkg.cmake` in the root folder of your vcpkg installation.

And build the project with cmake: `cmake -B build -S "%PATH_TO_CLONED_REPO%" --preset RelWithDebInfo`


## Notes

* The aim of this simulation was to keep a natural & organic feel. 
Thus sporadic, aggressive & highly adaptable/regenerative pathing was preferred over perfectly optimized routes.
* This project was completed in 1 week. However further improvement updates may be committed over time.


## Credits

Special thanks to my friends <a href="https://github.com/Sephixum" target="_blank">**Sepehr**</a> & <a href="https://github.com/MiliAxe" target="_blank">**Milad**</a> for their great suggestions & technical help with some aspects of C++.


