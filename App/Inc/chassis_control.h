/**
 * @file    chassis_control.h
 * @brief   底盘控制调度模块
 *          整合编码器读取→运动学解算→PID→电机输出
 *          并提供速度设定接口（供遥控器/上位机调用）
 */

#ifndef __CHASSIS_CONTROL_H
#define __CHASSIS_CONTROL_H

#include <stdint.h>

/* 底盘状态 */
typedef enum
{
    CHASSIS_STOP = 0, // 停止
    CHASSIS_RUNNING,  // 运行中
    CHASSIS_ERROR     // 错误状态
} ChassisState_t;

/* 函数声明 */
void Chassis_Init(void);         // 初始化所有底盘模块
void Chassis_Control_Loop(void); // 控制循环（在10ms中断中调用）

/* 速度设定接口（供外部模块调用） */
void Chassis_Set_Velocity(float Vx, float Vy, float Omega);
void Chassis_Stop(void);
void Chassis_Emergency_Stop(void);

/* 状态获取 */
ChassisState_t Chassis_Get_State(void);

#endif