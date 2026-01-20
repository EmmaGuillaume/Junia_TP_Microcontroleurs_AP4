#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define POT PORTAbits.RA0
#define DIR_POT TRISAbits.TRISA0

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

void init_led_pot();
void eteindre_toutes_leds();
void config_adc();
char read_adc();

void main(void) {
    char valeur;

    init_led_pot();
    config_adc();

    while (1) {
        valeur = read_adc();
        eteindre_toutes_leds();

        if (valeur < 32) {
            LED1 = 1;
        } else if (valeur < 64) {
            LED2 = 1;
        } else if (valeur < 96) {
            LED3 = 1;
        } else if (valeur < 128) {
            LED4 = 1;
        } else if (valeur < 160) {
            LED5 = 1;
        } else if (valeur < 192) {
            LED6 = 1;
        } else if (valeur < 224) {
            LED7 = 1;
        } else {
            LED8 = 1;
        }
    }
}

void config_adc(void) {
    ADCON0bits.CHS = 0b00000;
    ADCON1bits.ADFM = 0;
    ADCON0bits.ADON = 1;
}

/* Lecture de la valeur sur 8 bits */
char read_adc(void) {
    ADCON0bits.GO = 1; // Lancer la lecture de l?ADC
    while (ADCON0bits.GO) {
    } // Attendre la fin de l?acquisition
    return ADRESH; // Retourner les 8bits de poids fort du résultat
}

void eteindre_toutes_leds() {
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    LED6 = 0;
    LED7 = 0;
    LED8 = 0;
}

void init_led_pot() {
    DIR_LED1 = 0;
    DIR_LED2 = 0;
    DIR_LED3 = 0;
    DIR_LED4 = 0;
    DIR_LED5 = 0;
    DIR_LED6 = 0;
    DIR_LED7 = 0;
    DIR_LED8 = 0;

    eteindre_toutes_leds();

    DIR_POT = 1;
    ANSELAbits.ANSA0;
}