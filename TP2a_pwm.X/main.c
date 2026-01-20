#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define LED1 LATDbits.LATD0
#define DIR_LED1 TRISDbits.TRISD0


void config_timer2();
void config_pwm4();
void init_led();;
void init_interrupt();

void main(void) {
    init_led();
    init_interrupt();
    config_timer2();
    config_pwm4();
    while (1) {
        
    }
}

void __interrupt() isr(void) {
    if (PIR1bits.TMR2IF) {
        PIR1bits.TMR2IF = 0;

        // interruption logic goes here
    }
}

/* Configurer le Timer2 avec une période de 40 us */
void config_timer2(void){
T2CONbits.T2CKPS = 3; // Prescaler = 1:64
T2CONbits.T2OUTPS = 4; // Postscaler = 1:5
PR2 = 249; // Période de Timer2 pour 40ms
T2CONbits.TMR2ON = 1; // Activer Timer2
}
/* Configurer la PWM4 avec un rapport cyclique de 10% */
void config_pwm4(void){
PWM4DCH = 25; // Rapport cyclique (poids fort) : 25
PWM4DCL = 0; // Rapport cyclique (poids faible) : 0
// Soit rapport cyclique = [(25 << 2) + 0] / 4(249+1) = 0.1
PWM4CONbits.PWM4EN = 1; // Activer PWM4
}

void init_interrupt() {
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void init_led() {
    DIR_LED1 = 0; LED1 = 0;
}



