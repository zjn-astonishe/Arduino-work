//右手手套代码
/*实现功能包括：
    1、控制两个光敏电阻
    2、蓝牙主机发送
*/
#include <SoftwareSerial.h> 

// Pin2为RX，接HC05的TXD
// Pin3为TX，接HC05的RXD
SoftwareSerial BT(2, 3); 

#define AD4 A4//定义模拟口A4
#define AD5 A5//定义模拟口A5

int Intensity_1 = 0;//定义模拟口A4对应光照度数
int Intensity_2 = 0;//定义模拟口A5对应光照度数
int send_data;//设置发送数字  
char result[4];//定义字符串准备储存整形数据。
int now_time;
int last_time;

void setup() {
  // HC-05默认，38400
  BT.begin(38400);
  Serial.begin(9600);
}
 
void loop() {
    Intensity_1 = analogRead(AD4);
    Intensity_2 = analogRead(AD5);
    if(Intensity_2>500&&Intensity_1<500)
        send_data = 2;
    else if(Intensity_1<=500&&Intensity_2<=500)
        send_data = 1;
    else if(Intensity_1>500&&Intensity_2>500)
        send_data = 3;
        if(send_data)
        {
            itoa(send_data,result,10);
            BT.write(result);
            Serial.print(result);
            delay(100);
        }
}