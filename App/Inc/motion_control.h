/**
 * @file    motion_control.h
 * @brief   全向轮运动学解算模块
 *          将底盘期望速度(Vx, Vy, Omega)解算为四个轮子目标转速
 */

#ifndef __MOTION_CONTROL_H
#define __MOTION_CONTROL_H

#include "chassis_config.h"
#include <stdint.h>
#include "math.h"

/* 底盘速度结构体 */
typedef struct
{
    float Vx;    // 前向速度(m/s)，前进为正
    float Vy;    // 横向速度(m/s)，向左为正
    float Omega; // 旋转角速度(rad/s)，逆时针为正
} ChassisVelocity_t;

/* 轮子目标转速结构体 */
typedef struct
{
    float rps[4]; // 四个轮子目标转速(转/秒)
} WheelTarget_t;

/* 函数声明 */
WheelTarget_t Motion_Calculate(float Vx, float Vy, float Omega);
WheelTarget_t Motion_Calculate_Struct(ChassisVelocity_t *vel);

#endif