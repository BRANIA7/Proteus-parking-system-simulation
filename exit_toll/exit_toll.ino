#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Ultrasonic.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define PIN_TEST 11
#define SERVO_PIN 5
#define USRANGER_PIN 12
#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define MAX_DISTANCE 400
#define RXD 2
#define TXD 3
#define SD_CS 10

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gateServo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
SoftwareSerial wirelessSerial(RXD, TXD);

Ultrasonic ranger(10);

struct Parking {
  String license;
  int parkingSpot;
  long entryTime;
  long exitTime;
};

struct Parking entry;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.init();
  gateServo.attach(SERVO_PIN);
  lcd.backlight();
  lcd.print("EXIT TOLL!");
  lcd.setCursor(0, 1);
  lcd.print("Active");
  Serial.println("Exit toll serial logs: \n");
  wirelessSerial.begin(19200);
  wirelessSerial.print("THIS IS A SIMULATED CAMERA (EXIT)");
  gateServo.write(0);
}

void loop() {

  readSonar();
}


void readSonar() {
  long distance = sonar.ping_cm();

  if (distance <= 100) {
    Serial.println("Exiting Car has been detected >> ");
    Serial.print("Distance = ");
    Serial.println(distance);
    Serial.println();

    if (readCameraSerial()) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No: " + entry.license);
      lcd.setCursor(0, 1);
      entry.exitTime = millis();
      lcd.print("TIME: " + String((entry.exitTime - entry.entryTime)));
      Serial.println("OPENING GATE");
      while (sonar.ping_cm() < 100) {
        gateServo.write(90);
      }
    }
  }
  delay(300);
  Serial.print("CLOSING GATE");
  Serial.println();
  gateServo.write(0);
}

bool readCameraSerial() {
  String input = "";
  Serial.print("Reading camera values");
  Serial.println();
  wirelessSerial.println("Retreiving License plate");
  if(Serial.available() > 0){
    input = Serial.readString();
  }
  delay(300);
  wirelessSerial.print("FOUND: " + input);
  entry.license = input;
  entry.entryTime = 0;
  wirelessSerial.println();
  

  if (!validateLicense(input)) {
    Serial.print(input);
    wirelessSerial.println();
    delay(300);
    readCameraSerial();
  }
  entry.license = input;
  entry.parkingSpot = random(1, 10);
  entry.entryTime = millis();
  entry.exitTime = 0;

  return true;
}

bool validateLicense(String license) {
  if (license.length() != 7) {
    wirelessSerial.print("INVALID LENGTH : " + String(license.length()));
    return false;
  }
  

  return true;
}
