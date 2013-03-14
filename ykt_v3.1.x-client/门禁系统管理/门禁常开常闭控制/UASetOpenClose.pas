unit UASetOpenClose;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, Buttons,
  ComCtrls, RzListVw, RzButton, RzRadChk;

type
  TfaqhSetOpenClose = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    cbbSet: TComboBox;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    Label7: TLabel;
    WVEdit3: TWVEdit;
    WVComboBox7: TWVComboBox;
    Label12: TLabel;
    Label11: TLabel;
    WVComboBox5: TWVComboBox;
    Label15: TLabel;
    Label18: TLabel;
    WVEdit6: TWVEdit;
    WVComboBox8: TWVComboBox;
    Label14: TLabel;
    Label16: TLabel;
    cbbScode: TWVComboBox;
    WVComboBox9: TWVComboBox;
    btnEquQuery: TBitBtn;
    lvGate: TRzListView;
    lvResult: TListView;
    Label1: TLabel;
    chkSelectAll: TRzCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnEquQueryClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
  private

    { Private declarations }
    function findIndexLV(inLv:TRzListView;iId:string): Boolean;
    procedure AddListViewItem(FEquipID: string; FSuccess: string);
    function  ifSelectGate():Boolean ;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetOpenClose: TfaqhSetOpenClose;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhSetOpenClose.Init;
begin
  inherited;
end;

procedure TfaqhSetOpenClose.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSetOpenClose.btnEquQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
  sCode:string;
begin
  //lvGate.Items.Clear;
  sCode := Copy(cbbScode.Text,1,Pos('-',cbbScode.Text)-1);
  WorkView2.FieldByName('���ʹ���').Data.SetString(sCode);
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView2.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView2.FieldByName('��ѯ�����').Data.AsObject);
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
    //tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);                          //�豸���
    //tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdataset.fieldbyname('lserial0').AsString));       //������ϵͳ
    //tmpItem.SubItems.Add(GetIdObjectName(-28,tmpdataset.fieldbyname('lserial1').AsString));       //��������
    tmpdataset.Next;
  end;
end;

function TfaqhSetOpenClose.findIndexLV(inLv: TRzListView;iId: string): Boolean;
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

procedure TfaqhSetOpenClose.btnQueryClick(Sender: TObject);
var
  I:Integer;
  Id, EquID,EquName: string;
  gateSign:string;
begin
  gateSign := Copy(cbbSet.Text,1,Pos('-',cbbSet.Text)-1);
  if (gateSign='') or (gateSign='-') then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ���Ž�״̬��Ȼ�����´�������');
    exit;
  end;

  if (ifSelectGate=False) then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ�Ž��豸��');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ����ѡ����Ž�Ϊ��ǰ״̬��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for I := 0 to lvGate.Items.Count-1 do
  begin
    if lvGate.Items[i].Checked then
    begin
      Id := lvGate.Items[i].caption;
      //EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvGate.Items[i].SubItems[0];
      //WorkView.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WorkView.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      WorkView.FieldByName('��־').Data.SetInteger(StrToInt(gateSign));
      try
        MainRequest.SendCommand;
        if WorkView.FieldByName('������').Data.AsInteger <> 0 then
          AddListViewItem(EquName, WorkView.FieldByName('������Ϣ').Data.AsString)
        else
          AddListViewItem(EquName, WorkView.FieldByName('������Ϣ').Data.AsString);
      except
        on e:Exception do
          AddListViewItem(EquName, e.Message);
      end;
    end;
  end;
end;

procedure TfaqhSetOpenClose.AddListViewItem(FEquipID, FSuccess: string);
var TmpItem: TListItem;
begin
  TmpItem := lvResult.Items.Add;
  TmpItem.Caption := '�Ž���������';
  //TmpItem.SubItems.Add(cbbName.Text);
  TmpItem.SubItems.Add(FormatDateTime('yyyy-mm-dd hh:MM:ss',Now));
  TmpItem.SubItems.Add(FEquipID);
  TmpItem.SubItems.Add(FSuccess);

end;

function TfaqhSetOpenClose.ifSelectGate: Boolean;
var
  i:Integer;
begin
  Result := False;
  for i:= 0 to lvGate.Items.Count-1 do
  begin
    if (lvGate.Items[i].Checked) then
    begin
      Result := True;
      Exit;
    end;
  end;
end;

procedure TfaqhSetOpenClose.chkSelectAllClick(Sender: TObject);
var
  i:Integer;
begin
  if chkSelectAll.Checked = True then
  begin
    for i := 0 to lvgate.Items.Count - 1 do
    begin
      lvgate.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvgate.Items.Count - 1 do
    begin
      lvgate.Items[i].Checked := False;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('�Ž�������������',TfaqhSetOpenClose);

end.