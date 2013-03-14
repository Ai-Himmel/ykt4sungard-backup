unit UAEPurseReg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, RzStatus, RzPanel, RzEdit;

type
  TfaqhEPurseReg = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVComboBox8: TWVComboBox;
    WVComboBox9: TWVComboBox;
    WVEdit10: TWVEdit;
    WVEdit11: TWVEdit;
    WVLabel2: TWVLabel;
    WVEdit2: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    Label13: TLabel;
    WVComboBox4: TWVComboBox;
    WVLabel3: TWVLabel;
    cbbEPurse: TWVComboBox;
    btnReg: TBitBtn;
    WVEPurseReg: TWorkView;
    WVREPurseReg: TWVRequest;
    grp1: TGroupBox;
    lbl1: TLabel;
    edtPwd: TWVEdit;
    Label12: TLabel;
    edtRePwd: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnRegClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhEPurseReg: TfaqhEPurseReg;

implementation

uses KsFrameworks,KSClientConsts,
  SmartCardCommon,UtCardDll;

{$R *.DFM}

procedure TfaqhEPurseReg.Init;
begin
  inherited;
  btnReg.Enabled := False;
end;

procedure TfaqhEPurseReg.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;



procedure TfaqhEPurseReg.btnQueryClick(Sender: TObject);
var
  ErrMsg: string;
begin
  if trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  {
  if trim(WVEdit10.Text) <> '' then
  begin
    if ValidateIDcard(WVEdit10.Text, ErrMsg) <> 0 then
    begin
      Showmessage(ErrMsg);
      WVEdit10.SelectAll;
      WVEdit10.SetFocus;
      Exit;
    end;
  end;
  }
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;
  if Grid.DataSource.DataSet.IsEmpty then
    btnReg.Enabled := False
  else
    btnReg.Enabled := True;
end;

procedure TfaqhEPurseReg.btnRegClick(Sender: TObject);
var
  custId:Integer;
  tmpDataSet:TDataSet;
  pwd:string;
  tmppwd:string;
begin
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  custId := tmpDataSet.fieldbyname('lvol1').AsInteger;
  if Length(Trim(edtPwd.Text))<>6 then
  begin
    Context.GetDialogSystem.ShowMessage('请输入6位帐户密码！');
    Exit;
  end;
  if Trim(edtPwd.Text)<>Trim(edtRePwd.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('两次输入的密码不一致，请重新输入！');
    Exit;
  end;
  try
    pwd := encCardpwd(0,smartCardPwd,Trim(edtPwd.Text));
    //ShowMessage(smartCardPwd);
    tmppwd := decCardpwd(0,smartCardPwd,pwd);
    //ShowMessage(tmppwd);
    WVEPurseReg.FieldByName('客户号').Data.SetInteger(custId);
    WVEPurseReg.FieldByName('帐户密码').Data.SetString(pwd);
    WVREPurseReg.SendCommand;
    if WVEPurseReg.FieldByName('返回码').Data.AsInteger=0 then
    begin
      Context.GetDialogSystem.ShowMessage(WVEPurseReg.fieldbyname('返回信息').Data.AsString);
      RzStatusPane1.Caption := WVEPurseReg.fieldbyname('返回信息').Data.AsString;
    end;
  finally
    edtPwd.Text := '';
    edtRePwd.Text := '';
  end;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('电子钱包开户', TfaqhEPurseReg);

end.
