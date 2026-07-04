#ifndef PID_H
#define PID_H

typedef struct{
    float kp;
    float ki;
    float kd;
    
    float target;
    float measure;
    float last_measure;
    

    float err;
    // float last_err;
    float integral;// integral accumulation

    float max_integral;
    float max_out;

    float output;
}pid_t;

void PID_Init(volatile pid_t * pid, float kp, float ki, float kd, float max_integral, float max_out);
float PID_Calc(volatile pid_t * pid, float target, float measure, float dt);

#endif
