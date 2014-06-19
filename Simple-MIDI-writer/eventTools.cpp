#include <array>
#include "event.h"
#include <iostream>

M_Event::M_Event()
{
	delta_t = 0;
	data = 0;
}

void M_Event::set_values(int _status, int _channel, int _value1, int _value2)
{
	data = (_status & 0x0F) << 20 | \
		(_channel & 0x0F) << 16 | \
		(_value1 & 0xFF) << 8 | \
		(_value2 & 0xFF);
}

void M_Event::set_delta_t(unsigned long _delta_t)
{
	delta_t = _delta_t;
}

void M_Event::get_data(char* _data)
{
	_data[0] = (char)(data >> 16) & 0xFF;
	_data[1] = (char)(data >> 8) & 0xFF;
	_data[2] = (char)(data) & 0xFF;
}

void M_Event::get_vlv(char* _vlv)
{
	int length = get_vlv_length() - 1;

	for (int i = length; i > 0; i--) {
		_vlv[length - i] = (char)(delta_t >> 7 * i & 0x7F) | 0x80; // Continuation bit is set
	}
	_vlv[length] = (char)delta_t & 0x7F;
}

int M_Event::get_vlv_length()
{
	unsigned long _delta_t = delta_t;
	int length = 1;

	while (_delta_t >>= 7) {
		length++;
	}
	return length;
}

unsigned long eventArrayBytes(M_Event* events, int length)
{
	unsigned long track_length = 0;

	for (int i = 0; i < length; i++) {
		track_length += events[i].get_vlv_length() + 3;
	}

	return track_length;
}