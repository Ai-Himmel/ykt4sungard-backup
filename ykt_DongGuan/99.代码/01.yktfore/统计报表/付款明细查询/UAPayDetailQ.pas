unit UAPayDetailQ;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhPayDetailQ = class(TfaqhSimpleQueryTemp)
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
    edtDDate: TWVEdit;
    edtCdate: TWVEdit;
    edtBusiId: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    cbbNetInfo: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPayDetailQ: TfaqhPayDetailQ;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhPayDetailQ.Init;
begin
  inherited;
end;

procedure TfaqhPayDetailQ.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCdate.Text)<>'' then
    if CheckInputDateFormat(edtCdate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtCdate.SetFocus;
      Exit;
    end;
  if Trim(edtDDate.Text)<>'' then
    if CheckInputDateFormat(edtDDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('ί���������벻��ȷ����ʽ��yyyymmdd');
      edtDDate.SetFocus;
      Exit;
    end;
  if (edtBusiId.Text='') then
    edtBusiId.Text :='0';
  inherited;

end;

initialization
  TUIStdClassFactory.Create('������ϸ��ѯ',TfaqhPayDetailQ);

end.