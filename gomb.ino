#include <Servo.h>
#include <Timer.h>
#include "gomb.h"

Servo sl;
Servo sr;
Servo sc;
Timer t;

void timer() {
    digitalWrite(12, digitalRead(12) ^ 1);
    int x = analogRead(A2);
    int y = analogRead(A3);
    log("sensors", x, y);
}

void loop() {
    t.update();
}

// servo

void servos(Mode m) {
    log(m.m);
    angle(&sl, m.sl);
    angle(&sc, m.sc);
    angle(&sr, m.sr);
}

void angle(Servo *s, int a) {
    s->write(a);
}

void dance(int d) {
    for (int i=0; i < 3; i++) {
        servos(M_OPEN);
        delay(d);
        servos(M_CLOSED);
        delay(d);
    }
}

// init

void setup() {
    innit();
    report();
    ready();
}

void innit() {
    init_serial();
    init_pins();
    init_timer();
    init_ultras();
    init_servos();
}

void report() {
    dance(500);
}

void ready() {
    servos(M_CLOSED);
    digitalWrite(13, HIGH);
    delay(5000);
    digitalWrite(13, LOW);
    servos(M_OPEN);
}

void init_serial() {
    Serial.begin(9600);
}

void init_pins() {
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
}

void init_timer() {
    t.every(100, timer);
}

void init_servos() {
    sl.attach(9);
    sc.attach(8);
    sr.attach(7);
}

void init_ultras() {
}

// log

void log(char *m, int v) {
    Serial.print(m);
    Serial.print(": ");
    Serial.println(v, DEC);
}

void log(char *m) {
    Serial.println(m);
}

void log(char *m, int x, int y) {
    char c[128];
    sprintf(c, "%s: %d %d",m, x, y);
    Serial.println(c);
}
