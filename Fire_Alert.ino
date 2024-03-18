//include the library code:
#include <LiquidCrystal.h>
// initialize the library with numbers of the interface pins 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//delcaration of I/O ports
int led = 8;
int buzzer = 9;
int gasSensor = A0;
int triggerButton = 7;
int stopButton = SREG_T;

//tolerance of gas thresh 
int gasThresh = 400;

void setup()
{ 
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(gasSensor, INPUT);
  /*when you press button the system stops
  provided there is no smoke*/
  pinMode(triggerButton, OUTPUT);
}

void loop()
{
  //reading amount of gas 
  int gasState = analogRead(gasSensor);
  Serial.println(gasState);
  
  int buttonState = digitalRead(triggerButton);
  Serial.println(buttonState);
  //checks if thershold value is reached
  if(gasState > gasThresh)
  {
    //blinks LED for fire notification
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    delay(500);
    
    //targets the first row of the LED 
    lcd.setCursor(0, 0);
    lcd.print("FIRE ALERT!");
    
    //targets the second row of the LED 
    lcd.setCursor(0, 1);
    lcd.print("PLEASE EVACUATE");
    //emmits sound out of the buzzer 
    tone(buzzer, 500, 5000);    
  }
  else if(buttonState == HIGH){
    //blinks LED for fire notification
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    delay(500);
    
    //targets the first row of the LED 
    lcd.setCursor(0, 0);
    lcd.print("FIRE ALERT!");
    
    //targets the second row of the LED 
    lcd.setCursor(0, 1);
    lcd.print("PLEASE EVACUATE");
    //emmits sound out of the buzzer 
    tone(buzzer, 500, 100000);
    delay(100000);
  }
  else
  {
    //LED is off
    digitalWrite(8, LOW);
    
    //prints safe, all clear if there is no fire
    lcd.setCursor(0, 0);
    lcd.print("SAFE");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("ALL CLEAR");
    delay(1000);
    lcd.clear();
    
    //buzzer is off  
    noTone(buzzer);
  }
}