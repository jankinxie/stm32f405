#ifndef __USART2_LCD_H_
#define __USART2_LCD_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "usart.h"

#define USART2_SEND_COMMOND_LEN   8    //����2���ƴ���ָ���

void Hand_Lcd_Data(uint8_t *USART2_RxBuff,uint8_t USART2_RxLength);

#endif

