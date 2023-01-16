//capteur de distance
#include "Seeed_vl53l0x.h"
Seeed_vl53l0x VL53L0X;
float r = 0; //la distance calculée par le laser
float theta = 0; //angle de rotation de la plaque tournante

//moteur donnant une hauteur z
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#include<Stepper.h>
int temps = 10;
int temps_2 = 1000; // temps de pause du moteur 2 (pour la hauteur) pour laisser le temps au moteur 2 de tourner
int i = 0;
int nombrepas = 2048;
float z=0; //coordonnées selon z de l'objet

void setup() {
    //setup du capteur de distance
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    Serial.begin(115200);
    Status = VL53L0X.VL53L0X_common_init();
    if (VL53L0X_ERROR_NONE != Status) {
        VL53L0X.print_pal_error(Status);
        while (1);
    }

    VL53L0X.VL53L0X_high_accuracy_ranging_init();

    if (VL53L0X_ERROR_NONE != Status) {
        
        VL53L0X.print_pal_error(Status);
        while (1);
    }
    //fin du setup du capteur de distance

    //setup du moteur donnant une hauteur z
      Serial.begin(115200);
      pinMode(IN1, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(IN3, OUTPUT);
      pinMode(IN4, OUTPUT);
    //fin du setup du moteur donnant une hauteur z
     
}


void loop() {
      for(i=0; i <= 512; i++){ //déterminer i
        VL53L0X_RangingMeasurementData_t RangingMeasurementData;
        VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
        memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));
        Status = VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
  
          if (VL53L0X_ERROR_NONE == Status) {
              if (RangingMeasurementData.RangeMilliMeter >= 2000) {            
              } else {
                  //r = RangingMeasurementData.RangeMilliMeter;
                  //Serial.println(r*sin(theta)); //coordonnées selon x
                  //Serial.println(r*cos(theta)); //coordonnées selon y
                  Serial.print(RangingMeasurementData.RangeMilliMeter);
              }
          }
        delay(300);
  
        
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        delay(temps);
        z+=2; //on définit un mouvement comme 2 unités (à modifier)
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        delay(temps);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        delay(temps);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        delay(temps); 
      
        Serial.print(" ");
        Serial.println(z);
     }
     delay(temps_2);

     
}
