/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************/

#include "stm32f10x_it.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* CANOpen includes */
#include "canfestival.h"
#include "can_STM32.h"

/*TEST*/
#include "canopen_thread.h"  //test
#include "ObjDict_CAN1.h"
#include "ObjDict_CAN2.h"
#include "LIFTER_OD.h"
//#include "globalstruct.h"

extern xQueueHandle xQ_CAN_MSG;
CO_DATA_STRUCT  CO_D_TEST = {NULL,NULL};  //test

void NMI_Handler(void)
{
	/* This interrupt is generated when HSE clock fails */
	if (RCC_GetITStatus(RCC_IT_CSS) != RESET)
	{
		/* At this stage: HSE, PLL are disabled (but no change on PLL config) and HSI
		is selected as system clock source */

		/* Enable HSE */
		RCC_HSEConfig(RCC_HSE_ON);

		/* Enable HSE Ready and PLL Ready interrupts */
		RCC_ITConfig(RCC_IT_HSERDY | RCC_IT_PLLRDY, ENABLE);

		/* Clear Clock Security System interrupt pending bit */
		RCC_ClearITPendingBit(RCC_IT_CSS);

		/* Once HSE clock recover, the HSERDY interrupt is generated and in the RCC ISR
		routine the system clock will be reconfigured to its previous state (before
		HSE clock failure) */
	}
}
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
// void SVC_Handler(void)
// {
// }
void DebugMon_Handler(void)
{
}
// void PendSV_Handler(void)
// {
// }

#include"stm32f10x.h"


// void SysTick_Handler(void)
// {
//  
// }
/*****************************************************************************/
void USART1_IRQHandler(void)
{ 
  uint8_t RX_dat; 
	CanTxMsg USART2CAN;
  
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		RX_dat =USART_ReceiveData(USART1);
		
		printf("USART1 Recevie Data: %x ",RX_dat);
				
		if(RX_dat == 0x01)
		{
			printf("Send a SDO Message: \r\n");
			
			USART2CAN.StdId = 0x206;
			USART2CAN.ExtId = 0x00;
			/* �Ƿ�Զ��֡ */
			USART2CAN.RTR = 0x00;
			/* CAN 2.0A ����B����� */
			USART2CAN.IDE = CAN_ID_STD;
			/* ���ݳ��� */
			USART2CAN.DLC = 1;
			/* Ϊ���ݸ�ֵ */                 

			USART2CAN.Data[0] = 0xFF;

			CAN_Transmit(CAN1, &USART2CAN);
			
		}
		else if(RX_dat == 0x02)
		{
			printf("Send a PDO Message: \r\n");
			
			USART2CAN.StdId = 0x206;
			USART2CAN.ExtId = 0x00;
			/* �Ƿ�Զ��֡ */
			USART2CAN.RTR = 0x00;
			/* CAN 2.0A ����B����� */
			USART2CAN.IDE = CAN_ID_STD;
			/* ���ݳ��� */
			USART2CAN.DLC = 1;
			/* Ϊ���ݸ�ֵ */                 

			USART2CAN.Data[0] = 0xEE;

			CAN_Transmit(CAN1, &USART2CAN);
		}else{
			printf("Nothing Send \r\n");
		}
		
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET);
		{
		  USART_ClearFlag(USART1,USART_FLAG_RXNE);
		}
  }	
}

/*****************************************************************************/
void USART2_IRQHandler(void)
{
		
}
/*******************************************************************************/

