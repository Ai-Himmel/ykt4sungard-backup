unit WaterDll;

interface
uses
  Windows, Messages, SysUtils, Classes, Dialogs,KSFrameWorks,WorkViews,WVCmdReq,KSClientConsts;
const
  //****************************************************************************
  //��̬�ⶨ��
  CARD_DLL ='kscard.dll';
  KS_SZROAD_WATER = 1;  // ��·ˮ��
  KS_YNCS_XT_WATER = 2; // �ƽ�ְˮ��
  KS_HD_WATER = 3;      // ����ѻ�ˮ��


type
  //���ڿ�·ˮ�����
  TWATERPACK = packed record
    money : Integer;                    //�������
    pre_money : Integer;                //�ϴ����Ѷ�
    add_time : array[0..14] of Char;    //�ϴγ�ֵʱ��
    add_count : Integer;                //��ֵ����
  end;
  PWATERPACK = ^TWATERPACK;
  
  TWATERINFO = packed record
	  cardno : Integer;                   //���׿���
    cardtype : Integer;                 //�����
    custno : Integer;                   //�ͻ���
  end;
  PWATERINFO = ^TWATERINFO;

  //ˮ��ͨ�ýṹ��
  TWATERCOMMPACK = packed record
    cardno : Integer;                   //���׿���
    custno : Integer;                   //�ͻ���
    custtype : Integer;                 //�ͻ����
    expireddate : array[0..8] of Char;  //��Ч��
    lockflag : Integer;                 //������־��00 ������FF����
    // Ǯ����Ϣ
    money : Integer;                    //�����
    totalmoney : Integer;               //��ֵ�ܽ��
    addtime : array[0..14] of Char;     //��ֵʱ��
    addcount : Integer;                 //��ֵ����
    price1 : Integer;                   //ˮ��1
    price2 : Integer;                   //ˮ��2
    price3 : Integer;                   //ˮ��3

  end;
  PWATERCOMMPACK = ^TWATERCOMMPACK;

  TWATERPARAM = packed record
    sWorkKey : array[1..17] of Char ;	  //������Կ = (0x01,0x02,0x03,0x04,0x05,0x06)
    iMinMoney : Integer;				        //��Ǯ��Ԥ�����
    iMaxMoney : Integer;				        //��Ǯ���������
    iUnit : Integer;					          //�Ʒѵ�λ
    iTransMone : Integer;				        //����ת�˽��
    iUnitMoney : Integer;				        //����
    iPpriceIndex : Integer;				      //ˮ������ 1
    iWaterSect : Integer;				        //ˮ��Ǯ����
    iCardFlag : Integer;				        //��������־������0������1���㿨��
    iTermId : Integer;					        //�ն˺�
  end;
  PWATERPARAM = ^TWATERPARAM;

//ˮ����ض���ṹ��------------------------------------------------------------
// ��ǰȨ�޵ķ��ʸ���
type
  TFeeRate = packed record
  time_ladder :Byte ;				                              // ʱ�����
	deduct_time :Byte ;				                              // �۷ѵĵ�λʱ�䣬����Ϊ��λ
	deduct_fee :Byte ;				                              // �۷ѵĵ�λ���Է�Ϊ��λ
  end;


// ��ǰȨ�޵ķ��ʸ���
  TFeeRightNo = packed record
	right_flag : SHORT;					                            // Ȩ�ޱ�־, 1��, 0�ر�
	right_num : SHORT;					                            // ���뵱ǰȨ���µķ��ʸ���
	fee_rate : array[1..5] of TFeeRate;				              // �������Ϊ5��
  end;
  
// ���ʿ��ṹ˵��
  TFeeRateCardInfo = packed record
	water_card_flag : array[1..5] of Byte;			            // ˮ�ؿ���־
	packet_num : Char;					                            // ˮ��Ǯ����
	main_work_key : array[1..9] of Byte;			              // ��������Կ(����)
	packet_work_key : array[1..9] of Byte;			            // СǮ��������Կ(����)
  work_model:Byte;                                        // ����ģʽ
  water_packet_limit : Integer;				                    // ˮ��Ǯ���޶�-----
	transfer_limit : Integer;					                      // ˮ��ת���޶�-----
	data_length : array[1..3] of Byte;				              // ���ݳ���
	check_crc : array[1..2] of Byte;				                // Ч���ֽ�
	fee_right_num : array[1..256] of TFeeRightNo;	          // ���÷��ʵĸ���
  end;
  PFeeRateCardInfo = ^TFeeRateCardInfo;

  Tcollect_balance = packed record
  devId :array[1..9] of Char;
  sum_balance :Double;
  end;
  Pcollect_balance = ^Tcollect_balance;
//ˮ�ؽṹ�嶨�����end---------------------------------------------------------

  
//����ˮ�ؿ�
function ks_sr_publishcard(waterInfo:PWATERINFO):Integer;
  stdcall;far; external CARD_DLL name 'ks_sr_publishcard';
//����ˮ�ؿ�
function ks_sr_recyclecard():Integer;
  stdcall;far; external CARD_DLL name 'ks_sr_recyclecard';
//��ȡˮ�����
function ks_sr_readmoney(waterPack:PWATERPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_sr_readmoney';
//����ˮ�����
function ks_sr_setmoeny(money,cnt:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_sr_setmoeny';


//ͨ��ˮ�ؿ��������------------------------------------------------------------
//����ˮ�ؿ�
function ks_water_publishcard(watertype:Integer;ks_water_pack_t:PWATERCOMMPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_publishcard';
//����ˮ�ؿ�
function ks_water_recyclecard(watertype:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_recyclecard';
//��ȡˮ�ؿ�
function ks_water_readmoney(watertype:Integer;ks_water_pack_t:PWATERCOMMPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_readmoney';
//д��ˮ�ؿ�
function ks_water_writemoney(watertype:Integer;ks_water_pack_t:PWATERCOMMPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_writemoney';

//ˮ�ع�������
function ks_water_publish_legacycard(watertype:Integer;ks_water_param_t:PWATERPARAM):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_publish_legacycard';
//ˮ�ع�����ȡ
function ks_water_read_legacycard(watertype:Integer;ks_water_param_t:PWATERPARAM):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_read_legacycard';

//ˮ�ع�������
function ks_water_publishparamcard(watertype:Integer;ks_water_param_t:PWATERPARAM):Integer;
  stdcall;far; external CARD_DLL name 'ks_water_publishparamcard';
//ˮ�ع�������
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
    Fcardno : Integer;                   //���׿���
    Fcustno : Integer;                   //�ͻ���
    Fcusttype : Integer;                 //�ͻ����
    Fexpireddate : string;               //��Ч��
    Flockflag : Integer;                 //������־��00 ������FF����
    // Ǯ����Ϣ
    Fmoney : Integer;                    //�����
    Ftotalmoney : Integer;               //��ֵ�ܽ��
    Faddtime : string;                   //��ֵʱ��
    Faddcount : Integer;                 //��ֵ����
    Fprice1 : Integer;                   //ˮ��1
    Fprice2 : Integer;                   //ˮ��2
    Fprice3 : Integer;                   //ˮ��3

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
