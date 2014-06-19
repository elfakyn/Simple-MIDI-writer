#include <stdlib.h>
#include "musicGenerators.h"

int linearWalk(M_Event* events, char channel, int velocity, char baseNote, unsigned long noteLength, unsigned long pauseLength, int interval, int number)
{
	for (int i = 0, j = 0; i < number; i++, j += 2) {
		events[j].set_values(M_NOTE_ON, channel, baseNote + i * interval, velocity);
		events[j].set_delta_t(pauseLength);

		events[j + 1].set_values(M_NOTE_OFF, channel, baseNote + i * interval, velocity);
		events[j + 1].set_delta_t(noteLength);
	}
	return number;
}

int chord(M_Event* events, char channel, int velocity, char baseNote, unsigned long noteLength, unsigned long pauseLength, int type)
{
	int second, third;

	switch (type) {
	case M_GEN_CHORD_MAJOR:
		second = 4;
		third = 7;
		break;
	case M_GEN_CHORD_MINOR:
		second = 3;
		third = 7;
		break;
	case M_GEN_CHORD_AUGMENTED:
		second = 4;
		third = 8;
		break;
	case M_GEN_CHORD_DIMINISHED:
		second = 3;
		third = 6;
		break;
	default:
		return 0; // fail silently
	}

	int count = 0;

	
	events[count].set_values(M_NOTE_ON, channel, baseNote, velocity);
	events[count++].set_delta_t(pauseLength);
	events[count].set_values(M_NOTE_ON, channel, baseNote + second, velocity);
	events[count++].set_delta_t(0);
	events[count].set_values(M_NOTE_ON, channel, baseNote + third, velocity);
	events[count++].set_delta_t(0);
	
	events[count].set_values(M_NOTE_OFF, channel, baseNote, velocity);
	events[count++].set_delta_t(noteLength);
	events[count].set_values(M_NOTE_OFF, channel, baseNote + second, velocity);
	events[count++].set_delta_t(0);
	events[count].set_values(M_NOTE_OFF, channel, baseNote + third, velocity);
	events[count++].set_delta_t(0);

	return count;
}

int scaleWalk(M_Event* events, char channel, int velocity, char baseNote, unsigned long noteLength, unsigned long pauseLength, int scaleType, int baseNumeral, int minNumeral, int maxNumeral, int number, int switchProb)
{
	int direction = 1;
	int numeral = baseNumeral;
	int count = 0;
	int note;
	for (int i = 0; i < number; i++) {
		note = scaleChordNote(numeral, scaleType, baseNote);
		events[count].set_values(M_NOTE_ON, channel, note, velocity);
		events[count++].set_delta_t(pauseLength);
		events[count].set_values(M_NOTE_OFF, channel, note, velocity);
		events[count++].set_delta_t(noteLength);
		if (rand() % 100 < switchProb) {
			direction = -direction;
		}
		numeral = numeral + direction;
		if ((numeral < minNumeral || numeral > maxNumeral)) { // outside the scale
			direction = -direction;
			numeral = numeral + 2*direction;
		}
	}
	return count;
}