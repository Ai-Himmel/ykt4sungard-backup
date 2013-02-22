 /*********************************************
 **	    HT LCD extended functions	     **
 **		 Heading File                **
 *********************************************/
 /**************************************************************
 **　以下的函数中，点坐标值在HT-2800上0<=x<=127，0<=y<=127；  **
 **                点坐标值在HT-1820上0<=x<=127，0<=y<=63；   **
 **                在HT-2800上，行号为1~8，列号为1~16；       **
 **                在HT-1820上，行号为1~4，列号为1~16。       **
 **                文本缓冲区的行数最大为25，列数最大为80。   **
 **************************************************************/

 #define _fnt_CCA  0x01
 #define _fnt_CCB  0x02
 #define _fnt_ENG  0x03

 #define _cur_NOR  0x00
 #define _cur_CAP  0x01
 #define _cur_INS  0x02

 #define _pul_NON  0x00
 #define _pul_HOR  0x01
 #define _pul_VER  0x02

 #define _col_WHR  0x00
 #define _col_BLK  0x01
 #define _col_INV  0x02

 #define _mod_ABS  0x00
 #define _mod_OR   0x01
 #define _mod_XOR  0x02

 #define _map_UP   0x00
 #define _map_DWN  0x01
 #define _map_LFT  0x02
 #define _map_RGT  0x03

 #define _bkl_OFF  0x00
 #define _bkl_ON   0x02

 #ifndef __HTLCD


    extern void ClrGraph(void);
    /*
      1.清除液晶屏幕和图形缓冲区。
　　　参数：　
		 无
　　  返回参数：
		 无
　　 【注释】　此功能调用并不清除文本缓冲区。
    */

    extern unsigned int LCDinChinese(void);
    /*
      2.测试当前显示字符集是否为中文字符集。
　　　参数：　
		 无
　　  返回参数：
                 无
      函数值:
             　  0　       为全英文字符集
                 1         为中文简体字符集
                 2         为中文繁体字符集
    */
    
    extern void SetFont(unsigned char FontID);
    /*
　　3.设置显示字符集。
　　参数：　　
   　          FontID       字符集标识符
                    1       中文简体字符集
                    2　   　中文繁体字符集
                    3　   　全英文字符集
　  返回参数：
                 无
    函数值:
                 无
    */

    extern void RefreshWin(void);
    /*
 　  4.刷新当前液晶视窗。
     　参数：　
                 无
       返回参数：
                 无
      函数值:
                 无
    */

    extern void RefreshLCD(void);
    /*
      5.按图形缓冲区刷新液晶屏幕。
     　参数：　
                 无
       返回参数：
                 无
      函数值:
                 无
    */

    extern void ClrLCDScr(void);
    /*
   　6.清除液晶屏幕、文本缓冲区及图形缓冲区，并移光标到屏幕左上角。
　　　参数：　
                 无
　　  返回参数：
                 无
      函数值:
                 无
    */

    extern void SetCurType(unsigned char CursorType);
    /*
　  　7.选择光标形状。
　  　参数：
                 CursorType           光标类型
                   _cur_NOR 　        正常光标
                   _cur_CAP　         <Caps>光标
                   _cur_INS 　        <Ins> 光标
                   _cur_INS+_cur_CAP　<Caps>且<Ins> 光标
　　  返回参数：
                 无
      函数值:
                 无
    */
 
    extern void GetLCDMap(int _far *x, int _far *y);
    /*
      8.取得当前光标相对于液晶视窗左上角的点坐标
　  　参数：　
                 X     Ｘ坐标（点坐标）
                 y     Ｙ坐标（点坐标）
　　  返回参数：  
                 X     当前光标相对于液晶视窗左上角的Ｘ坐标（点坐标）
                 y     当前光标相对于液晶视窗左上角的Ｙ坐标（点坐标）
      函数值:
                 无
    */

    extern void SetLCDMap(int x, int y);
    /*
    　9.调整液晶视窗到文本缓冲区的映射使当前光标相对于液晶视
        窗左上角的点坐标为指定值
　  　参数：
                 X            指定的Ｘ坐标（点坐标）
                 y            指定的Ｙ坐标（点坐标）
　　  返回参数：
                 无
      函数值:
                 无
    */

    extern unsigned char SetPullMode(unsigned char CursorMode);
    /*
　  　10.设置屏幕滚动方式。
　  　参数：
                 CurSorMode   屏幕滚动方式    
                   _pul_NON    禁止滚动
                   _pul_HOR    禁止纵向滚动,允许横向滚动
                   _pul_VER    禁止纵向滚动,允许纵向滚动
                   _pul_HOR
                   +_pul_VER   允许横向滚动,允许纵向滚动
　　  返回参数： 无
      函数值:    旧滚动方式，含义同上。
     【注释】　屏幕滚动方式决定当光标移出液晶视窗时，视窗是否
              沿移动方向滚动。允许横向滚动表示当光标沿Ｘ向移出液晶实屏时，视窗
              沿移动方向滚动，否则保持视窗不动；允许纵向滚动表示当光标沿Ｙ向移
              出液晶实屏时，视窗沿移动方向滚动，否则保持视窗不动。
    */

    extern unsigned char GetPullMode(void);
    /*
　  　11.取得屏幕滚动方式。
　　　参数：　
                 无
　　  返回参数：
                 无
      函数值:    滚动方式，含义同上。
    */

    extern void WriteAtDot(unsigned int dotX, unsigned int dotY,
                           unsigned char Mode, unsigned char Attr,
                           unsigned int dblChar);
    /*
　  　12.在当前液晶视窗的指定点坐标位置上显示字符。
　  　参数：
                 dotX        Ｘ坐标
　　　　　　   　dotY        Ｙ坐标
                 Mode        显示模式
                 _mod_ABS  　显示指定字符的点阵
                 _mod_OR   　显示指定字符的点阵与坐标处原点阵相或产生的点阵
                 _mod_XOR  　显示指定字符的点阵与坐标处原点阵相异或产生的点阵
　　　　　　　   Attr        字符的显示属性
                 dblChar     要显示的字符（可以是汉字字符）
　　  返回参数：
                 无
      函数值:
                 无
   　【注释】　该坐标为该点位置相对于当前液晶视窗左上角的点的 点
               坐标，即当前液晶视窗左上角的点的坐标为（0, 0）。
    */

    extern void MoveLCDMap(unsigned char Direction);
    /*
　  　13.移动液晶视窗到文本缓冲区的映射。
　　  参数：
                 Direction   移动方向              
                   _map_UP 　上移视窗，使得视窗中每一行均与文本缓冲区中原对应行的
                             上一行相对应
                   _map_DWN  下移视窗，使得视窗中每一行均与文本缓冲区中原对应行的
                             下一行相对应
                   _map_LFT  左移视窗，使得视窗中每一列均与文本缓冲区中原对应列的
                             左一列相对应
                   _map_RGT  右移视窗，使得视窗中每一列均与文本缓冲区中原对应列的
                             右一列相对应
　　  返回参数：
                 无
      函数值:
                 无
     【注释】 当视窗最边缘的行（列）显示的字符不完整时，向这个方向
              移动产生的效果是使得这个字符显示完整。
    */

    extern void ReverseArea(unsigned char luX, unsigned char luY,
                            unsigned char rlX, unsigned char rlY);
    /*
  　　14.将液晶屏幕指定区域所有点的显示属性反转。
　  　参数：　　
                 luX          指定区域左上角的Ｙ坐标（点坐标）
　               luY          指定区域左上角的Ｘ坐标（点坐标）
                 rlX          指定区域右下角的Ｙ坐标（点坐标）
                 rlY          指定区域右下角的Ｘ坐标（点坐标）
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　区域左上角、右下角的坐标是相对于液晶实屏左上角的点坐标。
    */

    extern void ResetLCDMap(void);
    /*
　  　15.复位光标及液晶视窗到文本缓冲区的映射。
　　　参数：　
                 无
　　  返回参数：
                 无
      函数值:
                 无
     【注释】  此调用液晶视窗左上角对应于文本缓冲区的首行首列，而且使光标回到该
              位置。
    */

    extern void LCDWindow(unsigned char luX, unsigned char luY,
                          unsigned char rlX, unsigned char rlY,
                          unsigned char ColCnt, unsigned char RowCnt);
    /*
  　　16.定义液晶视窗。
  　　参数：　　
                 luX          视窗左上角的Ｙ坐标
　               luY          视窗左上角的Ｘ坐标
                 rlX          视窗右下角的Ｙ坐标
                 rlY          视窗右下角的Ｘ坐标
                 RowCnt       该视窗所用的文本缓冲区的行数
　　　　　　　   ColCnt       该视窗所用的文本缓冲区的列数
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　视窗左上角、右下角的坐标是相对于液晶实屏左上角的点坐标；
               文本缓冲区的行数最大为25，列数最大为80。
    */

    extern void SaveScreen(char _far *Buffer);
    /*
  　　17.保存当前液晶屏幕内容及显示状态。
  　　参数：　　
                 Buffer       保存缓冲区地址
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　当前液晶屏幕内容包括文本及图形缓冲区内容；显示状态包括字符集、
               光标位置、视窗定义等所有显示控制信息。当前所需缓冲区
               的大小可以由WinSize()获得，最大可达 5K 字节。
    */

    extern char _far * HeapSaveScr(void);
    /*
  　　18.保存当前液晶屏幕内容及显示状态。
  　　参数：　　
                 无
　　  返回参数：
                 无
      函数值:
                 保存缓冲区地址
     【注释】　当前液晶屏幕内容包括文本及图形缓冲区内容；显示状态包括字符集、
               光标位置、视窗定义等所有显示控制信息。
               缓冲区是开在堆中的，所以用户的堆要开的足够大。
    */

    extern void SaveGraph(char _far *Buffer);
    /*
　  　19.保存当前液晶图形缓冲区内容。
　　  参数：   
                 Buffer       保存缓冲区地址
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　缓冲区的大小为1024字节。
    */

    extern void RestoreScreen(char _far *Buffer);
    /*
　　  20.恢复液晶屏幕内容及显示状态。
  　　参数：　　
                 Buffer       保存缓冲区地址
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　缓冲区的内容必须是由SaveScreen()填写的，并且不应有任何改动。
    */

    extern void HeapRestoreScr(char _far *Buffer);
    /*
　　  21.恢复液晶屏幕内容及显示状态。
  　　参数：　　
                 Buffer       保存缓冲区地址
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　缓冲区的内容必须是由HeapSaveScr()填写的，并且不应有任何改动。
    */

    extern void RestoreGraph(char _far *Buffer);
    /*
　  　22.恢复液晶图形缓冲区内容。
    　参数：　　
		 Buffer      保存缓冲区地址
　　  返回参数：
                 无
      函数值:
                 无
    【注释】　缓冲区的内容必须是由SaveGraph调用填写的，并且不应有任何改动。
    */

    extern void DotWrite(unsigned char dotX, unsigned char dotY,
                         unsigned char Color);
    /*
　  　23.在指定点坐标位置上显示点。
　　  参数：
                 dotX         该点的Ｙ坐标
                 dotY       　该点的Ｘ坐标
                 Color        点的颜色
                   _col_WHR   白色
                   _col_BLK   黑色
                   _col_INV   反转该坐标上原点的颜色
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　该点的坐标是相对于液晶实屏左上角的点坐标。此调用仅
               更新液晶图形缓冲区，只有当下次调用子功能 03H──按图形缓冲区刷新
               液晶显示才会将更新后的图形缓冲区显示出来。
    */

    extern void DrawBox(unsigned char luX, unsigned char luY,
                        unsigned char rlX, unsigned char rlY,
                        char Color);
    /*
  　　24.按指定点坐标画框。
　  　参数：
                 luY          框左上角的Ｙ坐标
　               luX          框左上角的Ｘ坐标
                 rlX          框右下角的Ｙ坐标
                 rlY          框右下角的Ｘ坐标
                 Color        框的颜色
                   _col_WHR   白色
                   _col_BLK   黑色
                   _col_INV   反转框所经过的每一处坐标上原点的颜色
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　框左上角、右下角的坐标是是相对于液晶实屏左上角的点
               坐标。此调用仅更新液晶图形缓冲区，只有当下次调用子功能 03H──按
               图形缓冲区刷新液晶显示才会将更新后的图形缓冲区显示出来。
    */

    extern unsigned int BackLightOn(void);
    /*
　    25.取得液晶背光状态。
　　　参数：　
                 无
　　  返回参数：
                 无
      函数值:    0    背光关闭
                 非0  背光开启
    */

    extern void TurnBackLight(unsigned char On_Off);
    /*
      26.设置液晶背光开关。  
　  　参数：
                 On_Off       背光开关
                   _blk_OFF   关闭背光
                   _blk_ON    开启背光
　    返回参数：
                 无
      函数值:
                 无
    */

    extern unsigned int WinSize(unsigned char _far *ColCnt,
                                unsigned char _far *RowCnt);
    /*
　  　27.取得保存当前液晶屏幕内容及显示状态所需缓冲区的大小。
　  　参数：
                 ColCnt
                 RowCnt
　　  返回参数：　
                 RowCnt       当前文本缓冲区的行数
　　　　　　　   ColCnt       当前文本缓冲区的列数
      函数值:    所需缓冲区的大小(字节数)
    */                

    extern void DrawLine(unsigned char startX, unsigned char startY,
                         unsigned char endX, unsigned char endY,
                         unsigned char Color);
    /*
    　28.按指定点坐标画线。
　  　参数：　　
                 StartY       线起点的Ｙ坐标
　               StartX       线起点的Ｘ坐标
                 endX         线终点的Ｙ坐标
                 endY         线终点的Ｘ坐标
                 color        线的颜色
                    _col_WHR  白色
                    _col_BLK  黑色
                    _col_INV  反转线所经过的每一处坐标上原点的颜色
　    返回参数：
                 无
      函数值:
                 无
     【注释】　线起点、终点的坐标是相对于液晶实屏左上角的点坐标。
               此调用仅更新液晶图形缓冲区，只有当下次调用子功能 03H──按图形缓
               冲区刷新液晶显示才会将更新后的图形缓冲区显示出来。
    */

    extern void Draw(char _far *DrawStr);
    /*
  　　29.按指定的画图命令串画图。
  　　参数：　　
                 DrawStr      画图命令串地址
　    返回参数：
                 无
      函数值:
                 无

    【注释】  画图命令串是一个由一组连续的画图命令组成，并以一个不可识别的命令
     结尾的字符串。画图命令的格式如下：
      'M'<坐标定位指令> 移动画图光标到坐标定位指令指定的点坐标位置；
　　  'L'<坐标定位指令> 从当前画图光标到坐标定位指令指定的点坐标位置，用当前画图
                        颜色画线，并移动当前画图光标到该指定位置；
　　  'B'<坐标定位指令> 以当前画图光标为左上角，以坐标定位指令指定的点坐标位置为
                        右下角，用当前画图颜色画框，并移动当前画图光标到该指定位
                      置；　　　　　
　　  'S'<坐标定位指令> 以当前画图光标为左上角，以坐标定位指令指定的点坐标位置为
                        右下角，用当前画图颜色画矩形，并移动当前画图光标到该指定
                        位置；
　　  'C'<画图颜色>     设置当前画图颜色为指定颜色
                        画图颜色为一字节变量，含义如下：
                        00H 白色
                        01H 黑色
                        02H 反转图形每一处坐标上原点的颜色；
　　  'R'                按图形缓冲区刷新液晶屏幕；
      '$'               命令字串结束。
  　　坐标定位指令格式如下：
      't'<X><Y>   绝对坐标（相对于液晶实屏左上角──点坐标(0, 0)）(X, Y)，即Ｘ坐
                  标为X，Ｙ坐标为Y；
      'r'<X><Y>   相对（于当前画图坐标）坐标(X, Y)，即Ｘ坐标为当前画图Ｘ坐标加X，
                  Ｙ坐标为当前画图Ｙ坐标加Y；
      'du'<N>     相对（于当前画图坐标）坐标(0, -N)，即Ｘ坐标为当前画图Ｘ坐标，
                  Ｙ坐标为当前画图Ｙ坐标上移N点；
      'dr'<N>     相对（于当前画图坐标）坐标(N, 0)，即Ｘ坐标为当前画图Ｘ坐标右移
                  N点，Ｙ坐标为当前画图Ｙ坐标；
      'dd'<N>     相对（于当前画图坐标）坐标(0, N)，即Ｘ坐标为当前画图Ｘ坐标，Ｙ
                  坐标为当前画图Ｙ坐标下移N点；
      'dl'<N>     相对（于当前画图坐标）坐标(-N, 0)， 即Ｘ坐标为当前画图Ｘ坐标左
                  移N点，Ｙ坐标为当前画图Ｙ坐标；
      'de'<N>     相对（于当前画图坐标）坐标(-N, -N)，即Ｘ坐标为当前画图Ｘ坐标左
                  移N点，坐标为当前画图Ｙ坐标上移N点；
      'df'<N>     相对（于当前画图坐标）坐标(N, -N)， 即Ｘ坐标为当前画图Ｘ坐标右
                  移N点，坐标为当前画图Ｙ坐标上移N点；
      'dg'<N>     相对（于当前画图坐标）坐标(N, N)，即Ｘ坐标为当前画图Ｘ坐标右移
                  N点，坐标为当前画图Ｙ坐标下移N点；
      'dh'<N>     相对（于当前画图坐标）坐标(-N, N)， 即Ｘ坐标为当前画图Ｘ坐标左
                移N点，坐标为当前画图Ｙ坐标下移N点；
      以上N、X、Y均为字节变量。
      画图光标的坐标是相对于液晶实屏左上角的点坐标。此调用更新液晶图形缓冲区，当
      调用RefreshLCD()--按图形缓冲区刷新液晶显示或在画图命令串中发刷新命令时才会
      将更新后的图形缓冲区显示出来。
    */

    extern void MovePen(unsigned char penX, unsigned char penY);
    /*
  　　30.移动画图光标到指定坐标。
  　　参数：　
                 penY         新画图光标的Ｙ坐标
                 penX         新画图光标的Ｘ坐标
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　  新画图光标位置的坐标是相对于液晶实屏左上角的点坐标。
    */

    extern void HTSound(unsigned int freq);
    /*
　  　31.开始发声。
　  　参数：　　
                 freq         发声频率
　　  返回参数：
                 无
      函数值:
                 无
    */

    extern void HTNoSound(void);
    /*
　　  32.停止发声。
　  　参数：　　
                 无 
　　  返回参数：
                 无
      函数值:
                 无
    */

    extern void DrawSolidRec(unsigned char luX, unsigned char luY,
                        unsigned char rlX, unsigned char rlY,
                        char Color);
    /*
  　　33.按指定点坐标画实心矩。
  　　参数：
                 luY          框左上角的Ｙ坐标
　               luX          框左上角的Ｘ坐标
                 rlY          框右下角的Ｙ坐标
                 rlX          框右下角的Ｘ坐标          
                 color        框的颜色
                    _col_WHR  白色
                    _col_BLK  黑色
                    _col_INV  反转框所经过的每一处坐标上原点的颜色
　　  返回参数：
                 无
      函数值:
                 无
     【注释】　框左上角、右下角的坐标是是相对于液晶实屏左上角的点
               坐标。此调用仅更新液晶图形缓冲区，只有当下次调用子功能 03H──按
               图形缓冲区刷新液晶显示才会将更新后的图形缓冲区显示出来。
    */ 

    extern void MusicPlay(char _far *MusicStr);
    /*
　  　34.开始演奏音乐。
　  　参数：　　
                 MusicStr     音乐字串
　　  返回参数：
                 无
      函数值:
                 无
     【注释】音乐的演奏是在后台进行的。音乐字串格式如下：
           t1,n1, t2,n2, ……，e
           t -- 音高（byte）  21h 为中音 1
                              22h 为中音 2
                              31h 为高音 1
                              11h 为低音 1
                              如此类推
           n -- 音长（byte）  32 为 1 秒
                              16 为 0.5 秒
                              如此类推
           e -- 结束符（byte）255 结束并停止演奏
                              254 无限重复演奏
    */

    extern void MusicStop(void);
    /*
　  　35.停止演奏音乐。
　　　参数：　
		 无
　　  返回参数：
		 无
      函数值:
		 无
    */

    extern void TurnOffHT(void);
    /*
　  　36.关掉HT电源。
　　　参数：　
		 无
　　  返回参数：
		 无
      函数值:
		 无
    */

    extern void TurnOnR232(void);
    /*
　  　37.开通RS232电源。
　　　参数：　
		 无
　　  返回参数：
		 无
      函数值:
		 无
    */

    extern void TurnOffR232(void);
    /*
　  　38.关掉RS232电源。
　　　参数：　
		 无
　　  返回参数：
		 无
      函数值:
		 无
    */

    extern void HTShowBatt(void);
    /*
　  　39.看电池容量。
　　　参数：　
		 无
　　  返回参数：
		 无
      函数值:
		 无
    */

    extern unsigned HTGetBatt(void);
    /*
　  　40.获取电池容量数据。
　　　参数：　
		 无
　　  返回参数：
		 无
      函数值:
		 电池容量数值
    */

    extern char _far *HTLogoCtrl(char _far *p);
    /*
　  　41.设置开机背景位图。
　　　参数：
		 存储背景位图的缓冲区
　　  返回参数：
		 无
      函数值:
		 存储背景位图的缓冲区
    */

    extern void HTPutHDP(char _far *p);
    /*
　  　42.显示HDP位图。
　　　参数：
		 存储背景位图的缓冲区
　　  返回参数：
		 无
      函数值:
		 无
    */

    extern unsigned char BackupBatt(void);
    /*
    43.测备份电池是否正常。
       参数：    无
     　返回参数：无
       函数值:
                 0    备份电池正常
                 1    备份电池不正常
    /*

    extern void GetDotMatrix (unsigned int dblChar, unsigned char Attr,
                              char _far *Buffer);
    /*
    44.获取字符点阵。
       参数：
           dblChar   字符(汉字)
           Attr      属性
           Buffer    保存点阵的缓冲区地址(已分配好,大小为32字节)
     　返回参数：
           Buffer    缓冲区里保存点阵
       函数值:
		 无
    */

    extern void LCDCntrstInc(void);
    /*
    45.增加液晶屏幕灰度。
       参数：无
     　返回参数：无
       函数值: 无
      【注释】每调用一次, 增加一级灰度
    */

    extern void LCDCntrstReset(void);
    /*
    46.恢复液晶屏幕缺省灰度。
       参数：无
     　返回参数：无
       函数值: 无
    */

    extern void LCDCntrstDec(void);
    /*
    47.减少液晶屏幕灰度。
       参数：无
     　返回参数：无
       函数值: 无
      【注释】每调用一次, 减少一级灰度
    */

    extern void SetSleeper(unsigned int SleepSec);
    /*
    48.设置自动关机时间。
       参数：
           SleepSec  自动关机秒数
     　返回参数：无
       函数值: 无
    */

    extern unsigned int GetSleeper(void);
    /*
    49.获取自动关机时间。
       参数：无
     　返回参数：无
       函数值：自动关机秒数
    */

    extern void EnterClock(void);
    /*
    50.进入系统电子钟。
       参数：无
     　返回参数：无
       函数值: 无
    */

    extern unsigned int HtMachineCode(void);
    /*
    51.识别机器型号。
       参数：无
     　返回参数：
              =3 HT2200 五行显示
			  =5 HT1820/HT2200 四行显示
			  =6 HT2600/HT2800X
    */

#endif
