/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit the website for more
*information：https://docs.m5stack.com/en/core/atom_matrix
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/atom_matrix
*
* Product: Button example.  按键示例
* Date: 2021/7/21
*******************************************************************************
*/
#include "M5Atom.h"
#include <RBD_Timer.h>

// Target CPM values
// Push button to toggle between low and high.
// Defaults to high if no button present
constexpr uint32_t HIGH_RATE = 1200;
constexpr uint32_t LOW_RATE = 300;
constexpr uint32_t PULSE_DURATION = 1000;         // Microseconds
RBD::Timer repetion_timer{1000 * 60 / HIGH_RATE}; // initially fast rate

constexpr int PULSE_PIN = 22; // pulse this pin low then high

// uint8_t
//     DisBuff[2 + 5 * 5 * 3]; // Used to store RGB color values.  用来存储RBG色值

// void setBuff(uint8_t Rdata, uint8_t Gdata,
//              uint8_t Bdata) { // Set the colors of LED, and save the relevant
//                               // data to DisBuff[].  设置RGB灯的颜色
//   DisBuff[0] = 0x05;
//   DisBuff[1] = 0x05;
//   for (int i = 0; i < 25; i++) {
//     DisBuff[2 + i * 3 + 0] = Rdata;
//     DisBuff[2 + i * 3 + 1] = Gdata;
//     DisBuff[2 + i * 3 + 2] = Bdata;
//   }
// }

void setup() {
  delay(1000);
  // Serial.begin(9600);
  // Serial.println("setup started");

  //   setup pins:
  digitalWrite(PULSE_PIN, HIGH);
  pinMode(PULSE_PIN, OUTPUT);

  // //  setup leds
  // M5.begin(false, false,
  //          true); // only use LED function

  // setBuff(0xff, 0x00, 0x00);
  // M5.dis.displaybuff(DisBuff);

  //   set timer
  repetion_timer.restart();
}

uint8_t FSM = 0; // Store the number of key presses.

void loop() {

  static uint32_t rate = HIGH_RATE;
  static bool fast = true;

  if (M5.Btn.wasPressed()) { // Check if the key is pressed.
    switch (FSM) {
    case 0:
      // setBuff(0x40, 0x00, 0x00);
      rate = LOW_RATE;
      fast = false;
      // Serial.println(rate);
      repetion_timer.setTimeout(1000 * 60L / rate);
      break;
    case 1:
      // setBuff(0x00, 0x40, 0x00);
      rate = HIGH_RATE;
      fast = true;
      // Serial.println(rate);
      repetion_timer.setTimeout(1000 * 60L / rate);
      break;
    default:
      break;
    }
    // M5.dis.displaybuff(DisBuff);

    FSM++;
    if (FSM >= 2) {
      FSM = 0;
    }
  }

  if (repetion_timer.onRestart()) {
    digitalWrite(PULSE_PIN, LOW);
    delayMicroseconds(PULSE_DURATION);
    digitalWrite(PULSE_PIN, HIGH);
  }

  // M5.update(); // Read the press state of the key.
}