/*
 * File:   mainadc.c
 * Author: chiky
 *
 * Created on 16 de septiembre de 2020, 12:33 PM
 */
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = OFF     // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = ON       // Watchdog Timer Enable bits (WDT is always enabled. SWDTEN bit has no effect)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<5:0> pins are configured as analog input channels on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)
#define _XTRAL_FREQ 32000000

#include <xc.h>
//#include "config.h" 
void main(void) {
    int resadc;
    OSCCONbits.IRCF = 0b110; //8 Megas (x PLL =32MHz)
    OSCTUNEbits.PLLEN = 0b1; //Hailitar el PLL
    OSCCONbits.SCS = 0b00; //Oscilador seleccionado por fosc(Interno)
    ANSELAbits.ANSA0 = 1; //Establecemos RA0 analogico
    ANSELCbits.ANSC6 = 0; //Establecemos RC6 digital
    ANSELCbits.ANSC7 = 0; //Establecemos RC7 digital
    ANSELCbits.ANSC4 = 0; //Establecemos RC4 digital
    ANSELD = 0; //Establecemos el puerto D digital
    TRISAbits.RA0 = 1; //Establecemos RA0 como entrada
    TRISCbits.RC6 = 0; //Establecemos RC6 como salida
    TRISCbits.RC7 = 0; //Establecemos RC7 como salida
    TRISCbits.RC4 = 0; //Establecemos RC4 como salida
    TRISD = 0; //Establecemos el puerto D como salida;
   
    ADCON0bits.CHS = 0;
    
    ADCON1bits.NVCFG = 0; //VRef negativo interno
    ADCON1bits.PVCFG =0; //VRef positivo interno
    ADCON2bits.ADCS = 0b110; //Fosc/64
    ADCON2bits.ADFM = 1; //Recorrido a la derecha
    ADCON2bits.ACQT = 0b101; //12 TAD
    ADCON0bits.ADON = 1; //Encendemos el ADC
    PORTD=0x00;
    while(1){
        ADCON0bits.GO = 1; //Empieza el ADC
        while(ADCON0bits.GO);
            resadc = ADRES;
//            resadc = resadc<<8;
//            resadc = resadc + ADRESL;
        
            PORTCbits.RC6 = ADRESH >> 1;
            PORTCbits.RC7 = ADRESH;
            PORTD = ADRESL;
            if (resadc>=0b1100110){ // .5/4.8x10^-3
            PORTCbits.RC4 = 1;
            }
            else if (resadc<=0b110100){ // .25/4.8x10^-3
            PORTCbits.RC4 = 0;
            }
            
    }
    return;
}
