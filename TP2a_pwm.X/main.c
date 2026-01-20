#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define LED1 LATDbits.LATD0
#define DIR_LED1 TRISDbits.TRISD0
#define BUTTON1 PORTBbits.RB0
#define DIR_BUTTON1 TRISBbits.TRISB0

void config_timer2();
void config_pwm4();
void init_led_button();

void main(void) {
    init_led_button();
    config_timer2();
    config_pwm4();
    while (1) {
        if(BUTTON1 == 1) {
            PWM4DCH = 249; // (250 × 4 + 0) / 1000 = 1000/1000 = 100%
        } else {
            PWM4DCH = 24; // (25 × 4 + 0) / 1000 = 100/1000 = 10%
        }
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
    PWM4DCH = 0;
    PWM4DCL = 0;

    PWM4CONbits.PWM4EN = 1;  // Activer PWM4
    
    DIR_LED1 = 0; // RB0 = sortie
    RD0PPS = 0x0F; // RB0 ? PWM4OUT
}

void init_interrupt() {
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void init_led_button() {
    DIR_LED1 = 0; LED1 = 1;
    DIR_BUTTON1 = 1;
    ANSELBbits.ANSB0 = 0; // PAS analogique par pitié
}



