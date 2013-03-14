unit UAQueryBusinessEquipByOther;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, SmartCardCommon, Buttons, EditExts;

type
  TfaqhQueryBusinessEquipByOther = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label3: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    edtBDate: TWVEdit;
    edtETime: TWVEdit;
    edtEDate: TWVEdit;
    Label10: TLabel;
    WVLabel1: TWVLabel;
    WVLabel2: TWVLabel;
    Label7: TLabel;
    WVEdit1: TWVEdit;
    Label2: TLabel;
    WVComboBox2: TWVComboBox;
    edtId: TWVDigitalEdit;
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
  faqhQueryBusinessEquipByOther: TfaqhQueryBusinessEquipByOther;

implementation

uses KsFrameworks, 
     KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhQueryBusinessEquipByOther.Init;
begin
  inherited;
end;

procedure TfaqhQueryBusinessEquipByOther.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhQueryBusinessEquipByOther.btnQueryClick(Sender: TObject);
begin
  if (not CheckInputDateFormat(edtBDate.Text))
    and (edtBDate.Text <> '')then
  begin
    Context.GetDialogSystem.ShowMessage('设备启用日期输入有误！');
    Exit;
  end;
  if (not CheckInputDateFormat(edtEDate.Text))
    and (edtEDate.Text <> '') then
  begin
    Context.GetDialogSystem.ShowMessage('设备停用日期输入有误！');
    Exit;
  end;
  if (not CheckInputTimeFormat(edtETime.Text))
    and (edtETime.Text <> '') then
  begin
    Context.GetDialogSystem.ShowMessage('使用结束时间输入有误！');
    Exit;
  end;
  inherited;
end;

initialization
  TUIStdClassFactory.Create('设备商户关系查询',TfaqhQueryBusinessEquipByOther);

end.