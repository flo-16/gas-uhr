#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor{
	private:
		uint8_t pin;
		uint8_t testOn;
		uint16_t leerTakte;
		uint16_t idle;
		uint32_t counter;
		uint16_t testWert;
		void test();
	public:
		Sensor(const uint8_t p, const uint8_t tActiv, const uint16_t leer):pin(p), testOn(tActiv), leerTakte(leer), idle(0) {}
		uint32_t getCounter() const { return counter; }
		void setCounter(uint32_t v) { counter = v; }
		void setup();
		void update();
};

void Sensor::setup() {
	pinMode(pin, INPUT_PULLUP);
}

void Sensor::update() {
	if(!(digitalRead(pin) || idle)) {
		counter++;
		idle = leerTakte;
	}
	if(idle) { --idle; }
	if(testOn) { test(); }
}

void Sensor::test() {
	testWert++;
	if(!testWert) counter++;
}

#endif
