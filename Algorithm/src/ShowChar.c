#include "ShowChar.h"
#include "lcd.h"
#include "ov7670.h"
#include "string.h" 


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

vu8 tim3_num = 0;                                                     //TIM3���Ӽ�ʱ

void Data_LCD_Display(void) {																					//������ʾ
	vu16 a = 0,b = 0;
	LCD_SetWindows(0,0,320,240);																				//������ʾ����  
	GPIO_WriteBit(LCD_RS_PORT, LCD_RS_PIN,1);														//��־������д��

	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==1);
	GPIO_WriteBit(FIFO_WRST_PORT, FIFO_WRST_PIN, 0);
	GPIO_WriteBit(FIFO_WRST_PORT, FIFO_WRST_PIN, 1);
	GPIO_WriteBit(FIFO_WR_PORT, FIFO_WR_PIN, 1);
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==0);
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==1);
	GPIO_WriteBit(FIFO_WR_PORT, FIFO_WR_PIN, 0);
	
	FIFO_Reset_Read_Addr(); 
 
	for (a = 0; a < 240; a++) {
		for(b = 0; b < 320; b++) {
			GPIOC->BRR = 1<<4;
			AA = GPIOA->IDR;						
			GPIOC->BSRR = 1<<4;
			
			GPIOC->BRR = 1<<4;
			BB = GPIOA->IDR&0x00ff;								
			GPIOC->BSRR = 1<<4;	
			
			color = (AA<<8)|BB;
			
			LCD_DATA_PORT->ODR = color;

			GPIOC->BRR = 1<<11;
			GPIOC->BSRR = 1<<11;
		}							
	}	 
}

void Show_Title(void) {																								 //��ʾ����
	LCD_ShowChar(35+8*0,10,'N',0);
	LCD_ShowChar(35+8*1,10,'u',0);
	LCD_ShowChar(35+8*2,10,'m',0);
	LCD_ShowChar(35+8*3,10,'b',0);
	LCD_ShowChar(35+8*4,10,'e',0);
	LCD_ShowChar(35+8*5,10,'r',0);
	
	LCD_ShowChar(35+8*9,10,'T',0);
	LCD_ShowChar(35+8*10,10,'i',0);
	LCD_ShowChar(35+8*11,10,'m',0);
	LCD_ShowChar(35+8*12,10,'e',0);

	
	LCD_ShowChar(35+8*17,10,'P',0);
	LCD_ShowChar(35+8*18,10,'r',0);
	LCD_ShowChar(35+8*19,10,'i',0);
	LCD_ShowChar(35+8*20,10,'c',0);
	LCD_ShowChar(35+8*21,10,'e',0);
}


void WordShow(vu8 num,vu16 x,vu16 y) {																 //��ʾ����16*16
	vu16 a = 0,b = 0,e = 0,num1 = 0;
	vu8 table1[32] = {0};
	if(num == 1) {
		for(a = 0; a< 32; a++) {
			table1[a]= table_yu[a];	
		}		
	}else if(num == 2) {
		for(a = 0; a < 32; a++) {
			table1[a] = table_min[a];	
		}		
	}else if(num == 3) {
		for(a = 0; a < 32; a++) {
			table1[a] = table_lu[a];	
		}		
	}else if(num == 4) {
		for(a = 0; a < 32; a++) {
			table1[a] = table_zhe[a];	
		}		
	}else if(num==5) {
		for(a = 0; a < 32; a++) {
			table1[a] = table_shan[a];	
		}		
	}else if(num == 6) {
		for(a = 0; a < 32; a++) {
			table1[a] = table_cuan[a];	
		}		
	}
	for(a = 0; a < 16; a++) {
		for(b = 0; b < 16; b++) {
			if(table1[b/8+a*2]&(1<<(7-b%8))) {
				num1=0xffff;
			} else {
				num1=0x0000;
			}
			LCD_DrawPoint(b+x,a+y,num1);                                         //����
		}				
	}	
}

void PictureToString(void) {                                              //ͼƬ->����table_picture   150�ֽ�   
	vu16 a = 0,b = 0,num1 = 0;
	
	for(a = 0; a < 150; a++) {                                              //����
		table_picture[a] = 0x00;	
	}	
	for(a = 0; a< 50; a++) {                                                //50��
		for(b = 0; b < 24; b++) {                                             //24��
			num1 = LCD_ReadPoint(b+296,a+191);
			if(num1 == 0xffff) {
				table_picture[b/8+a*3]|=(1<<(7-b%8));                             //(1<<(7-b%8))   ��"1" �任�ڵ��ֽ��е���Ӧλ���ϡ�  
			}
		}				
	}
}

