#include <iostream>
#include "midi.h"
#include "musicGenerators.h"

using std::cout;

int main(void)
{
	M_Stream *m = new M_Stream("test.mid");

	m->write_header(M_FORMAT_SINGLE_TRACK, 1, 0x9E78); // 30fps @ 120 ticks/frame
	const unsigned long BASE_TIME = 2400;

	M_Event events[10000];
	int num_events = 0;

	num_events += linearWalk(events, 1, 127, 40, 1, 40, BASE_TIME * 4, BASE_TIME);
	int track_length = eventArrayBytes(events, num_events);

	m->write_track(track_length);
	for (int i = 0; i < num_events; i++) {
		m->write_event(events[i]);
	}
	/*
	num_events = 0;

	num_events += linearWalk(events + num_events, 1, 127, 80, -1, 60, BASE_TIME * 2, BASE_TIME);
	track_length = eventArrayBytes(events, num_events);

	m->write_track(track_length);
	for (int i = 0; i < num_events; i++) {
		m->write_event(events[i]);
	}*/

	delete m;

	return 0;
}