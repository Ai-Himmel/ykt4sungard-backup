unit UAsetGateGroupForGate;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, RzPanel, RzSplit, 
  RzListVw, RzLstBox, UIncrementComboBox, Mask, RzChkLst, Buttons;

type
  TfaqhsetGateGroupForGate = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    pnl1: TPanel;
    Label8: TLabel;
    rzszpnl1: TRzSizePanel;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    cbbType: TWVComboBox;
    MainRequest2: TWVRequest;
    WorkView2: TWorkView;
    chkSelectAll: TRzCheckBox;
    pnl2: TPanel;
    pnl3: TPanel;
    lvGate: TRzListView;
    Label2: TLabel;
    WVEdit1: TWVEdit;
    Label3: TLabel;
    WVComboBox1: TWVComboBox;
    Label9: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    cbbScode: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVComboBox3: TWVComboBox;
    Label10: TLabel;
    WVComboBox2: TWVComboBox;
    WVEdit3: TWVEdit;
    Label11: TLabel;
    Label12: TLabel;
    WVEdit6: TWVEdit;
    btnEquQuery: TBitBtn;
    lst1: TRzCheckList;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnEquQueryClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure lvGateCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
  private

    { Private declarations }
    procedure addGateGroupToLst;
    procedure addGateToLV;
    procedure noSelect;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetGateGroupForGate: TfaqhsetGateGroupForGate;

implementation

uses KsFrameworks, 
     KSDataDictionary, gateComm,USetParamsTemp;
     
{$R *.DFM}

procedure TfaqhsetGateGroupForGate.Init;
begin
  inherited;
  {
  WorkView.FieldByName('��ѯ.�Ž�����').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�Ž������').DefaultValue := 0;
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�Ž�����').DefaultValue := 0;
  WorkView.FieldByName('�Ž������').DefaultValue := 0;
  WorkView.Reset;
  //WorkView2.FieldByName('�豸����').DefaultValue := '';
  //WorkView2.FieldByName('�����豸ע���').DefaultValue := '';
  //WorkView2.FieldByName('�豸����ID').DefaultValue := '';
  WorkView2.FieldByName('����').DefaultValue := 0;
  WorkView2.FieldByName('���ʹ���').DefaultValue := '';
  WorkView2.FieldByName('�ϼ��豸����ID').DefaultValue :='' ;
  WorkView2.FieldByName('�豸״̬').DefaultValue := 0;
  WorkView2.FieldByName('�豸�����ͺ�').DefaultValue := 0;
  WorkView2.FieldByName('������ϵͳ').DefaultValue := 0;
  WorkView2.FieldByName('�豸��������').DefaultValue := 0;
  WorkView2.FieldByName('������Ա����').DefaultValue := '';
  WorkView2.Reset;
  }
  //FreeIdObjects(-46);
  btnEquQuery.caption := '�豸��ѯ';
  addGateGroupToLst;
end;

procedure TfaqhsetGateGroupForGate.addGateGroupToLst;
var
  tmpDataSet:TDataSet;
begin
  WorkView1.FieldByName('��ѯ.�Ž�����').Data.SetInteger(0);
  WorkView1.FieldByName('��������').Data.SetString('R');
  WVRequest1.SendCommand;
  tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  if tmpDataSet.IsEmpty then
    Exit;
  lst1.Items.Clear;
  tmpDataSet.First;
  while not tmpDataSet.Eof do
  begin
    lst1.Items.Add(tmpDataSet.fieldbyname('lvol0').AsString+'-'+tmpDataSet.fieldbyname('semail').AsString);
    tmpDataSet.Next;
  end;
end;

procedure TfaqhsetGateGroupForGate.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhsetGateGroupForGate.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetGateGroupForGate.addGateToLV;
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
  sCode:string;
begin
  lvGate.Items.Clear;
  sCode := Copy(cbbScode.Text,1,Pos('-',cbbScode.Text)-1);
  WorkView2.FieldByName('���ʹ���').Data.SetString(sCode);
  MainRequest2.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView2.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView2.FieldByName('��ѯ�����').Data.AsObject);
  //if tmpDataSet=nil then
    //Exit;
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvGate.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString);                            //�豸����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);                          //�豸���
    tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdataset.fieldbyname('lserial0').AsString));       //������ϵͳ
    tmpItem.SubItems.Add(GetIdObjectName(-28,tmpdataset.fieldbyname('lserial1').AsString));       //��������
    tmpdataset.Next;
  end;
