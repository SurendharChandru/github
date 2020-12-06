#include <Servo.h>
 Servo myservo; 
// Shock Sensor code
int pos = 0;
int shockPin = 10; // Use Pin 10 as our Input
int shockVal = HIGH; // This is where we record our shock measurement

boolean bAlarm = false;

unsigned long lastShockTime; // Record the time that we measured a shock

int shockAlarmTime = 500; // Number of milli seconds to keep the shock alarm high

int soundDetectedPin = 9; // Use Pin 10 as our Input
int soundDetectedVal = HIGH; // This is where we record our Sound Measurement
  // attaches the servo on pin 9 to the servo object

unsigned long lastSoundDetectTime; // Record the time that we measured a sound
int soundAlarmTime = 500; // Number of milli seconds to keep the sound alarm high


void setup()
{
  setup1();
  
   
}
void loop()
{
  a();
  b();
  d();
}


// Sound Detection Sensor code


void setup1 ()
{
  Serial.begin(9600);  
  pinMode (soundDetectedPin, INPUT) ; // input from the Sound Detection Module
  pinMode (shockPin, INPUT) ; // input from the KY-002
  myservo.attach(5);
  
}
void a(){
  soundDetectedVal = digitalRead (9) ; // read the sound alarm time
  
  if (soundDetectedVal == LOW) // If we hear a sound
  {
  
    lastSoundDetectTime = millis(); // record the time of the sound alarm
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("no sound ");
      bAlarm = true;
      b();
    }
  }
  else
  {
    if( soundDetectedVal == HIGH)
    {
      Serial.println("loud");
      bAlarm = false;
      delay(5000);
     
    }
  }
  
}

void b()
{
  shockVal = digitalRead (shockPin) ; // read the value from our sensor
  
  if (shockVal == LOW) // If we're in an alarm state
  {
    lastShockTime = millis(); // record the time of the shock
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("Shock Alarm");
      bAlarm = true;
      Serial.println("ac");
  Serial.print("\r");
  delay(1000);                  
  Serial.print("AT+CMGF=1\r");    
  delay(1000);
  /*Replace XXXXXXXXXX to 10 digit mobile number &  ZZ to 2 digit country code*/
  Serial.print("AT+CMGS=\"+916381845405\"\r");    
  delay(1000);
  //The text of the message to be sent.
  Serial.print("accident alert   latitude-11.615270 ;longitude-78.144623");   
  delay(1000);
  Serial.write(0x1A);
  delay(1000); 
      delay(5000);
    }
  }
  else
  {
    if (shockVal == HIGH)
    {
      Serial.println("no alarm");
      bAlarm = false;
      delay(5000);
      Serial.println("no accident");
      delay(5000);
    }
    
  }
}
void d() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(0);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(0);                       // waits 15ms for the servo to reach the position
  }
}
