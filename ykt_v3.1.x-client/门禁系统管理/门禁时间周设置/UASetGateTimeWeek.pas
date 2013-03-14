unit UASetGateTimeWeek;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, ComCtrls,
  RzListVw, RzPanel, RzSplit, RzButton, RzRadChk, Buttons;

type
  TfaqhSetGateTimeWeek = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    RzSizePanel1: TRzSizePanel;
    RzPanel1: TRzPanel;
    rzpnl1: TRzPanel;
    lvGate: TRzListView;
    Label7: TLabel;
    WVEdit3: TWVEdit;
    Label12: TLabel;
    WVComboBox7: TWVComboBox;
    WVComboBox5: TWVComboBox;
    Label11: TLabel;
    Label18: TLabel;
    WVEdit6: TWVEdit;
    WVComboBox8: TWVComboBox;
    Label15: TLabel;
    Label16: TLabel;
    Label14: TLabel;
    WVComboBox9: TWVComboBox;
    cbbScode: TWVComboBox;
    rzpnl2: TRzPanel;
    Label19: TLabel;
    WVEdit8: TWVEdit;
    btnWeekQuery: TBitBtn;
    lvWeek: TRzListView;
    btnDevquery: TBitBtn;
    WVRequest5: TWVRequest;
    WorkView5: TWorkView;
    chkGateUnAllot: TRzCheckBox;
    chkDevSelectAll: TRzCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnWeekQueryClick(Sender: TObject);
    procedure btnDevqueryClick(Sender: TObject);
    procedure chkGateUnAllotClick(Sender: TObject);
    procedure chkDevSelectAllClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    function findIndexLV(inLv:TRzListView;iId:string): Boolean;
    function listViewSelectAll(inListView:TRzListView;chkBox:TRzCheckBox):Boolean;
    function selectItem(inListView:TRzListView):Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetGateTimeWeek: TfaqhSetGateTimeWeek;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhSetGateTimeWeek.Init;
begin
  inherited;
  {
  WorkView1.FieldByName('�豸����').DefaultValue := '';
  WorkView1.FieldByName('�����豸ע���').DefaultValue := '';
  WorkView1.FieldByName('�豸����ID').DefaultValue := '';
  WorkView1.FieldByName('����').DefaultValue := 0;
  WorkView1.FieldByName('���ʹ���').DefaultValue := '';
  WorkView1.FieldByName('�ϼ��豸����ID').DefaultValue :='' ;
  WorkView1.FieldByName('�豸״̬').DefaultValue := 0;
  WorkView1.FieldByName('�豸�����ͺ�').DefaultValue := 0;
  WorkView1.FieldByName('������ϵͳ').DefaultValue := 0;
  WorkView1.FieldByName('�豸��������').DefaultValue := 0;
  WorkView1.FieldByName('������Ա����').DefaultValue := '';
  WorkView1.Reset;
  WorkView5.FieldByName('��ѯ.ʱ�������').DefaultValue := 0;
  WorkView5.FieldByName('��ѯ.��һ����').DefaultValue := 0;
  WorkView5.FieldByName('��ѯ.�ܶ�����').DefaultValue := 0;
  WorkView5.FieldByName('��ѯ.��������').DefaultValue := 0;
  WorkView5.FieldByName('��ѯ.��������').DefaultValue := 0;
  WorkView5.FieldByName('��ѯ.��������').DefaultValue := 0;
  WorkView5.FieldByName('��ѯ.��������').DefaultValue := 0;
  WorkView5.FieldByName('��ѯ.��������').DefaultValue := 0;
  WorkView5.FieldByName('ʱ�������').DefaultValue := 0;
  WorkView5.FieldByName('��һ����').DefaultValue := 0;
  WorkView5.FieldByName('�ܶ�����').DefaultValue := 0;
  WorkView5.FieldByName('��������').DefaultValue := 0;
  WorkView5.FieldByName('��������').DefaultValue := 0;
  WorkView5.FieldByName('��������').DefaultValue := 0;
  WorkView5.FieldByName('��������').DefaultValue := 0;
  WorkView5.FieldByName('��������').DefaultValue := 0;
  WorkView5.Reset;
  }
  btnDevquery.Caption := '�豸��ѯ';
  btnWeekQuery.Caption := '�ܲ�ѯ';
  btnQuery.Caption := '�� ��';
end;

procedure TfaqhSetGateTimeWeek.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhSetGateTimeWeek.btnWeekQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  lvWeek.Items.Clear;
  WorkView5.FieldByName('��������').Data.SetString('R');
  WVRequest5.SendCommand;
  if WorkView5.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView5.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView5.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvWeek.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //�豸����
    tmpdataset.Next;
  end;
end;

procedure TfaqhSetGateTimeWeek.btnDevqueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
  //sCode:string;
