/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "usart.h"
#include "usart2_lcd.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE BEGIN Variables */
 
#define MAIL_SIZE        (uint32_t) 4
 
typedef struct { 
   uint16_t DataLength;
	 uint8_t *DataReceive;
} Amail_TypeDef;
 
osMailQId USART2_MailId;  //创建串口2邮箱信息
osMailQId USART3_MailId;


 
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId USART3_DataProcHandle;
osThreadId USART2_DataProcHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void USART3_DataProcessTask(void const * argument);
void USART2_DataProcessTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  
  //初始化串口2消息邮箱的ID号
  osMailQDef(Usart2MailId, MAIL_SIZE, Amail_TypeDef); /* Define mail queue */
  USART2_MailId = osMailCreate(osMailQ(Usart2MailId), NULL); /* create mail queue */

  osMailQDef(Usart3MailId, MAIL_SIZE, Amail_TypeDef); /* Define mail queue */
  USART3_MailId = osMailCreate(osMailQ(Usart3MailId), NULL); /* create mail queue */

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of USART3_DataProc */
  osThreadDef(USART3_DataProc, USART3_DataProcessTask, osPriorityIdle, 0, 128);
  USART3_DataProcHandle = osThreadCreate(osThread(USART3_DataProc), NULL);

  /* definition and creation of USART2_DataProc */
  osThreadDef(USART2_DataProc, USART2_DataProcessTask, osPriorityIdle, 0, 128);
  USART2_DataProcHandle = osThreadCreate(osThread(USART2_DataProc), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_USART3_DataProcessTask */
/**
* @brief Function implementing the USART3_DataProc thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_USART3_DataProcessTask */
void USART3_DataProcessTask(void const * argument)
{
  /* USER CODE BEGIN USART3_DataProcessTask */
  
  /* Infinite loop */
  osEvent USART3_Event;
  Amail_TypeDef *USART3_RxMail;
  
  static uint8_t *USART3_RxBuff;
  static uint8_t USART3_RxLength = 0;
  
  USART3_RxBuff = pvPortMalloc(256);
  BSP_USART3_Init();
  for(;;)
  {
    USART3_Event = osMailGet(USART3_MailId, 0);   //等待邮箱发送数据
		if(USART3_Event.status == osEventMail)
		{
		  USART3_RxMail = USART3_Event.value.p;     //获取邮箱中的数据        
			
			USART3_RxLength = USART3_RxMail->DataLength;
			USART3_RxBuff = USART3_RxMail->DataReceive;
			osMailFree(USART3_MailId, USART3_RxMail);  //释放在串口空闲中断中申请的邮箱内存
			
      printf("Usart3 Receive Data len：%d\r\n",USART3_RxLength);
      BSP_USART3_SendData(USART3_RxBuff,USART3_RxLength);
			for(uint8_t i=0;i<USART3_RxLength;i++)
			{
				printf("%x\r\n",USART3_RxBuff[i]);
			}
		}
    osDelay(1);
  }
  /* USER CODE END USART3_DataProcessTask */
}

/* USER CODE BEGIN Header_USART2_DataProcessTask */
/**
* @brief Function implementing the USART2_DataProc thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_USART2_DataProcessTask */
void USART2_DataProcessTask(void const * argument)
{

  /* USER CODE BEGIN USART2_DataProcessTask */
  /* Infinite loop */
  osEvent USART2_Event;
	Amail_TypeDef *USART2_RxMail;
	
	static uint8_t *USART2_RxBuff;
	static uint8_t USART2_RxLength = 0;
	
	USART2_RxBuff = pvPortMalloc(256);
  BSP_USART2_Init();
  for(;;)
  {
    USART2_Event = osMailGet(USART2_MailId, 0);   //等待邮箱发送数据
		if(USART2_Event.status == osEventMail)
		{
		  USART2_RxMail = USART2_Event.value.p;     //获取邮箱中的数据        
			
			USART2_RxLength = USART2_RxMail->DataLength;
			USART2_RxBuff = USART2_RxMail->DataReceive;
			osMailFree(USART2_MailId, USART2_RxMail);  //释放在串口空闲中断中申请的邮箱内存
			
      printf("Usart2 Receive Data len：%d\r\n",USART2_RxLength);
      BSP_USART2_SendData(USART2_RxBuff,USART2_RxLength);
      Hand_Lcd_Data(USART2_RxBuff,USART2_RxLength);
			for(uint8_t i=0;i<USART2_RxLength;i++)
			{
				printf("%x\r\n",USART2_RxBuff[i]);
			}
     }
     osDelay(1);
  }
  /* USER CODE END USART2_DataProcessTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
