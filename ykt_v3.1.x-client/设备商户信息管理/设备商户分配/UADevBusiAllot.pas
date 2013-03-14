unit UADevBusiAllot;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, ComCtrls, RzDBGrid, Buttons, EditExts, RzPanel,
  RzSplit, RzListVw, RzTreeVw, AAFont, AACtrls, RzLabel;

type
  PBusiRec = ^TBusiRec;
  TBusiRec = record
    busiId: Integer;
    busiName: string;
end;

type
  TfaqhDevBusiAllot = class(TfaqhSimpleQueryTemp)
    RzSizePanel1: TRzSizePanel;
    Panel1: TPanel;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label2: TLabel;
    WVEdit1: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVComboBox6: TWVComboBox;
    edtMachineNo: TWVEdit;
    WVEdit2: TWVEdit;
    btnAdd: TBitBtn;
    btnDel: TBitBtn;
    btnChange: TBitBtn;
    WorkView1: TWorkView;
    AddRequest: TWVRequest;
    QueryRequest2: TWVRequest;
    WorkView2: TWorkView;
    lvDev: TRzListView;
    tvBusiness: TRzTreeView;
    rzszpnl1: TRzSizePanel;
    lvAllotDev: TRzListView;
    pnlAllot: TPanel;
    lblShowAllot: TRzURLLabel;
    WorkView3: TWorkView;
    WVRequest1: TWVRequest;
    grp1: TGroupBox;
    lblBusiName: TLabel;
    Label12: TLabel;
    edtStartDate: TWVEdit;
    Label11: TLabel;
    Label7: TLabel;
    edtEndTime: TWVEdit;
    edtStopDate: TWVEdit;
    Label13: TLabel;
    WVEdit4: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure tvBusinessClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDelClick(Sender: TObject);
    procedure lblShowAllotClick(Sender: TObject);
  private
    { Private declarations }
    gbusiId:Integer;
    gbusiName:string;
    procedure RefreshBusiTree;
    procedure AddDataToTree(tv:TRzTreeView;DataSet:TDataSet;parentId,currId,currName:string);
    function findParent(tv:TRzTreeView;parentId:Integer;imgIndex:integer):TTreeNode;

    function ifSelectBusi: Integer;

    function ifSelectDev(lv:TRzListView): Integer;

    function checkDateAndTime: Integer;

    procedure clearAllotDev(lv:TRzListView);

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhDevBusiAllot: TfaqhDevBusiAllot;
  flag:integer;

implementation

uses KsFrameworks,KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}
procedure TfaqhDevBusiAllot.Init;
begin
  inherited;
  RefreshBusiTree;
  lblBusiName.Caption := '��ѡ���̻�';
  WorkView1.FieldByName('ʹ�ý���ʱ��').Data.SetString('235959');
  WorkView1.FieldByName('��������').Data.SetString(FormatDateTime('yyyymmdd',Date));
  WorkView1.FieldByName('ͣ������').Data.SetString('99991231');
  WorkView1.Reset;
  //lblDevCount.Caption := '';
end;
procedure TfaqhDevBusiAllot.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhDevBusiAllot.btnQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdata:TDataSet;
begin
  if Trim(edtMachineNo.Text)='' then
    edtMachineNo.Text := '0';
  inherited;
  lvDev.Items.Clear;
  
  tmpdata := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  tmpdata.First;
  while not tmpdata.eof do
  begin
    tmpItem := lvDev.Items.Add;
    //��������
    tmpItem.Caption := GetIdObjectName(-28,tmpdata.fieldbyname('lserial1').AsString);
    //�豸��ʾ
    tmpItem.SubItems.Add(tmpdata.fieldbyname('lvol0').AsString);
    //�豸����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('scert_no').AsString);
    //������
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sphone3').AsString);
    //���ʹ���
    tmpItem.SubItems.Add(GetIdObjectName(47,tmpdata.fieldbyname('sbank_code').AsString));
    //������ϵͳ
    tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdata.fieldbyname('lserial0').AsString));
    //�豸��;
    tmpItem.SubItems.Add(GetIdObjectName(81,tmpdata.fieldbyname('damt5').AsString));
    tmpdata.Next;
  end;
