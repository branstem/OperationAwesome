<<<<<<< HEAD
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

#define __AVR_ATtiny461__
#include <avr/io.h>
#include <util/delay.h>


#define NUM_LEDS	10	// Number of LEDs in the matrix
#define ADC_ZERO	150	// Value ADC gives when gyroscope is at rest

#define setbit(a, b) (a) |= (1 << (b))
#define clearbit(a, b) (a) &= ~(1 << (b))


#define ROWSTROBE 	PA5	// advance decade counter
#define ROWRESET 	PA6	// reset decade counter

#define LED_BLUE 	PA0	// Output port for blue on LED
#define LED_GREEN 	PA2	// Output port for green on LED
#define LED_RED 	PA1	// Output port for red on LED

#define PROTOTYPE	0	// account for differences between prototype and final board

struct sched_t
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;	
};

void scheduler_run(struct sched_t sched[NUM_LEDS]);
void scheduler_schedule_color(struct sched_t *sched, int red, int green, int blue);
void scheduler_fill(struct sched_t sched[NUM_LEDS], int red, int green, int blue);
void row_advance(void);
void row_reset(void);
void row_set_color (int red, int green, int blue);
void scheduler_rotate_left(struct sched_t sched[NUM_LEDS]);
void scheduler_rotate_right(struct sched_t sched[NUM_LEDS]);
void scheduler_do_startup(struct sched_t sched[NUM_LEDS]);
void schedule_party_mode(struct sched_t sched[NUM_LEDS]);
int init_microcontroller(void);
void init_ports(void);
void init_ADC(void);
uint8_t read_ADC(void);	// Single conversion read

=======
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

#define __AVR_ATtiny461__
#include <avr/io.h>
#include <util/delay.h>


#define NUM_LEDS	3	// Number of LEDs in the matrix
#define ADC_ZERO	150	// Value ADC gives when gyroscope is at rest

#define setbit(a, b) (a) |= (1 << (b))
#define clearbit(a, b) (a) &= ~(1 << (b))


#define ROWSTROBE 	PA5	// advance decade counter
#define ROWRESET 	PA6	// reset decade counter

#define LED_BLUE 	PA2	// Output port for blue on LED
#define LED_GREEN 	PA1	// Output port for green on LED
#define LED_RED 	PA0	// Output port for red on LED

struct sched_t
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;	
};

void scheduler_run(struct sched_t sched[NUM_LEDS]);
void scheduler_schedule_color(struct sched_t *sched, int red, int green, int blue);
void scheduler_fill(struct sched_t sched[NUM_LEDS], int red, int green, int blue);
void row_advance(void);
void row_reset(void);
void row_set_color (int red, int green, int blue);
void scheduler_rotate_left(struct sched_t sched[NUM_LEDS]);
void scheduler_rotate_right(struct sched_t sched[NUM_LEDS]);
void scheduler_do_startup(struct sched_t sched[NUM_LEDS]);
int init_microcontroller(void);
void init_ports(void);
void init_ADC(void);
uint8_t read_ADC(void);	// Single conversion read

>>>>>>> 8cad91cf0d7da6f5b4824872de31216d80ebe9ae
