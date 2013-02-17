#include <Servo.h>
#include <IRremote.h>

#define PIN_T0 2
#define PIN_T1 5

#define C_HEARTBEAT "."
#define C_T0_ACTIVE "R"
#define C_T1_ACTIVE "S"

#define MS_BEAT 1000
#define MS_QUIET 20000
#define MS_SETTLE 5000

unsigned long remove = millis();

typedef struct {
    int active;
    int quiet;
    int prev;
    char *code;
    unsigned long ms;
} Trip;

Servo d0;
Servo d1;
Servo d2;
IRsend ir;
unsigned long msbeat = millis();
unsigned long mssettled = millis();
Trip t[2] = {
    { HIGH, HIGH, LOW, "r", millis() },
    { HIGH, HIGH, LOW, "s", millis() }
};

void setup() {
    Serial.begin(9600);
    d0.attach(8);
    d1.attach(9);
    d2.attach(10);
    pinMode(PIN_T0, INPUT);
    pinMode(PIN_T1, INPUT);
    ir.enableIROut(38);
    ir.mark(0);
    dance();
    delay(2000);
}

void loop() {
    times();
    consume();
    trips();
}

void times() {
    if (is_beat()) beat();
    if (is_quiet(0)) quiet(0);
    if (is_quiet(1)) quiet(1);
}

int available() {
    return Serial.available() > 0;
}

void consume() {
    if (!available()) return;
    for(;available();)
        command();
}

void trips() {
    trips(PIN_T0, 0, C_T0_ACTIVE);
    trips(PIN_T1, 1, C_T1_ACTIVE);
}

int is_beat() {
    return past(msbeat, MS_BEAT);
}

int is_quiet(int i) {
    return past(t[i].ms, MS_QUIET);
}

int is_settled() {
    return past(mssettled, MS_SETTLE);
}

int past(unsigned long v, unsigned long p) {
    return millis() - v > p;
}

void beat() {
    send(C_HEARTBEAT);
    t[0].active = t[1].active = HIGH;
    msbeat = millis();
}

int quiet(int i) {
    quiescent(i);
    t[i].quiet = HIGH;
}

void trips(int pin, int i, char* code) {
    if (!is_settled()) return;
    if (digitalRead(pin) == HIGH) return;
    if (t[i].active == LOW) return;
    t[i].active = t[i].quiet = LOW;
    t[i].ms = millis();
    send(code);
}

void quiescent(int i) {
    if (t[i].quiet == t[i].prev) return;
    t[i].prev = t[i].quiet;
    if (t[i].quiet == LOW) return;
    send(t[i].code);
}

void command() {
    command(Serial.read());
}

void command(int b) {
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
