/**
  ******************************************************************************
  * @file    bsp.c
  * @author  Jim
  * @version V1.0
  * @date    01-Sep-2014
  * @brief   This is the bsp driver function for STM32F407ZGT6.
  * @brief 	 bsp = Borad surport packet �弶֧�ְ�
  *          ����Ӳ���ײ�������������ļ���ÿ��c�ļ����� #include "bsp.h" 
  *          ���������е���������ģ��
  * 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 CSST Robot Research Center</center></h2>
  *
  ******************************************************************************
  */


#include "bsp.h"
#include "stm32f10x_conf.h"


void bsp_Init(void)
{
	/*
		����ST�̼���������ļ��Ѿ�ִ����CPUϵͳʱ�ӵĳ�ʼ�������Բ����ٴ��ظ�����ϵͳʱ�ӡ�
		�����ļ�������CPU��ʱ��Ƶ�ʡ��ڲ�Flash�����ٶȺͿ�ѡ���ⲿSRAM FSMC��ʼ����

		ϵͳʱ��ȱʡ����Ϊ168MHz�������Ҫ���ģ������޸� system_stm32f4xx.c �ļ�
	*/
   /* Enable CRC clock */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	
	 /* ��Բ�ͬ��Ӧ�ó��������Ҫ�ĵײ�����ģ���ʼ������ */
	 bsp_InitLed(); 		/* ��ʼLEDָʾ�ƶ˿� */
}


/****************** (C) COPYRIGHT CSST Robot Research Center *****END OF FILE****/
