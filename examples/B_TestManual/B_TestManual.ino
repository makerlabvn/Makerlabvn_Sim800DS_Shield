/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Muc tieu dat ra: Giao tiep giua PC voi Module Sim thong qua Arduino
Target: Communicating from PC to GSM-module.
******

IMPORTAN: Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********

Tutorial: 
********

Code download:  https://github.com/makerlabvn/Makerlabvn_Sim800DS_Shield
Link product:   https://hshop.vn/products/arduino-gsm-gprs-sim800ds-shield

P/S:  1/ Choosing "Both NL & CR" and "9600" baudrate!
      2/ Type "AT" then enter to see result -. it 'll be return "OK"
      3/ Type the same other AT command
      4/ Type "-Z" to send CTRL+Z [Used in SMS AT command]
      
Update: 7/2/2017
***********************************************************************************************/
#include <SoftwareSerial.h>

SoftwareSerial sim800ds(12, 13);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sim800ds.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String tempString = "";
    tempString = Serial.readStringUntil('\n');

    if(tempString.indexOf("-Z")>-1){
      sim800ds.write(26);
      Serial.println("Ctr+Z");
    }else{
      sim800ds.println(tempString);
    }
  }else;
  
  if(sim800ds.available()){
    Serial.write(sim800ds.read());
  }else;
}
