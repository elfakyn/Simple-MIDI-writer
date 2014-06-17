#include <fstream>

#ifndef MIDI_H
#define MIDI_H

using std::fstream;

void midi_write_int(fstream &dev_out, int value, int length);
void midi_write_header(fstream &dev_out, int format, int tracks, int time_div);
void midi_write_track(fstream &dev_out, int chunk_size);

#endif