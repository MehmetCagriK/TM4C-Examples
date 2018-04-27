/**
  This program toggles the onboard red LED each second.
*/
#include "TM4C123.h"                    // Device header

void delay_millisecond(uint32_t time);

int main()
{
  SYSCTL->RCGCGPIO |= 0x20;     // Unlock clock for Port F
  GPIOF->DIR = 0x02;            // Set PF1(RED) LED pin as output
  GPIOF->DEN = 0x02;            // Digital Enable PF1(RED) LED
  
  while(1)
  {
    delay_millisecond(1000U);   // Wait 1 sec
    GPIOF->DATA ^= 0x02;        // Toggle output value of PF1(RED LED)
  }
}

void delay_millisecond(uint32_t time)
{
  /**
    Waits for a time*milliseconds delay.
    First, Timer 1/A is configured for 1 millisecond delay operation.
    Then delay is waited, and clock is disabled again. Delay is controlled
    by polling Raw Interrupt Status register. 

    @param time number of milliseconds to wait
    @return void
  */
  SYSCTL->RCGCTIMER |= 0x02;    // Enable and provide a clock to TIMER1
  TIMER1->CTL = 0x00;           // Timer 1-A is disabled.
  TIMER1->CFG = 0x04;           // Select 16 bit timer
  TIMER1->TAMR = 0x2;           // Set periodic timer mode
  TIMER1->TAILR = 16000U - 1;   // 0 to 15 = 16 ticks for 1 microsecond
  TIMER1->ICR = 0x1;            // Clear interrupts from TIMER1(Unnecessary here?)
  TIMER1->CTL = 0x01;           // Timer 1-A enabled
  
  for(int i = 0;i < time; i++){ // Spin as many milliseconds delay as desired
    while((TIMER1->RIS & 0x1) == 0x00); // Check raw interrupt status for timer timeout
    TIMER1->ICR = 0x1;          // Clear Timer 1-A interrupt every 16 ticks if timeout occurred
  }
  
  TIMER1->CTL = 0x00;           // Timer 1-A is disabled.
  SYSCTL->RCGCTIMER &= ~0x02;   // Disable and provide a clock to TIMER1
}
