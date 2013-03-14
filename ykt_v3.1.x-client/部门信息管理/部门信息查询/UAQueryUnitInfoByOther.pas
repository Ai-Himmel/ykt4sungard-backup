unit UAQueryUnitInfoByOther;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons;

type
  TfaqhQueryUnitInfoByOther = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    WVComboBox3: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhQueryUnitInfoByOther: TfaqhQueryUnitInfoByOther;

implementation

uses KsFrameworks, 
     KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhQueryUnitInfoByOther.Init;
begin
  inherited;
  {
  WorkView.FieldByName('单位代码').DefaultValue := '';
  WorkView.FieldByName('是否院系').DefaultValue := '';
  WorkView.FieldByName('单位名称').DefaultValue :='' ;
  WorkView.FieldByName('英文名称').DefaultValue := '';
  WorkView.FieldByName('上级单位').DefaultValue := '';
  //WorkView.FieldByName('单位级别').DefaultValue := 0;
  WorkView.FieldByName('是否有效').DefaultValue := '';
  WorkView.Reset;

  FreeIdObjects(-22);
  WVComboBox3.ItemsDataEntry := '';
  WVComboBox3.ItemsDataEntry := '*-22';
  }
end;

procedure TfaqhQueryUnitInfoByOther.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



initialization
  TUIStdClassFactory.Create('部门信息查询',TfaqhQueryUnitInfoByOther);

end.