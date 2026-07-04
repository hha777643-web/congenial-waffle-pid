#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include "bsp_pwm.h"

/* 最大占空比 */
#define PWM_MAX_DUTY 999

/* 电机ID枚举 */
typedef enum {
    MOTOR_RF = 0,
    MOTOR_LF = 1,
    MOTOR_LR = 2,
    MOTOR_RR = 3
} MotorId;

/* 接口声明 */
void motorInit(void);
void motorSetPwm(MotorId motor_id, int16_t duty);
void motorStopAll(void);
void motorEnable(void);
void motorDisable(void);

#endif /* MOTOR_DRIVER_H */