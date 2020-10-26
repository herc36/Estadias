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

#include <xc.h>
#define _XTRAL_FREQ 64000000
void mandarspi(unsigned char entradaspi);
//void mandarspiepron(unsigned char entradaspi);
//void statusepron(void);
void main(void) {
    //Configuracion osc
    OSCCONbits.IRCF = 0b111; //16 Megas (x PLL =64MHz)
    OSCTUNEbits.PLLEN = 0b1; //Habilitar el PLL
    OSCCONbits.SCS = 0b00; //Oscilador seleccionado por Config1(Interno)
    //Config de otros pins
    ANSELB = 0; //Establecemos puerto B digital
    TRISB = 1; //Establecemos el puerto B como entrada
    PORTB = 0;
    //Config de SPI
    ANSELC = 0;
    TRISCbits.RC3 = 0; //Establecemos RC3 (SCK) como salida
    TRISCbits.RC4 = 1; //Establecemos RC4 (SDI) como entrada
    TRISCbits.RC5 = 0; //Establecemos RC5 (SDO) como salida
    TRISAbits.RA5 = 0; //Establecemos RA5 (SS) como salida
    LATAbits.LA5 = 1; //Inicia estado de SS
    SSP1CON1bits.SSPEN = 1; //Habilitamos el SPI
    SSP1CON1bits.SSPM = 0b0010; //SPI Master mode, clock = FOSC/64 (1Mhz))
    SSP1STATbits.SMP = 0; //Muestreo del input data a medio tiempo
//    SSP1STATbits.CKE = 0; //Transmision en flanco de bajada
    SSP1STATbits.CKE = 1; //Transmision en flanco de bajada
    SSP1CON1bits.CKP = 0; //Estado de espera de SCK bajo
//    statusepron();
    while(1){
        mandarspi(PORTB);
        _delay(1000000);
    }
}

void mandarspi(unsigned char entradaspi){
        LATAbits.LA5 = 0;
        _delay(100);
        SSP1BUF = entradaspi;
        while(PIR1bits.SSP1IF==0);
        _delay(100);
        PIR1bits.SSP1IF=0;
        LATAbits.LA5 = 1;
}

//void mandarspiepron(unsigned char entradaspi){
//        LATAbits.LA5 = 0;
//        _delay(100);
//        SSP1BUF = 0b10;
//        while(PIR1bits.SSP1IF==0);
//        PIR1bits.SSP1IF=0;
//        SSP1BUF = 0b0;
//        while(PIR1bits.SSP1IF==0);
//        PIR1bits.SSP1IF=0;
//        SSP1BUF = 0b10101010;
//        while(PIR1bits.SSP1IF==0);
//        PIR1bits.SSP1IF=0;
//        _delay(100);
//        LATAbits.LA5 = 1;
//}
//
//void statusepron(void){
//        LATAbits.LA5 = 0;
//        _delay(100);
//        SSP1BUF = 0b1;
//        while(PIR1bits.SSP1IF==0);
//        PIR1bits.SSP1IF=0;
//        SSP1BUF = 0b0;
//        while(PIR1bits.SSP1IF==0);
//        PIR1bits.SSP1IF=0;
//        _delay(100);
//        LATAbits.LA5 = 1;
//}

