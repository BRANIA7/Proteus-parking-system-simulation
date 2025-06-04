#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Ultrasonic.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

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
File sdFile;
String files;

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
  Serial.println("SD initialization done.");

  lcd.init();
  gateServo.attach(SERVO_PIN);
  lcd.backlight();
  lcd.print("WELCOME!");
  lcd.setCursor(0, 1);
  lcd.print("Wait for allocation");
  Serial.println("Entry toll serial logs: \n");
  wirelessSerial.begin(19200);
  wirelessSerial.print("THIS IS A SIMULATED CAMERA");
  gateServo.write(0);
}

void loop() {

  readSonar();
  // readFile();
}

void readFile() {
  sdFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (sdFile) {
    Serial.print("Writing to test.txt...");
    sdFile.println("testing 1, 2, 3.");
    // close the file:
    sdFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  sdFile = SD.open("test.txt");
  if (sdFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (sdFile.available()) {
      Serial.write(sdFile.read());
    }
    // close the file:
    sdFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void readSonar() {
  long distance = sonar.ping_cm();

  if (distance <= 100) {
    Serial.println("Car has been detected >> ");
    Serial.print("Distance = ");
    Serial.println(distance);
    Serial.println();

    if (readCameraSerial()) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No: " + entry.license);
      lcd.setCursor(0, 1);
      lcd.print("SLOT: " + String(entry.parkingSpot));
      Serial.println("OPENING GATE");
      while (sonar.ping_cm() < 100) {
        gateServo.write(90);
      }
    }
  }
  delay(300);
  Serial.print("CLOSING GATE");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("STAND BY");
  Serial.println();
  gateServo.write(0);
}

bool readCameraSerial() {
  Serial.println("Reading camera values");
  wirelessSerial.println("Generating random License plate");
  delay(300);
  wirelessSerial.println();
  String input = "UAE" + String(random(100,999)) + "B";
  
  if (!validateLicense(input)) {
    Serial.print(input);
    wirelessSerial.print("INVALID LICENSE !!  \t\t TRY AGAIN");
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
    wirelessSerial.print("INVALID LENGTH : " + String(license.length()) );
    return false;
  }
  // if (!isAlpha(license.charAt(6))) {
  //   wirelessSerial.print("INVALID END: " + license.charAt(6));
  //   return false;
  // }
  // if (!isDigit(license.charAt(2))) {
  //   wirelessSerial.print("INVALID MID: " + license.charAt(2));
  //   return false;
  // }

  return true;
}
