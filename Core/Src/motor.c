//
// Created by MECHERVO on 2025/11/20.
//
#include "motor.h"
#include "cmsis_os.h"
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;


#define DIR_L_Forward() HAL_GPIO_WritePin(GPIOC,L_DIR_Pin,GPIO_PIN_SET)
#define DIR_L_Backward() HAL_GPIO_WritePin(GPIOC,L_DIR_Pin,GPIO_PIN_RESET)
#define DIR_R_Forward() HAL_GPIO_WritePin(GPIOC,R_DIR_Pin,GPIO_PIN_RESET)
#define DIR_R_Backward() HAL_GPIO_WritePin(GPIOC,R_DIR_Pin,GPIO_PIN_SET)

#define STEP_L_On() HAL_GPIO_WritePin(GPIOC,L_STEP_Pin,GPIO_PIN_SET)
#define STEP_L_Off() HAL_GPIO_WritePin(GPIOC,L_STEP_Pin,GPIO_PIN_RESET)
#define STEP_R_On() HAL_GPIO_WritePin(GPIOC,R_STEP_Pin,GPIO_PIN_SET)
#define STEP_R_Off() HAL_GPIO_WritePin(GPIOC,R_STEP_Pin,GPIO_PIN_RESET)

#define Pulse_duration 10

void MotorOn() {HAL_GPIO_WritePin(GPIOB, SLEEP_Pin, GPIO_PIN_SET);}
void MotorOff() {HAL_GPIO_WritePin(GPIOB, SLEEP_Pin, GPIO_PIN_RESET);}
//void setVelocity(float w_l,float w_r){
//    //dps
//
//}
void drive_motor(uint16_t mode){
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 50);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 50);
    if (mode == 16){
        __HAL_TIM_SET_AUTORELOAD(&htim4, 199);
        __HAL_TIM_SET_AUTORELOAD(&htim4, 199);
        MotorOn();
        DIR_L_Forward();
        DIR_R_Forward();
        STEP_L_On();
        STEP_R_On();
        //delay_us(Pulse_duration);
        osDelay(1);
        STEP_L_Off();
        STEP_R_Off();
        osDelay(9);

    }
    else if (mode == 64){
        __HAL_TIM_SET_AUTORELOAD(&htim4, 99);
        __HAL_TIM_SET_AUTORELOAD(&htim4, 99);
        MotorOn();
        DIR_L_Forward();
        DIR_R_Forward();
        STEP_L_On();
        STEP_R_On();
        //delay_us(Pulse_duration);
        osDelay(1);
        STEP_L_Off();
        STEP_R_Off();
        osDelay(4);
    }
    else if (mode == 32){
        MotorOn();
        __HAL_TIM_SET_AUTORELOAD(&htim4, 66);
        __HAL_TIM_SET_AUTORELOAD(&htim4, 66);
        DIR_L_Forward();
        DIR_L_Forward();
        STEP_L_On();
        STEP_R_On();
        //delay_us(Pulse_duration);
        osDelay(1);
        STEP_L_Off();
        STEP_R_Off();
        osDelay(1);
    }
    else if (mode == 128){
        MotorOn();
        __HAL_TIM_SET_AUTORELOAD(&htim4, 1999);
        __HAL_TIM_SET_AUTORELOAD(&htim4, 19999);
        DIR_L_Forward();
        DIR_L_Forward();
        STEP_R_On();
        //delay_us(Pulse_duration);
        osDelay(1);
        STEP_R_Off();
        osDelay(39);
    }
    else{
        MotorOff();
        osDelay(10);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 0);
    }
}