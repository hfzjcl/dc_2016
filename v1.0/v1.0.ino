//直立小车控制部分
//2016.8.13
#define encoder_l_a 13 //left wheel编码器A,B相
#define encoder_l_b 14 //A相绿线B相白线

#define encoder_r_a 15 //right wheel encoder channel A,B
#define encoder_r_b 16

/*
 测速部分
*/
#define sampling_time //定义采样时间

long int encoder_l_pos,encoder_r_pos;
float speed_l,speed_r;

