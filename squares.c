#include "image.h"

int main() {
	int width = 275;
	int height = 275;
	char*** image = blankImage(width, height);
	int i;
	int coordX = 40;
	int coordY = 40;
	int red = 255;
	int green = 0;
	int blue = 0;
	for (i = 0; i < 20; i++) {
		drawSquare(image, width, height, coordX, coordY, 20, red, green, blue);
		coordX += 10;
		coordY += 10;
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
	writeImage("image.ppm", image, width, height);
	freeImage(image, width, height);
}