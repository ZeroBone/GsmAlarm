#include <SoftwareSerial.h>
#include "LowPower.h"

#define ALARM_ACTION_LIMIT 1 // maximum amount of sms messages (prevents spam)

#define START_TIMEOUT 10000 // 10 seconds, time to turn on the alarm and leave

#define ALARM_ACTION_TIMEOUT 10000 // 10 seconds, time to turn off the alarm

#define PHONE "" // put the phone number here (e.g: +7xxxxxxxxxx) Sms messages will be sent to this number.

#define SIM_RX 4

#define SIM_TX 5

#define ALARM_LED_PIN 13 // led indicating that the system detected movement, 13 is the on-board arduino led pin

#define SENSOR_PIN 3 // the pin where the movement sensor is connected to

SoftwareSerial sim(SIM_RX, SIM_TX); // RX, TX

int actionsDone = 0;

boolean sleepFlag = false;

void sendSms(String phone, String text) {
  
  Serial.println("Sending sms...");
  
  sim.println("AT+CMGS=\"" + phone + "\"");
  
  delay(1000);
  
  sim.print(text);
  
  delay(300);
  
  sim.print((char)26);
  
  delay(300);
  
  Serial.println("SMS sent successfully.");
  
  delay(3000);
  
}

void wakeUp() {

  digitalWrite(ALARM_LED_PIN, HIGH);
  
}

void hibernate() {

  Serial.println("Sleeping...");

  sleepFlag = true;

  digitalWrite(ALARM_LED_PIN, LOW);

  delay(100);

  // sleep
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  
}

void setup() {

  pinMode(SENSOR_PIN, INPUT);

  pinMode(13, INPUT);

  Serial.begin(19200);

  sim.begin(19200);

  sim.println("AT");

  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), wakeUp, RISING);

  Serial.println("Starting...");

  delay(START_TIMEOUT);

  Serial.println("Alarm system ready.");

}

void loop() {

  if (sim.available())
    Serial.write(sim.read());
  if (Serial.available())
    sim.write(Serial.read());

  return;

  if (sleepFlag) {

    Serial.println("Woken up");

    // woken up after sleeping

    digitalWrite(ALARM_LED_PIN, HIGH);

    if (actionsDone < ALARM_ACTION_LIMIT) {

        Serial.println("Waiting for the user to deactivate the alarm.");

        delay(ALARM_ACTION_TIMEOUT);

        Serial.println("ALARM!!! Sending sms...");

        sendSms(PHONE, "ALARM v2"); // you can change the alarm message here

        actionsDone++;
      
    }

    sleepFlag = false;
    
  }

  delay(1000);

  hibernate();

}
