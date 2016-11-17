#include <stdio.h>
#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	addOrgan(waveform, 440.0, 2.0);
	writeSoundFile("test.wav", waveform);
	freeWaveform(waveform);
}