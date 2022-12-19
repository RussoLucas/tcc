#define BLYNK_USE_DIRECT_CONNECT
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(10, 11); // RX, TX

//#define BLYNK_PRINT DebugSerial Configurações para conexão com o Blynk

#include <BlynkSimpleSerialBLE.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <SD.h>

#define DHT_PIN 7 //Definição de pinos dos sensores
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

int MQ_135 = A0;

Adafruit_BMP085 bmp;

LiquidCrystal_I2C lcd(0x27,20,4);

char auth[] = "nJZTjEvsx70lQil9Fu3QcWKop_QxbFdP"; //Código de acesso ao Blynk

const int chipSelect = 4;

void LcdPrint() {
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Umidade:");
  lcd.setCursor(9,0);
  lcd.print(dht.readHumidity(),0);
  lcd.setCursor(11,0);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temperatura:");
  lcd.setCursor(12,1);
  lcd.print(dht.readTemperature(),0);
  lcd.setCursor(15,1);
  lcd.print("C");
  delay(3000);
  
  //tela 2
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gas: ");
  lcd.setCursor(5,0);
  lcd.print(analogRead(MQ_135));
  lcd.setCursor(8,0);
  lcd.print("ppm");
  delay(3000);
  
  //tela 3
  lcd.clear();
  lcd.print("Pressao:");
  lcd.setCursor(8,0);
  lcd.print(bmp.readPressure());
  lcd.setCursor(0,1);
  lcd.print("Altitude:");
  lcd.setCursor(9,1);
  lcd.print(bmp.readAltitude());
  lcd.setCursor(14,1);
  lcd.print("m");
  delay(3000);
}

void salvaSD(){
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.print("Umidade: ");
    dataFile.print(dht.readHumidity());
    dataFile.print("; Temperatura: ");
    dataFile.print(dht.readTemperature());
    dataFile.print("; Pressão: ");
    dataFile.print(bmp.readPressure());
    dataFile.print("; Altitude: ");
    dataFile.print(bmp.readAltitude());
    dataFile.print("; Gas: ");
    dataFile.print(analogRead(A0));
    dataFile.print(";\n");
    dataFile.close();
  }
}

void setup(){
  DebugSerial.begin(9600);
  Serial.begin(9600);
  dht.begin();
  bmp.begin();
  Blynk.begin(Serial, auth);

  
  lcd.init();                     
  lcd.init();
  lcd.backlight();

  SD.begin(chipSelect);
}

void loop()
{
  Blynk.run();

  Blynk.virtualWrite(V1,dht.readHumidity());
  Blynk.virtualWrite(V2,analogRead(MQ_135));
  Blynk.virtualWrite(V3,bmp.readPressure());
  Blynk.virtualWrite(V4,bmp.readAltitude());
  Blynk.virtualWrite(V5,dht.readTemperature());

  LcdPrint();
  salvaSD();
   
  delay(3000);
}