void USART3_IRQHandler(void)
{ 
  uint8_t RX_dat; 
	CanTxMsg USART2CAN;
  
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {	
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		
		RX_dat =USART_ReceiveData(USART3);
		
		printf("USART1 Recevie Data: %x ",RX_dat);
				
		if(RX_dat == 0x01)
		{
			printf("Send a SDO Message: \r\n");
			
			USART2CAN.StdId = 0x206;
			USART2CAN.ExtId = 0x00;
			/* �Ƿ�Զ��֡ */
			USART2CAN.RTR = 0x00;
			/* CAN 2.0A ����B����� */
			USART2CAN.IDE = CAN_ID_STD;
			/* ���ݳ��� */
			USART2CAN.DLC = 1;
			/* Ϊ���ݸ�ֵ */                 

			USART2CAN.Data[0] = 0xFF;

			CAN_Transmit(CAN1, &USART2CAN);
			
		}
		else if(RX_dat == 0x02)
		{
			printf("Send a PDO Message: \r\n");
			
			USART2CAN.StdId = 0x206;
			USART2CAN.ExtId = 0x00;
			/* �Ƿ�Զ��֡ */
			USART2CAN.RTR = 0x00;
			/* CAN 2.0A ����B����� */
			USART2CAN.IDE = CAN_ID_STD;
			/* ���ݳ��� */
			USART2CAN.DLC = 1;
			/* Ϊ���ݸ�ֵ */                 

			USART2CAN.Data[0] = 0xEE;

			CAN_Transmit(CAN1, &USART2CAN);
		}else{
			printf("Nothing Send \r\n");
		}
		
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET);
		{
		  USART_ClearFlag(USART3,USART_FLAG_RXNE);
		}
  }	
}
/*****************************************************************************/
void DMA1_Channel7_IRQHandler(void)	//TX
{

}
/********************************************************************/
void DMA1_Channel3_IRQHandler(void)//RX
{

}
void DMA1_Channel4_IRQHandler(void)
{
	 /*DMA_Cmd(DMA1_Channel4, DISABLE);
	 DMA1_Channel4->CNDTR = trsbytes;
	 DMA_ClearITPendingBit(DMA1_IT_TC4);
	 DMA_Cmd(DMA1_Channel4, ENABLE);*/
}


