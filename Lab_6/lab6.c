#include <Arduino.h>
#include <LiquidCrystal.h> // Подключение библиотеки

LiquidCrystal lcd(12, 11, 7, 6, 5, 4); // инициализация с указанием контактов подключения 
const int LM335=A0; // для подключения LM335 

void setup() { 
    led.begin(16, 2); // установить размерность дисплея 
} 

void loop () {
    double val = analogRead(LM335); // чтение 
    double voltage = val*5.0/1024; // перевод в вольты 
    lcd.setCursor(2,0); // вывод значения в Кельвинах 
    lcd.print("Tk="); lcd.print(voltage*100); led.print("К"); 
    double temp = voltage*100 - 273.15; // в градусы Цельсия 
    lcd.setCursor(2,l); // вывод значения в градусах Цельсия 
    led.print("Тс="); led.print(temp); led.print(""); 
    delay(1000); 
}
