/**
  ******************************************************************************
  * @file    CAN/LoopBack/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
//#include "main.h"  //comment on 23/10/2014

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* CANOpen includes */
#include "canfestival.h"
#include "can_STM32.h"

/*TEST*/
#include "canopen_thread.h"  //test

#include "CHASSIS_OD.h"
#include "globalstruct.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern xQueueHandle xQ_CAN_MSG;
CO_DATA_STRUCT  CO_D_TEST = {NULL,NULL};  //test
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
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

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
		//USART_Send(4,4,4,4,4,USART1);
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
// void SVC_Handler(void)
// {
// }

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
// void DebugMon_Handler(void)
// {
// }

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
// void PendSV_Handler(void)
// {
// }

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
// void SysTick_Handler(void)
// {
// }

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

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

			CAN_Transmit(CAN2, &USART2CAN);
			
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

			CAN_Transmit(CAN2, &USART2CAN);
		}else{
			printf("Nothing Send \r\n");
		}
		
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
		{
		  //USART_ClearFlag(USART1,USART_FLAG_RXNE);
		}
  }	
	
}

void UART4_IRQHandler(void)                            //��f1��?
{
// 	int index_dump;
// 	if (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) != RESET)   //�P??�ͱ�����?
// 	{
// 		USART_ClearITPendingBit(UART4,   USART_IT_RXNE);       //�M����??��
// 		if(lidar_init_ok_P==FALSE)
// 		{
// 			if(lidar_offset_count<=62)
// 			{
// 				lidar_offset_count++;
// 			}
// 			if(lidar_offset_count>56)
// 			{
// 				if(lidar_offset_count<=63)
// 				{
// 					lidar_message[lidar_offset_count-57] = USART_ReceiveData(UART4);
// 					{
// 						if(lidar_offset_count==63)
// 						{
// 							if(lidar_message[0] == 0xa5 && lidar_message[1] == 0x5a && lidar_message[2] == 0x05 && lidar_message[3] == 0x00 && 
// 							lidar_message[4] == 0x00 && lidar_message[5] == 0x40 && lidar_message[6] == 0x81)
// 							{
// 								lidar_init_ok_P = true;
// 								lidar_offset_count = 0;
// 							}
// 						}
// 					}
// 				}
// 				
// 			}
// 		}
// 		else
// 		{
// 		   
// 		   	if(lidar_offset_count < 5)
// 			{
// 				lidar_message[lidar_offset_count] = USART_ReceiveData(UART4);
// 				lidar_offset_count++;
// 			}
// 			if(lidar_offset_count == 5)
// 			{	
// 				lidar_offset_count = 0;
// 				
// 				index_dump = (lidar_message[2]*256+lidar_message[1])/128;
// 				if(index_dump<360)
// 				{
// 					RP_Lidar_Buf[index_dump][0] = (lidar_message[4]*256+lidar_message[3])/40-20;
// 					if(RP_Lidar_Buf[index_dump][0]<0)
// 					{
// 						RP_Lidar_Buf[index_dump][0]=300;
// 					}
// 					if(RP_Lidar_Buf[index_dump][0]>300)
// 					{
// 						RP_Lidar_Buf[index_dump][0]=300;
// 					}

// 					
// 				//	USART_SendData(USART1, RP_Lidar_Buf[index_dump][0]);                                     //?�e?�u
// 				//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}//����?�e?
// 				}
// 				
// 			}	
// 			  
// 		
// 		//	USART_SendData(USART1, USART_ReceiveData(UART4));                                     //?�e?�u
// 		//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}//����?�e?��
// 				
// 		}
// 		
// 	}
	
}

//#ifdef USE_CAN1
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

