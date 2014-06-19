#ifndef MUSICGENERATORS_H
#define MUSICGENERATORS_H

#include "midi.h"
#include "musicPrimitives.h"

#define M_GEN_CHORD_MAJOR      0
#define M_GEN_CHORD_MINOR      1
#define M_GEN_CHORD_AUGMENTED  2
#define M_GEN_CHORD_DIMINISHED 3

int linearWalk(M_Event* events, char channel, int velocity, char baseNote, unsigned long noteLength, unsigned long pauseLength, int interval, int number);
int chord(M_Event* events, char channel, int velocity, char baseNote, unsigned long noteLength, unsigned long pauseLength, int type);
int scaleWalk(M_Event* events, char channel, int velocity, char baseNote, unsigned long noteLength, unsigned long pauseLength, int scaleType, int baseNumeral, int minNumeral, int maxNumeral, int number, int switchProb, int stepSize);
int chordWalk(M_Event* events, char channel, int velocity, char baseNote, unsigned long noteLength, unsigned long pauseLength, int scaleType, int baseNumeral, int minNumeral, int maxNumeral, int number, int switchProb, int stepSize);
#endif