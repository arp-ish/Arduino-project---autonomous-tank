///////////////////////   OBSTACLE AVOIDING CAR. WITH 3 SENSORS; 2 front and 1 back:    //////////////////////////
//////////////////////////   nr.1 left_front, nr.2 right_front, nr.3 back_middle.    ////////////////////////////

#include <NewPing.h>
#include <String.h>

int SpeedLow = 130;
int SpeedMed = 200;
int SpeedHigh = 250;
int drive_velocity_1 = 120;
int drive_velocity_2 = 104;
// defines variables
    long duration;
    int distance;

#define enA 7
#define in1 3
#define in2 4
#define enB 2
#define in3 5
#define in4 6

NewPing sensors[3] = {           // Array of sensors of 3 sensors.   // SENSOR  - (TRIG,ECHO, MAX allowed distance[cm])
  NewPing (10,8, 200),       // SENSOR 1  - LEFT FRONT.
  NewPing (11,9, 200),       // SENSOR 2  - RIGHT FRONT.
  NewPing (12,13, 200)       // SENSOR 3  - BACK MIDDLE 
};      

int threshold_min = 18;  // 18 | [cm] threshold distance to stop motors for sensor 3 which look ahead.
int threshold_max = 40;  // 40 | [cm] threshold distance to stop motors for sensor 3 which look ahead.
int threshold_30 = 40;   // [cm] threshold distance to stop motors for sensor 2 which looks with 30 deg. angle.
int threshold_90 = 36;   // [cm] threshold distance to stop motors for sensor 1 which looks with 90 deg. angle.

int threshold_LF = 36;   // 36 | [cm] LEFT, front threshold distance to stop motors for sensor 1 which looks with  for LEFT angle.
int threshold_RF = 36;   // 36 | [cm] RIGHT,front threshold distance to stop motors for sensor 2 which looks with for RIGHT angle.

void FRONT(); void BACK(); void RIGHT_F(); void LEFT_F(); void RIGHT_B(); void LEFT_B(); void STOP();
 
void setup() {
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  
  pinMode(enA, OUTPUT);   // RIGHT MOTOR - SPEED
  pinMode(enB, OUTPUT);   // LEFT MOTOR  - SPEED
  
  pinMode(in1, OUTPUT);   // RIGHT MOTOR - REVERSE RS
  pinMode(in2, OUTPUT);   // LEFT MOTOR  - REVERSE LS
  
  pinMode(in3, OUTPUT);   // RIGHT MOTOR - FORWARD RS
  pinMode(in4, OUTPUT);   // LEFT MOTOR  - FORWARD LS

  delay(3000);          //deley 3 sek.

}
 
void loop() {
    

 ///// SENSOR NO.1 - 90 degree LEFT.      Sensor look for obstacle 90 deg. on left side | TURN LEFT
  if (sensors[0].ping_cm() < threshold_90 && sensors[0].ping_cm()> 0){  
      digitalWrite(enA, drive_velocity_1 +30);
      digitalWrite(enB, drive_velocity_2 +30);
      LEFT_F(); 
      MeshSonar(0,"Sensor LEFT 90: ");
    }
    
   else  { // SENSOR NO.5   | TURN RIGHT 90 degree
        if (sensors[1].ping_cm() < threshold_90 && sensors[1].ping_cm() > 0){ //  90 degree RIGHT. Sensor look for obstacle 90 deg. on right side.
            digitalWrite(enA, drive_velocity_2 +30);                //digitalWrite(enA, drive_velocity_1 +30);
            digitalWrite(enB, drive_velocity_1 +30);                //digitalWrite(enB, drive_velocity_2 +30);
            RIGHT_F();
            MeshSonar(1,"Sensor RIGHT 90: ");
        }
   
        else { // SENSOR NO.2 | TURN LEFT 30 degree
            if(sensors[0].ping_cm() <= threshold_30 && sensors[0].ping_cm()> 0){ // 30   degree left. Sensor look for obstacle 30 deg. on left side
              digitalWrite(enA, drive_velocity_1);
              digitalWrite(enB, drive_velocity_2); 
              LEFT_F();
              MeshSonar(0,"Sensor LEFT 30: ");
            }
            
             else{ // SENSOR NO.4 | TURN RIGHT 30 degree
                  if(sensors[1].ping_cm() <= threshold_30 && sensors[1].ping_cm()> 0){ //   30   degree left. Sensor look for obstacle 30 deg. on left side
                    digitalWrite(enA, drive_velocity_1);
                    digitalWrite(enB, drive_velocity_2); 
                    RIGHT_F();
                    MeshSonar(1,"Sensor RIGHT 30: ");
                    }
                  else {   
                       ///////////////////   
                       // SENSOR NO.1 & NO.2       
                       // DRIVES FORWARD
                        if (sensors[0].ping_cm() > threshold_max){
                          
                          digitalWrite(enA, drive_velocity_1);
                          digitalWrite(enB, drive_velocity_1);        // with 2 two forward sensor (LEFT & RIGHT): digitalWrite(enB, drive_velocity_2);
                          FRONT();
                          MeshSonar(0,"Sensor FORWARD 0 0: ");
                          
                        }
                        if (sensors[1].ping_cm() > threshold_max){
                          
                          digitalWrite(enA, drive_velocity_1);
                          digitalWrite(enB, drive_velocity_1);        // with 2 two forward sensor (LEFT & RIGHT): digitalWrite(enB, drive_velocity_2);
                          FRONT();
                          MeshSonar(1,"Sensor FORWARD 1 1: ");
                          
                        }
                        
                        
                        //////// CAR STOPES ///////////////
                        if (sensors[0].ping_cm() > threshold_min && sensors[0].ping_cm() < threshold_max ){
                          digitalWrite(enA, 0);
                          digitalWrite(enB, 0);      
                          STOP();  
                          MeshSonar(1,"Sensor STOP 0 0: ");
                        } 
                        if (sensors[1].ping_cm() > threshold_min && sensors[1].ping_cm() < threshold_max ){                         
                          digitalWrite(enA, 0);
                          digitalWrite(enB, 0);    
                          STOP();    
                          MeshSonar(1,"Sensor STOP 1 1: ");
                        }  
                         
                         ////////////// CAR REVERES BACK //////////////
                         if (sensors[0].ping_cm() <= threshold_min && sensors[0].ping_cm() > 0){
                           digitalWrite(enA, drive_velocity_1);
                           digitalWrite(enB, drive_velocity_1);  
                           BACK();
                           MeshSonar(1,"Sensor BACK 0 0: ");      
                         }   
                         if (sensors[0].ping_cm() <= threshold_min && sensors[0].ping_cm() > 0){
                           digitalWrite(enA, drive_velocity_1);
                           digitalWrite(enB, drive_velocity_1); 
                           BACK();
                           MeshSonar(1,"Sensor FORWARD 1 11: ");       
                         } 
                  }
            }     
        }
    } 
}

