/*
 * frisbee_runtime1.c
 *
 * Created: 12/4/2012 5:55:44 PM
 *  Author: Vernon
 */ 


#include "../frisbee.c"

#define EPSILON 10

int main(void)
{
	uint8_t adc_value;
	int i;
	struct sched_t sched[NUM_LEDS];
    init_microcontroller();
	int rolling_counter = 0;
	int is_on = 0;
	int value = 0;
	for (;;)
	{
		adc_value = read_ADC();
		if (adc_value < (ADC_ZERO - (EPSILON / 2)) || adc_value > (ADC_ZERO + (EPSILON / 2)))
		{
			switch(rolling_counter)
			{
				case 0:
					scheduler_fill(sched, 1, 0, 0);
					break;
				case 1:
					scheduler_fill(sched, 0, 1, 0);
					break;
				case 2:
					scheduler_fill(sched, 0, 0, 1);
					break;
				case 3:
					if (!is_on)
						schedule_party_mode(sched);
					else
						scheduler_rotate_right(sched);
					break;
				case 4:
					if (value == 0)
					{
						scheduler_fill(sched, 1, 0, 0);
						value++;
					}
					else if (value == 1)
					{
						scheduler_fill(sched, 0, 1, 0);
						value++;
					}
					else if (value == 2)
					{
						scheduler_fill(sched, 0, 0, 1);
						value++;
						value = 0;
					}		
					break;	
				default:
					rolling_counter = 0;
			}
			is_on = 1;
		}
		else
		{
			scheduler_fill(sched, 0, 0, 0);
			if (is_on)
				rolling_counter = (rolling_counter+1) % 5;
			is_on = 0;
		}
		for (i=0; i<60; i++)
			scheduler_run(sched);		
	}
	return 0;
}