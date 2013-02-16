#include <Servo.h>
#include <IRremote.h>

#define PIN_T0 2
#define PIN_T1 5

#define C_HEARTBEAT "."
#define C_T0_ACTIVE "0"
#define C_T1_ACTIVE "1"

Servo d0;
Servo d1;
Servo d2;
IRsend ir;
unsigned long last;
int t[2];

void setup() {
    Serial.begin(9600);
    d0.attach(8);
    d1.attach(9);
    d2.attach(10);
    pinMode(PIN_T0, INPUT);
    pinMode(PIN_T1, INPUT);
    ir.enableIROut(38);
    ir.mark(0);
    t[0] = t[1] = HIGH;
    last = millis();
    dance();
}

void loop() {
    if (quantum()) clear();
    for (;Serial.available() > 0;) in();
    trips();
}

int quantum() {
    if (millis() - last < 1000) return 0;
    last = millis();
    return 1;
}

void clear() {
    send(C_HEARTBEAT);
    t[0] = HIGH;
    t[1] = HIGH;
}

void trips() {
    trips(PIN_T0, 0, C_T0_ACTIVE);
    trips(PIN_T1, 1, C_T1_ACTIVE);
}

void trips(int pin, int i, char* code) {
    if (digitalRead(pin) == HIGH) return;
    if (t[i] == LOW) return;
    t[i] = LOW;
    send(code);
}

// Not used.
void in() {
    int b = Serial.read();
    if (b == 'A') open(d0);
    if (b == 'B') open(d1);
    if (b == 'C') open(d2);
    if (b == 'a') close(d0);
    if (b == 'b') close(d1);
    if (b == 'c') close(d2);
}

void send(char *code) {
    Serial.write(code);
}

void close(Servo s) {
    angle(s, 50);
}

void open(Servo s) {
    angle(s, 160);
}

void angle(Servo s, int a) {
    s.write(a);
}

void dance() {
    close(d0); delay(300);
    close(d1); delay(300);
    close(d2); delay(300);
     open(d0); delay(300);
     open(d1); delay(300);
     open(d2); delay(300);
    close(d0); delay(300);
    close(d1); delay(300);
    close(d2); delay(300);
}
