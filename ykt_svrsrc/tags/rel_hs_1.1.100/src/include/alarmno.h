/*
���徯��ź�
���ߣ�����
ʱ�䣺2004��9��28��
*/
#ifndef  __ALARMNO_H_
#define  __ALARMNO_H_

/*
�����Ŀ���
1.		�豸���	
2.		������ˮ	
3.		����һ����	
4.		ϵͳ״̬	
5.		������������δ���	
*/
#define MEXCEPTION_DEVICE           		1 
#define MEXCEPTION_TRADE           		2 
#define MEXCEPTION_CARDDB           		3
#define MEXCEPTION_SYSSTATE          		4
#define MEXCEPTION_ALARMOP           		5



/*                                             
��̨��������ˮ��صľ���Ŷ���                   
                                               
����� 100301 ������ʱ�䲻������������ʱ��       
����� 100302 ����ʱ���ڵĿ������������ڵ���ϵͳ?
����� 100303 һ�ο�������ȴ���ϵͳĬ�Ͽ��������?
����� 100304 ���Ƿ�������                       
*/                                             
#define ALA_CARDOPERATE_TIME            			100301 
#define ALA_CARDOPERATE_COUNT	 			100302 
#define ALA_CARDOPERATE_FEE					100303 
#define ALA_CARDOPERATE_ILLEGALCARD			100304 
#define ALA_CARDOPERATE_FAIL					100305 

/*
��̨��ؿ��ⲻƽ�쳣�ľ���Ŷ���

����� 100401 ��ǰ�˻����������ڵ�ǰ�����˻����
����� 100402 ��ǰ�˻��������С�ڵ�ǰ�����˻����
*/
#define ALA_BALANCE_APC         100401        
#define ALA_BALANCE_CPA 		100402

/*
��̨ϵͳ״̬��صľ���Ŷ���

����� 100501 ��ʾ���㳬ʱ
*/
#define ALA_SYSSTATE_OTW 100701


#endif                                                            

