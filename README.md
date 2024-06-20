# FDF Project
### (42 School Project | still in progress)
---
---

## Overview

The FDF (Fil De Fer) project is a graphical program that reads a file containing 3D map data and visualizes it in a 2D window using isometric projection. The program uses the MiniLibX graphics library to render the map and display it in a window. This project is a part of the 42 School curriculum, designed to teach students about graphics programming, file parsing, and memory management.
---
---
## Features

- Reads 3D map data from a file in the form of coordinates.
- Visualizes the 3D map in a 2D isometric projection.
- Displays window size and points' coordinates on the screen.
- Supports basic interaction via keyboard and window events.

## Getting Started

### Prerequisites

- MiniLibX library
- Make sure you have a Unix-like operating system (Linux or macOS).

### Installation

1. **Clone the repository:**

    ```sh
    git clone https://github.com/yourusername/fdf.git
    cd fdf
    ```

2. **Build the project:**

    ```sh
    make
    ```

### Usage

To run the program, use the following command:

```sh
./fdf <file>


./fdf maps/test_maps/10-2.fdf
```


Functions Used

    . read_fdf(file, grid): Reads the 3D map data from the file and stores it in the grid structure.
    . init_mlx(): Initializes the MiniLibX library.
    . create_window(window): Creates a window with the specified dimensions.
    . create_image(window): Creates an image buffer to draw on.
    . draw_line(window, p1, p2, color): Draws a line between points p1 and p2 with the specified color.
    . mlx_put_image_to_window(mlx, win, img, x, y): Displays the image in the window.
    . mlx_string_put(mlx, win, x, y, color, string): Displays a string in the window at the specified coordinates.
    . mlx_key_hook(win, key_handle, param): Sets up a key hook to handle keyboard events.
    . mlx_hook(win, 17, 0, close_window, param): Sets up a hook to handle window close events.
    . mlx_loop(mlx): Starts the MiniLibX event loop.

File Structure

    . src/: Contains the source code files.
    . inc/: Contains the header files.
    . maps/: Contains sample 3D map data files.
    . Makefile: Script to build the project.

Dependencies

    MiniLibX: A small graphics library for creating windows, drawing images, and handling events.


This project is licensed under the MIT License. See the LICENSE file for details.
Acknowledgments

    Thanks to the authors and maintainers of MiniLibX.
    Special thanks to the 42 School for providing the project specifications and environment.
