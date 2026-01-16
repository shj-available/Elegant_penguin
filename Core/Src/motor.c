//
// Created by MECHERVO on 2025/11/20.
//
#include "motor.h"
#include "cmsis_os.h"
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

static float cur_speed_L = 0.0f;
static float cur_speed_R = 0.0f;

static float tgt_speed_L = 0.0f;
static float tgt_speed_R = 0.0f;

static float max_accel_L = 1500.0f;   // step/s^2
static float max_accel_R = 1500.0f;

#define CONTROL_PERIOD_MS   1.0f
#define TIMER_CLK_HZ        1000000.0f   // 你的 TIM 时钟（Prescaler 后）
#define MIN_SPEED           10.0f

void MotorOn() {HAL_GPIO_WritePin(GPIOB, SLEEP_Pin, GPIO_PIN_SET);}
void MotorOff() {HAL_GPIO_WritePin(GPIOB, SLEEP_Pin, GPIO_PIN_RESET);}

static void update_pwm_from_speed(TIM_HandleTypeDef *htim, float speed)
{
    if (speed < MIN_SPEED)
    {
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, 0);
        return;
    }

    float period = TIMER_CLK_HZ / speed;   // us
    uint32_t arr = (uint32_t)(period - 1);

    __HAL_TIM_SET_AUTORELOAD(htim, arr);
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, arr / 1.05); // 50% duty
}

/* ================= 主控制接口 ================= */
void drive_motor(uint16_t mode)
{    switch (mode)
    {
        case 16:
            tgt_speed_L = 1500;
            tgt_speed_R = 1500;
            break;

        case 32:
            tgt_speed_L = 1500;
            tgt_speed_R = 0;
            break;

        case 64:
            tgt_speed_L = 500;
            tgt_speed_R = 0;
            break;

        case 128:
            tgt_speed_L = 0;
            tgt_speed_R = 1500;
            break;

        default:
            tgt_speed_L = 0;
            tgt_speed_R = 0;
            break;
    }

    float dv_L = max_accel_L * (CONTROL_PERIOD_MS / 1000.0f);
    float dv_R = max_accel_R * (CONTROL_PERIOD_MS / 1000.0f);

    /* ===== 左电机缓启动 ===== */
    if (cur_speed_L < tgt_speed_L)
    {
        cur_speed_L += dv_L;
        if (cur_speed_L > tgt_speed_L)
            cur_speed_L = tgt_speed_L;
    }
    else if (cur_speed_L > tgt_speed_L)
    {
        cur_speed_L -= dv_L;
        if (cur_speed_L < tgt_speed_L)
            cur_speed_L = tgt_speed_L;
    }

    /* ===== 右电机缓启动 ===== */
    if (cur_speed_R < tgt_speed_R)
    {
        cur_speed_R += dv_R;
        if (cur_speed_R > tgt_speed_R)
            cur_speed_R = tgt_speed_R;
    }
    else if (cur_speed_R > tgt_speed_R)
    {
        cur_speed_R -= dv_R;
        if (cur_speed_R < tgt_speed_R)
            cur_speed_R = tgt_speed_R;
    }

    /* ===== 输出控制 ===== */
    if (cur_speed_L > 0.0f || cur_speed_R > 0.0f)
    {
        MotorOn();
        update_pwm_from_speed(&htim4, cur_speed_L);
        update_pwm_from_speed(&htim5, cur_speed_R);
    }
    else
    {
        MotorOff();
    }
}
