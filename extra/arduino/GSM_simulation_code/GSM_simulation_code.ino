#include "SoftwareSerial.h"

SoftwareSerial gsmSer(2,3);

#define BAUD_PC   9600
#define BAUD_GSM    9600
void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_PC);
  gsmSer.begin(BAUD_GSM);
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadDataFrom_MCU();
  ReadDataFromPC();
}

void ReadDataFrom_MCU(){
  if(gsmSer.available()){
    String tempData = gsmSer.readStringUntil('\n');

    tempData.toUpperCase();

    Serial.println("MCU: " + tempData);

    if(tempData.indexOf("AT+CMGS=\"") > -1){
      gsmSer.println(">");
      Serial.println("Answer: >");
    }else if(tempData.indexOf("AT") > -1){
      gsmSer.println("OK");
      Serial.println("Answer: OK");
    }
  }
}

void ReadDataFromPC(){
  if(Serial.available()){
    String tempData = Serial.readStringUntil('\n');
    Serial.println("Input: " + tempData);
    gsmSer.println(tempData);
  }
}
