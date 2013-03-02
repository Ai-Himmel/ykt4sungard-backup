/*: 定义全局参数宏                                       
  作者  : 耿刚                                  
  时间	：2004-08-18                          
*/ 

#ifndef  __GLOBALPARAMETER_H_
#define  __GLOBALPARAMETER_H_


#define GLOBE_FLAG_BALANCE		1	 //结算标志全局参数
#define GLOBE_MAXCARDBALANCE		2	 //最大充值金额
#define GLOBE_MONTH_ACC_TIME		3	//月结日期
#define GLOBE_BLACKSHEETVER		5	 //黑名单版本
#define GLOBE_BLACKSHEETTIME		6	 //黑名单有效期
#define GLOBE_TMPCARDVALIDDATE	7	 //过渡临时卡有效期
#define GLOBE_TRADESEIALDATE		8	 //默认所有设备交易流水同步间隔
#define GLOBE_RENEWCARDDATE		9	 //默认挂失补办正式卡期限
#define GLOBE_NO_NAME_TMPCARDVALIDDATE	10	 //非记名临时卡有效期
#define GLOBE_MAX_CARDDB_NOBALANCE_TIMES	11	 //允许卡库不平最大次数邋（天数）
#define GLOBE_MAX_CARDDB_NOBALANCE_MONEY	12	 //允许卡库不平最大金额
//#define GLOBE_FLAG_SYNCCUT					13	 //客户同步程序标识
#define GLOBE_FLAG_TEMPCARD_FEETYPE	13
#define GLOBE_FLAG_TEMPCARD_CUTTYPE  14
#define GLOBE_SCHOOL_NAME			15  //一卡通用户名
#define GLOBAL_MAX_PER_SUBSIDY	    16 // 单笔补助最大金额




/*监控部分－设备监控*/
#define GLOBE_DEV_BEATTIME	1000	 //设备心跳间隔时间
#define GLOBE_DEV_BEATCOUNT	1001	 //没有收到设备心跳次数阀值
#define GLOBE_DEV_BSVER    		1002	 //设备黑名单版本号与系统当前版本号差值阀值       
#define GLOBE_DEV_STORGEP  	1003	 //硬盘应用百分比警戒值                           
#define GLOBE_DEV_MEMORYP  	1004	 //内存应用百分比警戒值                           
#define GLOBE_DEV_CPUP     		1005	 //CPU应用百分比警戒值 
#define GLOBE_DEV_TIME     		1006	 //设备时钟不同步阀值
/*监控部分－应用监控*/
#define GLOBE_APP_BEATTIME	1100	 //应用心跳间隔时间
#define GLOBE_MIF_SUMTIME		1101	 //默认结算运行时间
#define GLOBE_MIF_NOTIFTIME	1102	 //默认报警处理时间全局参数(单位秒)

#define GLOBE_MIF_CARDOPERATETIMES	1103	 //监控定时长内卡操作次数，定时长全局参数
#define GLOBE_MIF_CARDOPERATECOUNT	1104	 //监控定时长内卡操作次数，卡操作次数全局参数
#define GLOBE_MIF_CARDOPERATEMAXFEE	1105	 //单次卡操作默认最大额全局参数

#define GLOBE_DEV_DAY_TRADE_LIMIT 1106		// 终端日消费限额
#define GLOBE_DEV_ONCE_TRADE_LIMIT 1107		// 终端单次消费限额

/*三九相关*/
#define GLOBE_999_SHUTTIMES	2005	 //扎帐时间
#define GLOBE_999_DEVAUTHKEY	2006	 //设备授权密钥
#define GLOBE_999_65CARDKEY	2007	 //65类卡密钥

/* 门禁相关*/
#define GLOBE_DOOR_HOLIDAY_MAX 2008	//门禁节假日最大个数
#define GLOBE_PURSE_TWO_CARDKEY  2009	 //小钱包密钥
#define GLOBE_WATER_PURSE_NO  2010 //水控钱包号

/*小钱包上限, 单位为元*/
#define GLB_PACKET_LIMITS     3001
//add by hhd
#define GLOBLE_SYSPARA_STATIC_KEY 	2006  /* 密钥*/

#define GLOBAL_SCHOOL_CODE	2999  /* 学校编号 */

// add by 汤成 2008-1-11 , 下载文件的路径
#define GLOBAL_DOWNLOAD_PATH	2305
// 上传文件路径
#define GLOBAL_UPLOAD_PATH		2306

//对账文件可执行程序存放路径
#define GOLBAL_EXC_ACC_CHK_PATH	2100

/* add by 汤成 2008-1-11 , 松江大学城工行 ISBP 来盘文件使用 */
// 单位委托码
#define GLOBAL_ISBP_ENTRUST_CODE 4000
// 业务代码
#define GLOBAL_ISBP_OPERATION_CODE 4001
// 委托单位帐号
#define GLOBAL_ISBP_BANKCODE 4002
// 委托单位名称
#define GLOBAL_ISBP_NAME 4003

#endif
