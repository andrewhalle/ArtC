#include <stdio.h>
#include <stdlib.h>

/* Helper math functions */

int circleError(int x, int y, int r) {
	int error = (r*r) - (x*x) - (y*y);
	if (error > 0) {
		return error;
	} else {
		return -error;
	}
}

/* End helper functions */



void writeImage(char* filename, char*** image, int width, int height) {
	FILE* fp = fopen(filename, "wb");
	fprintf(fp, "P6\n%d\n%d\n255\n", width, height);
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			fwrite(image[i][j], sizeof(char), 3, fp);
		}
	}
	fclose(fp);
}

char*** blankImage(int width, int height) {
	int i, j, k;
	char*** image = (char***) malloc(height * sizeof(char**));
	for (i = 0; i < height; i++) {
		image[i] = (char**) malloc(width * sizeof(char*));
		for (j = 0; j < width; j++) {
			image[i][j] = (char*) malloc(3 * sizeof(char));
			for (k = 0; k < 3; k++) {
				image[i][j][k] = 255;
			}
		}
	}
	return image;
}

void freeImage(char*** image, int width, int height) {
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			free(image[i][j]);
		}
		free(image[i]);
	}
	free(image);
}

void setColor(char*** image, int width, int height, int coordX, int coordY, char red, char green, char blue) {
	if ((coordX < width) && (coordY < height)) {
		image[coordY][coordX][0] = red;
		image[coordY][coordX][1] = blue;
		image[coordY][coordX][2] = green;
	}
}

void drawSquare(char*** image, int width, int height, int coordX, int coordY, int radius, char red, char green, char blue) {
	if ((coordX >= radius) && (coordX <= width - radius) && (coordY >= radius) && (coordY <= height - radius)) {
		int i;
		for (i = -radius; i <= radius; i++) {
			setColor(image, width, height, coordX + i, coordY + radius, red, green, blue);
			setColor(image, width, height, coordX + i, coordY - radius, red, green, blue);
			setColor(image, width, height, coordX + radius, coordY + i, red, green, blue);
			setColor(image, width, height, coordX - radius, coordY + i, red, green, blue);
		}
	}
}

void drawCircle(char*** image, int width, int height, int coordX, int coordY, int radius, char red, char green, char blue) {
	if ((coordX >= radius) && (coordX <= width - radius) && (coordY >= radius) && (coordY <= height - radius)) {
		int x = radius;
		int y = 0;
		while (x >= y) {
			setColor(image, width, height, coordX + x, coordY + y, red, green, blue);
			setColor(image, width, height, coordX + y, coordY + x, red, green, blue);
			setColor(image, width, height, coordX - x, coordY + y, red, green, blue);
			setColor(image, width, height, coordX - y, coordY + x, red, green, blue);
			setColor(image, width, height, coordX + x, coordY - y, red, green, blue);
			setColor(image, width, height, coordX + y, coordY - x, red, green, blue);
			setColor(image, width, height, coordX - x, coordY - y, red, green, blue);
			setColor(image, width, height, coordX - y, coordY - x, red, green, blue);
			y += 1;
			if (circleError(x - 1, y, radius) < circleError(x, y, radius)) {
				x -= 1;
			}
		}
	}
}