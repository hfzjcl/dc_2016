#include <PID_v1.h>
#define kp_pos_l 1
#define ki_pos_l 1
#define kd_pos_l 1
#define kp_pos_r 1
#define ki_pos_r 1
#define kd_pos_r 1

double Kp_pos_l = kp_pos_l, Ki_pos_l = ki_pos_l, Kd_pos_l = kd_pos_l, Kp_pos_r = kp_pos_r, Ki_pos_r = ki_pos_r, Kd_pos_r = kd_pos_r;
double Input_pos_l, Output_pos_l, Input_pos_r, Output_pos_r;
//initialize the variables we're linked to
double Pos_Setpoint = 0;

PID PID_pos_l(&Input_pos_l, &Output_pos_l, &Pos_Setpoint, Kp_pos_l, Ki_pos_l, Kd_pos_l, DIRECT);
PID PID_pos_r(&Input_pos_r, &Output_pos_r, &Pos_Setpoint, Kp_pos_r, Ki_pos_r, Kd_pos_r, DIRECT);

