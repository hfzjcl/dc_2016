void initialization(struct moto, struct moto, int, int, int, int);

int motor_work(struct motor moto, int pwm);
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
  initialization(motor_l, motor_r, en_l_pin_a, en_l_pin_b, en_r_pin_a, en_r_pin_b);
  attachInterrupt(digitalPinToInterrupt(en_l_pin_a), doencoder_l , CHANGE);
  attachInterrupt(digitalPinToInterrupt(en_r_pin_a), doencoder_r , CHANGE);
}
void loop() {
  char pos = 'l';
  motor_work(motor_l, 255);
}

