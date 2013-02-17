#include <Servo.h>

Servo servo_0;
Servo servo_1;
Servo servo_2;

int PORT_0 = 8;
int PORT_1 = 9;
int PORT_2 = 10;
int OPEN = 50;
int CLOSED = 160;
int state = OPEN;

void setup() {
  Serial.begin(9600);
  servo_0.attach(PORT_0);
  servo_1.attach(PORT_1);
  servo_2.attach(PORT_2);
  
  open();
  delay(3000);
  close();
}

void open() {
  open(servo_0);
  delay(1000);
  open(servo_1);
  delay(1000);
  open(servo_2);
}

void close() {
  close(servo_2);
  delay(1000);
  close(servo_1);
  delay(1000);
  close(servo_0);
}

void loop() {
  delay(2000);
  open();
  delay(2000);
  close();
}

void open(Servo s) {
  angle(s, OPEN);
}

void close(Servo s) {
  angle(s, CLOSED);
}


void angle(Servo s, int a) {
  log("angle: ", a);
  s.write(a);
}

void log(char* s, int v) {
  Serial.print(s);
  Serial.println(v, DEC);
}
