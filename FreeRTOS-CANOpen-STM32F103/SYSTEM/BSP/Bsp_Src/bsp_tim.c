/*
*********************************************************************************************************
*
*	ģ������ : BSP-TIMģ��
*	�ļ����� : bsp_led.c
* ��    �� ��Jim
* ��    �� ��1.0
* ��    �� ��2014.08.25
*
*	˵    �� : 
* 	�ó���������CSST���������ARM���ư壬�����������Ӳ�������޸���Ӧ����
*		CSST-STM32F407 ������LED���߷��䣺
*		LED1	:	PE2		�͵�ƽ�������ߵ�ƽϨ��
*		LED2	: PE3		�͵�ƽ�������ߵ�ƽϨ��
*		LED3	: PE4		�͵�ƽ�������ߵ�ƽϨ��
*		LED4	: PE5		�͵�ƽ�������ߵ�ƽϨ��
*
* �޸ļ�¼ :
* 	�汾��		����				����				˵��
* 	V1.0		2014-08-24		Jim				�����ļ�����ӻ�����������
*
*	Copyright (C), 2013-2014
*
*********************************************************************************************************
*/

#include "bsp.h"

/* �����Ӧ��RCCʱ�Ӽ��˿� */
// #define RCC_LED RCC_AHB1Periph_GPIOE
// #define LEDPORT GPIOE
// #define LED1    GPIO_Pin_2
// #define LED2    GPIO_Pin_3
// #define LED3    GPIO_Pin_4
// #define LED4    GPIO_Pin_5

/* ARM������ָʾ�ƶ��� */
#define RCC_LED RCC_AHB1Periph_GPIOA
#define LEDPORT GPIOA
#define LED1    GPIO_Pin_4
#define LED2    GPIO_Pin_5
#define LED3    GPIO_Pin_6
#define LED4    GPIO_Pin_7

/**
  * @brief  Sets the TIMx Capture Compare1 Register value
  * @param  TIMx: where x can be 1 to 14 except 6 and 7, to select the TIM peripheral.
  * @param  Compare1: specifies the Capture Compare1 register new value.
  * @retval None
  */
void bsp_InitTim(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ��TIMʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
	
	//T1PWM
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);
	//T1PWM
	
	
	
// 	uint16_t PrescalerValue = 0;	// Prescaler of the Timer5

//   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
//   TIM_OCInitTypeDef TIM_OCInitStructure;   
// 	//--------------TIM1������
//   TIM_TimeBaseStructure.TIM_Prescaler = 100;
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//   TIM_TimeBaseStructure.TIM_Period = HALFPWMTIMERPERIOD*2;
//   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//   TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
//   TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
//   
//   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
//   TIM_OCInitStructure.TIM_Pulse = 0;
//   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  //��ûƥ�䣬��!
//   TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;  //ƥ��֮�󣬵�!
//   TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//   TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//   //TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
//   TIM_OC2Init(TIM1, &TIM_OCInitStructure);
// 	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
//   TIM_OC4Init(TIM1, &TIM_OCInitStructure);
//   TIM_Cmd(TIM1, ENABLE);
//   TIM_CtrlPWMOutputs(TIM1, ENABLE);
//   //---------------TIM1������

//   //--------------TIM5������
//   /* Compute the prescaler value */
//   // System clock 100MHz
//   PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 24000000) - 1;


//   /* TIM5 clock enable */
//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
//   /* Time base configuration */
//   TIM_TimeBaseStructure.TIM_Period = 800000;  //    Timer5: 24000000/1000000 = 24 hz
//   TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue; 
//   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//   TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
//   /* TIM IT enable */
//   TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
//   /* TIM5 enable counter */
//   TIM_Cmd(TIM5, ENABLE);
//   //--------------TIM5������
  

	/*
		�������е�LEDָʾ��GPIOΪ�������ģʽ
		���ڽ�GPIO����Ϊ���ʱ��GPIO����Ĵ�����ֵȱʡ��0����˻�����LED����.
		�����Ҳ�ϣ���ģ�����ڸı�GPIOΪ���ǰ���ȹر�LEDָʾ��
	*/
// 	bsp_LedOff(1);
// 	bsp_LedOff(2);
// 	bsp_LedOff(3);
// 	bsp_LedOff(4);
	
	bsp_LedOn(1);
	bsp_LedOn(2);
	bsp_LedOn(3);
	bsp_LedOn(4);
	
	GPIO_InitStructure.GPIO_Pin = LED1|LED2|LED3|LED4;		 /* ��Ϊ����� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;/* ��Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; /* ���������費ʹ�� */
	GPIO_Init(LEDPORT, &GPIO_InitStructure);
	//GPIO_WriteBit(LEDPORT, LED1|LED2|LED3|LED4, Bit_SET);
}

/***********************************************************************************************/
