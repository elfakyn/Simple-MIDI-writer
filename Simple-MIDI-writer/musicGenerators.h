#ifndef MUSICGENERATORS_H
#define MUSICGENERATORS_H

#include "midi.h"

int linearWalk(M_Event* events, int channel, int velocity, int startingNote, int interval, int notes, int noteLength, int pauseLength);

#endif