unit UASetSubSystemInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  UIncrementComboBox, RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs,
  Buttons;

type
  TfaqhSetSubSystemInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    WVDigitalEdit2: TWVDigitalEdit;
    WVEdit3: TWVEdit;
	WVComboBox4: TWVComboBox;
    WVEdit6: TWVEdit;
    WVDigitalEdit7: TWVDigitalEdit;
    WVEdit10: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    WVLabel2: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel3: TWVLabel;
    WVEdit2: TWVEdit;
    WVLabel4: TWVLabel;
    WVComboBox3: TWVComboBox;
    WVLabel5: TWVLabel;
    WVEdit4: TWVEdit;
    WVLabel6: TWVLabel;
    WVEdit5: TWVEdit;
    WVDigitalEdit8: TWVEdit;
    WVDigitalEdit9: TWVEdit;
    WVLabel7: TWVLabel;
    WVLabel8: TWVLabel;
    WVLabel9: TWVLabel;
    cbbency: TWVComboBox;
    Label2: TLabel;
    WVEdit7: TWVEdit;
    Label13: TLabel;
    WVEdit8: TWVEdit;
    WVLabel10: TWVLabel;
    Label1: TLabel;
    WVLabel11: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVEdit9: TWVEdit;
    WVLabel12: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit11: TWVEdit;
    WVLabel13: TWVLabel;
    WVLabel14: TWVLabel;
    WVEdit12: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVLabel15: TWVLabel;
    cbbSubSystem: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure WVDigitalEdit8DblClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure btnViewDetailClick(Sender: TObject);
  private
    { Private declarations }
  public
    procedure Init; override;
    function SubSystemCheckSave:Boolean;
    { Public declarations }
  end;

var
  faqhSetSubSystemInfo: TfaqhSetSubSystemInfo;

implementation

uses KsFrameworks, 
     KSDataDictionary,UWorkerNum,SmartCardCommon;
     
{$R *.DFM}

