unit UABankBingdingQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhBankBingdingQuery = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    edtErrorCode: TWVEdit;
    cbbQFeeType: TWVComboBox;
    Label8: TLabel;
    WVComboBox1: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBankBingdingQuery: TfaqhBankBingdingQuery;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhBankBingdingQuery.Init;
begin
  inherited;
  {
  WorkView.FieldByName('���ײο���').DefaultValue := '';
  WorkView.FieldByName('�������κ�').DefaultValue := '';
  WorkView.FieldByName('���׿�ʼ����').DefaultValue := '';
  WorkView.FieldByName('���׽�������').DefaultValue := '';
  WorkView.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView.FieldByName('ѧ��').DefaultValue := '';
  WorkView.FieldByName('���п���').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := 0;
  WorkView.FieldByName('��ɾ��־').DefaultValue := 0;
  WorkView.FieldByName('������').DefaultValue := 0;
  WorkView.Reset;
  }
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
end;

procedure TfaqhBankBingdingQuery.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtErrorCode.Text)='' then
    edtErrorCode.Text := '0';
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ:yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�������벻��ȷ����ʽ:yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ�������!');
  inherited;

end;

initialization
  TUIStdClassFactory.Create('���п�����ˮ��ѯ',TfaqhBankBingdingQuery);

end.