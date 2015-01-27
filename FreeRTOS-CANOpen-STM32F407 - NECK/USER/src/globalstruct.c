/**
  ******************************************************************************
  * @file    globalsturct.c
  * @author  Jim
  * @version V1.0
  * @date    01-Sep-2014
  * @brief   This is the global struct program, use it with the H file.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 CSST Robot Research Center</center></h2>
  *
  ******************************************************************************
  */

#include "globalstruct.h"

char gNetBuffer[NET_BUFFER_MAX_NUMBER]="send up the data\r\n";
int gNetDataSize=15;

/*��������     ���Ĵ�����      �ڱۿ���     �����ۿ���    ��е�ֿ���*/
xQueueHandle xQ_DRIVE_COMM, xQ_FLIP_COMM, xQ_ARM_COMM,xQ_HAND_COMM;

/*command ����״̬����.h�� define���Ӧ*/
const char* gNetCommandResStr[]=
{
	"Invalid",
	"Reached",
	"Canceled",
	"Pushed",
	"Ok",
	"Failed",
	"ReadOnly",
	"OverRun"
};

NET_CLIENT_USER_INFO_STRUCT* NetUserSearchBySocket(struct netconn * sock)
{
	int i;
	for(i=0;i<MAX_CLIENT_NUM;i++)
	{
		if(sock == user_info[i].conn)
			return (&user_info[i]);
	}
	return NULL;
}
