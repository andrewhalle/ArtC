#include "image.h"
#include <stdio.h>

int main() {
	int width = 250;
	int height = 250;
	char*** image = blankImage(width, height);
	
	int i;
	int x = 30;
	int y = 30;
	char red = 255;
	char green = 0;
	char blue = 0;
	for (i = 0; i < 20; i++) {
		drawCircle(image, width, height, x, y, 20, red, green, blue);
		x += 10;
		y += 10;
		if (red > 0) {
			red -= 26;
			green += 26;
		} else {
			green -= 26;
			blue += 26;
		}
		if (red < 0) {
			red = 0;
		}
		if (green > 255) {
			green = 255;
		}
	}

	writeImage("image.ppm", image, 250, 250);
	freeImage(image, 250, 250);
}