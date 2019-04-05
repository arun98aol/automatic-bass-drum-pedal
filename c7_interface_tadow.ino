#include <AFMotor.h>
#include <Servo.h>
#include <Key.h>
#include "Keypad.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
const byte Rows= 4;
const byte Cols= 4;
char keypressed,keyp;
Servo name_servo;  
int modeone();
int servo_position = 0 ;
int i=0,j,bf=0;
int col_scan,t[5]={0},t2[50]={0},avg=0,ass=0;
char keymap[Rows][Cols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
int entermenu=0;
byte rPins[Rows]= {A0,A1,A2,A3}; 
byte cPins[Cols]= {A4,A5,12,13}; 
Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);
void setup() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("OOOlllAAAA");
//  Serial.begin(4800);
  name_servo.attach (9);
   lcd.begin(16, 2);
   
   welcome();
   Serial.println("Welcome done");
}


void loop() {
  if(entermenu==0){
    entermenu=1;
     //int servo_position = 0;
     Serial.println("Enter mode: ");
     menu();
  }
  keypressed = kpd.getKey();
  int con=keypressed-48;
     if (keypressed != NO_KEY){ 
          Serial.println(keypressed);
          lcd.clear();
         // integer(con,0);
          data("You've selected",0);
          if(keypressed=='1'){
            Serial.println(keypressed);
           // data(keypressed);
           
            data("Mode 1",1);
            Serial.println("\nMode 1");
            delay(1000);
            entermenu=0;
            int ran=modeone();
          }
          else if(keypressed=='2'){
            Serial.println(keypressed);
            Serial.println("\nMode 2");
            // data(keypressed);
           
            data("Mode 2",1);
            delay(1000);
            entermenu=0;
            modetwo();
          }
          else if(keypressed=='3')
          {
            Serial.println(keypressed);
            data("Mode 3",1);
            Serial.println("\nMode 3");
            delay(1000);
            entermenu=0;
            modethree();
            bf=0;
          }
          else
          {
            Serial.println(keypressed);
           Serial.println("Invalid input. Try again"); 
           lcd.clear();
           data("Invalid input",0);
           data("Try again",1);
           entermenu=0;
          }  
     }
}


int modeone(){
  int p=1;
   lcd.clear();
  data("Tap 4 times",0);
  while(p<=4){
    Serial.println("watch me roll");
    keyp = kpd.waitForKey();
    Serial.println(keyp);
    //lcd.setCursor(p*2,1);
    int con1=p-48;
   //integer(con1,1);
    Serial.println("keypressed");
    if(keyp!=NO_KEY){
        Serial.println("one");
        Serial.println(keyp);
        t[p] = millis()-ass;
        Serial.println(t[p]);
    }
    ass+=t[p];
    p++;
    delay(300);
  }
  avg = (t[2]+t[3]+t[4])/3;
  Serial.println("Avg = ");
  Serial.println(avg);
   lcd.clear();
   data("Average is",0);
   integer(avg,1);
   lcd.clear();
   data("Let's begin",0);
  if(bf==1)
  return avg;
  else
 { servo_call(avg);
return 0;
}
}
void servo_call(int avg){

  while(kpd.getKey()!='*'){
    Serial.println("i'm in");
    for (servo_position = 0; servo_position <=60; servo_position +=60){
      name_servo.write(servo_position);
      delay(2*avg);
    }
     Serial.println("i'm OUT");
       
  }
  lcd.clear();
  data("RESET",0);
}









void modetwo(){
   name_servo.write(0);
   Serial.println("Number of taps: ");
   lcd.clear();   
   data("Number of taps:",0);
    keyp = kpd.waitForKey();
    
 
    int ts=keyp-48;
       integer(ts,1);
     Serial.println(ts);   
   int p=1;
   lcd.clear();
   data("Tap pattern two",0);
   data("times",1);
  while(p<=(2*ts))
  {
    Serial.println("watch me roll");
    keyp = kpd.waitForKey();
    Serial.println(keyp);      
    Serial.println("keypressed");
      if(keyp!=NO_KEY){
        Serial.println("one");
        Serial.println(keyp);
        t2[p] = millis()-ass;
        Serial.println(t2[p]);
      }
        ass+=t2[p];
        p++;
        delay(300);
  }
 for(int r=2;r<=ts+1;r++)
 {
  if(r==ts)
  continue;
  if(r==ts+1)
  continue;
  else
  t2[r]=((t2[r]+t2[ts+r])/2);
 }
 lcd.clear();
 data("Entered ",0);
 data("Successfully",1);
 lcd.clear();
 data("Let's begin",0);
  servo_call_two(t2,ts);
}

void servo_call_two(int t2[50],int ts){
 
  while(kpd.getKey()!='*')
 {int s=2;
 servo_position=0;
 name_servo.write(servo_position);

  while(s<=ts+1){
  
  Serial.println("i'm in");
    for (servo_position = 60; servo_position >=0; servo_position -=60){
      name_servo.write(servo_position);
      //delay(1000);
      delay(230);
    
    }
    delay(t2[s]-230);
   // delay((1*avg)/16);
   if(kpd.getKey()=='*')
   return;
     Serial.println("i'm OUT");
 /*   for (servo_position = 60; servo_position > 0;servo_position -=60 ){
      name_servo.write(servo_position);
      //delay(1000);
      delay(t[s]-230);
    }   */
    s++;
  }
   // delay((1*avg)/16);
  }
 }



















