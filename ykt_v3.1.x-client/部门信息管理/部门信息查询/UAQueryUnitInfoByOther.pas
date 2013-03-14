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
  WorkView.FieldByName('��λ����').DefaultValue := '';
  WorkView.FieldByName('�Ƿ�Ժϵ').DefaultValue := '';
  WorkView.FieldByName('��λ����').DefaultValue :='' ;
  WorkView.FieldByName('Ӣ������').DefaultValue := '';
  WorkView.FieldByName('�ϼ���λ').DefaultValue := '';
  //WorkView.FieldByName('��λ����').DefaultValue := 0;
  WorkView.FieldByName('�Ƿ���Ч').DefaultValue := '';
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
  TUIStdClassFactory.Create('������Ϣ��ѯ',TfaqhQueryUnitInfoByOther);

end.