
// set up some constants
  const int red = 13 ;
  const int amber = 12;
  const int green = 11;


void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(amber, OUTPUT);
  pinMode(green,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(red, HIGH);
  delay(1000);
  // digitalWrite(red, LOW);
  digitalWrite(amber, HIGH);
  delay(1000);
  digitalWrite( red, LOW);
  digitalWrite(amber, LOW);
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(green, LOW);
  digitalWrite(amber, HIGH);
  delay(1000);
  digitalWrite(amber, LOW);
}
