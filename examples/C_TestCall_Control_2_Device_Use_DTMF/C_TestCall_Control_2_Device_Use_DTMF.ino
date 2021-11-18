/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Khi co cuoc goi den hop le tu UL_PhoneNum, Module SIM800DS se bat may va cho tin hieu DTMF duoc bam tu dien thoai.
      Nhan cac phim tu (0) den (NUMBER_RELAY - 1) tren dien thoai de chon vi tri relay tuong ung
      Nhan "*" hoac "#" de bat hoac tat relay.
      
Decription: if a call (coming) from UL_PhoneNum, it will answer and wait for the DTMF signal.
******      The key from (0) to (NUMBER_RELAY - 1) on your phone is used to choose the location of RELAY.
            The key that is "*" or "#" used to close/open the relay.

IMPORTAN: - Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********  - Replace delay [origin] by *.delay [example: HGSM.delay(1000)]
          - DO NOT use "delay" or "*.delay" in "GSM_Ready" [it seems to be interrupt when data is comming [.getDataGSM] from GSM]

Tutorial:
********

Code download:  https://github.com/makerlabvn/Makerlabvn_Sim800DS_Shield
Link product:   https://hshop.vn/products/arduino-gsm-gprs-sim800ds-shield
***********************************************************************************************/
#include "SoftwareSerial.h"
#include "Makerlabvn_Sim800DS_Shield.h"

// Declare Library:
SoftwareSerial sim800ds(12, 13);
Makerlabvn_Sim800DS_Shield HGSM = Makerlabvn_Sim800DS_Shield(&sim800ds);

// Declare phone number valid:
unsigned long UL_PhoneNum = 938022500;  // String: "0938022500" or "+84938022500"

// Declare pin of relays:
#define NUMBER_RELAY    2
unsigned char Relay_pin[NUMBER_RELAY] = {10, 11};
unsigned char Relay_active = 0; // Relay active LOW
unsigned char Relay_pos = 0;

void setup() {
  // put your setup code here, to run once:
  // Relay init:
  for(unsigned char count_for = 0; count_for < NUMBER_RELAY; count_for++){
    pinMode(Relay_pin[count_for], OUTPUT);
    digitalWrite(Relay_pin[count_for], !Relay_active);  // turn off relay
  }
  
  //Only show monitor
  Serial.begin(9600);
  Serial.println("Start!!");
  
  // Init library:
  HGSM.init(&GSM_Ready, 9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
}

void GSM_Ready() {
  if (HGSM.getDataGSM() != "") {
    Serial.println(HGSM.getDataGSM());  //show data comming
    
    if(HGSM.checkData(UL_PhoneNum)){
      Serial.println("Detect my valid Number!");
      
      HGSM.answer();
    }else;
    
    // Detect Key is number. Format: <CR><LF>+DTMF:<number/symbol><CR><LF>
    for(unsigned char count_for = 0; count_for < NUMBER_RELAY; count_for++){
      if(HGSM.checkData("+DTMF:" + String(count_for))){
        Relay_pos = count_for;
      }else;
    }
    
    // Detect key is symbol. if "*" then close Relay, else if "#" open Relay
    if(HGSM.checkData("+DTMF:*")){
      digitalWrite(Relay_pin[Relay_pos], Relay_active);
      Serial.println("I turn on relay pos: " + String(Relay_pos));
    }else if(HGSM.checkData("+DTMF:#")){
      digitalWrite(Relay_pin[Relay_pos], !Relay_active);
      Serial.println("I turn off relay pos: " + String(Relay_pos));
    }else;
    
  } else;
}
