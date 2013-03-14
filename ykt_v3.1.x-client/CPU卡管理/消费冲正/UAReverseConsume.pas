unit UAReverseConsume;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus, RzPanel;

type
  TfaqhReverseConsume = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    edtSeriNo: TWVEdit;
    WVEdit6: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnReverse: TBitBtn;
    btnReadCard: TBitBtn;
    WVReserveConsume: TWorkView;
    WVRReserveConsume: TWVRequest;
    Label14: TLabel;
    Label13: TLabel;
    edtPwd: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    cbbErrOperNo: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReverseClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhReverseConsume: TfaqhReverseConsume;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhReverseConsume.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhReverseConsume.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhReverseConsume.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('查询类型').Data.SetString('3');
  btnReverse.Enabled := False;
  inherited;
  btnReverse.Enabled := True;
end;

procedure TfaqhReverseConsume.btnReverseClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  operDate:string;
  seriId:Integer;
  stationId:Integer;
  cardId:Integer;
  outMoney:Integer;
  balance:Integer;
  CardPhyID:string;
  cm:TCM;
  payCnt,dptCnt:Integer;
  tp:TTRANSPACK;
  tradeDate,tradeTime:string;
  st:Integer;
  operCode:string;
  operPwd:string;
  subsidyNo:Integer;
  phyId:string;
begin
  if preReadCard=False then
    Exit;
  if Application.MessageBox('如果要冲正该记录，请把卡放置到读写器上，确定要冲正吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  operDate := tmpDataSet.fieldbyname('sdate3').AsString;
  seriId := tmpDataSet.fieldbyname('lserial1').AsInteger;
  stationId := tmpDataSet.fieldbyname('lwithdraw_flag').AsInteger;

  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    {
    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PATCH_NO);
    }
    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
      Exit;
    end;
    //读取物理卡号
    CardPhyID := cm.getCardSeriNo;
    if CardPhyID='' then
    begin
      Context.GetDialogSystem.ShowMessage('读取物理卡号失败！');
      Exit;
    end;
    //交易次数
    try
      //tradeNum:=StrToInt(cm.getCardCnt);
      balance := StrToInt(cm.getCardBalance);
      payCnt := StrToInt(cm.getPayCardCnt);
      dptCnt := StrToInt(cm.getDptCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('读取卡消费次数失败，操作取消--'+e.Message);
        Exit;
      end;
    end;

    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    WVReserveConsume.FieldByName('操作员密码').Data.SetString(operPwd);
    WVReserveConsume.FieldByName('物理卡号').Data.SetString(CardPhyID);
    WVReserveConsume.FieldByName('卡号').Data.SetInteger(StrToInt(cm.getCardNo));
    WVReserveConsume.FieldByName('业务日期').Data.SetString(operDate);
    WVReserveConsume.FieldByName('流水号').Data.SetInteger(seriId);
    WVReserveConsume.FieldByName('终端编号').Data.SetInteger(stationId);
    WVReserveConsume.FieldByName('入卡值').Data.SetInteger(balance);
    WVReserveConsume.FieldByName('充值次数').Data.SetInteger(dptCnt);
    WVReserveConsume.FieldByName('卡交易次数').Data.SetInteger(payCnt);
    WVRReserveConsume.SendCommand;
    cardId := WVReserveConsume.FieldByName('卡号').Data.AsInteger;
    outMoney := WVReserveConsume.Fieldbyname('出卡值').Data.AsInteger;
    tradeDate := WVReserveConsume.fieldbyname('业务日期').Data.AsString;
    tradeTime := WVReserveConsume.fieldbyname('业务时间').Data.AsString;
    if cardId<>StrToInt(cm.getCardNo) then
    begin
      Context.GetDialogSystem.ShowMessage('你要冲正的卡和放置的卡不是同一张卡，请重新操作');
      Exit;
    end;
    try
      //preSetMoney(tp);
      ZeroMemory(@tp,SizeOf(tp));
      //终端交易序列号
      tp.TermSeqno := 1;
      //终端编号
      StrCopy(@tp.Termno,PChar(scSiteNo));
      //交易卡号
      tp.CardNo := StrToInt(cm.getCardNo);
      //物理编号
      StrCopy(@tp.CardPhyID,PChar(cm.getCardSeriNo));
      //交易日期
      StrCopy(@tp.TransDate,PChar(tradeDate));
      //交易时间
      StrCopy(@tp.TransTime,PChar(tradeTime));
      //交易前金额
      tp.BefBalance := balance;
      //交易后金额
      tp.AftBalance := outMoney;
      //交易前充值次数
      tp.DptCardCnt := dptCnt;
      //交易前消费次数
      tp.PayCardCnt := payCnt;
      //补助批次号
      tp.SubsidyNo := subsidyNo;
      st := ks_setcardbal(@tp);
      if st <>0 then
        Context.GetDialogSystem.ShowMessage('在冲正时没有写卡信息，请重新执行冲正交易'+inttostr(st))
      else
        cm.beep;
      RzStatusPane1.Caption := WVReserveConsume.fieldbyname('返回信息').Data.AsString;
      btnQuery.Click;
    except
      Context.GetDialogSystem.ShowMessage('在冲正时没有写卡信息，请重新执行冲正交易！');
    end;
  finally
    cm.Destroy;
  end;
  edtPwd.Text := '';
end;

procedure TfaqhReverseConsume.btnReadCardClick(Sender: TObject);
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

initialization
  TUIStdClassFactory.Create('消费冲正',TfaqhReverseConsume);

end.