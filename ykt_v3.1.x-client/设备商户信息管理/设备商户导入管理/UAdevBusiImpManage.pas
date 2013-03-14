unit UAdevBusiImpManage;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs;

type
  TfaqhdevBusiImpManage = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label20: TLabel;
    Label22: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
	WVEdit2: TWVEdit;
	WVEdit6: TWVEdit;
	WVEdit7: TWVEdit;
	WVEdit9: TWVEdit;
    edtPatchNo: TWVEdit;
    edtDevName: TWVEdit;
    edtBusiName: TWVEdit;
    edtEndTime: TWVEdit;
    edtStartDate: TWVEdit;
    edtStopDate: TWVEdit;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    WVImpCheck: TWorkView;
    WVRImpCheck: TWVRequest;
    edtDevNo: TWVEdit;
    edtBusiNo: TWVEdit;
    edtNO: TWVEdit;
    btnPatchDel: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label33: TLabel;
    edtDelPatchNo: TWVEdit;
    pbstat: TProgressBar;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnPatchDelClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhdevBusiImpManage: TfaqhdevBusiImpManage;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhdevBusiImpManage.Init;
begin
  inherited;
end;

procedure TfaqhdevBusiImpManage.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhdevBusiImpManage.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhdevBusiImpManage.btnAddClick(Sender: TObject);
var
  tmpDate:TDataSet;
  patchNo:string;
  No:Integer;
begin
  //inherited;
  if Application.MessageBox('你确定要审核该批设备商户绑定关系吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  try
    tmpDate := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
    tmpDate.Last;
    pbstat.Max := tmpDate.RecordCount;
    tmpDate.First;
    while not tmpDate.Eof do
    begin
      patchNo := tmpDate.fieldbyname('scust_limit').AsString;
      no := tmpDate.fieldbyname('lvol4').AsInteger;
      WVImpCheck.FieldByName('导入批次号').Data.SetString(patchNo);
      WVImpCheck.FieldByName('导入顺序号').Data.SetInteger(No);
      WVImpCheck.FieldByName('操作标志').Data.SetString('C');
      WVRImpCheck.SendCommand;
      Sleep(50);
      pbstat.Position := pbstat.Position+1;
      tmpDate.Next;
    end;
    pbstat.Position := pbstat.Max;
    Context.GetDialogSystem.ShowMessage('设备商户关系绑定审核完成！');
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(ex.Message);
    end;
  end;
end;

procedure TfaqhdevBusiImpManage.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('U');
  edtPatchNo.Enabled := False;
  edtNo.Enabled := False;
  edtBusiName.Enabled := False;
  edtDevName.Enabled := False;
end;

procedure TfaqhdevBusiImpManage.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
end;

procedure TfaqhdevBusiImpManage.btnQueryClick(Sender: TObject);
begin
  if Trim(edtDevNo.Text)='' then
    edtDevNo.Text := '0';
  if Trim(edtBusiNo.Text)='' then
    edtBusiNo.Text := '0';
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    btnPatchDel.Enabled := False;
    btnAdd.Enabled := False;
  end
  else
  begin
    btnAdd.Enabled := True;
    btnPatchDel.Enabled :=True;
  end;
end;

procedure TfaqhdevBusiImpManage.btnOKClick(Sender: TObject);
begin
  if (Trim(edtStartDate.Text)<>'') and (CheckInputDateFormat(edtStartDate.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('启用日期输入格式不正确！');
    edtStartDate.SetFocus;
    Exit;
  end;
  if (Trim(edtStopDate.Text)<>'') and (CheckInputDateFormat(edtStopDate.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('停用日期输入格式不正确！');
    edtStopDate.SetFocus;
    Exit;
  end;
  if (Trim(edtEndTime.Text)<>'') and (CheckInputTimeFormat(edtEndTime.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('结束时间输入格式不正确！');
    edtEndTime.SetFocus;
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhdevBusiImpManage.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该批次号的设备商户吗？',PChar(Application.Title),MB_YESNO)=idno then
    Exit;
  if edtDelPatchNo.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入要批量删除的批次号！');
    Exit;
  end;
  WorkView1.FieldByName('操作标志').Data.SetString('D');
  WorkView1.FieldByName('批量标志').Data.SetInteger(1);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
    edtDelPatchNo.Text :='';
  Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString);
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('设备商户导入管理',TfaqhdevBusiImpManage);

end.