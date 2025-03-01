#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Gina Start ang LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD Type: I2C address, columns, rows 

// Pins sa Arduino
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int piezoPin1  = A0;
const int piezoPin2  = A1;
const int buzzerPin  = 7;
const int rgbRedPin  = 9;
const int rgbGreenPin= 10;
const int rgbBluePin = 11;

// Feature activation (after power wala anay feature ma start)
bool feature1Active = false;
bool feature2Active = false;
bool feature3Active = false;

bool firstRunFeature1 = true;
bool firstRunFeature2 = true;
bool firstRunFeature3 = true;

bool feature2Running = false;
unsigned long feature2StartTime = 0;

//RGB LED State after mag pindot sang third Button
int colorState = 0;

void setup() {
  Serial.begin(9600);

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  pinMode(rgbRedPin, OUTPUT);
  pinMode(rgbGreenPin, OUTPUT);
  pinMode(rgbBluePin, OUTPUT);

  pinMode(piezoPin1, INPUT);
  pinMode(piezoPin2, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Starting LCD
  lcd.init();
  lcd.backlight();

  // Testing ka LCD if ga andar
  lcd.setCursor(0, 0);
  lcd.print("LCD Initialized!");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (digitalRead(button1Pin) == LOW) {
    activateFeature1();
  } else if (digitalRead(button2Pin) == LOW) {
    activateFeature2();
  } else if (digitalRead(button3Pin) == LOW) {
    activateFeature3();
  }

  if (feature1Active) {
    displayFeature1();
  } else if (feature2Active) {
    if (!feature2Running) {
      startFeature2();
    } else {
      if (millis() - feature2StartTime >= 3000) {
        announceFeature2Winner();
        feature2Active = false;  
      }
    }
  } else if (feature3Active) {
    displayFeature3();
  }
}

void activateFeature1() {
  feature1Active = true;
  feature2Active = false;
  feature3Active = false;

  firstRunFeature1 = true;
  feature2Running = false; 

  playActivationTune1(); //Play anay button 1 song before maggwa si feature 1

  digitalWrite(rgbRedPin, HIGH);
  digitalWrite(rgbGreenPin, LOW);
  digitalWrite(rgbBluePin, LOW);

  Serial.println("Feature 1 Activated");
}

void activateFeature2() {
  feature1Active = false;
  feature2Active = true;
  feature3Active = false;

  firstRunFeature2 = true;
  feature2Running = false; 

  playActivationTune2(); //Play anay button 1 song before maggwa si feature 2

  digitalWrite(rgbRedPin, LOW);
  digitalWrite(rgbGreenPin, HIGH);
  digitalWrite(rgbBluePin, LOW);

  Serial.println("Feature 2 Activated");
}

void activateFeature3() {
  feature1Active = false;
  feature2Active = false;
  feature3Active = true;

  firstRunFeature3 = true;

  playActivationTune3(); //Play anay button 1 song before maggwa si feature 3

  digitalWrite(rgbRedPin, LOW);
  digitalWrite(rgbGreenPin, LOW);
  digitalWrite(rgbBluePin, HIGH);

  Serial.println("Feature 3 Activated");
}

void playActivationTune1() {
  // Happy Birthday
  int melody[] = {
    262, 262, 294, 262, 349, 330, 
    262, 262, 294, 262, 392, 349, 
  };
  int noteDurations[] = {
    500, 500, 750, 250, 1000, 1000, 
    500, 500, 750, 250, 1000, 1000,
  };
  int numNotes = sizeof(melody) / sizeof(int);
  playMelodyWithFixedDuration(melody, noteDurations, numNotes, 15000); // 15 seconds
}

void playActivationTune2() {
  // Ba ba black sheep
  int melody[] = {
    294, 294, 392, 392, 440, 440, 392, 
    349, 349, 330, 330, 294,            
  };
  int noteDurations[] = {
    500, 500, 500, 500, 500, 500, 1000,
    500, 500, 500, 500, 1000,
  };
  int numNotes = sizeof(melody) / sizeof(int);
  playMelodyWithFixedDuration(melody, noteDurations, numNotes, 15000); // 15 seconds
}

void playActivationTune3() {
  // Twinkle Twinkle
  int melody[] = {
    262, 262, 392, 392, 440, 440, 392, 
    349, 349, 330, 330, 294, 294, 262, 
  };
  int noteDurations[] = {
    500, 500, 500, 500, 500, 500, 1000,
    500, 500, 500, 500, 500, 500, 1000,
  };
  int numNotes = sizeof(melody) / sizeof(int);
  playMelodyWithFixedDuration(melody, noteDurations, numNotes, 15000); // 15 seconds
}

void playMelodyWithFixedDuration(int *melody, int *noteDurations, int numNotes, int totalDuration) {
  int durationSum = 0;
  for (int i = 0; i < numNotes; i++) {
    durationSum += noteDurations[i];
  }
  int pauseBetweenNotes = 50; 
  durationSum += pauseBetweenNotes * (numNotes - 1);

  float speedFactor = (float)totalDuration / durationSum;

  for (int i = 0; i < numNotes; i++) {
    int adjustedDuration = noteDurations[i] * speedFactor;
    tone(buzzerPin, melody[i], adjustedDuration);
    delay(adjustedDuration);
    delay(pauseBetweenNotes);
  }
}

void startFeature2() {
  if (firstRunFeature2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Feature 2: Game");
    lcd.setCursor(0, 1);
    lcd.print("Get Ready...");
    firstRunFeature2 = false;
    feature2StartTime = millis();
    feature2Running = true;
  }
}

void announceFeature2Winner() {
  int player1Voltage = getAverageReading(piezoPin1);
  int player2Voltage = getAverageReading(piezoPin2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Feature 2: Game");

  lcd.setCursor(0, 1);

  if (player1Voltage > player2Voltage) {
    lcd.print("Player 1 Wins!");
    playVictoryTune1();
  } else if (player2Voltage > player1Voltage) {
    lcd.print("Player 2 Wins!");
    playVictoryTune2();
  } else {
    lcd.print("It's a Tie!");
    playTieTune();
  }

  feature2Running = false;
}

void playVictoryTune1() {
  int melody[] = {523, 587, 659, 698};
  int durations[] = {200, 200, 200, 400};
  playMelodySimple(melody, durations, 4);
}

void playVictoryTune2() {
  int melody[] = {698, 659, 587, 523};
  int durations[] = {200, 200, 200, 400};
  playMelodySimple(melody, durations, 4);
}

void playTieTune() {
  int melody[] = {523, 523, 523};
  int durations[] = {300, 300, 300};
  playMelodySimple(melody, durations, 3);
}

void playMelodySimple(int *melody, int *durations, int numNotes) {
  for (int i = 0; i < numNotes; i++) {
    tone(buzzerPin, melody[i], durations[i]);
    delay(durations[i] + 50);
  }
}

void displayFeature1() {
  if (firstRunFeature1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Feature 1: Volt");
    firstRunFeature1 = false;
  }

  float voltage = getCombinedVoltage();

  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(voltage, 2);
  lcd.print(" V   ");

  int voltageLevel = (int)voltage;
  beepVoltageLevel(voltageLevel);
}

void displayFeature3() {
  if (firstRunFeature3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Feature 3: Piano");
    firstRunFeature3 = false;
  }

  float piezoVoltage1 = getAverageReading(piezoPin1);
  float piezoVoltage2 = getAverageReading(piezoPin2);

  if (piezoVoltage1 > 0.60 || piezoVoltage2 > 0.60) {
    tone(buzzerPin, 1000, 500);
    switchColor();
  }
}

float getCombinedVoltage() {
  float avgVoltage1 = getAverageReading(piezoPin1);
  float avgVoltage2 = getAverageReading(piezoPin2);
  return (avgVoltage1 + avgVoltage2) / 2.0;
}

float getAverageReading(int pin) {
  const int numReadings = 5;
  int readings[numReadings];
  int sum = 0;

  for (int i = 0; i < numReadings; i++) {
    readings[i] = analogRead(pin);
    sum += readings[i];
    delay(5);
  }
  return (float)sum / numReadings * (5.0 / 1023.0);
}

void switchColor() {
  colorState = (colorState + 1) % 3;

  switch (colorState) {
    case 0:
      digitalWrite(rgbRedPin, HIGH);
      digitalWrite(rgbGreenPin, LOW);
      digitalWrite(rgbBluePin, LOW);
      break;
    case 1:
      digitalWrite(rgbRedPin, LOW);
      digitalWrite(rgbGreenPin, HIGH);
      digitalWrite(rgbBluePin, LOW);
      break;
    case 2:
      digitalWrite(rgbRedPin, LOW);
      digitalWrite(rgbGreenPin, LOW);
      digitalWrite(rgbBluePin, HIGH);
      break;
  }

  Serial.println("RGB Color Switched");
}

void beepVoltageLevel(int level) {
  for (int i = 0; i < level; i++) {
    tone(buzzerPin, 1000, 200);
    delay(300);
  }
}
