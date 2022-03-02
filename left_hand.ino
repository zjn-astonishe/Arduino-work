//左手代码
/*实现功能：
    一、两种控制方式
        1、蓝牙接收控制
            a、手机控制
            b、右手套控制
        2、键盘控制
        3、软串口通信
    三、手部运动模式
        1、握拳
            a、紧握
            b、变换
        2、石头剪子布
        3、数数字1-7
*/

#include<Servo.h>
#include<SoftwareSerial.h>
#include<Keypad.h>
#include <MsTimer2.h>

const byte rows_num = 4;//四行
const byte cols_num = 4;//四列
char keysboard[rows_num][cols_num] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
byte rows_pin[rows_num] = {19,18,17,16};//行对应引脚
byte cols_pin[cols_num] = {7,8,11,12};//列对应引脚
Keypad keypad = Keypad( makeKeymap(keysboard), rows_pin, cols_pin, rows_num, cols_num );//创建键盘

//定义手指舵机
Servo thumb;
Servo index;
Servo middle;
Servo ring;
Servo little;

// 定义蓝牙接口：Pin2为RX，接HC05的TXD；Pin4为TX，接HC05的RXD
SoftwareSerial BSlave(2, 4);
// 定义软串口：PinA0为RX，接另一块Arduino的TX；PinA1为TX，接另一块Arduino的RX
SoftwareSerial Connect(14,15);

static int j = 0;//固定变量
static int i = 0;//普通循环变量
static char key;//键盘输入读取
char result[4];//定义字符串准备储存整形数据。
static int count = 0;
int send_data;
static char data;
int run;

void setup()
{
    Connect.begin(9600);
    Serial.begin(9600);
    BSlave.begin(38400);
    thumb.attach(3);
    index.attach(5);
    middle.attach(6);
    ring.attach(9);
    little.attach(10);
}
void loop()
{
    i = 0;
    key = keypad.getKey();
    if(key)
    {   
        star:run = 0;
        Serial.print("co");
        Serial.println(count);
        Serial.print("key");
        Serial.println(key);   
        if(count==2)
            switch(key)
            {
                case '1':send_data = 1;one();break;
                case '2':send_data = 2;two();break;
                case '3':send_data = 3;three();break;
                case '4':send_data = 4;four();break;
                case '5':send_data = 5;five();break;
                case '6':send_data = 6;six();break;
                case '7':send_data = 7;seven();break;
                case '8':send_data = 8;clench();break;
                case '9':send_data = 9;fist();break;
                case '0':send_data = 14;hand();count=1;break;
                case 'A':send_data = 10;count++;break;
                case 'B':send_data = 11;count++;break;
            }
        else if(count==3)
            switch(key)
            {
                case 'A':send_data = 10;count++;check();goto star;break;
                case 'B':send_data = 11;count++;check2();goto star;break;
                case '0':send_data = 14;count=1;hand();break; 
            }
        else if(count==4)
            switch(key)
            {
                case '*':send_data = 12;send();backB();goto star;break;
                case '#':send_data = 16;send();backA();goto star;break;
                case 'C':send_data = 12;send();backA();goto star;break;
                case 'D':send_data = 13;send();backA();goto star;break;
                case '0':send_data = 14;count=1;hand();break;
            }
        else if(count==0)
            switch(key)
            {
                case '1':send_data = 1;break;
                case '2':send_data = 2;break;
                case '3':send_data = 3;break;
                case '4':send_data = 4;break;
                case '5':send_data = 5;break;
                case '6':send_data = 6;break;
                case '7':send_data = 7;break;
                case '8':send_data = 8;break;
                case '9':send_data = 9;break;
                case 'A':send_data = 10;break;
                case 'B':send_data = 11;break;
                case 'C':send_data = 12;break;
                case 'D':send_data = 13;break;
                case '0':send_data = 14;hand();count++;break;
                case '#':send_data = 16;break;
            }
        else if(count==1)
            switch(key)
            {
                case '1':send_data = 1;count++;break;
                case '2':send_data = 2;count++;break;
                case '0':send_data = 0;hand();break;
            }
        MsTimer2::set(1,read);        
        if(!run)
            MsTimer2::start();
        else
        {
            MsTimer2::stop();
        }
        send();
        
    }
}
//手掌和拳头
void fist()//拳头
{
    for(;j<=120;j++)
    {
        thumb.write(j);
        index.write(j);
        middle.write(j);
        ring.write(j);
        little.write(j);
        delay(10);
    }
}
void hand()//手掌
{
    for(;j>=0;j--)
    {
        thumb.write(j);
        index.write(j);
        middle.write(j);
        ring.write(j);
        little.write(j);
        delay(10);
    }
}
void clench()//伸缩
{
    fist();
    delay(5);
    hand();
}
//数字1-7
void one()
{
    thumb.write(120);
    index.write(0);
    middle.write(120);
    ring.write(120);
    little.write(120);
}
void two()
{
    thumb.write(120);
    index.write(0);
    middle.write(0);
    ring.write(120);
    little.write(120);
}
void three()
{
    thumb.write(120);
    index.write(0);
    middle.write(0);
    ring.write(0);
    little.write(120);
}
void four()
{
    thumb.write(120);
    index.write(0);
    middle.write(0);
    ring.write(0);
    little.write(0);
}
void five()
{
    thumb.write(0);
    index.write(0);
    middle.write(0);
    ring.write(0);
    little.write(0);
}
void six()
{
    thumb.write(0);
    index.write(120);
    middle.write(120);
    ring.write(120);
    little.write(0);
}
void seven()
{
    thumb.write(0);
    index.write(0);
    middle.write(120);
    ring.write(120);
    little.write(120);
}
//石头剪子布
void stone()
{
    thumb.write(120);
    index.write(120);
    middle.write(120);
    ring.write(120);
    little.write(120);
}
void scissors()
{
    two();
}
void cloth()
{
    five();
}
void check()
{
        read();
        int compare = random(1,4);
        Serial.print("com");
        Serial.println(compare);
            switch(compare)
            {
                case 1:cloth();delay(1000);break;
                case 2:scissors();delay(1000);break;
                case 3:stone();delay(1000);break;
            }
            Serial.print("com");
            Serial.println(compare);
            if(data-'0'==compare)
            {
                key = '#';
                i--;
            }
            else if((data=='1'&&compare==3)||(data=='2'&&compare==1)||(data=='3'&&compare==2))
                key = 'C';
            else if((compare==1&&data=='3')||(compare==2&&data=='1')||(compare==3&&data=='2'))
                key = 'D';
            Serial.println(send_data);
            Serial.println(key);
}
void check2()
{
        read();
        Serial.print("data");
        Serial.println(data);
            if(data=='1')
            {
                scissors();
                delay(1000);
                key = '*';
            }
            else if(data=='2')
            {
                stone();
                delay(1000);
                key = '*';
            }
            else if(data=='3')
            {
                cloth();
                delay(1000);
                key = '*';
            }        
}
void backA()
{
    if(i<=5)
    {
        key = 'A';
        count = 3;
        i++;
    }
    else
    {
        key = '0';
        count = 0;
    }
    
}
void backB()
{
    if(i<=5)
    {
        key = 'B';
        count = 3;
        i++;
    }
    else
    {
        key = '0';
        count = 0;
    }
}
void send()
{
    if(send_data)
    {
        itoa(send_data,result,10);
        Connect.write(result);
        Serial.print(result);
        delay(100);
    }
}
void read()
{
    if (BSlave.available()) {
    data = BSlave.read();
    Serial.println(data);
    }
    run = 1;
}