unit UAsetCardFee;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhsetCardFee = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label4: TLabel;
    Label11: TLabel;
    Label13: TLabel;
    WVComboBox4: TWVComboBox;
    WVComboBox5: TWVComboBox;
    cbbCardType: TWVComboBox;
    cbbFee: TWVComboBox;
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
    function checkValue(cbb:TWVComboBox): Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetCardFee: TfaqhsetCardFee;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetCardFee.Init;
begin
  inherited;

end;

procedure TfaqhsetCardFee.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetCardFee.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetCardFee.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhsetCardFee.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
end;

procedure TfaqhsetCardFee.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('U');
end;

procedure TfaqhsetCardFee.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');

end;

procedure TfaqhsetCardFee.btnOKClick(Sender: TObject);
begin
  if checkValue(cbbCardType)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择卡类别！');
    cbbCardType.SetFocus;
    Exit;
  end;
  if checkValue(cbbFee)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择收费类别！');
    cbbFee.SetFocus;
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

function TfaqhsetCardFee.checkValue(cbb: TWVComboBox): Integer;
var
  str:string;
begin
  str := Copy(cbb.Text,1,Pos('-',cbb.Text)-1);
  if (str='') or (str='-') then
    Result := -1
  else
    Result := 0;
end;

initialization
  TUIStdClassFactory.Create('发卡收费类别设置',TfaqhsetCardFee);

end.