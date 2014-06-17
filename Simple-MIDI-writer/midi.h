#ifndef MIDI_H
#define MIDI_H

#include <fstream>
#include "event.h"
using std::fstream;

class M_Stream {
private:
	fstream dev_out;
public:
	M_Stream(char &path)
	{
		dev_out.open(&path, fstream::binary | fstream::out);
	}

	~M_Stream()
	{
		dev_out.close();
	}

	void write_int(long value, int length);
	void write_header(int format, int tracks, int time_div);
	void write_track(long chunk_size);
	void write_event(M_Event midi_event);
};

#endif