#include <stdio.h>
#include <stdlib.h>

/* Math functions */

double PI() {
	return 3.14159;
}

double SIN(double x) {
	double sign;
	if (x < 0) {
		return SIN(x + (2.0 * PI()));
	}
	if (x > 2.0*PI()) {
		return SIN(x - (2.0*PI()));
	}
	if (x < PI() / 2.0) {
		sign = 1.0;
	} else if (x < PI()) {
		sign = 1.0;
		x = PI() - x;
	} else if (x < PI() * (3.0/2.0)) {
		sign = -1;
		x -= PI();
	} else if(x < 2.0 * PI()) {
		sign = -1;
		x -= PI();
		x = PI() - x;
	} else if (x == 0) {
		return 0;
	} else if (x == PI() / 2) {
		return 1;
	} else if (x == PI() * (3.0/2.0)) {
		return -1;
	} else {
		return 0;
	}
	if (x < PI()/4.0) {
		return sign * (x - (x*x*x)/6.0 + (x*x*x*x*x)/120.0);
	} else {
		x = PI()/2.0 - x;
		return sign * (1 - (x*x)/2.0 + (x*x*x*x)/24.0 - (x*x*x*x*x*x)/720.0);
	}
}

unsigned char ROUND(double x) {
	int base = (int) x;
	double y = x - (double) base;
	if (y >= 0.5) {
		base += 1;
	}
	if (base > 255) {
		base = 255;
	}
	return base;
}

/* end math */

/* Linked list implementation */

typedef struct LinkedList {
	int size;
	unsigned char value;
	struct LinkedList* next;
	struct LinkedList* end;
} LinkedList;

LinkedList* singleLinkedList(unsigned char v) {
	LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
	ll->size = 1;
	ll->value = v;
	ll->next = NULL;
	ll->end = ll;
	return ll;
}

void appendLinkedList(LinkedList* ll, unsigned char value) {
	ll->end->next = singleLinkedList(value);
	ll->end = ll->end->next;
	ll->size += 1;
}

void freeLinkedList(LinkedList* ll) {
	if (ll->next == NULL) {
		free(ll);
	} else {
		free(ll->next);
		free(ll);
	}
}

/* End linked list */

LinkedList* newWaveform() {
	return singleLinkedList(0);
}

void freeWaveform(LinkedList* waveform) {
	freeLinkedList(waveform);
}

void addSineWave(LinkedList* waveform, double frequency, double duration) {
	double sampleFreq = 44100;
	double t = 0;
	double value;
	unsigned char sample;
	while (t < duration) {
		value = SIN(2.0 * PI() * frequency * t) + 1;
		value = (value * 255.0) / 2.0;
		sample = ROUND(value);
		appendLinkedList(waveform, sample);
		t += 1/sampleFreq;
	}

}

void addOrgan(LinkedList* waveform, double frequency, double duration) {
	double sampleFreq = 44100;
	double t = 0;
	double value;
	unsigned char sample;
	while (t < duration) {
		value = SIN(2.0 * PI() * frequency * t) + 0.2 * SIN(3.0 * PI() * frequency * t) + 1.5;
		value = value / 1.2;
		value = (value * 255.0) / 2.0;
		sample = ROUND(value);
		appendLinkedList(waveform, sample);
		t += 1/sampleFreq;
	}
}

void loadSize(int number, unsigned char* size) {
	int i;
	for(i = 0; i < 4; i++) {
		size[i] = (unsigned char) (number & 0xff);
		number = number >> 8;
	}
}

void writeSoundFile(char* filename, LinkedList* waveform) {
	FILE* fp = fopen(filename, "wb");
	unsigned char x[] = {0x52, 0x49, 0x46, 0x46};
	unsigned char y[] = {0x57, 0x41, 0x56, 0x45, 0x66, 0x6d, 0x74, 0x20, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x44, 0xac, 0x00, 0x00, 0x44, 0xac, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x64, 0x61, 0x74, 0x61};
	unsigned char size[4];
	fwrite(x, sizeof(char), 4, fp);
	loadSize(waveform->size + 36, size);
	fwrite(size, sizeof(char), 4, fp);
	fwrite(y, sizeof(char), 32, fp);
	loadSize(waveform->size, size);
	fwrite(size, sizeof(char), 4, fp);
	unsigned char v[1];
	while (waveform != NULL) {
		v[0] = waveform->value;
		fwrite(v, sizeof(char), 1, fp);
		waveform = waveform->next;
	}
	fclose(fp);
}