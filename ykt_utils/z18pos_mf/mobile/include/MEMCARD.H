 /*********************************************
 **	    HT Mememory Card Control Functions   **
 **		 Heading File                        **
 *********************************************/
   #define _syn_3vMemCard  0x00
   #define _syn_5vMemCard  0x01

   #define _transbyte_positive  0x00
   #define _transbyte_inverse   0x01

   #define _NO_ERROR       0x00
   #define _UNKNOWN_ERROR  0x01
   #define _UNINST_ERROR   0x02
   #define _TYPESET_ERROR  0x03
   #define _POWER_FAIL     0x04
   #define _NO_INIT        0x05

   #ifndef __HTMEMCARD

   extern int MemCard_Init(unsigned char MemCardType);
   /* 功能：IC卡初始化设置。
      参数:   MemCardType  卡类型
              _syn_3vMemCard  3V卡
              _syn_5vMemCard  5V卡
      返回值:
              _NO_ERROR
              _TYPESET_ERROR
   */

   extern void MemCard_Exit(void);
   /* 功能：退出IC卡控制过程模块。
      参数:    无
      返回值:  无
      注意：   退出存储IC卡控制子过程应调用此函数，系统将完成某些重要
               的退出处理工作。
   */

   extern int MemCard_Read(char _far *RDaddr,unsigned char RDBytes,unsigned char ByteInv);
   /* 功能： IC卡读操作。
      参数:   RDaddr           读数据源目的指针
              RDBytes          读数据字节数
              ByteInv          节数位流次序
              _transbyte_positive   bit7..bit0
              _transbyte_inverse    bit0..bit7

      返回值:
              _NO_ERROR
              _UNINST_ERROR
              _UNKNOWN_ERROR
              _NO_INIT
   */


   extern int MemCard_Write(char _far *WTaddr,unsigned char WTBits,unsigned char ByteInv);
   /* 功能： IC卡写操作。
      参数:   WTaddr           写数据源指针
              WTBits           写数据bit数
              ByteInv          节数位流次序
              _transbyte_positive   bitn..bit0
              _transbyte_inverse    bit0..bitn

      返回值:
              _NO_ERROR
              _UNINST_ERROR
              _UNKNOWN_ERROR
   */

   extern int MemCard_PowerUp(void);
   /* 功能：IC卡控制器上电通讯状态。
      参数:   无
      返回值:
              _NO_ERROR
              _POWER_FAIL
              _NO_INIT
      注意：  IC卡控制器通讯须先调用此函数。
   */

   extern int MemCard_PowerDown(void);
   /* 功能： IC卡控制器进入省电模式。
      参数:   无
      返回值:
              _NO_ERROR
              _UNINST_ERROR
              _NO_INIT
   */

   extern void MemCard_PinDir(unsigned char CDRio,unsigned char CDRc4,unsigned char CDRc8);
   /* 功能： IC卡双向IO输入\输出方向控制。
      参数:   CDRio \CDRc4 \CDRc8    -      IO PIN
              0 － 输出
              1 － 输入
      返回值: 无
   */

   extern void MemCard_PinRd(unsigned char _far *CDRio,unsigned char _far *CDRc4,unsigned char _far *CDRc8);
   /* 功能： 存储IC卡输入IO读取。
      参数:   CDRio \CDRc4 \CDRc8    -      IO PIN
      返回值: 无
   */

   extern void MemCard_PinSet(unsigned char CDRio,unsigned char CDRc4,unsigned char CDRc8,unsigned char CDRRst,unsigned char CClk);
   /* 功能： 存储IC卡输出IO设置。
      参数:   CDRio \CDRc4 \CDRc8 \CDRRst \CClk  -  IO PIN
      返回值: 无
   */

   extern void SYNPulse_Width(unsigned char HDelay,unsigned char Delay);
   /* 功能：IC卡同步时钟高低电位保持时间\占空比\频率调整。
      参数:   HDelay  高电位延时计数器
              Delay   低电位延时计数器
      返回值: 无
   */

   #endif
