    #define _RFSTD    0x4E
    #define _RFEven   0x45
    #define _RFOdd    0x4F
    
    #ifndef __RFFUNC
                      
    extern  void  TurnOffRF(void);
    /*      
      ����˵���� �ر�RF
      ������     ��
      ����ֵ��   ��
    */
    
    extern  int   TurnOnRF(void);
    /*      
      ����˵���� ��RF
      ������     ��
      ����ֵ��   0    ��RF�ɹ�
                 ��0  ��RFʧ��
    */
    
    extern  void  GetRFParm(unsigned int *BaudRate,unsigned char *RFOEmode,
                            unsigned char *RFChannel);
    /*      
      ����˵���� ��ȡRF����
      ������     BaudRate
                 RFOEmode
                 RFChannel
      ����ֵ��   
                 BaudRate      ������
                 9600          9600bps
                 4800          4800bps
                 2400          2400bps
                 1200          1200bps
                               
                 RFOEmode      ������ʽ
                 _RFSTD        ��У��
                 _RFEven       żУ��
                 _RFOdd        ��У��
                 
                 RFChannel     �ŵ�
                 1             �ŵ�1
                 2             �ŵ�2
                 3	       �ŵ�3 		
                 4	       �ŵ�4
                 5             �ŵ�5
                 6             �ŵ�6
                 7             �ŵ�7                
    */                        
    
    extern  int   SetRFParm(unsigned int BaudRate,unsigned char RFOEmode,
                            unsigned char RFChannel);      
    /*      
      ����˵���� ����RF����
      ������     BaudRate
                 RFOEmode
                 RFChannel
   
                 BaudRate      ������
                 9600          9600bps
                 4800          4800bps
                 2400          2400bps
                 1200          1200bps
                               
                 RFOEmode      ������ʽ
                 _RFSTD        ��У��
                 _RFEven       żУ��
                 _RFOdd        ��У��
                 
                 RFChannel     �ŵ�
                 1             �ŵ�1
                 2             �ŵ�2
                 3	       �ŵ�3 		
                 4	       �ŵ�4
                 5             �ŵ�5
                 6             �ŵ�6
                 7             �ŵ�7 
                 
      ����ֵ��   0    ���óɹ�
                 ��0  ����ʧ��           
                                
    */                                   
    #endif                                          