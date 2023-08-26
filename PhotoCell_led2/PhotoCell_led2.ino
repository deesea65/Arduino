const int analogPin = A0;
int analogValue = 0;
const int red = 11;
int mylist[10] ;
int index = 0;
int total = 0;
int average = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  total = 0;
  index = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  analogValue = analogRead(analogPin);
  analogValue = map( analogValue, 0, 1023, 0, 255);
  mylist[index++] = analogValue;
  index %= 10; // mod 10 index
  total += analogValue;
  total -= mylist[(index+1) % 10];
  average = total / 10;
  
  Serial.print("analog value = ");
  Serial.println(analogValue, DEC);
//  Serial.print(" total = ");
//  Serial.println( total, DEC);
//  Serial.print("index is ");
//  Serial.println( index, DEC);
  Serial.print("average is ");
  Serial.println(average, DEC);
  analogWrite(red, average);
  
  delay(125);
}
