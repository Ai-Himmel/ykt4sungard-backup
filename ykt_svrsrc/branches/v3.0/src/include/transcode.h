#ifndef TRANSCODE_H
#define TRANSCODE_H
#define CARDOPEN     1001


#define TCTYPE_ADD 1	//添加
#define TCTYPE_DEL 2	//删除
#define TCTYPE_UPD 3	//修改
#define TCTYPE_QRY 4	//查询
#define TCTYPE_IMP 5	//导入
#define TCTYPE_CHK 6	//审核
#define TCTYPE_RESET 7	//重置
#define TCTYPE_REVERSE 1 //冲正


#define MAKETRANSCODEADD(x) (x+TCTYPE_ADD)
#define MAKETRANSCODEDEL(x) (x+TCTYPE_DEL)
#define MAKETRANSCODEUPD(x) (x+TCTYPE_UPD)
#define MAKETRANSCODEQRY(x) (x+TCTYPE_QRY)
#define MAKETRANSCODEIMP(x) (x+TCTYPE_IMP)
//#define MAKETRANSCODECHK(x) (x+TCTYPE_CHK)
//#define MAKETRANSCODERESET(x) (x+TCTYPE_RESET)

#define MAKETRANSCODEREVERSE(x) (x+TCTYPE_REVERSE)


#define IS_TRANSCODEQRY(x) (x%10==TCTYPE_QRY)

//交易码规则:第1为表示类型第2、3位表示交易类别第4为序号
//TCM_标志为交易码宏
#define TCM_AREA	  		1000	//区域
#define TCM_BRANCH 			1010	//网点
#define TCM_SITE   			1020	//站点
#define TCM_OPER   			1030	//操作员
#define TC_OPERPWDUPD 		1040	//操作员密码修改
#define TC_OPERPWDRESET 	1041	//操作员密码重置
#define TCM_OPERSITE 		1050	//操作员站点
#define TCM_AUTHTPL  		1060	//权限模板
#define TCM_DEPT			1070	//部门
#define TCM_SPECIALTY 		1080	//专业
#define TCM_SUBSYS			1090	//子系统
#define TCM_DEVICE			1100	//设备
#define TCM_DICTIONARY		1120	//数据字典
#define TCM_PARAM			1130	//全局参数
#define TCM_CARDTYPE 		1140	//卡类别
#define TCM_PURSE			1150	//钱包
#define TCM_CUSTTYPE		1160  	//客户类别
#define TCM_FEETYPE			1170  	//收费类别
#define TCM_CFGFEE			1180  	//交易配置
#define TCM_TASK			1190	//计划任务
#define TC_TASKLOGQRY		1200	//计划任务日志查询
#define TCM_MQ				1210	//消息队列
#define TCM_BANKCARD		1220  	//银行卡绑定
#define TCM_POSSHOP 		1230 	//POS商户
#define TCM_DEPOSITSHOPPOS 	1240 	//充值商户POS
#define TCM_DEPOSITOPER 	1250    //充值操作员
#define TCM_DEPOSITOPERPOS 	1260 	//充值操作员POS
#define TCM_MEAL			1270	//餐次
#define TCM_SHOPMEAL		1280    //商户餐次
#define TCM_SHOPRAKEOFF  	1290    //商户佣金
#define TCM_CUSTOMER 		1300	//客户信息
#define TCM_CFGSHOPFEE 		1310	//商户搭伙费费率
#define TCM_CARDTYPERIGHT 	1320	//卡类别权限

#define TCM_DOORGROUP		1400   	//门禁组

#define TC_CUSTOMERTMPIMP 	2001	//客户信息导入
#define TC_CUSTOMERTMPDEL 	2002	//客户信息导入删除
#define TC_CUSTOMERTMPUPD 	2003	//客户信息导入修改
#define TC_CUSTOMERTMPQRY 	2004	//客户信息导入查询
#define TC_CUSTOMERTMPCHK 	2005	//客户信息导入审核


#define TC_DEVICETMPIMP  	2011  	//设备文件导入
#define TC_DEVICETMPDEL  	2012  	//设备文件导入删除
#define TC_DEVICETMPUPD  	2013  	//设备文件导入修改
#define TC_DEVICETMPQRY  	2014  	//设备文件查询
#define TC_DEVICETMPCHK  	2015  	//设备文件审核

#define TC_SHOPPOSTMPIMP  	2021  //商户POS文件导入
#define TC_SHOPPOSTMPDEL  	2022  //商户POS文件导入删除
#define TC_SHOPPOSTMPUPD  	2023  //商户POS文件导入修改
#define TC_SHOPPOSTMPQRY  	2024  //商户POS文件导入查询
#define TC_SHOPPOSTMPCHK  	2025  //商户POS文件导入审核

#define TC_POSDTLTMPIMP 	2030  //POS流水导入
#define TC_POSDTLTMPADD		2031  //POS流水手工录入
#define TC_POSDTLTMPDEL 	2032  //POS流水导入删除
#define TC_POSDTLTMPUPD 	2033  //POS流水导入修改
#define TC_POSDTLTMPQRY 	2034  //POS流水导入查询
#define TC_POSDTLTMPCHK 	2035  //POS流水导入审核

