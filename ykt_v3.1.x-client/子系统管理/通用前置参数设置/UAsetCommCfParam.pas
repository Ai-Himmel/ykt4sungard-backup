unit UAsetCommCfParam;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  Buttons;

type
  TfaqhsetCommCfParam = class(TfaqhSetParamsTemp)
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
    Label27: TLabel;
    Label28: TLabel;
    Label29: TLabel;
    WVEdit16: TWVEdit;
    WVEdit17: TWVEdit;
    WVDigitalEdit18: TWVEdit;
    WVDigitalEdit19: TWVEdit;
    WVDigitalEdit20: TWVEdit;
    WVDigitalEdit21: TWVEdit;
    WVDigitalEdit22: TWVEdit;
    WVDigitalEdit23: TWVEdit;
    WVDigitalEdit24: TWVEdit;
    WVEdit25: TWVEdit;
    WVDigitalEdit26: TWVEdit;
    WVEdit27: TWVEdit;
    WVDigitalEdit28: TWVEdit;
    WVDigitalEdit29: TWVEdit;
    Panel1: TPanel;
    WVComboBox1: TWVComboBox;
    Label2: TLabel;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    Label3: TLabel;
    edtIp: TWVEdit;
    Label4: TLabel;
    WVEdit3: TWVEdit;
    Label5: TLabel;
    WVEdit4: TWVEdit;
    Label6: TLabel;
    WVEdit5: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetCommCfParam: TfaqhsetCommCfParam;

implementation

uses KsFrameworks,SmartCardCommon,DataTypes;
     
{$R *.DFM}

procedure TfaqhsetCommCfParam.Init;
begin
  inherited;
  {
  //WorkView.FieldByName('标志').DefaultValue := '';
  WorkView.FieldByName('前置编号').DefaultValue := 0;
  WorkView.FieldByName('前置机名').DefaultValue := '';
  WorkView.FieldByName('心跳时间间隔').DefaultValue := 0;
  WorkView.FieldByName('心跳接阀值').DefaultValue := 0;
  WorkView.FieldByName('心跳应答功能号').DefaultValue := 0;
  WorkView.FieldByName('指令调度队列号').DefaultValue := 0;
  WorkView.FieldByName('指令应答功能号').DefaultValue := 0;
  WorkView.FieldByName('指令执行超时时间').DefaultValue := 0;
  WorkView.FieldByName('指令获取时间间隔').DefaultValue := 0;
  WorkView.FieldByName('设备种类标志').DefaultValue := '';
  WorkView.FieldByName('设备档案请求功能号').DefaultValue := 0;
  WorkView.FieldByName('设备联机模式').DefaultValue := '';
  WorkView.FieldByName('流水采集频率').DefaultValue := 0;
  WorkView.FieldByName('指令队列上限').DefaultValue := 0;
  WorkView.FieldByName('工作密钥').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhsetCommCfParam.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetCommCfParam.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetCommCfParam.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhsetCommCfParam.btnAddClick(Sender: TObject);
begin
  inherited;
  WVComboBox1.Enabled:=True;
  WorkView.FieldByName('标志').Data.SetString('I');
end;

procedure TfaqhsetCommCfParam.btnChangeClick(Sender: TObject);
begin
  inherited;
  WVComboBox1.Enabled:=false;
  WorkView.FieldByName('标志').Data.SetString('U');
end;

procedure TfaqhsetCommCfParam.btnOKClick(Sender: TObject);
var
  tmpMsg:string;
  i:Integer;
begin
  if (Trim(edtIP.Text)<>'') then
  begin
    tmpMsg := CheckIpAddress(edtIP.Text);
    if tmpMsg<>'' then
    begin
      Context.GetDialogSystem.ShowMessage(tmpMsg);
      edtIP.SetFocus;
      Exit;
    end;
  end;
  for i := 0 to tsEdit.ControlCount-1 do
  begin
    if tsEdit.Controls[i] is TWVEdit then
      if ((TWVEdit(tsEdit.Controls[i]).Text)='') and (TWVEdit(tsEdit.Controls[i]).Tag=9) then
        TWVEdit(tsEdit.Controls[i]).Text := '0';
  end;
  inherited;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('通用前置参数设置',TfaqhsetCommCfParam);

end.