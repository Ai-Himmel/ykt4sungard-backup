unit UAfillOperEquBanding;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  RzListVw, Buttons;

type
  TfaqhfillOperEquBanding = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
	WVEdit1: TWVEdit;
    grp1: TGroupBox;
    Label3: TLabel;
    cbbFillOper: TWVComboBox;
    WVComboBox1: TWVComboBox;
    lvEqu: TRzListView;
    MainRequest: TWVRequest;
    WorkView1: TWorkView;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
  private

    { Private declarations }
    procedure fillEquList;
    function getBusiStr: string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhfillOperEquBanding: TfaqhfillOperEquBanding;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhfillOperEquBanding.fillEquList;
var
  tmpDataSet : TDataSet;
  tmpItem: TListItem;
begin
  WorkView1.FieldByName('���ʹ���').Data.SetString('0201');
  MainRequest.SendCommand;
  try
    tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
    tmpDataSet.First;
    lvEqu.Items.Clear;
    while not tmpDataSet.Eof do
    begin
      tmpItem := lvEqu.Items.Add;
      tmpItem.Caption := tmpdataset.fieldbyname('lvol0').AsString;         //�豸���
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString);   //�豸����
      tmpItem.SubItems.Add(GetIdObjectName(5,tmpdataset.fieldbyname('lvol4').AsString));      //״̬
      tmpItem.SubItems.Add(GetIdObjectName(-28,tmpdataset.fieldbyname('lserial1').AsString)); //��������       //����У��
      tmpdataset.Next;
    end;
  except
  end;
end;

function TfaqhfillOperEquBanding.getBusiStr: string;
var
  i:Integer;
  ss:string;
begin
  for i := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
      ss := ss+lvequ.Items[i].Caption+',';
  end;
  Result := ss;
end;

procedure TfaqhfillOperEquBanding.Init;
begin
  inherited;
  WorkView.FieldByName('��ѯ.�豸���').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��ֵ����Ա��').DefaultValue := '';
  WorkView.FieldByName('��ֵ����Ա��').DefaultValue := '';
  WorkView.FieldByName('�豸���').DefaultValue := '';
  WorkView.Reset;
  WorkView1.FieldByName('����').DefaultValue := 0;
  WorkView1.FieldByName('�豸״̬').DefaultValue := 0;
  WorkView1.FieldByName('�豸�����ͺ�').DefaultValue := 0;
  WorkView1.FieldByName('������ϵͳ').DefaultValue := 0;
  WorkView1.FieldByName('�豸��������').DefaultValue := 0;
  WorkView1.Reset;
end;

procedure TfaqhfillOperEquBanding.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhfillOperEquBanding.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhfillOperEquBanding.btnOKClick(Sender: TObject);
begin
  WorkView.FieldByName('�豸���').Data.SetString(getBusiStr);
  inherited;
  btnQuery.Click;
end;

procedure TfaqhfillOperEquBanding.btnDeleteClick(Sender: TObject);
var
  equId:string;
  operId:string;
begin
  if Application.MessageBox('��ȷ��Ҫɾ���ó�ֵ����Ա�������豸��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  equId := Grid.DataSource.DataSet.fieldbyname('saddr').AsString;
  operId := Grid.DataSource.DataSet.fieldbyname('scust_auth').AsString;
  WorkView.FieldByName('��ֵ����Ա��').Data.SetString(operId);
  WorkView.FieldByName('�豸���').Data.SetString(equId);
  DeleteRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger=0 then
    ShowMessage('ɾ����ֵ����Ա�豸�ɹ���');
  btnQuery.Click;
end;

procedure TfaqhfillOperEquBanding.btnAddClick(Sender: TObject);
begin
  inherited;
  fillEquList;

end;

procedure TfaqhfillOperEquBanding.GridDblClick(Sender: TObject);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('��ֵ����Ա�豸��',TfaqhfillOperEquBanding);

end.