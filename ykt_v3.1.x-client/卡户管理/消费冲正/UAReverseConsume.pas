unit UAReverseConsume;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,UtCardDll,
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
var
  strDate:string;
begin
  inherited;
  //strDate := FormatDateTime('yyyymmdd',Date);
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
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
  CardManage : TCardManage;
  cardId:Integer;
  outMoney:Integer;
  tradeNum:Integer;
  balance:Integer;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  CardPhyID:string;
  operCode:string;
  operPwd:string;
begin
  if PrepareReadCardInfo=False then
    Exit;
  if Application.MessageBox('如果要冲正该记录，请把卡放置到读写器上，确定要冲正吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  operDate := tmpDataSet.fieldbyname('sdate3').AsString;
  seriId := tmpDataSet.fieldbyname('lserial1').AsInteger;
  stationId := tmpDataSet.fieldbyname('lwithdraw_flag').AsInteger;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //读取物理卡号
    CardPhyID := '';
    if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取物理卡号失败！');
      Exit;
    end;
    //交易次数
    if CardManage.ReadCardConsumeInfo(LPI, nPacketNo) then
    begin
      tradeNum:=StrToInt(format('%d', [LPI.DealTimes]));
      balance := StrToInt(Format('%d',[LPI.RemainMoney]));
    end else
    begin
      Context.GetDialogSystem.ShowMessage('读取卡消费次数失败，操作取消！');
      Exit;
    end;

    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    WVReserveConsume.FieldByName('操作员密码').Data.SetString(operPwd);
    WVReserveConsume.FieldByName('物理卡号').Data.SetString(CardPhyID);
    WVReserveConsume.FieldByName('卡号').Data.SetInteger(StrToInt(readCardNo));
    WVReserveConsume.FieldByName('业务日期').Data.SetString(operDate);
    WVReserveConsume.FieldByName('流水号').Data.SetInteger(seriId);
    WVReserveConsume.FieldByName('终端编号').Data.SetInteger(stationId);
    WVReserveConsume.FieldByName('入卡值').Data.SetInteger(balance);
    WVReserveConsume.FieldByName('卡交易次数').Data.SetInteger(tradeNum);
    WVRReserveConsume.SendCommand;
    cardId := WVReserveConsume.FieldByName('卡号').Data.AsInteger;
    outMoney := WVReserveConsume.Fieldbyname('出卡值').Data.AsInteger;
    if cardId<>StrToInt(readCardNo) then
    begin
      ShowMessage('你要冲正的卡和放置的卡不是同一张卡，请重新操作');
      Exit;
    end;
    try
      if CardManage.packetSetMoneyAndChk(IntToStr(outMoney),outMoney) <>0 then
        ShowMessage('在冲正时没有写卡信息，请重新执行冲正交易！');
      CardManage.ControlBuzzer;
      RzStatusPane1.Caption := WVReserveConsume.fieldbyname('返回信息').Data.AsString;
      btnQuery.Click;
    except
      ShowMessage('在冲正时没有写卡信息，请重新执行冲正交易！');
    end;
  finally
    CardManage.Destroy;
  end;
  edtPwd.Text := '';
end;

procedure TfaqhReverseConsume.btnReadCardClick(Sender: TObject);
begin
  edtCardNo.Text:=readCardNo;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('消费冲正',TfaqhReverseConsume);

end.