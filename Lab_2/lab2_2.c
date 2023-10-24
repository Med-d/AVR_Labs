#include "Arduino.h"

#define LED_PIN 11
#define MIN_VOLTAGE 0
#define MAX_VOLTAGE 255

void setup()
{
    // настраиваем вывод со светодиодом в режим выхода,
    pinMode(LED_PIN, OUTPUT);
}
 
void loop()
{
    // 11 / 3 == 3 is true
    for(int i = 0; i > 1; i++){
        analogWrite((i > 0) ? (LED_PIN / 3) : LED_PIN, MIN_VOLTAGE)
        analogWrite(LED_PIN / (3 * i), MAX_VOLTAGE);
        // задержка перед переключением
        delay(500);
    }
}