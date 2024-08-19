#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN 9     
#define SS_PIN 10     

#define TRIGGER_PIN 2 
#define ECHO_PIN 3    

#define SERVO1_PIN 8   
#define SERVO2_PIN 4   

#define LED1_PIN 5      
#define WATER_PUMP_PIN 7 

#define WATER_LEVEL_SENSOR_PIN A0

MFRC522 mfrc522(SS_PIN, RST_PIN);  
Servo servo1;
Servo servo2;

// RFID tag UID you want to allow
byte allowedTagUID[4] = {0xA0, 0x84, 0x2C, 0x0E};

// Timing variables
unsigned long previousMillisGate = 0; 
unsigned long previousMillisFood = 0; 
unsigned long previousMillisWater = 0; 

// Intervals (in milliseconds)
const long gateOpenInterval = 5000; 
const long foodDispenseInterval = 6000;
const long foodDispenseDuration = 3000; 
const long waterPumpInterval = 5000; 

// State variables
bool gateOpen = false; 
bool foodDispensing = false;
bool waterPumpOn = false; 

void setup() {
  Serial.begin(9600); 
  SPI.begin();        
  mfrc522.PCD_Init(); 

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);

  servo1.write(90); // Close the gate initially
  servo2.write(0); // Close the food dispenser initially
}

void loop() {
  unsigned long currentMillis = millis();

  // 1. Main Gate Control
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    if (compareTagUID(mfrc522.uid.uidByte, allowedTagUID)) {
      if (!gateOpen) {
        servo1.write(0); // Open the gate
        gateOpen = true;
        previousMillisGate = currentMillis; 
      }
    }
    mfrc522.PICC_HaltA();
  }

  if (gateOpen && (currentMillis - previousMillisGate >= gateOpenInterval)) {
    servo1.write(90); // Close the gate
    gateOpen = false;
  }

  // 2. Food Dispenser
  if (currentMillis - previousMillisFood >= foodDispenseInterval) {
    previousMillisFood = currentMillis; 

    if (!foodDispensing) {
      servo2.write(45); // Open the food dispenser
      foodDispensing = true;
      previousMillisFood = currentMillis; // Reset timer for dispense duration
    }
  }

  if (foodDispensing && (currentMillis - previousMillisFood >= foodDispenseDuration)) {
    servo2.write(0); // Close the food dispenser
    foodDispensing = false;
  }

  // 3. Food Level Monitoring
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1; // Calculate the distance in centimeters

  if (distance > 16) {
    digitalWrite(LED1_PIN, HIGH); 
    delay(500);        
    digitalWrite(LED1_PIN, LOW); 
    delay(500);        
  } else {
    digitalWrite(LED1_PIN, LOW); 
  }

  // 4. Water Level Control
  int waterLevel = analogRead(WATER_LEVEL_SENSOR_PIN);

  if (waterLevel < 280 && !waterPumpOn) {
    digitalWrite(WATER_PUMP_PIN, HIGH); 
    waterPumpOn = true;
    previousMillisWater = currentMillis; 
  }

  if (waterPumpOn && (currentMillis - previousMillisWater >= waterPumpInterval)) {
    digitalWrite(WATER_PUMP_PIN, LOW); 
    waterPumpOn = false;
  }
}

// Helper function to compare RFID tag UIDs
bool compareTagUID(byte *uid1, byte *uid2) {
  for (byte i = 0; i < 4; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}
