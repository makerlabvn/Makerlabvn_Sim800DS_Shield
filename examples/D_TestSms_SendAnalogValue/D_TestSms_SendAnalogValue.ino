/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Khi module GSM nhan duoc tin nhan sms "CHECK SENSOR", Uno se gui SMS den SDT 0938022500 voi noi dung la: "Pin A0: <gia tri analog>".
Decription: When module GSM receive a SMS with content "CHECK SENSOR", Uno will Send a SMS to 0938022500 with content: "Pin A0: <analog value>"
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

int MyAnalogValue = 0;

bool allowSendSMS = false;

void setup() {
  // put your setup code here, to run once:
  //Only show monitor
  Serial.begin(9600);
  Serial.println("Start!!");

  // Init Country code default: VietNam (+84)
  HGSM.init(&GSM_Ready, 9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
  
  //Read analog Value on pin A0
  MyAnalogValue= analogRead(A0);
  HGSM.delay(100);
  
  if(allowSendSMS == true){
    HGSM.sendsms(Str_PhoneNum, "Pin A0:" + String(MyAnalogValue));
    allowSendSMS = false; // turn off flag
  }
}

void GSM_Ready() {
  if (HGSM.getDataGSM() != "") {
//    Serial.println(HGSM.getDataGSM());  //show data comming
    
    if(HGSM.checkData("CHECK SENSOR")){
      Serial.println("Detect my valid sms command!");
      allowSendSMS = true;  // turn on flag
    }else;
    
  } else;
}