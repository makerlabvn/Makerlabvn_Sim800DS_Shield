/***********************************************************************************************
Author: Ngoc Khuu
Tac gia: Khuu Xuan Ngoc

Mo ta: Khung chuong trinh tối giản.
Decription: Basic project.
******

IMPORTAN: - Make sure UPLOAD sketch "FirstUpLoad" first (Only 1 time), then run this sketch!
********  - Replace delay [origin] by *.delay [example: HGSM.delay(1000)]
          - DO NOT use "delay" or "*.delay" in "GSM_Ready" [it seems to be interrupt when data is comming [.getDataGSM] from GSM]

Tutorial:
********

Code download:  https://github.com/makerlabvn/Makerlabvn_Sim800DS_Shield
Link produce:   https://hshop.vn/products/arduino-gsm-gprs-sim800ds-shield

P/s: Remember SET country code if you are NOT in VietNam
***********************************************************************************************/
#include "SoftwareSerial.h"
#include "Makerlabvn_Sim800DS_Shield.h"

SoftwareSerial sim800ds(12, 13);
Makerlabvn_Sim800DS_Shield HGSM = Makerlabvn_Sim800DS_Shield(&sim800ds);


void setup() {
  // put your setup code here, to run once:

  // Init Country code default: VietNam (+84)
  HGSM.init(&GSM_Ready, 9600);
  
  // Your code below:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  HGSM.handle();
  
  // Your code below:
  
}

void GSM_Ready() {
  if (HGSM.getDataGSM() != "") {
    
  } else;
}