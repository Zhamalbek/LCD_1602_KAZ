#include <Wire.h> 
#include <LCD_1602_KAZ.h> 

LCD_1602_KAZ LCD(0x27,16,2);


void setup() {
    Serial.begin(9600);   
   LCD.init(); 
   LCD.backlight();
   
   LCD.setCursor(2,0); 
   LCD.print("Сәлем Tarru!!!"); 
   
   LCD.setCursor(1,1);
   LCD.print("arduino қазақша"); 
   
}

void loop() {
 
}
