/**
 * @file    encoder.h
 * @brief   编码器模块 - 读取电机转速和方向
 */

#ifndef __ENCODER_H
#define __ENCODER_H

#include "chassis_config.h"
#include "tim.h"
#include <stdint.h>

/* 编码器数据结构 */
typedef struct
{
    int16_t last_cnt;  // 上一次TIMx->CNT值
    float speed_rps;   // 当前转速(转/秒)
    uint8_t direction; // 转动方向: 0=正转, 1=反转
} WheelEncoder_t;

/* 全局变量 */
extern volatile WheelEncoder_t wheels[4];

/* 函数 */
void Encoder_Init(void);                         // 初始化编码器(启动硬件编码器接口；初始化四个结构体)
void Encoder_Update_Speed(void);                 // 更新所有轮子的转速和方向
float Encoder_Get_Speed_RPS(uint8_t wheel_id);   // 获取指定轮子转速(rps)
uint8_t Encoder_Get_Direction(uint8_t wheel_id); // 获取指定轮子方向

#endif