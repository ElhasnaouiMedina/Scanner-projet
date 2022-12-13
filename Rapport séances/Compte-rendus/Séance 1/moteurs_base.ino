#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#include<Stepper.h>
int temps = 10;
int i = 0;
int nombrepas = 2048;

void setup(){
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
}

void loop () {
   for(i=0; i <= 1; i++){
//    Stepper monmoteur(nombrepas, PIN1, PIN2, PIN3, PIN4);
//    monmoteur.setSpeed(5000);
//    monmoteur.step(nombrepas);
    Serial.println(i);  
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
  

   }
   
}
