# SwarmSim Pathfinding

Live simulation of adaptable pathfinding, modelled loosely on the pheromone-based movements of ant colonies.

![GitHub top language](https://img.shields.io/github/languages/top/nem-gdev/swarm-pathfinding-sim)
    [![CodeFactor](https://www.codefactor.io/repository/github/nem-gdev/swarm-pathfinding-sim/badge/main)](https://www.codefactor.io/repository/github/nem-gdev/swarm-pathfinding-sim/overview/main)     ![GitHub](https://img.shields.io/github/license/nem-gdev/swarm-pathfinding-sim)




![SwarmSim Demo Gif](Demo.gif) 


## Usage

The swarm agents (ants) will attempt to find a path between the Home & the Food.
You may place multiple of these, and block the path or make a maze with the walls.

*A large set of variables define the characteristics of the colony and program settings.*
*Currently there are multiple ready-made presets that can be picked to initialize the simulation.*

_**Depending on your CPU you may get lower framerates on bigger presets, which will decrease the stability of the simulation.**_

**You can either download and run the executable (Windows), or compile the project yourself (any platform) explained in the next section.**
1. Download & Run [`swarm-pathfinding-sim.exe`](https://github.com/Nem-GDev/swarm-pathfinding-sim/releases/tag/v2.0)
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
* CMake setup on your system
* [`vcpkg`](https://vcpkg.io/en/) installed
* `sfml:x64-windows` library installed on vcpkg

Finally modify the `CMakePresets.json` file in the root of the repository;
`"toolchainFile": "%ADDRESS%"`
Where `%ADDRESS%` is the address to the `vcpkg.cmake` in the root folder of your vcpkg installation.

And build the project with cmake: `cmake -B build -S "%PATH_TO_CLONED_REPO%" --preset RelWithDebInfo`


## Notes

* The aim of this simulation was to keep a natural & organic feel. 
Thus sporadic, aggressive & highly adaptable/regenerative pathing was preferred over perfectly optimized routes.
* This project was completed in 1 week. However further improvement updates may be committed over time.


## Credits

Special thanks to my friends [Sepehr](https://github.com/Sephixum) & [Milad](https://github.com/MiliAxe) for their great suggestions & technical help with some aspects of C++.


