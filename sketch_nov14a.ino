#include<Encoder.h>

Encoder myEnc(2,3);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
 
}

long intStartTime = 0;
long oldPosition = -999;
long Kp = 1;
long Kd = 1;
long e = 0;
long f = 0;
long Vout11 = 0;
long Vout9=0;


void loop() {
  long currTime = millis();
  if( (currTime - intStartTime) > 100){
      long newPosition = myEnc.read();
      float radPosition = newPosition/180*PI;
      Serial.println(radPosition);
      Serial.println(newPosition);
      //actual code fun fun
      Serial.println("looping");
      intStartTime = millis();
      
      //calculating controller output 
      long velocity = (newPosition - oldPosition)/(currTime - intStartTime);
      //old position is the same
      e = 1 - sin(f*t); //rad? f*t?
      long C = Kp*e + Kd*(f*cos(f*t)); //ask TA to check derivate 

      //converting controller output units
      value = C *255 / 5;
      if(abs (C) =<5){
        if(C>0){
          Vout11 = C;
          Vout9 = 0;
        }
        else 
          Vout11 = 0;
          Vout9 = C;    
        }
        
        analogWrite(9,Vout9);
        analogWrite(11,Vout11);
      }           
      
      
  }
}
