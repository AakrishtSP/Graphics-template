// Turbo C++ style graphics.h demo. Press a key (or close the window) to exit.
//
// Build and run:   ./run.sh          (Windows: .\run.ps1)
// Plain CMake:     cmake -S . -B build && cmake --build build && ./build/app
#include <graphics.h>

int main() {
    int driver = DETECT;
    int mode = 0;
    initgraph(&driver, &mode, nullptr);

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

    // Animate a ball bouncing inside the frame until a key is pressed.
    const int radius = 18;
    int x = w / 4, y = h / 4;
    int dx = 6, dy = 4;

    while (!kbhit()) {
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
