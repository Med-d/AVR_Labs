#include <Arduino.c>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>

const byte ROWS = 4; // четыре строки
const byte COLS = 4; // четыре столбца
long int set1;
long int set2;
long int set3;
long int set4;
long int j;
String hours;
String minutes;
String seconds;

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 6, 7, 8, 9 };// подсоедините контакты клавиатуры ROW0, ROW1, ROW2 и ROW3 к этим контактам Arduino
byte colPins[COLS] = { 10, 11, 12, 13 };// подсоедините контакты клавиатуры COL0, COL1, COL2 и COL3 к этим контактам Arduino
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(A0, A1, 5, 4, 3, 2); // создаем объект ЖК дисплея с параметрами (rs, enable, d4, d5, d6, d7)
int t1, t2, t3, t4, t5, t6;
int r1, r2, r3;
bool feed = true; // условие для срабатывания сигнализации
char key;
String r[8];
void setFeedingTime()
{
    feed = true;
    int i=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set feeding Time");
    delay (2000);
    lcd.clear();
    lcd.print("HH:MM:SS");
    lcd.setCursor(0,1);
    while(1){
        key = kpd.getKey();
        char j;
    
        if(key!=NO_KEY){
                lcd.setCursor(j,1);
                lcd.print(key);
                r[i] = key-48;
            i++;
            j++;
            if (j==2 || j == 5)
            {
            lcd.print(":"); j++;
            }
            delay(500);
        }
        if (key == '*') { key=0; break; }
    }
    lcd.clear();
}

void setup() 
{ 
    lcd.begin(16,2);
    Serial.begin(9600);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A3, INPUT);
    pinMode(A4, OUTPUT);
} 

void loop() 
{ 
    lcd.setCursor(0,0);
    lcd.print("Arduino Timer");
    Serial.println(A3);
    if (digitalRead(A3)==1) 
    {
        lcd.clear();
        setFeedingTime(); 
        for(int i = 0; i < 6; i++)  // в этом цикле мы передаем заданное значение времени в окно монитора последовательной связи
        {
        Serial.print(r[i]);
        Serial.println();
        }
            hours = String (r[0]) + String (r[1]) ; //объединяем два значения целого типа r[0] и r[1] в одну строку и сохраняем ее в переменную "hours"
        minutes = String (r[2]) + String (r[3]) ;  // объединяем два значения целого типа r[2] и r[3] в одну строку и сохраняем ее в переменную "minutes"
        seconds = String (r[4]) + String (r[5]) ;  // объединяем два значения целого типа r[4] и r[5] в одну строку и сохраняем ее в переменную "seconds"
        set1 = (hours.toInt()*3600); // конвертируем часы в секунды     
        set2 = (minutes.toInt() * 60);  //конвертируем минуты в секунды
        set3 = seconds.toInt();
        set4 = (hours.toInt() * 3600)+ (minutes.toInt() * 60) + seconds.toInt(); //объединяем set1, set2 и set3 вместе в набор set4
        Serial.print("set4");
        Serial.print(set4);
        Serial.println();
        lcd.setCursor(0,0);
        lcd.print("Countdown begins");
        delay(1000);
        lcd.clear();
            for(long int j = set4; j >= 0; j--) // этот цикл используется для уменьшения общего времени счета в секундах
        {
            Serial.println(j);
            lcd.setCursor(0,0);
            lcd.print("HH:MM:SS");
            long int HH = j / 3600; // конвертируем оставшееся время в часы
            lcd.setCursor(0,1);
            Serial.println(HH);
            if (HH < 10) { lcd.print('0');  }
            lcd.print(HH);
            lcd.print(":");
            long int MM = (j - (HH*3600))/60 ; // конвертируем оставшееся время в минуты
            lcd.setCursor(3,1);
            Serial.println(MM);
            if (MM < 10) { lcd.print('0');  }
            lcd.print(MM);
            lcd.print(":");
            long int SS = j - ((HH*3600)+(MM*60)); // конвертируем оставшееся время в секунды
            lcd.setCursor(6,1);
            Serial.println(SS);
            if (SS < 10) { lcd.print('0');  } 
            lcd.print(SS);
            delay(1000);
            if (digitalRead(A3)==1){ break; } 
            if (j == 0)
            {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Timer Stop");
                lcd.setCursor(2,1);
                lcd.print("-Ring-Ring-");
                for(int k =0; k<= 100; k++) // этот цикл используется для того чтобы зуммер звучал 100 раз после того как таймер достигнет нуля
                {
                    digitalWrite(A4,HIGH);
                    delay(300);
                    digitalWrite(A4,LOW);  
                    delay(300); 
                    if (digitalRead(A3)==1){break;}  
                }
            }
        }
    }
}
