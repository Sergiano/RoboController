/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
     данных, который генерируется согласно показаниям с кнопки и с
     двух потенциомтеров. Приёмник (RX) получает массив, и записывает
     данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define in1 2 //down
#define in2 3//up
#define in3 4//right
#define in4 5//left
#define in5 6//no comand
//========================================//
//=============== Команды ================//
//========================================//
#define NO_COMMAND 0
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
int last_command = NO_COMMAND;
byte incomingByte = 0;


void set_command(int Comand) {
  switch (Comand) {
    case  COMMAND_UP:
      comandUp();
      break;
    case  COMMAND_DOWN:
      comandDown();
      break;
    case COMMAND_LEFT:
      comandLeft();
      break;
    case  COMMAND_RIGTH:
      comandRigth();
      break;
    case  NO_COMMAND:
      noCommand();
      break;
    default:
      break;
  }
}

void comandUp() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
}

void comandDown() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
}

void comandLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
}

void comandRigth() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
}

void noCommand() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
}

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
    last_command = incomingByte;
  }
  switch (last_command) {
    case KEY_W: {
        set_command(COMMAND_UP);
        break;
      }
    case KEY_A: {
        set_command(COMMAND_LEFT);
      }
    case KEY_S: {
        set_command(COMMAND_DOWN);
        break;
      }
    case KEY_D: {
        set_command(COMMAND_RIGTH);
        break;
      }
    case KEY_X: {
        set_command(NO_COMMAND);
        break;
      }
    case KEY_R: {
        set_command(NO_COMMAND);
        break;
      }
    default:
      break;
  }
}

