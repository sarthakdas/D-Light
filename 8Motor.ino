#include <Stepper.h>
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

int red = 2;
int green = 2;
int blue = 2;

unsigned int rgbColour[3];


#define joyX A0
#define joyY A1
#define joyZ A2
const int button = 2; //Tilt sensor

int xMap, yMap, zMap, xValue, yValue, zValue;

bool volatile m_tighten = false;
const int stepsPerRevolution = 2048;
const int rolePerMinute = 15;

const int stepSize = 10;

Stepper m1(stepsPerRevolution, 23, 25, 22, 24);
Stepper m2(stepsPerRevolution, 26, 28, 27, 29);
Stepper m3(stepsPerRevolution, 31, 33, 30, 32);
Stepper m4(stepsPerRevolution, 35, 37, 34, 36);

Stepper m5(stepsPerRevolution, 39, 41, 38, 40);
Stepper m6(stepsPerRevolution, 43, 45, 42, 44);
Stepper m7(stepsPerRevolution, 48, 49, 46, 47);
Stepper m8(stepsPerRevolution, 50, 52, 51, 53);

int cpos[3] = {0, 0, 0};
int npos[3] = {0, 0, 0};


int mpos[2][3] = {{0, 0, 50}, {0, 0, 0}};



void setup() {
  Serial.begin(9600);

  m1.setSpeed(rolePerMinute);
  m2.setSpeed(rolePerMinute);
  m3.setSpeed(rolePerMinute);
  m4.setSpeed(rolePerMinute);
  m5.setSpeed(rolePerMinute);
  m6.setSpeed(rolePerMinute);
  m7.setSpeed(rolePerMinute);
  m8.setSpeed(rolePerMinute);

  setColourRgb(0, 0, 0);



  // Start off with red.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 255;
}

void loop() {

  setColourRgb(rgbColour[0]-1, rgbColour[1]+1, rgbColour[2]);
  delay(10);


  //  m8.step(100);
  //  tighten();

  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  zValue = analogRead(joyZ);
  xMap = map(xValue, 0, 1023, 20, -20);
  yMap = map(yValue, 0, 1023, -20, 20);
  zMap = map(zValue, 0, 1023, 20, -20);
  Serial.println(String(xMap) + "  " + String(yMap) );

  npos[0] = cpos[0] + xMap;
  npos[1] = cpos[1] + yMap;
  npos[2] = cpos[2] + zMap;

  Serial.println("===== Moving to   " + String(cpos[0]) + cpos[1]);
  pos(npos);

  //  for (int i = 0; i < 2; i++) {
  //    Serial.println("===== Moving to   " + String(mpos[i][0]) + mpos[i][1]);
  //    pos(mpos[i]);
  //    Serial.println("===== Moved to   " + String(mpos[i][0]) + mpos[i][1]);
  //    delay(1000);
  //  }
}

int ispos(int number) {
  if (number > 0) {
    return 0; // Go down
  } else {
    return 1; //Go up
  }
}

void z_move(bool dir, int steps = 1) {
  Serial.print("Moving z ");
  if (dir == 1) {
    Serial.println("--UP ");
    m1.step(stepSize);
    m2.step(stepSize);
    m3.step(stepSize);
    m4.step(stepSize);

    m5.step(-stepSize);
    m6.step(-stepSize);
    m7.step(-stepSize);
    m8.step(-stepSize);
  } else {
    Serial.println("--DOWN ");
    m1.step(-stepSize);
    m2.step(-stepSize);
    m3.step(-stepSize);
    m4.step(-stepSize);

    m5.step(stepSize);
    m6.step(stepSize);
    m7.step(stepSize);
    m8.step(stepSize);
  }
}

void x_move(bool dir, int steps = 1) {
  Serial.print("Moving x ");
  if (dir == 1) {
    Serial.println("--RIGHT ");
    m1.step(-stepSize);
    m2.step(-stepSize);
    m3.step(stepSize);
    m4.step(stepSize);

    m5.step(-stepSize);
    m6.step(-stepSize);
    m7.step(stepSize);
    m8.step(stepSize);
  } else {
    Serial.println("--LEFT ");
    m1.step(stepSize);
    m2.step(stepSize);
    m3.step(-stepSize);
    m4.step(-stepSize);

    m5.step(stepSize);
    m6.step(stepSize);
    m7.step(-stepSize);
    m8.step(-stepSize);
  }
}

void y_move(bool dir, int steps = 1) {
  Serial.print("Moving y ");
  if (dir == 1) {
    Serial.println("--BACKWARDS");
    m1.step(-stepSize);
    m2.step(stepSize);
    m3.step(stepSize);
    m4.step(-stepSize);

    m5.step(-stepSize);
    m6.step(stepSize);
    m7.step(stepSize);
    m8.step(-stepSize);

  } else {
    Serial.println("--FORWARDS");
    m1.step(stepSize);
    m2.step(-stepSize);
    m3.step(-stepSize);
    m4.step(stepSize);

    m5.step(stepSize);
    m6.step(-stepSize);
    m7.step(-stepSize);
    m8.step(stepSize);
  }
}

void pos(int npos[]) {
  int x_diff = cpos[0] - npos[0];
  int x_sign  = ispos(x_diff);
  int y_diff = cpos[1] - npos[1];
  int y_sign  = ispos(y_diff);
  int z_diff = cpos[2] - npos[2];
  int z_sign  = ispos(z_diff);

  Serial.println(z_sign);
  Serial.println(z_diff);

  x_diff = abs(x_diff);
  y_diff = abs(y_diff);
  z_diff = abs(z_diff);

  for (int i = x_diff; i > 0; i--) {
    x_move(x_sign);
  }

  for (int i = y_diff; i > 0; i--) {
    y_move(y_sign);
  }

  for (int i = z_diff; i > 0; i--) {
    z_move(z_sign);
  }

  tighten();

  cpos[0] = npos[0];
  cpos[1] = npos[1];
  cpos[2] = npos[2];

  Serial.println("===Move Done====");

  update_pos(npos);
}

void tighten() {
  for (int i = 5; i > 0; i--) {
    m1.step(stepSize);
    m2.step(stepSize);
    m3.step(stepSize);
    m4.step(stepSize);

    m5.step(stepSize);
    m6.step(stepSize);
    m7.step(stepSize);
    m8.step(stepSize);

  }
}

void update_pos(int npos[]) {
  for (int i = 0; i < 3; i++) {
    cpos[i] = npos[i];
  }
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
