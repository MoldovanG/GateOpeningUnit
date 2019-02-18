#define BUTTON1_PIN 11
#define BUTTON2_PIN 12
#define INFRARED_PIN 13

#define RELAY1_OPENPLUS_PIN 2
#define RELAY1_OPENMINUS_PIN 3
#define RELAY2_CLOSEPLUS_PIN 4
#define RELAY2_CLOSEMINUS_PIN 5

#define LEDCOLORPIN A1
#define S0 6
#define S1 7
#define S2 8
#define S3 9
#define sensorOut 10
#include <IRremote.h>
#define OPEN 0
#define CLOSED 1
#define CODMINUS 0xFFE01F
#define CODPLUS 0xFFA857
IRrecv irrecv(INFRARED_PIN);
decode_results results;

int gatePosition;

void setup() {
  Serial.begin(9600);
  //Setting up the button pins 
  pinMode (BUTTON1_PIN, INPUT);
  pinMode (BUTTON2_PIN, INPUT);
  //done with buttons

  //setting up the relays 
  pinMode (RELAY1_OPENPLUS_PIN, OUTPUT);
  pinMode (RELAY1_OPENMINUS_PIN, OUTPUT);
  
  pinMode (RELAY2_CLOSEPLUS_PIN, OUTPUT);
  pinMode (RELAY2_CLOSEMINUS_PIN, OUTPUT);

  digitalWrite (RELAY1_OPENPLUS_PIN, HIGH);
  digitalWrite (RELAY1_OPENMINUS_PIN, HIGH);
  digitalWrite (RELAY2_CLOSEPLUS_PIN, HIGH);
  digitalWrite (RELAY2_CLOSEMINUS_PIN, HIGH);
  //done with relays

  //setting up the color sensor
  pinMode (LEDCOLORPIN, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(LEDCOLORPIN, LOW);
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  //done with color sensor

  //setting up infrared reading 
  irrecv.enableIRIn();
  //done with infreared
  
  gatePosition = CLOSED;
}

void openGate()
{
  Serial.println("Poarta se deschide");
  
  digitalWrite (RELAY1_OPENPLUS_PIN, LOW);
  digitalWrite (RELAY1_OPENMINUS_PIN, LOW);
  
  while (digitalRead(BUTTON1_PIN) == LOW);
  digitalWrite (RELAY1_OPENPLUS_PIN, HIGH); 
  digitalWrite (RELAY1_OPENMINUS_PIN, HIGH);
  Serial.println("Poarta s-a deschis");

  gatePosition = OPEN;
}
void closeGate()
{
  
  Serial.println("Poarta se inchide");
  
  digitalWrite (RELAY2_CLOSEPLUS_PIN, LOW);
  digitalWrite (RELAY2_CLOSEMINUS_PIN, LOW);
  
  while (digitalRead(BUTTON2_PIN) == LOW);
  
  digitalWrite (RELAY2_CLOSEPLUS_PIN, HIGH);
  digitalWrite (RELAY2_CLOSEMINUS_PIN, HIGH);
  
  Serial.println("Poarta s-a inchis");

  gatePosition = CLOSED;
}

void loop() {

  if (irrecv.decode (&results))
  {
    if (results.value == CODMINUS && gatePosition == CLOSED )
    {
      openGate();
    }
    else if (results.value == CODPLUS && gatePosition == OPEN)
    {
      closeGate();
    }
    irrecv.resume();
  }
  else {
    int redcolor, bluecolor,greencolor;
     // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  greencolor = pulseIn(sensorOut, LOW);
  
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(greencolor);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  redcolor = pulseIn(sensorOut, LOW);
  
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(redcolor);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  bluecolor = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(bluecolor);//printing RED color frequency
  Serial.println("  ");

  delay (1500);

  if (redcolor > 7000 && greencolor < 7000 && gatePosition == CLOSED )
      openGate();
  else if (redcolor < 7000 && greencolor > 7000  && gatePosition == OPEN) 
          closeGate();
       
  }

}
