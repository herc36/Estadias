// CONFIG1H
#pragma config FOSC = INTIO67    // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = ON      // 4X PLL Enable (Oscillator multiplied by 4)
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
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include "flex_lcd.h"
#include <stdio.h>
#include <pic18.h>
int resadc[9]; int x=0;
float temp[9]; float promedio=0.0;
unsigned char impresion[20];

void __interrupt() myIsr(void){
    if (INTCONbits.TMR0IF==1){
        if (x<10){
            PORTAbits.RA5 = 1;
            _delay(500000);
            PORTAbits.RA5 = 0;
            
            ADCON0bits.GO = 1; //Empieza el ADC
            while(ADCON0bits.GO);
            resadc[x] = ADRES;
            x++;
//            ADCON0bits.GO = 0; //Finaliza el ADC
        }
        PORTAbits.RA1 =~PORTAbits.RA1;
        INTCONbits.TMR0IF = 0;
        TMR0L = 0b10000100; //Parte baja del tmr0 de 28036 [65536-37500] (300ms seg con ps de 64)
        TMR0H = 0b01101101; //Parte alta del tmr0 de 28036 [65536-37500] (300ms seg con ps de 64)        
    }
}

void main(void) {
    //Configuracion osc
    OSCCONbits.IRCF = 0b110; //8 Megas (x PLL =32MHz)
    OSCTUNEbits.PLLEN = 0b1; //Hailitar el PLL
    OSCCONbits.SCS = 0b00; //Oscilador seleccionado por Config1(Interno)
    //Configuracion interrupciones
    INTCONbits.TMR0IE = 1; //Habilita la interrupcion del timer 0
    INTCONbits.TMR0IF = 0; //Establece flag en 0
    INTCONbits.GIEH = 1; //Habilita todas las interrupciones altas
    INTCONbits.GIEL = 1; //Habilita todas las interrupciones bajas
    //Configuracion timer
    T0CONbits.T08BIT = 0; //Establece en 16 bits el timer
    T0CONbits.T0CS = 0; //Selecciona el reloj interno
    T0CONbits.PSA = 0; //Habilita el prescaler
    T0CONbits.T0PS = 0b101; //Prescaler a 64
    TMR0L = 0b10000100; //Parte baja del tmr0 de 28036 [65536-37500] (300ms seg con ps de 64)
    TMR0H = 0b01101101; //Parte alta del tmr0 de 28036 [65536-37500] (300ms seg con ps de 64)
    //Configuracion ADC
    ANSELAbits.ANSA0 = 1; //Establecemos RA0 analogico
    TRISAbits.RA0 = 1; //Establecemos RA0 como entrada
    ADCON0bits.CHS = 0; //Seleccionamos AN0
    ADCON1bits.NVCFG = 0; //VRef negativo interno
    ADCON1bits.PVCFG =0; //VRef positivo interno
    ADCON2bits.ADCS = 0b011; //Fosc interno
    ADCON2bits.ADFM = 1; //Recorrido a la derecha
    ADCON2bits.ACQT = 0b101; //12 TAD
    ADCON0bits.ADON = 1; //Encendemos el ADC
    //Config de pins
    ANSELAbits.ANSA1 = 0; //Establecemos RA1 digital
    TRISAbits.RA1=0; //Establecemos RA1 como salida
    ANSELAbits.ANSA5 = 0; //Establecemos RA5 digital
    TRISAbits.RA5=0; //Establecemos RA5 como salida
    PORTD=0; //Limpiamos el puerto D
    TRISD = 0; //Establecemos el puerto D como salida;
    ANSELD = 0; //Establecemos el puerto D digital
    //Config LCD
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    _delay(100000);
    
    while(1){
        if (x<10){
            Lcd_Out(1,1,"Temperatura:");
            Lcd_Out(2,1,"Cargando");
            Lcd_Cmd(LCD_BLINK_CURSOR_ON);
            _delay(100000);
        }
        else if (x>10){
            for (int i=0; i<10; i++){
                temp[i] = 100*(resadc[i]*5.0/1024.0);
                promedio = promedio + temp[i];
            }
            Lcd_Cmd(LCD_CLEAR);
            Lcd_Cmd(LCD_CURSOR_OFF);
            Lcd_Out(1,1,"Temperatura:");
            _delay(100000);
            promedio = promedio/10;
            sprintf(impresion,"%04.2f",promedio);
            Lcd_Out2(2,1,impresion);            
        }
        PORTD = resadc[0];
    }
    
    return;
}