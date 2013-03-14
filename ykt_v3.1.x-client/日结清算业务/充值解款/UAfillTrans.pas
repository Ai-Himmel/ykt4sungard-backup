unit UAfillTrans;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhfillTrans = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnTrans: TBitBtn;
    Label1: TLabel;
    edtOperCode: TWVEdit;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit4: TWVEdit;
    Label4: TLabel;
    Label5: TLabel;
    Label3: TLabel;
    WVComboBox3: TWVComboBox;
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
  faqhfillTrans: TfaqhfillTrans;

implementation

uses KsFrameworks, KSClientConsts;
     
{$R *.DFM}

procedure TfaqhfillTrans.Init;
begin
  inherited;
  {
  WorkView.FieldByName('����Ա��').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('ʳ���˺�').DefaultValue := '';
  WorkView.FieldByName('���').DefaultValue := 0.00;
  WorkView.FieldByName('��ע').DefaultValue := '';
  WorkView.Reset;
  }
  edtOperCode.Text := Context.ParamData(svOperatorNoName).AsString;
end;

procedure TfaqhfillTrans.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhfillTrans.btnQueryClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ���г�ֵ��������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  inherited;
  if WorkView.FieldByName('������').Data.AsInteger=0 then
    ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString);
end;

initialization
  TUIStdClassFactory.Create('��ֵ���',TfaqhfillTrans);

end.