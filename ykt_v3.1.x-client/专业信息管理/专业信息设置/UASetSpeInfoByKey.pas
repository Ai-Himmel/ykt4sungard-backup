unit UASetSpeInfoByKey;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo;

type
  TfaqhSetSpeInfoByKey = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
	WVComboBox1: TWVComboBox;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetSpeInfoByKey: TfaqhSetSpeInfoByKey;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSetSpeInfoByKey.Init;
begin
  inherited;
  WorkView.FieldByName('查询.专业代码').DefaultValue := GetFirstItemID(10);
  WorkView.FieldByName('专业代码').DefaultValue := '';
  WorkView.FieldByName('专业名称').DefaultValue := '';
  WorkView.FieldByName('备注').DefaultValue := ;
  WorkView.Reset;
end;

procedure TfaqhSetSpeInfoByKey.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
end;
procedure TfaqhSetSpeInfoByKey.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetSpeInfoByKey.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



initialization
  TUIStdClassFactory.Create('专业信息设置',TfaqhSetSpeInfoByKey);

end.