unit UASmlTradeRcv;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,WaterDll;

type
  TfaqhSmlTradeRcv = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    edtSeriNo: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnReadCard: TBitBtn;
    Label13: TLabel;
    edtTBDate: TWVEdit;
    Label14: TLabel;
    edtTEDate: TWVEdit;
    Label15: TLabel;
    cbbNetConn: TWVComboBox;
    Label16: TLabel;
    edtBTime: TWVEdit;
    Label17: TLabel;
    edtEtime: TWVEdit;
    lbl1: TLabel;
    cbb1: TWVComboBox;
    Label18: TLabel;
    WVComboBox5: TWVComboBox;
    WVRSerialRcv: TWVRequest;
    WVSerialRcv: TWorkView;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSmlTradeRcv: TfaqhSmlTradeRcv;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhSmlTradeRcv.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
  btnPrint.Caption :='冲  正';
end;

procedure TfaqhSmlTradeRcv.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('记账开始日期输入不正确，格式：yyyymmdd');
      edtbdate.SetFocus;
      Exit;
    end;
  if Trim(edtEDate.Text)<>'' then
    if CheckInputDateFormat(edtEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('记账开始日期输入不正确，格式：yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if (Trim(edtBDate.Text)<>'') and (Trim(edtEDate.Text)<>'') then

  if Trim(edtBDate.Text)>Trim(edtEDate.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('记账开始日期不能大于结束日期，请重新输入！');
    edtBDate.SetFocus;
    Exit;
  end;

  if Trim(edtTBDate.Text)<>'' then
    if CheckInputDateFormat(edtTBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('交易开始日期输入不正确，格式：yyyymmdd');
      edtTBDate.SetFocus;
      Exit;
    end;
  if Trim(edtTEDate.Text)<>'' then
    if CheckInputDateFormat(edtTEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('交易开始日期输入不正确，格式：yyyymmdd');
      edtTEDate.SetFocus;
      Exit;
    end;
  if (Trim(edtBDate.Text)<>'') and (Trim(edtEDate.Text)<>'') then

  if Trim(edttBDate.Text)>Trim(edttEDate.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('交易开始日期不能大于结束日期，请重新输入！');
    edttBDate.SetFocus;
    Exit;
  end;
  if Trim(edtBTime.Text)<>'' then
    if CheckInputTimeFormat(edtBTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始时间输入不正确，请重新输入！');
      edtBTime.SetFocus;
      Exit;
    end;
  if Trim(edteTime.Text)<>'' then
    if CheckInputTimeFormat(edteTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('结束时间输入不正确，请重新输入！');
      edteTime.SetFocus;
      Exit;
    end;
  if Trim(edtBTime.Text)>Trim(edtEtime.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('开始时间不能大于结束时间，请重新输入！');
    edtBTime.SetFocus;
    Exit;
  end;


  WorkView.FieldByName('钱包号').Data.SetInteger(0);
  //WorkView.FieldByName('联机状态').Data.SetInteger(33);
  inherited;

end;

procedure TfaqhSmlTradeRcv.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtCardNo.Text:='0';
  cardNo := readCardOneInfo(CARD_NO);
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，卡号为零或不存在!');
    Exit;
  end;
  edtCardNo.Text:=cardNo;
  btnQuery.Click;
end;

procedure TfaqhSmlTradeRcv.btnPrintClick(Sender: TObject);
var
  tmpData:TDataSet;
  siteNo,serialNo,custId,cardNo:Integer;
  tradeDate,tradeTime:string;
  tradeAmt:Double;
  smlBal:Integer;
  st:Integer;
  phyId:string;

  //cardno : Integer;                   //交易卡号
  custno : Integer;                   //客户号
  custtype : Integer;                 //客户类别
  expireddate : string;  //有效期
  lockflag : Integer;                 //锁定标志，00 锁定，FF可用
  //钱包信息
  totalmoney : Integer;               //充值总金额
  addtime : string;                   //充值时间
  addcount : Integer;                 //充值次数
  nprice1 : Integer;                   //水价1
  nprice2 : Integer;                   //水价2
  nprice3 : Integer;                   //水价3
  waterPack:TWATERCOMMPACK;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  smlbgNo:Integer;

begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  try
    tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
    siteNo := tmpData.FieldByName('lwithdraw_flag').AsInteger;
    serialNo := tmpData.fieldbyname('lserial1').AsInteger;
    custId := tmpData.FieldByName('lvol1').AsInteger;
    cardNo := tmpData.FieldByName('lvol0').AsInteger;
    tradeDate := tmpData.fieldbyname('sdate0').AsString;
    tradeTime := tmpData.fieldbyname('stime0').AsString;
    tradeAmt := tmpData.fieldbyname('damt0').AsFloat;
    smlbgNo := tmpData.FieldByName('lvol3').AsInteger;
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(ex.Message);
      Exit;
    end;
  end;
  WVSerialRcv.FieldByName('终端编号').Data.SetInteger(siteNo);
  WVSerialRcv.FieldByName('终端流水号').Data.SetInteger(serialNo);
  WVSerialRcv.FieldByName('客户号').Data.SetInteger(custId);
  WVSerialRcv.FieldByName('卡号').Data.SetInteger(cardNo);
  WVSerialRcv.FieldByName('交易日期').Data.SetString(tradeDate);
  WVSerialRcv.FieldByName('交易时间').Data.SetString(tradeTime);
  WVSerialRcv.FieldByName('交易金额').Data.SetFloat(tradeAmt);
  WVRSerialRcv.SendCommand;
  if (WVSerialRcv.FieldByName('返回码').Data.AsString<>'0')then
  begin
    Context.GetDialogSystem.ShowMessage(WVSerialRcv.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  smlBal :=WVSerialRcv.FieldByName('小钱包余额').Data.AsInteger;

  //读小钱包信息
  st := mfcard(phyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('水控钱包寻卡失败--'+inttostr(st));
    Exit;
  end;
  preCommWaterPack(waterPack);
  st := ks_water_readmoney(smlbgNo,@waterpack);
  reSt := ks_geterrmsg(PChar(@reErrMsg));
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('读取小钱包失败,该钱包已经回收-'+reSt+inttostr(st));
    Exit;
  end;
  cardno := waterPack.cardno;                     //交易卡号
  custno := waterPack.custno;                     //客户号
  custtype := waterPack.custtype;                 //客户类别
  expireddate := waterPack.expireddate;           //有效期
  lockflag := waterPack.lockflag;                 //锁定标志，00 锁定，FF可用
  // 钱包信息
  //money := waterPack.money;                       //卡余额
  totalmoney := waterPack.totalmoney;             //充值总金额
  addtime := waterPack.addtime;                   //充值时间
  addcount := waterPack.addcount;                 //充值次数

  nprice1 := waterPack.price1;                     //水价1
  nprice2 := waterPack.price2;                     //水价2
  nprice3 := waterPack.price3;                     //水价3
  preCommWaterPack(waterPack);
  //设置小钱包结构体
  waterPack.cardno := cardno;
  waterPack.custno := custno;
  waterPack.custtype := custtype;
  StrCopy(@waterPack.expireddate,PChar(FormatDateTime('yyyymmdd',Date+waterExpiredate)));
  //ShowMessage(waterPack.expireddate);
  waterPack.lockflag := lockflag;
  waterPack.money := smlBal;
  waterPack.totalmoney := totalmoney+smlbal;
  StrCopy(@waterPack.addtime,PChar(addtime));
  waterPack.addcount := addcount+1;
  waterPack.price1 := nprice1;
  waterPack.price2 := nprice2;
  waterPack.price3 := nprice3;
  //ShowMessage(IntToStr(waterPack.money));
  st := ks_water_writemoney(smlbgNo,@waterPack);

  if st = 0 then
  begin
    KNG_beep;
    Context.GetDialogSystem.ShowMessage('小钱包冲正成功！');
  end
  else
    Context.GetDialogSystem.ShowMessage('写水控钱包失败，请到冲正界面冲正该交易--'+inttostr(st));
end;

initialization
  TUIStdClassFactory.Create('小钱包流水冲正',TfaqhSmlTradeRcv);

end.