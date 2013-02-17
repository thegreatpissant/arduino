#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

#define NUMLEGS 6
#define STEP 9
class leg {
private:
  int key;
public:
  int knee;
  int hip;
  int dir;
  Servo sknee;
  Servo ship;

  leg () {
    set_key (0);
  }
  void move () {
    sknee.write(knee);
    ship.write(hip);
  }
  void set_key ( int k)
  {
    key = k;
    //  Set the knee
    if (k >= 6 && k <= 16) {
      knee = 65;
    } 
    else {
      knee = 90;
    }

    //  Set the hip
    if (k >= 1 && k <=5) {
      hip = (STEP * k);
    } 
    else if (k >= 6 && k <=10) {
      hip = ((10 - k + 1) * STEP);
    } 
    else if (k >= 12 && k <=16) {
      hip = ((k-11) * -STEP);
    } 
    else if (k >= 17 && k <=21)  {
      hip = ((21 - k + 1) * -STEP);
    } 
    else {
      hip = 0;
    }
    hip *= dir;
    hip +=  90;
  }
};

struct leg legs[NUMLEGS];

void setup() 
{ 
  legs[0].ship.attach(23);
  legs[0].sknee.attach(24);
  legs[0].dir = 1;
  legs[1].ship.attach(25);
  legs[1].sknee.attach(26);
  legs[1].dir = 1;
  legs[2].ship.attach(27);
  legs[2].sknee.attach(28);
  legs[2].dir = 1;
  legs[3].ship.attach(46);
  legs[3].sknee.attach(47);
  legs[3].dir = -1;
  legs[4].ship.attach(48);
  legs[4].sknee.attach(49);
  legs[4].dir = -1;
  legs[5].ship.attach(50);
  legs[5].sknee.attach(51);
  legs[5].dir = -1;
  for ( int i = 0; i < NUMLEGS; ++i ) {
    legs[i].move();
  }

  Serial.begin(57600);
} 


int key_frame_l = 0;
int key_frame_r = 13;

void forward_walk ();
void bill_cosby ();
void debug_three ();

void loop () {
  //  debug_three();
  forward_walk ();  
  //  bill_cosby ();
  delay (45);
}

void update_frame (int &k_frame) {
  k_frame = (k_frame < 21) ? k_frame + 1 : 0;
}


void debug_three () {
  update_frame (key_frame_l);
  int i = 2;
  legs[i].set_key (key_frame_l);
  legs[i].move();
}

void forward_walk () {
  update_frame (key_frame_l);
  update_frame (key_frame_r);
  //key_frame = (key_frame < 21) ? key_frame + 1 : 0;
  for (int i = 0; i <= 4; i+=2) {
    legs[i].set_key (key_frame_l);
    legs[i+1].set_key (key_frame_r);
  }
  for (int i = 0; i < NUMLEGS; i++)
    legs[i].move();
  //  Serial.println (key_frame);
}

void bill_cosby() {
  update_frame (key_frame_l);
  for (int i = 0; i < NUMLEGS; i++)
    legs[i].set_key (key_frame_l);
  for (int i = 0; i < NUMLEGS; i++)
    legs[i].move();
  Serial.println (key_frame_l);
}





