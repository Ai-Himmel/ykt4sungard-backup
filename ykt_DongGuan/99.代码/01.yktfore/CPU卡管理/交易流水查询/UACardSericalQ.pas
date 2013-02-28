unit UACardSericalQ;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll;

type
  TfaqhCardSericalQ = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    edtCustName: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit10: TWVEdit;
    WVEdit11: TWVEdit;
    WVComboBox1: TWVComboBox;
    cbbDept: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Label9: TLabel;
    edtAppSerialNo: TWVEdit;
    btnReadCard: TBitBtn;
    Label13: TLabel;
    WVComboBox3: TWVComboBox;
    WVComboBox4: TWVComboBox;
    Label14: TLabel;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardSericalQ: TfaqhCardSericalQ;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhCardSericalQ.Init;
begin
  inherited;
  {
  WorkView.FieldByName('��ʼ����').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('֤������').DefaultValue := '';
  WorkView.FieldByName('֤������').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�绰').DefaultValue := '';
  WorkView.FieldByName('�ֻ�').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('������').DefaultValue := 0;
  WorkView.Reset;
  }
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
end;

procedure TfaqhCardSericalQ.btnQueryClick(Sender: TObject);
begin
  if (Trim(edtBeginDate.Text)='') or (Trim(edtEndDate.Text)='') then
  begin
    Context.GetDialogSystem.ShowMessage('�����뿪ʼ���ںͽ������ڣ�');
    Exit;
  end;
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ�');
  if Trim(edtCustName.Text)='' then
    edtCustName.Text := '0';
  inherited;

end;

procedure TfaqhCardSericalQ.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppSerialNo.Text:='';
  try
    cardNo := readCardOneInfo(CF_APPSERIALNO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('������ѯʧ�ܣ�Ӧ�����к�Ϊ��򲻴���!');
    Exit;
  end;
  edtAppSerialNo.Text:=cardNo;
  btnQuery.Click();
end;

initialization
  TUIStdClassFactory.Create('������ˮ��ѯ',TfaqhCardSericalQ);

end.