#include <iostream>
#include "midi.h"

using std::cout;

int main(void)
{
	M_Stream *m = new M_Stream("test.mid");

	m->write_header(M_FORMAT_SINGLE_TRACK, 1, 0x9E78); // 30fps @ 120 ticks/frame

	M_Event events[10];
	int track_length = 0;
	unsigned long __delta_t = 24000;
	for (int i = 0; i < 10; i += 2) {
		
		events[i].set_values(M_NOTE_ON, 1, 60 + i, 127);
		events[i].set_delta_t(__delta_t);
		track_length += events[i].get_vlv_length() + 3;
		events[i + 1].set_values(M_NOTE_OFF, 1, 60 + i, 127);
		events[i + 1].set_delta_t(__delta_t);
		track_length += events[i + 1].get_vlv_length() + 3;
	}

	m->write_track(track_length);
	for (int i = 0; i < 10; i++) {
		m->write_event(events[i]);
	}

	delete m;

	return 0;
}