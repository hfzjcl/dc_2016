

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

