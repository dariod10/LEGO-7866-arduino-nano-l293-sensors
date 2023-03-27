/* OVO JE OK
    LEGO 7866 (2 motors + blink cube) controled by l293
    2 sets of IR Sensors (LM393+IRLED+IRtransistor)
    l293
    2 button
    Arduino nano
    for 2 rail tracks 4 sensors (two sensor inputs on same pin)
    
    History:
    -Code portions from Geoff Bunza's sketch
    -Modified by Tom Kvichak 10/20/2018
    -From Lesson 07 Arduino Made Easy(er)
    -Adapted for myself (l293 and 2 button cntrl) by Dario Dominovic 18.03.2023.
 

                    wiring diagram

                          IR Sensor1
                          ---
           Arduino pin6---OUT pin
                     GND--GND pin
                   vcc5V--VCC pin
                          ---
                          
                          IR Sensor2
                          ---
           Arduino pin7---OUT pin
                      GND-GND pin
                   vcc5V--VCC pin
                          ---

                          Button DW
           Arduino pin8---pin a                         
             GND---R10k---pin a
                  vcc5V---pin b 

                          Button UP
           Arduino pin4---pin a                         
             GND---R10k---pin a
                  vcc5V---pin b                   

                            l293
                          ---__---
                   vcc5V--1      16--vcc5V
           Arduino pin3---2      15
      pin1 LEGO MOT(2)----3      14
                      GND-4      13-GND
                      GND-5      12-GND
      pin2 LEGO MOT(2)----6      11----pin minus LEGO BLINK brick (pin plus LEGO BLINK brick to VCC12V)
           Arduino pin2---7      10---Arduino pin5
                  VCC12V--8      9--vcc5V
                          --------  

*/

int motp1 = 2;                // (2) to l293 pin 7 - control motor pole 1 
int motp2 = 3;                // (3) to l293 pin 2 - control motor pole 2 
int blink = 5;                // (4) to l293 pin 10 - control blink brick
int sensor1 = 6;              // (5) IR sensor==Pin goes LOW when train detected
int sensor2 = 7;              // (6) IR sensor==Pin goes LOW when train detected
int buttUP = 4;               // (7) IR sensor==Pin goes LOW when train detected
int buttDW = 8;               // (8) IR sensor==Pin goes LOW when train detected


int entering_sensor = 6;      // (5) which sensor was triggered first
int leaving_sensor = 7;       // (6) which sensor shows train leaving
int sequence_started = 0;     // this says if the crossing is active
int sensor_count = 0;         // declare variable for while statement
int buttUPState = 0;  // variable for reading the pushbutton status
int buttDWState = 0;  // variable for reading the pushbutton status



void setup() {

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(motp1,OUTPUT);
  pinMode(motp2,OUTPUT);
  pinMode(buttUP, INPUT);
  pinMode(buttDW, INPUT);
  digitalWrite(motp1, HIGH);
  digitalWrite(motp2, HIGH);
  digitalWrite(blink, HIGH);
  digitalWrite(buttUP, LOW);
  digitalWrite(buttDW, LOW);
}

void loop() {
 
 if (digitalRead (buttDW) == HIGH) {
    sequence_started = 2; 
    power_motor_dw();
   }

  if (digitalRead (buttUP) == HIGH) {
    sequence_started = 0; 
    power_motor_up();

 }

 if ((digitalRead (sensor1) == LOW) && (sequence_started == 2)) {   // sensor LOW - sensor activated
    sequence_started = 1;                                            // 0 not activ, 1 activ
    leaving_sensor = sensor2;
      }
  if ((digitalRead (sensor2) == LOW) && (sequence_started == 2)) {
    sequence_started = 1;
    leaving_sensor = sensor1;
    
  } 






 
 if ((digitalRead (sensor1) == LOW) && (sequence_started == 0)) {   // sensor LOW - sensor activated
    sequence_started = 1;                                            // 0 not activ, 1 activ
    leaving_sensor = sensor2;
    power_motor_dw();
  }
  if ((digitalRead (sensor2) == LOW) && (sequence_started == 0)) {
    sequence_started = 1;
    leaving_sensor = sensor1;
    power_motor_dw();
  } 
 
  if ((digitalRead(leaving_sensor) == LOW) && (sequence_started == 1)) {  // train reach leaving sensor

    // as long as the leaving sensor is active the train is still in the crossing
    // while checks if train is gone yet
    while (sequence_started == 1) {
      sensor_count = 0;
       for (int i = 1; i < 40; i++) {
        if (digitalRead(leaving_sensor) == LOW) sensor_count++;
        delay (30);
      }
      if (sensor_count == 0) sequence_started = 0;
    }
    // At this point train is no longer over the leaving sensor
    power_motor_up();
            // ramp down
  }
}

void power_motor_up() {
  digitalWrite(motp1, HIGH);
  digitalWrite(motp2, LOW);
  delay(400);
  digitalWrite(motp1,HIGH);
  digitalWrite(motp2,HIGH);
  delay(1600);
  digitalWrite(blink, HIGH);
}

void power_motor_dw() {
  digitalWrite(blink, LOW);
  delay(2000);
  digitalWrite(motp1, LOW);
  digitalWrite(motp2, HIGH);
  delay(400);
  digitalWrite(motp1,HIGH);
  digitalWrite(motp2,HIGH);
    
  
}

