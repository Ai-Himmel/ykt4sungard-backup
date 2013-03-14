unit UAquerySublidyList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhquerySublidyList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    edtPatchNo: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    cbbType: TWVComboBox;
    Label10: TLabel;
    edtCustNo: TWVEdit;
    Label9: TLabel;
    edtCardno: TWVEdit;
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
  faqhquerySublidyList: TfaqhquerySublidyList;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhquerySublidyList.Init;
begin
  inherited;
  {
  WorkView.FieldByName('ѧ����').DefaultValue := '';
  WorkView.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView.FieldByName('�������κ�').DefaultValue := 0;
  WorkView.FieldByName('����').DefaultValue := 0;
  WorkView.FieldByName('�������κ�').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('��ȡ����').DefaultValue := '';
  WorkView.FieldByName('���������֤��').DefaultValue := '';
  WorkView.FieldByName('����������').DefaultValue := '';
  WorkView.FieldByName('״̬').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhquerySublidyList.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhquerySublidyList.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtPatchNo.Text)='' then
    edtPatchNo.Text := '0';
  if Trim(edtCardno.Text)='' then
    WorkView.FieldByName('����').Data.SetInteger(0);
  WorkView.FieldByName('��������').Data.SetString('R');
  inherited;

end;

initialization
  TUIStdClassFactory.Create('������Ϣ��ѯ',TfaqhquerySublidyList);

end.