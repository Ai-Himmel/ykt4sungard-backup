unit UAgateSerialDetailQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhgateSerialDetailQuery = class(TfaqhSimpleQueryTemp)
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
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    Label10: TLabel;
    WVEdit10: TWVEdit;
    Label11: TLabel;
    WVEdit11: TWVEdit;
    WVComboBox7: TWVComboBox;
    lbl1: TLabel;
    Label12: TLabel;
    WVComboBox1: TWVComboBox;
    Label13: TLabel;
    WVComboBox6: TWVComboBox;
    lblMachineType: TWVLabel;
    cbbMachineType: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhgateSerialDetailQuery: TfaqhgateSerialDetailQuery;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhgateSerialDetailQuery.Init;
var
  sDate,sTime:string;
begin
  sDate := FormatDateTime('yyyymmdd',Date);
  sTime := FormatDateTime('hhmmss',Now);
  inherited;
  WorkView.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView.FieldByName('�¼�').DefaultValue := 0;
  WorkView.FieldByName('���׿���').DefaultValue := 0;
  WorkView.FieldByName('������').DefaultValue := '';
  WorkView.FieldByName('��ʼ����').DefaultValue := sDate;
  WorkView.FieldByName('��ʼʱ��').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := sDate;
  WorkView.FieldByName('����ʱ��').DefaultValue := '';
  WorkView.FieldByName('�豸��ʶ').DefaultValue := 0;
  WorkView.FieldByName('�豸������').DefaultValue := '';
  WorkView.Reset;
end;

procedure TfaqhgateSerialDetailQuery.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



initialization
  TUIStdClassFactory.Create('�Ž���ˮ��ѯ',TfaqhgateSerialDetailQuery);

end.