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
void fstring (char msj[]);
char salidatx[]="Hola Hector";
int cont=0;
char x;

void __interrupt() myIsr(void){
    if (PIR1bits.RC1IF == 1){
        PORTAbits.RA1 =~PORTAbits.RA1;
        x = RCREG1;
        if (cont==0){
            if (x==72 || x==104){
                cont++;
                PORTAbits.RA7 =~PORTAbits.RA7;
            }
            else {
                cont=0;
            }
        }
        else if (cont==1){
            if (x==79 || x==111){
            cont++;
            PORTAbits.RA7 =~PORTAbits.RA7;
            }
            else {
            cont=0;
            }
        }
              
        else if (cont==2){
            if (x==76 || x==108){
            cont++;
            PORTAbits.RA7 =~PORTAbits.RA7;
            }
            else {
            cont=0;
            }
        }
        
        else if (cont==3){
            if (x==65 || x==97){
            cont++;
            PORTAbits.RA7 =~PORTAbits.RA7;
            }
            else {
            cont=0;
            }
        }
        
        else if (cont==4){
            if (x==32){
            cont++;
            PORTAbits.RA7 =~PORTAbits.RA7;
            }
            else {
            cont=0;
            }
        }
        
        else if (cont==5){
            if (x==80 || x==112){
            cont++;
            PORTAbits.RA7 =~PORTAbits.RA7;
            }
            else {
            cont=0;
            }
        }
        
        else if (cont==6){
            if (x==73 || x==105){
            cont++;
            PORTAbits.RA7 =~PORTAbits.RA7;
            }
            else {
            cont=0;
            }
        }
        
        else if (cont==7){
            if (x==67 || x==99){
            cont++;
            PORTAbits.RA7 =~PORTAbits.RA7;
            }
            else {
            cont=0;
            }
        }
        
        else if (cont==8){
            fstring(salidatx);
            cont=0;
        }
        PIR1bits.RC1IF = 0;
    }
}
            
void main(void) {
    //Configuracion osc
    OSCCONbits.IRCF = 0b111; //16 Megas (x PLL =64MHz)
    OSCTUNEbits.PLLEN = 0b1; //Habilitar el PLL
    OSCCONbits.SCS = 0b00; //Oscilador seleccionado por Config1(Interno)
    //Configuracion interrupciones
    INTCONbits.PEIE = 1; //Habilita la interrupcion por periferico
    PIR1bits.RC1IF = 0; //Establece flag en 0
    INTCONbits.GIEH = 1; //Habilita todas las interrupciones altas
    INTCONbits.GIEL = 1; //Habilita todas las interrupciones bajas
    PIE1bits.RC1IE = 1; //Habilitamos interrupcion por recepcion serial
    //Config del puerto serial
    TRISCbits.RC6 = 0; //Establecemos el puerto RC6 (TX1) como salida
    TRISCbits.RC7 = 1; //Establecemos el puerto RC7 (RX1) como entrada
    ANSELC = 0;
    TX1STAbits.SYNC = 0; //Establecemos modo asincrono
    TX1STAbits.TXEN = 1; //Habilitamos la transmision
    RCSTA1bits.SPEN = 1; //Habilitamos el puerto serial
    RCSTA1bits.CREN = 1; //Habilita recepcion continua
    BAUD1CONbits.BRG16 = 0; //8 bits del generador
    TX1STAbits.BRGH = 0; //Baud rate de baja velocidad
    SPBRG1 = 103;  //Baud rate a 9600
    //Config de otros pins
    ANSELA = 0; //Establecemos RA1 digital
    TRISA=0; //Establecemos RA1 como salida
    PORTA = 0;
    PORTC = 0;
    while(1);
    return;
}

void fstring (char msj[]){
    int i=0;
    while(msj[i]){
        TXREG1 = msj[i];
        i++;
        while(TX1STAbits.TRMT==0);
    }
}