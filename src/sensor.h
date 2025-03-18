#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
	private:
		uint8_t pin;
		uint32_t bouce;
		uint32_t counter;
	public:
		Sensor(const uint8_t p, const uint32_t b):pin(p), bouce(b) {}
		uint32_t getCounter() const { return counter; }
		void setCounter(uint32_t v) { counter = v; }
		void setup();
		void update(uint32_t t);
};

void Sensor::setup() {
	pinMode(pin, INPUT_PULLUP);
}

void Sensor::update(uint32_t t) {
	static uint8_t oldState = HIGH;
	static uint8_t buttonState = HIGH;
	static uint32_t bouceTime = 0;

	uint8_t reading = digitalRead(pin);
  if (reading != oldState) { bouceTime = t; }
	  	
	if ((t - bouceTime) > bouce) {
		if (reading != buttonState) {
			buttonState = reading;
			if (buttonState == LOW) { counter++; }
		}
	}
	
	oldState = reading;
}
	
#endif