void MeshSonar(int i,char* a){
   delay(50);
   unsigned int distance = sensors[i].ping_cm();
   Serial.print(a);
   Serial.print(distance);
   Serial.println("cm");
}


void FRONT() {
  //digitalWrite(enA, drive_velocity_1);                
  //digitalWrite(enB, drive_velocity_2); 
  digitalWrite(in1,LOW);    // REVERSE - RIGHT
  digitalWrite(in2,LOW);    // REVERSE LEFT  
  digitalWrite(in3,HIGH);   // FORWARD RIGHT
  digitalWrite(in4,HIGH);   // FORWARD LEFT
}
void BACK(){ 
  //digitalWrite(enA, drive_velocity_2);                
  //digitalWrite(enB, drive_velocity_1); 
  digitalWrite(in1,HIGH);    // REVERSE - RIGHT
  digitalWrite(in2,HIGH);    // REVERSE LEFT  
  digitalWrite(in3,LOW);     // FORWARD RIGHT
  digitalWrite(in4,LOW);     // FORWARD LEFT
}

void RIGHT_F(){
  //digitalWrite(enA, drive_velocity_1);                
  //digitalWrite(enB, drive_velocity_2);
  digitalWrite(in1,LOW);    // REVERSE - RIGHT
  digitalWrite(in2,LOW);    // REVERSE LEFT  
  digitalWrite(in3,HIGH);   // FORWARD RIGHT
  digitalWrite(in4,LOW);    // FORWARD LEFT
 }
 void LEFT_F() {
  //digitalWrite(enA, drive_velocity_1);                
  //digitalWrite(enB, drive_velocity_2); 
  digitalWrite(in1,LOW);    // REVERSE - RIGHT
  digitalWrite(in2,LOW);    // REVERSE LEFT  
  digitalWrite(in3,HIGH);    // FORWARD RIGHT
  digitalWrite(in4,HIGH);   // FORWARD LEFT
 }
 void RIGHT_B(){
  //digitalWrite(enA, drive_velocity_2);                
  //digitalWrite(enB, drive_velocity_1);
  digitalWrite(in1,HIGH);   // REVERSE - RIGHT
  digitalWrite(in2,LOW);    // REVERSE LEFT  
  digitalWrite(in3,LOW);    // FORWARD RIGHT
  digitalWrite(in4,LOW);    // FORWARD LEFT
 }
 void LEFT_B() {
  //digitalWrite(enA, drive_velocity_2);                
  //digitalWrite(enB, drive_velocity_1); 
  digitalWrite(in1,LOW);    // REVERSE - RIGHT
  digitalWrite(in2,HIGH);    // REVERSE LEFT  
  digitalWrite(in3,LOW);    // FORWARD RIGHT
  digitalWrite(in4,LOW);   // FORWARD LEFT
 }
 void STOP(){
  //digitalWrite(enA, 0);                
  //digitalWrite(enB, 0);
  digitalWrite(in1,LOW);     //STOP
  digitalWrite(in2,LOW);     //STOP
  digitalWrite(in3,LOW);     //STOP
  digitalWrite(in4,LOW);     //STOP
 }
