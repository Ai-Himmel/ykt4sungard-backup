unit UAPatchAccount;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid,WVCommands, RzStatus, RzPanel, Buttons;

type
  TfaqhPatchAccount = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    edtCardNo: TWVEdit;
    edtBankCardNo: TWVEdit;
    WVRBackState: TWVRequest;
    WVBackState: TWorkView;
    WVRPatchAccount: TWVRequest;
    WVPatchAccount: TWorkView;
    Label3: TLabel;
    edtBeginDate: TWVEdit;
    Label4: TLabel;
    edtEndDate: TWVEdit;
    grp1: TGroupBox;
    Label6: TLabel;
    edtMoney: TWVEdit;
    Label7: TLabel;
    edtChk: TWVEdit;
    Label8: TLabel;
    edtChkPwd: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVEdit1: TWVEdit;
    Label5: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure WVRPatchAccountBeforeExec(Request: TWVRequest;
      Command: TWVCommand);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPatchAccount: TfaqhPatchAccount;

implementation

uses KsFrameworks, 
     KSClientConsts,UtCardDll;
     
{$R *.DFM}

procedure TfaqhPatchAccount.Init;
begin
  inherited;
  WorkView.FieldByName('交易卡号').DefaultValue := 0;
  WorkView.Reset;
  btnPrint.Caption:='&O 确定';
  edtBeginDate.Text:=FormatDateTime('yyyymmdd',Date);
  edtEndDate.Text:=FormatDateTime('yyyymmdd',Date);
end;

procedure TfaqhPatchAccount.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  ///btnQuery.Enabled:=Valid;
end;



procedure TfaqhPatchAccount.btnQueryClick(Sender: TObject);
begin
  edtMoney.Text:='';
  edtChk.Text:='';
  edtChkPwd.text:='';
  WorkView.FieldByName('状态').Data.SetInteger(1);
  if Trim(edtCardNo.Text)='' then
    WorkView.FieldByName('交易卡号').Data.SetInteger(0);

  inherited;

end;

procedure TfaqhPatchAccount.btnPrintClick(Sender: TObject);
var
  CardManage: TCardManage;
  CardPhyID: string;
  tempDataSet: TDataSet;
  TOF: boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  //serialdate,serialno流水发生日期，流水号
  oldmoney,OperatorID,CardNo,serialdate,serialno:string;
  AccUseNum,SeilID,DM:integer;
  OutMoney, ShareMoney, UnuseMoney: real;
  operCode:string;
  operPwd:string;

begin
  //inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;
  {if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('请先打开串口！');
    Exit;
  end;
  if not SmartCardAuthStatus then
  begin
    Context.GetDialogSystem.ShowWarning('请先为读写器授权！');
    Exit;
  end;}
  if PrepareReadCardInfo=False then
    Exit;
  CardManage := TCardManage.Create;
  //读取物理卡号
  CardPhyID := '';
  if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
  begin
    Context.GetDialogSystem.ShowMessage('读取物理卡号失败！');
    CardManage.Destroy;
    Exit;
  end;
  //读取卡中余额
  TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
  if TOF = True then
  begin
    OldMoney := format('%f', [(LPI.RemainMoney) / 100.0]);
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('读取卡余额失败！');
    CardManage.Destroy;
    Exit;
  end;
  //AccUseNum 当前卡的账户使用次数
  if CardManage.ReadCardConsumeInfo(LPI, nPacketNo) then
  begin
    AccUseNum:=StrToInt(format('%d', [LPI.DealTimes]));
  end else
  begin
    Context.GetDialogSystem.ShowMessage('读取卡消费次数失败，操作取消！');
    CardManage.Destroy;
    Exit;
  end;

  tempDataSet := WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet;
  CardNo := tempDataSet.FieldByName('lvol1').AsString;
  serialdate := tempDataSet.fieldbyname('sbank_pwd').AsString;
  serialno := tempDataSet.fieldbyname('lvol0').AsString;
  //两个操作员 OperatorID
  OperatorID := Context.ParamData(svOperatorNoName).AsString;
  if Trim(edtMoney.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入发生金额！');
    edtMoney.SetFocus;
    CardManage.Destroy;
    exit;
  end;
  operCode := Trim(edtChk.Text);
  operPwd := encOperPwd(operCode,Trim(edtChkPwd.Text));
  WVPatchAccount.FieldByName('复核员密码').Data.SetString(operPwd);
  WVPatchAccount.FieldByName('物理卡号').Data.SetString(CardPhyID);
  WVPatchAccount.FieldByName('入卡值').Data.SetFloat(StrToFloat(OldMoney));
  WVPatchAccount.FieldByName('交易卡号').Data.SetInteger(StrToInt(cardno));
  WVPatchAccount.FieldByName('当前卡交易次数').Data.SetInteger(AccUseNum);
  WVPatchAccount.FieldByName('工作站号').Data.SetInteger(SmartCardSubSystemNo);
  WVPatchAccount.FieldByName('操作员').Data.SetString(OperatorID);
  WVPatchAccount.FieldByName('原流水号').Data.SetInteger(StrToInt(serialno));
  WVPatchAccount.FieldByName('流水发生日期').Data.SetString(serialdate);
  try
    WVRPatchAccount.SendCommand;
  except
    Context.GetDialogSystem.ShowMessage('传输参数失败，请检查原因！');
    CardManage.Destroy;
    Exit;
  end;
  
  CardManage.Destroy;
  if WVPatchAccount.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    getReturn('',WVPatchAccount);
    exit;
  end;
  OutMoney := WVPatchAccount.FieldByName('充值金额').Data.AsFloat;
  ShareMoney := WVPatchAccount.FieldByName('搭伙费').Data.AsFloat;
  SeilID := WVPatchAccount.FieldByName('流水号').Data.AsInteger;
  dm := StrToInt(floattostr(OutMoney))*100;
  //dm := StrToInt(FloatToStr(OutMoney * 100)) -
    //StrToInt(FloatToStr(StrToFloat(OldMoney) * 100));
  if CardManage.AddCardMoney(IntToStr(dm))=False then
  begin
    //写卡失败进行回滚交易
    WVBackState.FieldByName('后台交易流水号').Data.SetInteger(SeilID);
    WVBackState.FieldByName('卡标识').Data.SetInteger(StrToInt(CardNo));
    WVBackState.FieldByName('交易码').Data.SetInteger(240157);
    try
      WVRBackState.SendCommand;
      Context.GetDialogSystem.ShowMessage('写卡充值失败！已修改卡状态！');
    except
    end;
  end
  else
  begin
    CardManage.ControlBuzzer;
    Context.GetDialogSystem.ShowMessage('补帐交易成功！');
    edtMoney.Text:='';
    edtChk.Text:='';
    edtChkPwd.text:='';
  end;

end;

procedure TfaqhPatchAccount.WVRPatchAccountBeforeExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  //CheckCommandParamOneByOne(Command);
  inherited;
end;

initialization
  TUIStdClassFactory.Create('补帐交易',TfaqhPatchAccount);

end.