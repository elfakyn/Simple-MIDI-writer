#ifndef MIDI_H
#define MIDI_H

#include <fstream>
#include "event.h"
using std::fstream;

#define M_FORMAT_SINGLE_TRACK 0
#define M_FORMAT_SYNCRHONOUS  1
#define M_FORMAT_ASYNCHRONOUS 2

class M_Stream {
private:
	fstream dev_out;
public:
	M_Stream(char* path)
	{
		dev_out.open(path, fstream::binary | fstream::out);
	}

	~M_Stream()
	{
		dev_out.close();
	}

	void write_int(long value, int length);
	void write_header(int format, unsigned int tracks, unsigned int time_div);
	void write_track(long chunk_size);
	void write_event(M_Event midi_event);
};

#endif