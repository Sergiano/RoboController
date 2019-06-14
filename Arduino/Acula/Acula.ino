/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
     данных, который генерируется согласно показаниям с кнопки и с
     двух потенциомтеров. Приёмник (RX) получает массив, и записывает
     данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define in1 2
#define in2 3
#define in3 4
#define in4 5
#define in5 6
//========================================//
//=============== Команды ================//
//========================================//
#define NO_COMMAND 0

//команды на перемещение танка
#define COMMAND_UP 1
#define COMMAND_DOWN 2
#define COMMAND_LEFT 3
#define COMMAND_RIGTH 4

#define END_LINE 10
//бит, означающий малые буквы стандартного управления WASD(перемещение)+QE(башня)+пробел(стрельба)+R(перезарядка)
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_Q 113
#define KEY_E 101
#define KEY_R 114
#define KEY_X 120
#define KEY_SPACE 32
#define KEY_C 99

//========================================//
//========== Данные и переменные =========//
//========================================//
//команды управления
int _command = NO_COMMAND;
byte incomingByte = 0;

void setup() {
pinMode(in1, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in2, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in3, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in4, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in5, OUTPUT);      // устанавливает режим работы - выход
}

void loop() {
  // считываем байт

  if (Serial.available() <= 0) {
    incomingByte = Serial.read();
  }
    switch (incomingByte) {
      case KEY_W:{
        //set_command(COMMAND_UP);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        digitalWrite(in5, LOW);
        break;
        }
      case KEY_A:{
        //set_command(COMMAND_UP);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        digitalWrite(in5, LOW);
        break;
        }
      case KEY_S:{
        //set_command(COMMAND_UP);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        digitalWrite(in5, LOW);
        break;
        }
      case KEY_D:{
        //set_command(COMMAND_UP);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        digitalWrite(in5, LOW);
        break;
        }
      default:
        break;
    }
}

