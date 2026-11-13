// Turbo C++ style graphics.h demo. Press a key, close the window or Ctrl+C
// to exit.
//
// Build and run:   ./run.sh          (Windows: python run.py)
// Plain CMake:     cmake -S . -B build && cmake --build build && ./build/app
#include <graphics.h>

// BGI's delay() polls SDL events and drops the close/quit ones, so a plain
// kbhit() loop never ends when the window is closed or the program gets
// Ctrl+C. An event watch sees exit events before anything can consume them.
static volatile bool stop = false;

static int on_event(void*, SDL_Event* event) {
    if (event->type == SDL_QUIT ||
        (event->type == SDL_WINDOWEVENT &&
         event->window.event == SDL_WINDOWEVENT_CLOSE)) {
        stop = true;
    }
    return 0;
}

int main() {
    int driver = DETECT;
    int mode = 0;
    initgraph(&driver, &mode, nullptr);
    SDL_AddEventWatch(on_event, nullptr);

    const int w = getmaxx();
    const int h = getmaxy();

    // Background: a dusk sky, one BGI line per scanline (BGI has no gradient).
    setbkcolor(BLACK);
    cleardevice();
    for (int y = 0; y < h; ++y) {
        setcolor(8 + (y * 8) / h);
        line(0, y, w, y);
    }
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(w / 2, h / 3, 60, 60);
    setcolor(DARKGRAY);
    line(0, h * 2 / 3, w, h * 2 / 3);

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(20, 20, const_cast<char*>("graphics.h on SDL_bgi"));

    // Animate a ball bouncing inside the frame until a key, the close button
    // or SIGINT/SIGTERM stops it.
    const int radius = 18;
    int x = w / 4, y = h / 4;
    int dx = 6, dy = 4;

    while (!stop && !kbhit()) {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(x, y, radius, radius);

        x += dx;
        y += dy;
        if (x < radius || x > w - radius) dx = -dx;
        if (y < radius + 60 || y > h - radius) dy = -dy;

        setcolor(LIGHTCYAN);
        setfillstyle(SOLID_FILL, CYAN);
        fillellipse(x, y, radius, radius);
        delay(12);
    }

    closegraph();
    return 0;
}
