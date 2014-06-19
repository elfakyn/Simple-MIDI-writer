#include <stdlib.h>
#include "midi.h"
#include "musicGenerators.h"
#include "musicPrimitives.h"

int main(void)
{
	M_Stream *m = new M_Stream("test.mid");

	m->write_header(M_FORMAT_SYNCHRONOUS, 1, 0x9E78); // 30fps @ 120 ticks/frame
	const unsigned long BASE_TIME = 360;

	int num_events = 0;
	M_Event events[10000];

	m->write_track(0xFFFFFFFF); // just set the maximum chunk size so we won't need to "keep track" of it.. I'll see myself out

	num_events += scaleWalk(events + num_events, 1, 127, 60, BASE_TIME * 4, BASE_TIME, M_PRIM_SCALE_MAJOR, 3, 1, 10, 400, 25);
	for (int i = 0; i < num_events; i++) {
		m->write_event(events[i]);
	}

	m->write_meta_event(M_META_END_OF_TRACK, NULL);
	
	/*
	int numeral = 1;
	int pause_value = 4 * BASE_TIME;
	
	for (int i = 0; i < num_events; i++) {
		m->write_event(events[i]);
	}

	m->write_meta_event(M_META_END_OF_TRACK, NULL);

	m->write_track(0xFFFFFFFF);

	num_events = 0;

	for (int i = 0; i < 20; i += 2) {
		num_events += linearWalk(events + num_events, 1, 127, 20 + 40 * (i % 2), BASE_TIME * 2, BASE_TIME, 2 - 4 * (i % 2), 40);
	}

	for (int i = 0; i < num_events; i++) {
		m->write_event(events[i]);
	}

	m->write_meta_event(M_META_END_OF_TRACK, NULL);

	m->write_track(0xFFFFFFFF);
	num_events = 0;

	for (int i = 1; i < 21; i += 2) {
		num_events += linearWalk(events + num_events, 1, 127, 20 + 40 * (i % 2), BASE_TIME * 2, BASE_TIME, 2 - 4 * (i % 2), 40);
	}

	for (int i = 0; i < num_events; i++) {
		m->write_event(events[i]);
	}
	m->write_meta_event(M_META_END_OF_TRACK, NULL);
	*/

	delete m;

	return 0;
}