#include "motor_driver.h"
#include "bsp_pwm.h"

/* 硬件引脚映射 (采用全大写下划线) */
/* 基于 STM32 HAL GPIO_PIN_x 对应的十六进制值映射 */
#define M1_AIN1_PORT BSP_PORT_B
#define M1_AIN1_PIN 0x0001U /* PB0 */
#define M1_AIN2_PORT BSP_PORT_B
#define M1_AIN2_PIN 0x0002U /* PB1 */
#define M1_PWM_CH BSP_PWM_CH1

#define M2_AIN1_PORT BSP_PORT_B
#define M2_AIN1_PIN 0x0008U /* PB3 */
#define M2_AIN2_PORT BSP_PORT_B
#define M2_AIN2_PIN 0x0010U /* PB4 */
#define M2_PWM_CH BSP_PWM_CH2

#define M3_AIN1_PORT BSP_PORT_B
#define M3_AIN1_PIN 0x0020U /* PB5 */
#define M3_AIN2_PORT BSP_PORT_B
#define M3_AIN2_PIN 0x0100U /* PB8 */
#define M3_PWM_CH BSP_PWM_CH3

#define M4_AIN1_PORT BSP_PORT_B
#define M4_AIN1_PIN 0x0200U /* PB9 */
#define M4_AIN2_PORT BSP_PORT_B
#define M4_AIN2_PIN 0x0400U /* PB10 */
#define M4_PWM_CH BSP_PWM_CH4

#define STBY_PORT BSP_PORT_B
#define STBY_PIN 0x0004U /* PB2 */

void motorInit(void)
{
    bspPwmInit();
    motorEnable();
    motorStopAll();
}

void motorSetPwm(MotorId motor_id, int16_t duty)
{
    if (duty > PWM_MAX_DUTY)
    {
        duty = PWM_MAX_DUTY;
    }
    if (duty < -PWM_MAX_DUTY)
    {
        duty = -PWM_MAX_DUTY;
    }

    uint16_t abs_duty = (uint16_t)(duty < 0 ? -duty : duty);

    switch (motor_id)
    {
    case MOTOR_RF:
        if (duty > 0)
        {
            bspGpioWritePin(M1_AIN1_PORT, M1_AIN1_PIN, BSP_GPIO_HIGH);
            bspGpioWritePin(M1_AIN2_PORT, M1_AIN2_PIN, BSP_GPIO_LOW);
        }
        else if (duty < 0)
        {
            bspGpioWritePin(M1_AIN1_PORT, M1_AIN1_PIN, BSP_GPIO_LOW);
            bspGpioWritePin(M1_AIN2_PORT, M1_AIN2_PIN, BSP_GPIO_HIGH);
        }
        else
        {
            bspGpioWritePin(M1_AIN1_PORT, M1_AIN1_PIN, BSP_GPIO_LOW);
            bspGpioWritePin(M1_AIN2_PORT, M1_AIN2_PIN, BSP_GPIO_LOW);
        }
        bspPwmSetCompare(M1_PWM_CH, abs_duty);
        break;

    case MOTOR_LF:
        if (duty > 0)
        {
            bspGpioWritePin(M2_AIN1_PORT, M2_AIN1_PIN, BSP_GPIO_HIGH);
            bspGpioWritePin(M2_AIN2_PORT, M2_AIN2_PIN, BSP_GPIO_LOW);
        }
        else if (duty < 0)
        {
            bspGpioWritePin(M2_AIN1_PORT, M2_AIN1_PIN, BSP_GPIO_LOW);
            bspGpioWritePin(M2_AIN2_PORT, M2_AIN2_PIN, BSP_GPIO_HIGH);
        }
        else
        {
            bspGpioWritePin(M2_AIN1_PORT, M2_AIN1_PIN, BSP_GPIO_LOW);
            bspGpioWritePin(M2_AIN2_PORT, M2_AIN2_PIN, BSP_GPIO_LOW);
        }
        bspPwmSetCompare(M2_PWM_CH, abs_duty);
        break;

    case MOTOR_LR:
        if (duty > 0)
        {
            bspGpioWritePin(M3_AIN1_PORT, M3_AIN1_PIN, BSP_GPIO_HIGH);
            bspGpioWritePin(M3_AIN2_PORT, M3_AIN2_PIN, BSP_GPIO_LOW);
        }
        else if (duty < 0)
        {
            bspGpioWritePin(M3_AIN1_PORT, M3_AIN1_PIN, BSP_GPIO_LOW);
            bspGpioWritePin(M3_AIN2_PORT, M3_AIN2_PIN, BSP_GPIO_HIGH);
        }
        else
        {
            bspGpioWritePin(M3_AIN1_PORT, M3_AIN1_PIN, BSP_GPIO_LOW);
            bspGpioWritePin(M3_AIN2_PORT, M3_AIN2_PIN, BSP_GPIO_LOW);
        }
        bspPwmSetCompare(M3_PWM_CH, abs_duty);
        break;

    case MOTOR_RR:
        if (duty > 0)
        {
            bspGpioWritePin(M4_AIN1_PORT, M4_AIN1_PIN, BSP_GPIO_HIGH);
            bspGpioWritePin(M4_AIN2_PORT, M4_AIN2_PIN, BSP_GPIO_LOW);
        }
        else if (duty < 0)
        {
            bspGpioWritePin(M4_AIN1_PORT, M4_AIN1_PIN, BSP_GPIO_LOW);
            bspGpioWritePin(M4_AIN2_PORT, M4_AIN2_PIN, BSP_GPIO_HIGH);
        }
        else
        {
            bspGpioWritePin(M4_AIN1_PORT, M4_AIN1_PIN, BSP_GPIO_LOW);
            bspGpioWritePin(M4_AIN2_PORT, M4_AIN2_PIN, BSP_GPIO_LOW);
        }
        bspPwmSetCompare(M4_PWM_CH, abs_duty);
        break;

    default:
        break;
    }
}

void motorStopAll(void)
{
    motorSetPwm(MOTOR_RF, 0);
    motorSetPwm(MOTOR_LF, 0);
    motorSetPwm(MOTOR_LR, 0);
    motorSetPwm(MOTOR_RR, 0);
}

void motorEnable(void)
{
    bspGpioWritePin(STBY_PORT, STBY_PIN, BSP_GPIO_HIGH);
}

void motorDisable(void)
{
    bspGpioWritePin(STBY_PORT, STBY_PIN, BSP_GPIO_LOW);
}