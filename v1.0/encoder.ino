#include "line.h"
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
