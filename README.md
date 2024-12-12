# Graphics.h Template for Visual Studio Code

This template provides an easy-to-use setup for running C++ graphics programs using `<graphics.h>` in Visual Studio Code. Setting up `graphics.h` can be challenging due to compatibility issues, but this template simplifies the process by pre-configuring the required files and folder structure.

## Features

-   Pre-configured folder structure for headers and libraries.
-   `graphics.h` and `libbgi.a` included in the template.
-   VS Code configurations for building and debugging.
-   MinGW setup instructions for seamless integration.

## Why `graphics.h` is Hard to Set Up in VS Code

The `graphics.h` library was originally designed for Turbo C++ and is not natively supported by modern compilers. This makes it challenging to:

-   Set up the necessary library files.
-   Ensure proper linking during compilation.
-   Handle compatibility with modern IDEs like Visual Studio Code.

This template overcomes these issues by including all necessary files and configuring the build system for you.

## Folder Structure

The template is organized as follows:

```
workspace/
├── include/        # Contains graphics.h and winbgi.h
├── lib/            # Contains libbgi.a
├── src/            # Source files go here (e.g., main.cpp)
├── build/          # Compiled binaries will be generated here
├── .vscode/        # VS Code configurations
│   ├── launch.json
│   ├── tasks.json
│   ├── c_cpp_properties.json
```

Simply place your C++ source files inside the `src/` folder, and the template will handle the rest.

## How to Install MinGW and Add it to PATH

1. Download MinGW from the [official website](https://osdn.net/projects/mingw/).
2. Run the installer and select `gcc`, `g++`, and `gdb` during installation.
3. Once installed, find the `bin` folder inside your MinGW installation directory (e.g., `C:\MinGW\bin`).
4. Add the `bin` folder to your system's PATH:
    - Open System Properties > Advanced > Environment Variables.
    - Find the `Path` variable, click Edit, and add the path to the `bin` folder.
5. Verify the installation by running `gcc --version` and `g++ --version` in a terminal.

## How to Clone and Use This Template

1. Clone the repository:
    ```bash
    git clone https://github.com/AakrishtSP/graphics-template.git
    ```
2. Navigate to the project directory:
    ```bash
    cd graphics-template
    ```
3. Open the project in VS Code:
    ```bash
    code .
    ```
4. Add your source files to the `src/` folder.
5. Build and run your project:
    - Build: Press `Ctrl+Shift+B`.
    - Run: Press `F5`.

## How to Use This Template in Your Projects

1. Clone this template as the starting point for your project.
2. Copy your existing C++ source files into the `src/` folder.
3. Modify or add new files as needed within the `src/` directory.
4. Follow the build and run instructions provided above.

## Follow Me on GitHub

If you find this template useful, consider following me on GitHub for more projects and resources:
[GitHub Profile](https://github.com/AakrishtSP)

## Additional Notes

-   Ensure you use `g++` with the correct flags as configured in `tasks.json` to avoid issues with linking `graphics.h`.
-   If you encounter any issues, check that the `include` and `lib` directories are correctly referenced in the configurations.
-   This template is designed for Windows and may require modifications for other platforms.

Happy coding!
