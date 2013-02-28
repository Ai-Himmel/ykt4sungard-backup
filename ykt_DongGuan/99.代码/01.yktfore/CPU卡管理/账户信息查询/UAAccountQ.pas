unit UAAccountQ;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll;

type
  TfaqhAccountQ = class(TfaqhSimpleQueryTemp)
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
    edtCustName: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit11: TWVEdit;
    edtAppSerialNo: TWVEdit;
    cbbDept: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    btnReadCard: TBitBtn;
    WVComboBox3: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhAccountQ: TfaqhAccountQ;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhAccountQ.Init;
begin
  inherited;
  {
  WorkView.FieldByName('客户号').DefaultValue := 0;
  WorkView.FieldByName('姓名').DefaultValue := '';
  WorkView.FieldByName('证件类型').DefaultValue := '';
  WorkView.FieldByName('证件号码').DefaultValue := '';
  WorkView.FieldByName('发卡部门').DefaultValue := '';
  WorkView.FieldByName('电话').DefaultValue := '';
  WorkView.FieldByName('手机').DefaultValue := '';
  WorkView.FieldByName('卡号').DefaultValue := '';
  WorkView.FieldByName('卡物理编号').DefaultValue := '';
  WorkView.FieldByName('卡类型').DefaultValue := 0;
  WorkView.FieldByName('制卡日期').DefaultValue := '';
  WorkView.FieldByName('发行批次号').DefaultValue := 0;
  WorkView.Reset;
  }
end;

procedure TfaqhAccountQ.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCustName.Text)='' then
    edtCustName.Text := '0';
  inherited;

end;

procedure TfaqhAccountQ.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppSerialNo.Text:='';
  try
    cardNo := readCardOneInfo(CF_APPSERIALNO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，应用序列号为零或不存在!');
    Exit;
  end;
  edtAppSerialNo.Text:=cardNo;
  btnQuery.Click();
end;

initialization
  TUIStdClassFactory.Create('账户信息查询',TfaqhAccountQ);

end.