#include "midi.h"

void midi_write_int(fstream &dev_out, int value, int length)
{
	while (length-- >= 0) {
		dev_out.put(value >> 8 * length);
	}
}

void midi_write_header(fstream &dev_out, int format, int tracks, int time_div)
{
	midi_write_int(dev_out, 0x4D546864, 4); // "MThd"
	midi_write_int(dev_out, 6, 4); // Header chunk size is always 6 bytes
	midi_write_int(dev_out, format, 2);
	midi_write_int(dev_out, tracks, 2);
	midi_write_int(dev_out, time_div, 2);
}

void midi_write_track(fstream &dev_out, int chunk_size)
{
	midi_write_int(dev_out, 0x4D54726B, 4); // "MTrk"
	midi_write_int(dev_out, chunk_size, 4);
}