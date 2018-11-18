int ledPin = 13;   // LED connected to digital pin 13
int dahPin = 7;    // DAH  digital input pin 7
int ditPin = 6;    // DIT digital input 6
int spd = 300 ;    // keyer WPM speed
int piezoPin = 3;  //  8 ohm speaker  with 330 ohm in series
int dah = 1 ;
int dit = 1 ;

void setup()
{
  pinMode(ledPin, OUTPUT);              // sets the digital pin 13 as output
  pinMode(dahPin, INPUT_PULLUP);        // sets the digital pin 7 as input and internal resistor to HIGH
  pinMode(ditPin, INPUT_PULLUP);        // sets the digital pin 6 as input and internal resistor to HIGH 

}

void loop()
{
  dah = digitalRead(dahPin);     // read the DAH input pin
  if (dah == LOW) { 
    digitalWrite(ledPin, LOW);
    analogWrite(3,127);
    delay(spd);
    digitalWrite(ledPin, HIGH);
    analogWrite(3,0);
    delay(spd/3)  ;
  }

  dit = digitalRead(ditPin);     // read the DIT input pin
  if (dit == LOW) { 
    digitalWrite(ledPin, LOW);
    analogWrite(3,127);
    delay(spd/3);
    digitalWrite(ledPin, HIGH);
    analogWrite(3,0);
    delay(spd/3)  ;
  }
