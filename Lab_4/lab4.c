#include "Arduino.h"
#include <SPI.h> //подключим библиотеку SPI и инициализируем интерфейс SPI

const int pinSelect = 8; // вывод регистра как ведомого устройства SS. Очистим сдвиговый регистр, задав ему   логический "0". Инициализируем последовательный порт.

void setup() {
    SPI.begin(); // запускаем интерфейс SPI
    pinMode(pinSelect, OUTPUT); // 
    digitalWrite(pinSelect, LOW); // выбор ведомого устройств (регистра)
    SPI.transfer(0); // стираем содержимое регистра
    digitalWrite(pinSelect, HIGH); // конец передачи сообщения
    Serial.begin(9600); //число бод
}

void loop() { //делаем пересчет светодиодов от 0 до7
    for (int i=0; i<8; i++) {    
        double L = pow(2, i); // вычисляем активный светодиод, функция pow(основание, степень) возводит 2 в степень счётчика цикла.                 
        int leds = round(L); // округляем до целого числа
        digitalWrite(pinSelect, LOW); // выбор нашего регистра сдвига 74HC595
        SPI.transfer(leds); // передаём получившееся значение в сдвиговый регистр
        digitalWrite(pinSelect, HIGH); // конец передачи
        Serial.println(leds, BIN); // вывод в двоичном представлении
        delay(250); // задержка 250 миллисекунд
    }
    Serial.println("--------");
}
