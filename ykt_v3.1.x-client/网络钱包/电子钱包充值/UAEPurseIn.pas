unit UAEPurseIn;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, EditExts, RzStatus, RzPanel;

type
  TfaqhEPurseIn = class(TfaqhSimpleQueryTemp)
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
    WVEPurseIn: TWorkView;
    WVREPurseIn: TWVRequest;
    grp1: TGroupBox;
    lbl1: TLabel;
    Label12: TLabel;
    edtTicketNo: TEdit;
    WVComboBox1: TWVComboBox;
    Label1: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    cbbType: TWVComboBox;
    Label2: TLabel;
    edtMoney: TWVDigitalEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
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
  faqhEPurseIn: TfaqhEPurseIn;

implementation

uses KsFrameworks, 
  SmartCardCommon;

{$R *.DFM}

procedure TfaqhEPurseIn.Init;
begin
  inherited;
  btnMoneyIn.Enabled := False;
  edtTicketNo.Enabled := False;
  cbbType.ItemIndex := 0;
end;

procedure TfaqhEPurseIn.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;



procedure TfaqhEPurseIn.btnQueryClick(Sender: TObject);
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

procedure TfaqhEPurseIn.btnMoneyInClick(Sender: TObject);
var
  //custId:Integer;
  custName:string;
  accNo:string;
  inType:string;
  tmpDataSet:TDataSet;
begin
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  //custId := tmpDataSet.fieldbyname('lvol1').AsInteger;
  custName := tmpDataSet.fieldbyname('sall_name').AsString;
  accNo := tmpDataSet.fieldbyname('sbank_acc').AsString;
  if Application.MessageBox(PChar('你确定要为客户【'+custname+'】充值吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  inType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  WVEPurseIn.FieldByName('付款方式').Data.SetInteger(StrToInt(inType));
  WVEPurseIn.FieldByName('凭证号码').Data.SetString(Trim(edtTicketNo.Text));
  WVEPurseIn.FieldByName('帐号').Data.SetString(accno);

  WVREPurseIn.SendCommand;
  if WVEPurseIn.FieldByName('返回码').Data.AsInteger=0 then
  begin
    Context.GetDialogSystem.ShowMessage(WVEPurseIn.fieldbyname('返回信息').Data.AsString);
    RzStatusPane1.Caption := WVEPurseIn.fieldbyname('返回信息').Data.AsString;
  end;
  btnQueryClick(Sender);
end;

procedure TfaqhEPurseIn.cbbTypeChange(Sender: TObject);
begin
  if cbbType.ItemIndex=0 then
    edtTicketNo.Enabled := False
  else
    edtTicketNo.Enabled := True;

end;

initialization
  TUIStdClassFactory.Create('电子钱包充值', TfaqhEPurseIn);

end.
