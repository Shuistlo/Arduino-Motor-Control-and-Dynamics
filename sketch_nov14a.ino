#include<Encoder.h>

Encoder myEnc(2,3);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
 
}

long intStartTime = 0;
long currentPosition = -999;
long goalPosition = 0;
long Kp = 1;
long Kd = 1;
long Vout11 = 0;
long Vout9=0;
long prevError = 0;
long currError = 0;


void loop() {
  long currTime = millis();
  if( (currTime - intStartTime) > 100){
      currentPosition = myEnc.read();
      float radPosition = currentPosition/180*PI;
      //Serial.println(radPosition);
      //Serial.println(newPosition);
      //actual code fun fun
      Serial.println("looping");
      intStartTime = millis();
      
      //calculating controller output 
      //long velocity = (currentPosition - oldPosition)/(currTime - intStartTime);
      //old position is the same
      currError = goalPosition - radPosition; 
      long dervError = (currError - prevError)/(currTime - intStartTime);
      long C = Kp*currError + Kd*dervError;  
      prevError = currError;

      //converting controller output units
     float value = C *255 / 5;
      if(abs (C) <= 5){
        if(value>0){
          Vout11 = value;
          Vout9 = 0;
        }
        else {
          Vout11 = 0;
          Vout9 = value;    
        }
        
        analogWrite(9,Vout9);
        analogWrite(11,Vout11);
      }          

  }
      
}
