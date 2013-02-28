#ifndef TRANSCODE_H
#define TRANSCODE_H

#define TC_DICTADD			1000	//数据字典增加
#define TC_DICTDEL			1010	//数据字典删除
#define TC_DICTUPD			1020	//数据字典修改

#define TC_PARAMADD			1030	//全局参数添加
#define TC_PARAMDEL			1040	//全局参数删除
#define TC_PARAMUPD			1050	//全局参数修改

#define TC_CARDTYPEADD 		1090	//卡类别添加
#define TC_CARDTYPEDEL 		1100	//卡类别删除
#define TC_CARDTYPEUPD 		1110	//卡类别修改

#define TC_AUTHTPLADD  		1120	//权限模板添加
#define TC_AUTHTPLDEL  		1130	//权限模板删除
#define TC_AUTHTPLUPD  		1140	//权限模板修改

#define TC_BRANCHADD		1150	//网点注册
#define TC_BRANCHDEL		1160	//网点注销
#define TC_BRANCHUPD		1170	//网点修改

#define TC_SITEADD			1180	//站点注册
#define TC_SITEDEL			1190	//站点注销
#define TC_SITEUPD			1200	//站点修改

#define TC_SUBSYSADD		1210	//子系统注册
#define TC_SUBSYSDEL		1220	//子系统注销
#define TC_SUBSYSUPD		1230	//子系统修改

#define TC_DEVICEADD			1240	//设备添加
#define TC_DEVICEDEL			1250	//设备删除
#define TC_DEVICEUPD			1260	//设备修改

#define TC_DEVMAIN			1270	//设备维修
#define TC_DEVDISCARD		1280	//设备报废
#define TC_DEVREUSE			1290	//设备重用


#define TC_OPERADD			1300	//操作员注册
#define TC_OPERDEL			1310	//操作员注销
#define TC_OPERUPD			1320	//操作员修改

#define TC_OPERPWDUPD 		1330	//操作员密码修改
#define TC_OPERPWDRESET 	1340	//操作员密码重置

#define TC_OPERSITEADD		1350	//操作员站点添加
#define TC_OPERSITEDEL		1360	//操作员站点删除
#define TC_OPERSITEUPD		1370	//操作员站点修改

#define TC_OPERAUTHADD		1400	//操作员权限增加
#define TC_OPERAUTHDEL		1410	//操作员权限删除

#define TC_CUSTAPPLYADD		2000	//新莞人信息录入
#define TC_CUSTAPPLYDEL		2010	//新莞人信息删除
#define TC_CUSTAPPLYUPD		2020	//新莞人信息修改
#define TC_CARDNOGEN		2030	//非实名卡号生成
#define TC_MAKECARDAPROVE	2040	//制卡名单审核
#define TC_IMPMAKECARDDATA	2050	//导入制卡数据
#define TC_PRINTCARDAPROVE	2060	//二次制卡名单审核
#define TC_IMPMOBILE			2070	//导入手机号
#define TC_CARDINFOUPD		2080 //卡信息修改

#define TC_OPENCARDAPPLY	2100	//办卡申请
#define TC_CHANGECARDAPPLY	2110	//换卡申请
#define TC_RENEWCARDAPPLY	2120	//补办申请
#define TC_CLOSECARDAPPLY	2130	//销户申请
#define TC_APPLYCANCEL		2140	//申请撤销

#define TC_CARDOPEN			2200  //卡开户
#define TC_CARDINSTEAD		2210  //换卡
#define TC_CARDRENEW		2220  //补办
#define TC_CARDCLOSE		2230  //销户
#define TC_CARDLOSS			2240  //卡挂失
#define TC_CARDUNLOSS   		2250  //卡解挂
#define TC_CARDFROZE		2260  //卡冻结
#define TC_CARDUNFROZE  		2270  //卡解冻

#define TC_CARDPWDUPD		2300  //卡密码修改
#define TC_CARDPWDRESET		2310  //卡密码重置
#define TC_CARDBALMOD		2320  //卡余额调整
#define TC_CARDBALUPD		2330  //卡余额修正


#define TC_SELLCARD			3000	//发售非实名卡
#define TC_ISSUECARD			3010	//发放实名卡
#define TC_PREPAID			3020	//收卡成本费
#define TC_ISSUEDPS			3030	//发卡充值

//#define TC_CARDDPSATM  		3100  //自助现金充值/回退
#define TC_CARDDPSCASH  		3100  //现金充值/回退
#define TC_CARDDPSBANK  		3110  //银行卡充值/回退
#define TC_CARDDPSBILL		3120  //支票充值/回退
#define TC_BANKTRANS		3200  //圈存转账

#define TC_CARDPAYMENT		3300  //卡支付交易

#define TC_POSPAY  			3400  //POS消费/冲正
#define TC_ONLINEPAY		3410	//联机消费
#define TC_LOSTPAY			3500	//挂失消费
#define TC_CLOSEPAY			3510	//注销消费
#define TC_PAYREPEAT        		3520	//脱机重复消费

#define TC_POSLOCKCARD		3600	//POS锁卡
#define TC_CONSUMEFAIL		3700	//消费失败
#define TC_CARD2CARD		3800 //余额转移
#define TC_TRANSREV			3900	 //交易冲正
#define TC_MERCHOPEN		4000	//商户开户
#define TC_MERCHCLOSE		4010	//商户销户
#define TC_MERCHUPD			4020	//商户信息修改

#define TC_MERCHDEVADD		4100	//商户设备添加
#define TC_MERCHDEVUPD		4120	//商户设备修改
#define TC_MERCHDEVDEL		4130	//商户设备删除


#define TC_SHOPSAVING 		4200    //商户存款
#define TC_SHOPPOSDEPOSIT  	4210  //充值商户POS充值/冲正


#define TC_PKGDEL			4310 //删除包裹单
#define TC_PKGUPD			4320 //修改包裹单

#define TC_PKGFILEDEL		4410 //删除包裹文件
#define TC_PKGFILEUPD		4420 //修改包裹文件


#define TC_SUBJADD			5000	//科目添加
#define TC_SUBJDEL			5010	//科目删除
#define TC_SUBJUPD			5020	//科目修改


#define TC_VOUCHERMAKE		6000	//凭证录入
#define TC_VOUCHERUPD		6010	//凭证修改
#define TC_VOUCHERDEL		6020	//凭证删除
#define TC_VOUCHERSIGN		6030	//凭证签字
#define TC_VOUCHERCHECK		6040	//凭证复核
#define TC_VOUCHERCHECKREV	6050	//凭证复核取消
#define TC_VOUCHERBOOK		6060	//凭证入账
#define TC_VOUCHERBOOKREV	6070	//凭证冲销

#define TC_DAYEND			7000	//日终结算
#define TC_MONTHEND			7010	//期末结转
#define TC_YEAREND			7020	//年终结转

#endif /* TRANSCODE_H */
