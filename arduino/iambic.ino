// My transceiver main controller needs 2 PTT signals, PTT input for Break in controll and a classic PTT for conventional mode.
// I have to rebuild code to include classic PTT .. TODO

int ledPin = 13;   // LED connected to digital pin 13
int key_in = 12;     // Straight Key input pin 12
int straight = 0 ; // straight key temp variable
int ptt_in = 11 ;    // PTT input pin 11
int dahPin = 10;    // DAH  digital input pin 10
int ditPin = 9;    // DIT digital input 9
int ptt_out = 8 ;     // PTT output pin 8
int key_out = 7 ;     // key output pin 7
int piezoPin = 5;  //  8 ohm speaker  with 330 ohm in series pin 5
int spd = 300 ;    // keyer WPM speed
int dah = 1 ;
int dit = 1 ;
int val = 0;     // variable for reading straight key
int analogPin = A7;     // potentiometer connected to analog pin 11 , ground and 3.3V (arduino Due !!! other boards  may accept 5 V but be carefull)
unsigned long previousMillis = millis();
unsigned long currentMillis = millis();
void setup()
{
  pinMode(ledPin, OUTPUT);              // sets the digital pin 13 as output
  pinMode(dahPin, INPUT_PULLUP);        // sets the dah pin as input and internal resistor to HIGH
  pinMode(ditPin, INPUT_PULLUP);        // sets the dit pin as input and internal resistor to HIGH 
  pinMode(ptt_out, OUTPUT) ;
  pinMode(ptt_in, INPUT_PULLUP) ;
  pinMode(key_out, OUTPUT);
  pinMode(key_in, INPUT_PULLUP);  
  digitalWrite(ptt_out, HIGH);
  digitalWrite(key_out, HIGH);
}

void loop()
{
  spd = analogRead(analogPin);  // read potentiometer analogue value
  dah = digitalRead(dahPin);    // read the DAH input pin
  dit = digitalRead(ditPin);    // read the DIT input pin
  val = digitalRead(key_in);    // read straight key input pin

  // Begin straight key 
  if (val == LOW )      // check if straight key pressed
  {
    previousMillis = millis();
    straight = 1 ;
    digitalWrite(ledPin, HIGH);
    digitalWrite(ptt_out, LOW); 
    digitalWrite(key_out, HIGH);
    analogWrite(piezoPin,127);
  } 
  if (val == HIGH && straight == 1) // check if straight key is released
    {
      //previousMillis = millis();
      straight == 0 ;
      digitalWrite(ledPin, LOW);  // turn LED OFF
      analogWrite(piezoPin,0);
      digitalWrite(key_out, LOW);
    }  
    
    // Begin iambic key  //
  if (dah == LOW) {
    previousMillis = millis();
    digitalWrite(ptt_out, LOW);
    digitalWrite(key_out, HIGH);
    digitalWrite(ledPin, HIGH);
    analogWrite(piezoPin,127);
    delay(spd);
    digitalWrite(ledPin, LOW);
    digitalWrite(key_out,LOW);
    analogWrite(piezoPin,0);
    delay(spd/3)  ;
  }
  
  if (dit == LOW) { 
    previousMillis = millis();
    digitalWrite(ptt_out, LOW);
    digitalWrite(key_out,HIGH);
    digitalWrite(ledPin, HIGH);
    analogWrite(piezoPin,127);
    delay(spd/3);
    digitalWrite(ledPin, LOW);
    digitalWrite(key_out,LOW);
    analogWrite(piezoPin,0);
    delay(spd/3)  ;
    
  }
  
 // Begin computing delta for Full Break  PTT hang time
  currentMillis = millis();
  if (currentMillis - previousMillis >= spd*3)
  {
      digitalWrite(ptt_out, HIGH);
  }
       
  
  
}

