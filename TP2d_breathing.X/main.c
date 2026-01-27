#include "../Ressources/configbits.h"
#include <xc.h>
#include <stdbool.h>

#define LED1 LATDbits.LATD0
#define DIR_LED1 TRISDbits.TRISD0

void init_leds();
void init_timer();
void init_interrupt();
void config_pwm4();



 unsigned int intensite = 0;
  bool reverse = false;

void __interrupt() isr(void) {
    if (PIR1bits.TMR2IF) {
        PIR1bits.TMR2IF = 0;

        if(reverse) {
            intensite--;
        } else {
            intensite++;
        }
        
        PWM4DCH = intensite;
        
        if (intensite >= 249){
            reverse = true;
            intensite = 249; // juste au cas où on dépasse les bornes
        } else if (intensite <= 0){
            reverse = false;
            intensite = 0; // juste au cas où on dépasse les bornes
        }
    }
}

void main(void) {
    init_leds();
    init_timer();
    init_interrupt();
    config_pwm4();


    while (1) {

    }
}

void config_pwm4(void){
    PWM4DCH = 0;
    PWM4DCL = 0;

    PWM4CONbits.PWM4EN = 1;  // Activer PWM4
    
    DIR_LED1 = 0; // RB0 = sortie
    RD0PPS = 0x0F; // RB0 ? PWM4OUT
}

void init_leds() {
    DIR_LED1 = 0;
    LED1 = 0;
}

void init_timer() {
    PR2 = 249;
    T2CONbits.T2CKPS = 0b01;
    T2CONbits.T2OUTPS = 0b0111;
    T2CONbits.TMR2ON = 0b1; 
    // (PR2 - 1) * ((prescaler * postcaler) / (FrequPoc / 4)
    // = 0.004 ~ 1/249  
    
}

void init_interrupt() {
    PIR1bits.TMR2IF = 0; // Efface le flag avant de commencer
    PIE1bits.TMR2IE = 1; // Active l'interruption du TMR2
    INTCONbits.PEIE = 1; // Active les interruptions des périphériques
    INTCONbits.GIE = 1; // Active les interruptions globales
}

