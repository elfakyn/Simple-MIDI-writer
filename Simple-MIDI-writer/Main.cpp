#include <stdlib.h>
#include "midi.h"
#include "musicGenerators.h"
#include "musicPrimitives.h"

void writeTrack(M_Stream* m, M_Event* events, int num_events)
{
	m->write_track(0xFFFFFFFF);
	for (int i = 0; i < num_events; i++) {
		m->write_event(events[i]);
	}
	m->write_meta_event(M_META_END_OF_TRACK, NULL);
}

int main(void)
{
	M_Stream *m = new M_Stream("test.mid");
	m->write_header(M_FORMAT_SYNCHRONOUS, 3, 0x9E78); // 30fps @ 120 ticks/frame
	
	const unsigned long BASE_TIME = 480;
	
	int num_events = 0;
	M_Event events[10000];

	num_events += scaleWalk(events, 1, 110, 60, BASE_TIME * 5, BASE_TIME, M_PRIM_SCALE_MAJOR, 3, 1, 10, 400, 25, 1);
	writeTrack(m, events, num_events);

	num_events = 0;
	num_events += chordWalk(events, 1, 127, 51, BASE_TIME * 30, BASE_TIME * 6, M_PRIM_SCALE_MINOR, 2, -5, 10, 200, 33, 3);
	writeTrack(m, events, num_events);
	
	

	delete m;
	return 0;
}