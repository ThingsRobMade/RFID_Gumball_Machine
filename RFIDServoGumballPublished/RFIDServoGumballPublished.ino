/*
  RFID m&m® Dispenser
  Author: Rob Reynolds
  SparkFun Electronics
  Created: July 20, 2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/15209

  This build uses a gumball-style vending maching to set
  the number of servings of candy-coated chocolate treats
  in a day.

  Components used:
  SparkFun Redboard Qwiic - https://www.sparkfun.com/products/15123
  SparkFun RFID Qwiic Kit - https://www.sparkfun.com/products/15209
  Additional RFID Tags if needed - https://www.sparkfun.com/products/14325
  SparkFun Qwiic Real Time Clock RV-8803 - https://www.sparkfun.com/products/16281
  Generic High Torque Continuous Rotation Servo -https://www.sparkfun.com/products/9347
  LEDs - https://www.sparkfun.com/products/12062

  Connect servo control line to Pin 8
  Connect blue LED to Pin 10
  Connect green LED to Pin 11
  Connect red LED to Pin 12

  RFID Reader and RTC connect via Qwiic cables
  
*/

#include <Servo.h>  //Library to manage Servo
#include <Wire.h>   //Library to manage I2C communication
#include <SparkFun_Qwiic_Rfid.h>  //Library to manage RFID Reader
#include <SparkFun_RV8803.h> //Library to manage Real Time Clock

RV8803 rtc;


#define RFID_ADDR 0x7D // Default I2C address 

Qwiic_Rfid myRFID(RFID_ADDR);

String tag; 
float scanTime;
int serialInput; 
float previousMinute = 0;
String previousDate = "";

Servo gumballServo;

int pos = 90; //This sets speed of continuous rotation servo to 0

// Here we'll define variables for the number of servings for each RFID tag
int dadServings = 0;
int momServings = 0;
int daughterServings = 0;
int sonServings = 0;

// Here we define pin #s for the LEDs
const int greLight = 11;
const int bluLight = 10;
const int redLight = 12;

void setup()
{
  // Begin I-squared-C
  Wire.begin(); 
  Serial.begin(115200); 
  Serial.println("SparkFun RFID Gumball Machine");  // For testing only

  gumballServo.attach(8);
  pinMode(bluLight, OUTPUT);
  pinMode(redLight, OUTPUT);
  pinMode(greLight, OUTPUT);

  if(myRFID.begin())
    Serial.println("Ready to scan some tags!"); 
  else
    Serial.println("Could not communicate with Qwiic RFID!"); 

  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
  }
  else
  {
    Serial.println("RTC online!");
  }  

  previousDate = rtc.stringDate();
}

void loop()
{
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  }

  String currentDate = rtc.stringDate(); //Get the current date in dd/mm/yyyy format
  String currentTime = rtc.stringTime(); //Get the time
  Serial.print(currentDate);
  Serial.print(" ");
  Serial.println(currentTime);

  if(currentDate != previousDate){
    
//  This section was used for testing serving number reset by the minute unstead of by the day    
//  float currentMinute = rtc.getMinutes();
//  Serial.print("This is minute ");
//  Serial.println(currentMinute, 0);
//  if (currentMinute != previousMinute){
    resetServings();
  }

  previousDate = currentDate;

//  previousMinute = currentMinute;
  
  

  tag = myRFID.getTag();

  /* Empty string is returned if no tag is present,
   * wait till a valid ID string is returned.
   * All of the Serial.print lines were for testing while still programming.
   * However, with minor recoding they could be sent to a Micro OLED Breakout.
   */
      if(tag.length() != 6){
        Serial.print("Tag ID: ");
        Serial.println(tag);

        //Use RFID Example_1 to read RFID Tag numbers, then insert them here

        if(tag == "***************"){
          Serial.println("Dad's card!");
          dad();
        }

        else if(tag == "***************"){
          Serial.println("Mom's card!");
          mom();
        }

        else if(tag == "**************"){
          Serial.println("Daughter's card!");
          daughter();
        }

        else if(tag == "***************"){
          Serial.println("Son's card!");
          son();
        }

        else if(tag == "***************"){
          Serial.println("Emergency! This is not a drill!");
          emergency();
        }
        
      }
      delay(1000);
}


//I'm sure there are cleaner ways to write this sketch, but in my haste this is what I churned out

