#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* Math functions */

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

/* Ring buffer implementation */

typedef struct RingBufferNode {
	double value;
	struct RingBufferNode* next;
	struct RingBufferNode* prev;
} RingBufferNode;

typedef struct RingBuffer {
	RingBufferNode* head;
} RingBuffer;

RingBuffer* ringBufferOfSize(int n) {
	srand(time(NULL));
	RingBuffer* ring = (RingBuffer*) malloc(sizeof(RingBuffer));
	RingBufferNode* h = (RingBufferNode*) malloc(sizeof(RingBufferNode));
	ring->head = h;
	h->value = ((double) rand() / (double) RAND_MAX);
	h->prev = NULL;
	h->next = NULL;
	int i;
	RingBufferNode* traverse = h;
	for (i = 1; i < n; i++) {
		traverse->next = (RingBufferNode*) malloc(sizeof(RingBufferNode));
		traverse->next->value = ((double) rand() / (double) RAND_MAX);
		traverse->next->prev = traverse;
		traverse->next->next = NULL;
		traverse = traverse->next;
	}
	h->prev = traverse;
	traverse->next = h;
	return ring;
}

double averageAndShift(RingBuffer* ring) {
	double x = (ring->head->value + ring->head->next->value) / 2.0;
	RingBufferNode* n = (RingBufferNode*) malloc(sizeof(RingBufferNode));
	n->value = x;
	n->prev = ring->head->prev;
	n->next = ring->head->next;
	ring->head->prev->next = n;
	ring->head->next->prev = n;
	RingBufferNode* temp = ring->head;
	ring->head = ring->head->next;
	free(temp);
	return x;
}

/* end ring buffer */

LinkedList* newWaveform() {
	return singleLinkedList(0);
}

void freeWaveform(LinkedList* waveform) {
	freeLinkedList(waveform);
}

void addSineWave(LinkedList* waveform, double frequency, double duration) {
	double sampleFreq = 44100.0;
	double t = 0;
	double value;
	unsigned char sample;
	while (t < duration) {
		value = sin(2.0 * M_PI * frequency * t) + 1;
		value = (value * 255.0) / 2.0;
		sample = ROUND(value);
		appendLinkedList(waveform, sample);
		t += 1/sampleFreq;
	}

}

void addOrgan(LinkedList* waveform, double frequency, double duration) {
	double sampleFreq = 44100.0;
	double t = 0;
	double value;
	unsigned char sample;
	while (t < duration) {
		value = sin(2.0 * M_PI * frequency * t) + 0.2 * sin(3.0 * M_PI * frequency * t);
		value = value / 1.2;
		value += 1;
		value = (value * 255.0) / 2.0;
		sample = ROUND(value);
		appendLinkedList(waveform, sample);
		t += 1/sampleFreq;
	}
}

void addNoise(LinkedList* waveform, double duration) {
	srand(time(NULL));
	double sampleFreq = 44100.0;
	double t = 0;
	unsigned char sample;
	while (t < duration) {
		int value = rand();
		sample = (unsigned char) value;
		appendLinkedList(waveform, sample);
		t += 1/sampleFreq;
	}
}

void addGuitar(LinkedList* waveform, double frequency, double duration) {
	double sampleFreq = 44100.0;
	RingBuffer* buffer = ringBufferOfSize((int) lround(sampleFreq / frequency));
	double t = 0;
	double value;
	unsigned char sample;
	while (t < duration) {
		value = averageAndShift(buffer);
		sample = ROUND(value * 255.0);
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