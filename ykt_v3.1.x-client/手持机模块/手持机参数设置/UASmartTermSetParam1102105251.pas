unit UASmartTermSetParam;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo;

type
  TfaqhSmartTermSetParam = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit10: TWVEdit;
    WVEdit11: TWVEdit;
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSmartTermSetParam: TfaqhSmartTermSetParam;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhSmartTermSetParam.Init;
begin
  inherited;
  WorkView.FieldByName('�豸����').DefaultValue := '';
  WorkView.FieldByName('�����豸ע���').DefaultValue := '';
  WorkView.FieldByName('�豸���').DefaultValue := ;
  WorkView.FieldByName('����').DefaultValue := 0;
  WorkView.FieldByName('���ʹ���').DefaultValue := '';
  WorkView.FieldByName('�ϼ��豸���').DefaultValue := ;
  WorkView.FieldByName('�豸״̬').DefaultValue := 0;
  WorkView.FieldByName('�豸�����ͺ�').DefaultValue := 0;
  WorkView.FieldByName('������ϵͳ').DefaultValue := 0;
  WorkView.FieldByName('�豸��������').DefaultValue := 0;
  WorkView.FieldByName('������Ա����').DefaultValue := '';
  WorkView.Reset;
end;

procedure TfaqhSmartTermSetParam.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
end;
procedure TfaqhSmartTermSetParam.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



initialization
  TUIStdClassFactory.Create('�ֳֻ���ˮ�ɼ�',TfaqhSmartTermSetParam);

end.