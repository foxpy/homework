#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
	lcd.begin(16, 2);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
}

void loop() {
	char str[17];
	for(uint8_t i = 6; i < 10; i++) {
		snprintf(str, 17, "Speaker:       %1d", i-5);
		lcd.setCursor(0, 0);
		lcd.print(str);
		snprintf(str, 17, "Frequency:  %4d", 4*i*i);
		lcd.setCursor(0, 1);
		lcd.print(str);
		tone(i, 4*i*i, 1000);
		delay(1000);
	}
}
