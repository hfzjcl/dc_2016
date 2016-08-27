// #include "PID.h"//声明函数
int motor_work(struct motor moto, int pwm);
//中断程序
void doencoder_l() {
  if (digitalRead(en_l_pin_a) == digitalRead(en_l_pin_b))
    en_l_pos_a++;
  else
    en_l_pos_a--;
}
void doencoder_r() {
  if (digitalRead(en_r_pin_a) == digitalRead(en_r_pin_b))
    en_r_pos_a++;
  else
    en_r_pos_a--;
}

void setup() {
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
  Serial.print(en_l_pos_a);
  Serial.print(",");
  Serial.println(en_r_pos_a);
  pwm = Position_PID(en_l_pos_a, Target);
  motor_work(motor_l,pwm);
  delay(10);




}

