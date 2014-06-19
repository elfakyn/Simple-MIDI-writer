#include "musicPrimitives.h"

int scaleChordType(int numeral, int scaleType)
{
	numeral--;
	int row;
	int lookupTable[2][7] = {
		{ // major
			M_GEN_CHORD_MAJOR,
			M_GEN_CHORD_MINOR,
			M_GEN_CHORD_MINOR,
			M_GEN_CHORD_MAJOR,
			M_GEN_CHORD_MINOR,
			M_GEN_CHORD_DIMINISHED,
		},
		{ // minor
			M_GEN_CHORD_MINOR,
			M_GEN_CHORD_DIMINISHED,
			M_GEN_CHORD_MAJOR,
			M_GEN_CHORD_MINOR,
			M_GEN_CHORD_MINOR,
			M_GEN_CHORD_MAJOR,
			M_GEN_CHORD_MAJOR,
		}
	};
	switch (scaleType) {
	case M_PRIM_SCALE_MAJOR:
		row = 0;
		break;
	case M_PRIM_SCALE_MINOR:
		row = 1;
		break;
	default:
		return -1; // really need some error handling or something
	}
	return lookupTable[row][(numeral - 1) % 7];
}

int scaleChordNote(int numeral, int scaleType, int baseNote)
{
	numeral--;
	int row;
	int lookupTable[2][7] = {
		{ 0, 2, 4, 5, 7, 9, 11 }, // major
		{ 0, 2, 3, 5, 7, 8, 10 } // minor
	};
	switch (scaleType) {
	case M_PRIM_SCALE_MAJOR:
		row = 0;
		break;
	case M_PRIM_SCALE_MINOR:
		row = 1;
		break;
	default:
		return -1;
	}
	return baseNote + numeral / 7 * 12 + lookupTable[row][numeral % 7];
}