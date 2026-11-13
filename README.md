# graphics.h template (Turbo C++ BGI, modern C++)

Write the old Turbo C++ graphics programs — `initgraph`, `line`, `circle`,
`outtextxy`, `getch` — and run them on Linux, macOS and Windows with a modern
compiler. No MS-DOS, no Turbo C, no MinGW-only libbgi, no linker flags to hunt
down: this is a GitHub template with `graphics.h` already wired into CMake.

```cpp
#include <graphics.h>

int main() {
    int driver = DETECT, mode;
    initgraph(&driver, &mode, nullptr);
    circle(320, 240, 100);
    getch();
    closegraph();
}
```

Press **Run** in VS Code, or `./run.sh`. That's the whole setup.

## Use this template

Click **Use this template → Create a new repository**, then:

```bash
git clone https://github.com/<you>/<your-repo> my-graphics-lab
cd my-graphics-lab
./run.sh          # Linux / macOS / Git Bash
python run.py    # Windows (or anywhere with Python 3)
```

The first configure downloads SDL_bgi (and SDL2, if you do not have it
installed) into `build/_deps`; later builds are instant.

## Why SDL_bgi and not libbgi / WinBGIm

Most `graphics.h` templates hand you a prebuilt `libbgi.a` and a pile of Win32
libraries (`gdi32`, `comdlg32`, `ole32`, `uuid`, …). That library is a 2000s
port of BGI to Win32: it only links with MinGW, it cannot run on Linux or macOS
or in a browser, and it is unmaintained.

[SDL_bgi](https://github.com/sergev/SDL_bgi) implements the same BGI API on top
of SDL2, in plain C, under the zlib licence:

- **Same API** — `initgraph`, `closegraph`, `line`, `circle`, `fillellipse`,
  `floodfill`, `setcolor`, `setfillstyle`, `outtextxy`, `getmaxx`, `delay`,
  `kbhit`, `getch`, all the BGI fonts and colour constants.
- **Cross-platform** — Linux, macOS, Windows, WebAssembly and Python.
- **Real window** — SDL2 handles the window, input and rendering; no Win32.
- **Builds from source** — the template compiles SDL_bgi itself, so it works
  with whatever compiler you have.

The trade-off: SDL_bgi needs SDL2. On Linux install `libsdl2-dev`, on macOS
`brew install sdl2`; on Windows the template fetches and builds SDL2 for you.

## Quick start

```bash
./run.sh                        # build src/main.cpp and run it
./run.sh -f src/foo.cpp         # build any other file
./run.sh -r                     # release build
./run.sh -c                     # wipe the build directory first
./run.sh -B                     # build without running
./run.sh -- --flag 42           # everything after -- goes to the program
```

Plain CMake works too:

```bash
cmake -S . -B build
cmake --build build
./build/app
```

## CMake options

| Option | Default | Meaning |
|---|---|---|
| `FILE` | `src/main.cpp` | Source file to build |
| `GRAPHICS` | `ON` | Link `graphics.h` (SDL_bgi). `-DGRAPHICS=OFF` builds plain C/C++ |
| `CPP_STD` | `20` | C++ standard: `17`, `20` or `23` |
| `IMPORT_STD` | `OFF` | Use `import std;` instead of `#include` (C++23) |
| `SDL_BGI_TAG` | pinned commit | SDL_bgi revision to fetch |

```bash
cmake -S . -B build -DGRAPHICS=OFF      # plain console program
cmake -S . -B build -DCPP_STD=23
./run.sh -i -f src/foo.cpp              # import std (own build directory)
```

`CPP_STD` and `IMPORT_STD` are inherited from the companion
[single-file C/C++ runner](https://github.com/AakrishtSP/cpp-single-file-runner),
which is this template without the graphics part.

## Layout

```
.
├── CMakeLists.txt        # single-file target + SDL_bgi wiring
├── CMakePresets.json     # default | release | import-std | make
├── run.sh, run.py        # configure + build + run
├── src/main.cpp          # the demo: dusk sky, bouncing ball, press a key to exit
├── examples/hello.c      # plain C program, proves it all works from C too
└── .vscode/              # settings, tasks, launch, IntelliSense, extensions
```

The source file is a cache variable: `-DFILE=...`, else `src/main.cpp`, else
`src/main.c`, else the only file in `src/`. The language is enabled from the
extension, so a C-only machine never needs a C++ compiler.

## How the graphics bits are wired

`graphics.h` from SDL_bgi is a one-line file that includes `<SDL2/SDL_bgi.h>`,
so both headers are copied at configure time into `build/bgi_include/` and
`build/bgi_include/SDL2/`. SDL_bgi is compiled from source into a static
library and linked to the target: no install step, no system-wide headers.

SDL_bgi's own `CMakeLists.txt` insists on a preinstalled SDL2 found through the
old `SDL2_INCLUDE_DIRS` variables, so this template fetches the sources without
running their build file and depends on SDL2 alone.

## VS Code

Open the folder, accept the recommended extensions (`cpptools`, `cmake-tools`):

- **Ctrl+Shift+B** — build.
- **Ctrl+Shift+P → Tasks: Run Task** — `Run`, `Run current file`,
  `Build current file`, `Clean`.
- **F5** — debug with gdb (Linux/MinGW) or lldb (macOS).

IntelliSense resolves `graphics.h` from the generated include directory, so the
editor and the compiler agree about the API.

## Other IDEs

`CMakePresets.json` is read by CLion, Visual Studio, Qt Creator and anything
else that speaks CMake. Open the project, pick the `default` preset, then build
and run the `app` target. No IDE-specific project files needed.

## Requirements

- CMake ≥ 3.20
- GCC, Clang or MSVC (MinGW-w64 on Windows)
- SDL2 development files, or let the template fetch them
- Ninja (optional, recommended) and Git (to fetch SDL_bgi on first configure)
- Python 3.8+ (only for `run.py`)

## Troubleshooting

**Black window / nothing drawn** — the demo waits for a key: click the window
and press a key. Over SSH, `SDL_VIDEODRIVER=dummy ./build/app` runs without a
display.

**The window will not close** — SDL_bgi's `delay()` polls SDL events and throws
away the close and quit ones, so `while (!kbhit())` never ends when the window
manager closes the window or the program receives Ctrl+C. `src/main.cpp` shows
the way out: an `SDL_AddEventWatch` callback sees those events before anything
consumes them and ends the loop.

**`initgraph` fails** — usually a missing display (`DISPLAY` unset over SSH) or
a broken SDL2 install; `SDL_VIDEODRIVER=dummy ./build/app` tells them apart.

**Old code includes `<conio.h>`** — `getch`/`kbhit` come with SDL_bgi through
`<graphics.h>`; drop the `conio.h` include.

## Licence

Template code: MIT — see [LICENSE](LICENSE). SDL_bgi is fetched at configure
time under the zlib licence; SDL2 under the zlib licence.
