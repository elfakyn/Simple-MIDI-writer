#ifndef MUSICGENERATORS_H
#define MUSICGENERATORS_H

#include "midi.h"

int linearWalk(M_Event* events, char channel, int velocity, char startingNote, int interval, int notes, int noteLength, int pauseLength);

#endif