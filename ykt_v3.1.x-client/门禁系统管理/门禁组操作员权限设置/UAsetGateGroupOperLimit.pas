unit UAsetGateGroupOperLimit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  ComCtrls, RzListVw, RzPanel, RzSplit, RzLstBox, RzChkLst, Mask, Buttons;

type
  TfaqhsetGateGroupOperLimit = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    WVComboBox1: TWVComboBox;
    Panel2: TPanel;
    lvGate: TRzListView;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    rzszpnl1: TRzSizePanel;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    lst1: TRzCheckList;
    chkSelectAll: TRzCheckBox;
    edtName: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure lvGateCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
  private

    { Private declarations }
    OperatorNoName:string;
    procedure addGateToLV;
    procedure noSelect;
    procedure fillCheckListBox;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetGateGroupOperLimit: TfaqhsetGateGroupOperLimit;

implementation

uses KsFrameworks,USetParamsTemp, 
     KSClientConsts, gateComm;
     
{$R *.DFM}

procedure TfaqhsetGateGroupOperLimit.Init;
begin
  inherited;
  {
  WorkView.FieldByName('��ѯ.�Ž�������').DefaultValue := '';
  WorkView.FieldByName('��ѯ.����Ա��').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�Ž�����').DefaultValue := 0;
  WorkView.FieldByName('����Ա��').DefaultValue := '';
  WorkView.Reset;
  }
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  fillCheckListBox;
  addGateToLV;
end;

procedure TfaqhsetGateGroupOperLimit.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetGateGroupOperLimit.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetGateGroupOperLimit.btnOKClick(Sender: TObject);
var
  i ,k: Integer;
  groupId:string;
  equNO:string;
begin
  if checkListSelcet(lst1)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ����Ĳ���Ա��');
    Exit;
  end;
  if checkListViewSelect(lvGate)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ������Ž��飡');
    exit;
  end;
  for k := 0 to lst1.Items.Count-1 do
  begin
    if lst1.Itemchecked[k] then
    begin
      groupId := Copy(lst1.Items.Strings[k],1,Pos('-',lst1.Items.Strings[k])-1);
      for i := 0 to lvGate.Items.Count - 1 do
      begin
        if lvGate.Items[i].Checked = True then
        begin
          equNO:=lvGate.Items[i].Caption;
          WorkView.SynchronizeCtrlsToFields;
          WorkView.FieldByName('����Ա��').Data.SetString(groupId);
          WorkView.FieldByName('�Ž�����').Data.SetInteger(StrToInt(equNO));
          WorkView.FieldByName('��������').Data.SetString('A');
          AddRequest.SendCommand;
        end;
      end;
    end;
  end;
  Status := ssBrowse;
  noSelect;
  btnQuery.Click;
end;

procedure TfaqhsetGateGroupOperLimit.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('�Ž�����').Data.SetInteger(0);
  addType(operatorNoName,WorkView);

end;

procedure TfaqhsetGateGroupOperLimit.btnQueryClick(Sender: TObject);
begin
  queryType(operatorNoName,WorkView);
  inherited;

end;

procedure TfaqhsetGateGroupOperLimit.btnDeleteClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ��������¼��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView.FieldByName('����Ա��').Data.SetString(Grid.DataSource.DataSet.fieldbyname('scust_limit').AsString);
  WorkView.FieldByName('�Ž�����').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WorkView.FieldByName('��������').Data.SetString('D');
  DeleteRequest.SendCommand;
  btnQuery.Click;
end;

procedure TfaqhsetGateGroupOperLimit.addGateToLV;
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  WorkView1.FieldByName('�Ž�����').Data.SetInteger(0);
  WorkView1.FieldByName('��������').Data.SetString('R');
  WVRequest1.SendCommand;
  tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  if tmpDataSet.IsEmpty then
    Exit;
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvGate.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //�豸����
    tmpdataset.Next;
  end;
end;

procedure TfaqhsetGateGroupOperLimit.noSelect;
var
  i:Integer;
begin
  for i := 0 to lvGate.Items.Count - 1 do
  begin
    lvGate.Items[i].Checked := False;
  end;
  chkSelectAll.Checked:=false;
end;

procedure TfaqhsetGateGroupOperLimit.chkSelectAllClick(Sender: TObject);
begin
  if listViewSelectAll(lvGate,chkSelectAll)=False then
     Context.GetDialogSystem.ShowMessage('���Ȳ�ѯҪ������Ž��飡');
end;

procedure TfaqhsetGateGroupOperLimit.GridDblClick(Sender: TObject);
begin
  //inherited;

end;

procedure TfaqhsetGateGroupOperLimit.lvGateCustomDrawItem(
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

procedure TfaqhsetGateGroupOperLimit.fillCheckListBox;
var
  tmpDataSet : TDataSet;
  operCode,operName:string;
begin
  WorkView2.FieldByName('�������').Data.SetString('R');
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger=0 then
  begin
    tmpDataSet := TDataSet(WorkView2.FieldByName('��ѯ�����').Data.AsObject);
    lst1.Items.Clear;
    tmpDataSet.First;
    while not tmpDataSet.Eof do
    begin
      operCode := tmpDataSet.fieldbyname('scust_no').AsString;
      operName := tmpDataSet.fieldbyname('sname').AsString;
      lst1.Items.Add(operCode+'-'+opername);
      tmpDataSet.Next;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('�Ž������ԱȨ������',TfaqhsetGateGroupOperLimit);

end.