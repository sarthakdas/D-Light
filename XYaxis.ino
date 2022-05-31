#include <Stepper.h>

#define joyX A0
#define joyY A1


const int stepsPerRevolution = 2048;
const int rolePerMinute = 17;

const int stepSize = 10;

Stepper m1(stepsPerRevolution, 22, 24, 23, 25);
Stepper m2(stepsPerRevolution, 27, 29, 26, 28);
Stepper m3(stepsPerRevolution, 30, 32, 31, 33);
Stepper m4(stepsPerRevolution, 34, 36, 35, 37);



int xMap, yMap, xValue, yValue;


int cpos[2] = {0, 0};
int npos[2] = {0, 0};

int n_points = 2;
int mpos[2][2] = {{0, 100}, {0, 0}};

void setup() {
  Serial.begin(9600);

  m1.setSpeed(rolePerMinute);
  m2.setSpeed(rolePerMinute);
  m3.setSpeed(rolePerMinute);
  m4.setSpeed(rolePerMinute);

}

void loop() {

  delay(10);
  m8.step(100);

//  // put your main code here, to run repeatedly:
//  xValue = analogRead(joyX);
//  yValue = analogRead(joyY);
//  xMap = map(xValue, 0, 1023, 20, -20);
//  yMap = map(yValue, 0, 1023, 20, -20);
//  Serial.println(String(xMap) + "  " + String(yMap) );
//
//  if (xMap == 2 and yMap == 2) {
//    tighten();
//  } else {
//    npos[0] = cpos[0] + xMap;
//    npos[1] = cpos[1] + yMap;
//
//    Serial.println("===== Moving to   " + String(cpos[0]) + cpos[1]);
//    pos(npos);
//  }
//



  //  for (int i = 0; i < n_points; i++) {
  //    Serial.println("===== Moving to   " + String(mpos[i][0]) + mpos[i][1]);
  //    pos(mpos[i]);
  //    Serial.println("===== Moved to   " + String(mpos[i][0]) + mpos[i][1]);
  //    delay(1000);
  //      m3.step(stepSize);
  //      m4.step(stepSize);
}

void x_move(bool dir, int steps = 1) {
  Serial.print("Moving x ");
  if (dir == 1) {
    Serial.println("--RIGHT ");
    m1.step(-stepSize);
    m2.step(stepSize);
    m3.step(stepSize);
    m4.step(-stepSize);
  } else {
    Serial.println("--LEFT ");
    m1.step(stepSize);
    m2.step(-stepSize);
    m3.step(-stepSize);
    m4.step(stepSize);
  }
}

void y_move(bool dir, int steps = 1) {
  Serial.print("Moving y ");
  if (dir == 1) {
    Serial.println("--DOWN");
    m1.step(-stepSize);
    m2.step(-stepSize);
    m3.step(stepSize);
    m4.step(stepSize);
  } else {
    Serial.println("--UPWARDS");
    m1.step(stepSize);
    m2.step(stepSize);
    m3.step(-stepSize);
    m4.step(-stepSize);
  }
}

void pos(int npos[]) {
  int x_diff = cpos[0] - npos[0];
  int x_sign  = ispos(x_diff);
  int y_diff = cpos[1] - npos[1];
  int y_sign  = ispos(y_diff);

  x_diff = abs(x_diff);
  y_diff = abs(y_diff);

  for (int i = x_diff; i > 0; i--) {
    x_move(x_sign, x_diff);
  }

  for (int i = y_diff; i > 0; i--) {
    y_move(y_sign);
  }

  for (int i = 5; i > 0; i--) {
    tighten();
  }

  cpos[0] = npos[0];
  cpos[1] = npos[1];


  Serial.println("===Move Done====");

  update_pos(npos);
}

int ispos(int number) {
  if (number > 0) {
    return 0; // Negetive Movement
  } else {
    return 1; // Positive Movement
  }
}

void update_pos(int npos[]) {
  for (int i = 0; i < 2; i++) {
    cpos[i] = npos[i];
  }
}

void tighten() {
  m1.step(stepSize);
  m2.step(stepSize);
  m3.step(stepSize);
  m4.step(stepSize);
}
