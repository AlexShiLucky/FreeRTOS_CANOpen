/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��
*	�ļ����� : bsp.h
* ��    �� ��Jim
* ��    �� ��1.0
* ��    �� ��2014.08.25
*
*	˵    �� : 
* 	���ǵײ�����ģ�����е�h�ļ��Ļ����ļ���
* 	Ӧ�ó���ֻ�� #include bsp.h ���ɣ�����Ҫ#include ÿ��ģ��� h �ļ���
*
* �޸ļ�¼ :
* 	�汾��		����				����				˵��
* 	V1.0		2014-12-01		Jim				�����ļ�����ӻ�����������
*
*	Copyright (C), 2013-2014, CSST
*********************************************************************************************************
*/

#ifndef _BSP_H_
#define _BSP_H

/* ���� BSP �汾�� */
#define __STM32F103_BSP_VERSION		"1.0"

// /* ����ȫ���жϵĺ� */
// #define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
// #define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

/* ���������ڵ��Խ׶��Ŵ� */
//#define BSP_Printf	printf


/* STM32 includes. */
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

#include "main.h"

/* BSP Driver includes */
#include "bsp_led.h"
// #include "bsp_can.h"
// #include "bsp_usart.h"
// #include "bsp_tim.h"
// #include "bsp_exti.h"
// #include "bsp_adc.h"

#include "serial_debug.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* CANOpen includes. */
#include "canopen_thread.h"

/* Robot Control includes. */
//#include "lifter_control.h"


#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif


void bsp_Init(void);

#endif

/*** (C) COPYRIGHT 2014 CSST R&D Intelligent Robotics Research Centre *END OF FILE*/

