/*
 * Source from https://www.adafruit.com/products/2857
 * Sensor value display on the LCD 1602 Module
 * Sensor compensation test of Temp
 */
 
#include <Arduino.h>
#include <Wire.h>
#include "Jasper_SHT31.h"
#include <LiquidCrystal_I2C.h>

//ALWAYS USE THIS WITH LCD I2C and Addres 0x3F
#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

Jasper_SHT31 sht31 = Jasper_SHT31();

//int a = 5;

void setup() {
  Serial.begin(9600);

  //while (!Serial)
    //delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  //Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
  
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
}


void loop() {
  
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  //Test Sensor Compensation of temp 
  float a = 2.0; //Set a value
  float c=0; //Set a container 
  c=t+a; //The container include the source temp value with compensation

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); 
    Serial.print(t); //Source value print
    lcd.setCursor(0,0);
    lcd.print("Temp*C=");
    lcd.setCursor(8,0);
    lcd.print(c); // After compensation
    
  } else { 
    Serial.println("Failed to read temperature");
    lcd.setCursor(0,0);
    lcd.print("Temp*C= Break");
  }

  Serial.print(',');
  Serial.print(' ');
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); 
    Serial.print(h);

    lcd.setCursor(0,1);
    lcd.print("Humi %=");
    lcd.setCursor(8,1);
    lcd.print(h);
    
  } else { 
    Serial.println("Failed to read humidity");
    lcd.setCursor(0,1);
    lcd.print("Humi %= Break");
  }
  Serial.println();
  delay(1000);
}