void DMA1_Channel5_IRQHandler(void)
{
   USART1->CR1|=0X00000010; 					//Enable idle interupt
	DMA_ClearITPendingBit(DMA1_IT_TC5);//Clear flag
}


 /**
  * CAN1�����жϴ�����
  * @brief  
  *         ��ͨ���Ĵ����У�CAN�ж���ֻ�����ST�⺯���е�CAN���մ�����CAN_Receive()
  *         ��CANOpen�е�CAN���պ���canDispatch(&object_data,&m)����.
  *         
  *         �ڱ������У�CAN��Ϣ���洢�ڶ���xQ_CAN_MSG��(���пɴ洢20������CAN2.0A��Ϣ)
  *         ���ԣ���CANx_RX0_IQRHandler�н����ǽ����յ������ݴ�CAN_FIFO0��ȡ����������
  *         xQ_CAN_MSG�У�������������ӦΪ��
  *         
  *         ����CAN���ձ���->ʧ��CAN�ж�->����CAN��������->�����յ�����push��������->
  *         �˳��ٽ���->�ó�CPUռ��->��������ж�->ʹ��CAN�ж�
  *         
  * @param  None
  * @retval None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CANOpen_Message CAN1_Rx_m;

	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;     //�ж��л���������

	printf("ENTER CAN1 RX0 IRQHandler... \r\n");

	taskENTER_CRITICAL();                                  //�����ж�

	CAN_Receive(CAN1, CAN_FIFO0, &(CAN1_Rx_m.m));	    //��CAN1 FIFO0��������

	CAN1_Rx_m.CANx = 1;

	if(NULL != xQ_CAN_MSG)         // ����з������ݰ�
	{
		xQueueSendFromISR(xQ_CAN_MSG, &CAN1_Rx_m, &xHigherPriorityTaskWoken);
	}
	
	taskEXIT_CRITICAL();
	
	if( xHigherPriorityTaskWoken != pdFALSE )
	{
		portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );           //ǿ���������л�
	}  

	
	
// 	u8 n;
// 	CanTxMsg TXMSG;
// 	
// 	CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);
// 	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage_FIFO0);
// 	
// 	//GPIO_ResetBits(GPIOA,GPIO_Pin_2); 
// 	
// 	for (n=0;n<RxMessage_FIFO0.DLC;n++)
// 	{
// 		RxMessage_BMS.Data[n] = RxMessage_FIFO0.Data[n];
// 	}
// 	

// 	if (RxMessage_FIFO0.StdId == 0x015)				//Data From PC
//  	{
// 		TXMSG.StdId = 0x051;
// 		TXMSG.ExtId = 0;
// 		TXMSG.IDE   = CAN_ID_STD;
// 		TXMSG.RTR   = CAN_RTR_DATA;

// 		if (RxMessage_FIFO0.Data[0] == 0x10)
// 		{
// 			TXMSG.DLC     = 2;
// 			TXMSG.Data[0] = RxMessage_FIFO0.Data[0];
// 			TXMSG.Data[1] = BMS.Status;
// 		}
// 		else
// 		if (RxMessage_FIFO0.Data[0] == 0x11)
// 		{
// 			TXMSG.DLC = 2;
// 			
// 			BMS.Status    = RxMessage_BMS.Data[1];
// 			TXMSG.Data[0] = RxMessage_FIFO0.Data[0];
// 			TXMSG.Data[1] = BMS.Status;
// 		}
// 		else
// 		if (RxMessage_FIFO0.Data[0] == 0x12)
// 		{
// 			TXMSG.DLC     = 2;
// 			TXMSG.Data[0] = RxMessage_FIFO0.Data[0];
// 			TXMSG.Data[1] = BMS.StateOfCharge;
// 		}
// 		else
// 		if (RxMessage_FIFO0.Data[0] == 0x13)
// 		{
// 			TXMSG.DLC     = 3;
// 			TXMSG.Data[0] = RxMessage_FIFO0.Data[0];
// 			TXMSG.Data[1] = (BMS.Voltage)>>8;
// 			TXMSG.Data[2] = (BMS.Voltage)&0xff;
// 		}
// 		else
// 		if (RxMessage_FIFO0.Data[0] == 0x14)
// 		{
// 			TXMSG.DLC     = 3;	
// 			TXMSG.Data[0] = RxMessage_FIFO0.Data[0];
// 			TXMSG.Data[1] = (BMS.TimeToEmpty)>>8;
// 			TXMSG.Data[2] = (BMS.TimeToEmpty)&0xff;
// 		}
// 		else
// 		if (RxMessage_FIFO0.Data[0] == 0x15)
// 		{
// 			TXMSG.DLC     = 2;
// 			TXMSG.Data[0] = RxMessage_FIFO0.Data[0];
// 			TXMSG.Data[1] = BMS.StateOfHealth;
// 		}else
// 		if (RxMessage_FIFO0.Data[0] == 0x16)
// 		{
// 			TXMSG.DLC     = 3;
// 			TXMSG.Data[0] = RxMessage_FIFO0.Data[0];
// 			TXMSG.Data[1] = (BMS.AverageCurrent)>>8;
//       TXMSG.Data[2] = (BMS.AverageCurrent)&0xff;
// 		}else
// 		{
// 			TXMSG.DLC     = 1;
// 			TXMSG.Data[0] = 0xFF;
//     	}
// 	}else
// 	if ((RxMessage_FIFO0.StdId == 0x035)&&(RxMessage_FIFO0.Data[0] == 0x10))				//Data From CHASSIS
//  	{
// 		TXMSG.StdId = 0x053; 
// 		TXMSG.ExtId = 0;     
// 		TXMSG.IDE   = CAN_ID_STD;                                    
// 		TXMSG.RTR   = CAN_RTR_DATA;
// 		TXMSG.DLC     = 2;
// 		
// 		
// 		USART_SendData(USART1,0x53);
// 		
// 		if (GPIO_ReadInputDataBit(CHARGE_DET_PORT,CHARGE_DET_PIN)== 0)
// 		{
// 			/* Send Flag With CAN1 - U Have to STOP!!! CHASSIS!!!!*/
// 			TXMSG.Data[0] = 0x10;
// 			TXMSG.Data[1] = 0x01;  //Charging-Stop
// 		}else
// 		{
// 			TXMSG.Data[0] = 0x10;
// 			TXMSG.Data[1] = 0x02;	//Uncharging-Free to Go
// 		}
// 	}
// // 	}else
// // 	{
// // 		TXMSG.StdId = 0x051; 
// // 		TXMSG.ExtId = 0;     
// // 		TXMSG.IDE   = CAN_ID_STD;                                    
// // 		TXMSG.RTR   = CAN_RTR_DATA;
// // 		
// // 		TXMSG.DLC     = 8;	
// // 		TXMSG.Data[0] = RxMessage_FIFO0.StdId;
// // 		TXMSG.Data[1] = RxMessage_FIFO0.Data[0];
// // 		TXMSG.Data[2] = RxMessage_FIFO0.Data[1];
// // 		TXMSG.Data[3] = RxMessage_FIFO0.Data[2];
// // 		TXMSG.Data[4] = RxMessage_FIFO0.Data[3];
// // 		TXMSG.Data[5] = RxMessage_FIFO0.Data[4];
// // 		TXMSG.Data[6] = RxMessage_FIFO0.Data[5];
// // 		TXMSG.Data[7] = RxMessage_FIFO0.Data[6];

// // 		mailbox = CAN_Transmit(CAN1,&TXMSG);
// // 		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
// // 		//delay(500000000);
// // 	}
//   

