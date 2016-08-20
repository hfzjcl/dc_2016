/*
 * motor接线
 */
#define motor_l_in1 1
#define motor_l_in2 2
#define motor_l_pwm 3
#define motor_r_in1 4
#define motor_r_in2 5
#define motor_r_pwm 6
/*
 * encoder接线
 */
#define encoder_l_a 7
#define encoder_l_b 7
#define encoder_r_a 7
#define encoder_r_b 7
/*
 *
 */
struct motor {
  char Name;
  int in1;
  int in2;
  int pwm;
};

motor motor_l = {'l', motor_l_in1, motor_l_in2, motor_l_pwm};
motor motor_r = {'r', motor_r_in1, motor_r_in2, motor_r_pwm};

/*
 *
 */

int en_l_pos_a = 0;
int en_l_pin_a = encoder_l_a;
int en_l_pin_b = encoder_l_b;
int en_r_pos_a = 0;
int en_r_pin_a = encoder_r_a;
int en_r_pin_b = encoder_r_b;