function TfaqhSetSubSystemInfo.SubSystemCheckSave:Boolean;
var TmpMsg:String;
begin
  Result:=True;
  if Trim(WVEdit3.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入子系统名称！','');
    WVEdit3.SetFocus;
    Result:=False;
    Exit;
  end;
  if Trim(WVEdit6.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入IP地址！','');
    WVEdit6.SetFocus;
    Result:=False;
    Exit;
  end;
  if Trim(WVEdit4.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入MAC地址！','');
    WVEdit4.SetFocus;
    Result:=False;
    Exit;
  end;
  if Trim(WVEdit4.Text)<>'' then
  begin
    TmpMsg:=CheckMACAddress(Trim(WVEdit4.Text));
    if TmpMsg<>'' then
    begin
      Context.GetDialogSystem.ShowMessage(TmpMsg);
      WVEdit4.SetFocus;
      Result:=False;
      Exit;
    end;
  end;
  if Trim(WVEdit6.Text)<>'' then
  begin
    TmpMsg:=CheckIpAddress(Trim(WVEdit6.Text));
    if TmpMsg<>'' then
    begin
      Context.GetDialogSystem.ShowMessage(TmpMsg);
      WVEdit6.SetFocus;
      Result:=False;
      Exit;
    end;
  end;
  if ((WVComboBox3.itemindex=-1) or (WVComboBox3.itemindex=0)) then
  begin
    Context.GetDialogSystem.ShowMessage('请选择子系统类别！');
    Result:=False;
    Exit;
  end;
  if WVComboBox4.itemindex=-1 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择所在区域！');
    Result:=False;
    Exit;
  end;
  if strtoint(WVDigitalEdit7.text)>65535 then
  begin
    Context.GetDialogSystem.ShowMessage('请输入1-65535之间的整数！');
    Result:=False;
    Exit;
  end;
end;



procedure TfaqhSetSubSystemInfo.Init;
begin
  inherited;
  WVComboBox1.ItemIndex:=0;
  WVComboBox2.ItemIndex:=0;
  WVComboBox3.ItemIndex:=0;
  WVComboBox4.ItemIndex:=0;
  WVDigitalEdit8.readonly:=True;
end;

procedure TfaqhSetSubSystemInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetSubSystemInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetSubSystemInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WVLabel6.Visible:=False;
  WVLabel2.Visible:=False;
  WVLabel3.Visible:=False;
  WVDigitalEdit2.Visible:=False;
  WVComboBox2.Visible:=False;
  WVDigitalEdit2.Enabled:=True;
  WVComboBox2.Enabled:=True;
  WVEdit2.Enabled:=True;
  WVComboBox2.ItemIndex:=0;
  WVDigitalEdit8.readonly:=True;
  WVEdit2.Visible:=False;
  WVLabel3.Visible:=False;
  WVEdit2.Visible:=False;
end;

procedure TfaqhSetSubSystemInfo.btnChangeClick(Sender: TObject);
begin
  WVLabel6.Visible:=True;
  WVLabel2.Visible:=True;
  WVLabel3.Visible:=True;
  WVDigitalEdit2.Visible:=True;
  WVComboBox2.Visible:=True;
  WVEdit2.Visible:=True;
  WVDigitalEdit2.ReadOnly:=True;
  WVLabel3.Visible:=False;
  WVEdit2.Visible:=False;
  if (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol2').Asinteger=6 then
  begin
    Context.GetDialogSystem.ShowWarning('不能对状态为注销的子系统进行信息修改！');
    Exit;
  end;
  inherited;
  WVDigitalEdit8.readonly:=True;
  WVComboBox2.Enabled:=False;
end;

procedure TfaqhSetSubSystemInfo.btnDeleteClick(Sender: TObject);
begin
  if (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol2').Asinteger=6 then
  begin
    Context.GetDialogSystem.ShowWarning('不能对状态为注销的子系统再进行注销操作！');
    Exit;
  end;
  inherited;
  WVLabel6.Visible:=True;
  WVLabel2.Visible:=True;
  WVLabel3.Visible:=True;
  WVDigitalEdit2.Visible:=True;
  WVComboBox2.Visible:=True;
  WVEdit2.Visible:=True;
  WVDigitalEdit2.ReadOnly:=True;
  WVLabel3.Visible:=False;
  WVEdit2.Visible:=False;
  inherited;
end;

procedure TfaqhSetSubSystemInfo.btnCancelClick(Sender: TObject);
begin
  inherited;
  WVLabel6.Visible:=True;
  WVLabel2.Visible:=True;
  WVLabel3.Visible:=True;
  WVDigitalEdit2.Visible:=True;
  WVComboBox2.Visible:=True;
  WVEdit2.Visible:=True;
  QueryRequest.SendCommand;
end;

procedure TfaqhSetSubSystemInfo.btnQueryClick(Sender: TObject);
begin
  inherited;
  FreeIdObjects(-32);
  cbbSubSystem.Clear;
  cbbSubSystem.ItemsDataEntry:='';
  cbbSubSystem.ItemsDataEntry:='*-32';
  cbbSubSystem.ItemIndex:=0;
end;

procedure TfaqhSetSubSystemInfo.WVDigitalEdit8DblClick(Sender: TObject);
begin
  QueryWorkerNum:=TQueryWorkerNum.Create(nil);
  try
    QueryWorkerNum.ShowModal;
    WorkView.FieldByName('负责人员工号').Data.SetString(QueryWorkerNum.WorkerInfo.WorkerNo);
  finally
    QueryWorkerNum.Free;
  end;
end;

procedure TfaqhSetSubSystemInfo.btnOKClick(Sender: TObject);
begin
  if Trim(WVEdit3.Text)='' then
  begin
    ShowMessage('请输入子系统名称！');
    WVEdit3.SetFocus;
    Exit;
  end;
  if not SubSystemCheckSave then  exit
  else inherited;
  FreeIdObjects(-32);
  WVComboBox1.Clear;
  WVComboBox1.ItemsDataEntry:='';
  WVComboBox1.ItemsDataEntry:='*-32';
  WVComboBox1.ItemIndex:=0;
  btnQuery.Click;
end;

procedure TfaqhSetSubSystemInfo.GridDblClick(Sender: TObject);
begin
  inherited;
  WVEdit2.ReadOnly:=True;
  WVEdit2.Visible:=False;
  WVLabel3.Visible:=False;
end;

procedure TfaqhSetSubSystemInfo.btnViewDetailClick(Sender: TObject);
begin
  inherited;
  WVEdit2.Visible:=False;
  WVLabel3.Visible:=False;

end;

initialization
  TUIStdClassFactory.Create('子系统设置',TfaqhSetSubSystemInfo);

end.