#include "sound.h"

int main() {
	LinkedList* waveform = newWaveform();
	int i;
	for (i = 0; i < 3; i++) {
		addGuitar(waveform, 293.66, 0.23);
		addGuitar(waveform, 587.33, 0.23);
		addGuitar(waveform, 440.00, 0.23);
		addGuitar(waveform, 293.66, 0.23);
		addGuitar(waveform, 783.99, 0.23);
		addGuitar(waveform, 587.33, 0.23);
		addGuitar(waveform, 739.99, 0.23);
		addGuitar(waveform, 587.33, 0.23);
	}
	writeSoundFile("sweet_child.wav", waveform);
	freeWaveform(waveform);
}