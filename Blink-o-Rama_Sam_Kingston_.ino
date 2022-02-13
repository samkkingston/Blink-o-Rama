/*
  Blink-o-Rama
  Sam Kingston
  DIGF-3010-001 Advanced Wearable Electronics
  OCAD University
  Created on 2022-02-09
*/

//DECLARING PINS AND VARIABLES
const int rightLED = A3;
const int commonLED = A0;
const int leftLED = A2;
int tPin = A6;
int iPin = A7;
int mPin = A1;
int pPin = A5;
int pinkyButton = 0;
int indexButton = 0;
int middleButton = 0;
int hazzardCount = 0;



void setup() {
  //IDENTIFYING PINS AS EITHER INPUT OR OUTPUT
  pinMode(rightLED, OUTPUT);
  pinMode(commonLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(tPin, OUTPUT);
  pinMode(iPin, INPUT);
  pinMode(mPin, INPUT);

  digitalWrite(tPin, HIGH);         //THUMB PIN IS SET TO HIGH TO TRIGGER CONDUCTIVE FABRIC ON OTHER FINGERS

  Serial.begin(9600);
}

void loop() {

  indexButton = digitalRead(iPin);        //CHECK STATUS OF INDEX PIN
  middleButton = digitalRead(mPin);       //CHECK STATUS OF MIDDLE PIN

  if (indexButton == HIGH) {    //IF INDEX PIN RETURNS HIGH, RUN THE RIGHT TURN FUNCTION
    rightTurn();
  }

  if (middleButton == HIGH) {   //IF MIDDLE PIN RETURNS HIGH, RUN THE LEFT TURN FUNCTION
    leftTurn();
  }

  hazzardCounter();   //RUN THE HAZARD COUNTER FUNCTION ON EACH LOOP
}

void hazzardCounter() {

  pinkyButton = digitalRead(pPin);    //CHECK STATUS OF PINKY PIN

  if (pinkyButton == HIGH) {  //IF PINKY PIN RETURNS HIGH, INCREASE HAZZARD COUNT VARIABLE BY 1
    hazzardCount += 1;
  }

  if (hazzardCount > 1) {   //IF HAZZARD COUNTER IS ABOVE ONE, SET HAZZARD COUNTER BACK TO 0.
    hazzardCount = 0;       //THIS ENSURES THAT HAZZARD COUNT TOGGLES BETWEEN 0 AND ONE EACH TIME IT'S ACTIVATED
  }

  Serial.println(hazzardCount);
  Hazzards();     //RUN THE HAZZARD FUNCTION
}

void leftTurn() {   //LOOPS ONLY ONCE-USER CAN HOLD AND RELEASE FINGER FOR THE DURATION OF THE SIGNAL
  Serial.println("left");
  digitalWrite(leftLED, HIGH);
  digitalWrite(commonLED, HIGH);
  delay(250);
  digitalWrite(leftLED, LOW);
  digitalWrite(commonLED, LOW);
  //delay(250);----------NO DELAY NEEDED-HAZZARD FUNCTION TAKES CARE OF THIS
}

void rightTurn() {  //LOOPS ONLY ONCE-USER CAN HOLD AND RELEASE FINGER FOR THE DURATION OF THE SIGNAL
  Serial.println("right");
  digitalWrite(rightLED, HIGH);
  digitalWrite(commonLED, HIGH);
  delay(250);
  digitalWrite(rightLED, LOW);
  digitalWrite(commonLED, LOW);
  //delay(250);----------NO DELAY NEEDED-HAZZARD FUNCTION TAKES CARE OF THIS
}

void Hazzards() {

  if (hazzardCount == 1) {    //LOOPS WITH ALL LEDS FLASHING SO LONG AS PINKY TOGGLE REMAINS ACTIVATED
    Serial.println("Hazzards On");
    digitalWrite(rightLED, HIGH);
    digitalWrite(commonLED, HIGH);
    digitalWrite(leftLED, HIGH);
    delay(250);
    digitalWrite(rightLED, LOW);
    digitalWrite(commonLED, LOW);
    digitalWrite(leftLED, LOW);
    delay(250);
  }


  else {    //ONCE TOGGLE IS PRESSED FOR A SECOND TIME, TURN AND KEEP OFF ALL LEDS
    digitalWrite(rightLED, LOW);
    digitalWrite(commonLED, LOW);
    digitalWrite(leftLED, LOW);
    delay(250);   //KEEPS LEDS FROM BEING SET TO LOW TOO FREQUENTLY RESULTING IN UNDESIREABLE RESULTS
    //THIS DELAY REPLACES THE LAST DELAY IN THE RIGHT AND LEFT TURN FUNCTIONS BECAUSE OF THE ORDER THAT THE FUNCTIONS LOOP/
  }
}
