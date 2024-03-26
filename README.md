<div style="text-align: center">

# **Intersection of convex polygons**
![intersection](misc/intersection.png)

</div>

## Description
**The Intersections of Convex Polygons** project allows users to solve a mathematical problem concerning finding the common area of intersection of two or more convex polygons on a plane using the resulting *.exe* file format  without having to worry about the intricacies of the implementation.

Our team provide users with a grid on a plane that allows them to construct exclusively convex shapes and see the intersection of these shapes, as well as their area.

The project has important practical applications in computer graphics, design and other areas where geometric data processing is required.



## Possibility of use
As mentioned previously, the project enables users to visually represent convex shapes entered on a grid, identify their intersections, and calculate the area of the overlapping regions. The important feature of the project is the ability to **snap vertices to the grid**, meaning that the coordinates of the figure's vertices can only be integer values located at the grid lines' intersections.

Users can:
- **move along** the grid while **holding down LMB**.
- **zoom** using **mouse wheel**.
- **remove all shapes** from the grid by pressing **Delete** key.
- **move a specific vertex** when you **hover the mouse** over this vertex and **hold down the LCTRL** key.
- **delete a specific vertex** when you **hover the mouse** over this vertex and **press RMB**.
- **delete the last constructed polygon** pressing down **LCTRL** + **Z**.

## Project structure
The project structure looks like this:
```python
C-AUTOCAD-TRIAL-VER/
│
├── include/
│   ├── algorithm.hpp
│   ├── grid.hpp
│   ├── line.hpp
│   ...
├── misc/
│   ├── Dosis-VariableFont_wght.ttf
│   ├── intersection.png
│   ...
├── src/
│   ├── algorithm.cpp
│   ├── grid.cpp
│   ├── line.cpp
│   ...
├── .gitignore
├── CMakeLists.txt
├── README.md
```
The *include* folder contains header files in hpp format for including project files.

The *misc* folder stores auxiliary project files, such as fonts, images for the README, etc.

The *src* folder contains cpp files with project implementation code.

*.gitignore* is necessary to ensure that locally collected files are not uploaded to the shared repository.

*CMakeLists.txt* is required to build the project on the local machine using CMake utilities. As a result, a *../build* folder will be created with the standard project build files.

*README.md* is needed to describe the project on the repository page.
## Authors and Feedback
The project was made by:
- [Vladislav Tyurin](https://github.com/conk7)
- [Pavel Lekomtsev](https://github.com/PavelLekomtsev)
- [Maxim Zakharov](https://github.com/maximvw)
- [Alexey Kalinkin](https://github.com/cactuarix)
- [Timofey Pyankov](https://github.com/TomBomBon)
- [Rodion Kholodov](https://github.com/londxz)
  
  For feedback on the project, you should write to our product manager: *Rodion Kholodov* - https://t.me/londxz