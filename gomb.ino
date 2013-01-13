#include <Servo.h>
#include <Timer.h>
#include "gomb.h"

Servo sl;
Servo sr;
Servo sc;
Timer t;

Motor ml = {"left",   30, 120, sl};
Motor mc = {"centre", 30, 120, sc};
Motor mr = {"righ",   30, 120, sr};

Ultra uc = {{"capture", A2}, {0, 0, 0UL}};
Ultra uf = {{"flush",   A3}, {0, 0, 0UL}};

void loop() {
    t.update();
}

void timer() {
    heartbeat();
    read_ultras();
    update();
}

// transitions

void update() {
    log("ultra", uc.val.v, uf.val.v);
}

// ultra

void set_baseline(Ultra *u) {
    read_ultra(u);
    u->val.base = u->val.v;
    u->val.quiet_at = millis();
    log(u);
}

void read_ultras() {
    read_ultra(&uc);
    read_ultra(&uf);
}

void read_ultra(Ultra *u) {
    u->val.v = analogRead(u->def.pin);
}

// servo

void set_servos(Mode m) {
    set_servo(&ml, m.l);
    set_servo(&mc, m.c);
    set_servo(&mr, m.r);
    log(m.m);
}

void set_servo(Motor *m, int mode) {
    if (mode == MODE_OPEN) drive_servo(m, m->open);
    if (mode == MODE_CLOSED) drive_servo(m, m->close);
}

void drive_servo(Motor *m, int a) {
    m->servo.write(a);
}

void dance(int d) {
    for (int i=0; i < 3; i++) {
        set_servos(M_OPEN);
        delay(d);
        set_servos(M_CLOSED);
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
    init_state();
}

void report() {
    dance(500);
}

void ready() {
    set_baseline(&uc);
    set_baseline(&uf);
    set_servos(M_CLOSED);
    digitalWrite(13, HIGH);
    delay(5000);
    digitalWrite(13, LOW);
    set_servos(M_OPEN);
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
    ml.servo.attach(9);
    mc.servo.attach(8);
    mr.servo.attach(7);
}

void init_ultras() {
    noop();
}

void init_state() {
    S_INITIAL.next = &S_INITIAL;
    S_OPEN.next = &S_CAPTURE;
    S_CAPTURE.next = &S_FLUSH;
    S_FLUSH.next = &S_OPEN;
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
    log(c);
}

void log (Ultra *u) {
    char c[128];
    sprintf(c, "ultra(%s): v=%d, base=%d, quiet=%lu", u->def.name, u->val.v, u->val.base, u->val.quiet_at);
    log(c);
}

void log(State *s) {
    char c[128];
    sprintf(c, "state(%s): EMPTY", s->name);
    log(c);
}

// util

void noop() {
}

void heartbeat() {
    digitalWrite(12, digitalRead(12) ^ 1);
}
