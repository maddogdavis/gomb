#include "Timer.h"

Timer t;

void setup() {
    init_serial();
    init_pins();
    init_timer();
}

void init_serial() {
    Serial.begin(9600);
}

void init_pins() {
    pinMode(13, OUTPUT);
//   pinMode(12, OUTPUT);
}

void init_timer() {
    t.every(2000, timer);
}


void timer() {
    digitalWrite(13, digitalRead(13) ^ 1);
}

void loop() {
    t.update();
}
