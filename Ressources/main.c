#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2
#define LED4 LATDbits.LATD3
#define LED5 LATDbits.LATD4
#define LED6 LATDbits.LATD5
#define LED7 LATDbits.LATD6
#define LED8 LATDbits.LATD7

#define DIR_LED1 TRISDbits.TRISD0
#define DIR_LED2 TRISDbits.TRISD1
#define DIR_LED3 TRISDbits.TRISD2
#define DIR_LED4 TRISDbits.TRISD3
#define DIR_LED5 TRISDbits.TRISD4
#define DIR_LED6 TRISDbits.TRISD5
#define DIR_LED7 TRISDbits.TRISD6
#define DIR_LED8 TRISDbits.TRISD7

void init_leds();
void delay_approx();
const int delay_cycles = 500; // Nb of delay cycles

void main(void) {
    init_leds();
    while (1) {
        LED1 = 0;
        LED2 = 0;
        LED3 = 0;
        LED4 = 0;
        LED5 = 1;
        LED6 = 1;
        LED7 = 1;
        LED8 = 1;
        delay_approx(); // wait
        LED1 = 1;
        LED2 = 1;
        LED3 = 1;
        LED4 = 1;
        LED5 = 0;
        LED6 = 0;
        LED7 = 0;
        LED8 = 0;
        delay_approx(); // wait
    }
}

void init_leds() {
    DIR_LED1 = 0;
    LED1 = 0;
    DIR_LED2 = 0;
    LED2 = 0;
    DIR_LED3 = 0;
    LED3 = 0;
    DIR_LED4 = 0;
    LED4 = 0;
    DIR_LED5 = 0;
    LED5 = 0;
    DIR_LED6 = 0;
    LED6 = 0;
    DIR_LED7 = 0;
    LED7 = 0;
    DIR_LED8 = 0;
    LED8 = 0;
}

void delay_approx() {
    for (int i = 0; i < delay_cycles; i++) {
    }
}

