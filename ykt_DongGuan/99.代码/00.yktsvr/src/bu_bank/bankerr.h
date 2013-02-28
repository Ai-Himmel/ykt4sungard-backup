#ifndef _BUBANK_BANKERR_H_
#define _BUBANK_BANKERR_H_

#define EB_SUCCESS        0 //成功
#define EB_SYSTEM         1 //系统故障
#define EB_NETWORK        2 //网络故障

///////////////////////////////////////////////////////////////////////////////
#define EB_AUTHENTICATION 11 //认证错误,密钥或批次号不正确
#define EB_LOGIN          12 //签到错误
#define EB_OUTSERVICE     13 //不在服务时间
#define EB_BANKLINK       14 //银行网络故障
#define EB_TERMSEQERR     15 //终端流水号重复
#define EB_DTLNOTEXITS    16 //流水不存在
#define EB_SYS_CUTON      17 //系统日切中

///////////////////////////////////////////////////////////////////////////////
#define EB_CARDLOST       21 //卡已挂失
#define EB_CARDFROZEN     22 //卡已冻结
#define EB_CARDCANCEL     23 //卡已注销
#define EB_CARDNOTEXIST   24 //卡不存在
#define EB_CARDEXPIRED    25 //卡已过期
#define EB_CARDDPSCNTERR  26 //卡充值次数异常
#define EB_CARDBAL_ABNORMAL 27 //卡余额异常，请到管理中心处理

///////////////////////////////////////////////////////////////////////////////
#define EB_BANKNOTSUPPORT 30 //该银行不支持
#define EB_BANKCARDNOTSUPPORT 31 //该银行卡不允许圈存
#define EB_DTLHASDEAL     32  //流水已处理
#define EB_DTLERROR       33  //流水状态异常
///////////////////////////////////////////////////////////////////////////////
#define EB_QUERYCOND      41 //查询条件错误

//////////////////////////////////////////////////////////////////////////////
#define EB_UNKNOWN        99 //其他错误


#endif
