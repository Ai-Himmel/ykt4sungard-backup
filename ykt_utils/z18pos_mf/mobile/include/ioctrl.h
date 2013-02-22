 /*********************************************
 **	    HT IO Control extended functions     **
 **		Heading File For HT2800              **
 *********************************************/

#ifndef __IOCTRL

    extern unsigned int GetIOsts(void)
    /*
    1.读取IO并口输入／输出状态设置，HT2800有效。
    参数：无
    返回参数：
    函数值:  字 （对应11脚，高五BITS无意义）
           1－输入，0－输出
    */

    extern void SetIOsts(unsigned int status)
    /*
    2.设置IO并口输入／输出状态，HT2800有效。
    参数： 字 （对应11脚，高五BITS无意义）
         1－输入，0－输出
    返回参数： 无
    */

    extern unsigned int ReadIOPort(void)
    /*
    3.从IO并口读取数据，HT2800有效。
    参数：无
    返回参数：
    函数值:  字 （对应11脚，高五BITS无意义）
    */

    extern void SetIOPort(unsigned int value)
    /*
    4.向IO并口送数据，HT2800有效。
    参数： 字 （对应11脚，高五BITS无意义）
    返回参数： 无
    */

    extern void NormalIOsts(void)
    /*
    5.退出IO并口输入／输出状态，HT2800有效。
    参数：无
    返回参数： 无
    */

#endif
