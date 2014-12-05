/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  Jim
  * @version V1.0
  * @date    01-Sep-2014
  * @brief   This is the led driver function.
  * @brief   LED  	PORT	ACTION 	
  *          LED1 : PE3		�͵�ƽ�������ߵ�ƽϨ��
  *          LED2 : PE4		�͵�ƽ�������ߵ�ƽϨ��
  *          LED3 : PE5		�͵�ƽ�������ߵ�ƽϨ��
  *          LED4 : PE5		�͵�ƽ�������ߵ�ƽϨ��
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 CSST Robot Research Center</center></h2>
  *
  ******************************************************************************
  */
 

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "bsp.h"

#ifdef ARM_CSST
	/* ����ARM_CSST��Ӧ��RCCʱ�Ӽ��˿� */
	#define RCC_LED RCC_AHB1Periph_GPIOE
	#define LEDPORT GPIOE
	#define LED1    GPIO_Pin_2
	#define LED2    GPIO_Pin_3
	#define LED3    GPIO_Pin_4
	#define LED4    GPIO_Pin_5
#endif

#ifdef ARM_ORIGINAL
	/* ARM������ָʾ�ƶ��� */
	#define RCC_LED RCC_AHB1Periph_GPIOA
	#define LEDPORT GPIOA
	#define LED1    GPIO_Pin_4
	#define LED2    GPIO_Pin_5
	#define LED3    GPIO_Pin_6
	#define LED4    GPIO_Pin_7
#endif

/* ���ⲿ���õĺ������� */
void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no, uint32_t _us);
uint8_t bsp_IsLedOn(uint8_t _no);

#endif

/****************** (C) COPYRIGHT CSST Robot Research Center *****END OF FILE****/
