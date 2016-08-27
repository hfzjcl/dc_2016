
#include "line.h"
#include <PID_v1.h>

//Define Variables we'll be connecting to
double Input_pos_l, Output_pos_l,Input_pos_r, Output_pos_r;
double Kp_pos_l = 10, Ki_pos_l = 0, Kd_pos_l = 10,Kp_pos_r = 10, Ki_pos_r = 0, Kd_pos_r = 10;
//initialize the variables we're linked to
double Setpoint = 0;

PID PID_pos_l(&Input_pos_l, &Output_pos_l, &Setpoint, Kp_pos_l, Ki_pos_l, Kd_pos_l, DIRECT);
PID PID_pos_r(&Input_pos_r, &Output_pos_r, &Setpoint, Kp_pos_r, Ki_pos_r, Kd_pos_r, DIRECT);



int motor_work(struct motor moto, int pwm);
//中断程序
void doencoder_l() {
  if (digitalRead(en_l_pin_a) == digitalRead(en_l_pin_b))
    en_l_pos_a--;
  else
    en_l_pos_a++;
}
void doencoder_r() {
  if (digitalRead(en_r_pin_a) == digitalRead(en_r_pin_b))
    en_r_pos_a++;
  else
    en_r_pos_a--;
}

void setup() {

  //PID control
  PID_pos_l.SetOutputLimits(-255, 255);
  PID_pos_r.SetOutputLimits(-255, 255);
  //turn the PID on
  PID_pos_r.SetMode(AUTOMATIC);
  PID_pos_r.SetMode(AUTOMATIC);

  PID_pos_l.SetSampleTime(20);
  PID_pos_l.SetSampleTime(20);
  //
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz). Comment this line if having compilation difficulties with TWBR.
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }


  motor motor_l = {'l', motor_l_in1, motor_l_in2, motor_l_pwm};
  motor motor_r = {'r', motor_r_in1, motor_r_in2, motor_r_pwm};
  Serial.begin(9600);
  pinMode(motor_l.in1, OUTPUT);
  pinMode(motor_l.in2, OUTPUT);
  pinMode(motor_r.in1, OUTPUT);
  pinMode(motor_r.in2, OUTPUT);
  pinMode(en_l_pin_a, INPUT);
  pinMode(en_r_pin_a, INPUT);
  pinMode(en_l_pin_b, INPUT);
  pinMode(en_r_pin_b, INPUT);
  attachInterrupt(digitalPinToInterrupt(en_l_pin_a), doencoder_l , RISING);
  attachInterrupt(digitalPinToInterrupt(en_r_pin_a), doencoder_r , RISING);
}
int Target = 195 + 780;
int i = 0;
int pwm;
void loop() {

  while (!mpuInterrupt && fifoCount < packetSize) {
    // other program behavior stuff here
    // .
    // .
    // .
    // if you are really paranoid you can frequently test in between other
    // stuff to see if mpuInterrupt is true, and if so, "break;" from the
    // while() loop to immediately process the MPU data
    // .
    // .
    // .
  }

  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    //Serial.print("ypr\t");
    //Serial.print(ypr[0] * 180 / M_PI);
    //Serial.print("\t");
    //Serial.print(ypr[1] * 180 / M_PI);
    //Serial.print("\t");
    //Serial.println(ypr[2] * 180 / M_PI);

  }
  Serial.print(en_l_pos_a);
  Serial.print(",");
  Serial.println(en_r_pos_a);

  //
  Input_pos_l = ypr[0] * 180 / M_PI;
  Input_pos_r = ypr[0] * 180 / M_PI;
  PID_pos_l.Compute();
  PID_pos_r.Compute();
  //
  //pwm = Position_PID(en_l_pos_a, Target);
  motor_work(motor_l, Output_pos_l);
  motor_work(motor_r, Output_pos_r);

}

