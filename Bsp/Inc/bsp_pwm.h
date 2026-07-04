/**
 * @file    bsp_pwm.h
 * @brief   底层硬件支持包：PWM输出与通用IO控制
 * @note    完全隔离 HAL 库，供 Components 层调用
 */

#ifndef BSP_PWM_H
#define BSP_PWM_H

#include <stdint.h>

/* 类型采用大驼峰 (PascalCase) */

/* 常量采用全大写下划线 (SCREAMING_SNAKE_CASE) */
typedef enum
{
    BSP_PORT_A = 0,
    BSP_PORT_B,
    BSP_PORT_C,
    BSP_PORT_D,
    BSP_PORT_E,
    BSP_PORT_F,
    BSP_PORT_G,
    BSP_PORT_H,
    BSP_PORT_I
} BspGpioPort;

typedef enum
{
    BSP_GPIO_LOW = 0,
    BSP_GPIO_HIGH = 1
} BspGpioState;

typedef enum
{
    BSP_PWM_CH1 = 1,
    BSP_PWM_CH2 = 2,
    BSP_PWM_CH3 = 3,
    BSP_PWM_CH4 = 4
} BspPwmChannel;

/* 函数采用小驼峰 (camelCase) */
void bspPwmInit(void);
void bspPwmSetCompare(BspPwmChannel channel, uint16_t compare_val);
void bspGpioWritePin(BspGpioPort port, uint16_t pin, BspGpioState state);

#endif /* BSP_PWM_H */