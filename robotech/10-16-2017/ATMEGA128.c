// some specific includes and defines

#define TRUE    1
#define FALSE   0

void set_leds(char mode);
void set_motors(char mode);



int main(void) {
    char previous_button_state = FALSE;

    // behaviour mode defines the machine behaviour
    // 1 - forwards, 2 - backwards, 3 - stop
    char behaviour_mode = 0;

    while (TRUE) {
        if (previous_button_state && !get_button_state()) {
            // button released, switch behaviour mode and apply it
            behaviour_mode++;
            set_leds(behaviour_mode);
            set_motors(behaviour_mode);

            if (behaviour_mode = 3) {
                // reset behaviour mode to 0 (it would be 1 with next iteration)
                behaviour_mode = 0;
            }
        }
        previous_button_state = get_button_state();
    }
}


void set_leds(char mode) {
    // turn off all leds
    LED.1 = 0x00;
    LED.2 = 0x00;
    LED.3 = 0x00;

    // turn on the specified led
    switch(mode) {
        case 1:
            LED.1 = 0xff;
            break;
        case 2:
            LED.2 = 0xff;
            break;
        case 3:
            LED.3 = 0xff;
            break;
    }
}


void set_motors(char mode) {
    switch(mode) {
        case 1:
            PORTD.1 = 1;
            PORTD.2 = 1;
            OCR1A = 0x7f;
            OCR2A = 0x7f;
            break;
        case 2:
            PORTD.1 = 0;
            PORTD.2 = 0;
            OCR1A = 0x7f;
            OCR2A = 0x7f;
            break;
        case 3:
            OCR1A = 0x00;
            OCR2A = 0x00;
            break;
    }
}

