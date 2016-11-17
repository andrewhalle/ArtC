#include <stdio.h>
#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	addSineWave(waveform, 349.23, 0.6);
	printf("1");
	addSineWave(waveform, 622.25, 0.9);
	printf("1");
	addSineWave(waveform, 587.33, 0.3);
	addSineWave(waveform, 523.25, 0.201);
	addSineWave(waveform, 466.16, 0.201);
	addSineWave(waveform, 440, 0.201);
	addSineWave(waveform, 415.30, 1.2);
	writeSoundFile("star_trek.wav", waveform);
	freeWaveform(waveform);
}