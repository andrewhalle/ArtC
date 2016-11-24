#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	addCello(waveform, 415.30, 2.0);
	writeSoundFile("test.wav", waveform);
	freeWaveform(waveform);
}