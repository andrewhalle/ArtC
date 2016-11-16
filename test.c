#include "image.h"
#include <stdio.h>

int main() {
	char*** image = blankImage(250, 250);
	drawCircle(image, 250, 250, 100, 100, 50, 0, 0, 0);
	writeImage("image.ppm", image, 250, 250);
	freeImage(image, 250, 250);
}