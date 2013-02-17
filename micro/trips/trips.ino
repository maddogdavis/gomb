#include <IRremote.h>

#define PIN_IR 3
#define PIN_DETECT_0 2
#define PIN_DETECT_1 5
#define PIN_STATUS_0 13
#define PIN_STATUS_1 12

IRsend irsend;
void setup()
{
  pinMode(PIN_DETECT_0, INPUT);
  pinMode(PIN_DETECT_1, INPUT);
  pinMode(PIN_STATUS_0, OUTPUT);
  pinMode(PIN_STATUS_1, OUTPUT);
  Serial.begin(9600);
  irsend.enableIROut(38);
  irsend.mark(0);
}

void loop() {
    digitalWrite(PIN_STATUS_0, digitalRead(PIN_DETECT_0));
    digitalWrite(PIN_STATUS_1, digitalRead(PIN_DETECT_1));
}
