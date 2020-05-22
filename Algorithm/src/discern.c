#include "discern.h"
#include "delay.h"
#include "lcd.h"
#include "ov7670.h" 

#include "algorithm.h"


void CameraScan(void) {                                               //����ͷɨ�����
	vu16 a = 0,b = 0;
	
	for(a = 0; a < 240; a++) {                                          //����������������������
		TableChangePoint_240[a] = 0;
	}
	Min_blue = 320;                                                     //��ʼ����¼��ɫ���������ֵ
	Max_blue = 0;
	
	LCD_SetWindows(0,0,320,240);                                        //������ʾ����
	GPIO_WriteBit(LCD_RS_PORT, LCD_RS_PIN,1);                           //��־������д��

	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==1);
	GPIO_WriteBit(FIFO_WRST_PORT, FIFO_WRST_PIN, 0);
	GPIO_WriteBit(FIFO_WRST_PORT, FIFO_WRST_PIN, 1);
	GPIO_WriteBit(FIFO_WR_PORT, FIFO_WR_PIN, 1);
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==0);
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==1);
	GPIO_WriteBit(FIFO_WR_PORT, FIFO_WR_PIN, 0);
	
	FIFO_Reset_Read_Addr(); 
 
	
	for(a = 0; a < 240; a++) {
		for(b = 0; b < 320; b++) {
			GPIOC->BRR = 1<<4;
			AA = GPIOA->IDR;						
			GPIOC->BSRR = 1<<4;
			
			GPIOC->BRR = 1<<4;
			BB = GPIOA->IDR&0x00ff;								
			GPIOC->BSRR = 1<<4;	
			
			color = (AA<<8)| BB;

			R = color>>11;
			G = (color>>5)&0x3f;
			B = color&0x1f;
			
			if((R > Red_Vlaue) && (G >= Green_Value) && (B >= Blue_Value)) {                             //��ֵ��,����ֵ��25.55.25���Ϻ�����ֵ��21,47,21��
				color = 0xffff;
			} else {
				color = 0x0000;
			}
			
			if(color != color_save) {                                              //�����
				TableChangePoint_240[a]++;		                                       //������������+1
			}
			color_save = color;                                                    //��������ֵ������һ���жϺͱȽ�
			
			color = (AA<<8) | BB;                                                  //��ԭɫ��
					
			LCD_DATA_PORT->ODR = color;
			GPIOC->BRR = 1<<11;
			GPIOC->BSRR = 1<<11;
		}
	}
	ChangePoint_Show_240();                                                     //240�����������ʾ
	ChangePoint_Analysis_240();	                                                //��������  ��ó��Ƹ߶�
}

void CameraDiscern(void) {                                                    //����ͷɨ��
	vu8 i = 0;

	CameraScan();
	//����flag_MaxMinCompare��Min_ChangePoint_240��Max_ChangePoint_240
	if(flag_MaxMinCompare == 1) {  
		//�����ɸѡ�ɹ�  ���߶Ⱥ���
//			BEEP_ON;        
//			delayms(500);
//			BEEP_OFF;
		
		//������ʾ�������ұ߽�
		 ChangePoint_Analysis_Blue();                                             //320��ɫ�������,���ö�ȡ���أ��ý��Min_blue,Max_blue  �����������ұ߽�
		if(Min_blue > Max_blue) {
			flag_MaxMinCompare=0;                                                   //���к������ж�1
		}
			
		if((Min_blue > 290) || (Max_blue > 290)) {
			flag_MaxMinCompare = 0;                                                  //���к������ж�2
		}	
	}
	if(flag_MaxMinCompare == 1) {                                                //�����ɸѡ�ɹ�  ���ұ߽��ȡ�ɹ� ���Һ���
		ChangePoint_Analysis_320();                                                //��ɫ�����У�320��������,��ã�TableChangePoint_320[b]��� ���ұ߽��ڶ�ֵ��
		ChangePoint_Show_320();                                                    //320�����������ʾ
		i = SegmentationChar(); 
		
		if(i == 8) {                                                               //�ַ��ָ�,���طָ���ַ������������жϺϷ���
			CharacterRecognition();                                                  //�ַ�ʶ��	
		} else {
			LCD_Fill(0x6666);                                                        //��������ʾMeasure Faill
			LCD_ShowChar(8*1,200,'M',0);
			LCD_ShowChar(8*2,200,'e',0);
			LCD_ShowChar(8*3,200,'a',0);
			LCD_ShowChar(8*4,200,'s',0);
			LCD_ShowChar(8*5,200,'u',0);
			LCD_ShowChar(8*6,200,'r',0);
			LCD_ShowChar(8*7,200,'e',0);
			
			LCD_ShowChar(8*9,200,'F',0);
			LCD_ShowChar(8*10,200,'a',0);
			LCD_ShowChar(8*11,200,'i',0);
			LCD_ShowChar(8*12,200,'l',0);
			LCD_ShowChar(8*13,200,'l',0);

			delay_ms(800);
		}
	}
}

