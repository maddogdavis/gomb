#include <Servo.h>
#include "Timer.h"

Servo sl;
//Servo sr;
//Servo sc;
Timer t;

void timer() {
    digitalWrite(13, digitalRead(13) ^ 1);
}

void loop() {
    t.update();
}

// servo

void angle(Servo *s, int a) {
    log("angle", a);
    s->write(a);
}

// init

void setup() {
    innit();
    report();
}

void innit() {
    init_serial();
    init_pins();
    init_timer();
    init_servos();
}

void report() {
    angle(&sl, 30);
    delay(500);
    angle(&sl, 120);
    delay(500);
    angle(&sl, 30);
    delay(500);
    angle(&sl, 120);
}

void init_serial() {
    Serial.begin(9600);
}

void init_pins() {
    pinMode(13, OUTPUT);
}

void init_timer() {
    t.every(2000, timer);
}

void init_servos() {
    sl.attach(9);
//    sr.attach(17);
//    sc.attach(18);
}

// util

void log(char *m, int v) {
    Serial.print(m);
    Serial.print(": ");
    Serial.println(v, DEC);
}
