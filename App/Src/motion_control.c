/**
 * @file    motion_control.c
 * @brief   全向轮运动学解算实现
 *          【正方向定义】
 *            Vx   : 底盘前进方向(正前方)
 *            Vy   : 底盘正左方向(与前进方向垂直向左)
 *            Omega: 逆时针旋转为正
 */

#include "motion_control.h"
#include "chassis_config.h"

/**
 * @brief  将底盘三轴速度解算为四个轮子目标转速
 * @param  Vx    期望前向速度(m/s)
 * @param  Vy    期望横向速度(m/s)
 * @param  Omega 期望旋转角速度(rad/s)
 * @return WheelTarget_t 包含四个轮子目标转速(rps)
 */
WheelTarget_t Motion_Calculate(float Vx, float Vy, float Omega)
{
    WheelTarget_t target;

    /* 逆运动学矩阵计算 */
    target.rps[WHEEL_RF] = (sqrt(2) * (-Vy + Vx) + Omega * CHASSIS_RADIUS) / WHEEL_RADIUS * GEAR_RATIO;
    target.rps[WHEEL_LF] = (sqrt(2) * (-Vy - Vx) + Omega * CHASSIS_RADIUS) / WHEEL_RADIUS * GEAR_RATIO;
    target.rps[WHEEL_LR] = (sqrt(2) * (Vy - Vx) + Omega * CHASSIS_RADIUS) / WHEEL_RADIUS * GEAR_RATIO;
    target.rps[WHEEL_RR] = (sqrt(2) * (Vy + Vx) + Omega * CHASSIS_RADIUS) / WHEEL_RADIUS * GEAR_RATIO;

    return target;
}

/**
 * @brief  结构体版本的运动学解算(便于外部调用)
 * @param  vel 底盘速度结构体指针
 * @return WheelTarget_t
 */
WheelTarget_t Motion_Calculate_Struct(ChassisVelocity_t *vel)
{
    return Motion_Calculate(vel->Vx, vel->Vy, vel->Omega);
}