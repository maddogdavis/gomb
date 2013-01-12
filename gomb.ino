#include <Servo.h>
#include <Timer.h>
#include "gomb.h"

Servo sl;
Servo sr;
Servo sc;
Timer t;
Ultra uc = {"capture", A2, 0, 0};
Ultra uf = {"flush",   A3, 0, 0};

Mode *mode;

void loop() {
    t.update();
}

void timer() {
    digitalWrite(12, digitalRead(12) ^ 1);
    ultra(&uc);
    ultra(&uf);
    transitions();
}

// transitions

void transitions() {
}

// ultra

void ultra(Ultra *u) {
    u->v = analogRead(u->pin);
}

void baseline(Ultra *u) {
    ultra(u);
    u->base = u->v;
    log(u->m, u->base);
}

// servo

void servos(Mode m) {
    angle(&sl, m.sl);
    angle(&sc, m.sc);
    angle(&sr, m.sr);
    log(m.m);
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
    baseline(&uc);
    baseline(&uf);
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
    uc.pin = A2;
    uf.pin = A3;
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
