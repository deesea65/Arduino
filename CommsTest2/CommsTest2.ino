// declare useful constants
const int Green = 12;
const int Red = 10;
const int lightPin = A0;
// declare global variables
int tempValue = 0;
boolean val = false;
String cmd_text = "";
int lamp = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(lightPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0 ) {
     cmd_text = Serial.readString(); // get input from other end
     Serial.println(cmd_text);  // send back what we got
     
    // determine action to take
        
     if (cmd_text == "light") { 
       // next improvement is to allow light with paramters 
        // eg light 1 on, light 2 off, light mood
        //int lamp = Serial.parseInt();  // read next digit
        //Serial.print(" lamp value is ");
        //Serial.print( lamp );
        if (lamp == 1 ) {
            switchLight( Red);
        }
        else {
            switchLight( Green); // fix this to be more specific 
        }
          
     }
   
     if (cmd_text == "temp") {
        tempValue = readLightSensor();
        Serial.print("Photoresistor value is ");
        Serial.println(tempValue);
     }
   
  }
  delay(1);
}

int readLightSensor() {
  int level ;
  level = analogRead(lightPin);
  // Serial.print(" Photo level is ");
  // Serial.println(level);
  return int(level);
}

void switchLight(int lamp) {
      int val = !digitalRead(lamp);
      Serial.print("lamp value is ");
      Serial.print( lamp, DEC);
      Serial.print(" In Light value is ");
      Serial.println(val);
      digitalWrite(lamp, val );
}
