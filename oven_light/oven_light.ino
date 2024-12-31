/*
  Arduino Oven light temp detector
  Bevan Weir - 27 Dec 2024
  calibration code from "Project 6 - Light Theremin" by Scott Fitzgerald

*/

// variable to hold sensor value
int sensorValue;
// variable to calibrate low value
int sensorLow = 1023;
// variable to calibrate high value
int sensorHigh = 0;
// onboard LED pin
const int ledPin = 13;
// set the pitch
int pitch = 4000;


void setup() {
  // Make the LED pin an output and turn it on
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // Make the red LED an output
  pinMode(4, OUTPUT);

  // calibrate for the first five seconds after program runs
  while (millis() < 5000) {
    // record the maximum sensor value
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    // record the minimum sensor value
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
  // turn the LED off, signaling the end of the calibration period
  digitalWrite(ledPin, LOW);
}

void loop() {
  //read the input from A0 and store it in a variable
  sensorValue = analogRead(A0);

  if (sensorValue > sensorLow) {
    // turn on the LED on pin 4
    digitalWrite(4, HIGH);
  }

  if (sensorValue < 0.8 * sensorHigh) {
    // play the tone for 20 ms on pin 8
    tone(8, pitch, 20);
    // turn off the red LED
    digitalWrite(4, LOW);
  }

  // wait for a moment
  delay(10);
}
