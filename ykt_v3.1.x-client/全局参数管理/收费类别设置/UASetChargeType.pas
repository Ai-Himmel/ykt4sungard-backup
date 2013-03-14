unit UASetChargeType;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  RzListVw, Buttons;

type
  TfaqhSetChargeType = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label5: TLabel;
    edtName: TWVEdit;
    chkif: TRzCheckBox;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    Label2: TLabel;
    Label4: TLabel;
    edtId: TWVDigitalEdit;
    cbbfeetype: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure chkifClick(Sender: TObject);
  private

    { Private declarations }
    ifFee:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetChargeType: TfaqhSetChargeType;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSetChargeType.Init;
begin
  inherited;
  {
  WorkView.FieldByName('类别标志').DefaultValue := 0;
  WorkView.Reset;
  }
end;

procedure TfaqhSetChargeType.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  //btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetChargeType.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetChargeType.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('类别标志').Data.SetInteger(0);
  WorkView.FieldByName('是否收搭伙费').Data.SetString('');
  WorkView.FieldByName('标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetChargeType.btnAddClick(Sender: TObject);
begin
  inherited;
  //WorkView.FieldByName('是否收搭伙费').Data.SetString(ifFee);
  edtId.ReadOnly := False;
  WorkView.FieldByName('标志').Data.SetString('A');
end;

procedure TfaqhSetChargeType.btnChangeClick(Sender: TObject);
var
  ss:string;
begin
  ss := Grid.DataSource.DataSet.fieldbyname('sall_name').AsString;
  if ss='1' then
    chkif.Checked := True
  else
    chkif.Checked := False;
  inherited;
  edtId.ReadOnly := True;
  WorkView.FieldByName('标志').Data.SetString('U');
end;

procedure TfaqhSetChargeType.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('标志').Data.SetString('D');
end;

procedure TfaqhSetChargeType.btnOKClick(Sender: TObject);
begin
  if Trim(edtName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('收费类别不能为空！');
    edtName.SetFocus;
    Exit;
  end;
  if (StrToInt(edtId.Text)<10) or (StrToInt(edtId.Text)>255) then
  begin
    Context.GetDialogSystem.ShowMessage('收费类别编号必须在10~255之间');
    Exit;
  end;
  if Trim(edtName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('收费类别名称不能为空！');
    edtName.SetFocus;
    Exit;
  end;
  WorkView.FieldByName('是否收搭伙费').Data.SetString(ifFee);
  inherited;
  FreeIDObjects(-43);  // update the data dict
  cbbfeetype.ItemsDataEntry := '';
  cbbfeetype.itemsdataentry := '*-43';
  btnQuery.Click;
end;

procedure TfaqhSetChargeType.chkifClick(Sender: TObject);
begin
  if chkif.Checked then
  begin
    ifFee := '1';
  end
  else
  begin
    ifFee := '2';
  end;
end;

initialization
  TUIStdClassFactory.Create('收费类别设置',TfaqhSetChargeType);

end.