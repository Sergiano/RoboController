/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
     данных, который генерируется согласно показаниям с кнопки и с
     двух потенциомтеров. Приёмник (RX) получает массив, и записывает
     данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//#define BY_SERIAL
#ifndef BY_SERIAL
#define BY_NRF
#endif //!BY_SERIAL

#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define in5 3
#define in6 2
#define in7 8

//========================================//
//=============== Команды ================//
//========================================//
#define NO_COMMAND 0

//команды на перемещение танка
#define COMMAND_UP 1
#define COMMAND_DOWN 2
#define COMMAND_LEFT 3
#define COMMAND_RIGTH 4

//команды на вращение башни и стрельбу
#define COMMAND_TURRET_LEFT 5
#define COMMAND_TURRET_RIGHT 6
#define COMMAND_FIRE 7
#define COMMAND_MOVE_GUN 8

//========================================//
//=========== Байты для команд ===========//
//========================================//
//символы для декодирования команды
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

RF24 radio(9, 10); // "создать" модуль радиопередачи на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера приёмников

void init_pins() {
  pinMode(in1, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in2, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in3, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in4, OUTPUT);      // устанавливает режим работы - выход
  
  pinMode(in5, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in6, OUTPUT);      // устанавливает режим работы - выход
  pinMode(in7, OUTPUT);      // устанавливает режим работы - выход
}

void ACTION_NO_COMMAND() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
}

void ACTION_COMMAND_UP() {
#ifdef BY_SERIAL
  Serial.println("COMMAND_UP");
#endif //BY_SERIAL

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
}

void ACTION_COMMAND_DOWN() {
#ifdef BY_SERIAL
  Serial.println("COMMAND_DOWN");
#endif //BY_SERIAL
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
}

void ACTION_COMMAND_LEFT() {
#ifdef BY_SERIAL
  Serial.println("COMMAND_LEFT");
#endif //BY_SERIAL
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
}

void ACTION_COMMAND_RIGTH() {
#ifdef BY_SERIAL
  Serial.println("COMMAND_RIGTH");
#endif //BY_SERIAL
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
}

void ACTION_COMMAND_TURRET_LEFT() {
#ifdef BY_SERIAL
  Serial.println("COMMAND_TURRET_LEFT");
#endif //BY_SERIAL
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
}

void ACTION_COMMAND_TURRET_RIGHT() {
#ifdef BY_SERIAL
  Serial.println("COMMAND_TURRET_RIGHT");
#endif //BY_SERIAL
  digitalWrite(in6, LOW);
  digitalWrite(in5, HIGH);
}

void ACTION_COMMAND_FIRE() {
#ifdef BY_SERIAL
  Serial.println("COMMAND_FIRE");
#endif //BY_SERIAL
}

void ACTION_COMMAND_MOVE_GUN() {
#ifdef BY_SERIAL
  Serial.println("COMMAND_MOVE_GUN");
#endif //BY_SERIAL
  digitalWrite(in7, HIGH);
}

void set_command(int command) {
  if (command != _command) {
    _command = command;
    ACTION_NO_COMMAND();
    switch (_command) {
      case NO_COMMAND:
        ACTION_NO_COMMAND();
        break;
      case COMMAND_UP:
        ACTION_COMMAND_UP();
        break;
      case COMMAND_DOWN:
        ACTION_COMMAND_DOWN();
        break;
      case COMMAND_LEFT:
        ACTION_COMMAND_LEFT();
        break;
      case COMMAND_RIGTH:
        ACTION_COMMAND_RIGTH();
        break;
      case COMMAND_TURRET_LEFT:
        ACTION_COMMAND_TURRET_LEFT();
        break;
      case COMMAND_TURRET_RIGHT:
        ACTION_COMMAND_TURRET_RIGHT();
        break;
      case COMMAND_FIRE:
        ACTION_COMMAND_FIRE();
        break;
      case COMMAND_MOVE_GUN:
        ACTION_COMMAND_MOVE_GUN();
        break;
    }
  }
}

void fixedPinsControl() {
#ifdef BY_SERIAL
  for (int i = 0; i <= COMMAND_MOVE_GUN; i++) {
    set_command(i);
  }
  set_command(NO_COMMAND);
#endif //BY_SERIAL
}

void init_nrf() {
  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openReadingPipe(1, address[0]);     //хотим слушать приёмник 0
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_2MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль
}

void setup() {
#ifdef BY_SERIAL
  Serial.begin(9600);
#endif
#ifdef BY_NRF
  init_nrf();
#endif //BYNRF
  init_pins();
  fixedPinsControl();
}

void loop() {
  // считываем байт
#ifdef BY_NRF
  byte pipeNo, gotByte;
  while ( radio.available(&pipeNo)) {  // слушаем эфир со всех труб
    radio.read( &gotByte, sizeof(gotByte) );         // чиатем входящий сигнал
    Serial.print("Recieved: "); Serial.println(gotByte);
    incomingByte = gotByte;
#endif //BY_NRF 
       
#ifdef BY_SERIAL
    while (Serial.available() <= 0) {
      incomingByte = Serial.read();
#endif //BY_SERIAL 
         
      switch (incomingByte) {
        case KEY_W:
          set_command(COMMAND_UP);
          break;
        case KEY_A:
          set_command(COMMAND_LEFT);
          break;
        case KEY_S:
          set_command(COMMAND_DOWN);
          break;
        case KEY_D:
          set_command(COMMAND_RIGTH);
          break;
        case KEY_Q:
          set_command(COMMAND_TURRET_LEFT);
          break;
        case KEY_E:
          set_command(COMMAND_TURRET_RIGHT);
          break;
        case KEY_C:
          set_command(COMMAND_MOVE_GUN);
          break;
        case KEY_SPACE:
          set_command(COMMAND_FIRE);
          break;
        case KEY_R:
          set_command(NO_COMMAND);
        case KEY_X:
          set_command(NO_COMMAND);
          break;
        default:
          break;
      }
    }
  }

