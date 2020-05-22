/* ��ֹ�ݹ������ͷ�ļ� ------------------------------------------------------*/
#ifndef __LCD_H
#define __LCD_H
	 
#include "stm32f10x.h"
	 

void LCD_Init(void);
u16 LCD_ReadPoint(u16 x,u16 y);
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
void LCD_Fill(unsigned short color);
void LCD_DrawPoint(u16 x,u16 y,u16 color);//��ָ��λ��д��һ�����ص�����
void LCD_ShowChar(u16 x,u16 y, u8 num,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);
void LCD_ShowNumPoint(u16 x,u16 y,u16 num);//��ʾ4λ��+2λС����
#ifdef __cplusplus
}
#endif


#endif 

