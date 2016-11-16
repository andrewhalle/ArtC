#include <stdio.h>
#include <stdlib.h>

/* Helper math functions */

double square_root(double x, double precision) {
	double guess = x / 2.0;
	double result = x / guess;
	while ((result - guess > precision) || (guess - result > precision)) {
		guess = (result + guess) / 2.0;
		result = x / guess;
	}
	return result;
}

int round_double(double x) {
	int x_prime = (int) x;
	double check_decimal = (double) x_prime;
	if (x - check_decimal >= 0.5) {
		return x_prime + 1;
	} else {
		return x_prime;
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
		double x_left, x_right, y_left, y_right;
		double r = (double) radius;
		int i, j;
		for (i = -radius + 1; i < radius; i++) {
			x_left = (double) i - 0.5;
			x_right = (double) i + 0.5;
			y_left = (r * r) - (x_left * x_left);
			y_left = square_root(y_left, 0.01);
			y_right = (r * r) - (x_right * x_right);
			y_right = square_root(y_right, 0.01);
			if (y_left > y_right) {
				for (j = round_double(y_right); j < round_double(y_left); j++) {
					setColor(image, width, height, i + coordX, coordY + j, red, green, blue);
					setColor(image, width, height, i + coordX, coordY - j, red, green, blue);
				}
			} else if (y_right > y_left) {
				for (j = round_double(y_left); j < round_double(y_right); j++) {
					setColor(image, width, height, i + coordX, coordY + j, red, green, blue);
					setColor(image, width, height, i + coordX, coordY - j, red, green, blue);
				}
			} else {
				setColor(image, width, height, i + coordX, round_double(y_left) + coordY, red, green, blue);
			}
		}
		setColor(image, width, height, coordX - r, coordY, red, green, blue);
		setColor(image, width, height, coordX - r, coordY - 1, red, green, blue);
		setColor(image, width, height, coordX - r, coordY + 1, red, green, blue);
		setColor(image, width, height, coordX + r, coordY, red, green, blue);
		setColor(image, width, height, coordX + r, coordY - 1, red, green, blue);
		setColor(image, width, height, coordX + r, coordY + 1, red, green, blue);
	}
}