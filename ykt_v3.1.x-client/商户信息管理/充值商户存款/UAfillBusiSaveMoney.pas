unit UAfillBusiSaveMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, EditExts, UIncrementComboBox,
  RzLabel, RzEdit, RzStatus, RzPanel, Buttons;

type
  TfaqhfillBusiSaveMoney = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    grp1: TGroupBox;
    edtSveMoney: TWVDigitalEdit;
    lbl1: TRzLabel;
    RzLabel1: TRzLabel;
    grpSuccInfo: TGroupBox;
    RzLabel2: TRzLabel;
    RzLabel3: TRzLabel;
    RzLabel6: TRzLabel;
    RzLabel8: TRzLabel;
    RzLabel10: TRzLabel;
    RzLabel12: TRzLabel;
    RzLabel14: TRzLabel;
    RzLabel16: TRzLabel;
    lblBl: TRzLabel;
    RzLabel18: TRzLabel;
    lblAccMoney: TRzLabel;
    WorkView1: TWorkView;
    QueryRequest: TWVRequest;
    lbl2: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    edtSeriId: TRzEdit;
    edtBusiId: TRzEdit;
    edtBusiName: TRzEdit;
    edtDate: TRzEdit;
    edtTc: TRzEdit;
    edtAccMoney: TRzEdit;
    edtSaveMoney: TRzEdit;
    cbbBusiName: TWVComboBox;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnSaveMoney: TImageButton;
    RzLabel4: TRzLabel;
    cbbType: TWVComboBox;
    RzLabel5: TRzLabel;
    edtTicketNo: TRzEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure cbbBusiNameChange(Sender: TObject);
    procedure btnSaveMoneyClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
  private

    { Private declarations }
    procedure clearSuccInfo;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhfillBusiSaveMoney: TfaqhfillBusiSaveMoney;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhfillBusiSaveMoney.Init;
begin
  inherited;
  {
  WorkView1.FieldByName('��ѯ.�̻���').DefaultValue := 0;
  WorkView1.FieldByName('��ѯ.�̻�����').DefaultValue := '';
  WorkView1.FieldByName('��ѯ.�̻�����������').DefaultValue := '';
  WorkView1.FieldByName('��ѯ.�̻�֤������').DefaultValue := 0;
  WorkView1.FieldByName('��ѯ.�̻���ɱ���').DefaultValue := 0.00;
  WorkView1.FieldByName('��ѯ.�̻�֤������').DefaultValue := '';
  WorkView1.Reset;
  WorkView.FieldByName('�̻���').DefaultValue := 0;
  WorkView.FieldByName('�����').DefaultValue := 0.00;
  WorkView.Reset;
  }
  cbbBusiName.ItemIndex := -1;
  //btnSaveMoney.Caption := '�̻����';
end;

procedure TfaqhfillBusiSaveMoney.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhfillBusiSaveMoney.cbbBusiNameChange(Sender: TObject);
var
  busiId:string;
  tmpDataSet:TDataSet;
begin
  //inherited;
  clearSuccInfo;
  lblBl.Caption := '';
  lblAccMoney.Caption := '';
  busiId := Copy(cbbBusiName.Text,1,Pos('-',cbbBusiName.Text)-1);

  WorkView1.FieldByName('��ѯ.�̻���').Data.SetInteger(StrToInt(busiId));
  WorkView1.FieldByName('������־').Data.SetString('R');
  //WorkView1.FieldByName('��ѯ.�̻���ɱ���').Data.SetFloat(0);
  QueryRequest.SendCommand;
  try
    tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
    lblBl.Caption := FloatToStr(tmpDataSet.fieldbyname('drate1').AsFloat);
    lblAccMoney.Caption := tmpDataSet.fieldbyname('damt0').AsString;
  except
  end;
end;

procedure TfaqhfillBusiSaveMoney.clearSuccInfo;
var
  i:Integer;
begin
  for i := 0 to grpSuccInfo.ControlCount-1 do
  begin
    if grpSuccInfo.Controls[i] is TRzEdit then
      TRzEdit(grpSuccInfo.Controls[i]).Text := '';
  end;
end;

procedure TfaqhfillBusiSaveMoney.btnSaveMoneyClick(Sender: TObject);
var
  fillType:string;
begin
  //inherited;
  if (cbbBusiName.Text='')or(cbbBusiName.Text='-') then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ��ֵ���̻���');
    Exit;
  end;
  fillType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  if (fillType='')or (fillType='-') then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���ֵ���ͣ�');
    cbbType.SetFocus;
    exit;
  end;
  if StrToInt(fillType)<>1 then
    if Trim(edtTicketNo.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('������Ʊ�ݺ��룡');
      edtTicketNo.SetFocus;
      Exit;
    end;
  if Application.MessageBox('��ȷ��ҪΪ�ó�ֵ�̻������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  WorkView.FieldByName('��ֵ����').Data.SetInteger(StrToInt(fillType));
  WorkView.FieldByName('Ʊ�ݺ���').Data.SetString(edtTicketNo.Text);
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger=0 then
  begin
    Context.GetDialogSystem.ShowMessage('�ó�ֵ�̻���ֵ�ɹ���');
    edtSeriId.Text := WorkView.fieldbyname('��̨��ˮ��').Data.AsString;
    edtBusiId.Text := WorkView.fieldbyname('�̻���').Data.AsString;
    edtBusiName.Text := WorkView.fieldbyname('�̻�����').Data.AsString;
    edtDate.Text := WorkView.fieldbyname('��������').Data.AsString;
    edtSaveMoney.Text := WorkView.fieldbyname('�����').Data.AsString;
    edtTc.Text := WorkView.fieldbyname('��ɽ��').Data.AsString;
    edtAccMoney.Text := WorkView.fieldbyname('�ʻ����').Data.AsString;
    RzStatusPane1.Caption := WorkView.fieldbyname('������Ϣ').Data.AsString;
  end;
end;

procedure TfaqhfillBusiSaveMoney.cbbTypeChange(Sender: TObject);
begin
  edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
    edtTicketNo.Enabled := False
  else
    edtTicketNo.Enabled := True;

end;

initialization
  TUIStdClassFactory.Create('��ֵ�̻����',TfaqhfillBusiSaveMoney);

end.