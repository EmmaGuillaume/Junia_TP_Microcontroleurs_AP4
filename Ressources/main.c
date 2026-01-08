#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define DIR_LED1 TRISDbits.TRISD0
#define DIR_LED2 TRISDbits.TRISD1

void init_leds() ;
void delay_approx();
const int delay_cycles = 500; // Nb of delay cycles

void main(void) {
    init_leds();
    while(1){ // Inf. loop : Blink LED1 & LED2
        LED1 = 1; // LED1 ON
        LED2 = 0; // LED2 OFF
        delay_approx(); // wait
        LED1 = 0; // LED1 OFF
        LED2 = 1; // LED2 ON
        delay_approx(); // wait
    }
}
void init_leds(){
    DIR_LED1 = 0; LED1 = 0; // LED1 : output, OFF
    DIR_LED2 = 0; LED2 = 0; // LED2 : output, OFF
}

void delay_approx(){
    for(int i=0; i<delay_cycles; i++){}
}

