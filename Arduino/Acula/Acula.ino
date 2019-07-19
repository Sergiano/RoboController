#define ALL_DOWN  PORTB=0   // все пины вниз
#define D8        PORTB=1   // пин наклона вниз 
#define D9        PORTB=2   // пин наклона вверх
#define D10       PORTB=4   // пин махов хвостом
#define D11       PORTB=8   // пин поворота влево
#define D12       PORTB=16  // пин поворта вправо

#define DELAY_W   3000      ///////////////////////////////////
#define DELAY_S   3000      //                               //
#define DELAY_R   6000      //   ПРОДОЛЖИТЕЛЬНОСТЬ КОМАНД    //
#define DELAY_A   1000      //                               //
#define DELAY_D   1000      ///////////////////////////////////

#define ACTION_X  ALL_DOWN  //////////////////////////////////// 
#define ACTION_W  D8        //                                //
#define ACTION_S  D9        //  СООТВЕТСТВИЕ ПИНОВ И КОМАНД   //
#define ACTION_R  D10       //                                //
#define ACTION_A  D11       //                                //
#define ACTION_D  D12       ////////////////////////////////////

#define KEY_X     120
#define KEY_W     119
#define KEY_S     115
#define KEY_R     114
#define KEY_A     97
#define KEY_D     100

byte incomingByte;

void setup() 
{
  DDRB = B00011111; // D8..D12 на выход
  ACTION_X;
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    
    switch (incomingByte)
    {        
      case KEY_W:
        ACTION_W;
        delay(DELAY_W);
        ACTION_X;
        break;
      case KEY_S:
        ACTION_S;
        delay(DELAY_S);
        ACTION_X;          
        break;
      case KEY_A:
        ACTION_A;
        delay(DELAY_A);
        ACTION_X;
        break;
      case KEY_D:
        ACTION_D;
        delay(DELAY_D);
        ACTION_X;
        break; 
      case KEY_R:
        ACTION_R;
        delay(100);
        ACTION_X;
        delay(DELAY_R);
        ACTION_R;
        delay(100);
        ACTION_X;
        break;  
      /*case KEY_X:      
        break; 
        default:
        break;*/    
    }  

    while (Serial.available()) Serial.read();
  }
}
