//Reference from - https://diyprojects.io/using-i2c-128x64-0-96-ssd1306-oled-display-arduino/#.WxaqpUxuKP8
//Personal project done during my free time using Arduino Nano, MPU6050 and 128X64 I2C OLED
//Combined two reference codes from accelerometer and adafruit oled to interface between these two components and the microcontroller
//Requires Adafruit LED libraries and <wire.h> library for I2C communication

//Import Libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16

//Define Variables
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup(){
    Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");

  //Text display tests
  //For Accel
  //Displays "AcX: "
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("AcX: ");
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //Displays the value of AcX
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,0);
  display.println(AcX);
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //Displays "AcY: "
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("AcY: ");
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //Displays the value of AcY   
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,10);
  display.println(AcY);
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //Displays "AcZ: "
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("AcZ: ");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  
  //Displays the value of AcZ
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,20);
  display.println(AcZ);
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //For Gyro
  //Displays "GyX: "
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(64,0);
  display.println("GyX: ");
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //Displays the value of GyX
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(86,0);
  display.println(GyX);
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //Displays "GyY: "
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(64,10);
  display.println("GyY: ");
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //Displays the value of GyY
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(86,10);
  display.println(GyY);
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  //Displays "GyZ: "
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(64,20);
  display.println("GyZ: ");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  
  //Displays the value of GyZ
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(86,20);
  display.println(GyZ);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  
  //Hold the data on the screen for 300 milli seconds and then reset the display for the next loop
  display.display();
  delay(300);
  display.clearDisplay();
}
