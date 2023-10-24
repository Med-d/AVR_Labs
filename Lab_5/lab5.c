#include <Arduino.h>
#include <Servo.h>

class Flasher
{
    // Переменные и составляющие класса устанавливаются при запуске
    int ledPin; // Вывод со светодиодом
    long OnTime; // длительность включения в миллисекундах
    long OffTime; // длительность включения в миллисекундах 
    // Контроль текущего состояния
    int ledState; // устанавливает текущее состояние светодиода
    unsigned long previousMillis; // время последнего обновления состояния светодиода
    // Конструктор - создает объект Flasher, инициализирует переменные-составляющие, состояние
    
    public:

    Flasher(int pin, long on, long off)
    {
        ledPin = pin;
        pinMode(ledPin, OUTPUT);
        OnTime = on;
        OffTime = off;
        ledState = LOW; 
        previousMillis = 0;
    }

    void Update(unsigned long currentMillis)
    {
        if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
        {
                ledState = LOW; // ВЫКЛ
                previousMillis = currentMillis; // Save  время
                digitalWrite(ledPin, ledState); // Обновление  светодиода
        }
        else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
        {
            ledState = HIGH; // Включение
            previousMillis = currentMillis; // Save время
            digitalWrite(ledPin, ledState); // Обновленисветодиода
        }
    }
};

class Sweeper
{
    Servo servo; // объект servo
    int pos; // текущее положение сервопривода
    int increment; // определяем увеличение перемещения на каждом интервале
    int updateInterval; // определяем время между обновлениями
    unsigned long lastUpdate; // определяем последнее обновление положения
    public: 
    
    Sweeper(int interval)
    {
        updateInterval = interval;
        increment = 1;
    }
    
    void Attach(int pin)
    {
        servo.attach(pin);
    }
   
    void Detach()
    {
        servo.detach();
    }
    
    void reset() 
    { 
        pos = 0;
        servo.write(pos);
        increment = abs(increment);
    }
    void Update(unsigned long currentMillis)
    {
        if((currentMillis - lastUpdate) > updateInterval) //время обновиться
        {
            lastUpdate = millis();
            pos += increment;
            servo.write(pos);
            if ((pos >= 180) || (pos <= 0)) // запускаем конец вращения
            {
                // запускаем обратное направление
                increment = -increment;
            }
        }
    }
};


Flasher led1(11, 123, 400);
Flasher led2(12, 350, 350);
Flasher led3(13, 200, 222);
Sweeper sweeper1(25);
Sweeper sweeper2(35);
void setup() 
{ 
    sweeper1.Attach(9);
    sweeper2.Attach(10);
    // Timer0 уже используется millis() - прерываемся в середине и инициализируем функцию "Compare A"
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    pinMode(2, INPUT_PULLUP);
     attachInterrupt(0, Reset, FALLING);
}

void Reset()
{
    sweeper1.reset();
     sweeper2.reset();
}

// Прерывание вызывается один раз в миллисекунду, и в случае прихода новых данных сохраняет их
SIGNAL(TIMER0_COMPA_vect) 
{
    unsigned long currentMillis = millis();
    sweeper1.Update(currentMillis);
    if(digitalRead(2) == HIGH)
    {
        sweeper2.Update(currentMillis);
        led1.Update(currentMillis);
    }
    led2.Update(currentMillis);
    led3.Update(currentMillis);
}

void loop()
{
}