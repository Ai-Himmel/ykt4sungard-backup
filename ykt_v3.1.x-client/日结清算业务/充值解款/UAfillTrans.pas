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
  WorkView.FieldByName('操作员号').DefaultValue := '';
  WorkView.FieldByName('密码').DefaultValue := '';
  WorkView.FieldByName('食堂账号').DefaultValue := '';
  WorkView.FieldByName('金额').DefaultValue := 0.00;
  WorkView.FieldByName('备注').DefaultValue := '';
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
  if Application.MessageBox('你确定要进行充值解款操作吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  inherited;
  if WorkView.FieldByName('返回码').Data.AsInteger=0 then
    ShowMessage(WorkView.FieldByName('返回信息').Data.AsString);
end;

initialization
  TUIStdClassFactory.Create('充值解款',TfaqhfillTrans);

end.