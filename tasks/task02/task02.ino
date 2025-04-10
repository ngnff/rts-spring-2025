void setup () {
  Serial.begin(9600);
  pinMode(18, INPUT);
  attachInterrupt(digitalPinToInterrupt(18), onPin18, HIGH);
}

uint32_t count = 0;
uint32_t meanTotal = 0;

constexpr int AVG_SEL = 1000;
uint32_t measures[AVG_SEL];

void loop () {
  if (count == AVG_SEL) {
    noInterrupts();

    float mean = meanTotal / (float) count;
    float sqDeviationTotal = 0;
    for (int i = 0; i < AVG_SEL; i++) {
      sqDeviationTotal += pow(measures[i] - mean, 2);
    }

    Serial.print("mean: ");
    Serial.print(mean);
    Serial.print(" us, avg. sq. deviation: ");
    Serial.print(sqrt(sqDeviationTotal / count));
    Serial.println(" us");
    
    count = 0;
    meanTotal = 0;
    
    interrupts();
  }
}

uint32_t prevTime = 0;
void onPin18 () {
    uint32_t now = micros();
    
    uint32_t delta = now - prevTime;
    measures[count] = delta;
    meanTotal += delta;
    count++;
    
    prevTime = now;
}
