#include <stdio.h>
#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	addOrgan(waveform, 349.23, 0.6);
	addOrgan(waveform, 622.25, 0.9);
	addOrgan(waveform, 587.33, 0.3);
	addOrgan(waveform, 523.25, 0.201);
	addOrgan(waveform, 466.16, 0.201);
	addOrgan(waveform, 440, 0.201);
	addOrgan(waveform, 415.30, 1.2);
	writeSoundFile("star_trek.wav", waveform);
	freeWaveform(waveform);
}