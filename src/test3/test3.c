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

/* Test Case 3
 * This tests the RGB LED array (including the RGB coming from the microcontroller,
 * and the decade counter. It does not test the gyroscope.
 * Each LED goes through a specified set of phases:
 * 1) Red
 * 2) Green
 * 3) Blue
 * Each step has a 1s hold time.
 */

int main(void)
{
	int i;
	
	init_microcontroller();
	for (;;)
	{
		row_reset();
		for (i=0; i<NUM_LEDS; i++)
		{
			row_set_color(1, 0, 0);		// set LED red
			_delay_ms(1000);
			row_set_color(0, 1, 0);		// set LED green
			_delay_ms(1000);
			row_set_color(0, 0, 1);		// set LED blue
			_delay_ms(1000);
			row_set_color(0, 0, 0);		// set LED off
			row_advance();
		}
		row_reset();
	}
	return;
}

