#include <LwTx.h>   /  library for 433 transmission

// declare useful constants
const int Green = 12;
const int Red = 10;
const int photoPin = A0;
const int temperaturePin = A1;


// declare global variables
float tempValue = 0.0;
int photoValue = 0;
// boolean val = false;
String cmd_text = "";
String args[10];  // arg to hold serial commands
int numArgs = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Green, OUTPUT);  // led green 
  pinMode(Red, OUTPUT);  // led red
  pinMode(photoPin, OUTPUT);  // photoresistor
  pinMode(temperaturePin, INPUT); // tmp36
  Serial.begin(9600);  // set up comms
  //Transmit on pin 7, 10 repeats,no invert, 140uSec tick)
  lwtx_setup(7, 10, 0, 140);

}



void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0 ) {
     cmd_text = Serial.readString(); // get input from other end
     numArgs = getParameters( cmd_text );
     // Serial.print("number of arguments is "); Serial.println( numArgs);
     cmd_text = args[0]; 
  
     //Serial.print("command : "); Serial.println(cmd_text);  // send back what we got
     
    // determine action to take
        
     if (cmd_text == "light") { 
         processLights( args[2], args[1]);  
     }
   
     if (cmd_text == "temp") {
        tempValue = readTemp();
        Serial.print("Temperature:");
        Serial.println(tempValue);
     }
     
     if (cmd_text == "photo") {
        photoValue = readPhotoSensor();
        Serial.print("photo:");
        Serial.println(photoValue);
     }
     
   
  }
  delay(1);
}

int readPhotoSensor() {
  int level ;
  level = analogRead(photoPin);
  // Serial.print(" Photo level is ");
  // Serial.println(level);
  return int(level);
}


float readTemp()  {
   int reading = analogRead(temperaturePin);  
 
   // converting that reading to voltage, for 3.3v arduino use 3.3
   float voltage = reading * 5.0;
   voltage /= 1024.0; 
   float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
   return temperatureC;
}

int getParameters(String command) {
  // break up string based on expecting csv string
  // given: String command
  int MAX_ARGS = 10;
  int data[MAX_ARGS];
  int numArgs = 0;

  int beginIdx = 0;
  int idx = command.indexOf(",");

  String arg;
  char charBuffer[16];

  while (idx != -1)
  {
      arg = command.substring(beginIdx, idx);
      arg.toCharArray(charBuffer, 16);

      // add error handling for atoi:
      args[numArgs++] = charBuffer;
      beginIdx = idx + 1;
      idx = command.indexOf(",", beginIdx);
  }

  args[numArgs++] = command.substring(beginIdx);
  return numArgs; // send back number of parts 
}

// processing for light
void processLights(String light, String state) {
       int lamp = light.toInt();
       //Serial.print("lamp value is "); Serial.println( lamp );
       // debug what lamp contains
       // String state = args[1];
       //Serial.print("state value is "); Serial.println( state );
              
        // determine which light to change        
        switch(lamp) {
           case 2:
                     switchLight( Red, state);
                     light_command(2,state);
                     break;
           case 3:
                     switchLight(Green, state);
                     light_command(3, state);
                     break;
           case 99: /// mood
                     switchLight( Red,state);
                     switchLight( Green, state);
                     break;
           default:
                     Serial.println("no such light!"); 
                     break;
        }  
 }
  
  
  
void switchLight(int bulb, String status) {
      //boolean val = !digitalRead( bulb);
      // Serial.print("bulb value is ");
      // Serial.println( bulb);
      // Serial.print(" In Light value is ");
      //Serial.println(status);
      boolean newState = LOW;
      if ( status == "on" ) newState = HIGH ; else newState= LOW;
      digitalWrite( bulb, newState );
}

void light_command(int bulb, String status) {
  
byte msg1[] = {0,0,2,1,0xF,2,8,0xD,1,5}; // switch 3 on
byte msg2[] = {0,0,2,0,0xF,2,8,0xD,1,5}; // switch 3 off
long timeout = 0;

msg1[2] = bulb -1; //set to desire light
msg2[2] = bulb -1; 
  if (lwtx_free()) {
    if (status == "on") {
          lwtx_send(msg1);
    }
    else {
        lwtx_send(msg2);
    }
        
    timeout = millis();
    Serial.print(timeout);
    Serial.println(" msg start");
  }
  while(!lwtx_free() && millis() < (timeout + 1000)) {
    delay(10);
  }
  timeout = millis() - timeout;
  Serial.print(millis());
  Serial.print(" msg sent:");
  Serial.println(timeout);
  // delay(100);
  
}



