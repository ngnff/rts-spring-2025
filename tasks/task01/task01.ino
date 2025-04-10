void setup () {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

unsigned long timerD3, timerD5, timerD6, timerD9, timerD10;
bool d3, d5, d6, d9, d10;

#define set_strobe(now, pin, period)         \
  if (now - timerD##pin >= period / 2) {     \
    digitalWrite(pin, d##pin ? HIGH : LOW);  \
    d##pin = !d##pin;                        \
    timerD##pin = now;                       \
  }

void loop () {
  unsigned long now = micros();
  set_strobe(now, 10, 50);
  set_strobe(now, 9, 100);
  set_strobe(now, 6, 500);
  set_strobe(now, 5, 1000);
  set_strobe(now, 3, 10000);
}
