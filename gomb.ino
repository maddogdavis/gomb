#include <Servo.h>
#include <IRremote.h>

#define C_HEARTBEAT "."
#define C_RESET "*"

#define MS_BEAT 1000
#define MS_QUIET 300000
#define MS_SETTLE 1000

Servo s0;
Servo s1;
Servo s2;

typedef struct {
    int pin;
    int active;
    int quiet;
    int prev;
    char *acode;
    char *qcode;
    unsigned long ms;
} Trip;

typedef struct {
    int pin;
    Servo servo;
} Door;

IRsend ir;
unsigned long msbeat;
unsigned long mssettled;
Door d[3] = {
    {  8, s0 },
    {  9, s1 },
    { 10, s2 }
};
Trip t[2] = {
    { 2, HIGH, HIGH, LOW, "R", "r", millis() },
    { 5, HIGH, HIGH, LOW, "S", "s", millis() }
};

void setup() {
    Serial.begin(9600);
    d[0].servo.attach(d[0].pin);
    d[1].servo.attach(d[1].pin);
    d[2].servo.attach(d[2].pin);
    pinMode(t[0].pin, INPUT);
    pinMode(t[1].pin, INPUT);
    ir.enableIROut(38);
    ir.mark(0);
    dance();
    msbeat = millis();
    mssettled = millis();
    send(C_RESET);
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
    trip(0);
    trip(1);
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

void trip(int i) {
    trip(t[i].pin, i, t[i].acode); 
}

void trip(int pin, int i, char* code) {
    if (!is_settled()) return;
    if (tripped(pin) == HIGH) return;
    if (t[i].active == LOW) return;
    t[i].active = t[i].quiet = LOW;
    t[i].ms = millis();
    send(code);
}

int tripped(int pin) {
    if (digitalRead(pin) == HIGH) return HIGH;
    delay(5);
    if (digitalRead(pin) == HIGH) return HIGH;
    delay(5);
    if (digitalRead(pin) == HIGH) return HIGH;
    delay(5);
    if (digitalRead(pin) == HIGH) return HIGH;
    delay(5);
    if (digitalRead(pin) == HIGH) return HIGH;
    return LOW;
}

void quiescent(int i) {
    if (t[i].quiet == t[i].prev) return;
    t[i].prev = t[i].quiet;
    if (t[i].quiet == LOW) return;
    send(t[i].qcode);
}

void command() {
    command(Serial.read());
}

void command(int b) {
    if (b == 'A') open(0);
    if (b == 'B') open(1);
    if (b == 'C') open(2);
    if (b == 'a') close(0);
    if (b == 'b') close(1);
    if (b == 'c') close(2);
}

void send(char *code) {
    Serial.write(code);
}

void open(int i) {
    angle(d[i].servo, 160);
}

void close(int i) {
    angle(d[i].servo, 50);
}

void angle(Servo s, int a) {
    s.write(a);
    mssettled = millis();
}

void dance() {
    close(0); delay(300);
    close(1); delay(300);
    close(2); delay(300);
     open(0); delay(300);
     open(1); delay(300);
     open(2); delay(300);
    close(0); delay(300);
    close(1); delay(300);
    close(2); delay(300);
}
