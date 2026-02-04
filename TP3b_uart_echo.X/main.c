#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

void delay_approx();
void config_uart();
void recevoir_envoyer_char();
const int delay_cycles = 10000; // Nb of delay cycles

void main(void) {
    config_uart();
    while(1){
        recevoir_envoyer_char();
    }
}

void delay_approx() {
    for (int i = 0; i < delay_cycles; i++) {
    }
}

void recevoir_envoyer_char() {
    if (PIR1bits.RCIF){
        TX1REG = RC1REG;
        PIR1bits.RCIF = 0;
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
    
    // Activation des pins (Bit SPEN, registre RC1STA)
    RC1STAbits.SPEN = 1;
    // Activation du transmitter (Bit TXEN, registre TX1STA)
    TX1STAbits.TXEN = 1;
    // Activation du receiver (Bit CREN, registre RC1STA)
    RC1STAbits.CREN = 1;
}

