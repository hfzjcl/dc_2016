//霍尔码盘测速
//二倍频,A相中断,B相普通
void doencoder_l() { //左轮编码器
  if (digitalRead(encoder_l_a) == digitalRead(encoder_l_b))
    encoder_l_pos++;
  else encoder_l_pos--;
}

void doencoder_r() { //右轮编码器
  if (digitalRead(encoder_r_a) == digitalRead(encoder_r_b))
    encoder_r_pos++;
  else encoder_r_pos--;
}
void speedmeasure() {
  int newpos_l, newpos_r, oldpos_l, oldpos_r;
  oldpos_l = encoder_l_pos;
  oldpos_r = encoder_r_pos;
  delay(sampling_time);
  newpos_r = encoder_r_pos;
  newpos_l = encoder_l_pos;
  speed_l = ((newpos_l - oldpos_l) * 360 / 780) / sampling_time * 1000;
  speed_r = ((newpos_r - oldpos_r) * 360 / 780) / sampling_time * 1000;
  /*
   * 使用二倍频,编码器390线,所以乘二
   */
}

