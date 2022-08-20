// A circuit to remind me to move from the desk every 30 mins
// Outputs run details + status to serial port

// Circuit has 3 LEDs, 1 buzzer, 2 switches
// 3 lights to indicate time. Increment every 10 minutes
// After 30 mins, red light + Buzzer

// Two switches - sleep and reset
// Reset starts timer again
// Sleep stops it running until sleep pressed again

// Pins connected to positive electrodes for all components

// To build circuit, connect as below
// Green LED: 		2
// Yellow LED: 		3
// Red LED: 		4
// Piezo:			5
// Sleep button: 	12
// Reset button:	13

// Assign Pins
int greenLed_pin = 2;
int yellowLed_pin = 3;
int redLed_pin = 4;
int buzzer_pin = 5;
int sleep_pin = 12;
int reset_pin = 13;

// Variables
int sleep=0;

unsigned long startTime = 0;

unsigned int currentTime;
String hrs;
String mins;
String secs;
String timeStamp;

void(* resetFunc) (void) = 0;//declare reset function at address 0

String getTimeStamp() {

  currentTime = millis() / 1000;  
  
  // Get hours
  if (currentTime >= 36000) {
    hrs = String(currentTime / 3600);
  } else if (currentTime >= 3600) {
    hrs = String ("0" + String(currentTime / 3600));
  } else {
    hrs = String ("00");
  }

  // Get minutes
  currentTime = currentTime % 3600; // currentTime now just remainder after full hours removed
  if (currentTime >= 600) {
    mins = String(currentTime / 60);
  } else if (currentTime >= 60) {
    mins = String ("0" + String(currentTime / 60));
  } else {
    mins = String ("00");
  }

  // Get seconds
  currentTime = currentTime % 60; // currentTime now just remainder after full minutes removed
  if (currentTime > 9) {
    secs = String(currentTime);
  } else {
    secs = String ("0" + String(currentTime));
  }

  String timeStamp = String (hrs + ":" + mins + ":" + secs);
  return timeStamp;
}


void setStartTime(){
  startTime = millis();
}


void setup() {
  Serial.begin(9600);
  for(int x=greenLed_pin;x<=buzzer_pin;x++){
    pinMode(x, OUTPUT);  
  } 
  for(int x=sleep_pin;x<=reset_pin;x++){
    pinMode(x, INPUT_PULLUP); 
  } 
}

void loop() {
  Serial.print("Run time: ");
  Serial.print(getTimeStamp());
  
  int checkSleepButton = digitalRead(sleep_pin);
  if(checkSleepButton==0){
    delay(1000);
    if (sleep == 0){
      sleep = 1;
    }else{
      sleep = 0;
      setStartTime();
    }
  }
  
  if (sleep==1) {
    // Lights flash as visual indicator of sleeping
    // Serial output also indicates sleeping
    if ((millis() /1000) % 2 == 0) {
      digitalWrite(greenLed_pin,HIGH);
      digitalWrite(yellowLed_pin,LOW);
      digitalWrite(redLed_pin,HIGH);
    }else{
     digitalWrite(greenLed_pin,LOW);
     digitalWrite(yellowLed_pin,HIGH); 
     digitalWrite(redLed_pin,LOW);
    }
    Serial.println(" | Sleeping");
  }else{
    if (millis() - startTime > 600000){
      digitalWrite(greenLed_pin,HIGH);
    } else {
      digitalWrite(greenLed_pin,LOW);
      }
    if (millis() - startTime > 600000 * 2){
      digitalWrite(yellowLed_pin,HIGH);
    } else {
      digitalWrite(yellowLed_pin,LOW);
      }
    if (millis() - startTime > 600000 * 3){
      digitalWrite(redLed_pin,HIGH);
      digitalWrite(buzzer_pin,HIGH);
    } else {
      digitalWrite(redLed_pin,LOW);
      digitalWrite(buzzer_pin,LOW);
      }
  
    // Serial.print("sleep: ");
    // Serial.print(sleep);
//    Serial.print("Run time: ");
//    Serial.print(getTimeStamp());
    Serial.print(" | seconds up: ");
    Serial.print(millis() / 1000);
    // Serial.print("| start Time (Mseconds): ");
    // Serial.print(startTime);
    Serial.print("| start Time (seconds): ");
    Serial.print(startTime / 1000);
    Serial.print(" | elapsed seconds: ");
    Serial.println((millis()-startTime)/1000);
  }

  int checkResetButton = digitalRead(reset_pin);
  // Serial.print("reset Button : ");
  // Serial.println(checkResetButton);
  if(checkResetButton==0){
    delay(1000);
    //startTime = millis();
    setStartTime();
    //resetFunc(); //call reset 
  }
  delay(75);
}