end;

procedure TfaqhsetGateGroupForGate.btnOKClick(Sender: TObject);
var
  i ,k: Integer;
  groupId:Integer;
  equNO:string;
begin
  if checkListViewSelect(lvGate)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ������Ž�����');
    exit;
  end;
  if checkListSelcet(lst1)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ������飡');
    Exit;
  end;
  for k := 0 to lst1.items.count-1 do
  begin
    //groupId := StrToInt(Copy(lst1.selecteditem,1,Pos('-',lst1.SelectedItem)-1));
    if lst1.Itemchecked[k] then
    begin
      groupId := StrToInt(Copy(lst1.Items.Strings[k],1,Pos('-',lst1.Items.Strings[k])-1));
      for i := 0 to lvGate.Items.Count - 1 do
      begin
        if lvGate.Items[i].Checked = True then
        begin
          equNO:=lvGate.Items[i].Caption;
          WorkView.SynchronizeCtrlsToFields;
          WorkView.FieldByName('�Ž�����').Data.SetInteger(groupId);
          WorkView.FieldByName('�Ž������').Data.SetInteger(StrToInt(equNO));
          WorkView.FieldByName('��������').Data.SetString('A');

          AddRequest.SendCommand;
        end;
      end;
    end;
  end;
  //inherited;
  Status := ssBrowse;
  noSelect;
  FreeIdObjects(-46);

  cbbType.ItemsDataEntry := '';
  cbbType.itemsdataentry := '*-46';
  btnQuery.Click;
end;

procedure TfaqhsetGateGroupForGate.noSelect;
var
  i:Integer;
begin
  for i := 0 to lvGate.Items.Count - 1 do
  begin
    lvGate.Items[i].Checked := False;
  end;
  chkSelectAll.Checked:=false;
  for i := 0 to lst1.Items.Count-1 do
    lst1.ItemChecked[i] := False;
end;

procedure TfaqhsetGateGroupForGate.chkSelectAllClick(Sender: TObject);
begin
  {
  if lvGate.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelectAll.Checked = True then
  begin
    for i := 0 to lvGate.Items.Count - 1 do
    begin
      lvGate.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvGate.Items.Count - 1 do
    begin
      lvGate.Items[i].Checked := False;
    end;
  end;
  }
  if listViewSelectAll(lvGate,chkSelectAll)=False then
    ShowMessage('���Ȳ�ѯ����¼����');
    //chkSelectAll.Checked:=False;
end;

procedure TfaqhsetGateGroupForGate.btnQueryClick(Sender: TObject);
begin
  queryType('',WorkView);
  inherited;

end;

procedure TfaqhsetGateGroupForGate.btnAddClick(Sender: TObject);
begin
  inherited;
  addType('',WorkView);
  lvGate.Items.Clear;
end;

procedure TfaqhsetGateGroupForGate.btnDeleteClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ��������¼��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView.FieldByName('�Ž�����').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WorkView.FieldByName('��������').Data.SetString('D');
  WorkView.FieldByName('�Ž������').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol1').AsInteger);
  DeleteRequest.SendCommand;
  btnQuery.Click;
end;

procedure TfaqhsetGateGroupForGate.btnEquQueryClick(Sender: TObject);
begin
  addGateToLV;
end;

procedure TfaqhsetGateGroupForGate.GridDblClick(Sender: TObject);
begin
  //inherited;
end;

procedure TfaqhsetGateGroupForGate.lvGateCustomDrawItem(
  Sender: TCustomListView; Item: TListItem; State: TCustomDrawState;
  var DefaultDraw: Boolean);
begin
  inherited;
  {
  DefaultDraw:=false;
  if Item.Index mod 2 <>0 then
    Sender.Canvas.Brush.Color := clInfoBk
  else
    Sender.Canvas.Brush.Color := $00EBDED0;
  Sender.Canvas.Font.Color := clBlack;
  DefaultDraw:=true;
  }
end;

initialization
  TUIStdClassFactory.Create('�Ž�����������',TfaqhsetGateGroupForGate);

end.