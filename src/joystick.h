#ifndef __joystick_h__
#define __joystick_h__

#include <inttypes.h>

struct Joystick;
typedef struct Joystick Joystick;

Joystick* joystick_create();
void joystick_free(Joystick* js);
void joystick_set_button(Joystick* js, uint8_t btn, uint8_t down);
void joystick_set_x(Joystick* js, uint16_t value);
uint16_t joystick_get_x(Joystick* js);
void joystick_set_y(Joystick* js, uint16_t value);
uint16_t joystick_get_y(Joystick* js);
void joystick_set_z(Joystick* js, uint16_t value);
uint16_t joystick_get_z(Joystick* js);
void joystick_set_rx(Joystick* js, uint16_t value);
uint16_t joystick_get_rx(Joystick* js);
void joystick_set_ry(Joystick* js, uint16_t value);
uint16_t joystick_get_ry(Joystick* js);
void joystick_set_rz(Joystick* js, uint16_t value);
uint16_t joystick_get_rz(Joystick* js);
void joystick_set_s1(Joystick* js, uint16_t value);
uint16_t joystick_get_s1(Joystick* js);
void joystick_set_s2(Joystick* js, uint16_t value);
uint16_t joystick_get_s2(Joystick* js);

#endif // __joystick_h__
