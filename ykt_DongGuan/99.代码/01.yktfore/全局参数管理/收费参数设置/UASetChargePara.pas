unit UASetChargePara;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  Buttons;

type
  TfaqhSetChargePara = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    cbbdep: TWVComboBox;
    cbbcusttype: TWVComboBox;
    Label1: TLabel;
    cbbfeetype: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnViewDetailClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
    function judgeNull(inStr:string): Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetChargePara: TfaqhSetChargePara;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhSetChargePara.Init;
begin
  inherited;
  cbbdep.ItemIndex:=0;
  cbbcusttype.ItemIndex:=0;
  cbbfeetype.ItemIndex:=0;
end;

procedure TfaqhSetChargePara.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetChargePara.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhSetChargePara.btnViewDetailClick(Sender: TObject);
begin
  inherited;
  WorkView.SynchronizeCtrlsToFields;

end;

procedure TfaqhSetChargePara.btnChangeClick(Sender: TObject);
begin
  inherited;
  cbbdep.Enabled:=False;
  cbbcusttype.Enabled:=false;
end;

procedure TfaqhSetChargePara.btnOKClick(Sender: TObject);
begin
  if (judgeNull(cbbdep.Text)=False) or (judgeNull(cbbcusttype.Text)=False) or (judgeNull(cbbfeetype.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('所有选项的值都不能为空，请选择有效的值！');
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhSetChargePara.judgeNull判断输入的值是否为空
  作者:      Administrator
  日期:      2005.07.27
  参数:      inStr: string
  返回值:    Boolean
-------------------------------------------------------------------------------}
function TfaqhSetChargePara.judgeNull(inStr: string): Boolean;
begin
  if Trim(inStr)='' then
    Result:=False;
end;

initialization
  TUIStdClassFactory.Create('收费参数设置',TfaqhSetChargePara);

end.