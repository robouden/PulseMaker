/**
 * @file main.cpp
 * @author Louis Bertrand <louis@bertrandtech.ca>
 * @brief Send pulses to the bGeigieZen
 * @version 0.1
 * @date 2023-07-16
 * @details Target: Arduino on Adrafruit ItsyBitsy M4
 *
 * @copyright Copyright (c) 2023 - BSD Two-Clause Licence
 *
 */
#include <Arduino.h>
#include <RBD_Timer.h>

constexpr uint32_t TARGET_CPM = 45;                    // Counts per minute
constexpr uint32_t INTERVAL = 1000 * 60L / TARGET_CPM; // Milliseconds between successive pulses
constexpr uint32_t PULSE_DURATION = 1000;              // Microseconds
RBD::Timer repetion_timer{INTERVAL};
constexpr uint32_t BLINK_TIME = 100; // Milliseconds to flash onboard LED
RBD::Timer blink_timer{BLINK_TIME};

constexpr int PULSE_PIN = 7; // pulse this pin low then high
constexpr int LED_PIN = 13; // Arduino onboard LED

void setup()
{
  Serial.begin(38400);  // Terminal to IDE
  Serial1.begin(38400); // Serial1 is on the Rx and Tx pins at the corner of the ItsyBitsy M4
  digitalWrite(LED_PIN, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(PULSE_PIN, HIGH);
  pinMode(PULSE_PIN, OUTPUT);
  repetion_timer.restart();
}

void loop()
{
  if (repetion_timer.onRestart())
  {
    blink_timer.restart();
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(PULSE_PIN, LOW);
    delayMicroseconds(PULSE_DURATION);
    digitalWrite(PULSE_PIN, HIGH);
  }
  if (blink_timer.onExpired())
  {
    digitalWrite(LED_PIN, LOW);
  }
  if (Serial1.available() > 0)
  {
    Serial.print(Serial1.read());
  }
}
