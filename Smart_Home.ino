
// DS1302:  CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 4
#include <DS1302.h>      // rtc(clock)
#include <Servo.h>       // servo     
int Relay = 8;
DS1302 rtc(2, 3, 4);
Time t;
byte OnHour   = 12;  //  for the DEMONSTRATION consider,
byte OnMin    = 0;   //      12:00:03 - MORNING( door OPEN and light ON))
byte OnSec    =3;    //    & 12:00:12 - NIGHT  ( door CLOSE and light OFF) 
byte OffHour  = 12;
byte OffMin   = 0;
byte OffSec   =12;   // attachment of PROTEUS STUMILATION is along with this in which bluetooth module part is not present 
char light;
char door;

Servo servo_test;        //initialize a servo object for the connected servo                  
int angle=0 ;   
 
void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(115200);
  pinMode(Relay,OUTPUT);
  digitalWrite(Relay, LOW);
  // The following lines can be commented out to use 
  // the values already stored in the DS1302
  rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(18, 1, 2020); // Set the date to August 6th, 2019 
  servo_test.attach(9);     // attach the signal pin of servo to pin9 of arduino
// ############################
   Serial.begin(115200);
  pinMode(13,OUTPUT);      // attach the bluetooth module HC05 to 13 pin
}

void loop()
{
  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(":");
  Serial.println(t.sec);
  Serial.println("*********");
 
  if (t.hour == OnHour && t.min == OnMin && t.sec==OnSec)
   {
    digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    light='ON';                              // the variable light is assigned 'ON' and door is assigned 'OPEN' 
    door='OPEN';
    for(angle =0; angle <=180; angle +=5)    // command to move from 0 degrees to 180 degrees 
        {                                  
         servo_test.write(angle);            //command to rotate the servo to the specified angle
         delay(15);                       
        } 
   }
  if (t.hour == OffHour && t.min == OffMin && t.sec==OffSec)
   {
    digitalWrite(Relay,LOW);
    Serial.println("LIGHT OFF");
    light='OFF';                             // the variable light is assigned 'OFF' and door is assigned 'CLOSE' 
    door='CLOSE';
    for(angle =180; angle>=1; angle-=10)     // command to move from 180 degrees to 0 degrees 
       {                                
        servo_test.write(angle); //command to rotate the servo to the specified angle
        delay(5);                
       }  
   }
   loop1();                  // calling the function for bluetooth module 
 delay (1000);
}

void loop1() {
  if(Serial.available()>0)
  {
   char c=Serial.read();         // the char we are typing using ARDUINO BLUETOOTH CONTROL(avaliable in playstore) is read using Serial.read()
   Serial.println(c);
   if(c=='1'&& light=='OFF')     //type '1' for 'ON' the light (type '1' on the ARDUINO BLUETOOTH CONTROL)
    { digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    light='ON';                       
    }
   else if(c=='2'&& light=='ON')      // type '2' for 'OFF' the  light
    {digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
      light='OFF';
    }
   if(c=='3'&& door=='CLOSE')         // type '3' for open the door
     { 
      for(angle =0; angle <=180; angle +=5)       // command to move from 0 degrees to 180 degrees 
        {servo_test.write(angle);                 //command to rotate the servo to the specified angle
         delay(15);                       
        }
       door='OPEN'; 
   }
    else if(c=='4'&& door=='OPEN')       //type '4'for close the door 
      {
       for(angle =180; angle>=1; angle-=10)    // command to move from 180 degrees to 0 degrees 
         {servo_test.write(angle);             //command to rotate the servo to the specified angle
           delay(5);                
         } 
        door='CLOSE'; 
         }}}
       

 
