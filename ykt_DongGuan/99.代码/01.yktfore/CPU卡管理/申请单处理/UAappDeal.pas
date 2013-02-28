unit UAappDeal;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll;

type
  TfaqhappDeal = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    edtAppDate: TWVEdit;
    edtDealDate: TWVEdit;
    edtOrderNo: TWVEdit;
    edtCardNo: TWVEdit;
    WVEdit6: TWVEdit;
    edtAppSerialNo: TWVEdit;
    cbbIDType: TWVComboBox;
    WVComboBox1: TWVComboBox;
    btnReadQ: TBitBtn;
    WVCancelApp: TWorkView;
    WVRCancelApp: TWVRequest;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadQClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhappDeal: TfaqhappDeal;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhappDeal.Init;
begin
  inherited;
  {
  WorkView.FieldByName('������־').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('���뵥��').DefaultValue := 0;
  WorkView.FieldByName('����').DefaultValue := 0;
  WorkView.FieldByName('֤������').DefaultValue := '';
  WorkView.FieldByName('Ӧ�����к�').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := 0;
  WorkView.FieldByName('����״̬').DefaultValue := 0;
  WorkView.Reset;
  }
end;

procedure TfaqhappDeal.btnQueryClick(Sender: TObject);
begin
  if Trim(edtAppDate.Text)<>'' then
    if CheckInputDateFormat(edtAppDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtAppDate.SetFocus;
      Exit;
    end;
  if Trim(edtDealDate.Text)<>'' then
    if CheckInputDateFormat(edtDealDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtDealDate.SetFocus;
      Exit;
    end;
  if edtCardNo.Text = '' then
    edtCardNo.Text := '0';
  if edtOrderNo.Text = '' then
    edtOrderNo.Text := '0';
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;

end;

procedure TfaqhappDeal.btnReadQClick(Sender: TObject);
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

procedure TfaqhappDeal.btnPrintClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫȡ�������뵥��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVCancelApp.FieldByName('������־').Data.SetString('C');
  WVCancelApp.FieldByName('���뵥��').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol1').AsInteger);
  WVRCancelApp.SendCommand;
  if WVCancelApp.FieldByName('������').Data.AsString='0' then
    Context.GetDialogSystem.ShowMessage('ȡ�����뵥�ɹ���')
  else
    Context.GetDialogSystem.ShowMessage(WVCancelApp.FieldByName('������Ϣ').Data.AsString);
end;

initialization
  TUIStdClassFactory.Create('���뵥����',TfaqhappDeal);

end.