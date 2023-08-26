const int analogPin = A0;
int analogValue = 0;
const int red = 11;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(red, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogValue = analogRead(analogPin);
  Serial.print("analog value = ");
  Serial.println(analogValue, DEC);
  if (analogValue < 170) {
    digitalWrite(red, HIGH);
  }
  else
  {
     digitalWrite(red, LOW);
  }
  
  delay(125);
}
