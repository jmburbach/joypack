#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>
#include <assert.h>

#include "joystick.h"


int random_int(int imin, int imax)
{
	struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);

    int a = imin, b = imax;

    int val = a + (b-a) * (double)rand() / (double)RAND_MAX + 0.5;

    return val;
}


typedef void (*axis_setter_func)(Joystick*, uint16_t);
typedef uint16_t (*axis_getter_func)(Joystick*);

typedef struct Axis {
	axis_setter_func set;
	axis_getter_func get;
} Axis;


void shuffle_axis(Axis* axes, size_t n)
{
	size_t i,j;
	Axis tmp;

	for (i = 0; i < n - 1; ++i) {
		j = random_int(0, n-1);
		tmp = axes[j];
		axes[j] = axes[i];
		axes[i] = tmp;
	}
}

/* 
 * Randomly set all axis values and then check correct values returned
 * from getter. Tests that the packing code is not inadvertently stepping
 * on neighboring bits.
 */
int main()
{
	int i,j;
	Joystick* js;
	int values[8];
	Axis axes[8] = {
		{joystick_set_x, joystick_get_x},
		{joystick_set_y, joystick_get_y},
		{joystick_set_z, joystick_get_z},
		{joystick_set_rx, joystick_get_rx},
		{joystick_set_ry, joystick_get_ry},
		{joystick_set_rz, joystick_get_rz},
		{joystick_set_s1, joystick_get_s1},
		{joystick_set_s2, joystick_get_s2}
	};

	js = joystick_create();

	for (i=0; i < 1000000; ++i) {
		shuffle_axis(axes, 8);

		for (j=0; j<8; ++j) {
			values[j] = random_int(0, 1023);
			axes[j].set(js, values[j]);
		}

		for (j=0; j<8; ++j) {
			assert(axes[j].get(js) == values[j]);
		}
	}

	joystick_free(js); js=NULL;

	return 0;
}
                                                                

/*
[X|X|X|X|X|X|X|X] B0

[Y|Y|Y|Y|Y|Y|X|X] B1

[Z|Z|Z|Z|Y|Y|Y|Y] B2
 
[RX|RX|Z|Z|Z|Z|Z|Z] B3

[RX|RX|RX|RX|RX|RX|RX|RX] B4
*/
