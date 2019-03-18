/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
     данных, который генерируется согласно показаниям с кнопки и с
     двух потенциомтеров. Приёмник (RX) получает массив, и записывает
     данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>          // библиотека для работы с шиной SPI
#include "nRF24L01.h"     // библиотека радиомодуля
#include "RF24.h"         // ещё библиотека радиомодуля

RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

void setup() {
  Serial.begin(9600); //открываем порт для связи с ПК

  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openWritingPipe(address[0]);   //мы - труба 0, открываем канал для передачи данных
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_2MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp(); //начать работу
  radio.stopListening();  //не слушаем радиоэфир, мы передатчик
}
int incomingByte = 0;   // for incoming serial data]
int command_byte = 0;
int delay_command_time_u = 60;//119
int delay_command_time_d = 40;//115
int delay_command_time_l_r = 15;//97 100
int delay_timer = 0;
void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte != command_byte) { //если команда новая
      command_byte = incomingByte;
    }
    if (command_byte == 119 ) {
      delay_timer = delay_command_time_u;
    }
    if (command_byte == 115) {
      delay_timer = delay_command_time_d;
    }

    if (command_byte == 97 || command_byte == 100) {
      delay_timer = delay_command_time_l_r;
    }
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  if (delay_timer > 0) {
    delay(1);
    delay_timer--;
    Serial.print("delay_timer = "); Serial.println(delay_timer);
  } else {
    command_byte = 114;
  }
  radio.write(&command_byte, sizeof(command_byte));
}
