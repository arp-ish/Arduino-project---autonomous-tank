<<<//OBSTACLE AVOIDING CAR. WITH 5 SENSORS; nr.1 left_90, nr.2 left_30, nr.3 FRONT_0, nr.4 right_30, nr.5 right 90.
#include <NewPing.h>
//#include <AFMotor.h>

//char t;                          // BLUETOOTH
int drive_velocity_1 = 120;
int drive_velocity_2 = 104;

#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7

NewPing sensors[5] = {           // Array of sensors of 3 sensors.
  NewPing (6,6, 200),       // SENSOR 1  - LEFT 90, degree
  NewPing (9,9, 200),       // SENSOR 2  - LEFT 30, degree
  NewPing (16,16, 200),     // SENSOR 3  - FRONT 0, degree
  NewPing (13,13, 200),     // SENSOR 4  - RIGHT 30, degree
  NewPing (14,14, 200)      // SENSOR 5  - RIGHT 90, degree
};

int threshold_min = 12;  // 18 | [cm] threshold distance to stop motors for sensor 3 which look ahead.
int threshold_max = 35;  // 40 | [cm] threshold distance to stop motors for sensor 3 which look ahead.
int threshold_30 = 46;  // [cm] threshold distance to stop motors for sensor 2 which looks with 30 deg. angle.
int threshold_90 = 36;  // [cm] threshold distance to stop motors for sensor 1 which looks with 90 deg. angle.

 void FORWARD();
 void REVERSE();
 void RIGHT();
 void LEFT();
 void STOP();
 
void setup() {
  //Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  
  pinMode(enA, OUTPUT);   // RIGHT MOTOR - SPEED
  pinMode(enB, OUTPUT);   // LEFT MOTOR - SPEED
  
  pinMode(in1, OUTPUT);   // RIGHT MOTOR  - Forward
  pinMode(in2, OUTPUT);   // RIGHT MOTOR  - Reverse
  
  pinMode(in3, OUTPUT);   // LEFT MOTOR - Forward
  pinMode(in4, OUTPUT);   // LEFT MOTOR - Reverse

  delay(3000);
}
 
void loop() {

  ///// SENSOR NO.1 - 90 degree LEFT.      Sensor look for obstacle 90 deg. on left side | TURN LEFT
  if (sensors[0].ping_cm() < threshold_90 && sensors[0].ping_cm()> 0){  
      
      LEFT();
      digitalWrite(enA, drive_velocity_1 +30);
      digitalWrite(enB, drive_velocity_2 +30); 
    }
    
   else  { // SENSOR NO.5   | TURN RIGHT 90 degree
      if (sensors[4].ping_cm() < threshold_90 && sensors[4].ping_cm() > 0){ //  90 degree RIGHT. Sensor look for obstacle 90 deg. on right side.
          RIGHT();
          digitalWrite(enA, drive_velocity_2 +30);                //digitalWrite(enA, drive_velocity_1 +30);
          digitalWrite(enB, drive_velocity_1 +30);                //digitalWrite(enB, drive_velocity_2 +30);
          }
 
      else { // SENSOR NO.2 | TURN LEFT 30 degree
        if(sensors[1].ping_cm() <= threshold_30 && sensors[1].ping_cm()> 0){ // 30   degree left. Sensor look for obstacle 30 deg. on left side
          LEFT();
          digitalWrite(enA, drive_velocity_1);
          digitalWrite(enB, drive_velocity_2); 
          }
        
          else{ // SENSOR NO.4 | TURN RIGHT 30 degree
            if(sensors[3].ping_cm() <= threshold_30 && sensors[3].ping_cm()> 0){ //   30   degree left. Sensor look for obstacle 30 deg. on left side
              RIGHT();
              digitalWrite(enA, drive_velocity_1);
              digitalWrite(enB, drive_velocity_2); 
              }
            else {
              // SENSOR NO.3      0 degrees front, FINal angle adjustment when sensor 3 sees an object
                // DRIVES FORWARD
                  if (sensors[2].ping_cm() > threshold_max){
                    FORWARD();
                    digitalWrite(enA, drive_velocity_1);
                    digitalWrite(enB, drive_velocity_1);        // with 2 two forward sensor (LEFT & RIGHT): digitalWrite(enB, drive_velocity_2);
                  }
                  //CAR STOPES
                  if (sensors[2].ping_cm() > threshold_min && sensors[2].ping_cm() < threshold_max ){
                    STOP();
                    digitalWrite(enA, 0);
                    digitalWrite(enB, 0);        
                  }  
                   //CAR REVERES BACK
                   if (sensors[2].ping_cm() <= threshold_min && sensors[2].ping_cm() > 0){
                     REVERSE();
                     digitalWrite(enA, drive_velocity_1);
                     digitalWrite(enB, drive_velocity_1);        
                   }   
              }
          }
      }
   } 
}

void FORWARD() {
  digitalWrite(in1,HIGH);    //FORWARD
  digitalWrite(in2,LOW);     //STOP  
  digitalWrite(in3,HIGH);    //Forward
  digitalWrite(in4,LOW);     //STOP
}
void REVERSE(){
  
  digitalWrite(in1,LOW);      //STOP
  digitalWrite(in2,HIGH);    //Reverse
  digitalWrite(in3,LOW);     //STOP
  digitalWrite(in4,HIGH);    //Reverse
}

void RIGHT(){
  digitalWrite(in1,HIGH);    //FORWARD RIGHT
  digitalWrite(in2,LOW);     //STOP
  digitalWrite(in3,LOW);     //STOP
  digitalWrite(in4,HIGH);    //REVERSE LEFT
 }
 void LEFT() {  
  digitalWrite(in1,LOW);     //STOP
  digitalWrite(in2,HIGH);    //REVERSE RIGHT
  digitalWrite(in3,HIGH);    //FORWARD LEFT
  digitalWrite(in4,LOW);     //STOP
 }
 void STOP(){

  digitalWrite(in1,LOW);     //STOP
  digitalWrite(in2,LOW);     //STOP
  digitalWrite(in3,LOW);     //STOP
  digitalWrite(in4,LOW);     //STOP
 }
