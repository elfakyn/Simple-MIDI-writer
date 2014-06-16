#include <array>
#include "event.h"

M_Event::M_Event()
{
	delta_t = 0;
	data = 0;
}

void M_Event::set_values(int _status, int _channel, int _value1, int _value2)
{
	data = _status << 20 & 0xF00000 | \
		_channel << 16 & 0x0F0000 | \
		_value1 << 8 & 0x00FF00 | \
		_value2 & 0x0000FF;
}

void M_Event::set_delta_t(unsigned long _delta_t)
{
	delta_t = _delta_t;
}

void M_Event::get_data(char* _data)
{
	_data[0] = data >> 16 & 0xFF;
	_data[1] = data >> 8 & 0xFF;
	_data[2] = data & 0xFF;
}

void M_Event::get_vlv(char* _vlv)
{
	int length = get_vlv_length();

	while (length--) {
		_vlv[length] = data >> 7 * length & 0x7F | 0x80; // Continuation bit is set
	}
	_vlv[0] = data & 0x7F;
}

int M_Event::get_vlv_length()
{
	unsigned long _data = data;
	int length = 0;

	while (_data) {
		length++;
		_data = _data >> 7;
	}

	return length;
}