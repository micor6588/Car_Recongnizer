#include "stm32f10x.h"
#include "stm32f10x_it.h" 

#include "key.h"
#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "ov7670.h"
#include "rcc.h"
#include "ShowChar.h"
#include "discern.h"

extern vu8 Red_Vlaue, Green_Value ,Blue_Value;//��ֵ


int main(void)
{  
	unsigned int scan_time = 0;
 
	STM32_Clock_Init(16);                                    //��ʼ��ʱ��

	LCD_Init();	
	Key_Init();	                                             //��ʼ�� KEY1 PA8
	OV7670_GPIO_Init();                                      //OV7670���ų�ʼ�������ڴ��ڳ�ʼ��ǰ��
	//USART1_init();                                         //��ʼ������	

	TIM3_Configuration();                                    //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
	LCD_Fill(0x6666);		
	while(!Sensor_Init());
	
	LCD_Fill(0xF800);
	delayms(100);

	scan_time = 2;
	
  //��ֵ����ֵ	
	Red_Vlaue = 24;
	Green_Value = 53;
	Blue_Value = 24;

	while(1)
	{
		if(scan_time <= 1) {
			CameraDiscern();                                    //����ʶ��
		}
		if(scan_time > 1) {
			CameraScan();                                       //����ͷɨ�����
			LCD_ShowNum(30,220,21 - scan_time, 2); 
			while(GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN)==0) //��������
			{
				LCD_Fill(0x00);                                   //����
				Show_Title();                                     //��ʾ����
				Show_Card(0);                                     //��ʾ�ڼ��鳵��
				Show_Card(1);
				Show_Card(2);
				Show_Card(3);
				Show_Card(4);
				delay_ms(5000);
			}
		}
		if(scan_time == 20) {
			 scan_time = 0;
		}
		scan_time++;
	} 
}


