//capteur de distance
#include "Seeed_vl53l0x.h"
Seeed_vl53l0x VL53L0X;
float r = 0; //la distance calculée par le laser

int i = 0;
int j=0;
//moteur donnant une rotation
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#include<Stepper.h>
int temps = 10;
int temps_1 = 1000; // temps de pause du moteur 1 (pour la rotation) 
int nombrepas = 2048;
float theta = 0; //angle de rotation de la plaque tournante

//moteur donnant une hauteur z
#define IN5 8
#define IN6 9
#define IN7 10
#define IN8 11
int temps_2 = 1000; // temps de pause du moteur 2 (pour la hauteur) pour laisser le temps au moteur 2 de tourner
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

    //setup du moteur donnant une rotation de la plaque tournante
      Serial.begin(115200);
      pinMode(IN1, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(IN3, OUTPUT);
      pinMode(IN4, OUTPUT);
    //fin du setup du moteur donnant une rotation de la plaque tournante

    //setup du moteur donnant une hauteur z
      Serial.begin(115200);
      pinMode(IN5, OUTPUT);
      pinMode(IN6, OUTPUT);
      pinMode(IN7, OUTPUT);
      pinMode(IN8, OUTPUT);
    //fin du setup du moteur donnant une hauteur z
     
}


void loop() {
      for(i=0; i <= 512; i++){ 
        VL53L0X_RangingMeasurementData_t RangingMeasurementData;
        VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    
        memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));
        Status = VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
  
          if (VL53L0X_ERROR_NONE == Status) {
              if (RangingMeasurementData.RangeMilliMeter >= 2000) {            
              } else {
                  
                  r = RangingMeasurementData.RangeMilliMeter;
                  Serial.print(r*sin(theta)); //coordonnées selon x
                  Serial.print(" ");
                  Serial.print(r*cos(theta)); //selon y
                  Serial.print(" ");
                  Serial.println(z);
                  
              }
          }
        delay(300);
  
        
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        delay(temps);
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
        if (i%32){
          theta+=PI/20;
        }
       
     }
     delay(temps_1);
     for(j=0; j <= 512; j++){ //à modifier

        digitalWrite(IN5, LOW);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, HIGH);
        delay(temps);
        digitalWrite(IN5, LOW);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, HIGH);
        digitalWrite(IN8, LOW);
        delay(temps);
        digitalWrite(IN5, LOW);
        digitalWrite(IN6, HIGH);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, LOW);
        delay(temps);
        digitalWrite(IN5, HIGH);
        digitalWrite(IN6, LOW);
        digitalWrite(IN7, LOW);
        digitalWrite(IN8, LOW);
        delay(temps); 
        
        
     }
     delay(temps_2);
     z+=2; //on définit un mouvement comme 2 unités (à modifier)

     
}
