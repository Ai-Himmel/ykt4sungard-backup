unit UASetSpeInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, WVCmdProc, KCWVProcBinds, 
  RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs, Buttons;

type
  TfaqhSetSpeInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit4: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit5: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetSpeInfo: TfaqhSetSpeInfo;

implementation

uses KsFrameworks, 
     UCMqhSpeInfoImp,KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSetSpeInfo.Init;
begin
  inherited;
end;

procedure TfaqhSetSpeInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetSpeInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhSetSpeInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('A');
  WVEdit2.ReadOnly:=False;
  //WVEdit2.Text:='';
  //WVEdit3.Text:='';
  //if ckAutoSetNewParams.Checked then
    //WorkView.SynchronizeCtrlsToFields;
end;

procedure TfaqhSetSpeInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('U');
  WVEdit2.ReadOnly:=True;
end;

procedure TfaqhSetSpeInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('D');
  WVEdit2.ReadOnly:=True;
end;

procedure TfaqhSetSpeInfo.btnOKClick(Sender: TObject);
begin
  if trim(WVEdit2.text)='' then
  begin
    Context.GetDialogSystem.ShowWarning('请输入专业代码！');
    Exit;
  end;
  if trim(WVEdit3.text)='' then
  begin
    Context.GetDialogSystem.ShowWarning('请输入专业名称！');
    Exit;
  end;
  inherited;
  FreeIdObjects(-23);
  btnQuery.Click;
end;

procedure TfaqhSetSpeInfo.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作类别').Data.SetString('R');
  inherited;

end;

initialization
  TUIStdClassFactory.Create('专业信息设置',TfaqhSetSpeInfo);

end.