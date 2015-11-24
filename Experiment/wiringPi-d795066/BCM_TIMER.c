#include <wiringPi.h>
#include <stdio.h>
#include <errno.h>

int pin1 = 7;
int pin2 = 5;
int pin3 = ;
int pin4 = ;

int step = 0;

void myInterrupt (void)
{
    printf("\n Interrupt Code started Executing \n");
     
    switch step
    {
        case 1 :
            Start_Led_Cycle(pin2);
	    break;
	case 2 :
	    Start_Led_Cycle(pin3);
	    break;
	case 3 :
	    Start_Led_Cycle(pin4);
	    break;
	case 4 :
	    step = 0;
	    Start_Led_Cycle(pin1);
            break;
    }
}

void Start_Led_Cycle (int pin_number)
{
   step++;
   printf("Turning LED %d ON\n",pin_number);
   digitalWrite(pin_number, 1);
   delay(10000);
   printf("Turning LED %d Off\n",pin_number);
   digitalWrite(pin_number, 0);
}

int main (void)
{
    int pin1 = 7;
	
    printf("Raspberry Pi My Stepper motor LED test\n");

    if (wiringPiSetup() == -1)
        return 1;

	
    if (wiringPiISR (pin1, INT_EDGE_FALLING, &myInterrupt) < 0)
    {
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
    }

    if (wiringPiISR (pin2, INT_EDGE_FALLING, &myInterrupt) < 0)
    {  
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
    }

    if (wiringPiISR (pin3, INT_EDGE_FALLING, &myInterrupt) < 0)
    {
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
			    }

    if (wiringPiISR (pin4, INT_EDGE_FALLING, &myInterrupt) < 0)
    {
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
    }			    }
     
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);

    Start_Led_Cycle(pin1);

    return 0;
}
