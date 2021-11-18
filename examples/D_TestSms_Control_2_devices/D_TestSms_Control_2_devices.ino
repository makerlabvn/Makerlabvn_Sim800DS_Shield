/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Dung dien thoai gui tin SMS voi noi dung phu hop voi tu khoa trong mang KeyWordON[x] de bat thiet bi x (Relay_pin[x]) hoac trong mang KeyWordOF[x] de tat thiet bi x (Relay_pin[x]).
Decription: If SMS has content that matches the array KeyWordON or KeyWordOF, it will turn on or turn off the relay.
******

IMPORTAIN: - Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********  - Replace delay [origin] by *.delay [example: HGSM.delay(1000)]

Tutorial:
********

Code download:  https://github.com/makerlabvn/Makerlabvn_Sim800DS_Shield
Link product:   https://hshop.vn/products/arduino-gsm-gprs-sim800ds-shield

P/s: Remember SET country code if NOT in VietNam
***********************************************************************************************/
#include "SoftwareSerial.h"
#include "Makerlabvn_Sim800DS_Shield.h"

SoftwareSerial sim800ds(12, 13);
Makerlabvn_Sim800DS_Shield HGSM = Makerlabvn_Sim800DS_Shield(&sim800ds);

// Declare pin of relays:
#define NUMBER_RELAY    2
unsigned char Relay_pin[NUMBER_RELAY] = {10, 11};
unsigned char Relay_active = 0; // Relay active LOW
String KeyWordON[NUMBER_RELAY] = {"ON1", "ON2"};
String KeyWordOF[NUMBER_RELAY] = {"OF1", "OF2"};

void setup() {
  // put your setup code here, to run once:
  // Relay init:
  for (unsigned char count_for = 0; count_for < NUMBER_RELAY; count_for++) {
    pinMode(Relay_pin[count_for], OUTPUT);
    digitalWrite(Relay_pin[count_for], !Relay_active);  // turn off relay
  }

  //Only show monitor
  Serial.begin(9600);
  Serial.println("Start!!");

  // Init Country code default: VietNam (+84)
  HGSM.init(&GSM_Ready, 9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
}

void GSM_Ready() {
  if (HGSM.getDataGSM() != "") {
//    Serial.println(HGSM.getDataGSM());  //show data comming
	
    for (unsigned char count_for = 0; count_for < NUMBER_RELAY; count_for++) {
      if (HGSM.checkData(KeyWordOF[count_for])) {            // if Key word (turn off) match
        digitalWrite(Relay_pin[count_for], !Relay_active);   // Turn off relay
        Serial.println("I turn off relay: " + String(count_for));
      } else if (HGSM.checkData(KeyWordON[count_for])) {     // if Key word (turn on) match
        digitalWrite(Relay_pin[count_for], Relay_active);    // Turn on relay
        Serial.println("I turn on relay: " + String(count_for));
      } else;
    }

  } else;
}