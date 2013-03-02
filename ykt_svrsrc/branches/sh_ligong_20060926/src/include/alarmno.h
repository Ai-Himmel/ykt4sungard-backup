/*
定义警戒号宏
作者：蔡扬
时间：2004年9月28日
*/
#ifndef  __ALARMNO_H_
#define  __ALARMNO_H_

/*
监控项目编号
1.		设备监控	
2.		交易流水	
3.		卡库一致性	
4.		系统状态	
5.		报警处理－超期未完成	
*/
#define MEXCEPTION_DEVICE           		1 
#define MEXCEPTION_TRADE           		2 
#define MEXCEPTION_CARDDB           		3
#define MEXCEPTION_SYSSTATE          		4
#define MEXCEPTION_ALARMOP           		5



/*                                             
后台卡操作流水监控的警戒号定义                   
                                               
警戒号 100301 卡操作时间不处于正常工作时间       
警戒号 100302 定长时间内的卡操作次数大于等于系统?
警戒号 100303 一次卡操作额度大于系统默认卡操作最大?
警戒号 100304 卡非法卡操作                       
*/                                             
#define ALA_CARDOPERATE_TIME            			100301 
#define ALA_CARDOPERATE_COUNT	 			100302 
#define ALA_CARDOPERATE_FEE					100303 
#define ALA_CARDOPERATE_ILLEGALCARD			100304 
#define ALA_CARDOPERATE_FAIL					100305 

/*
后台监控卡库不平异常的警戒号定义

警戒号 100401 当前账户可用余额大于当前卡中账户余额
警戒号 100402 当前账户可用余额小于当前卡中账户余额
*/
#define ALA_BALANCE_APC         100401        
#define ALA_BALANCE_CPA 		100402

/*
后台系统状态监控的警戒号定义

警戒号 100501 表示结算超时
*/
#define ALA_SYSSTATE_OTW 100701


#endif                                                            

