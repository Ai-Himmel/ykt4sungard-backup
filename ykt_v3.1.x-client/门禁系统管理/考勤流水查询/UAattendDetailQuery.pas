unit UAattendDetailQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhattendDetailQuery = class(TfaqhSimpleQueryTemp)
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
    edtCustNo: TWVEdit;
    WVEdit3: TWVEdit;
    edtCardNo: TWVEdit;
    WVEdit5: TWVEdit;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    WVComboBox6: TWVComboBox;
    Label10: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhattendDetailQuery: TfaqhattendDetailQuery;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhattendDetailQuery.Init;
var
  sDate:string;
begin
  inherited;
  sDate := FormatDateTime('yyyymmdd',Date);
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView.FieldByName('ѧ����').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := 0;
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('��ʼ����').DefaultValue := sDate;
  WorkView.FieldByName('��������').DefaultValue := sDate;
  WorkView.FieldByName('��ʼʱ��').DefaultValue := '';
  WorkView.FieldByName('����ʱ��').DefaultValue := '';
  WorkView.Reset;
end;

procedure TfaqhattendDetailQuery.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhattendDetailQuery.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCardNo.Text) = '' then
    edtCardNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  inherited;

end;

initialization
  TUIStdClassFactory.Create('������ˮ��ѯ',TfaqhattendDetailQuery);

end.