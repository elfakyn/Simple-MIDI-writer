#include "musicGenerators.h"

int linearWalk(M_Event* events, int channel, int velocity, int startingNote, int interval, int notes, int noteLength, int pauseLength)
{
	for (int i = 0, j = 0; i < notes; i++, j += 2) {
		events[j].set_values(M_NOTE_ON, channel, startingNote + i * interval, velocity);
		events[j].set_delta_t(pauseLength);

		events[j + 1].set_values(M_NOTE_OFF, channel, startingNote + i * interval, velocity);
		events[j + 1].set_delta_t(noteLength);
	}
	return notes;
}