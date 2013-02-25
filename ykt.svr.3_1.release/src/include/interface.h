#ifndef  __INTERFACE_H
#define  __INTERFACE_H
#define IFERR_SYSTEM			1	 //系统错误	
#define IFERR_DATABASE			2  	//数据库错误
#define IFERR_NETWORK			3 	//网络错误		
#define IFFER_TRANS				5	//交易失败
#define IFERR_NOTEXIST_SYSID	6  	//子系统不存在
#define IFERR_NOTEXIST_POS		7  	//POS不存在
#define IFERR_DINCKEY			8	//密钥错误
#define IFERR_DEVICE_NOSHOP		9  	//设备没有分配给商户
#define IFERR_NOTEXIST_CARD		11  //卡不存在
#define IFERR_CARDCLOSE			12  //卡已注销
#define IFERR_CARDLOST			13  //卡已挂失
#define IFERR_CARDFROZED		14  //卡已被冻结
#define IFERR_CARDBAD			15  //卡已损坏
#define IFERR_CARDLOCK			16  //卡已锁
#define IFERR_CARDEXPIRED		17  //卡已过有效期
#define IFERR_CARDPWD			18	//卡密码错误
#define IFERR_CARDBAL_SHORTAGE  19  //卡余额不足
#define IFERR_CARDCNT			20  //卡交易次数异常
#define IFERR_NOTEXIST_SHOP		31  //商户不存在
#define IFERR_SHOPCLOSE			32  //商户已注销
#define IFERR_SHOP_NOTCOSUME	33  //商户不是收费商户
#define IFERR_GETSUBSIDY		34	//领取补助错误
#endif
