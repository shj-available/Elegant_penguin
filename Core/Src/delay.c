//
// Created by MECHERVO on 2025/11/28.
//
#include "delay.h"

void DWT_Delay_Init(void)
{
    /* Enable TRC */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    /* Reset the counter */
    DWT->CYCCNT = 0;

    /* Enable the cycle counter */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = (SystemCoreClock / 1000000) * us;  // 1us 的 tick 数

    while ((DWT->CYCCNT - start) < ticks)
        ;
}