/**
 * @file    encoder.c
 * @brief   编码器模块实现
 *          通过TIM2/3/4/8的Encoder模式读取AB相脉冲，计算转速和方向
 *          【转速读取原理】
 *            转速(rps) = 脉冲增量 / (轮转一圈脉冲数 × 采样周期)
 *          【方向判断原理】
 *            delta > 0 → 正转(0)  A相超前B相
 *            delta < 0 → 反转(1)  B相超前A相
 */

#include "bsp_encoder.h"

/* 四个轮子的编码器数据 */
volatile WheelEncoder_t wheels[4];

// 计算脉冲增量函数
static int16_t Get_Encoder_Delta(TIM_HandleTypeDef *htim, int16_t *last_cnt)
{
    int16_t cnt_now = (int16_t)__HAL_TIM_GET_COUNTER(htim);
    int16_t delta = cnt_now - *last_cnt;
    *last_cnt = cnt_now;
    return delta;
}

// 初始化TIM2/3/4/8的Encoder（必须在使用编码器前调用
void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL); // 电机1(WHEEL_RF)
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // 电机2(WHEEL_LF)
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL); // 电机3(WHEEL_LR)
    HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL); // 电机4(WHEEL_RR)

    // 初始化四个编码器结构体
    for (int i = 0; i < 4; i++)
    {
        wheels[i].last_cnt = 0;
        wheels[i].speed_rps = 0.0f;
        wheels[i].direction = 0;
    }
}

/**
 * @brief  更新所有轮子的转速和方向
 *         应在每个控制周期(10ms)调用一次
 */
void Encoder_Update_Speed(void)
{
    static int16_t last_cnt[4] = {0, 0, 0, 0};
    int16_t delta[4];

    // 读取四个编码器增量
    delta[WHEEL_RF] = Get_Encoder_Delta(&htim2, &last_cnt[WHEEL_RF]);
    delta[WHEEL_LF] = Get_Encoder_Delta(&htim3, &last_cnt[WHEEL_LF]);
    delta[WHEEL_LR] = Get_Encoder_Delta(&htim4, &last_cnt[WHEEL_LR]);
    delta[WHEEL_RR] = Get_Encoder_Delta(&htim8, &last_cnt[WHEEL_RR]);

    /* 计算转速和方向 */
    for (int i = 0; i < 4; i++)
    {

        /* 转速计算: 增量 / (每转脉冲数 * 采样周期) = 转/秒 */
        if (PULSE_PER_REV > 0)
        {
            wheels[i].speed_rps = (float)delta[i] / (PULSE_PER_REV * CONTROL_PERIOD);
        }

        /* 方向判断 */
        if (delta[i] > 0)
        {
            wheels[i].direction = 0; // 正转
        }
        else if (delta[i] < 0)
        {
            wheels[i].direction = 1; // 反转
        }
        // delta=0 时保持上一次方向不变
    }
}

// 获取指定轮子的转速(转/秒)（轮子编号 0~3）
float Encoder_Get_Speed_RPS(uint8_t wheel_id)
{
    if (wheel_id < 4)
    {
        return wheels[wheel_id].speed_rps;
    }
    return 0.0f;
}

// 获取指定轮子的转动方向(转/秒)（轮子编号 0~3）
uint8_t Encoder_Get_Direction(uint8_t wheel_id)
{
    if (wheel_id < 4)
    {
        return wheels[wheel_id].direction;
    }
    return 0;
}