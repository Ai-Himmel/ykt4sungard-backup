unit UAQueryEquipmentByOther;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, ComCtrls, RzDBGrid, Buttons, EditExts;

type
  TEquipParaTreeNode = class
  public
    CEquipID: Integer;       {设备标识} //是 设备商户表 与 设备表关联的唯一字段，
    CNodeID: String;        {设备物理ID}
    CNodeCaption: String;   {设备名称}
    CNodeKind: String;     {机型ID}
    CParentNodeID: String;  {父设备物理ID}
    CParentNodeCaption: String;  {父设备名称}
    CNodeKindCaption:String; {机型名称}
    CEquipRegNo : String ;  {三九设备注册号}
 //   CEquipNo: Integer ; {机号}
 //   CEquipState : Integer; {设备状态ID}
 //   CEquipShowId:Integer;{设备所属类型归类}
 //   CNodeImage : Integer;
end;

type
  TfaqhQueryEquipmentByOther = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    WVEdit1: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVComboBox6: TWVComboBox;
    edtMachineNo: TWVEdit;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    Label11: TLabel;
    WVEdit4: TWVEdit;
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
  faqhQueryEquipmentByOther: TfaqhQueryEquipmentByOther;
  flag:integer;

implementation

uses KsFrameworks;
     
{$R *.DFM}
procedure TfaqhQueryEquipmentByOther.Init;
begin
  inherited;
  WVComboBox1.ItemIndex:=0;
  WVComboBox2.ItemIndex:=0;
  WVComboBox3.ItemIndex:=0;
  WVComboBox5.ItemIndex:=0;
  WVComboBox6.ItemIndex:=0;
end;
procedure TfaqhQueryEquipmentByOther.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhQueryEquipmentByOther.btnQueryClick(Sender: TObject);
begin
  if Trim(edtMachineNo.Text)='' then
    edtMachineNo.Text := '0';
  inherited;

end;

initialization
  TUIStdClassFactory.Create('设备信息查询',TfaqhQueryEquipmentByOther);

end.