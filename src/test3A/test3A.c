#include "../frisbee.c"
/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
/*
 * test3A.c
 * Light all LEDs different colors
 *
 *  Author: Vernon
 */ 


int main(void)
{
	int i;
	struct sched_t sched[NUM_LEDS];
	init_microcontroller();
	scheduler_do_startup(sched);
	scheduler_schedule_color(&sched[0], 1, 0, 0);
	if (NUM_LEDS > 1)
		scheduler_schedule_color(&sched[1], 0, 1, 0);
	if (NUM_LEDS > 2)
		scheduler_schedule_color(&sched[2], 0, 0, 1);
	if (NUM_LEDS > 3)
		scheduler_schedule_color(&sched[3], 1, 1, 0);
	if (NUM_LEDS > 4)
		scheduler_schedule_color(&sched[4], 1, 0, 1);
	if (NUM_LEDS > 5)
		scheduler_schedule_color(&sched[5], 0, 1, 1);
	if (NUM_LEDS > 6)
		scheduler_schedule_color(&sched[6], 1, 1, 1);
	for (;;)
	{
		for (i=0; i<400; i++)
			scheduler_run(sched);
		scheduler_rotate_right(sched);
	}
}
