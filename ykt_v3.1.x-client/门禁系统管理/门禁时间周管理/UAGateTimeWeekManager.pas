unit UAGateTimeWeekManager;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhGateTimeWeekManager = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label7: TLabel;
    Label10: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit10: TWVEdit;
    Label12: TLabel;
    WVComboBox7: TWVComboBox;
    cbbScode: TWVComboBox;
    btnDelete: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhGateTimeWeekManager: TfaqhGateTimeWeekManager;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhGateTimeWeekManager.Init;
begin
  inherited;
  WorkView.FieldByName('�������').DefaultValue := '';
  WorkView.FieldByName('���������').DefaultValue := 0;
  WorkView.FieldByName('��ϵͳ').DefaultValue := 0;
  WorkView.FieldByName('����������').DefaultValue := '';
  WorkView.FieldByName('�豸������').DefaultValue := '';
  WorkView.FieldByName('�豸����').DefaultValue := '';
  WorkView.FieldByName('�豸�����ͺ�').DefaultValue := '';
  WorkView.FieldByName('�豸����').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('ʱ���ܱ��').DefaultValue := 0;
  WorkView.FieldByName('ʱ��������').DefaultValue := '';
  WorkView.Reset;
  btnDelete.Caption := '&D ɾ��';
end;

procedure TfaqhGateTimeWeekManager.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('�������').Data.SetString('R');
  inherited;

end;

procedure TfaqhGateTimeWeekManager.btnDeleteClick(Sender: TObject);
var
  colId,devId,weekId:Integer;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ����Ȳ�ѯ��Ȼ���ٽ��в�����');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫɾ����ѡ����Ž�ʱ������',PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  try
    colId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
    //ȡ�ͻ���
    devId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol2').AsInteger;
    weekId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol3').AsInteger;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  WorkView1.FieldByName('�������').Data.SetString('D');
  WorkView1.FieldByName('���������').Data.SetInteger(colId);
  WorkView1.FieldByName('�豸���').Data.SetInteger(devId);
  WorkView1.FieldByName('ʱ���ܱ��').Data.SetInteger(weekId);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger=0 then
  begin
    Context.GetDialogSystem.ShowMessage('ɾ���Ž�ʱ���ܳɹ���');
  end;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('�Ž�ʱ���ܹ���',TfaqhGateTimeWeekManager);

end.