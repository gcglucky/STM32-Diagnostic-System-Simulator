#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include "DHT.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Définitions des broches (Reconstitué d'après le prototype)
#define TRIG PD6
#define ECHO PC0
#define DHTPIN PA0
#define DHTTYPE DHT11
#define chipSelect PA4
#define LED_DISTANCE_PIN PB11
#define BUZZER_PIN PD1
#define LED_TEMP_PIN PB0
#define LDR_PIN PB1
#define SDA_PIN PB9
#define SCL_PIN PB8

// Initialisation des Périphériques
TinyGPSPlus gps;
HardwareSerial SerialGPS(PA3, PA2);
File myFile;
RTC_DS3231 rtc;
DHT dht(DHTPIN, DHTTYPE);

const char* fichierLOG = "datalog.txt";

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600);
  
  // Configuration des broches
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_DISTANCE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_TEMP_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  // Initialisation des bus et capteurs
  dht.begin();
  if (!SD.begin(chipSelect)) {
    Serial.println("Erreur d'initialisation de la carte SD.");
  }
  if (!rtc.begin()) {
    Serial.println("Erreur RTC non trouvée.");
  }
}

// Fonction d'horodatage et d'écriture sur la carte SD
void logEvenement(String type, String message) {
  DateTime now = rtc.now();
  myFile = SD.open(fichierLOG, FILE_WRITE);
  if (myFile) {
    myFile.print(F("["));
    if(now.hour() < 10) myFile.print(F("0")); myFile.print(now.hour()); myFile.print(F(":"));
    if(now.minute() < 10) myFile.print(F("0")); myFile.print(now.minute()); myFile.print(F(":"));
    if(now.second() < 10) myFile.print(F("0")); myFile.print(now.second());
    myFile.print(F("] "));
    myFile.print(type);
    myFile.print(F(" - "));
    myFile.println(message);
    myFile.close();
  }
}

void loop() {
  // Routine principale d'acquisition des données (Simulée)
  // 1. Lecture GPS (TinyGPS++)
  // 2. Lecture Température/Humidité (DHT11)
  // 3. Mesure de distance (HC-SR04)
  // 4. Appel de logEvenement() si un seuil est franchi
  delay(2000);
}
