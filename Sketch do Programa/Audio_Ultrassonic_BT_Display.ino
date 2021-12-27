#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <NewPing.h>
#include "DFRobotDFPlayerMini.h"

SoftwareSerial BT (11,10);// RX, TX
SoftwareSerial MP3Serial(13, 12); //RX, TX

#define endereco 0x27
#define colunas 16
#define linhas 2
#define trigger 8 //cinza
#define echo 9 //roxo
#define distancia_max 200
#define volumeMP3 30

NewPing sonar (trigger, echo, distancia_max);
LiquidCrystal_I2C lcd (endereco, colunas, linhas);

DFRobotDFPlayerMini playerMP3;

char texto;
float distancia;

void setup() {
  
  MP3Serial.begin(9600);
  BT.begin(9600);

  playerMP3.begin(MP3Serial);
  playerMP3.volume(volumeMP3);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(3, 0);
  lcd.print("iniciando");
  delay(1500);
  lcd.clear();

  lcd.setCursor(4, 0);
  lcd.print("Projeto");
  lcd.setCursor(1, 1);
  lcd.print("Greifen - 2021");
  
}

void loop() {

if (BT.available()) {
  
    texto = BT.read();
    lcd.print(texto);

      if(texto=='@'){
        lcd.clear();
        playerMP3.playFolder(1, 1);}

      if(texto=='#'){
        lcd.backlight();  
        lcd.clear();
        playerMP3.playFolder(1, 2);}

      if(texto=='$'){
        lcd.noBacklight();
        lcd.clear();
        playerMP3.playFolder(1, 3);}

      if(texto=='.'){
        lcd.setCursor(0, 1);
        playerMP3.playFolder(1, 6);}

}

 else if(texto=='*'){
  
       distancia = sonar.ping_cm(); 
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Approximation:");
       lcd.setCursor(5,1);
       lcd.print(distancia);

       delay(250); }
}
