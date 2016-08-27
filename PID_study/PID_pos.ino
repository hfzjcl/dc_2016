#include "PID.h"
float Position_KP = Pos_KP, Position_KI = Pos_KI, Position_KD = Pos_KD;
int Position_PID (int Encoder, int Target)
{
  static float Bias, Pwm, Integral_bias, Last_Bias;
  Bias = Encoder - Target; //计算偏差
  Integral_bias += Bias; //求出偏差的积分
  Pwm = Position_KP * Bias + Position_KI * Integral_bias + Position_KD * (Bias - Last_Bias);
  Last_Bias = Bias; //保存上一次偏差
  return Pwm; //输出
}
