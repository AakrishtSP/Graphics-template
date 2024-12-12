#include <graphics.h>

int main()
{
	int gm, gd = DETECT;
	initgraph(&gd, &gm, NULL);

	// Your code here

	getch();
	closegraph();
	return 0;
}