/**
 * @file    bsp_pwm.c
 * @brief   底层硬件支持包实现
 */

#include "bsp_pwm.h"
#include "tim.h"
#include "gpio.h"

// 内部静态映射，隔离具体硬件外设
static GPIO_TypeDef *getPortGroup(BspGpioPort port)
{
    switch (port)
    {
    case BSP_PORT_A:
        return GPIOA;
    case BSP_PORT_B:
        return GPIOB;
    case BSP_PORT_C:
        return GPIOC;
    case BSP_PORT_D:
        return GPIOD;
    case BSP_PORT_E:
        return GPIOE;
    case BSP_PORT_F:
        return GPIOF;
    case BSP_PORT_G:
        return GPIOG;
    case BSP_PORT_H:
        return GPIOH;
    case BSP_PORT_I:
        return GPIOI;
    default:
        return NULL;
    }
}

void bspPwmInit(void)
{
    /* 启动四路PWM */
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}

void bspPwmSetCompare(BspPwmChannel channel, uint16_t compare_val)
{
    switch (channel)
    {
    case BSP_PWM_CH1:
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compare_val);
        break;
    case BSP_PWM_CH2:
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, compare_val);
        break;
    case BSP_PWM_CH3:
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, compare_val);
        break;
    case BSP_PWM_CH4:
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, compare_val);
        break;
    default:
        break;
    }
}

void bspGpioWritePin(BspGpioPort port, uint16_t pin, BspGpioState state)
{
    GPIO_TypeDef *gpio_group = getPortGroup(port);

    if (gpio_group == NULL)
    {
        return;
    }

    GPIO_PinState hal_state = (state == BSP_GPIO_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(gpio_group, pin, hal_state);
}