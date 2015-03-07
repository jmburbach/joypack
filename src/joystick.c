#include <string.h>
#include <stdlib.h>

#include "joystick.h"


/* 32 buttons and 8 axis */
struct Joystick {
	uint32_t buttons;
	uint8_t absdata[10];
};


static void pack_abs_0(uint8_t* data, uint16_t value)
{
	if (value > 1023)
		value = 1023;

	data[0] = value & 0xff;
	data[1] = (data[1] & 0xfc) | (value >> 8);
}


static uint16_t unpack_abs_0(uint8_t* data)
{
	uint16_t value;
	value = (data[0] | ((data[1] & 0x3) << 8));
	return value;
}


static void pack_abs_1(uint8_t* data, uint16_t value)
{	
	if (value > 1023)
		value = 1023;
 
	data[1] = (data[1] & 0x3) | (value << 2);
	data[2] = (data[2] & 0xf0) | (value >> 6);
}


static uint16_t unpack_abs_1(uint8_t* data)
{
	uint16_t value;
	value = (data[1] >> 2) | ((data[2] & 0xf) << 6);
	return value;
}


static void pack_abs_2(uint8_t* data, uint16_t value)
{
	if (value > 1023)
		value = 1023;

	data[2] = (data[2] & 0xf) | (value << 4);
	data[3] = (data[3] & 0xc0) | (value >> 4);
}


static uint16_t unpack_abs_2(uint8_t* data)
{
	uint16_t value;
	value = (data[2] >> 4) | ((data[3] & 0x3f) << 4);
	return value;
}


static void pack_abs_3(uint8_t* data, uint16_t value)
{
	if (value > 1023)
		value = 1023;

	data[3] = (data[3] & 0x3f) | (value << 6);
	data[4] = (value >> 2);
}


static uint16_t unpack_abs_3(uint8_t* data)
{
	uint16_t value;
	value = (data[3] >> 6) | (data[4] << 2);
	return value;
}


Joystick* joystick_create()
{
	Joystick* js;
	js = (Joystick*)malloc(sizeof(Joystick));
	memset(js, 0, sizeof(Joystick));
	return js;
}


void joystick_free(Joystick* js)
{
	free(js);
}


void joystick_set_button(Joystick* js, uint8_t btn, uint8_t down)
{
	if (--btn >= 32)
		return;

	if (down) {
		js->buttons &= (1 << btn);
	}
	else {
		js->buttons &= ~(1 << btn);
	}
}


void joystick_set_x(Joystick* js, uint16_t value)
{
	pack_abs_0(js->absdata, value);
}


uint16_t joystick_get_x(Joystick* js)
{
	return unpack_abs_0(js->absdata);
}


void joystick_set_y(Joystick* js, uint16_t value)
{
	pack_abs_1(js->absdata, value);
}


uint16_t joystick_get_y(Joystick* js)
{
	return unpack_abs_1(js->absdata);
}


void joystick_set_z(Joystick* js, uint16_t value)
{
	pack_abs_2(js->absdata, value);
}


uint16_t joystick_get_z(Joystick* js)
{
	return unpack_abs_2(js->absdata);
}


void joystick_set_rx(Joystick* js, uint16_t value)
{
	pack_abs_3(js->absdata, value);
}


uint16_t joystick_get_rx(Joystick* js)
{
	return unpack_abs_3(js->absdata);
}


void joystick_set_ry(Joystick* js, uint16_t value)
{
	pack_abs_0(js->absdata + 5, value);
}


uint16_t joystick_get_ry(Joystick* js)
{
	return unpack_abs_0(js->absdata + 5);
}


void joystick_set_rz(Joystick* js, uint16_t value)
{
	pack_abs_1(js->absdata + 5, value);
}


uint16_t joystick_get_rz(Joystick* js)
{
	return unpack_abs_1(js->absdata + 5);
}


void joystick_set_s1(Joystick* js, uint16_t value)
{
	pack_abs_2(js->absdata + 5, value);
}


uint16_t joystick_get_s1(Joystick* js)
{
	return unpack_abs_2(js->absdata + 5);
}


void joystick_set_s2(Joystick* js, uint16_t value)
{
	pack_abs_3(js->absdata + 5, value);
}


uint16_t joystick_get_s2(Joystick* js)
{
	return unpack_abs_3(js->absdata + 5);
}
