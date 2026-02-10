#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "spi.h"
#include "lcd.h"

#define POT PORTAbits.RA0
#define DIR_POT TRISAbits.TRISA0

#define BUTTON1 PORTBbits.RB0
#define DIR_BUTTON1 TRISBbits.TRISB0

void delay_approx();
void config_uart();
void recevoir_envoyer_char();
void init_interrupt();
void config_adc();
char read_adc();
void init_pot();
void init_button();
bool switch_button(bool, char);
char clean_char(char);
char crypt_char(char, int);
const int delay_cycles = 10000; // Nb of delay cycles
const char alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyz";
int index;
bool isCrypted = false;

void main(void) {
    char valeur = 0;
    char valeurOld = -1;
    bool isCryptedOld = false;

    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();

    init_pot();
    init_button();
    config_adc();
    config_uart();
    init_interrupt();

    while (1) {

        isCrypted = switch_button(isCrypted, BUTTON1);
        valeur = read_adc(); // 0?255
        if (valeurOld != valeur || isCryptedOld != isCrypted) {
            valeurOld = valeur;
            isCryptedOld = isCrypted;
            index = valeur * 36 / 256;
            LCD_Clear();
            LCD_GoTo(0, 0);
            char buffer[4]; // suffisant pour 0?35 + '\0'
            sprintf(buffer, "%d", index);

            LCD_WriteString(buffer);
            LCD_GoTo(1, 0);
            if (isCrypted) {
                LCD_WriteString("Chiffrement");
            } else {
                LCD_WriteString("En clair");
            }
        }
        delay_approx();
    }
}

void delay_approx() {
    for (int i = 0; i < delay_cycles; i++) {
    }
}

char clean_char(char c) {
    // majuscule vers minuscule
    if (c >= 'A' && c <= 'Z') {
        c = c + ('a' - 'A');
    }

    // chiffres
    if (c >= '0' && c <= '9') {
        return c;
    }

    // lettres minuscules autorisées
    if (c >= 'a' && c <= 'z') {
        return c;
    }

    // Hors alphabet ignoré
    return 0;
}

char crypt_char(char c, int decalage) {
    int len = strlen(alphabet);

    for (int i = 0; i < len; i++) {
        if (c == alphabet[i]) {
            return alphabet[(i + decalage) % len];
        }
    }
    return 0;
}

bool switch_button(bool etat, char bouton) {
    static char last_state = 0;

    if (bouton && !last_state) {
        etat = !etat;
    }

    last_state = bouton;
    return etat;
}

void __interrupt() isr(void) {
    if (PIR1bits.RCIF) {
        PIR1bits.RCIF = 0;
        if (isCrypted) {
            TX1REG = crypt_char(clean_char(RC1REG), index);
        } else {
            TX1REG = clean_char(RC1REG);
        }
    }
}

void init_interrupt() {
    PIR1bits.RCIF = 0; // Efface le flag avant de commencer
    PIE1bits.RCIE = 1; // Active l'interruption de RCIF
    INTCONbits.PEIE = 1; // Active les interruptions des p?riph?riques
    INTCONbits.GIE = 1; // Active les interruptions globales
}

void config_uart() {
    // Connecter RC6 ? TX/CK (via le registre RC6PPS)
    RC6PPS = 0b10100;
    // Connecter RC7 ? RX (via le registre RXPPS)
    RXPPS = 0b10111;

    // RC6 : Sortie
    TRISCbits.TRISC6 = 0;
    // RC7 : Entr?e num?rique
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

void init_pot() {
    DIR_POT = 1;
    ANSELAbits.ANSA0;
}

void init_button() {
    DIR_BUTTON1 = 1;
    ANSELBbits.ANSB0 = 0; // PAS analogique par pitié
}

