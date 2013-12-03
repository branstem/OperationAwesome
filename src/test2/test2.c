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

/* Test Case 2
 * Turn on LED, or Blink LED
 */

int main(void)
{
	struct sched_t sched[NUM_LEDS];
	init_microcontroller();
	clearbit(PORTA, LED_RED);
	//scheduler_fill(sched, 0, 0, 1);
	for (;;)
	{
		//scheduler_run(sched);
		
		/*
		setbit(PORTA, PA0);
		_delay_ms(1000);	
		clearbit(PORTA, PA0);
		_delay_ms(1000);	
		*/
	}		
	return 0;
}
