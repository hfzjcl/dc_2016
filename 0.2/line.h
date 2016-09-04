/*
 * motor接线
 */
#define motor_l_in1 7
#define motor_l_in2 6
#define motor_l_pwm 11
#define motor_r_in1 8
#define motor_r_in2 9
#define motor_r_pwm 10
/*
 * encoder接线
 */
#define encoder_l_a 0
#define encoder_l_b 4
#define encoder_r_a 1
#define encoder_r_b 5
/*

*/
#define Pos_KP 0
#define Pos_KI 0
#define Pos_KD 0
/*

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

*/

long int en_l_pos_a = 0;
int en_l_pin_a = encoder_l_a;
int en_l_pin_b = encoder_l_b;
long int en_r_pos_a = 0;
int en_r_pin_a = encoder_r_a;
int en_r_pin_b = encoder_r_b;

