//============================================================== DAGU 12 DOF Hexapod sample code =====================================
//                                                                 Written by: Russell Cameron


//#include <IRremote.h>                                      // IRremote library written by Ken Shirriff
//#include <IRremoteInt.h>                                   // the library can be downloaded from here: 
//                                           http://www.arcfn.com/2009/08/multi-protocol-infrared-remote-library.html




//--------------------------- different remotes will generate different values depending on make and model ---------------------------
//----------------------- use the IRtest mode and serial monitor to display the values received by your remote -----------------------

#define IRtest 0                                           // set to 1 for IR test mode




#include <Servo.h>                                         // Standard Arduino servo libarary

int svc[12]={                                              // servo center positions (typically 1500uS)
  1500,1550,1550,1450,                                     // D29 knee1, D46 Hip1, D47 knee2, D48 Hip2
  1500,1400,1500,1550,                                     // D49 knee3, D50 Hip3, D51 knee4, D24 Hip4
  1500,1500,1500,1400                                      // D25 knee5, D26 Hip5, D27 knee6, D28 Hip6
};

Servo sv[12];                                              // Yes! servos can be an array

int angle;                                                 // determines the direction/angle (0°-360°) that the robot will walk in 
int rotate;                                                // rotate mode: -1 = anticlockwise, +1 = clockwise, 0 = no rotation
int Speed;                                                 // walking speed: -15 to +15 
int Stride;                                                // size of step: exceeding 400 may cause the legs to hit each other

int RECV_PIN = 10;                                         // define D10 as input for IR receiver
//IRrecv irrecv(RECV_PIN);
//decode_results results;

void setup()
{
  Serial.begin (115200);
  Serial.println ("Stating to load program");

  pinMode(11,OUTPUT);                                      // use D11 as GND for IR receiver
  digitalWrite(11,0);
  pinMode(12,OUTPUT);                                      // use D12 as Vcc for IR receiver
  digitalWrite(12,1);
  
  sv[0].attach(29,800,2200);                               // knee 1 
  delay(40);
  sv[1].attach(46,800,2200);                               // Hip  1
  delay(40);
  sv[2].attach(47,800,2200);                               // knee 2
  delay(40);
  sv[3].attach(48,800,2200);                               // Hip  2
  delay(40);
  sv[4].attach(49,800,2200);                               // knee 3
  delay(40);
  sv[5].attach(50,800,2200);                               // Hip  3
  delay(40);
  sv[6].attach(10,800,2200);                               // knee 4
  delay(40);
  sv[7].attach(11,800,2200);                               // Hip  4
  delay(40);
  sv[8].attach(25,800,2200);                               // knee 5
  delay(40);
  sv[9].attach(26,800,2200);                               // Hip  5
  delay(40);
  sv[10].attach(27,800,2200);                              // knee 6
  delay(40);
  sv[11].attach(28,800,2200);                              // Hip  6
  delay(40);
  
  for(int i=0;i<12;i++)
  {
    sv[i].writeMicroseconds(svc[i]);                       // initialize servos
  }
  delay(3000);                                             // optional - gives you time to put the robot down before it starts
  
  /*  if(IRtest==1) Serial.begin(9600);                        // IR test mode displays IR receiver values on serial monitor
  irrecv.enableIRIn();                                     // Start the receiver
  */
}

