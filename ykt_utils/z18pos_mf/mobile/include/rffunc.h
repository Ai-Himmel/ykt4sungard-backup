    #define _RFSTD    0x4E
    #define _RFEven   0x45
    #define _RFOdd    0x4F
    
    #ifndef __RFFUNC
                      
    extern  void  TurnOffRF(void);
    /*      
      函数说明： 关闭RF
      参数：     无
      返回值：   无
    */
    
    extern  int   TurnOnRF(void);
    /*      
      函数说明： 打开RF
      参数：     无
      返回值：   0    打开RF成功
                 非0  打开RF失败
    */
    
    extern  void  GetRFParm(unsigned int *BaudRate,unsigned char *RFOEmode,
                            unsigned char *RFChannel);
    /*      
      函数说明： 获取RF参数
      参数：     BaudRate
                 RFOEmode
                 RFChannel
      返回值：   
                 BaudRate      波特率
                 9600          9600bps
                 4800          4800bps
                 2400          2400bps
                 1200          1200bps
                               
                 RFOEmode      检验形式
                 _RFSTD        无校验
                 _RFEven       偶校验
                 _RFOdd        奇校验
                 
                 RFChannel     信道
                 1             信道1
                 2             信道2
                 3	       信道3 		
                 4	       信道4
                 5             信道5
                 6             信道6
                 7             信道7                
    */                        
    
    extern  int   SetRFParm(unsigned int BaudRate,unsigned char RFOEmode,
                            unsigned char RFChannel);      
    /*      
      函数说明： 设置RF参数
      参数：     BaudRate
                 RFOEmode
                 RFChannel
   
                 BaudRate      波特率
                 9600          9600bps
                 4800          4800bps
                 2400          2400bps
                 1200          1200bps
                               
                 RFOEmode      检验形式
                 _RFSTD        无校验
                 _RFEven       偶校验
                 _RFOdd        奇校验
                 
                 RFChannel     信道
                 1             信道1
                 2             信道2
                 3	       信道3 		
                 4	       信道4
                 5             信道5
                 6             信道6
                 7             信道7 
                 
      返回值：   0    设置成功
                 非0  设置失败           
                                
    */                                   
    #endif                                          