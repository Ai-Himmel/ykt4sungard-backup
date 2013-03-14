unit UAEPurseFreeze;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, EditExts, RzStatus, RzPanel;

type
  TfaqhEPurseFreeze = class(TfaqhSimpleQueryTemp)
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
    btnUnFreeze: TBitBtn;
    WVEPurseFreeze: TWorkView;
    WVREPurseFreeze: TWVRequest;
    WVComboBox1: TWVComboBox;
    Label1: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnFreeze: TBitBtn;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnUnFreezeClick(Sender: TObject);
    procedure btnFreezeClick(Sender: TObject);
  private

    { Private declarations }
    procedure execCommand(iSign:Integer);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhEPurseFreeze: TfaqhEPurseFreeze;

implementation

uses KsFrameworks, 
  SmartCardCommon;

{$R *.DFM}

procedure TfaqhEPurseFreeze.Init;
begin
  inherited;
  btnFreeze.Enabled := False;
  btnUnFreeze.Enabled := False;
end;

procedure TfaqhEPurseFreeze.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;



procedure TfaqhEPurseFreeze.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;

  inherited;
  if Grid.DataSource.DataSet.IsEmpty then
  begin
    btnFreeze.Enabled := False;
    btnUnFreeze.Enabled := False;
  end
  else
  begin
    btnFreeze.Enabled := True;
    btnUnFreeze.Enabled := True;
  end;
end;

procedure TfaqhEPurseFreeze.btnUnFreezeClick(Sender: TObject);
begin
  execCommand(0);
  btnQueryClick(Sender);
end;

procedure TfaqhEPurseFreeze.execCommand(iSign: Integer);
var
  custName:string;
  custId:Integer;
  accNo:string;
  sign:string;
  tmpDataSet:TDataSet;
begin
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  custId := tmpDataSet.fieldbyname('lvol1').AsInteger;
  accNo := tmpDataSet.fieldbyname('sbank_acc').AsString;
  custName := tmpDataSet.fieldbyname('sall_name').AsString;
  if iSign=0 then
    sign := '正常'
  else
    sign := '止付';
  if Application.MessageBox(PChar('你确定要把客户【'+custname+'】变为【'+sign+'】状态吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  WVEPurseFreeze.FieldByName('客户号').Data.SetInteger(custId);
  WVEPurseFreeze.FieldByName('帐号').Data.SetString(accno);
  WVEPurseFreeze.FieldByName('标志').Data.SetString(IntToStr(iSign));

  WVREPurseFreeze.SendCommand;
  if WVEPurseFreeze.FieldByName('返回码').Data.AsInteger=0 then
  begin
    Context.GetDialogSystem.ShowMessage(WVEPurseFreeze.fieldbyname('返回信息').Data.AsString);
    RzStatusPane1.Caption := WVEPurseFreeze.fieldbyname('返回信息').Data.AsString;
  end;

end;

procedure TfaqhEPurseFreeze.btnFreezeClick(Sender: TObject);
begin
  execCommand(1);
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('钱包止付解付', TfaqhEPurseFreeze);

end.
