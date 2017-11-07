#include<Encoder.h>

Encoder myEnc(2,3);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
 
}

long intStartTime = 0;
long oldPosition = -999;

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
      
    
  }
   

}