#define TCM_POSDTL 			2040  //POS异常流水
#define TC_CARDGET			2100 //卡片领入
#define TC_CARDPUT			2110 //卡片上交
#define TC_CARDDISABLE		2120 //卡片作废
#define TC_CARDCHANGE   	2130 //卡片交接
#define TCM_CARDBAD			2140 //坏卡登记
#define TC_CARDQRY   		2154 //卡片查询

#define TC_AUTHCARDOPEN		2200 //授权卡发行
#define TC_AUTHCARDCLOSE	2210 //授权卡回收
#define TC_AUTHCARDLOSS		2220 //授权卡挂失
#define TC_AUTHCARDUNLOSS	2230 //授权卡解挂
#define TC_AUTHCARDUPD		2240 //授权卡更新
#define TC_AUTHCARDQRY		2254 //授权卡查询

#define TC_CARDOPEN			3000  //卡片开户
#define TC_CARDOPENREV		3001  //卡片开户冲正
#define TC_CARDCLOSE		3010  //卡片销户
#define TC_CARDRENEW		3020  //卡补办
#define TC_CARDRETURN		3030  //卡回收
#define TC_CARDLOSS			3040  //卡挂失
#define TC_CARDUNLOSS   	3050  //卡解挂
#define TC_CARDFROZE		3060  //卡冻结
#define TC_CARDUNFROZE  	3070  //卡解冻
#define TC_CARDUPDBASEINFO	3080  //更新卡基本信息
#define TC_CARDUPDEXPIREDATE 3081  //更新卡有效期
#define TC_CARDUPDBADCARD	3082 //坏卡修复
#define TC_CARDREWRITE		3083 //重写卡信息
#define TC_CARDCLEAR 		3084 // 清空卡信息
#define TC_CARDSAVEINFO		3090 //换卡保存卡信息
#define TC_CARDINSTEAD		3091 //换卡
#define TC_CARDINSTEADREV	3092 //换卡撤销

#define TC_CARDDEPOSIT  	3100  //卡充值
#define TC_CARDDEPOSITREV 	3101 //卡充值冲正
#define TC_CARDDRAW  		3110  //卡支取
#define TC_SUBSIDYIMP		3121  //补助导入
#define TC_SUBSIDYDEL		3122  //补助删除
#define TC_SUBSIDYUPD		3123  //补助修改
#define TC_SUBSIDYQRY		3124  //补助查询
#define TC_SUBSIDYPUT		3130  //补助下发
#define TC_POSDEPOSIT 		3140  //POS充值
#define TC_POSDEPOSITREV 	3141  //POS充值冲正
#define TC_SHOPPOSDEPOSIT  	3150  //充值商户POS充值
#define TC_SHOPPOSDEPOSITREV  3151  //充值商户POS充值冲正
#define TC_POSDRAW  		3160  //POS消费
#define TC_POSDRAWREV  		3161  //POS消费冲正
#define TC_BANKTRANS		3170  //圈存转账
#define TC_CARDPAYMENT		3180  //卡支付交易
#define TC_CARDPWDUPD		3200  //卡密码修改
#define TC_CARDPWDRESET		3210  //卡密码重置
#define TC_SUBSIDYGET		3220  //补助领取
#define TC_CARD2CARTRANS	3230  //卡卡转账(旧卡到新卡)
#define TC_CARDBALMOD		3240  //卡余额调整

#define TC_TRANSREV			4000  	//冲账交易
#define TC_CARDACCDIFF		4001  	//卡库不平

#define TC_SHOPOPEN			5001	//商户开户
#define TC_SHOPCLOSE		5002	//商户销户
#define TC_SHOPUPD			5003	//商户信息修改
#define TC_SHOPQRY      	5004	//商户信息查询
#define TC_SHOPSAVING 		5010    //商户存款

#define TC_EACCOPEN			6000  	//电子钱包开户
#define TC_EACCCLOSE		6010  	//电子钱包销户
#define TC_EACCDEPOSIT		6020  	//电子钱包充值
#define TC_EACCDRAW			6030  	//电子钱包取款
#define TC_CARD2EACC		6040	//卡到电子钱包转帐
#define TC_EACC2CARD		6050	//电子钱包到卡转帐
#define TC_BANK2EACC		6060	//银行卡到电子钱包转帐
#define TC_EACCSTOPPAY		6070  	//电子钱包止付
#define TC_EACCUNSTOPPAY 	6080  	//电子钱包解付
#define TC_EACCQRY		 	6094	//电子钱包信息查询
#define TC_EACCPWDUPD 	 	6100  	//电子钱包密码修改
#define TC_EACCPWDRESET  	6110  	//电子钱包密码重置
#define TC_EACCLOGIN		6200	//电子钱包支付系统签到
#define TC_EACCQRYBAL		6210	//电子钱包余额查询
#define TC_EACCFROZE		6220	//电子钱包冻结
#define TC_EACC2SHOP		6230	//电子钱包支付
#define TC_EACC2SHOPREV		6240	//电子钱包支付冲正
#define TC_MANUALDRCR	 	7000  	//手工借贷
#define TC_SHOPPAYMENT   	8000   	//商户解款

#endif /* TRANSCODE_H */
