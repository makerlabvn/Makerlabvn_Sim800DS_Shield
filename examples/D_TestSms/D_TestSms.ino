/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Goi SMS den SDT 0938022500.
Decription: Sending SMS to 0938022500.
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

String Str_PhoneNum = "0938022500";
unsigned long UL_PhoneNum = 938022500;

void setup() {
  // put your setup code here, to run once:
  //Only show monitor
  Serial.begin(9600);
  Serial.println("Start!!");

  // Init Country code default: VietNam (+84)
  HGSM.init(&GSM_Ready, 9600);


  //Send SMS with phone number as String
  HGSM.sendsms(Str_PhoneNum, "Makerlab.vn test GSM ");

  // Or send SMS with phone number as unsigned long
  // HGSM.sendsms(UL_PhoneNum, "Makerlab.vn test GSM ");
}


void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
}

void GSM_Ready() {
  if (HGSM.getDataGSM() != "") {
    Serial.println(HGSM.getDataGSM());  //show data comming
  } else;
}