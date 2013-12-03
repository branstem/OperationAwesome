/*
 * frisbee.c
 *
 * Created: 10/12/2012 5:40:17 PM
 *  Author: Matthew, Vernon
 *
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


#include "frisbee.h"


void row_advance(void)
{
	// Advance to the next row
	setbit(PORTA, ROWSTROBE);
	_delay_us(10);
	//for (i=0; i<10; i++);
	clearbit(PORTA, ROWSTROBE);
}

void row_reset(void)
{
	// Reset to the first row
	setbit(PORTA, ROWRESET);
	//for (i=0; i<10; i++);
	_delay_us(10);
	clearbit(PORTA, ROWRESET);
}

void row_set_color (int red, int green, int blue)
{
	// Set the row color
	if (!PROTOTYPE)
	{
		red = !red;
		green = !green;
		blue = !blue;
	}
	if (red)
		clearbit(PORTA, LED_RED);
	else
		setbit(PORTA, LED_RED);

	// GREEN
	if (green)
		clearbit(PORTA, LED_GREEN);
	else
		setbit(PORTA, LED_GREEN);

	// BLUE
	if (blue)
		clearbit(PORTA, LED_BLUE);
	else
		setbit(PORTA, LED_BLUE);
	return;
}


void scheduler_run(struct sched_t sched[NUM_LEDS])
{
	int i;
	row_reset();
	for (i=0; i<NUM_LEDS; i++)
	{
		row_set_color(sched[i].red, sched[i].green, sched[i].blue);
		//row_set_color(1, 0, 0);
		_delay_us(200);
		//_delay_ms(1);
		//_delay_ms(1000);
		row_set_color(0, 0, 0);
		row_advance();
	}
	row_reset();
	
	return;
}

void scheduler_schedule_color(struct sched_t *sched, int red, int green, int blue)
{
	sched->red = red;
	sched->green = green;
	sched->blue = blue;
	
	return;
}

void scheduler_fill(struct sched_t sched[NUM_LEDS], int red, int green, int blue)
{
	int i;
	for (i=0; i<NUM_LEDS; i++)
		scheduler_schedule_color(&sched[i], red, green, blue);
		
	return;
}

void scheduler_rotate_left(struct sched_t sched[NUM_LEDS])
{
	int i, nexti;
	struct sched_t held_sched;
	scheduler_schedule_color(&held_sched, sched[NUM_LEDS-1].red, sched[NUM_LEDS-1].green, sched[NUM_LEDS-1].blue);
	for (i=NUM_LEDS-1; i>=0; i--)
	{
		nexti = (i-1) % NUM_LEDS;
		scheduler_schedule_color(&sched[i], sched[nexti].red, sched[nexti].green, sched[nexti].blue);
	}
	scheduler_schedule_color(&sched[0], held_sched.red, held_sched.green, held_sched.blue);
	return;
}

void scheduler_rotate_right(struct sched_t sched[NUM_LEDS])
{
	int i, nexti;
	struct sched_t held_sched;
	scheduler_schedule_color(&held_sched, sched[0].red, sched[0].green, sched[0].blue);
	for (i=0; i<NUM_LEDS; i++)
	{
		nexti = (i+1) % NUM_LEDS;
		scheduler_schedule_color(&sched[i], sched[nexti].red, sched[nexti].green, sched[nexti].blue);
	}
	scheduler_schedule_color(&sched[NUM_LEDS-1], held_sched.red, held_sched.green, held_sched.blue);
	return;
}

void scheduler_do_startup(struct sched_t sched[NUM_LEDS])
{
	int i, j;
	scheduler_fill(sched, 0, 0, 0);
	scheduler_schedule_color(&sched[0], 0, 1, 0);
	for (i=0; i<NUM_LEDS-1; i++)
	{
		for (j=0; j<60; j++)
			scheduler_run(sched);
		scheduler_rotate_left(sched);
	}
	for (i=0; i<NUM_LEDS; i++)
	{
		for (j=0; j<60; j++)
			scheduler_run(sched);
			
		scheduler_rotate_right(sched);
	}
	return;
}


void schedule_party_mode(struct sched_t sched[NUM_LEDS])
{
	int color = 0;
	int i;
	for (i=0; i<NUM_LEDS; i++)
	{
		switch (color)
		{
			case 0:
				scheduler_schedule_color(&sched[i], 1, 0, 0);
				break;
			case 1:
				scheduler_schedule_color(&sched[i], 0, 1, 0);
				break;
			case 2:
				scheduler_schedule_color(&sched[i], 0, 0, 1);
				break;
			default:
				scheduler_schedule_color(&sched[i], 1, 1, 1);
		}
		color = (color + 1) % 3;
	}
	return;
}
int init_microcontroller(void)
{
	init_ports();				// setup the ports
	init_ADC();					// setup the Analog Converter
	
	return 0;
}

void init_ports(void)
{
   setbit(DDRA, PA0);	// Set as output (LED_RED)
   setbit(DDRA, PA1);	// Set as output (LED_GREEN)
   setbit(DDRA, PA2);	// Set as output (LED_BLUE)
   clearbit(DDRA, PA3);	// Set as input AREF
   clearbit(DDRA, PA4);	// Set as input (ADC3)
   setbit(DDRA, PA5);	// Set as output (ROWSTROBE)
   setbit(DDRA, PA6);	// Set as output (ROWRESET)
   setbit(DDRA, PA7);	// Set as output 
   setbit(PORTA, PA7);
}

void init_ADC(void)
{
   setbit(ADCSRB, REFS2);	// Set voltage reference to internal 2.56V
   setbit(ADMUX, REFS1);	// Set voltage reference to internal 2.56V
   //clearbit(ADMUX, REFS1);	// Set voltage reference to internal 3.3V
   clearbit(ADMUX, REFS0);	// Set voltage reference to internal 2.56V 
   
   setbit(ADMUX, ADLAR);	// Left adjust ADC result to allow easy 8 bit reading
   
   //Using Single Conversion this code not needed
   //setbit(ADCSRA, ADATE);	// Set ADD to Auto Trigger enabled for free running
   
   setbit(ADCSRA, ADPS2);	// Set ADC pre-scalar to 64 (8 MHZ / 64 = 125 KHZ)
   setbit(ADCSRA, ADPS1);	// Set ADC pre-scalar to 64 (8 MHZ / 64 = 125 KHZ)
   clearbit(ADCSRA, ADPS0);	// Set ADC pre-scalar to 64 (8 MHZ / 64 = 125 KHZ)
   
   // clear junk out (do an initial read off ADC)
   clearbit(ADMUX, MUX4);	// Select channel ADC3
   clearbit(ADMUX, MUX3);	// Select channel ADC3
   clearbit(ADMUX, MUX2);	// Select channel ADC3
   setbit(ADMUX, MUX1);		// Select channel ADC3
   setbit(ADMUX, MUX0);		// Select channel ADC3
   
   setbit(ADCSRA, ADEN);	// Enable ADC
   setbit(ADCSRA, ADSC);	// Start AD Conversions
}


uint8_t read_ADC(void)
{
	clearbit(ADMUX, MUX4);			// Select channel ADC3
	clearbit(ADMUX, MUX3);			// Select channel ADC3
	clearbit(ADMUX, MUX2);			// Select channel ADC3
	setbit(ADMUX, MUX1);			// Select channel ADC3
	setbit(ADMUX, MUX0);			// Select channel ADC3
	
	setbit(ADCSRA, ADSC);			// Start AD Conversions
	while(!(ADCSRA & (1<<ADIF)));	// Wait for conversion to complete
	setbit(ADCSRA, ADIF);			// Set flag AD conversion complete
	return ADCH;					// Return the 8 bit value
}
