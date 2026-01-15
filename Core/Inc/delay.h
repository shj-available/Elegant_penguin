//
// Created by MECHERVO on 2025/11/28.
//

#ifndef FREERTOS_LED_DELAY_H
#define FREERTOS_LED_DELAY_H

#include "stm32f4xx.h"

void DWT_Delay_Init(void);
void delay_us(uint32_t us);

#endif //FREERTOS_LED_DELAY_H
