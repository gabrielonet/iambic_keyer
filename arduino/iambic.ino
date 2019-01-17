int ledPin = 13;   // LED connected to digital pin 13
int key_in = 12;     // Straight Key input
int straight = 0 ; // straight key temp variable
int ptt_in = 11 ;    // PTT input
int dahPin = 10;    // DAH  digital input pin 7
int ditPin = 9;    // DIT digital input 6
int ptt_out = 8 ;     // PTT output
int key_out = 7 ;     // key output
int piezoPin = 5;  //  8 ohm speaker  with 330 ohm in series
int spd = 300 ;    // keyer WPM speed
int dah = 1 ;
int dit = 1 ;
int val = 0;     // variable for reading straight key
int analogPin = A7;     // potentiometer connected to analog pin 3 , ground and 3.3V (arduino Due !!! other boards  may accept 5 V but be carefull)
unsigned long previousMillis = millis();
unsigned long currentMillis = millis();
void setup()
{
  pinMode(ledPin, OUTPUT);              // sets the digital pin 13 as output
  pinMode(dahPin, INPUT_PULLUP);        // sets the digital pin 7 as input and internal resistor to HIGH
  pinMode(ditPin, INPUT_PULLUP);        // sets the digital pin 6 as input and internal resistor to HIGH 
  pinMode(ptt_out, OUTPUT) ;
  pinMode(ptt_in, INPUT_PULLUP) ;
  pinMode(key_out, OUTPUT);
  pinMode(key_in, INPUT_PULLUP);  
  digitalWrite(ptt_out, HIGH);
  digitalWrite(key_out, HIGH);
  Serial.begin(9600);
}

void loop()
{
  spd = analogRead(analogPin);   // read potentiometer analogue value
  dah = digitalRead(dahPin);     // read the DAH input pin
  dit = digitalRead(ditPin);     // read the DIT input pin
  val = digitalRead(key_in);  // read input value

  
  if (val == LOW )      // check if the input is HIGH (straight key released)
  {
    previousMillis = millis();
    straight = 1 ;
    digitalWrite(ledPin, HIGH);
    digitalWrite(ptt_out, LOW); 
    digitalWrite(key_out, HIGH);
    analogWrite(piezoPin,127);
  } 
  if (val == HIGH && straight == 1)
    {
      //previousMillis = millis();
      straight == 0 ;
      digitalWrite(ledPin, LOW);  // turn LED OFF
      analogWrite(piezoPin,0);
      digitalWrite(key_out, LOW);

          
    }  




    
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
  currentMillis = millis();
  
  if (currentMillis - previousMillis >= spd*3)
  {
      digitalWrite(ptt_out, HIGH);
      Serial.println(currentMillis - previousMillis);
  }
       
  
  
}

