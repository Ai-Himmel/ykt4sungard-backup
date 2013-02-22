 /**************************************************************
 **　以下的函数中，点坐标值在HT-2800上0<=x<=127，0<=y<=127；  **
 **                点坐标值在HT-1820上0<=x<=127，0<=y<=63；   **
 **                在HT-2800上，行号为1~8，列号为1~16；       **
 **                在HT-1820上，行号为1~4，列号为1~16。       **
 **                文本缓冲区的行数最大为25，列数最大为80。   **
 **************************************************************/

   #define Lcd28_Buffer 5120*2
   #define _attr_NORM 0x07
   #define _attr_INVE 0x70

   #define _F1  0x3b00
   #define _F10 0x4400
   #define _DEL 0x5300
   #define _ESC 0x011b
   #define _ENT 0x1c0d
   #define _SPC 0x3920
   #define _DWN 0x5000
   #define _UP  0x4800
   #define _LFT 0x4b00
   #define _RGT 0x4d00
   #define _PLS 0x0d2b
   #define _MIN 0x0c2d
   #define _MUL 0x092a
   #define _DIV 0x352f

  typedef struct {
    char *menubar;
    unsigned char menukey;
  } MENU_ITM;


  extern void blankscreen(unsigned char UpperLeftX, unsigned char UpperLeftY,
			  unsigned char LowerRightX, unsigned char LowerRightY);
    /*
    1.清除屏幕
    参数：UpperLeftX         左上角的列号
          UpperLeftY         左上角的行号
	  LowerRightX        右下角的列号
          LowerRightY        右下角的行号
          在HT-2800中，以上的行号在为1~8，列号为1~16；
          在HT-1820中，以上的行号在为1~4，列号为1~16；
    返回参数：无
    函数值：无
    */

  extern void scrollupscr(unsigned char UpperLeftX, unsigned char UpperLeftY,
			  unsigned char LowerRightX, unsigned char LowerRightY,
			  unsigned char ScrollLines);
    /*
    2.向上滚动屏幕
    参数：UpperLeftX         左上角的列号
          UpperLeftY         左上角的行号
	  LowerRightX        右下角的列号
          LowerRightY        右下角的行号
          ScrollLines        向上滚动的行数
          在HT-2800中，以上的行号在为1~8，列号为1~16；
          在HT-1820中，以上的行号在为1~4，列号为1~16；
    返回参数：无
    函数值：无
    */

  extern void scrolldownscr(unsigned char UpperLeftX, unsigned char UpperLeftY,
			    unsigned char LowerRightX, unsigned char LowerRightY,
			    unsigned char ScrollLines);
    /*
    3.向下滚动屏幕
    参数：UpperLeftX         左上角的列号
          UpperLeftY         左上角的行号
	  LowerRightX        右下角的列号
          LowerRightY        右下角的行号
          ScrollLines        向下滚动的行数
          在HT-2800中，以上的行号在为1~8，列号为1~16；
          在HT-1820中，以上的行号在为1~4，列号为1~16；
    返回参数：无
    函数值：无
    */

  extern void saycstr(unsigned char atX, unsigned char atY, char *str, unsigned char attr);
    /*
    4.在指定光标处显示字符串
    参数：atX         列号
          atY         行号
	  str         要显示的字符串
          attr        该行的属性（_attr_NORM:普通； _attr_INVE:反色）
          在HT-2800中，以上的行号在为1~8，列号为1~16；
          在HT-1820中，以上的行号在为1~4，列号为1~16；
    返回参数：无
    函数值：无
    */

  extern void saystr(char *str, unsigned len);
    /*
    5.在当前光标处显示字符串
    参数：str         要显示的字符串
          len         字符串的长度
    返回参数：无
    函数值：无
    */

  extern unsigned readspckey(void);
    /*
    6.读键盘
    参数：无
    返回参数：无
    函数值： 键值
    */

  extern void toxy(unsigned char X, unsigned char Y);
    /*
    7.指定光标位置
    参数：X     列号
          Y     行号
          在HT-2800中，以上的行号在为1~8，列号为1~16；
          在HT-1820中，以上的行号在为1~4，列号为1~16；
    返回参数：无
    函数值：无
    */

  extern void OpenLCDWindow(unsigned char luX, unsigned char luY,
		     unsigned char rlX, unsigned char rlY,
		     unsigned char ColCnt, unsigned char RowCnt,
		     char _far *Buffer);
    /*
    8.开窗口
    参数：luX          窗口的左上角的X坐标
          luY          窗口的左上角的Y坐标
          rlX          窗口的右下角的X坐标
          rlY          窗口的右下角的Y坐标
          ColCnt       当前文本缓冲区的列数
          RowCnt       当前文本缓冲区的行数
          Buffer       保存缓冲区地址
          在HT-2800中，以上的X、Y坐标为0~127；
          在HT-1820中，以上的X坐标为0~127，Y坐标为0~63；
    返回参数：无
    函数值：无
    */

  extern void CloseLCDWindow(char _far *Buffer);
    /*
    9.关窗口
    参数：Buffer       保存缓冲区地址
    返回参数：无
    函数值：无
    */

  extern void HideCursor(void);
    /*
    10.隐蔽光标
    参数：无
    返回参数：无
    函数值：无
    */

  extern void ShowCursor(void);
    /*
    11.显示光标
    参数：无
    返回参数：无
    函数值：无
    */

  extern unsigned char menu(MENU_ITM menuset[],
		     char *title, unsigned char deflbar,
		     unsigned char atX, unsigned char atY);
    /*
    12.建立菜单
    参数：menuset      菜单项
          title        菜单的标题
          deflbar      缺省时高光条在菜单中的位置
          atX          菜单左上角的行号
          atY          菜单左上角的列号
          在HT-2800中，以上的行号在为1~8，列号为1~16；
          在HT-1820中，以上的行号在为1~4，列号为1~16；
    返回参数：无
    函数值：菜单项的KEY值
    */

  extern unsigned char menuwin(unsigned char luX, unsigned char luY,
			unsigned char rlX, unsigned char rlY,
			unsigned char ColCnt, unsigned char RowCnt,
			MENU_ITM menuset[],
			char *title,  unsigned char deflbar);
    /*
    13.建立弹出式窗口菜单
    参数：luX          窗口的左上角的X坐标
          luY          窗口的左上角的Y坐标
          rlX          窗口的右下角的X坐标
          rlY          窗口的右下角的Y坐标
          ColCnt       当前文本缓冲区的列数
          RowCnt       当前文本缓冲区的行数
          menuset      菜单项
          title        菜单的标题
          deflbar      缺省时高光条在菜单中的位置
          在HT-2800中，以上的X、Y坐标为0~127；
          在HT-1820中，以上的X坐标为0~127，Y坐标为0~63；
    返回参数：无
    函数值：菜单项的KEY值
    */

  extern int show2lnbox(char *fstLine, char *sndLine,...);
    /*
    14.建立弹出式窗口提示信息
    参数：fstLine     第一行提示信息
          sndLine     第二行提示信息
          ...         一个整型参数（HT-1820可以不加此参数）
                      1     HT-1820
                      2     HT-2800
    返回参数：无
    函数值： 键值
    */

