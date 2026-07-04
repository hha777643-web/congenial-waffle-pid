/**
 * @file    chassis_config.h
 * @brief   底盘机械参数配置文件
 *          根据全向轮底盘修改此文件
 */

#ifndef __CHASSIS_CONFIG_H
#define __CHASSIS_CONFIG_H

/* ---------- 机械尺寸 ---------- */
#define WHEEL_RADIUS 0.05f   // 轮子半径(米)
#define CHASSIS_RADIUS 0.15f // 底盘中心到轮子水平距离(米)

/* ---------- MG520电机+编码器参数 ---------- */
#define ENCODER_LINE 13  // 编码器线数(电机转一圈产生13个AB脉冲)
#define GEAR_RATIO 30.0f // MG520减速比

// 轮子转一圈的总编码器计数值(四倍频后)
#define PULSE_PER_REV (ENCODER_LINE * GEAR_RATIO * 4)

/* ---------- 控制周期(秒) ---------- */
#define CONTROL_PERIOD 0.01f // 10ms = 100Hz控制频率

/* ---------- 轮子编号定义(从俯视图看) ---------- */
#define WHEEL_RF 0 // 右前轮 (Right-Front)
#define WHEEL_LF 1 // 左前轮 (Left-Front)
#define WHEEL_LR 2 // 左后轮 (Left-Rear)
#define WHEEL_RR 3 // 右后轮 (Right-Rear)

#endif