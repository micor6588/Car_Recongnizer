#include "value.h"
#include "stm32f10x.h"

vu8 cur_status = 0;
vu8 LED_flag = 0;

vu16 AA = 0,BB = 0;
vu16 color=0;
vu16 color_save=0;//����һ�����ص�ֵ
vu8 R=0,G=0,B=0;//��ɫ����
vu8 TableChangePoint_240[240];//�����240��
vu8 Max_ChangePoint_240=0,Min_ChangePoint_240=0,Max_bChangePoint=0,Min_bChangePoint=0;//���������ʼ��ĩ����,��������ʼ��ĩ����
vu8 a_Continue=0,b_Continue=0;//��¼�ݡ�����ͻ����������
vu8 flag_aMax=0;//ĩֵ���±�־
vu8 Max_aChangePoint_reset=0,Min_aChangePoint_reset=0;//�������������
vu16 Length_card=0,Width_card=0;//���Ƶĳ��Ϳ�
vu8 Max_aChangePoint_reset_1=0,Min_aChangePoint_reset_1=0;//�����ϴε�����
vu8 flag_MaxMinCompare=0;//Max_aChangePoint_reset_1��Max_aChangePoint_reset�ı�־
vu8 TableChangePoint_320[320];//���������320��
float V=0.00,S=0.00,H=0.00;//����HSVֵ
vu16 Min_blue=0;
vu16 Max_blue=0;//���峵����ɫ����ĺ������ֵ����Сֵ

//�˸��ַ��߽�
vu16 character_boundary_right_1 = 0,character_boundary_left_1 = 0;
vu16 character_boundary_right_2 = 0,character_boundary_left_2 = 0;
vu16 character_boundary_right_3 = 0,character_boundary_left_3 = 0;
vu16 character_boundary_right_4 = 0,character_boundary_left_4 = 0;
vu16 character_boundary_right_5 = 0,character_boundary_left_5 = 0;
vu16 character_boundary_right_6 = 0,character_boundary_left_6 = 0;
vu16 character_boundary_right_7 = 0,character_boundary_left_7 = 0;
vu16 character_boundary_right_8 = 0,character_boundary_left_8 = 0;

vu8 Red_Vlaue = 0, Green_Value = 0 ,Blue_Value = 0;//��ֵ

vu8 table_picture[150];//���屣��ͼƬ������
vu8 table_char[36]={0,1,2,3,4,5,6,7,8,9,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',};
	
vu8 table_char_char[36]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',};
vu8 table_card[5][8]={	//����5�����ƵĶ�ά����
{0,0,0,0,0,0,0,0},		//���һλ����ʱ��
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
};


vu8 table_cardMeasure[7];//�����ĳ��ƽ��

