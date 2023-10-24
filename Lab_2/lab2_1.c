#include "Arduino.h"

#define LED_PIN 11
#define ONE_VOLT 51

void setup()
{
  // настраиваем вывод со светодиодом в режим выхода,
  pinMode(LED_PIN, OUTPUT);
}
 
void loop()
{
  // напряжение на светодиод
  // (ШИМ-сигнал).
  // Микроконтроллер переводит число от 0 до 255 к напряжению
  // от 5В до 0В на протяжении 1 секунды
  for(int i = 5; i > -1; i--){
    analogWrite(LED_PIN, ONE_VOLT * i);
    // длительность яркости 200 миллисекунд
    delay(200);
  }
}