void CAN1_RX0_IRQHandler(void)
{ 
//   /*�����ж�*/
//   
//   int i;
//   Message RxMSG;  /* ��׼��CAN2.0A��Ϣ����ʼ������ */
//   CANOpen_Message CAN_Rx_m; /* CANOpen Message ����CAN Port(CANx) */

//   CAN_Rx_m.CANx = 1;

//   CO_D_TEST.CO_CAN1 = &ObjDict_CAN1_Data;
//   CO_D_TEST.CO_CAN1->canHandle = CAN1;

//   /* �����ж� */
//   CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);
//   printf("CAN_ITConfig\r\n");

//   /* ��CAN1 FIFO0�������ݴ���CAN1_Rx_m */
//   CAN_Receive(CAN1, CAN_FIFO0, &(CAN_Rx_m.m));
//   printf("CAN_Receive\r\n");

//   printf("Thread get a CAN packege\r\n");
//   RxMSG.cob_id = (uint16_t)(CAN_Rx_m.m.StdId);
//   RxMSG.rtr = CAN_Rx_m.m.RTR;
//   RxMSG.len = CAN_Rx_m.m.DLC;
//   for(i=0;i<RxMSG.len;i++)
//   {
//     RxMSG.data[i] = CAN_Rx_m.m.Data[i]; //Transfer data[0-7] from CAN_Rx_m to RxMSG
//   }

//   printf("CAN Message Receieved: %02x|%02x %02x \r\n", RxMSG.cob_id, RxMSG.data[0],RxMSG.data[1]);

//   printf("leaving the CAN_ITConfig\r\n");

//   /*Handle The Data Receive, �˴��Ͷ����ֵ���н���*/
//   printf("canDispatch\r\n");
//   //canDispatch(CO_D_TEST.CO_CAN1, &RxMSG); 
//   
//   if (RxMSG.cob_id == 0x206)
//   {
//      switch(RxMSG.data[0])
//      {
//        case  0x01:
//           /* Debug Message */
//           printf("Receieve a ARM-Linux msg : Up \r\n");
//           /* Control GPIO */
//           GPIO_SetBits(GPIOE, GPIO_Pin_11);
//           GPIO_ResetBits(GPIOE, GPIO_Pin_13);   
//           break;
//        case  0x02:
//           /* Debug Message */
//           printf("Receieve a ARM-Linux msg : Down \r\n");
//           /* Control GPIO */
//           GPIO_ResetBits(GPIOE, GPIO_Pin_11);
//           GPIO_SetBits(GPIOE, GPIO_Pin_13);
//           break;
//        case  0x03:
//           /* Debug Message */
//           printf("Receieve a ARM-Linux msg : Stop \r\n");
//           /* Control GPIO */
//           GPIO_SetBits(GPIOE, GPIO_Pin_11);
//           GPIO_SetBits(GPIOE, GPIO_Pin_13);
//           break;
//        default:
//           /* Debug Message */
//           printf("Unknown error msg : \r\n");
//      }
//   }
//   
//   
//   // if (1==canSend(CAN1,&RxMSG))
//   // {
//   //   printf("Send Succuss!\r\n" );
//   // }

//   //printf("leaving the CAN_ITConfig\r\n");

//   /* ��������ж�*/ 
//   CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
//   /* ʹ��CAN�ж�*/ 
//   CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);
}
/************************************************************************************/
//#endif  /* USE_CAN1 */


/**
  * @brief  This function handles CAN2 RX0 request.
  * @param  None
  * @retval None
  */
void CAN2_RX0_IRQHandler(void)
{
		CANOpen_Message CAN2_Rx_m;
	
	  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;     //�ж��л���������
	
		printf("ENTER CAN2 RX IRQHandler... \r\n");
	
	  taskENTER_CRITICAL();                                  //�����ж�
	
	  CAN_Receive(CAN2, CAN_FIFO0, &(CAN2_Rx_m.m));	    //��CAN2 FIFO0��������
	
	  CAN2_Rx_m.CANx = 2;
	
	  if(NULL != xQ_CAN_MSG)         // ����з������ݰ�
	  {
			xQueueSendFromISR(xQ_CAN_MSG, &CAN2_Rx_m, &xHigherPriorityTaskWoken);
	  }
		
	  taskEXIT_CRITICAL();
		
	  if( xHigherPriorityTaskWoken != pdFALSE )
	  {
	    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );           //ǿ���������л�
  	}  
	
}


void EXTI0_IRQHandler(void)
{
//     if(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_0))
// 	{
// 		Infared0_time_end=Infared0_time;
//     Infared0_time=0;		
// 		//GPIO_SetBits(GPIOA, GPIO_Pin_4);
// 		
// 		XXXXX++;
// 		
// 		//sprintf(message_ADC,"%d\r\n",ADC3ConvertedValue*5000/0xFFF);
// 		
// 		//USART6_Puts(message_ADC);
// 	}
//     EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
//     if(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1))	
// 	{
// 		Infared1_time_end=Infared1_time;
// 		Infared1_time=0;
// 		//GPIO_SetBits(GPIOA, GPIO_Pin_4);
// 	}
//     EXTI_ClearITPendingBit(EXTI_Line1);
}




/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
