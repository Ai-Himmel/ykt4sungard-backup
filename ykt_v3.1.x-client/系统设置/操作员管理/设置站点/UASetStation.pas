unit UASetStation;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  USetParamsTemp, UIncrementComboBox, RzDBNav, RzButton, RzRadChk,
  RzDBGrid, RzTabs, Buttons;

type
  TfaqhSetStation = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Labelsite_no1: TLabel;
    WVComboBox6: TWVComboBox;
    Labelsite_no2: TLabel;
    edtSiteNo: TWVEdit;
    WVEditmachine_name5: TWVEdit;
    Labelmachine_name5: TLabel;
    Labelip_addr3: TLabel;
    WVEditip_addr3: TWVEdit;
    Label2: TLabel;
    Label1: TLabel;
    WVEditmac_addr4: TWVEdit;
    Labelmac_addr4: TLabel;
    Labelnotes6: TLabel;
    WVEditnotes6: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetStation: TfaqhSetStation;

implementation

uses KsFrameworks, 
     KSDataDictionary,SmartCardCommon;

{$R *.DFM}

procedure TfaqhSetStation.Init;
begin
  inherited;
end;

procedure TfaqhSetStation.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetStation.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetStation.btnOKClick(Sender: TObject);
var TmpMsg:String;
begin
  if  (workview.FieldByName('ip地址').Data.AsString = '')  then
  begin
     ShowMessage('必须设置ip地址！');
     WVEditip_addr3.SetFocus;
     WVEditip_addr3.SelectAll;
     exit;
  end;
  if Trim(WVEditmachine_name5.Text)='' then
  begin
    ShowMessage('站点名称必须输入！');
    WVEditmachine_name5.SetFocus;
    Exit;
  end;
  if (workview.FieldByName('ip地址').Data.AsString <>'') then
  begin
    try
       TmpMsg:=CheckIpAddress(Trim(workview.FieldByName('ip地址').Data.AsString));
       if Trim(TmpMsg)<>'' then
       begin
         Context.GetDialogSystem.showmessage(TmpMsg);
         WVEditip_addr3.SetFocus;
         WVEditip_addr3.SelectAll;
         exit;
       end;
     except
       Context.GetDialogSystem.showmessage(TmpMsg);
       WVEditip_addr3.SetFocus;
       WVEditip_addr3.SelectAll;
       exit;
     end;
  end;
  inherited;
  btnQuery.Click;
  FreeIdObjects(-33);
  WVComboBox6.ItemsDataEntry := '';
  WVComboBox6.ItemsDataEntry := '*-33';
end;

procedure TfaqhSetStation.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('U');
  edtSiteNo.Enabled := false;
  WVEditip_addr3.SetFocus;
  WVEditip_addr3.SelectAll;
end;

procedure TfaqhSetStation.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('A');
  edtSiteNo.Enabled := False;
end;

procedure TfaqhSetStation.btnQueryClick(Sender: TObject);
begin
  //WorkView.FieldByName('查询.站点号').Data.SetInteger(0);
  WorkView.FieldByName('操作类别').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetStation.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作类别').Data.SetString('D');

end;

initialization
  TUIStdClassFactory.Create('登录站点设置',TfaqhSetStation);

end.