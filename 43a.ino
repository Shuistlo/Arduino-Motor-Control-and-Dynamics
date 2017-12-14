#include<Encoder.h>

Encoder myEnc(2,3);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
 
}

double intStartTime = 0;
double currentPosition = -999.0;
double goalPosition = 1;
double Kp = 4.5;
double Kd = 1;
double Vout11 = 0;
double Vout9=0;
double prevError = 0;
double currError = 0;

double riseTime = 0;

double startLoop = 0;
double endLoop = 0;

void loop() {
  double currTime = millis();
 // goalPosition = sin(currTime);
  if( (currTime - intStartTime) >= 10){
      currentPosition = myEnc.read();
      double radPosition = (currentPosition*2*PI)/(28*298);
      Serial.println(radPosition);
      Serial.println("looping");
      
      currError = goalPosition - radPosition; //steady state
      double dervError = (currError - prevError)/(currTime - intStartTime);

      double C = Kp*currError + Kd*dervError;  
      prevError = currError;

      //converting controller output units
     double value = C *255 / 5;
      if(abs (C) <= 5){
        if(value>0){
          Vout11 = 0;
          Vout9 = value;
        }
        else {
          Vout11 = -value;
          Vout9 = 0;
 
        }
        
      analogWrite(9,Vout9);
      analogWrite(11,Vout11); 
      
      }    

      if((radPosition < (goalPosition/10*9) )&& (radPosition > (goalPosition/10))){
        riseTime = currTime;
        
      }

     /*if(goalPosition < 1/20 * 19){
        startLoop = currTime;
      }
      if(goalPosition > -1/20 * 19){
        endLoop = currTime;
        Serial.println("rise");
        Serial.println(endLoop - startLoop);
      }*/

      Serial.println(currError); //overshoot only the final time    
      intStartTime = currTime;
      Serial.println(riseTime);
     }  
  
}


