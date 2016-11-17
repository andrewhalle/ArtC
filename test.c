#include <stdio.h>
#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	unsigned char value = 0;
	char direction = 1;
	int i;
	for (i = 0; i < 44100; i++) {
		appendLinkedList(waveform, value);
		if (value == 255) {
			direction = -1;
		}
		if (value == 0) {
			direction = 1;
		}
		value += direction;
	}
	writeSoundFile("test.wav", waveform);
	freeWaveform(waveform);
}