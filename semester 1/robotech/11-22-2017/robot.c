#include <mega128.h>
#include <stdio.h>
#include <delay.h>
#include <alcd.h>


#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT  1
#define ADC_VREF_TYPE   0x20


unsigned char adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
char lcd_buffer[33];



void set_motors(char mode) {
    switch (mode) {
        case 1:
            // forwards
            PORTA.1 = 0x01;
            PORTA.2 = 0x00;
            PORTA.3 = 0x01;
            PORTA.4 = 0x00;
            break;
        case 2:
            // backwards
            PORTA.1 = 0x00;
            PORTA.2 = 0x01;
            PORTA.3 = 0x00;
            PORTA.4 = 0x01;
            break;
        case 3:
            // stop
            PORTA.1 = 0x00;
            PORTA.2 = 0x00;
            PORTA.3 = 0x00;
            PORTA.4 = 0x00;
            break;
    }
}


void set_leds(char mode) {
    PORTA.5 = 0x00;
    PORTA.6 = 0x00;
    PORTA.7 = 0x00;

    switch (mode) {
        case 1:
            // green
            PORTA.5 = 0x01;
            break;
        case 2:
            // red
            PORTA.6 = 0x01;
            break;
        case 3:
            // yellow
            PORTA.7 = 0x01;
            break;
    }
}



// button released
interrupt [EXT_INT0] void ext_int0_isr(void) {
    static char mode = 0x00;
    mode++;

    set_motors(mode);
    set_leds(mode);

    if (mode == 0x03) {
    mode = 0x00;
    }
}


// system timer 0
interrupt [TIM0_OVF] void timer0_ovf_isr(void) {
    static unsigned char lcd_delay_count = 0x00;
    lcd_delay_count++;

    if (lcd_delay_count == 0xC8) {
        lcd_delay_count = 0x00;
        sprintf(lcd_buffer, "ADC1: %3d\nADC2: %3d", adc_data[0], adc_data[1]);
        lcd_clear();
        lcd_puts(lcd_buffer);
    }

    OCR1AL = adc_data[0];
    OCR1BL = adc_data[1];
}


// ADC auto input scanning
interrupt [ADC_INT] void adc_isr(void) {
    static unsigned char input_index=0;
    adc_data[input_index]=ADCH;
    if (++input_index > (LAST_ADC_INPUT-FIRST_ADC_INPUT)) {
        input_index=0;
    }
    ADMUX=(FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff))+input_index;
    delay_us(10);
    ADCSRA|=0x40;
}



void main(void) {
    // Port A: 0 - in, 1-7 - out
    PORTA=0x00;
    DDRA=0xFE;

    // Port B: 0-4 - in, 5,6 - out, 7 - in
    PORTB=0x00;
    DDRB=0x60;

    // Port C: 0-2 - out, 3 - in, 4-7 - out
    PORTC=0x00;
    DDRC=0xF7;

    // Port D-G: everything is for input
    PORTD=0x00; DDRD=0x00;
    PORTE=0x00; DDRE=0x00;
    PORTF=0x00; DDRF=0x00;
    PORTG=0x00; DDRG=0x00;


    // Timer 0 - 1000 Hz
    ASSR=0x00;
    TCCR0=0x02;
    TCNT0=0x00;
    OCR0=0x00;

    // Timer 1 - 1000 Hz, OC1{A,B} - PWM
    TCCR1A=0xA1;
    TCCR1B=0x0A;
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;
    OCR1CH=0x00;
    OCR1CL=0x00;


    // External interrupts: INT0 - falling edge
    EICRA=0x02;
    EICRB=0x00;
    EIMSK=0x01;
    EIFR=0x01;

    // enable timer interrupts
    TIMSK=0x01;
    ETIMSK=0x00;


    // ADC
    ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
    ADCSRA=0xCB;


    // LCD: 16 characters
    lcd_init(16);


    // Enable interrupts globally
    #asm("sei");


    while (1) {
        // do nothing forever
    }
}
