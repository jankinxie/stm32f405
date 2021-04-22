#include "usart2_lcd.h"

uint8_t show_Auto_Data_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x00,0x00,0x00};
uint8_t show_Auto_Data_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x00,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Connet_Data_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x01,0x00,0x00};
uint8_t show_Connet_Data_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x01,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Run_Data_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x02,0x00,0x00};
uint8_t show_Run_Data_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x02,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_One_Run_Data_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x08,0x00,0x00};
uint8_t show_One_Run_Data_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x08,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Auto_One_Run_Data_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x09,0x00,0x00};
uint8_t show_Auto_One_Run_Data_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x09,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Auto_JOG_1_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x10,0x00,0x00};
uint8_t show_Auto_JOG_1_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x10,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_JOG_2_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x11,0x00,0x00};
uint8_t show_JOG_2_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x11,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Pump_ON_OFF_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x12,0x00,0x00};
uint8_t show_Pump_ON_OFF_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x12,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Switch_ON_OFF_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x13,0x00,0x00};
uint8_t show_Switch_ON_OFF_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x13,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Ready_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x14,0x00,0x00};
uint8_t show_Ready_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x14,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Bussy_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x15,0x00,0x00};
uint8_t show_Bussy_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x15,0x00,0x01};  //控制自动手动图标切换命令

uint8_t show_Homing_0[8] = {0xA5,0x5A,0x05,0x82,0x01,0x04,0x00,0x00};
uint8_t show_Homing_1[8] = {0xA5,0x5A,0x05,0x82,0x01,0x04,0x00,0x01};  //控制自动手动图标切换命令




void Hand_Lcd_Data(uint8_t *USART2_RxBuff,uint8_t USART2_RxLength){
	uint16_t tempAddr = 0;
	uint8_t last_Value_Auto= 0;
	uint8_t last_Value_Connet = 0;
	uint8_t last_Value_Run = 0;
	uint8_t last_Value_One_Run = 0;
	uint8_t last_Value_Auto_One_Run = 0;
	
	uint8_t last_Value_JOG_1 = 0;
	uint8_t last_Value_JOG_2 = 0;
	uint8_t last_Value_Pump_ON_OFF = 0;
	uint8_t last_Value_Switch_ON_OFF = 0;
	uint8_t last_Value_Ready = 0;
	uint8_t last_Value_Bussy = 0;
	uint8_t last_Value_Homing = 0;

  //串口2数据解析
  if(USART2_RxBuff[0]==0xA5 && (USART2_RxBuff[1]==0X5A))
  {
    printf("Hello world\r\n");
    tempAddr = (USART2_RxBuff[4] << 8) + USART2_RxBuff[5];
    switch(tempAddr)
    {
      case 0x0701:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Auto = !last_Value_Auto;
          if(last_Value_Auto)
          {
//            HAL_UART_Transmit(&huart2,show_Auto_Data_0, 8,200);
            BSP_USART2_SendData(show_Auto_Data_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Auto_Data_1, 8,200);
            BSP_USART2_SendData(show_Auto_Data_1,USART2_SEND_COMMOND_LEN);
          }
        }
        break;
        
      case 0x0702:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Connet = !last_Value_Connet;
          if(last_Value_Connet)
          {
//            HAL_UART_Transmit(&huart2,show_Connet_Data_0, 8,200);
            BSP_USART2_SendData(show_Connet_Data_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Connet_Data_1, USART2_SEND_COMMOND_LEN,200);
            BSP_USART2_SendData(show_Connet_Data_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
        
      case 0x0703:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Run = !last_Value_Run;
          if(last_Value_Run)
          {
//            HAL_UART_Transmit(&huart2,show_Run_Data_0, 8,200);
            BSP_USART2_SendData(show_Run_Data_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Run_Data_1, 8,200);
             BSP_USART2_SendData(show_Run_Data_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0709:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_One_Run = !last_Value_One_Run;
          if(last_Value_One_Run)
          {
//            HAL_UART_Transmit(&huart2,show_One_Run_Data_0, 8,200);
             BSP_USART2_SendData(show_One_Run_Data_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_One_Run_Data_1, 8,200);
            BSP_USART2_SendData(show_One_Run_Data_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0710:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Auto_One_Run = !last_Value_Auto_One_Run;
          if(last_Value_Auto_One_Run)
          {
//            HAL_UART_Transmit(&huart2,show_Auto_One_Run_Data_0, 8,200);
            BSP_USART2_SendData(show_Auto_One_Run_Data_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Auto_One_Run_Data_1, 8,200);
            BSP_USART2_SendData(show_Auto_One_Run_Data_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0711:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_JOG_1 = !last_Value_JOG_1;
          if(last_Value_JOG_1)
          {
//            HAL_UART_Transmit(&huart2,show_Auto_JOG_1_0, 8,200);
            BSP_USART2_SendData(show_Auto_JOG_1_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Auto_JOG_1_1, 8,200);
            BSP_USART2_SendData(show_Auto_JOG_1_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0712:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_JOG_2 = !last_Value_JOG_2;
          if(last_Value_JOG_2)
          {
//            HAL_UART_Transmit(&huart2,show_JOG_2_0, 8,200);
             BSP_USART2_SendData(show_JOG_2_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_JOG_2_1, 8,200);
            BSP_USART2_SendData(show_JOG_2_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0713:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Pump_ON_OFF = !last_Value_Pump_ON_OFF;
          if(last_Value_Pump_ON_OFF)
          {
//            HAL_UART_Transmit(&huart2,show_Pump_ON_OFF_0, 8,200);
            BSP_USART2_SendData(show_Pump_ON_OFF_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Pump_ON_OFF_1, 8,200);
            BSP_USART2_SendData(show_Pump_ON_OFF_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0714:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Switch_ON_OFF = !last_Value_Switch_ON_OFF;
          if(last_Value_Switch_ON_OFF)
          {
//            HAL_UART_Transmit(&huart2,show_Switch_ON_OFF_0, 8,200);
            BSP_USART2_SendData(show_Switch_ON_OFF_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Switch_ON_OFF_1, 8,200);
            BSP_USART2_SendData(show_Switch_ON_OFF_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0715:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Ready = !last_Value_Ready;
          if(last_Value_Ready)
          {
//            HAL_UART_Transmit(&huart2,show_Ready_0, 8,200);
            BSP_USART2_SendData(show_Ready_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Ready_1, 8,200);
            BSP_USART2_SendData(show_Ready_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0716:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Bussy = !last_Value_Bussy;
          if(last_Value_Bussy)
          {
//            HAL_UART_Transmit(&huart2,show_Bussy_0, 8,200);
            BSP_USART2_SendData(show_Bussy_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Bussy_1, 8,200);
            BSP_USART2_SendData(show_Bussy_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      case 0x0718:
        if(USART2_RxBuff[8]==0x01)
        {
          last_Value_Homing = !last_Value_Homing;
          if(last_Value_Homing)
          {
//            HAL_UART_Transmit(&huart2,show_Homing_0, 8,200);
            BSP_USART2_SendData(show_Homing_0,USART2_SEND_COMMOND_LEN);
          }
          else
          {
//            HAL_UART_Transmit(&huart2,show_Homing_1, 8,200);
            BSP_USART2_SendData(show_Homing_1,USART2_SEND_COMMOND_LEN);
          }
          
        }
        break;
      default:
        printf("Commend Error...\r\n");
        break;
        
    }
  }

}
