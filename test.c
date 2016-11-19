#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	addNoise(waveform, 2.0);
	writeSoundFile("test.wav", waveform);
	freeWaveform(waveform);
}