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

/* end math */

/* Linked list implementation */

typedef struct LinkedList {
	int size;
	unsigned char value;
	struct LinkedList* next;
} LinkedList;

LinkedList* singleLinkedList(unsigned char v) {
	LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
	ll->size = 1;
	ll->value = v;
	ll->next = NULL;
	return ll;
}

void appendLinkedList(LinkedList* ll, unsigned char value) {
	LinkedList* temp = ll;
	if (temp->next == NULL) {
		temp->next = (LinkedList*) singleLinkedList(value);
		temp->size += 1;
	} else {
		appendLinkedList(ll->next, value);
		ll->size += 1;
	}
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

void addSineWave(LinkedList* waveform, double frequency, double duration) {
	double sampleFreq = 44100;
	double t = 0;
	double value;
	while (t < duration) {
		value += 1;
	}

}