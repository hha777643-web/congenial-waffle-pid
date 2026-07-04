/**
 * @file    pid_controller.c
 * @brief   PID控制器模块实现
 *          调用外部pid库的 PID_Calc 完成四个轮子的转速闭环
 */

#include "pid_controller.h"
#include "chassis_config.h"

/* ---------- 四个轮子各自的PID控制器实例 ---------- */
static pid_t pid_wheel[4];

// 初始化四个轮子的PID控制器（max_out=999 → 输出限幅，匹配PWM最大占空比
void PID_Controller_Init(void)
{
    for (int i = 0; i < 4; i++)
    {
        PID_Init(&pid_wheel[i],
                 1.0f,    // kp
                 0.0f,    // ki
                 0.0f,    // kd
                 500.0f,  // max_integral
                 999.0f); // max_out
    }
}

// 对指定轮子进行PID计算（正值 = 正转PWM，负值 = 反转PWM
float PID_Controller_Calc(uint8_t wheel_id, float target, float measure)
{
    if (wheel_id >= 4)
        return 0.0f;
    // 调用pid
    return PID_Calc(&pid_wheel[wheel_id], target, measure, CONTROL_PERIOD);
}

//重置指定轮子的PID积分累加值 切换运动模式或急停后调用，避免积分残留
void PID_Controller_Reset(uint8_t wheel_id) {
    if (wheel_id < 4) {
        pid_wheel[wheel_id].integral = 0.0f;
        pid_wheel[wheel_id].output   = 0.0f;
    }
}