end;

procedure TfaqhDevBusiAllot.AddDataToTree(tv: TRzTreeView;
  DataSet: TDataSet; parentId, currId, currName: string);
var
  busiRecPtr: PBusiRec;
  pId:TTreeNode;
begin
  tv.Items.Clear;
  DataSet.First;
  while not DataSet.Eof do
  begin
    New(busiRecPtr);
    busiRecPtr^.busiId := DataSet.fieldbyname(currId).AsInteger;
    busiRecPtr^.busiName := DataSet.fieldbyname(currName).AsString;
    pId:=findParent(tv,DataSet.fieldbyname(parentId).AsInteger,-1);
    if pId<>nil then
      tv.Items.AddChildObject(pId,DataSet.fieldbyname(currName).AsString,busiRecPtr)
    else
      tv.Items.AddObject(nil,DataSet.fieldbyname(currName).AsString,busiRecPtr);
      
    DataSet.Next;
  end;
end;

function TfaqhDevBusiAllot.findParent(tv: TRzTreeView; parentId,
  imgIndex: integer): TTreeNode;
var
  i:Integer;
begin
  Result:=nil;
  for i := 0 to tv.Items.Count-1 do
  begin
    if imgIndex<0 then
    begin
      if Integer(tv.Items[i].Data^)=parentId then
      begin
        Result:=tv.Items[i];
        Exit;
      end;
    end
    else
    begin
      if (Integer(tv.Items[i].Data^)=parentId) and (tv.Items[i].ImageIndex<>imgIndex) then
      begin
        Result:=tv.Items[i];
        Exit;
      end;
    end;
  end;
end;

procedure TfaqhDevBusiAllot.RefreshBusiTree;
var
  HasDataSet:Integer;
  DataSet:TDataSet;
