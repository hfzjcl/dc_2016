
void initialization(struct motor moto_l,struct motor moto_r, int en_l_pin_a, int en_r_pin_a, int en_l_pin_b, int en_r_pin_b) { //放setup里
  pinMode(moto_l.in1, OUTPUT);
  pinMode(moto_l.in2, OUTPUT);
  pinMode(moto_r.in1, OUTPUT);
  pinMode(moto_r.in2, OUTPUT);
  pinMode(en_l_pin_a, INPUT);
  pinMode(en_r_pin_a, INPUT);
  pinMode(en_l_pin_b, INPUT);
  pinMode(en_r_pin_b, INPUT);
}

int motor_work(struct motor moto, int pwm) { //运转函数
  if (moto.Name == 'l') {
    if (pwm >= 0) {
      digitalWrite(moto.in1, HIGH);
      digitalWrite(moto.in2, LOW);
      analogWrite(moto.pwm, pwm);
    }
    else {
      digitalWrite(moto.in1, LOW);
      digitalWrite(moto.in2, HIGH);
      analogWrite(moto.pwm, -pwm);
    }
  }
  else if (moto.Name == 'r') {
    if (pwm >= 0) {
      digitalWrite(moto.in1, HIGH);
      digitalWrite(moto.in2, LOW);
      analogWrite(moto.pwm, pwm);
    }
    else {
      digitalWrite(moto.in1, LOW);
      digitalWrite(moto.in2, HIGH);
      analogWrite(moto.pwm, -pwm);
    }
  }
  return pwm;
}

