#include "../Ressources/configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2
#define LED4 LATDbits.LATD3
#define LED5 LATBbits.LATB0
#define LED6 LATBbits.LATB1
#define LED7 LATBbits.LATB2
#define LED8 LATBbits.LATB3

#define DIR_LED1 TRISDbits.TRISD0
#define DIR_LED2 TRISDbits.TRISD1
#define DIR_LED3 TRISDbits.TRISD2
#define DIR_LED4 TRISDbits.TRISD3
#define DIR_LED5 TRISBbits.TRISB0
#define DIR_LED6 TRISBbits.TRISB1
#define DIR_LED7 TRISBbits.TRISB2
#define DIR_LED8 TRISBbits.TRISB3

void init_leds();
void delay_approx();
const int delay_cycles = 10000; // Nb of delay cycles

void main(void) {
    init_leds();
    while (1) {
        LED8 = 0;
        LED1 = 1;

        delay_approx(); // wait
        LED1 = 0;
        LED2 = 1;

        delay_approx(); // wait
        LED2 = 0;
        LED3 = 1;

        delay_approx(); // wait
        LED3 = 0;
        LED4 = 1;
        
        delay_approx(); // wait
        LED4 = 0;
        LED5 = 1;
        
        delay_approx(); // wait
        LED5 = 0;
        LED6 = 1;
        
        delay_approx(); // wait
        LED6 = 0;
        LED7 = 1; 
        
        delay_approx();
        LED7 = 0;
        LED8 = 1;   
        
        delay_approx();
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

