/**
 * @file    chassis_control.c
 * @brief   底盘控制调度模块实现
 *          整合底层模块，形成完整的闭环控制循环
 */

#include "chassis_control.h"
#include "chassis_config.h"
#include "bsp_encoder.h"
#include "motion_control.h"
#include "pid_controller.h"
#include "motor_driver.h"
#include <stddef.h>

/* 期望底盘速度 */
static volatile float chassis_Vx = 0.0f;
static volatile float chassis_Vy = 0.0f;
static volatile float chassis_Omega = 0.0f;

/* 底盘状态 */
static volatile ChassisState_t chassis_state = CHASSIS_STOP;

// 底盘总初始化
void Chassis_Init(void)
{
    /* 启动编码器硬件接口 */
    Encoder_Init();

    /* 启动电机驱动（PWM + STBY使能） */
    motorInit();

    /* 初始化PID控制器 */
    PID_Controller_Init();

    /* 初始速度归零 */
    chassis_Vx = 0.0f;
    chassis_Vy = 0.0f;
    chassis_Omega = 0.0f;
    chassis_state = CHASSIS_STOP;
}

// 底盘总控制循环（读取编码器 → 运动学解算 → PID计算 → 输出PWM
void Chassis_Control_Loop(void)
{
    /* 更新编码器，获取各轮实际转速 */
    Encoder_Update_Speed();

    if (chassis_state == CHASSIS_RUNNING)
    {
        /* 运动学解算，期望速度 → 四个轮子目标转速 */
        WheelTarget_t target = Motion_Calculate(chassis_Vx, chassis_Vy, chassis_Omega);

        /* PID闭环计算 */
        for (int i = 0; i < 4; i++)
        {
            float actual_speed = Encoder_Get_Speed_RPS(i);
            float pid_output = PID_Controller_Calc(i, target.rps[i], actual_speed);
            motorSetPwm(i, (int16_t)pid_output);
        }
    }
    else
    {
        /* 停止状态：直接输出0 */
        motorStopAll();
    }
}

// 设定期望底盘速度
void Chassis_Set_Velocity(float Vx, float Vy, float Omega)
{
    // chassis_Vx    = ?????????????;
    // chassis_Vy    = ??????;
    // chassis_Omega = ???????;

    /* 如果有非零速度，自动进入运行状态 */
    if (Vx != 0.0f || Vy != 0.0f || Omega != 0.0f)
    {
        chassis_state = CHASSIS_RUNNING;
    }
    else
    {
        chassis_state = CHASSIS_STOP;
    }
}

/**
 * @brief  正常停止（减速到零）
 */
void Chassis_Stop(void) {
    chassis_Vx    = 0.0f;
    chassis_Vy    = 0.0f;
    chassis_Omega = 0.0f;
    /* 不立即停机，让PID自然减速到零 */
}

/**
 * @brief  紧急停止（立即停止所有电机）
 */
void Chassis_Emergency_Stop(void) {
    chassis_state = CHASSIS_STOP;
    chassis_Vx    = 0.0f;
    chassis_Vy    = 0.0f;
    chassis_Omega = 0.0f;

    /* 立即停止所有电机 */
    motorStopAll();

    /* 重置PID积分，防止下次启动冲击 */
    for (int i = 0; i < 4; i++) {
        PID_Controller_Reset(i);
    }
}

// 获取底盘当前状态
ChassisState_t Chassis_Get_State(void)
{
    return chassis_state;
}