// 	//USART_SendData(USART1,TXMSG.Data[0]);
// 	//USART_SendData(USART1,TXMSG.Data[1]);
// 	
// 	//USART_SendData(USART1,0xEE);
// 	mailbox = CAN_Transmit(CAN1,&TXMSG);
// 	
// 	//data_back(BMS.Voltage, BMS.AverageCurrent, BMS.TimeToEmpty,
// 			  //BMS.StateOfCharge, BMS.StateOfHealth);
// 	
// 	//GPIO_SetBits(GPIOA,GPIO_Pin_2);
// 	CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
// 	CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);
}

void TIM2_IRQHandler(void)
{
// 	if (TIM2->SR&0x0001)
// 	{	
// 		GPIO_SetBits(GPIOA, GPIO_Pin_0);  //Work LED
// 		
// // 		if (GPIO_ReadInputDataBit(POWER_DET_PORT,POWER_DET_PIN)== 0)
// // 		{
// // 			if (TimerFlag.BQZ < 3)
// // 			{
// // 				CanSendDataShun[0] = 0x12;
// // 				CanSendDataShun[0] = 0x01;
// // 				CanSend(CAN1,0x057,0,CAN_ID_STD,CAN_RTR_DATA,2,CanSendDataShun);
// // 			}
// // 			
// // 			TimerFlag.BQZ++;  //Counter for WIFI Block Shut down
// // 			//USART_SendData(USART1,TimerFlag.BQZ);
// // 		}
// // 		
// //		Robot_task();
// 	}
// 	TIM2->SR&=~(1<<0);
}

/**********************************************************************/
void TIM3_IRQHandler(void)
{

}
/*************************************************************************/
void TIM4_IRQHandler(void)
{

}
/*************************************************************************/
void TIM5_IRQHandler(void)
{

}

//***********************************************************************

void TIM8_UP_IRQHandler(void)
{

}

void TIM1_UP_IRQHandler(void)
{

}
/*****************************************************************************/
void EXTI15_10_IRQHandler(void)
{		     	    

}
/****************************************************************************/
void EXTI2_IRQHandler(void)
{
	
}

void EXTI9_5_IRQHandler(void)
{
// 	 ErrorStatus HSEStartUpStatus;

//     //ʹ���ⲿ����
//     RCC_HSEConfig(RCC_HSE_ON);
//     //�ȴ��ⲿ�����ȶ�
//     HSEStartUpStatus = RCC_WaitForHSEStartUp();
//     //����ⲿ���������ɹ����������һ������
//     if(HSEStartUpStatus==SUCCESS)
//     {
//         //����HCLK��AHBʱ�ӣ�=SYSCLK
//         RCC_HCLKConfig(RCC_SYSCLK_Div1);

//         //PCLK1(APB1) = HCLK/2
//         RCC_PCLK1Config(RCC_HCLK_Div2);

//         //PCLK2(APB2) = HCLK
//         RCC_PCLK2Config(RCC_HCLK_Div1);
//         
//  
//         RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_4);
//         //����PLL
//         RCC_PLLCmd(ENABLE);
//         //�ȴ�PLL�ȶ�
//         while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
//         //ϵͳʱ��SYSCLK����PLL���
//         RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//         //�л�ʱ�Ӻ�ȴ�ϵͳʱ���ȶ�
//         while(RCC_GetSYSCLKSource()!=0x08);  
//      }
//    /* RCC system reset(for debug purpose) */
		 
	//if(EXTI_GetITStatus(EXTI_Line6) != RESET)     //���ָ����EXTI6��·�������������
	//{

		//EXTI_ClearITPendingBit(EXTI_Line6);  //���EXTI6��·����λ

// 		RCCInit();			//Clock Initial
// 		DMAInit();			//DMA   Initial
// 		GPIOInit();			//I/O 	Initial
// // 		POWER_OFF;
// // 		delay(5000000);		//Wait For Voltage Calm Down
// // 		CAN_Configuration();//CAN    Initial
//  		USARTInit();		//Serial Initial
// 		TIMInit();			//Timer  Initial
//  		NVICInit();			//Interrupt Controller Initial
//  		EXTIInit();
//  		
//  		DataBlockInit();
		
		//GPIO_SetBits(GPIOA,GPIO_Pin_2);
	//}
}

/*** (C) COPYRIGHT 2014 CSST R&D Intelligent Robotics Research Centre *END OF FILE*/
