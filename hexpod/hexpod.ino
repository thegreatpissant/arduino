#include <Servo.h>

#define NSERVOS 12
#define NKNEES 6

int spins[NSERVOS] = { 
  // Knee, Hip
  25, 26, // 1
  27, 28, // 2
  49, 48, // 3
  51, 50, // 4
  53, 52, // 5
  24, 23  // 6
};

Servo sv [NSERVOS];
int knees [NKNEES] = {0, 2, 4, 6, 8, 10};
int angle;
void setup () {
  Serial.begin (115200);
  Serial.println ("-== Attaching Servos ==-");
  for ( int i = 0; i < NSERVOS; i++ ) {
    Serial.print ("#");
    Serial.println (spins[i]);
    sv[i].attach (spins[i]);
  }
  angle = sv[0].read();
  Serial.println ("-== Attached ==-");
}

void wave (const int pin);

void jump ();
void idle ();
void loop () {
  //  jump();
}

void idle () {
}
void jump () {
  for ( int i = 0; i < NKNEES; i++ ){
    sv[knees[i]].write (150);
    delay (45);
  }
  delay (350);
  for ( int i = 0; i < NKNEES; i++) {
    sv[knees[i]].write (90);
    delay (45);
  }
  delay (150);
}


void wave (const int pin) {
  const int STEP = 2;
  static int dir = 0;
  sv[pin].write (angle);
  if (dir == 0) {
    if ((angle -= STEP) <= 0)
      dir = 1;
  } else {
    if ((angle += STEP) >= 150)
      dir = 0;
  }
  delay (5);
}
