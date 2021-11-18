# Makerlabvn_Sim800DS_Shield 
<a href="https://hshop.vn/products/arduino-gsm-gprs-sim800ds-shield"><img src="doc/image/Sim800DS_Shield.jpg?raw=true" width="400px"></a>&nbsp; <a href="https://hshop.vn/products/arduino-gsm-gprs-sim800ds-shield"><img src="doc/image/Sim800DS_Shield_2.jpg?raw=true" width="400px"></a> <BR/>

## Giới thiệu
Thư viện Makerlabvn_Sim800DS_Shield được tạo ra cho **Arduino GSM GPRS SIM800DS Shield** giúp bạn dễ dàng kết nối và sử dụng Module GSM GPRS SIM800DS trên Arduino, Shield tương thích với tất cả các loại board mạch Arduino (Uno, Mega2560, ...), ngoài ra Shield còn được tích hợp thêm 2 Relay với Opto cách ly giúp bạn dễ dàng thực hiện các ứng dụng đóng ngắt điều khiển thiết bị bằng GSM/GPRS.

## Các chương trình mẫu trong thư viện (đã test trên Uno)
- **A_FirstUpLoad**: Dùng để reset lại baudrate 9600 cho Module GSM
- **A_TemplateProject**: Khung chương trình mẫu cơ bản nhất
```C++
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
```
- **C_TestCall**: Module GSM sẽ gọi đến SĐT được chỉ định
```C++
HGSM.call(UL_PhoneNum);
```
- **C_TestCall_Control_1_Device_no_money**: Điều khiển bật tắt một relay trên shield qua thao tác nhá máy
- **C_TestCall_Control_2_Device_Use_DTMF**: Điều khiển 2 relay trên shield thông qua việc bấm số trên điện thoại *(mất phí cuộc gọi)*
- **D_TestSms**: Module GSM sẽ gửi 1 SMS đến SĐT được chỉ định
```C++
HGSM.sendsms(Str_PhoneNum, "Makerlab.vn test GSM ");
```
- **D_TestSms_Control_2_devices**: Điều khiển 2 relay trên shield thông qua tin nhắn SMS. Cú pháp là <br>
```ON1``` để bật relay 1, ```OF1``` để tắt relay 1. Tương tự với ```ON2``` và ```OF2```.
- **D_TestSms_Control_2_devices_WithAuth**: tương tự ví dụ trên nhưng có thêm phần kiểm tra ***Đúng*** số điện thoại mới cho phép điều khiển
```C++
String SDT = "+84938022500";  // Only receive SMS from this phone number
```
```C++
if(HGSM.checkData(SDT)){
    passOK = true;
}

if(passOK == true){
    for (unsigned char count_for = 0; count_for < NUMBER_RELAY; count_for++) {
    if (HGSM.checkData(KeyWordOF[count_for])) {            // if Key word (turn off) match
        digitalWrite(Relay_pin[count_for], !Relay_active);   // Turn off relay
        Serial.println("I turn off relay: " + String(count_for));
        passOK = false;
    } else if (HGSM.checkData(KeyWordON[count_for])) {     // if Key word (turn on) match
        digitalWrite(Relay_pin[count_for], Relay_active);    // Turn on relay
        Serial.println("I turn on relay: " + String(count_for));
        passOK = false;
    } else;
    
}
```
- **D_TestSms_SendAnalogValue**: Gửi phản hồi giá trị analog đọc từ chân A0 khi nhận được SMS có cú pháp ```CHECK SENSOR```
```C++
if(HGSM.checkData("CHECK SENSOR")){
    Serial.println("Detect my valid sms command!");
    allowSendSMS = true;  // turn on flag
}else;
```
```C++
if(allowSendSMS == true){
    HGSM.sendsms(Str_PhoneNum, "Pin A0:" + String(MyAnalogValue));
    allowSendSMS = false; // turn off flag
}
```
