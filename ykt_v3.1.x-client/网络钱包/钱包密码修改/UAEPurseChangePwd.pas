unit UAEPurseChangePwd;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, EditExts, RzStatus, RzPanel;

type
  TfaqhEPurseChangePwd = class(TfaqhSimpleQueryTemp)
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
    WVchangepwd: TWorkView;
    WVRchangepwd: TWVRequest;
    grp1: TGroupBox;
    lbl1: TLabel;
    Label12: TLabel;
    edtNewPwd: TWVEdit;
    WVComboBox1: TWVComboBox;
    Label1: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    Label2: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    edtOldPwd: TWVEdit;
    edtRePwd: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnMoneyInClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhEPurseChangePwd: TfaqhEPurseChangePwd;

implementation

uses KsFrameworks,KSClientConsts, 
  SmartCardCommon,UtCardDll;

{$R *.DFM}

procedure TfaqhEPurseChangePwd.Init;
begin
  inherited;
  btnMoneyIn.Enabled := False;
end;

procedure TfaqhEPurseChangePwd.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;



procedure TfaqhEPurseChangePwd.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;

  inherited;
  if Grid.DataSource.DataSet.IsEmpty then
    btnMoneyIn.Enabled := False
  else
    btnMoneyIn.Enabled := True;
end;

procedure TfaqhEPurseChangePwd.btnMoneyInClick(Sender: TObject);
var
  //custId:Integer;
  custName:string;
  accNo:string;
  tmpDataSet:TDataSet;
  oldpwd:string;
  newPwd:string;
begin
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  //custId := tmpDataSet.fieldbyname('lvol1').AsInteger;
  custName := tmpDataSet.fieldbyname('sall_name').AsString;
  accNo := tmpDataSet.fieldbyname('sbank_acc').AsString;
  if Application.MessageBox(PChar('你确定要修改客户【'+custname+'】的密码吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if Length(Trim(edtNewPwd.Text))<>6 then
  begin
    Context.GetDialogSystem.ShowMessage('请输入6位帐户密码！');
    edtNewPwd.SetFocus;
    Exit;
  end;
  if edtNewPwd.Text<>edtRePwd.Text then
  begin
    Context.GetDialogSystem.ShowMessage('两次输入的密码不相同，请重新输入！');
    Exit;
  end;
  try
    //ShowMessage(smartCardPwd);
    oldpwd := encCardpwd(0,smartCardPwd,Trim(edtOldPwd.Text));
    newPwd := encCardpwd(0,smartCardPwd,Trim(edtNewPwd.Text));
    WVchangepwd.FieldByName('原密码').Data.SetString(oldpwd);
    WVchangepwd.FieldByName('新密码').Data.SetString(newPwd);
    WVchangepwd.FieldByName('帐号').Data.SetString(accno);

    WVRchangepwd.SendCommand;
    if WVchangepwd.FieldByName('返回码').Data.AsInteger=0 then
    begin
      ShowMessage(WVchangepwd.fieldbyname('返回信息').Data.AsString);
      RzStatusPane1.Caption := WVchangepwd.fieldbyname('返回信息').Data.AsString;
    end;
  finally
    edtNewPwd.Text := '';
    edtRePwd.Text := '';
    edtOldPwd.Text := '';
  end;
  //btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('钱包密码修改', TfaqhEPurseChangePwd);

end.
