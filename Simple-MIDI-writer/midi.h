#ifndef MIDI_H
#define MIDI_H

#include <fstream>
#include "event.h"
using std::fstream;

#define M_FORMAT_SINGLE_TRACK 0
#define M_FORMAT_SYNCHRONOUS  1
#define M_FORMAT_ASYNCHRONOUS 2


#define M_META_SEQUENCE_NUMBER  0x00
#define M_META_TEXT_EVENT		0x01
#define M_META_COPYRIGHT_NOTICE	0x02
#define M_META_SEQUENCE_NAME	0x03
#define M_META_INSTRUMENT_NAME	0x04
#define M_META_LYRICS			0x05
#define M_META_MARKER			0x06
#define M_META_CUE_POINT		0x07
#define M_META_CHANNEL_PREFIX	0x20
#define M_META_END_OF_TRACK		0x2F
#define M_META_SET_TEMPO		0x51
#define M_META_SMPTE_OFFSET		0x54
#define M_META_TIME_SIGNATURE	0x58
#define M_META_KEY_SIGNATURE	0x59

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
	int write_meta_event(char type, char* data, int length = 0);
};

#endif