void modethree(){ 
bf=1;

int tempo;
Serial.println("List of Songs \n 1) Aint No Sunshine \n 2) Another One Bites the Dust \n 3) Believer \n 4) Just the way you are \n 5) We will rock you \nEnter song:\n");
sel_list();
 char n = kpd.waitForKey();
 
switch (n)
{
case '1': 
Serial.println("Aint No Sunshine");
tempo = modeone();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("1. Ain't no ");
lcd.setCursor(0,1);
lcd.print("Sunshine");
aint_no_sunshine(tempo); 
break;  

case '2': 
Serial.println("Another one bites the dust");
tempo = modeone();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("2. Another one ");
lcd.setCursor(0,1);
lcd.print("bites the dust");
another_one_bites_the_dust(tempo); 
break;  

case '3': 
Serial.println("Believer");
tempo = modeone();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("3. Believer");



believer(tempo); 
break; 

case '4': 
Serial.println("Just the way you are");
tempo = modeone();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("4. Just the way ");
lcd.setCursor(0,1);
lcd.print("you are");

just_the_way_you_are(tempo); 
break;  

case '5': 
Serial.println("We will rock you");
tempo = modeone();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("5. We will rock");
lcd.setCursor(0,1);
lcd.print("you");

we_will_rock_you(tempo); 
break; 

 default: 
 Serial.println("Invalid input");
 lcd.clear();
 data("Invalid input",0);
 data("Try again.",1);
 return;
}
}




void aint_no_sunshine(int avg){

 // while(){
  Serial.println("i'm in");
    for (servo_position = 0; servo_position <=30&&(kpd.getKey()!='*'); servo_position +=30)
  {
      servo_position =30;
      name_servo.write(servo_position);
      delay(1*avg);
      servo_position = 0;
      name_servo.write(servo_position);
      delay((5*avg)/2);      
       if(kpd.getKey()=='*')
   return;

      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      //delay(avg);
      delay((5*avg)/2);
  }
//}
}



void another_one_bites_the_dust(int avg){

 // while(1){
  Serial.println("i'm in");
    for (servo_position = 0; servo_position <=30&&(kpd.getKey()!='*'); servo_position +=30)
  {
      servo_position =30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg/2);      
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay((3*avg)/2);

      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay((5*avg)/2);
      
  }
//}
}



void believer(int avg)
    {

  //while(1){
  Serial.println("i'm in");
    for (servo_position = 0; servo_position <=30&&(kpd.getKey()!='*'); servo_position +=30)
    {
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg);
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg);

      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg/2);      
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay((3*avg)/2);
     
      
    }
    delay((1*avg)/16);
    Serial.println("I'm OUT"); 
    delay((1*avg)/16);

  
//    }
  }



void just_the_way_you_are(int avg)
{

 // while(1){
  Serial.println("i'm in");
    for (servo_position = 0; servo_position <=30&&(kpd.getKey()!='*'); servo_position +=30)
    {
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(2*avg);
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg);

      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg);
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg/2);      
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay((3*avg)/2);
     
      
    }
    delay((1*avg)/16);
    Serial.println("I'm OUT"); 
    delay((1*avg)/16);

  
   // }
  }



void we_will_rock_you(int avg){
  int count = 0;
 // while(1){
  Serial.println("i'm in");
    for (servo_position = 0; servo_position <=30&&(kpd.getKey()!='*'); servo_position +=30)
  {
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 30;
      name_servo.write(servo_position);
      delay(avg/2);
      servo_position = 0;
      name_servo.write(servo_position);
      delay((5*avg)/2);
  
 }
 //}
}





void welcome()
{
  int i;
  lcd.clear();
  //lcd.home();
  lcd.setCursor(0, 0); 
  lcd.print("AUTOMATIC BASS DRUM PEDAL");
  delay(1000);
  lcd.setCursor(4, 1); //Column 0, Line 2
  lcd.print("WELCOMES YOU!!!");
  delay(500);
  for(i=0;i<24;i++)
  {
  lcd.scrollDisplayLeft();
  delay(750);
  }
  lcd.clear();
  //lcd.setCursor(0, 0);//Column 0, Line1
}





void menu()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("MENU");
  lcd.setCursor(0,1);
  lcd.print("1.MODE 1");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("2.MODE 2");
  lcd.setCursor(0,1);
  lcd.print("3.MODE 3");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Please select ");
  lcd.setCursor(0,1);
  lcd.print("your choice : ");
  delay(2000);
 
}







void data(char datatoprint[],int k)
{
//lcd.clear();
//lcd.home();
int i,n;
n=strlen(datatoprint);
lcd.setCursor(0,k);
for(i=0;i<n;i++)
{
   lcd.print(datatoprint[i]);
}
delay(1000);
}






void integer(int i,int j)
{
  char a[5];
  String str;
  str=String(i);
  str.toCharArray(a,5);
  data(a,j);
}










void sel_list()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("LIST OF SONGS");
  lcd.setCursor(0,1);
  lcd.print("1.Ain't No");//\n 2) Another One Bites the Dust \n 3) Believer \n 4) Just the way you are \n 5) We will rock you");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sunshine");
  lcd.setCursor(0,1);
  lcd.print("2.Another One");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bites the Dust");
  lcd.setCursor(0,1);
  lcd.print("3.Believer");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("4.Just the way");
  lcd.setCursor(0,1);
  lcd.print("you are");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("5.We will rock");
  lcd.setCursor(0,1);
  lcd.print("you");
  delay(2000);
  lcd.clear();
  lcd.print("Please select ");
  lcd.setCursor(0,1);
  lcd.print("your choice : ");
  delay(2000);
}
