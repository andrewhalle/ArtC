#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	addGuitar(waveform, 349.23, 0.6);
	addGuitar(waveform, 622.25, 0.9);
	addGuitar(waveform, 587.33, 0.3);
	addGuitar(waveform, 523.25, 0.201);
	addGuitar(waveform, 466.16, 0.201);
	addGuitar(waveform, 440, 0.201);
	addGuitar(waveform, 415.30, 1.2);
	writeSoundFile("star_trek.wav", waveform);
	freeWaveform(waveform);
}