begin
  DataSet := nil;
  Try
    WorkView2.FieldByName('�̻���ʶ').Data.SetInteger(0);
    try
      QueryRequest2.SendCommand;
      HasDataSet:=1;
    finally
      CloseWaiting;
    end;
    if HasDataSet=0 then
    begin
       Context.GetDialogSystem.ShowMessage('�̻���Ϣ��ѯ����������ִ�иò�����');
       Exit;
    end;
    DataSet:=(WorkView2.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;
    AddDataToTree(tvBusiness,DataSet,'lvol1','lvol3','sall_name');
  Finally
    DataSet.Free;
  end;
end;

procedure TfaqhDevBusiAllot.tvBusinessClick(Sender: TObject);
begin
  try
    if not tvBusiness.Selected.Selected then
      exit;
    gbusiId:=PBusiRec(tvBusiness.selected.Data)^.busiId;
    gbusiName:=PBusiRec(tvBusiness.selected.Data)^.busiName;
    lblBusiName.Caption := '�̻���'+gbusiName;
    //pnlAllot.Caption := '�̻�<'+gbusiname+'>�ѷ����豸';
  except
  end;
  //��ѯ�Ѿ���������豸�б�
end;

function TfaqhDevBusiAllot.ifSelectBusi: Integer;
begin
  Result := 0;
  if gbusiId<1 then
    Result := 1;
  if tvBusiness.Selected.HasChildren then
    Result := 1;
end;

procedure TfaqhDevBusiAllot.btnAddClick(Sender: TObject);
var
  i:Integer;
  devId:string;
  errList:TStrings;
begin
  if ifSelectDev(lvDev)=1 then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫ������豸��');
    Exit;
  end;
  if ifSelectBusi=1 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ�����豸���̻���');
    Exit;
  end;
  if checkDateAndTime=1 then
    Exit;
  if Application.MessageBox('��ȷ��Ҫ�����̻�����ѡ����豸��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  errList := nil;
  try
    errList := TStringList.Create;
    for i := 0 to lvDev.Items.Count-1 do
    begin
      if lvDev.Items[i].Checked then
      begin
        devId := lvDev.Items.Item[i].SubItems[0];
        WorkView1.FieldByName('������־').Data.SetString('A');
        WorkView1.FieldByName('���').Data.SetInteger(0);
        WorkView1.FieldByName('�豸��ʶ').Data.SetInteger(StrToInt(devId));
        WorkView1.FieldByName('�̻���ʶ').Data.SetInteger(gbusiId);
        AddRequest.SendCommand;
        if WorkView1.FieldByName('������').Data.AsInteger<>0 then
        begin
          errList.Add('�豸��ʶΪ:'+devId+'���豸����ʧ�ܣ������룺'+WorkView1.FieldByName('������').Data.AsString+',������Ϣ��'+WorkView1.FieldByName('������Ϣ').Data.AsString);
        end;
        Sleep(50);
      end;
    end;
    clearAllotDev(lvDev);
    if errList.Count>0 then
    begin
      errList.SaveToFile('..\bin\logs\�̻��豸����ʧ���б�'+formatdatetime('yyyymmddhhmmss',Now)+'.txt');
      Context.GetDialogSystem.ShowMessage('�̻��豸�������,����ʧ����Ϣ'+inttostr(errlist.Count)+'�������ڰ�װĿ¼\logs��');
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage('�̻��豸������ɣ�');
    end;
  finally
    errList.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhDevBusiAllot.ifSelectDev�Ƿ�ѡ��Ҫ�������豸
  ����:      hanjiwei
  ����:      2008.12.17
  ����:      ��
  ����ֵ:    Integer��0������1������
-------------------------------------------------------------------------------}
function TfaqhDevBusiAllot.ifSelectDev(lv:TRzListView): Integer;
var
  i:Integer;
begin
  Result := 1;
  for i := 0 to lv.Items.Count-1 do
  begin
    if lv.Items[i].Checked then
    begin
      Result := 0;
      Exit;
    end;
  end;
end;

procedure TfaqhDevBusiAllot.btnChangeClick(Sender: TObject);
var
  i:Integer;
  busiDevId:string;
begin
  if ifSelectDev(lvAllotDev)=1 then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫ�޸ĵ��豸��');
    Exit;
  end;
  if checkDateAndTime=1 then
    Exit;
  if Application.MessageBox('��ȷ��Ҫ�޸�ѡ����豸�Ĳ�����',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  for i := 0 to lvAllotDev.Items.Count-1 do
  begin
    if lvAllotDev.Items[i].Checked then
    begin
      busiDevId := lvAllotDev.Items.Item[i].SubItems[0];
      WorkView1.FieldByName('������־').Data.SetString('U');
      WorkView1.FieldByName('���').Data.SetInteger(StrToInt(busiDevId));
      WorkView1.FieldByName('�豸��ʶ').Data.SetInteger(0);
      WorkView1.FieldByName('�̻���ʶ').Data.SetInteger(0);
      AddRequest.SendCommand;
      Sleep(50);
    end;
  end;
  clearAllotDev(lvAllotDev);
  //Context.GetDialogSystem.ShowMessage('�̻��豸�޸���ɣ�');
  if Application.MessageBox('ѡ���豸�޸���ɣ���Ҫˢ����ʾ�����',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  lblShowAllot.Click;
end;

procedure TfaqhDevBusiAllot.btnDelClick(Sender: TObject);
var
  i:Integer;
  busiDevId:string;
begin
  inherited;
  if ifSelectDev(lvAllotDev)=1 then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫɾ�����豸��');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫɾ��ѡ����豸��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  for i := 0 to lvAllotDev.Items.Count-1 do
  begin
    if lvAllotDev.Items[i].Checked then
    begin
      busiDevId := lvAllotDev.Items.Item[i].SubItems[0];
      WorkView1.FieldByName('������־').Data.SetString('D');
      WorkView1.FieldByName('���').Data.SetInteger(StrToInt(busiDevId));
      WorkView1.FieldByName('�豸��ʶ').Data.SetInteger(0);
      WorkView1.FieldByName('�̻���ʶ').Data.SetInteger(0);
      AddRequest.SendCommand;
      Sleep(50);
    end;
  end;
  clearAllotDev(lvAllotDev);
  if Application.MessageBox('ѡ���豸ɾ����ɣ���Ҫˢ����ʾ�����',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  lblShowAllot.Click;

end;

{-------------------------------------------------------------------------------
  ������:    TfaqhDevBusiAllot.checkDateAndTime�ж����ں�ʱ���ʽ�Ƿ���ȷ
  ����:      hanjiwei
  ����:      2008.12.17
  ����:      ��
  ����ֵ:    Integer
-------------------------------------------------------------------------------}
function TfaqhDevBusiAllot.checkDateAndTime: Integer;
begin
  Result := 0;
  if Trim(edtStartDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�������ڲ���Ϊ�գ������룡');
    Result := 1;
    Exit;
  end;

  if Trim(edtStopDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('ͣ�����ڲ���Ϊ�գ������룡');
    Result := 1;
    Exit;
  end;

  if Trim(edtEndTime.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('����ʱ�䲻��Ϊ�գ������룡');
    Result := 1;
    Exit;
  end;
  if (Trim(edtStartDate.Text)<>'') and (CheckInputDateFormat(edtStartDate.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('�������������ʽ����ȷ��');
    //edtStartDate.SetFocus;
    Result := 1;
    Exit;
  end;
  if (Trim(edtStopDate.Text)<>'') and (CheckInputDateFormat(edtStopDate.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('ͣ�����������ʽ����ȷ��');
    //edtStopDate.SetFocus;
    Result := 1;
    Exit;
  end;
  if (Trim(edtEndTime.Text)<>'') and (CheckInputTimeFormat(edtEndTime.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('����ʱ�������ʽ����ȷ��');
    //edtEndTime.SetFocus;
    Result := 1;
    Exit;
  end;

end;

{-------------------------------------------------------------------------------
  ������:    TfaqhDevBusiAllot.clearAllotDev����Ѿ�ѡ����豸
  ����:      hanjiwei
  ����:      2008.12.17
  ����:      lv: TRzListView
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhDevBusiAllot.clearAllotDev(lv: TRzListView);
var
  i:Integer;
begin
  for i := 0 to lv.Items.Count-1 do
  begin
    if lv.Items[i].Checked then
      lv.Items[i].Checked := False;
  end;
end;

procedure TfaqhDevBusiAllot.lblShowAllotClick(Sender: TObject);
var
  tmpData:TDataSet;
  tmpItem:TListItem;
  devCount:Integer;
begin
  WorkView3.FieldByName('�豸��ʶ').Data.SetInteger(0);
  WorkView3.FieldByName('�̻����').Data.SetInteger(gbusiId);
  WorkView3.FieldByName('ʹ��״̬').Data.SetString('1');
  WVRequest1.SendCommand;
  if WorkView3.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView3.FieldByName('��ѯ�����').Data.AsObject);
  //devCount := tmpData.RecordCount;
  lvAllotDev.Items.Clear;
  tmpdata.First;
  while not tmpdata.eof do
  begin
    Inc(devCount);
    tmpItem := lvAllotDev.Items.Add;
    //��������
    tmpItem.Caption := '';//GetIdObjectName(-28,tmpdata.fieldbyname('lserial1').AsString);
    //���
    tmpItem.SubItems.Add(tmpdata.fieldbyname('lvol0').AsString);
    //�豸����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sbankname').AsString);
    //�̻�����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sall_name').AsString);
    //��ʼʱ��
    tmpItem.SubItems.Add(tmpdata.fieldbyname('stime1').AsString);
    //����ʱ��
    tmpItem.SubItems.Add(tmpdata.fieldbyname('stime2').AsString);
    //��������
    tmpItem.SubItems.Add(tmpdata.fieldbyname('Sdate1').AsString);
    //��������
    tmpItem.SubItems.Add(tmpdata.fieldbyname('Sdate2').AsString);
    tmpdata.Next;
  end;
  pnlAllot.Caption := '�̻�<'+gbusiName+'>�ѷ����豸:'+inttostr(devCount)+'̨ ';
end;

initialization
  TUIStdClassFactory.Create('�豸�̻���ϵ����',TfaqhDevBusiAllot);

end.