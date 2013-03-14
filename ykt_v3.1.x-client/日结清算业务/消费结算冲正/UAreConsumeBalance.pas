unit UAreConsumeBalance;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhreConsumeBalance = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    edtOperCode: TWVEdit;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    Label13: TLabel;
    WVComboBox1: TWVComboBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
    sOperCode : string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhreConsumeBalance: TfaqhreConsumeBalance;

implementation

uses KsFrameworks, KSClientConsts;
     
{$R *.DFM}

procedure TfaqhreConsumeBalance.Init;
begin
  inherited;
  {
  WorkView1.FieldByName('�ɼ���ʼ����').DefaultValue := '';
  WorkView1.FieldByName('�ɼ���ʼʱ��').DefaultValue := '';
  WorkView1.FieldByName('�ɼ���������').DefaultValue := '';
  WorkView1.FieldByName('�ɼ�����ʱ��').DefaultValue := '';
  WorkView1.FieldByName('��ˮ��').DefaultValue := 0;
  WorkView1.FieldByName('�ϴ�����ˮ��').DefaultValue := 0;
  WorkView1.FieldByName('���״���').DefaultValue := 0;
  WorkView1.FieldByName('��ˮ״̬').DefaultValue := 0;
  WorkView1.FieldByName('�ϴ�����վ��ʶ').DefaultValue := 0;
  WorkView1.FieldByName('���׷����豸��ʶ').DefaultValue := 0;
  WorkView1.FieldByName('���׿���').DefaultValue := 0;
  WorkView1.FieldByName('�ͻ���ʶ').DefaultValue := 0;
  WorkView.FieldByName('����Ա��').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('������ˮ��').DefaultValue := 0;
  WorkView.Reset;
  }
  btnPrint.Caption := '�������';
  sOperCode := Context.ParamData(svOperatorNoName).AsString;
  edtOperCode.Text := sOperCode;
end;

procedure TfaqhreConsumeBalance.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhreConsumeBalance.btnQueryClick(Sender: TObject);
var
  sDate:string;
begin
  sDate := FormatDateTime('yyyymmdd',Date);
  WorkView1.FieldByName('�ɼ���ʼ����').Data.SetString(sDate);
  WorkView1.FieldByName('�ɼ���������').Data.SetString(sDate);
  WorkView1.FieldByName('���״���').Data.SetInteger(847222);
  WorkView1.FieldByName('��ˮ��').Data.SetInteger(0);
  WorkView1.FieldByName('�ϴ�����ˮ��').Data.SetInteger(0);
  WorkView1.FieldByName('��ˮ״̬').Data.SetInteger(0);
  WorkView1.FieldByName('�ϴ�����վ��ʶ').Data.SetInteger(0);
  WorkView1.FieldByName('���׷����豸��ʶ').Data.SetInteger(0);
  WorkView1.FieldByName('���׿���').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ���ʶ').Data.SetInteger(0);
  //inherited;
  WVRequest1.SendCommand;
end;

procedure TfaqhreConsumeBalance.btnPrintClick(Sender: TObject);
var
  serialNo:Integer;
begin
  if Application.MessageBox('��ȷ��Ҫ�������ѽ������������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject).IsEmpty then
  begin
    ShowMessage('û��Ҫ�����Ľ��ף�');
    Exit;
  end;
  serialNo := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject).fieldbyname('lvol0').AsInteger;
  WorkView.FieldByName('������ˮ��').Data.SetInteger(serialNo);
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger=0 then
    ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString);
end;

initialization
  TUIStdClassFactory.Create('���ѽ������',TfaqhreConsumeBalance);

end.