unit UAGateTimeWeekManager;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhGateTimeWeekManager = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label7: TLabel;
    Label10: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit10: TWVEdit;
    Label12: TLabel;
    WVComboBox7: TWVComboBox;
    cbbScode: TWVComboBox;
    btnDelete: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhGateTimeWeekManager: TfaqhGateTimeWeekManager;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhGateTimeWeekManager.Init;
begin
  inherited;
  WorkView.FieldByName('操作类别').DefaultValue := '';
  WorkView.FieldByName('控制器编号').DefaultValue := 0;
  WorkView.FieldByName('子系统').DefaultValue := 0;
  WorkView.FieldByName('控制器名称').DefaultValue := '';
  WorkView.FieldByName('设备物理编号').DefaultValue := '';
  WorkView.FieldByName('设备名称').DefaultValue := '';
  WorkView.FieldByName('设备物理型号').DefaultValue := '';
  WorkView.FieldByName('设备机型').DefaultValue := '';
  WorkView.FieldByName('所属区域').DefaultValue := '';
  WorkView.FieldByName('时间周编号').DefaultValue := 0;
  WorkView.FieldByName('时间周名称').DefaultValue := '';
  WorkView.Reset;
  btnDelete.Caption := '&D 删除';
end;

procedure TfaqhGateTimeWeekManager.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作类别').Data.SetString('R');
  inherited;

end;

procedure TfaqhGateTimeWeekManager.btnDeleteClick(Sender: TObject);
var
  colId,devId,weekId:Integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，请先查询，然后再进行操作！');
    Exit;
  end;
  if Application.MessageBox('你确定要删除所选择的门禁时间周吗？',PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  try
    colId := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
    //取客户号
    devId := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol2').AsInteger;
    weekId := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol3').AsInteger;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  WorkView1.FieldByName('操作类别').Data.SetString('D');
  WorkView1.FieldByName('控制器编号').Data.SetInteger(colId);
  WorkView1.FieldByName('设备编号').Data.SetInteger(devId);
  WorkView1.FieldByName('时间周编号').Data.SetInteger(weekId);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
  begin
    Context.GetDialogSystem.ShowMessage('删除门禁时间周成功！');
  end;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('门禁时间周管理',TfaqhGateTimeWeekManager);

end.