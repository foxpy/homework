#define RED 0
#define BLUE 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4

void setup()
{
	pinMode(A0, INPUT);
	for(uint8_t i = 0; i < 5; i++) {
		pinMode(i, OUTPUT);
	}
}

void loop()
{
	static uint8_t state = 0;
	if (digitalRead(A0) == HIGH) {
		state++;
		delay(200);
	}

	switch(state%4) {
		case 0:
			digitalWrite(RED, HIGH);
			digitalWrite(BLUE, HIGH);
			digitalWrite(ORANGE, LOW);
			digitalWrite(YELLOW, LOW);
			digitalWrite(GREEN, HIGH);
			break;
		case 1:
			digitalWrite(RED, LOW);
			digitalWrite(BLUE, LOW);
			digitalWrite(ORANGE, HIGH);
			digitalWrite(YELLOW, HIGH);
			digitalWrite(GREEN, HIGH);
		case 2:
			digitalWrite(RED, HIGH);
			digitalWrite(BLUE, LOW);
			digitalWrite(ORANGE, HIGH);
			digitalWrite(YELLOW, HIGH);
			digitalWrite(GREEN, LOW);
	}
}
