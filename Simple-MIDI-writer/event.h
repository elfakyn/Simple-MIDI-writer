#ifndef EVENT_H
#define EVENT_H

#define M_NOTE_OFF           0x8
#define M_NOTE_ON            0x9
#define M_NOTE_AFTERTOUCH    0xA
#define M_CONTROLLER         0xB
#define M_PROGRAM_CHANGE     0xC
#define M_CHANNEL_AFTERTOUCH 0xD
#define M_PITCH_BEND         0xE

class M_Event {
private:
	unsigned long delta_t; // up to 4 bytes as per MIDI specification
	unsigned long data; // 3 bytes

public:
	M_Event();

	void set_values(int status, int channel, int value1, int value2);
	void set_delta_t(unsigned long delta_t);

	void get_data(char* data);
	void get_vlv(char* vlv); // Variable length value of delta_t, up to 5 bytes
	int get_vlv_length();
};

#endif