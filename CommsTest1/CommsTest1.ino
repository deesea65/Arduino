const int Green = 12;
const int Red = 10;
boolean val = false;
String cmd_text = "";

void setup() {
  // put your setup code here, to run once:
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
     cmd_text = Serial.readString(); // get input from other end
     Serial.println(cmd_text);  // send back what we got
     
    // determine action to take
        
     if (cmd_text == "light") {
        val = !digitalRead(Red);
        Serial.print("In Light value is ");
        Serial.println(val);
        digitalWrite(Red, val );
     }
   
     if (cmd_text == "temp") {
        val = !digitalRead(Green);
        Serial.print("In temp value is ");
        Serial.println(val);
        digitalWrite(Green, val );
     }
   
  }
  delay(1);
}



