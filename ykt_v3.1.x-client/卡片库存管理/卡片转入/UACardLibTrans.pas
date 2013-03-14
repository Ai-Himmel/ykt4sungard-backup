unit UACardLibTrans;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,UtCardDll,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzStatus, RzPanel;

type
  TfaqhCardLibTrans = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    WVCardTrans: TWorkView;
    WVRCardTrans: TWVRequest;
    grp1: TGroupBox;
    Label2: TLabel;
    lblTransTo: TLabel;
    lblBNo: TLabel;
    Label3: TLabel;
    cbbCardType: TWVComboBox;
    edtBNo: TEdit;
    edtENo: TEdit;
    chkReadCard: TCheckBox;
    chkInfo: TCheckBox;
    btnJoin: TBitBtn;
    RzStatusBar1: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    cbbOperTrans: TWVComboBox;
    Label1: TLabel;
    WVComboBox3: TWVComboBox;
    edtPatchNo: TWVEdit;
    lbl1: TLabel;
    Label7: TLabel;
    WVComboBox4: TWVComboBox;
    Label6: TLabel;
    Label4: TLabel;
    edtShowCardNo: TWVEdit;
    WVComboBox2: TWVComboBox;
    Label8: TLabel;
    edtPwd: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnJoinClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardLibTrans: TfaqhCardLibTrans;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;

{$R *.DFM}

procedure TfaqhCardLibTrans.Init;
begin
  inherited;
end;

procedure TfaqhCardLibTrans.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhCardLibTrans.btnJoinClick(Sender: TObject);
var
  cardType:string;
  operCode:string;
  showCardNo:string;
  operPwd:string;
begin
  cardType := Copy(cbbCardType.Text,0,Pos('-',cbbCardType.Text)-1);
  operCode := Copy(cbbOperTrans.Text,0,Pos('-',cbbOperTrans.Text)-1);
  if ((cardType='')or(cardType='-')or(operCode='')or(operCode='-')) then
  begin
    ShowMessage('请选择要转交卡片的类型和要领入的操作员！');
    exit;
  end;

  if chkInfo.Checked then
    if Application.MessageBox('你确定要转交该类型的卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;

  if chkReadCard.Checked then
  begin
    showCardNo := readShowCarNo;
    edtBNo.Text := showCardNo;
    edtENo.Text := showCardNo;
  end;
  operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
  WVCardTrans.FieldByName('转入密码').Data.SetString(operPwd);
  WVCardTrans.FieldByName('起始编号').Data.SetString(edtBNo.Text);
  WVCardTrans.FieldByName('截至编号').Data.SetString(edtENo.Text);
  WVRCardTrans.SendCommand;
  RzStatusPane1.Caption := WVCardTrans.fieldbyname('返回信息').Data.AsString;
  edtPwd.Text := '';
  btnQueryClick(Sender);
end;

procedure TfaqhCardLibTrans.GridCellClick(Column: TColumn);
var
  tmpData:TDataSet;
begin
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  try
    edtBNo.Text := tmpData.FieldByName('scust_no').AsString;
    edteNo.Text := tmpData.FieldByName('scust_no').AsString;
    WVCardTrans.FieldByName('卡类型').Data.SetInteger(tmpData.FieldByName('lvol0').AsInteger);
  except
    on e:Exception do
      Context.GetDialogSystem.ShowMessage(e.Message);
  end;
end;

procedure TfaqhCardLibTrans.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('转入操作员').Data.SetString(context.GetParamValue(svOperatorNoName));
  inherited;

end;

initialization
  TUIStdClassFactory.Create('卡片转出',TfaqhCardLibTrans);

end.