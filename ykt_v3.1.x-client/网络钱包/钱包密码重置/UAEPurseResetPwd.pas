unit UAEPurseResetPwd;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, EditExts, RzStatus, RzPanel;

type
  TfaqhEPurseResetPwd = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    WVComboBox3: TWVComboBox;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVLabel2: TWVLabel;
    WVEdit2: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    btnMoneyIn: TBitBtn;
    WVresetpwd: TWorkView;
    WVRresetpwd: TWVRequest;
    grp1: TGroupBox;
    lbl1: TLabel;
    Label12: TLabel;
    edtTicketNo: TWVEdit;
    WVComboBox1: TWVComboBox;
    Label1: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    cbbType: TWVComboBox;
    Label2: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    edtPwd: TWVEdit;
    Label7: TLabel;
    edtRepwd: TEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnMoneyInClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhEPurseResetPwd: TfaqhEPurseResetPwd;

implementation

uses KsFrameworks,KSClientConsts,UtCardDll, 
  SmartCardCommon;

{$R *.DFM}

procedure TfaqhEPurseResetPwd.Init;
begin
  inherited;
  btnMoneyIn.Enabled := False;
  cbbType.ItemIndex := 0;
end;

procedure TfaqhEPurseResetPwd.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;



procedure TfaqhEPurseResetPwd.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;

  inherited;
  if Grid.DataSource.DataSet.IsEmpty then
    btnMoneyIn.Enabled := False
  else
    btnMoneyIn.Enabled := True;
end;

procedure TfaqhEPurseResetPwd.btnMoneyInClick(Sender: TObject);
var
  //custId:Integer;
  custName:string;
  accNo:string;
  inType:string;
  tmpDataSet:TDataSet;
  pwd:string;
begin
  tmpDataSet := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  //custId := tmpDataSet.fieldbyname('lvol1').AsInteger;
  custName := tmpDataSet.fieldbyname('sall_name').AsString;
  accNo := tmpDataSet.fieldbyname('sbank_acc').AsString;
  if Application.MessageBox(PChar('��ȷ��Ҫ���ÿͻ���'+custname+'����������'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if Length(Trim(edtPwd.Text))<>6 then
  begin
    Context.GetDialogSystem.ShowMessage('������6λ�������룡');
    edtPwd.SetFocus;
    Exit;
  end;
  if edtPwd.Text<>edtRepwd.Text then
  begin
    Context.GetDialogSystem.ShowMessage('������������벻һ�������������룡');
    Exit;
  end;
  inType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  try
    pwd := encCardpwd(0,smartCardPwd,Trim(edtPwd.Text));
    WVresetpwd.FieldByName('֤������').Data.SetString(inType);
    WVresetpwd.FieldByName('֤������').Data.SetString(Trim(edtTicketNo.Text));
    WVresetpwd.FieldByName('������').Data.SetString(pwd);
    WVresetpwd.FieldByName('�ʺ�').Data.SetString(accno);

    WVRresetpwd.SendCommand;
    if WVresetpwd.FieldByName('������').Data.AsInteger=0 then
    begin
      Context.GetDialogSystem.ShowMessage(WVresetpwd.fieldbyname('������Ϣ').Data.AsString);
      RzStatusPane1.Caption := WVresetpwd.fieldbyname('������Ϣ').Data.AsString;
    end;
  finally
    edtPwd.Text := '';
    edtRepwd.Text := '';
    edtTicketNo.Text := '';
  end;
  //btnQueryClick(Sender);
end;

procedure TfaqhEPurseResetPwd.cbbTypeChange(Sender: TObject);
begin
  if cbbType.ItemIndex=0 then
    edtTicketNo.Enabled := False
  else
    edtTicketNo.Enabled := True;

end;

initialization
  TUIStdClassFactory.Create('Ǯ����������', TfaqhEPurseResetPwd);

end.
