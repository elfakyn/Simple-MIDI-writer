#include "midi.h"

void M_Stream::write_int(long value, int length)
{
	while (--length >= 0) {
		dev_out.put(value >> 8 * length);
	}
}

void M_Stream::write_header(int format, unsigned int tracks, unsigned int time_div)
{
	dev_out.write("MThd", 4);
	write_int(6, 4); // Header chunk size is always 6 bytes
	write_int(format, 2);
	write_int(tracks, 2);
	write_int(time_div, 2);
}

void M_Stream::write_track(long chunk_size)
{
	dev_out.write("MTrk", 4);
	write_int(chunk_size, 4);
}

void M_Stream::write_event(M_Event midi_event)
{
	char data[3];
	char vlv[5];
	int vlv_length;

	midi_event.get_data(data);
	midi_event.get_vlv(vlv);
	vlv_length = midi_event.get_vlv_length();

	dev_out.write(vlv, vlv_length);
	dev_out.write(data, 3);
}