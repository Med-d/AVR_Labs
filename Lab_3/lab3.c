#include "Arduino.h"
#include <Stepper.h>

void loop(){
    digitalWrite(pin7,HIGH);   //вывод#7 высокий уровень
    digitalWrite(pin8,LOW);    // вывод #8 низкий уровень
    delay(4000);               //Задержка 4 секунды двигатель rotates in clock wise direction
    digitalWrite(pin7,LOW);    // вывод #7 низкий уровень
    digitalWrite(pin8,LOW);    // вывод #8 низкий уровень
    delay(2000);               // Задержка 2 секунды  Motor halts
    digitalWrite(pin8,HIGH);   // вывод #8 высокий уровень
    digitalWrite(pin7,LOW);    // вывод #7 низкий уровень
    delay(5000);               // Задержка 5 секунд  двигатель rotates in anti clock wise direction
    digitalWrite(pin7,LOW);    // вывод #7 низкий уровень
    digitalWrite(pin8,LOW);    // вывод #8 низкий уровень
    delay(3000);               // Задержка 3 секунды  Motor останов
}