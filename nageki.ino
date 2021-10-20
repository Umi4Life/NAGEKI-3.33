#include "./src/Encoder/Encoder.h"
//thanks my hero :)
//https://github.com/Reyn-Mukai/SDVX-DIY/tree/Standard
//from SDVX-DIY CODE
#include "Keyboard.h"
#include "Mouse.h"



/* button pin */
const int buttonPin1 = 9;          // Key left 1
const int buttonPin2 = 8;          // Key left 2
const int buttonPin3 = 7;          // Key left 3

const int buttonPin4 = 4;          // Key left 4
const int buttonPin5 = 5;          // Key left 5
const int buttonPin6 = 6;          // Key left 6


const int FunctionL = 15;          // FKey left 
const int FunctionR = 10;          // FKey right

const int SideL = 16;          // SKey left 
const int SideR = 14;          // SKey right


/* Encoder pin */
/* 如果发现转动方向是反的就把3和2的位置调换一下*/
#define ENC_1_PIN_A 2
#define ENC_1_PIN_B 3


/* Encoder */
Encoder encLeft(ENC_1_PIN_A, ENC_1_PIN_B);


void setup() {
  // 初始化按键引脚，如果没有上拉电阻，需要使用INPUT_PULLUP
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
  // 初始化模拟键盘功能
  Keyboard.begin();
  Keyboard.releaseAll(); //所有键盘按键松开
  //初始化鼠标
  Mouse.begin();
  //归零编码器
  encLeft.write(0);
  }


void Keys(){
   if (digitalRead(buttonPin1) == LOW){ //按键1
    Keyboard.press('J');
   }
   else {
    Keyboard.release('J');
}

   if (digitalRead(buttonPin2) == LOW){ //按键2
    Keyboard.press('K');
   }
   else {
    Keyboard.release('K');
}

   if (digitalRead(buttonPin3) == LOW){ //按键3
    Keyboard.press('L');
   }
   else {
    Keyboard.release('L');
}
if (digitalRead(buttonPin4) == LOW){ //按键4
    Keyboard.press('A');
   }
   else {
    Keyboard.release('A');
}

   if (digitalRead(buttonPin5) == LOW){ //按键5
    Keyboard.press('S');
   }
   else {
    Keyboard.release('S');
}

   if (digitalRead(buttonPin6) == LOW){ //按键6
    Keyboard.press('D');
   }
   else {
    Keyboard.release('D');
}
}
void Function(){
  if (digitalRead(FunctionL) == LOW){ //功能键左
    Keyboard.press('R');
   }
   else {
    Keyboard.release('R');
}
  if (digitalRead(FunctionR) == LOW){ //功能键右
    Keyboard.press('U');
   }
   else {
    Keyboard.release('U');
}
}
void Side(){
    if (digitalRead(SideL) == LOW){ //侧键1
    Keyboard.press('P');
   }
   else {
    Keyboard.release('P');
}
  if (digitalRead(SideR) == LOW){ //侧键2J
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

void loop() {
  Keys();
  Function();
  Side();
  encFuncLeft();
  updateMousePositionLeft();
}

//nageki test controller 1.0 绝赞开发中
