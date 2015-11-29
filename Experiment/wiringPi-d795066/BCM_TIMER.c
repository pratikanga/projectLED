#include <wiringPi.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int pin1 = 7; // GPIO-04 and pin-7
int pin2 = 5; // GPIO-24 and pin-18
int pin3 = 1; // GPIO-18 and pin-12
int pin4 = 4; // GPIO-23 and pin-16

static int step = 0;
void Start_Led_Cycle(int , int );
int timer = 10000;

/*
void myInterrupt (void)
{
    step++;
    printf("\n Interrupt Code started Executing %d \n",step);
     
    switch (step)
    {
        case 1 :
            print("\n In Case 1 : Step : %d Pin 18 is turning on \n",step);
            Start_Led_Cycle(pin2);
	    break;
	case 2 :
            print("\n In Case 2 : Step : %d Pin 12 is turning on \n",step);
            Start_Led_Cycle(pin3);
	    break;
	case 3 :
            print("\n In Case 3 : Step : %d Pin 16 is turning on \n",step);
            Start_Led_Cycle(pin4);
	    break;
	case 4 :
            print("\n In Case 4 : Step : %d Pin 7 is turning on \n",step);
            step = 0;
	    Start_Led_Cycle(pin1);
            break;
        default :
	    printf("\nSomething Wrong");
    }
}
*/

void myInterrupt1( void )
{
     step++;
     printf("\n In Case 1 : Step : %d Pin 18 is turning on \n",step);
     if(digitalRead(pin1)) 
     {
         printf("\n START : CASE 1\n");
         Start_Led_Cycle(pin2, timer);
	 printf("\n END : CASE 1\n");
     }
     else
     {
         printf("\n Case 1 : Previos Pin is still On \n");
     }
}


void myInterrupt2(void)
{
     step++;
     printf("\n In Case 2 : Step : %d Pin 12 is turning on \n",step);

     if(digitalRead(pin2))
     {
         printf("\n START : CASE 2\n");
         Start_Led_Cycle(pin3, timer);
         printf("\n END : CASE 2\n");
     }
     else 
     {
         printf("\n Case 2 : Previous Pin is Still On \n");
     }
}

void myInterrupt3(void)
{
     step++;
     printf("\n In Case 3 : Step : %d Pin 16 is turning on \n",step);
     if(digitalRead(pin3))
     {
         printf("\n START : CASE 3\n");
         Start_Led_Cycle(pin4, timer);
         printf("\n END : CASE 3");
     }
     else
     {
         printf("\n Case 3 : Previous pin is still ON \n");
     }
}

void myInterrupt4(void)
{
     step = 0;
     printf("\n In Case 4 : Step : %d Pin 7 is turning on \n",step);

     if(digitalRead(pin4))
     {
         printf("\n START : CASE 4\n");
         Start_Led_Cycle(pin1, timer);
	 printf("\n END : CASE 4\n");
     }
     else
     {
         printf("\n Case 4 : Previous pin is Still On \n");
     }
}

void Start_Led_Cycle (int pin_number, int delay1)
{
   pinMode(pin_number, OUTPUT);
   printf("Turning LED %d ON delay %d\n",pin_number,delay1);
   digitalWrite(pin_number, 1);
   delay(delay1);
   printf("Turning LED %d Off\n",pin_number);
   digitalWrite(pin_number, 0);
}

int main (void)
{
    printf("Raspberry Pi My Stepper motor LED test\n");

    if (wiringPiSetup() == -1)
        return 1;

	
    if (wiringPiISR (pin1, INT_EDGE_FALLING, &myInterrupt1) < 0)
    {
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
    }

    if (wiringPiISR (pin2, INT_EDGE_FALLING, &myInterrupt2) < 0)
    {  
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
    }

    if (wiringPiISR (pin3, INT_EDGE_FALLING, &myInterrupt3) < 0)
    {
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
    }

    if (wiringPiISR (pin4, INT_EDGE_FALLING, &myInterrupt4) < 0)
    {
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
    }	
     
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);

    Start_Led_Cycle(pin1);

    while(1){}

    return 0;
}
