unit UASetPOSInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhSetPOSInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label26: TLabel;
	WVEdit4: TWVEdit;
	WVEdit5: TWVEdit;
	WVEdit8: TWVEdit;
    WVEdit19: TWVEdit;
    WVEdit20: TWVEdit;
    edtPosName: TWVEdit;
    edtDate: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVComboBox6: TWVComboBox;
    WVComboBox7: TWVComboBox;
    edtPosIdQ: TWVEdit;
    edtBusiIdQ: TWVEdit;
    edtPosId: TWVEdit;
    edtBusiId: TWVEdit;
    Label1: TLabel;
    WVComboBox8: TWVComboBox;
    Label11: TLabel;
    WVEdit1: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetPOSInfo: TfaqhSetPOSInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhSetPOSInfo.Init;
begin
  inherited;
  {
  WorkView.FieldByName('查询.操作标志').DefaultValue := '';
  WorkView.FieldByName('查询.设备编号').DefaultValue := 0;
  WorkView.FieldByName('查询.所属商户号').DefaultValue := 0;
  WorkView.FieldByName('查询.设备终端号').DefaultValue := '';
  WorkView.FieldByName('查询.终端序列号').DefaultValue := '';
  WorkView.FieldByName('查询.设备型号').DefaultValue := 0;
  WorkView.FieldByName('查询.设备类型').DefaultValue := 0;
  WorkView.FieldByName('查询.设备名称').DefaultValue := '';
  WorkView.FieldByName('查询.用途').DefaultValue := 0;
  WorkView.FieldByName('查询.设备状态').DefaultValue := '';
  WorkView.FieldByName('查询.启用日期').DefaultValue := '';
  WorkView.FieldByName('查询.注册日期').DefaultValue := '';
  WorkView.FieldByName('查询.删除日期').DefaultValue := '';
  WorkView.FieldByName('查询.最后更新时间').DefaultValue := '';
  WorkView.FieldByName('查询.备注').DefaultValue := ;
  WorkView.FieldByName('操作标志').DefaultValue := '';
  WorkView.FieldByName('设备机编号').DefaultValue := 0;
  WorkView.FieldByName('所属商户号').DefaultValue := 0;
  WorkView.FieldByName('设备终端号').DefaultValue := '';
  WorkView.FieldByName('终端序列号').DefaultValue := '';
  WorkView.FieldByName('设备型号').DefaultValue := 0;
  WorkView.FieldByName('设备类型').DefaultValue := 0;
  WorkView.FieldByName('设备名称').DefaultValue := '';
  WorkView.FieldByName('用途').DefaultValue := 0;
  WorkView.FieldByName('设备状态').DefaultValue := '';
  WorkView.FieldByName('启用日期').DefaultValue := '';
  WorkView.FieldByName('注册日期').DefaultValue := '';
  WorkView.FieldByName('删除日期').DefaultValue := '';
  WorkView.FieldByName('最后更新时间').DefaultValue := '';
  WorkView.FieldByName('备注').DefaultValue := ;
  WorkView.Reset;
  }
end;

procedure TfaqhSetPOSInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  //btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetPOSInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetPOSInfo.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBusiIdQ.Text)='' then
    edtBusiIdQ.Text := '0';
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;
end;

procedure TfaqhSetPOSInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
  edtPosId.Text := '0';
  edtPosId.Enabled := False;
end;

procedure TfaqhSetPOSInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('E');
  edtPosId.Enabled := False;
end;

procedure TfaqhSetPOSInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
  edtPosId.Enabled := False;
end;

procedure TfaqhSetPOSInfo.btnOKClick(Sender: TObject);
begin
  if Trim(edtDate.Text)<>'' then
    if CheckInputDateFormat(edtDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('启用日期输入不正确，格式：yyyymmdd');
      edtDate.SetFocus;
      Exit;
    end;
  if Trim(edtPosName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('设备名称不能为空');
    edtPosName.SetFocus;
    Exit;
  end;
  if WorkView.FieldByName('地区编码').Data.AsString='' then
  begin
    Context.GetDialogSystem.ShowMessage('请选择地区编码！');
    Exit;
  end;
  if Trim(edtBusiId.Text)='' then
    edtBusiId.Text := '0';
  inherited;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('设备信息维护',TfaqhSetPOSInfo);

end.