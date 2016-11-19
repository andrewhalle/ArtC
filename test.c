#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	addGuitar(waveform, 660.0, 2.0);
	writeSoundFile("test.wav", waveform);
	freeWaveform(waveform);
}