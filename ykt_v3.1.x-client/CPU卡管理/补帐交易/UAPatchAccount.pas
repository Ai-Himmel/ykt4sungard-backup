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
  WorkView.FieldByName('���׿���').DefaultValue := 0;
  WorkView.Reset;
  btnPrint.Caption:='&O ȷ��';
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
  WorkView.FieldByName('״̬').Data.SetInteger(1);
  if Trim(edtCardNo.Text)='' then
    WorkView.FieldByName('���׿���').Data.SetInteger(0);

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
  //serialdate,serialno��ˮ�������ڣ���ˮ��
  oldmoney,OperatorID,CardNo,serialdate,serialno:string;
  AccUseNum,SeilID,DM:integer;
  OutMoney, ShareMoney, UnuseMoney: real;
  operCode:string;
  operPwd:string;

begin
  //inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ��޷����д˲�����');
    Exit;
  end;
  {if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
    Exit;
  end;
  if not SmartCardAuthStatus then
  begin
    Context.GetDialogSystem.ShowWarning('����Ϊ��д����Ȩ��');
    Exit;
  end;}
  if PrepareReadCardInfo=False then
    Exit;
  CardManage := TCardManage.Create;
  //��ȡ������
  CardPhyID := '';
  if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ȡ������ʧ�ܣ�');
    CardManage.Destroy;
    Exit;
  end;
  //��ȡ�������
  TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
  if TOF = True then
  begin
    OldMoney := format('%f', [(LPI.RemainMoney) / 100.0]);
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
    CardManage.Destroy;
    Exit;
  end;
  //AccUseNum ��ǰ�����˻�ʹ�ô���
  if CardManage.ReadCardConsumeInfo(LPI, nPacketNo) then
  begin
    AccUseNum:=StrToInt(format('%d', [LPI.DealTimes]));
  end else
  begin
    Context.GetDialogSystem.ShowMessage('��ȡ�����Ѵ���ʧ�ܣ�����ȡ����');
    CardManage.Destroy;
    Exit;
  end;

  tempDataSet := WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
  CardNo := tempDataSet.FieldByName('lvol1').AsString;
  serialdate := tempDataSet.fieldbyname('sbank_pwd').AsString;
  serialno := tempDataSet.fieldbyname('lvol0').AsString;
  //��������Ա OperatorID
  OperatorID := Context.ParamData(svOperatorNoName).AsString;
  if Trim(edtMoney.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�����뷢����');
    edtMoney.SetFocus;
    CardManage.Destroy;
    exit;
  end;
  operCode := Trim(edtChk.Text);
  operPwd := encOperPwd(operCode,Trim(edtChkPwd.Text));
  WVPatchAccount.FieldByName('����Ա����').Data.SetString(operPwd);
  WVPatchAccount.FieldByName('������').Data.SetString(CardPhyID);
  WVPatchAccount.FieldByName('�뿨ֵ').Data.SetFloat(StrToFloat(OldMoney));
  WVPatchAccount.FieldByName('���׿���').Data.SetInteger(StrToInt(cardno));
  WVPatchAccount.FieldByName('��ǰ�����״���').Data.SetInteger(AccUseNum);
  WVPatchAccount.FieldByName('����վ��').Data.SetInteger(SmartCardSubSystemNo);
  WVPatchAccount.FieldByName('����Ա').Data.SetString(OperatorID);
  WVPatchAccount.FieldByName('ԭ��ˮ��').Data.SetInteger(StrToInt(serialno));
  WVPatchAccount.FieldByName('��ˮ��������').Data.SetString(serialdate);
  try
    WVRPatchAccount.SendCommand;
  except
    Context.GetDialogSystem.ShowMessage('�������ʧ�ܣ�����ԭ��');
    CardManage.Destroy;
    Exit;
  end;
  
  CardManage.Destroy;
  if WVPatchAccount.FieldByName('������').Data.AsInteger<>0 then
  begin
    getReturn('',WVPatchAccount);
    exit;
  end;
  OutMoney := WVPatchAccount.FieldByName('��ֵ���').Data.AsFloat;
  ShareMoney := WVPatchAccount.FieldByName('����').Data.AsFloat;
  SeilID := WVPatchAccount.FieldByName('��ˮ��').Data.AsInteger;
  dm := StrToInt(floattostr(OutMoney))*100;
  //dm := StrToInt(FloatToStr(OutMoney * 100)) -
    //StrToInt(FloatToStr(StrToFloat(OldMoney) * 100));
  if CardManage.AddCardMoney(IntToStr(dm))=False then
  begin
    //д��ʧ�ܽ��лع�����
    WVBackState.FieldByName('��̨������ˮ��').Data.SetInteger(SeilID);
    WVBackState.FieldByName('����ʶ').Data.SetInteger(StrToInt(CardNo));
    WVBackState.FieldByName('������').Data.SetInteger(240157);
    try
      WVRBackState.SendCommand;
      Context.GetDialogSystem.ShowMessage('д����ֵʧ�ܣ����޸Ŀ�״̬��');
    except
    end;
  end
  else
  begin
    CardManage.ControlBuzzer;
    Context.GetDialogSystem.ShowMessage('���ʽ��׳ɹ���');
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
  TUIStdClassFactory.Create('���ʽ���',TfaqhPatchAccount);

end.