void dad(){
  dadServings++;
  Serial.print("This is serving #");
  Serial.println(dadServings);
  if (dadServings > 2){
    Serial.println("That's enough for you today");
    for(int y = 0; y < 10; y++){
      digitalWrite(bluLight, HIGH);
      digitalWrite(redLight, LOW);
      delay(300);
      digitalWrite(bluLight, LOW);
      digitalWrite(redLight, HIGH);
      delay(300);
    }
    digitalWrite(redLight, LOW);
    delay(1000);
  }
  
  else{
    digitalWrite(greLight, HIGH);
    Serial.print("Candy dispensed at ");
    String currentTime = rtc.stringTime();
    Serial.println(currentTime);
    gumballServo.write(110);              // Set the speed and direction of the servo
      delay(3250);                       // set how long the servo turns. **THIS MAY NEED TO BE ADJUSTED FOR EACH MACHINE!**
      //}
      gumballServo.write(90);
      digitalWrite(greLight, LOW);
      delay(2000); 
      } 
  }

void mom(){
  momServings++;
  Serial.print("This is serving #");
  Serial.println(momServings);
  if (momServings > 2){
    Serial.println("That's enough for you today");
    for(int y = 0; y < 10; y++){
      digitalWrite(bluLight, HIGH);
      digitalWrite(redLight, LOW);
      delay(300);
      digitalWrite(bluLight, LOW);
      digitalWrite(redLight, HIGH);
      delay(300);
    }
    digitalWrite(redLight, LOW);
    delay(1000);
  }
  
  else{
    digitalWrite(greLight, HIGH);
    Serial.print("Candy dispensed at ");
    String currentTime = rtc.stringTime();
    Serial.println(currentTime);
    gumballServo.write(110);              // // Set the speed and direction of the servo
      delay(3250);                       // set how long the servo turns. **THIS MAY NEED TO BE ADJUSTED FOR EACH MACHINE!**
      //}
      gumballServo.write(90);
      digitalWrite(greLight, LOW);
      delay(2000); 
      } 
  }

void daughter(){
  daughterServings++;
  Serial.print("This is serving #");
  Serial.println(daughterServings);
  if (daughterServings > 2){
    Serial.println("That's enough for you today");
    for(int y = 0; y < 10; y++){
      digitalWrite(bluLight, HIGH);
      digitalWrite(redLight, LOW);
      delay(300);
      digitalWrite(bluLight, LOW);
      digitalWrite(redLight, HIGH);
      delay(300);
    }
    digitalWrite(redLight, LOW);
    delay(1000);
  }
  
  else{
    digitalWrite(greLight, HIGH);
    Serial.print("Candy dispensed at ");
    String currentTime = rtc.stringTime();
    Serial.println(currentTime);
    gumballServo.write(110);              // // Set the speed and direction of the servo
      delay(3250);                       // set how long the servo turns. **THIS MAY NEED TO BE ADJUSTED FOR EACH MACHINE!**
      //}
      gumballServo.write(90);
      digitalWrite(greLight, LOW);
      delay(2000); 
      } 
  }

void son(){
  sonServings++;
  Serial.print("This is serving #");
  Serial.println(sonServings);
  if (sonServings > 2){
    Serial.println("That's enough for you today");
    for(int y = 0; y < 10; y++){
      digitalWrite(bluLight, HIGH);
      digitalWrite(redLight, LOW);
      delay(300);
      digitalWrite(bluLight, LOW);
      digitalWrite(redLight, HIGH);
      delay(300);
    }
    digitalWrite(redLight, LOW);
    delay(1000);
      }

   else{
    digitalWrite(greLight, HIGH);
    Serial.print("Candy dispensed at ");
    String currentTime = rtc.stringTime();
    Serial.println(currentTime);
    gumballServo.write(110);              // // Set the speed and direction of the servo
      delay(3250);                       // set how long the servo turns. **THIS MAY NEED TO BE ADJUSTED FOR EACH MACHINE!**
      //}
      gumballServo.write(90);
      digitalWrite(greLight, LOW);
      delay(2000); 
      }
          
  }

void emergency(){
  digitalWrite(redLight, HIGH);
  digitalWrite(greLight, HIGH);
  digitalWrite(bluLight, HIGH);
  gumballServo.write(110);              // // Set the speed and direction of the servo
      delay(3250);                       // set how long the servo turns. **THIS MAY NEED TO BE ADJUSTED FOR EACH MACHINE!**
  gumballServo.write(90);
  digitalWrite(redLight, LOW);
  digitalWrite(greLight, LOW);
  digitalWrite(bluLight, LOW);
  delay(2000); 
    
  
  }

void resetServings(){
  //When the date rolls over, serving numbers are resert to zero for the day
  dadServings = 0;
  momServings =0;
  daughterServings = 0;
  sonServings = 0;
  myRFID.clearTags();
}
