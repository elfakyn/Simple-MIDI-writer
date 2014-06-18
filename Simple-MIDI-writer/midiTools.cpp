#include "midi.h"

void M_Stream::write_int(long value, int length)
{
	while (--length >= 0) {
		dev_out.put((char)(value >> 8 * length));
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

int M_Stream::write_meta_event(char type, char* data, int length)
{
	switch (type) {
	case M_META_SEQUENCE_NUMBER:
		length = 2;
		break;
	case M_META_TEXT_EVENT:
	case M_META_COPYRIGHT_NOTICE:
	case M_META_SEQUENCE_NAME:
	case M_META_INSTRUMENT_NAME:
	case M_META_LYRICS:
	case M_META_MARKER:
	case M_META_CUE_POINT:
		break;
	case M_META_CHANNEL_PREFIX:
		length = 1;
		break;
	case M_META_END_OF_TRACK:
		length = 0;
		break;
	case M_META_SET_TEMPO:
		length = 3;
		break;
	case M_META_SMPTE_OFFSET:
		length = 5;
		break;
	case M_META_TIME_SIGNATURE:
		length = 4;
		break;
	case M_META_KEY_SIGNATURE:
		length = 2;
		break;
	default:
		return 0;
	}

	if (length == -1) {
		return 0; // silently fail
	}
	dev_out.put(0x00); // event always prefixed with 0x00
	dev_out.put(0xFF);
	dev_out.put(type);
	dev_out.put((char)length);
	dev_out.write(data, length);

	return 4 + length;
}