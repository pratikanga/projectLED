#include <wiringPi.h>
#include <stdio.h>
#include <errno.h>

int pin2 = 5;

void myInterrupt (void)
{
	printf("\n Interrupt Code started Executing \n");
    printf("Interrupt : LED On\n");
    digitalWrite(pin2, 1);
    delay(2000);
    printf("Interrupt : LED Off\n");
    digitalWrite(pin2, 0);
  //  delay(1000);

}


int main (void)
{
    int pin1 = 7;
	
    printf("Raspberry Pi wiringPi blink test\n");

    if (wiringPiSetup() == -1)
        return 1;

//   pinMode(pin2, OUTPUT);
// pinMode(pin1, OUTPUT);
	
    if (wiringPiISR (pin1, INT_EDGE_FALLING, &myInterrupt) < 0)
    {
        fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
        return 1 ;
    }
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    for (;;)
	{
        printf("LED On\n");
        digitalWrite(pin1, 1);
        delay(2000);
        printf("LED Off\n");
        digitalWrite(pin1, 0);
        delay(2000);
    }
  return 0;
}
