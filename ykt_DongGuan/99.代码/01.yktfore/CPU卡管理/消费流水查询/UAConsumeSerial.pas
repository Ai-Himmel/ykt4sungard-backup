unit UAConsumeSerial;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus,RM_Class;

type
  TfaqhConsumeSerial = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    edtAppSerialNo: TWVEdit;
    edtCardNo: TWVEdit;
    WVEdit6: TWVEdit;
    cbbIDType: TWVComboBox;
    RzStatusPane2: TRzStatusPane;
    btnReadCard: TBitBtn;
    Label13: TLabel;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    Label8: TLabel;
    WVComboBox2: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhConsumeSerial: TfaqhConsumeSerial;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhConsumeSerial.Init;
begin
  inherited;
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
end;

procedure TfaqhConsumeSerial.btnQueryClick(Sender: TObject);
begin
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
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ����������룡');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  inherited;

end;

procedure TfaqhConsumeSerial.btnReadCardClick(Sender: TObject);
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
  TUIStdClassFactory.Create('����������ˮ',TfaqhConsumeSerial);

end.