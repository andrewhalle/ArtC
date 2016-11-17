#include <stdio.h>
#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	addSineWave(waveform, 440.0, 1.0);
	addSineWave(waveform, 880.0, 1.0);
	writeSoundFile("test.wav", waveform);
	freeWaveform(waveform);
}