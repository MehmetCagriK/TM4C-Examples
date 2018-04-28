### Description
This program is written to show timer with interrupt example on TM4C123GXL.
Onboard red LED is toggled each second.Timer 1 is used as 32 bit periodic 
timer. 

In 32 bit mode, both A and B timers are **concatenated**(both are 16 bit timers
themselves) to make 32 bit timer. As you can see, when Timer A and Timer B are
concatenated, configuration is still done on Timer A(TAMR and TAILR register 
configurations). Also, interrupt handling done through Timer A's function.

In periodic timer mode, once timer "revolves enough cycles" according to the 
value written into load register(TAILR), it restarts again. In one shot mode
however, timer stops after one period. You can write 0x01 to TAMR register for
one shot timer mode and see the difference.  

### What to Know
For general knowledge about TM4C timers, please read the section **11. General
Purpose Timers** and especially section **11.4 Initialization and Configuration**