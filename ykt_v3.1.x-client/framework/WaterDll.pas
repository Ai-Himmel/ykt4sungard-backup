unit WaterDll;

interface
uses
  Windows, Messages, SysUtils, Classes, Dialogs,KSFrameWorks,WorkViews,WVCmdReq,KSClientConsts;
const
  //****************************************************************************
  //动态库定义
  CARD_DLL ='kscard.dll';
  KS_SZROAD_WATER = 1;  // 凯路水控
  KS_YNCS_XT_WATER = 2; // 云交职水控
  KS_HD_WATER = 3;      // 汇多脱机水控


type
  //深圳凯路水控相关
  TWATERPACK = packed record
    money : Integer;                    //卡上余额
    pre_money : Integer;                //上次消费额
    add_time : array[0..14] of Char;    //上次充值时间
    add_count : Integer;                //充值次数
  end;
  PWATERPACK = ^TWATERPACK;
  
  TWATERINFO = packed record
	  cardno : Integer;                   //交易卡号
    cardtype : Integer;                 //卡类别
    custno : Integer;                   //客户号
  end;
  PWATERINFO = ^TWATERINFO;

  //水控通用结构体
  TWATERCOMMPACK = packed record
    cardno : Integer;                   //交易卡号
    custno : Integer;                   //客户号
    custtype : Integer;                 //客户类别
    expireddate : array[0..8] of Char;  //有效期
    lockflag : Integer;                 //锁定标志，00 锁定，FF可用
    // 钱包信息
    money : Integer;                    //卡余额
    totalmoney : Integer;               //充值总金额
    addtime : array[0..14] of Char;     //充值时间
    addcount : Integer;                 //充值次数
    price1 : Integer;                   //水价1
    price2 : Integer;                   //水价2
    price3 : Integer;                   //水价3

  end;
  PWATERCOMMPACK = ^TWATERCOMMPACK;

  TWATERPARAM = packed record
    sWorkKey : array[1..17] of Char ;	  //种子密钥 = (0x01,0x02,0x03,0x04,0x05,0x06)
    iMinMoney : Integer;				        //卡钱包预警金额
    iMaxMoney : Integer;				        //卡钱包金额上线
    iUnit : Integer;					          //计费单位
    iTransMone : Integer;				        //单次转账金额
    iUnitMoney : Integer;				        //单价
    iPpriceIndex : Integer;				      //水价索引 1
    iWaterSect : Integer;				        //水控钱包号
    iCardFlag : Integer;				        //参数卡标志，新天0参数，1清零卡，
    iTermId : Integer;					        //终端号
  end;
  PWATERPARAM = ^TWATERPARAM;

//水控相关定义结构体------------------------------------------------------------
// 当前权限的费率个数
type
  TFeeRate = packed record
  time_ladder :Byte ;				                              // 时间阶梯
	deduct_time :Byte ;				                              // 扣费的单位时间，以秒为单位
	deduct_fee :Byte ;				                              // 扣费的单位金额，以分为单位
  end;


// 当前权限的费率个数
  TFeeRightNo = packed record
	right_flag : SHORT;					                            // 权限标志, 1打开, 0关闭
	right_num : SHORT;					                            // 传入当前权限下的费率个数
	fee_rate : array[1..5] of TFeeRate;				              // 最大设置为5个
  end;
  
// 费率卡结构说明
  TFeeRateCardInfo = packed record
	water_card_flag : array[1..5] of Byte;			            // 水控卡标志
	packet_num : Char;					                            // 水控钱包号
	main_work_key : array[1..9] of Byte;			              // 主工作密钥(明文)
	packet_work_key : array[1..9] of Byte;			            // 小钱包工作密钥(明文)
  work_model:Byte;                                        // 工作模式
  water_packet_limit : Integer;				                    // 水控钱包限额-----
	transfer_limit : Integer;					                      // 水控转账限额-----
	data_length : array[1..3] of Byte;				              // 数据长度
	check_crc : array[1..2] of Byte;				                // 效验字节
	fee_right_num : array[1..256] of TFeeRightNo;	          // 设置费率的个数
  end;
  PFeeRateCardInfo = ^TFeeRateCardInfo;

  Tcollect_balance = packed record
  devId :array[1..9] of Char;
  sum_balance :Double;
  end;
  Pcollect_balance = ^Tcollect_balance;
//水控结构体定义相关end---------------------------------------------------------

  
//发行水控卡
function ks_sr_publishcard(waterInfo:PWATERINFO):Integer;
  stdcall;far; external CARD_DLL name 'ks_sr_publishcard';
//回收水控卡
function ks_sr_recyclecard():Integer;
  stdcall;far; external CARD_DLL name 'ks_sr_recyclecard';
//读取水控余额
function ks_sr_readmoney(waterPack:PWATERPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_sr_readmoney';
//设置水控余额
function ks_sr_setmoeny(money,cnt:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_sr_setmoeny';


//通用水控卡操作相关------------------------------------------------------------
//发行水控卡
function ks_water_publishcard(watertype:Integer;ks_water_pack_t:PWATERCOMMPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_publishcard';
//回收水控卡
function ks_water_recyclecard(watertype:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_recyclecard';
//读取水控卡
function ks_water_readmoney(watertype:Integer;ks_water_pack_t:PWATERCOMMPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_readmoney';
//写入水控卡
function ks_water_writemoney(watertype:Integer;ks_water_pack_t:PWATERCOMMPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_writemoney';

//水控管理卡发行
function ks_water_publish_legacycard(watertype:Integer;ks_water_param_t:PWATERPARAM):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_publish_legacycard';
//水控管理卡读取
function ks_water_read_legacycard(watertype:Integer;ks_water_param_t:PWATERPARAM):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_read_legacycard';

//水控管理卡发行
function ks_water_publishparamcard(watertype:Integer;ks_water_param_t:PWATERPARAM):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_publishparamcard';
//水控管理卡回收
function ks_water_recycleparamcard(watertype:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_recycleparamcard';

function ks_water_readparamcard(watertype:Integer;ks_water_param_t:PWATERPARAM):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_readparamcard';
//------------------------------------------------------------------------------

procedure preReadWaterPack(waterPack:TWATERPACK);
procedure preCommWaterPack(waterPack:TWATERCOMMPACK);

type
  TWaterOper = class
  private
    Fcardno : Integer;                   //交易卡号
    Fcustno : Integer;                   //客户号
    Fcusttype : Integer;                 //客户类别
    Fexpireddate : string;               //有效期
    Flockflag : Integer;                 //锁定标志，00 锁定，FF可用
    // 钱包信息
    Fmoney : Integer;                    //卡余额
    Ftotalmoney : Integer;               //充值总金额
    Faddtime : string;                   //充值时间
    Faddcount : Integer;                 //充值次数
    Fprice1 : Integer;                   //水价1
    Fprice2 : Integer;                   //水价2
    Fprice3 : Integer;                   //水价3

  public
    //function waterWriteMoney():Integer;
  end; 

implementation

procedure preReadWaterPack(waterPack:TWATERPACK);
begin
  ZeroMemory(@waterPack,SizeOf(waterPack));
  //FillChar(waterPack.add_time,SizeOf(waterPack.add_time),0);
end;

procedure preCommWaterPack(waterPack:TWATERCOMMPACK);
begin
  ZeroMemory(@waterPack,SizeOf(waterPack));
  //FillChar(waterPack.expireddate,SizeOf(waterPack.expireddate),0);
  //FillChar(waterPack.addtime,SizeOf(waterPack.addtime),0);
end;

end.
