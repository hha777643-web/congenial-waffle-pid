/**
 * @file    pid_controller.h
 * @brief   PID控制器模块
 */

#ifndef __PID_CONTROLLER_H
#define __PID_CONTROLLER_H

#include <stdint.h>
#include "pid.h"

/* ---------- 函数声明 ---------- */
void PID_Controller_Init(void);
float PID_Controller_Calc(uint8_t wheel_id, float target, float measure);
void PID_Controller_Reset(uint8_t wheel_id);

#endif