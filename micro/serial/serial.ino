void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        int b = Serial.read();
        if (b == 65) {
            digitalWrite(13, LOW);
        } else {
            digitalWrite(13, HIGH);
        }
    }
}
