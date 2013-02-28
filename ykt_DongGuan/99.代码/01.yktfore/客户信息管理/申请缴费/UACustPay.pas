unit UACustPay;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzStatus;

type
  TfaqhCustPay = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label4: TLabel;
    Label12: TLabel;
    Label7: TLabel;
    cbb1: TWVComboBox;
    edtBirthdayQ: TWVEdit;
    cbbDept: TWVComboBox;
    WVEdit17: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVEdit9: TWVEdit;
    Label9: TLabel;
    Label14: TLabel;
    Label17: TLabel;
    Label15: TLabel;
    Label10: TLabel;
    cbbIDType: TWVComboBox;
    WVEdit15: TWVEdit;
    Label16: TLabel;
    Label11: TLabel;
    WVEdit11: TWVEdit;
    WVEdit16: TWVEdit;
    QueryRequest: TWVRequest;
    WorkView1: TWorkView;
    btnFee: TBitBtn;
    btnGetCard: TBitBtn;
    chkPrint: TCheckBox;
    lbl1: TLabel;
    lbl2: TLabel;
    edtMoney: TWVEdit;
    WorkView2: TWorkView;
    WVRequest1: TWVRequest;
    rzstspn1: TRzStatusPane;
    procedure btnQueryClick(Sender: TObject);
    procedure btnFeeClick(Sender: TObject);
    procedure btnGetCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCustPay: TfaqhCustPay;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhCustPay.Init;
begin
  inherited;
end;

procedure TfaqhCustPay.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBirthdayQ.Text)<>'' then
    if CheckInputDateFormat(edtBirthdayQ.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtBirthdayQ.SetFocus;
      Exit;
    end;

  WorkView1.FieldByName('������־').Data.SetString('R');
  QueryRequest.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);
    Exit;
  end;
  if WorkView1.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    btnGetCard.Enabled := False;
    btnFee.Enabled := False;
  end
  else
  begin
    btnGetCard.Enabled := True;
    btnFee.Enabled := True;
  end;
  //inherited;

end;

procedure TfaqhCustPay.btnFeeClick(Sender: TObject);
var
  custId:Integer;
  money:Double;
begin
  try
    if Trim(edtMoney.Text)='' then
      money := 0
    else
      money := StrToFloat(edtMoney.Text);
  except
    Context.GetDialogSystem.ShowMessage('��������Ч��Ԥ���');
    Exit;
  end;
  custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  if Application.MessageBox('��ȷ��Ҫ����Ԥ�������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView.FieldByName('������־').Data.SetString('F');
  WorkView.FieldByName('�ͻ���').Data.SetInteger(custId);
  WorkView.FieldByName('Ԥ����').Data.SetFloat(money);
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsString<>'0' then
    Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString)
  else
    Context.GetDialogSystem.ShowMessage('�ɷѳɹ���');
end;

procedure TfaqhCustPay.btnGetCardClick(Sender: TObject);
var
  custId:Integer;
begin
  custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  if Application.MessageBox('��ȷ��Ҫ�����쿨������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView.FieldByName('������־').Data.SetString('G');
  WorkView.FieldByName('�ͻ���').Data.SetInteger(custId);
  //WorkView.FieldByName('Ԥ����').Data.SetFloat(money);
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsString<>'0' then
    Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString)
  else
    Context.GetDialogSystem.ShowMessage('�쿨�ɹ���');
end;

procedure TfaqhCustPay.GridCellClick(Column: TColumn);
var
  custId:Integer;
  custType:Integer;
begin
  try
    custId:=Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
    custType :=Grid.DataSource.DataSet.fieldbyname('semp_no').AsInteger;
  except
    custId := 0;
    custType := 0;
  end;
  WorkView2.FieldByName('�ͻ���').Data.SetInteger(custId);
  WorkView2.FieldByName('�����').Data.SetInteger(custType);
  WVRequest1.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger=0 then
  begin
    rzstspn1.Caption := WorkView2.fieldbyname('�ɷ���Ϣ').Data.AsString;
    edtMoney.Text := WorkView2.fieldbyname('Ԥ�����').Data.AsString;
  end
  else
    rzstspn1.Caption := WorkView2.fieldbyname('������Ϣ').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('�ƿ��ɷ�',TfaqhCustPay);

end.