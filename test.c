#include "sound.h"

int main() {
	LinkedList* waveform1 = newWaveform();
	LinkedList* waveform2 = newWaveform();
	addGuitar(waveform1, 660.0, 2.0);
	addGuitar(waveform2, 440.0, 2.0);
	overlapWaveforms(waveform1, waveform2);
	writeSoundFile("test.wav", waveform1);
	freeWaveform(waveform1);
	freeWaveform(waveform2);
}