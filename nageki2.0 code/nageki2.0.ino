#include "Mouse.h"
#include "./src/Encoder/Encoder.h"
//thanks my hero :)
//https://github.com/Reyn-Mukai/SDVX-DIY/tree/Standard
//from SDVX-DIY CODE
#include "Keyboard.h"
#include "Mouse.h"
#include <Adafruit_NeoPixel.h>

/*WS2812*/

/*Pot*/
int Sensor=A0;//将A0引脚取名为Sensor/ A0 pin Named Sensor
int SensorRead=0;
int newdata=0;
int inputValue=0;
int a;

/* button pin */
const int buttonPin1 = 9;          // Key left 1
const int buttonPin2 = 8;          // Key left 2
const int buttonPin3 = 7;          // Key left 3

const int buttonPin4 = 6;          // Key Right 4
const int buttonPin5 = 5;          // Key Right 5
const int buttonPin6 = 4;          // Key Right 6


const int FunctionL = 15;          // FKey left 
const int FunctionR = 10;          // FKey right

const int SideL = 16;          // SKey left 
const int SideR = 14;          // SKey right

/* Encoder pin */
/* 如果发现转动方向是反的就把3和2的位置调换一下*/
/*Switch "3" and "2" if the spin way was wrong*/
#define ENC_1_PIN_A 2
#define ENC_1_PIN_B 3


/* Encoder */
Encoder encLeft(ENC_1_PIN_A, ENC_1_PIN_B);


void setup() {
  Serial.begin(9600);
  // 初始化按键引脚，如果没有上拉电阻，需要使用INPUT_PULLUP/Pin Mode.
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(FunctionL, INPUT_PULLUP);
  pinMode(FunctionR, INPUT_PULLUP);
  pinMode(SideL, INPUT_PULLUP);
  pinMode(SideR, INPUT_PULLUP);
  // 初始化模拟键盘功能/Begin keyboard
  Keyboard.begin();
  Keyboard.releaseAll(); //所有键盘按键松开/Releasekeyboard
  //初始化鼠标/Begin Mousemove
  Mouse.begin();
  //归零编码器/encoder write 0
  encLeft.write(0);
  }

void Keys(){
   if (digitalRead(buttonPin1) == LOW){ //按键1/Key1
    Keyboard.press('J');
   }
   else {
    Keyboard.release('J');
}

   if (digitalRead(buttonPin2) == LOW){ //按键2/Key2
    Keyboard.press('K');
   }
   else {
    Keyboard.release('K');
}

   if (digitalRead(buttonPin3) == LOW){ //按键3/Key3
    Keyboard.press('L');
   }
   else {
    Keyboard.release('L');
}
if (digitalRead(buttonPin4) == LOW){ //按键4/Key 4
    Keyboard.press('A');
   }
   else {
    Keyboard.release('A');
}

   if (digitalRead(buttonPin5) == LOW){ //按键5/Key 5
    Keyboard.press('S');
   }
   else {
    Keyboard.release('S');
}

   if (digitalRead(buttonPin6) == LOW){ //按键6/Key 6
    Keyboard.press('D');
   }
   else {
    Keyboard.release('D');
}
}
void Function(){
  if (digitalRead(FunctionL) == LOW){ //功能键左/Menu L
    Keyboard.press('R');
   }
   else {
    Keyboard.release('R');
}
  if (digitalRead(FunctionR) == LOW){ //功能键右/Menu R
    Keyboard.press('U');
   }
   else {
    Keyboard.release('U');
}
}
void Side(){
    if (digitalRead(SideL) == LOW){ //侧键1/Side 1
    Keyboard.press('P');
   }
   else {
    Keyboard.release('P');
}
  if (digitalRead(SideR) == LOW){ //侧键2/Side 2
    Keyboard.press('Q');
   }
   else {
    Keyboard.release('Q');
}
}
void encFuncLeft(){
  updateMousePositionLeft();
}

void updateMousePositionLeft()
{
  static int prev_value = 0;
  int a;
  a = encLeft.read();
  Mouse.move((prev_value - a) * 2, 0, 0);
  prev_value = a;
}


void lever() 
{
    SensorRead=analogRead(Sensor);//读出Sensor的值并将它赋给SensorRead/Read Sensor and wirte for SensorRead
    newdata=map(SensorRead,0,1023,0,255);
    if (newdata >= 255)
    {
      newdata=(newdata - 128);
      Serial.println(newdata);
      }
    else if (newdata <= 255)
     {
      newdata=(newdata - 127);
      Serial.println(newdata);
      }
    }

void move()

{
  static int prev_value = 0;
  a = newdata;
  Mouse.move((prev_value - a) * 2, 0, 0);
  prev_value = a;
  
}

void loop()
  {
  Keys();
  Function();
  Side();
  encFuncLeft();
  updateMousePositionLeft();
  lever();
  move();
  }
