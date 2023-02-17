//bouton start/stop
const int bouton1 = 12;
boolean boutonStart = false;

const int bouton2 = 13;
boolean boutonStop = false;


#include "Seeed_vl53l0x.h"
Seeed_vl53l0x VL53L0X;
float r = 0; //la distance calculée par le laser
float theta = 0;
float z=0;

//moteur donnant une rotation
#define IN1 11
#define IN2 10
#define IN3 9
#define IN4 8
#include<Stepper.h>
int Steps = 0;
int Direction = 0;
int number__steps = 512;

double stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution,8,10,9, 11);

//moteur donnant une hauteur z
#define IN5 4
#define IN6 5
#define IN7 6
#define IN8 7
int temps_2 = 1000; // temps de pause du moteur 2 (pour la hauteur) pour laisser le temps au moteur 2 de tourner

Stepper myStepper2(stepsPerRevolution,4,6,5,7);

void setup() {

    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    Serial.begin(115200);
    Status = VL53L0X.VL53L0X_common_init();
    if (VL53L0X_ERROR_NONE != Status) {
        Serial.println("start vl53l0x mesurement failed!");
        VL53L0X.print_pal_error(Status);
        while (1);
    }

    VL53L0X.VL53L0X_high_accuracy_ranging_init();

    if (VL53L0X_ERROR_NONE != Status) {
        Serial.println("start vl53l0x mesurement failed!");
        VL53L0X.print_pal_error(Status);
        while (1);
    }
     myStepper.setSpeed(15);
     myStepper2.setSpeed(15);
}


void loop() {
    //Serial.println(digitalRead(bouton1));
    if (digitalRead(bouton1)==1){
      boutonStart=true;
    }
    if (digitalRead(bouton2)==1){
         boutonStop=true;
    }
    while (boutonStart==true && boutonStop==false){
      for (int i=0;i<128;i++){
      if (digitalRead(bouton2)==1){
         boutonStop=true;
         break;
      }
      VL53L0X_RangingMeasurementData_t RangingMeasurementData;
      VL53L0X_Error Status = VL53L0X_ERROR_NONE;
  
      memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));
      Status = VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
  
      if (VL53L0X_ERROR_NONE == Status) {
          if (RangingMeasurementData.RangeMilliMeter >= 4000) {
        
          } else {
              r = RangingMeasurementData.RangeMilliMeter;
              theta+=PI/64;
              Serial.print(r*sin(theta)); //coordonnées selon x
              Serial.print(" ");
              Serial.print(r*cos(theta)); //selon y
              Serial.print(" ");
              Serial.println(z);
            //  Serial.println(digitalRead(bouton1));
            //  Serial.println(digitalRead(bouton2));
              }
      
          }
       
      delay(300);
      myStepper.step(stepsPerRevolution/64);
      delay(300);
     
      }
      
    
      if (boutonStop==false){
        for (int j=0;j<4;j++){
         myStepper2.step(-stepsPerRevolution); //à modifier selon la hauteur souhaité
        }
        z+=4; //on définit un mouvement comme 2 unités
      }
  }

  
   for (int f=0;f<z;f++){
    myStepper2.step(stepsPerRevolution);
   }
}
