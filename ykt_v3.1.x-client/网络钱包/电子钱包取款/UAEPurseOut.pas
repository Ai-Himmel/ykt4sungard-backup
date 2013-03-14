unit UAEPurseOut;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, EditExts, RzStatus, RzPanel;

type
  TfaqhEPurseOut = class(TfaqhSimpleQueryTemp)
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
    btnMoneyOut: TBitBtn;
    WVEPurseOut: TWorkView;
    WVREPurseOut: TWVRequest;
    grp1: TGroupBox;
    lbl1: TLabel;
    WVComboBox1: TWVComboBox;
    Label1: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    Label2: TLabel;
    edtMoney: TWVDigitalEdit;
    edtPwd: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnMoneyOutClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhEPurseOut: TfaqhEPurseOut;

implementation

uses KsFrameworks,KSClientConsts,UtCardDll, 
  SmartCardCommon;

{$R *.DFM}

procedure TfaqhEPurseOut.Init;
begin
  inherited;
  btnMoneyOut.Enabled := False;
end;

procedure TfaqhEPurseOut.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;



procedure TfaqhEPurseOut.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;

  inherited;
  if Grid.DataSource.DataSet.IsEmpty then
    btnMoneyOut.Enabled := False
  else
    btnMoneyOut.Enabled := True;
end;

procedure TfaqhEPurseOut.btnMoneyOutClick(Sender: TObject);
var
  custName:string;
  custId:Integer;
  accNo:string;
  tmpDataSet:TDataSet;
  pwd:string;
begin
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  custId := tmpDataSet.fieldbyname('lvol1').AsInteger;
  accNo := tmpDataSet.fieldbyname('sbank_acc').AsString;
  custName := tmpDataSet.fieldbyname('sall_name').AsString;
  if Application.MessageBox(PChar('你确定要为客户【'+custname+'】支取金额吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if Length(Trim(edtPwd.Text))<>8 then
  begin
    Context.GetDialogSystem.ShowMessage('请输入8位帐户密码！');
    Exit;
  end;
  try
    pwd := encCardpwd(0,smartCardPwd,Trim(edtPwd.Text));
    WVEPurseOut.FieldByName('客户号').Data.SetInteger(custId);
    WVEPurseOut.FieldByName('帐号').Data.SetString(accno);
    WVEPurseOut.FieldByName('取款密码').Data.SetString(pwd);
    WVREPurseOut.SendCommand;
    if WVEPurseOut.FieldByName('返回码').Data.AsInteger=0 then
    begin
      Context.GetDialogSystem.ShowMessage(WVEPurseOut.fieldbyname('返回信息').Data.AsString);
      RzStatusPane1.Caption := WVEPurseOut.fieldbyname('返回信息').Data.AsString;
    end;
  finally
    edtPwd.Text := '';
  end;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('电子钱包取款', TfaqhEPurseOut);

end.
