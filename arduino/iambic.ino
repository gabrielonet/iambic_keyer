int ledPin = 13;   // LED connected to digital pin 13
int key = 12 ;     // key output
int ptt = 11 ;     // PTT output
int inPin = 8;     // Straight Key input
int dahPin = 7;    // DAH  digital input pin 7
int ditPin = 6;    // DIT digital input 6
int spd = 300 ;    // keyer WPM speed
int piezoPin = 3;  //  8 ohm speaker  with 330 ohm in series
int dah = 1 ;
int dit = 1 ;
int val = 0;     // variable for reading straight key
int analogPin = A3;     // potentiometer connected to analog pin 3 , ground and 3.3V (arduino Due !!! other boards  may accept 5 V but be carefull)
unsigned long previousMillis = millis();
unsigned long currentMillis = millis();

void setup()
{
  pinMode(ledPin, OUTPUT);              // sets the digital pin 13 as output
  pinMode(dahPin, INPUT_PULLUP);        // sets the digital pin 7 as input and internal resistor to HIGH
  pinMode(ditPin, INPUT_PULLUP);        // sets the digital pin 6 as input and internal resistor to HIGH 
  pinMode(ptt, OUTPUT) ;
  pinMode(key, OUTPUT);
  pinMode(inPin, INPUT_PULLUP);  
  digitalWrite(ptt, HIGH);
  digitalWrite(key, HIGH);
  Serial.begin(9600);
}

void loop()
{
  spd = analogRead(analogPin);   // read potentiometer analogue value
  dah = digitalRead(dahPin);     // read the DAH input pin
  dit = digitalRead(ditPin);     // read the DIT input pin
  val = digitalRead(inPin);  // read input value

  
  if (val == HIGH) {         // check if the input is HIGH (straight key released)
    digitalWrite(ledPin, LOW);  // turn LED OFF
    analogWrite(3,0);
  } else {
    previousMillis = millis();
    digitalWrite(ledPin, HIGH);
    digitalWrite(ptt, LOW); 
    analogWrite(3,127);
  }
  
  if (dah == LOW) {
    previousMillis = millis();
    digitalWrite(ptt, LOW);
    digitalWrite(key, LOW);
    digitalWrite(ledPin, HIGH);
    analogWrite(3,127);
    delay(spd);
    digitalWrite(ledPin, LOW);
    digitalWrite(key,HIGH);
    analogWrite(3,0);
    delay(spd/3)  ;
  }
  
  if (dit == LOW) { 
    previousMillis = millis();
    digitalWrite(ptt, LOW);
    digitalWrite(key,LOW);
    digitalWrite(ledPin, HIGH);
    analogWrite(3,127);
    delay(spd/3);
    digitalWrite(ledPin, LOW);
    digitalWrite(key,HIGH);
    analogWrite(3,0);
    delay(spd/3)  ;
    
  }
  currentMillis = millis();
  
  if (currentMillis - previousMillis >= spd*3) {
      digitalWrite(ptt, HIGH);
      Serial.println("PTT off") ;
  }
       else
      {Serial.println("PTT on"); }
  
  
}

