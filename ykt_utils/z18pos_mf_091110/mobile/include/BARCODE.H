 /*********************************************
 **	    HT Barcode Scan extended functions   **
 **		Heading File For HT2800              **
 *********************************************/

#define       _BarRightEnd    7

    extern int GetBarStr(char _far * StrBuffer, char * BarType);
    /*
    读取条码串
    参数：     条码串输出缓冲区地址
               条码类型输出
    返回参数： 条码串输出缓冲区
    函数值:    条码串长度字
    */

    extern int SetBarTemp(unsigned char SetLength, char _far * ParmStrBuffer);
    /*
    解码器某参数设置，关机后该参数不保留。
  　参数：
           SetLength       参数串长度
           ParmStrBuffer   参数串
    返回参数：
            ＝  0  完成
           ＜＞ 0  失败
    */

    extern int GetBarTemp(unsigned char GetLength, char _far * ParmStrBuffer);
    /*
  　读取当前解码器某参数。
  　参数：
           GetLength       参数串长度
           ParmStrBuffer   参数串
    返回参数：
            ＝  0  完成
           ＜＞ 0  失败
    */

