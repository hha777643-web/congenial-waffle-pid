#include "pid.h"

void PID_Init(volatile pid_t *pid, float kp, float ki, float kd, float max_integral, float max_out)
{

    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->max_integral = max_integral;
    pid->max_out = max_out;

    pid->target = 0.0f;
    pid->measure = 0.0f;
    pid->last_measure = 0.0f;
    pid->err = 0.0f;
    // pid->last_err = 0.0f;
    pid->integral = 0.0f;
    pid->output = 0.0f;
}

float PID_Calc(volatile pid_t *pid, float target, float measure, float dt)
{

    pid->target = target;
    pid->measure = measure;

    // Cal current error
    pid->err = pid->target - pid->measure;

    // Cal accumulation of error
    pid->integral += pid->err * dt;

    // Integral clamping
    if (pid->integral > pid->max_integral)
    {
        pid->integral = pid->max_integral;
    }
    else if (pid->integral < -pid->max_integral)
    {
        pid->integral = -pid->max_integral;
    }

    // Cal Derivative
    // float der = (pid->err - pid->last_err) /dt;
    // pid->last_err = pid->err;

    float der = (pid->measure - pid->last_measure) / dt;
    pid->last_measure = pid->measure;

    // output
    pid->output = pid->kp * pid->err +
                  pid->ki * pid->integral +
                  pid->kd * der;

    // Output clamping
    if (pid->output > pid->max_out)
    {
        pid->output = pid->max_out;
    }
    else if (pid->output < -pid->max_out)
    {
        pid->output = -pid->max_out;
    }

    return pid->output;
}
