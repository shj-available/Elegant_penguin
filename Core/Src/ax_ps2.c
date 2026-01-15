/**			                                                    
		   ____                    _____ _______ _____       XTARK@???????
		  / __ \                  / ____|__   __|  __ \ 
		 | |  | |_ __   ___ _ __ | |       | |  | |__) |
		 | |  | | '_ \ / _ \ '_ \| |       | |  |  _  / 
		 | |__| | |_) |  __/ | | | |____   | |  | | \ \ 
		  \____/| .__/ \___|_| |_|\_____|  |_|  |_|  \_\
				| |                                     
				|_|                OpenCTR   ???????????
									 
  ****************************************************************************** 
  *           
  * ??????У? XTARK@???????  ??????У???????
  * ???????? www.xtark.cn   www.tarkbot.com
  * ???????? https://xtark.taobao.com  
  * ???????? ????????????????????????????????
  *      
  ******************************************************************************
  * @??  ??  Musk Han@XTARK
  * @??  ??  V1.0
  * @??  ??  2022-7-26
  * @??  ??  PS2??????????????
  *
  ******************************************************************************
  * @?  ??
  *
  *   PS2???????
  *   BYTE   DATA   ????
  *   01     idle
  *   02     0x73   ?????????
  *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
  *   04     data   SLCT  JOYR  JOYL  STRT   UP   RGIHT  DOWN   L
  *   05     data   L2     R2     L1    R1   /\     O     X    ??
  *   06     data   ??????  0x00 = ??    0xff = ??
  *   07     data   ??????  0x00 = ??    0xff = ??
  *   08     data   ??????  0x00 = ??    0xff = ??
  *   09     data   ??????  0x00 = ??    0xff = ??
  * 
  ******************************************************************************
  */

#include "ax_ps2.h"
#include "delay.h"
#include "main.h"
#include "cmsis_os2.h"

uint16_t num;

//PS2??????????????
#define DI()      HAL_GPIO_ReadPin(GPIOE, DAT_Pin)
#define CMD_H()   HAL_GPIO_WritePin(GPIOE, CMD_Pin, GPIO_PIN_SET)
#define CMD_L()   HAL_GPIO_WritePin(GPIOE, CMD_Pin, GPIO_PIN_RESET)
#define CS_H()    HAL_GPIO_WritePin(GPIOE, CS_Pin, GPIO_PIN_SET)
#define CS_L()    HAL_GPIO_WritePin(GPIOE, CS_Pin, GPIO_PIN_RESET)
#define CLK_H()   HAL_GPIO_WritePin(GPIOE, CLK_Pin, GPIO_PIN_SET)
#define CLK_L()   HAL_GPIO_WritePin(GPIOE, CLK_Pin, GPIO_PIN_RESET)


const  uint8_t PS2_cmnd[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //??????????????                         
volatile uint8_t PS2_data[9] = {0};  //?????????

static uint8_t PS2_ReadWriteData(uint8_t data)
{
	uint8_t ref,res = 0; //这里一定要置零！！！因为res可能会有随机值，此时当对某位不操作时，其本来应该变为0，但实际上会保留原值导致错误；
	
	
	for(ref = 0x01; ref > 0x00; ref <<= 1)
	{
		CLK_L();
		if(ref&data)
			CMD_H();
		else
			CMD_L();

        //delay_us(16);
		osDelay(1);
		
		CLK_H();
		if(DI()){
            res |= ref;//这里很唐，res只能从0变1不能从1变0，所以前面res必须初始化为0，不然结果就会多一堆1
            num++;
        }


        //delay_us(16);
		osDelay(1);
	}
	
	CMD_H();

	//???????????
    return res;	
}

/**
  * @??  ??  PS2?????????????????
  * @??  ??  *JoystickStruct ??????????
  * @?????  ??
  */
void AX_PS2_ScanKey(JOYSTICK_TypeDef *JoystickStruct)
{
	uint8_t i;
	
	//??????
	CS_L();
	
	//???PS2????
	for(i=0; i<9; i++)
	{
		PS2_data[i] = PS2_ReadWriteData(PS2_cmnd[i]);
		//delay_us(16);
		osDelay(1);
	}
	
	//??????
	CS_H();

	//???????
	JoystickStruct->mode = PS2_data[1];
	JoystickStruct->btn1 = ~PS2_data[3];
	JoystickStruct->btn2 = ~PS2_data[4];
	JoystickStruct->RJoy_LR = PS2_data[5];
	JoystickStruct->RJoy_UD = PS2_data[6];
	JoystickStruct->LJoy_LR = PS2_data[7];
	JoystickStruct->LJoy_UD = PS2_data[8];
}



/******************* (C) ??? 2022 XTARK **************************************/
