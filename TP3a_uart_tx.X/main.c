#include "configbits.h" // Bits de configuration
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

    }
}

void init_leds() {
    DIR_LED1 = 0; LED1 = 0;
    DIR_LED2 = 0; LED2 = 0;
    DIR_LED3 = 0; LED3 = 0;
    DIR_LED4 = 0; LED4 = 0;
    DIR_LED5 = 0; LED5 = 0;
    DIR_LED6 = 0; LED6 = 0;
    DIR_LED7 = 0; LED7 = 0;
    DIR_LED8 = 0; LED8 = 0;
}

void delay_approx() {
    for (int i = 0; i < delay_cycles; i++) {
    }
}

void config_uart() {
    // Connecter RC6 à TX/CK (via le registre RC6PPS)
    RC6PPS = 0b10100;
    // Connecter RC7 à RX (via le registre RXPPS)
    RXPPS = 0b10111;
    // RC6 : Sortie
    TRISCbits.TRISC6 = 0;
    // RC7 : Entrée numérique
    TRISCbits.TRISC7 = 1;
    ANSELCbits.ANSC7 = 0; // PAS analogique
    
    // Bit SYNC (registre TX1STA; on utilisera le module en mode asynchrone, donc SYNC=0)
    TX1STAbits.SYNC = 0;
    // Bit BRGH (registre TX1STA)
    TX1STAbits.BRGH = 0;
    // Bit BRG16 (registre BAUD1CON)
    BAUD1CONbits.BRG16 = 0;
    // Registres SP1BRGH, SP1BRGL (SP1BRG)
    SP1BRG = 12;

}

void envoyer(char[] ){
    // Activation des pins (Bit SPEN, registre RC1STA)
    RC1STAbits.SPEN = 1;
    // Activation du transmitter (Bit TXEN, registre TX1STA)
    TX1STAbits.TXEN = 1;
    
    
    // Activation du receiver (Bit CREN, registre RC1STA)
    RC1STAbits.CREN = 1;
    // La transmission d?1 octet de données se fait en écrivant dans le registre TX1REG
    
   
    
    //La réception d?1 octet de données se fait en lisant le registre RC1REG

}