void loop()
{ 
  /*  if (irrecv.decode(&results))                             // check for IR command
  {                                                        // change IRC comparison values to suit your TV, DVD, Stereo remote
    int IRC=results.value;
    if(IRtest==1) Serial.println(IRC);                     // display value from IR receiver on serial monitor in test mode
    
    if(IRC==2640 || IRC==528)                              // STOP
    {
      Speed=0;
      angle=0;
      rotate=0;
    }
    
    if(IRC==144 || IRC==2064)                              // FORWARD
    {
      Speed=10;
      rotate=0;
      angle=0;
    }
    
    if(IRC==2192 || IRC==3600)                             // REVERSE    
    {
      Speed=-10;
      rotate=0;
      angle=0;
    }
    
    if(IRC==1168)                                          // ROTATE CLOCKWISE  
    {
      Speed=10;
      rotate=1;
      angle=0;
    }
    
    if(IRC==3216)                                          // ROTATE COUNTER CLOCKWISE  
    {
      Speed=10;
      rotate=-1;
      angle=0;
    }
    
    if(IRC==16)                                            // 45 DEGREES    
    {
      Speed=10;
      rotate=0;
      angle=45;
    }
    
    if(IRC==3088)                                          // 90 DEGREES    
    {
      Speed=10;
      rotate=0;
      angle=90;
    }
    
    if(IRC==1552)                                          // 135 DEGREES    
    {
      Speed=10;
      rotate=0;
      angle=135;
    }
    
    if(IRC==272)                                           // 225 DEGREES    
    {
      Speed=10;
      rotate=0;
      angle=225;
    }
    
    if(IRC==2576)                                          // 270 DEGREES    
    {
      Speed=10;
      rotate=0;
      angle=270;
    }
    
    if(IRC==1040)                                          // 315 DEGREES    
    {
      Speed=10;
      rotate=0;
      angle=315;
    }
    irrecv.resume();                                       // receive the next value
  }
  
  if(IRtest==1) return;                                    // robot does not walk in IRtest mode
  */

  Speed = 10;
  rotate = 1;
  angle = 0;
    if (angle > 359)
    angle -= 360;
  else if (angle < 0)
    angle += 360;                                 // keep travel angle within 0°-360°
  if (angle>359) angle-=360;                               // keep travel angle within 0°-360°
  Serial.println("Walking");
  Serial.print ("Speed: ");
  Serial.print (Speed);
  Serial.print (" Rotate: ");
  Serial.print (rotate);
  Serial.print (" angle: ");
  Serial.println (angle);
  Walk();                                                  // move legs to generate walking gait
  delay(15);
}


void Walk()                                                // all legs move in a circular motion
{
  if(Speed==0)                                             // return all legs to default position when stopped
 {
    Stride-=25;                                            // as Stride aproaches 0, all servos return to center position
    if(Stride<0) Stride=0;                                 // do not allow negative values, this would reverse movements
  }
  else                                                     // this only affects the robot if it was stopped
  {
    Stride+=25;                                            // slowly increase Stride value so that servos start up smoothly
    if(Stride>450) Stride=450;                             // maximum value reached, prevents legs from colliding.
  }
  
  float A;                                                 // temporary value for angle calculations
  double Xa,Knee,Hip;                                      // results of trigometric functions
  static int Step;                                         // position of legs in circular motion from 0° to 360°                               
  
  Serial.println ("1 3 5");
  for(int i=0;i<6;i+=2)                                    // calculate positions for odd numbered legs 1,3,5
  {
    A=float(60*i+angle);                                   // angle of leg on the body + angle of travel
    if(A>359) A-=360;                                      // keep value within 0°-360°
   
    A*=PI/180;                                            // convert degrees to radians for SIN function
    
    Xa=Stride*rotate;                                      // Xa value for rotation
    if(rotate==0)                                          // hip movement affected by walking angle
    {
      Xa=sin(A)*(-Stride);                                   // Xa hip position multiplier for walking at an angle
    }
        
    A=float(Step);                                         // angle of leg
    A*=PI/180;                                            // convert degrees to radians for SIN function
    Knee=sin(A)*Stride;
    Hip=cos(A)*Xa;
    
    sv[i*2].writeMicroseconds(svc[i*2]+int(Knee));         // update knee  servos 1,3,5
    sv[i*2+1].writeMicroseconds(svc[i*2+1]+int(Hip));      // update hip servos 1,3,5
    Serial.print ("Knee: ");
    Serial.println (Knee);
    Serial.print (" Hip: ");
    Serial.println (Hip);
  }
  Serial.println ("2 4 6");
  for(int i=1;i<6;i+=2)                                    // calculate positions for even numbered legs 2,4,6
  {
    A=float(60*i+angle);                                   // angle of leg on the body + angle of travel
    if(A>359) A-=360;                                      // keep value within 0°-360°
   
    A*=PI/180;                                            // convert degrees to radians for SIN function
    Xa=Stride*rotate;                                      // Xa value for rotation
    if(rotate==0)                                          // hip movement affected by walking angle
    {
      Xa=sin(A)*(-Stride);                                   // Xa hip position multiplier for walking at an angle
    }
        
    A=float(Step+180);                                     // angle of leg
    if(A>359) A-=360;                                      // keep value within 0°-360°
    A*=PI/180;                                            // convert degrees to radians for SIN function
    Knee=sin(A)*Stride;
    Hip=cos(A)*Xa;
    
    sv[i*2].writeMicroseconds(svc[i*2]+int(Knee));         // update knee  servos 2,4,6
    sv[i*2+1].writeMicroseconds(svc[i*2+1]+int(Hip));      // update hip servos 2,4,6
  }
  
  Step+=Speed;                                             // cycle through circular motion of gait
  if (Step > 359)
    Step -= 360;
  else if (Step < 0)
    Step += 360;                         // keep value within 0°-360°

}
