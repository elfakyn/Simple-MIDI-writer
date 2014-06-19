#ifndef MUSICPRIMITIVES_H
#define MUSICPRIMITIVES_H

#include "musicGenerators.h"

#define M_PRIM_SCALE_MAJOR 0
#define M_PRIM_SCALE_MINOR 1

int scaleChordType(int numeral, int scaleType);
int scaleChordNote(int numeral, int scaleType, int baseNote);

#endif