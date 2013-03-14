unit UATradeReverse;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  RzStatus, RzPanel,CardDll;

type
  TfaqhTradeReserve = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    edtSeriNo: TWVEdit;
    WVEdit6: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnReserved: TBitBtn;
    Label13: TLabel;
    Label14: TLabel;
    edtPwd: TWVEdit;
    WVReserved: TWorkView;
    WVRReserved: TWVRequest;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    cbbErrOperNo: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReservedClick(Sender: TObject);
  private

    { Private declarations }
    procedure tradeReserver(resType:string);
    procedure reserveFinish;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhTradeReserve: TfaqhTradeReserve;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhTradeReserve.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
end;

procedure TfaqhTradeReserve.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhTradeReserve.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  btnReserved.Enabled := False;
  WorkView.FieldByName('查询类型').data.SetString('4');
  inherited;
  btnReserved.Enabled := True;
end;

procedure TfaqhTradeReserve.btnReservedClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要对该记录进行冲正操作吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tradeReserver('0');
  reserveFinish;
end;

procedure TfaqhTradeReserve.tradeReserver(resType: string);
var
  tmpData:TDataSet;
  operDate:string;
  seriId:Integer;
  tradeId:Integer;
  operCode:string;
  operPwd:string;
begin
  //inherited;
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  operDate := tmpData.fieldbyname('sdate3').AsString;
  seriId := tmpData.fieldbyname('lserial1').AsInteger;
  tradeId := tmpData.fieldbyname('lwithdraw_flag').AsInteger;
  operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
  operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
  WVReserved.FieldByName('操作员密码').Data.SetString(operPwd);
  WVReserved.FieldByName('业务日期').Data.SetString(operDate);
  WVReserved.FieldByName('流水号').Data.SetInteger(seriId);
  WVReserved.FieldByName('冲正类型').Data.SetString(resType);
  WVReserved.FieldByName('是否授权').Data.SetString('1');
  WVReserved.FieldByName('终端编号').Data.SetInteger(tradeId);
  WVRReserved.SendCommand;
  if WVReserved.FieldByName('返回码').Data.AsInteger=0 then
  begin
    if resType='1' then
      Context.GetDialogSystem.ShowMessage('该记录的冲正记录已经被撤销！')
    else
      Context.GetDialogSystem.ShowMessage('该记录已经冲正成功！');
    RzStatusPane1.Caption := WVReserved.fieldbyname('返回信息').Data.AsString;
  end;
end;

procedure TfaqhTradeReserve.reserveFinish;
begin
  //edtOper.Text := '';
  edtPwd.Text := '';
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('交易冲正',TfaqhTradeReserve);

end.