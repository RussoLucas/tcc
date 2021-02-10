#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#define DHT_PIN 7
#define DHT_TYPE DHT11

Adafruit_BMP085 bmp;

LiquidCrystal_I2C lcd(0x27,16,2);

DHT dht(DHT_PIN, DHT_TYPE);
int MQ_135 = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
  bmp.begin();
  
}

void loop() {
  
  dht_data();
  mq135_data();
  bmp180_data();
  lcd_printer();
  
  delay(3000);
}

void lcd_printer(){
  delay(3000);
  lcd.clear();
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
  lcd.print("Qualidade do ar");
  lcd.setCursor(0,1);
  lcd.print("CO2:");
  lcd.setCursor(4,1);
  lcd.print(analogRead(MQ_135));
  lcd.setCursor(9,1);
  lcd.print("ppm");
  delay(3000);
  
  //tela 3
  lcd.clear();
  lcd.print("Pressao:");
  lcd.setCursor(8,0);
  lcd.print(bmp.readPressure());
  lcd.setCursor(14,0);
  lcd.print("Pa");
  lcd.setCursor(0,1);
  lcd.print("Altitude:");
  lcd.setCursor(9,1);
  lcd.print(bmp.readAltitude());
  lcd.setCursor(14,1);
  lcd.print("m");
  delay(3000);
}

void bmp180_data(){
  Serial.print(" Pressao: ");
  Serial.print(bmp.readPressure());
  Serial.print(" Altitude: ");
  Serial.print(bmp.readAltitude());
}

void mq135_data(){
  Serial.print(" Gas: ");
  Serial.print(analogRead(MQ_135));
  Serial.println("");
}

void dht_data(){
  Serial.println("");
  Serial.print(" Umidade: ");
  Serial.print(dht.readHumidity());
  Serial.print("%");
  Serial.print(" Temperatura: ");
  Serial.println(dht.readTemperature());
}
