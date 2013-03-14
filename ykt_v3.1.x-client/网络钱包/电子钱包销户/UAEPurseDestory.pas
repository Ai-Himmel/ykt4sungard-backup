unit UAEPurseDestory;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, RzStatus, RzPanel;

type
  TfaqhEPurseDestory = class(TfaqhSimpleQueryTemp)
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
    btnReg: TBitBtn;
    WVEPurseDestory: TWorkView;
    WVREPurseDestory: TWVRequest;
    grp1: TGroupBox;
    lbl1: TLabel;
    edtPwd: TWVEdit;
    WVComboBox1: TWVComboBox;
    Label1: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
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
  faqhEPurseDestory: TfaqhEPurseDestory;

implementation

uses KsFrameworks, 
  SmartCardCommon,UtCardDll,KSClientConsts;

{$R *.DFM}

procedure TfaqhEPurseDestory.Init;
begin
  inherited;
  btnReg.Enabled := False;
end;

procedure TfaqhEPurseDestory.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;



procedure TfaqhEPurseDestory.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;

  inherited;
  if Grid.DataSource.DataSet.IsEmpty then
    btnReg.Enabled := False
  else
    btnReg.Enabled := True;
end;

procedure TfaqhEPurseDestory.btnRegClick(Sender: TObject);
var
  custId:Integer;
  accNo:string;
  tmpDataSet:TDataSet;
  pwd:string;
begin
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  custId := tmpDataSet.fieldbyname('lvol1').AsInteger;
  accNo := tmpDataSet.fieldbyname('sbank_acc').AsString;
  if Length(Trim(edtPwd.Text))<>6 then
  begin
    Context.GetDialogSystem.ShowMessage('请输入6位帐户密码！');
    Exit;
  end;
  try
    pwd := encCardpwd(0,smartCardPwd,Trim(edtPwd.Text));
    WVEPurseDestory.FieldByName('客户号').Data.SetInteger(custId);
    WVEPurseDestory.FieldByName('帐户密码').Data.SetString(pwd);
    WVEPurseDestory.FieldByName('帐号').Data.SetString(accno);

    WVREPurseDestory.SendCommand;
    if WVEPurseDestory.FieldByName('返回码').Data.AsInteger=0 then
    begin
      ShowMessage(WVEPurseDestory.fieldbyname('返回信息').Data.AsString);
      RzStatusPane1.Caption := WVEPurseDestory.fieldbyname('返回信息').Data.AsString;
    end;
  finally
    edtPwd.Text := '';
  end;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('电子钱包销户', TfaqhEPurseDestory);

end.
