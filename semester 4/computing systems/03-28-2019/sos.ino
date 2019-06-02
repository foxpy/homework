#define LED 4
#define SHORT_DELAY 250
#define LONG_DELAY 750

void blink(uint16_t time)
{
	digitalWrite(LED, HIGH);
	delay(time);
	digitalWrite(LED, LOW);
	delay(time);
}

void short_blink()
{
	for(uint8_t i = 0; i < 3; i++) {
		blink(SHORT_DELAY);
	}
}

void long_blink()
{
	for(uint8_t i = 0; i < 3; i++) {
		blink(LONG_DELAY);
	}
}

void setup()
{
	pinMode(LED, OUTPUT);

	short_blink();
	long_blink();
	short_blink();
}

void loop() {}
