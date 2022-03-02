//LCD显示屏代码
/*实现功能：
    1、接受软串口数据
    2、显示功能
    3、计数
*/
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal LCD (2,3,4,5,6,7,8,9,10,11);

SoftwareSerial mySerial(15,14);
String comdata = ""; //String 定义一个空的字符串
static int rdata = 0;
static int count1 = 0;
static int count2 = 0;
static int flo = 0;
int last_rdata[4];
char result[4];//定义字符串准备储存整形数据。

void setup()
{
    mySerial.begin(9600);
    Serial.begin(9600);
    LCD.begin(16,2);
    LCD.print("Welcome to use t");
    LCD.setCursor(0,2);
    LCD.print("his equipment!");
    delay(2500);
    LCD.clear();
    LCD.print("Please choose");
    LCD.setCursor(0,2);
    LCD.print("the mode:");
    delay(2500);
    LCD.clear();
    LCD.print("Press 0 to enter");
    LCD.setCursor(0,2);
    LCD.print("the menu");
    delay(2500);
}
void loop()
{
    read();
    star:
    if(rdata>0)
    {
        Serial.println(rdata);
        if(rdata==1&&flo==1){
            LCD.clear();
            LCD.print(" 1  2  3  4  5 ");
            LCD.setCursor(0,2);
            LCD.print(" 6  7  8  9  0 ");
            delay(500);
            last_rdata[flo] = rdata;
            flo++;
        }
        else if(((rdata==1)||(rdata==2)||(rdata==3)||(rdata==4)||(rdata==5)||(rdata==6)||(rdata==7)||(rdata==8)||(rdata==9))&&flo==2){
            LCD.clear();
            LCD.print("Loading....");
            delay(1000);
            last_rdata[flo] = rdata;
            rdata = 1;
            flo = 1;
            goto star;
        }
        else if(rdata==14){
            LCD.print(rdata);
            LCD.clear();
            LCD.print("1.Traing mode");
            LCD.setCursor(0,2);
            LCD.print("2.Game mode");
            delay(500);
            last_rdata[0] = 14;
            flo = 1;
            count1 = 0;
            count2 = 0;
        }
        else if(rdata==2&&flo==1){
            LCD.clear();
            LCD.print("A.Competition");
            LCD.setCursor(0,2);
            LCD.print("B.Cheat");
            delay(500);
            last_rdata[flo] = rdata;
            flo++;
        }
        else if(rdata==10&&flo==2){
            LCD.clear();
            LCD.print("P1:");
            LCD.print(count1);
            LCD.setCursor(0,2);
            LCD.print("P2:");
            LCD.print(count2);
            delay(500);
            last_rdata[flo] = rdata;
        }
        else if(rdata==11&&flo==2){
            LCD.clear();
            LCD.print("P1:");
            LCD.print(count1);
            LCD.setCursor(0,2);
            LCD.print("P2:");
            LCD.print(count2);
            delay(500);
            last_rdata[flo] = rdata;
        }
        else if(rdata==12)
        {
            count1++;
            LCD.clear();
            LCD.print("P1:");
            LCD.print(count1);
            LCD.setCursor(0,2);
            LCD.print("P2:");
            LCD.print(count2);
            last_rdata[flo] = rdata;
        }
        else if(rdata==13)
        {
            count2++;
            LCD.clear();
            LCD.print("P1:");
            LCD.print(count1);
            LCD.setCursor(0,2);
            LCD.print("P2:");
            LCD.print(count2);
            last_rdata[flo] = rdata;
        }
        else if(rdata==16)
        {
            LCD.clear();
            LCD.print("P1:");
            LCD.print(count1);
            LCD.setCursor(0,2);
            LCD.print("P2:");
            LCD.print(count2);
            last_rdata[flo] = rdata;
        }
        if(count1>count2&&(count1+count2)==5)
            {
                LCD.clear();
                LCD.print("P1:");
                LCD.print(count1);
                LCD.setCursor(0,2);
                LCD.print("P2:");
                LCD.print(count2);
                delay(2000);
                LCD.clear();
                LCD.print("P1 win");
                LCD.setCursor(0,2);
                LCD.print("Game over");
                delay(2000);
                rdata = 14;
                flo=0;
                count1=0;
                count2=0;
                goto star;
            }
        else if(count2>count1&&(count1+count2)==5)
            {
                LCD.clear();
                LCD.print("P1:");
                LCD.print(count1);
                LCD.setCursor(0,2);
                LCD.print("P2:");
                LCD.print(count2);
                delay(2000);
                LCD.clear();
                LCD.print("P2 win");
                LCD.setCursor(0,2);
                LCD.print("Game over");
                delay(2000);
                count1=0;
                count2=0;
                rdata = 14;
                flo=0;
                goto star;
            }
    }
}
void read()
{
    //读取数据     
    while (mySerial.available() > 0) 
    {
        comdata += char(mySerial.read());
        delay(2);
    }
    rdata = comdata.toInt();
    if (comdata.length() > 0)
        comdata = "";
    
}