#include <Arduino.h>
#include <NewPing.h>

#define MAX_DISTANCE 2          // Maximum measurable distance in cm
#define MIN_THRESHOLD_TIME 1500 // Threshold time for fast vehicle (in milliseconds)
#define MID_THRESHOLD_TIME 3000 // Upper threshold time for medium-speed vehicle (in milliseconds)
#define YELLOW_WARNING_TIME 2000 // Yellow warning duration in milliseconds

const int lane1Trig1 = 5, lane1Echo1 = 18, lane1Trig2 = 19, lane1Echo2 = 21;

const int lane1Red = 23, lane1Yellow = 33, lane1Green = 22;

const int pedestrianButtonPin = 13;  // Pedestrian button
const int emergencySwitchPin = 15;   // Emergency switch

NewPing lane1Sensor1(lane1Trig1, lane1Echo1, MAX_DISTANCE);
NewPing lane1Sensor2(lane1Trig2, lane1Echo2, MAX_DISTANCE);

bool pedestrianTriggered = false;

void setup() {
  Serial.begin(115200);

  // Configure LED pins
  pinMode(lane1Red, OUTPUT);
  pinMode(lane1Yellow, OUTPUT);
  pinMode(lane1Green, OUTPUT);

  // Configure button and emergency switch pins
  pinMode(pedestrianButtonPin, INPUT_PULLUP);
  pinMode(emergencySwitchPin, INPUT_PULLUP);

  // Initialize LEDs to off
  resetAllLights();
}

void loop() {
  // Check if the pedestrian button is pressed
  if (digitalRead(pedestrianButtonPin) == LOW) {
    pedestrianTriggered = true;
    Serial.println("Pedestrian button pressed");
  } else {
    Serial.println("No pedestrian trigger");
    delay(1000); // Short delay to avoid excessive printing
    return;      // Skip the rest of the loop if no pedestrian trigger
  }

  // Check if the emergency switch is activated
  if (digitalRead(emergencySwitchPin) == LOW) {
    Serial.println("Emergency switch activated");
    handleEmergencySequence();
    return; // Skip the rest of the loop if emergency is active
  }

  // If pedestrian crossing is requested, handle the traffic light sequence based on speed
  if (pedestrianTriggered) {
    controlTrafficBasedonSpeed();
    pedestrianTriggered = false; // Reset after processing
  }
}

// Function to handle the emergency light sequence (Red -> Yellow -> Green)
void handleEmergencySequence() {
  // Red light on for emergency
  digitalWrite(lane1Red, HIGH);
  Serial.println("Red light ON (Emergency)");
  delay(5000); // Keep red light on for 5 seconds
  digitalWrite(lane1Red, LOW);

  // Yellow light on after red
  digitalWrite(lane1Yellow, HIGH);
  Serial.println("Yellow light ON (Emergency)");
  delay(5000); // Keep yellow light on for 5 seconds
  digitalWrite(lane1Yellow, LOW);

  // Green light on after yellow
  digitalWrite(lane1Green, HIGH);
  Serial.println("Green light ON (Emergency)");
  delay(5000); // Keep green light on for 5 seconds
  digitalWrite(lane1Green, LOW);

  Serial.println("Emergency sequence completed");
}

// Function to measure speed and control lights based on travel time
void controlTrafficBasedonSpeed() {
  unsigned long lane1TravelTime = measureTravelTime(lane1Sensor1, lane1Sensor2);

  // Yellow warning light before switching to green or red
  digitalWrite(lane1Yellow, HIGH);
  Serial.println("Yellow light ON (Warning)");
  delay(YELLOW_WARNING_TIME);
  digitalWrite(lane1Yellow, LOW);

  // Traffic control based on travel time thresholds
  if (lane1TravelTime < MIN_THRESHOLD_TIME) { // Fast vehicle (under 1.5 seconds)
    Serial.println("Fast vehicle detected - Red light ON");
    digitalWrite(lane1Red, HIGH);
  } else if (lane1TravelTime >= MIN_THRESHOLD_TIME && lane1TravelTime < MID_THRESHOLD_TIME) { // Medium-speed vehicle
    Serial.println("Medium-speed vehicle detected - Green light ON");
    digitalWrite(lane1Green, HIGH);
  } else { // Slow vehicle
    Serial.println("Slow vehicle detected - Red light ON");
    digitalWrite(lane1Red, HIGH);
  }

  delay(5000); // Keep light on for 5 seconds before resetting
  resetAllLights(); // Reset lights after processing
}

// Measure time between two sensors for lane 1
unsigned long measureTravelTime(NewPing sensor1, NewPing sensor2) {
  unsigned long startTime = 0, endTime = 0;

  if (sensor1.ping_cm() > 0) { // Detect vehicle on sensor 1
    startTime = millis();
    Serial.println("First sensor detected vehicle");

    while (sensor2.ping_cm() == 0); // Wait for vehicle to pass second sensor
    endTime = millis();
    Serial.println("Second sensor detected vehicle");
  }

  unsigned long travelTime = (endTime > startTime) ? (endTime - startTime) : (MID_THRESHOLD_TIME + 1);
  return travelTime;
}

// Function to reset all lights
void resetAllLights() {
  digitalWrite(lane1Red, LOW);
  digitalWrite(lane1Yellow, LOW);
  digitalWrite(lane1Green, LOW);
}
