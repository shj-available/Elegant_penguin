/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOE
#define DAT_Pin GPIO_PIN_5
#define DAT_GPIO_Port GPIOE
#define CMD_Pin GPIO_PIN_6
#define CMD_GPIO_Port GPIOE
#define SPARE1_Pin GPIO_PIN_0
#define SPARE1_GPIO_Port GPIOC
#define SPARE2_Pin GPIO_PIN_1
#define SPARE2_GPIO_Port GPIOC
#define L_STEP_Pin GPIO_PIN_2
#define L_STEP_GPIO_Port GPIOC
#define L_DIR_Pin GPIO_PIN_3
#define L_DIR_GPIO_Port GPIOC
#define R_STEP_Pin GPIO_PIN_4
#define R_STEP_GPIO_Port GPIOC
#define R_DIR_Pin GPIO_PIN_5
#define R_DIR_GPIO_Port GPIOC
#define LED_R_Pin GPIO_PIN_11
#define LED_R_GPIO_Port GPIOE
#define SLEEP_Pin GPIO_PIN_1
#define SLEEP_GPIO_Port GPIOB
#define VCC_Pin GPIO_PIN_0
#define VCC_GPIO_Port GPIOB
#define LED_G_Pin GPIO_PIN_14
#define LED_G_GPIO_Port GPIOF
#define CLK_Pin GPIO_PIN_12
#define CLK_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
