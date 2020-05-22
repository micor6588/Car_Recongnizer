#ifndef __VALUE_H
#define __VALUE_H

#include "stm32f10x.h"

extern vu8 cur_status;
extern vu8 LED_flag;

extern vu16 AA,BB;
extern vu16 color;
extern vu16 color_save;//����һ�����ص�ֵ
extern vu8 R,G,B;//��ɫ����
extern vu8 TableChangePoint_240[240];//�����240��
extern vu8 Max_ChangePoint_240,Min_ChangePoint_240,Max_bChangePoint,Min_bChangePoint;//���������ʼ��ĩ����,��������ʼ��ĩ����
extern vu8 a_Continue,b_Continue;//��¼�ݡ�����ͻ����������
extern vu8 flag_aMax;//ĩֵ���±�־
extern vu8 Max_aChangePoint_reset,Min_aChangePoint_reset;//�������������
extern vu16 Length_card,Width_card;//���Ƶĳ��Ϳ�
extern vu8 Max_aChangePoint_reset_1,Min_aChangePoint_reset_1;//�����ϴε�����
extern vu8 flag_MaxMinCompare;//Max_aChangePoint_reset_1��Max_aChangePoint_reset�ı�־
extern vu8 TableChangePoint_320[320];//���������320��
extern float V,S,H;//����HSVֵ
extern vu16 Min_blue;
extern vu16 Max_blue;//���峵����ɫ����ĺ������ֵ����Сֵ
//extern vu16 k1,kk1,k2,kk2,k3,kk3,k4,kk4,k5,kk5,k6,kk6,k7,kk7,k8,kk8;//�˸��ַ��߽�
extern vu16 character_boundary_right_1,character_boundary_left_1;
extern vu16 character_boundary_right_2,character_boundary_left_2;
extern vu16 character_boundary_right_3,character_boundary_left_3;
extern vu16 character_boundary_right_4,character_boundary_left_4;
extern vu16 character_boundary_right_5,character_boundary_left_5;
extern vu16 character_boundary_right_6,character_boundary_left_6;
extern vu16 character_boundary_right_7,character_boundary_left_7;
extern vu16 character_boundary_right_8,character_boundary_left_8;

extern vu8 Red_Vlaue, Green_Value ,Blue_Value;//��ֵ

extern vu8 table_picture[150];//���屣��ͼƬ������
extern vu8 table_char[36];
	
extern vu8 table_char_char[36];
extern vu8 table_card[5][8];//����5�����ƵĶ�ά����

extern vu8 table_cardMeasure[7];//�����ĳ��ƽ��


#endif
