#include <Servo.h>

#include <LiquidCrystal_I2C.h> 

// Setting up LCD

const int rs = 13, en = 12, d4 = 7, d5 = 6, d6 = 5, d7 = 4;

LiquidCrystal_I2C lcd(0x27, 16, 2);


// Setting Values

int moistValue = 0;

int irValue = 0;

int distanceDry;

long durationDry;

int distanceWet;

long durationWet;

int distance;

int duration;

 
// Indicate pins for Components

int servoPin = 3;  // Servo

int trig1Pin = 11; // Dry Garbage Utrasonic Sensor

int echo1Pin = 9;

int trig2Pin = 10; // Wet Garbage Utrasonic Sensor

int echo2Pin = 8;


int Rled = A1;     // Dry Garbage Red LED

int Bled = A5;     // Wet Garbage Blue LED

int redPin= A4;    // Dustbin full or not LED

// Initiate Servo

Servo servo1;

void setup()

{

  pinMode(2, INPUT);

  pinMode(A0, INPUT);


  pinMode(Rled, OUTPUT);

  pinMode(Bled, OUTPUT);

  pinMode(redPin,OUTPUT);

//--------------------For Dry Garbage Ultrasonic Sensor--------------------

  pinMode(trig1Pin,OUTPUT);

  pinMode(echo1Pin,INPUT);

//--------------------For Wet Garbage Ultrasonic Sensor--------------------

  pinMode(trig2Pin,OUTPUT);

  pinMode(echo2Pin,INPUT);  

//-------------------------------------------------------------------------

  servo1.attach(servoPin); // Attaching the Servo  

//-------------------------------LCD Starting------------------------------

 
lcd.init();    // LCD setup
  lcd.backlight();

  lcd.setCursor(0, 0);

    

  lcd.print("Welcome to");

  lcd.setCursor(0, 1);

  lcd.print("our Project");

  delay(2000);

  lcd.clear();

  lcd.print("Waste");

  lcd.setCursor(0, 1);

  lcd.print("Segregation");

  delay(2000);

  lcd.clear();


} 

// This is for indicating if the dustbin is full or not

void ultrasensor(int trigPin,int echoPin)

 {

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  

  digitalWrite(trigPin, LOW);

  

  duration = pulseIn(echoPin, HIGH);  //Checks the Duration

  

  distance =(duration * 0.034 / 2);  //Calculates the distance

 }



// For selecting red color for RGB LED


void RGB_color(int redvalue)

{

  analogWrite(redPin, redvalue);

}

  

//-------------------------------------------------------------------------

void loop()

{

  irValue = digitalRead(2);

  moistValue = analogRead(A0);

  

  

  servo1.write(135); // Rotate the servo to 135 Deg

 
 

//Ultrasonic Sensor Part

  

  ultrasensor(trig1Pin, echo1Pin);

  distanceDry = distance;

  

  ultrasensor(trig2Pin, echo2Pin);

  distanceWet = distance;

 

  lcd.print("DRY  WET");

  lcd.setCursor(2,1);

  lcd.print(distanceDry);

  lcd.setCursor(11,1);

  lcd.print(distanceWet);

  delay(1000);

  lcd.clear();

  lcd.setCursor(0, 1);

  lcd.clear();


//------------------------Dustbin Full or NOT Part-------------------------

  if (distanceDry >= 150 && distanceWet >= 150)

    {

     lcd.print("Both Bins are ");

     lcd.setCursor(0, 1);

     lcd.print(" Full");

     delay(2000);

     lcd.clear();

     RGB_color(255);

     delay(450);

     RGB_color(0);

     delay(450);     

    }

  

    

    else if (distanceDry >= 150)

    {

     lcd.print("Dry Bin is Full");

     delay(2000);

     lcd.clear();

     RGB_color(255);

     delay(450);

     RGB_color(0);

     delay(450);     

    }

    

    else if (distanceWet >= 150)

    {

     lcd.print("Wet Bin is Full");

     delay(2000);

     lcd.clear();

     RGB_color(255);

     delay(450);

     RGB_color(0);

     delay(450);

    }

 

   else if (irValue == 1)

  {

    Serial.println(moistValue);

    lcd.clear();

    lcd.setCursor(0, 0);

    lcd.print("Moisture = ");

    lcd.print(moistValue);

    

    delay(500);

    

    if (moistValue>100) 

    {

      lcd.setCursor(0, 1);

      lcd.print("Its Dry Garbage");

      digitalWrite(Rled, HIGH);

      servo1.write(180);

      delay(3000);

      digitalWrite(Rled, LOW);

      lcd.clear();

   

    }

    else 
   

    {

      lcd.setCursor(0, 1);

      lcd.print("Its Wet Garbage");

      digitalWrite(Bled, HIGH);

      servo1.write(60);

      delay(3000);

      digitalWrite(Bled, LOW);

      lcd.clear();

    }

  }

  

}