begin
  lvGate.Items.Clear;
  //sCode := Copy(cbbScode.Text,1,Pos('-',cbbScode.Text)-1);
  //WorkView2.FieldByName('���ʹ���').Data.SetString(sCode);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if findIndexLV(lvGate,tmpdataset.fieldbyname('lvol0').asstring)=True then
    begin
      tmpDataSet.Next;
      Continue;
    end;
    tmpItem := lvGate.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString);                            //�豸����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt6').AsString);                          //�豸���
    tmpItem.SubItems.Add(GetIdObjectName(-31,tmpdataset.fieldbyname('damt6').AsString));                          //�豸���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sbank_code').AsString);                          //�豸���
    tmpItem.SubItems.Add(GetIdObjectName(47,tmpdataset.fieldbyname('lserial1').AsString));       //��������
    tmpdataset.Next;
  end;
end;

function TfaqhSetGateTimeWeek.findIndexLV(inLv: TRzListView;iId: string): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to inLv.Items.Count-1 do
  begin
    if inLv.Items[i].Caption = iId then
    begin
      Result := True;
      Exit;
    end;
  end;
end;

procedure TfaqhSetGateTimeWeek.chkGateUnAllotClick(Sender: TObject);
begin
  //inherited;
  if listViewSelectAll(lvWeek,chkGateUnAllot)=False then
    Exit;

end;

function TfaqhSetGateTimeWeek.listViewSelectAll(inListView: TRzListView;
  chkBox: TRzCheckBox): Boolean;
var
  i: integer;
begin
  //Result := False;
  if inListView.Items.Count = 0 then
  begin
    Result := False;
    Exit;
  end;
  if chkBox.Checked = True then
  begin
    for i := 0 to inListView.Items.Count - 1 do
    begin
      inListView.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to inListView.Items.Count - 1 do
    begin
      inListView.Items[i].Checked := False;
    end;
  end;
  Result := True;

end;

procedure TfaqhSetGateTimeWeek.chkDevSelectAllClick(Sender: TObject);
begin
  if listViewSelectAll(lvGate,chkDevSelectAll)=False then
    Exit;
end;

procedure TfaqhSetGateTimeWeek.btnQueryClick(Sender: TObject);
var
  i,k:Integer;
  errList:TStringList;
  weekId,devId:string;
begin
  //�ж��Ƿ���ѡ����豸��ʱ����
  if selectItem(lvWeek)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ���õ�ʱ���ܣ�');
    Exit;
  end;
  if selectItem(lvGate)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ���õ��Ž��豸��');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ������ѡ����Ž�ʱ������',PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  errList := nil;
  WorkView.FieldByName('������־').Data.SetString('A');
  try
    errList := TStringList.Create;
    for i := 0 to lvWeek.Items.Count-1 do
    begin
      if lvWeek.Items[i].Checked then
      begin
        weekId := lvWeek.Items[i].Caption;
        WorkView.FieldByName('ʱ���ܱ��').Data.SetInteger(StrToInt(weekId));
        for k := 0 to lvGate.Items.Count-1 do
        begin
          if lvGate.Items[k].Checked then
          begin
            devId := lvGate.Items[k].Caption;
            WorkView.FieldByName('���������').Data.SetInteger(StrToInt(lvGate.Items[k].SubItems[1]));
            WorkView.FieldByName('�豸���').Data.SetInteger(StrToInt(devId));
            WorkView.FieldByName('���ʹ���').Data.SetString((lvGate.Items[k].SubItems[3]));
            try
              MainRequest.SendCommand;
            except
              on e:Exception do
              begin
                errList.Add('�豸���-'+devid+',ʱ���ܱ��-'+weekid+'����ʧ�ܣ�ԭ��-'+e.Message);
              end;
            end;
          end;
        end;
      end;
    end;
    if errList.Count>0 then
    begin
      errList.SaveToFile('c:\�Ž�ʱ��������ʧ���б�.txt');
      Context.GetDialogSystem.ShowMessage('�Ž�ʱ�����������,����ʧ����Ϣ������[c:\�Ž�ʱ��������ʧ���б�.txt]');
    end;
    Context.GetDialogSystem.ShowMessage('�Ž�ʱ����������ɣ�');
  finally
    errList.Free;
  end;
end;

function TfaqhSetGateTimeWeek.selectItem(inListView: TRzListView): Boolean;
var
  i:Integer;
begin
  for i:= 0 to inListView.Items.Count-1 do
  begin
    if inListView.Items[i].Checked then
    begin
      Result := True;
      Exit;
    end;
  end;
  Result := False;
end;

initialization
  TUIStdClassFactory.Create('�Ž�ʱ��������',TfaqhSetGateTimeWeek);

end.