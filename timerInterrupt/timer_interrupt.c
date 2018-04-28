#include "TM4C123.h"                    // Device header
int count = 0;
void setup_1sec_timer(void);
void TIMER1A_Handler(void);

int main()
{
  SYSCTL->RCGCGPIO |= 0x20;     // Unlock clock for Port F
  GPIOF->DIR = 0x02;            // Set PF1(RED) LED pin as output
  GPIOF->DEN = 0x02;            // Digital Enable PF1(RED) LED
  
  setup_1sec_timer();           // Setup 1 sec timer
  while(1){                     // Loop continuously to prevent early exit
  count = TIMER1->TAR;          // Actual timer value is stored in this register
  }            
}

void setup_1sec_timer(void)
{
   /**
    In this function, Timer 1 is used as concatenated 32 bit timer.
    Timer 1 is also configured to send interrupt each second.
    Also, timer runs at the background continuously, as you can see
    it is not stopped(CTL) or disabled(RCGCTIMER)
    @return void
  */
  SYSCTL->RCGCTIMER |= 0x02;    // Enable and provide a clock to TIMER1
  TIMER1->CTL = 0x00;           // Timer 1-A is stopped.
  TIMER1->CFG = 0x00;           // Select 32 bit timer mode(Timers A/B together)
  TIMER1->TAMR = 0x02;          // Set periodic timer mode
  TIMER1->TAILR = 0x00F42400U;  // Count up to 16M for 1 sec delay
  TIMER1->IMR = 0x01;           // Enable Timer 1-A time-out interrupt
  NVIC->ISER[0] = (1<<21);      // Enable Timer 1-A Interrupt Service
  TIMER1->CTL = 0x01;           // Timer 1-A started           
}

void TIMER1A_Handler(void){
  /**
    This handler method is written to handle the interrupt that will
    be sent from Timer 1-A. In this case, it is periodic(1 sec) interupt.
    Interrupt is cleared first, then LED is toggled. Interrupt Service
    Routine functions should be short.
    
    @return void
  */
  TIMER1->ICR = 0x01;           // Acknowledge Interrupt
  GPIOF->DATA ^= 0x02;          // Toggle output value of PF1(RED LED)
}
