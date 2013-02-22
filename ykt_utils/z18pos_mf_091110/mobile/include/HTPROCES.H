 /*********************************************
 **	    HT Process Control Functions     **
 **		 Heading File                **
 *********************************************/

  #define _pro_NORE  0x01
  #define _pro_UNDE  0x02
  #define _pro_MUTI  0x04
  #define _pro_STD   0x00 

  #define _pro_KEEP  0x00
  #define _pro_END   0xff

  #ifndef __HTPROCESS


  extern void SetorSwtProcess(unsigned char ProcType,
			      char *ChiProcName, char *EngProcName);
  /*  设置进程属性和名字。
      参数:   ProgType     进程属性
              ChiProcName  中文进程名字符串
              EngProcName  英文进程名字符串
　　  返回值: 无
　　 【注释】 进程属性
              _pro_NORE    不可挂起进程
              _pro_UNDE    不可删除属性
              _pro_MUTI    多重实例属性
              _pro_STD     标准进程(可删除, 可挂起, 单一实例进程)

      例如不可删除, 可挂起, 多重实例进程可设为_pro_STD+_pro_UNDE+_pro_MUTI
      如果进程具单一实例属性， 那么调用此功能时系统首先根据英文进程名检查内存中
  的所有进程，如果存在同名进程，则自动结束本进程并切换至该进程；否则设置进程属性
  和名字并返回用户程序。*/


  extern unsigned int  SwtProcess(unsigned char EndSelf, char _far *EngProcName);
  /* 按英文进程名切换到指定进程。
    参数：　EndSelf 切换方式(是否保留当前进程)
                      _pro_KEEP 保留当前进程
                      _pro_END  结束当前进程
              EngProcName英文进程名字符串

　　返回值：　非零 切换成功 
              零   指定进程不存在。

　　【注释】 调用此功能时系统首先根据英文进程名检查内存中的所有进程，如果存在同名进程，
     则切换至该进程去；否则返回错误。如果切换方式为保留当前进程，则当前进程暂时挂起，
     否则自动结束当前进程。如果进程为不可挂起进程，则无论何种切换方式，均自动结束当
     前进程。 */


  extern unsigned int execsub(char _far *pathname,  char _far *commdln);
  /* 加载子进程。
    参数：　  pathname  程序名 
              commdln   命令行

　　返回值：　零    加载成功 
              非零  错误码(DOS)?
  */

 #endif


