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

/* Test Case 4
 * Combination of gyroscope and LEDs
 * Uses the scheduler for LED state
 * At rest: all LEDs are green
 * Spin Counter-Clockwise: LEDs light blue, starting with LED 0.
 *		The greater the angular velocity, the more LEDs are blue.
 * Spin Clockwise: Same pattern as CCW, except use red instead of green.
 */

#define EPSILON 10

int main(void)
{
	int i, j;
	uint16_t value;
	uint8_t adc_value;  //variable store value from conversion
	struct sched_t sched[NUM_LEDS];
	init_microcontroller();
	for (;;)
	{
		adc_value = read_ADC();
		//if (adc_value > 155)
		if (adc_value > ADC_ZERO + (EPSILON / 2))
		{
			// light blue radially from center
			scheduler_fill(sched, 0, 1, 0);
			scheduler_schedule_color(&sched[0], 0, 0, 1);
			value = ADC_ZERO + EPSILON;
			for (i=1; i<NUM_LEDS && value < 256; i++)
			{
				if (adc_value > value)
					scheduler_schedule_color(&sched[i], 0, 0, 1);
				else
					break;
				value += 10;
			}			
		}			
		else if (adc_value < ADC_ZERO - (EPSILON / 2))
		{
			// light red radially from center
			scheduler_fill(sched, 0, 1, 0);
			scheduler_schedule_color(&sched[0], 1, 0, 0);
			value = ADC_ZERO - EPSILON;
			for (i=1; i<NUM_LEDS && value >= 0; i++)
			{
				if (adc_value < value)
					scheduler_schedule_color(&sched[i], 1, 0, 0);
				else
					break;
				value -= 10;
			}			
		}								
		else
		{
			// at rest. light all green
			scheduler_fill(sched, 0, 1, 0);
		}			
		
		for (i=0; i<10; i++)
			scheduler_run(sched);
	}
	
	return 0;
}