void StringToPicture(void) {                                              //����->ͼƬ
	vu16 a = 0,b = 0,e = 0,num1 = 0;
	
	for(a = 0; a < 50; a++) {                                               //50��                              
		for(b = 0;b < 24; b++) {                                              //24��
			if(talble_0[b/8+a*3]&(1<<(7-b%8))) {
				num1=0xffff;
			} else {
				num1=0x0000;
			}
			LCD_DrawPoint(b+296,a+191,num1);                                    //����
		}				
	}	
}

void Show_Card(vu8 i) {                                                   //��ʾ�ڼ��鳵��
	vu16 t0=0;
	//��ʾ����
	if(table_card[i][0] != 0) {
		WordShow(table_card[i][0],9,i*16+50);//
	}
	
	if(table_card[i][1] < 10) {
		LCD_ShowNum(25,i*16+50,table_char[table_card[i][1]],1);
	} else {
		LCD_ShowChar(25,i*16+50,table_char[table_card[i][1]],0);
	}
	
	LCD_ShowChar(33,i*16+50,'.',0);													                	//��
	
	if(table_card[i][2] < 10) {
		LCD_ShowNum(41,i*16+50,table_char[table_card[i][2]],1);
	} else {
		LCD_ShowChar(41,i*16+50,table_char[table_card[i][2]],0);
	}
	
	if(table_card[i][3] < 10) {
		LCD_ShowNum(49,i*16+50,table_char[table_card[i][3]],1);
	} else {
		LCD_ShowChar(49,i*16+50,table_char[table_card[i][3]],0);
	}
	
	if(table_card[i][4] < 10) {
		LCD_ShowNum(57,i*16+50,table_char[table_card[i][4]],1);
	} else {
		LCD_ShowChar(57,i*16+50,table_char[table_card[i][4]],0);
	}
	
	if(table_card[i][5] < 10) {
		LCD_ShowNum(65,i*16+50,table_char[table_card[i][5]],1);
	} else {
		LCD_ShowChar(65,i*16+50,table_char[table_card[i][5]],0);
	}
	
	if(table_card[i][6] < 10) {
		LCD_ShowNum(73,i*16+50,table_char[table_card[i][6]],1);
	} else {
		LCD_ShowChar(73,i*16+50,table_char[table_card[i][6]],0);
	}
	
	t0 = table_card[i][7];
	LCD_ShowNum(100,i*16+50,t0,6);                                            //��ʾʱ��

	if(t0 < 60) {
		LCD_ShowNumPoint(168,i*16+50,t0*8);
	} else {
		LCD_ShowNumPoint(168,i*16+50,t0/60*500+t0%60*8);
	}
	
}

//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void) { 		    		  			    
	if(TIM3->SR&0X0001) {                                                    //����ж�
		if(tim3_num == 60) {
			if(table_card[0][0] != 0) {                                          //��1���ʱ
				table_card[0][7]++;
			}	
			
			if(table_card[1][0] != 0) {                                          //��2���ʱ
				table_card[1][7]++;
			}
			
			if(table_card[2][0] != 0) {                                          //��3���ʱ
				table_card[2][7]++;
			}	
			
			if(table_card[3][0] != 0) {                                          //��4���ʱ
				table_card[3][7]++;
			}	
			
			if(table_card[4][0] != 0) {                                          //��5���ʱ
				table_card[4][7]++;
			}
			tim3_num = 0;
		}		
	}			
	tim3_num++;
	TIM3->SR&=~(1<<0);                                                        //����жϱ�־λ 	    
}

void TIM3_Configuration(void) {
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* ---------------------------------------------------------------
	TIM3CLK ��PCLK1=36MHz
	TIM3CLK = 36 MHz, Prescaler = 7200, TIM3 counter clock = 5K,���ı�һ��Ϊ5K,���ھ�Ϊ10K
	--------------------------------------------------------------- */
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 2000;                                     //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������10000Ϊ1000ms
	TIM_TimeBaseStructure.TIM_Prescaler = (12800-1);                             //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                 //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Enables the Update event for TIM3 */
	//TIM_UpdateDisableConfig(TIM3,ENABLE); 	//ʹ�� TIM3 �����¼� 
	
	/* TIM IT enable */
	TIM_ITConfig(               //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3,                     //TIM3
		TIM_IT_Update  |          //TIM �ж�Դ
		TIM_IT_Trigger,           //TIM �����ж�Դ 
		ENABLE                    //ʹ��
		);
	
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);    //ʹ��TIMx����
}






