#include <iostream>
#include "midi.h"
#include "musicGenerators.h"

using std::cout;

int main(void)
{
	M_Stream *m = new M_Stream("test.mid");

	m->write_header(M_FORMAT_SYNCHRONOUS, 2, 0x9E78); // 30fps @ 120 ticks/frame
	const unsigned long BASE_TIME = 9600;

	int num_events = 0;
	M_Event events[10000];

	m->write_track(0xFFFFFFFF); // just set the maximum chunk size so we won't need to "keep track" of it.. I'll see myself out

	num_events += chord(events + num_events, 1, 127, 60, BASE_TIME * 3, BASE_TIME, M_GEN_CHORD_MAJOR);
	num_events += chord(events + num_events, 1, 127, 60, BASE_TIME * 3, BASE_TIME, M_GEN_CHORD_MINOR);
	num_events += chord(events + num_events, 1, 127, 60, BASE_TIME * 3, BASE_TIME, M_GEN_CHORD_AUGMENTED);
	num_events += chord(events + num_events, 1, 127, 60, BASE_TIME * 3, BASE_TIME, M_GEN_CHORD_DIMINISHED);
	
	for (int i = 0; i < num_events; i++) {
		m->write_event(events[i]);
	}
	delete m;

	return 0;
}