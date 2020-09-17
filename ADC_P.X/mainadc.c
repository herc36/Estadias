/*
 * File:   mainadc.c
 * Author: chiky
 *
 * Created on 16 de septiembre de 2020, 12:33 PM
 */


#include <xc.h>
#include "config.h"
void main(void) {
    int resadc;
    OSCCONbits.IRCF = 0b110; //8 Megas (x PLL =32MHz)
    OSCCONbits.SCS = 0b00; //Oscilador seleccionado por fosc(Interno)
    ANSELAbits.ANSA0 = 1; //Establecemos RA0 analogico
    ANSELCbits.ANSC6 = 0; //Establecemos RC6 digital
    ANSELCbits.ANSC7 = 0; //Establecemos RC7 digital
    ANSELD = 0; //Establecemos el puerto D digital
    TRISAbits.RA0 = 1; //Establecemos RA0 como entrada
    TRISCbits.RC6 = 0; //Establecemos RC6 como salida
    TRISCbits.RC7 = 0; //Establecemos RC7 como salida
    TRISD = 0; //Establecemos el puerto D como salida;
    ADCON0bits.ADON = 1; //Encendemos el ADC
    ADCON0bits.CHS = 0; //Seleccionamos el canal AN0
    ADCON1bits.NVCFG = 0; //VRef negativo interno
    ADCON1bits.PVCFG =0; //VRef positivo interno
    ADCON2bits.ADCS = 0b011; //Foscinterno
    ADCON2bits.ADFM = 1; //Recorrido a la derecha
    while(1){
        ADCON0bits.GO_nDONE = 1; //Empieza el ADC
        while(ADCON0bits.GO_nDONE == 0){
//            resadc = ADRESH;
//            resadc = resadc<<8;
//            resadc = resadc + ADRESL;
            PORTCbits.RC6 = ADRESH >> 1;
            PORTCbits.RC7 = ADRESH;
            PORTD = ADRESL;
        }
    }
    return;
}
