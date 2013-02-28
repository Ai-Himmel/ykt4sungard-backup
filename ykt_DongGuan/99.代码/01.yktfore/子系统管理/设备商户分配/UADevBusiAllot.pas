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
    btnDel: TBitBtn;
    lvDev: TRzListView;
    rzszpnl1: TRzSizePanel;
    lvAllotDev: TRzListView;
    pnlAllot: TPanel;
    lblShowAllot: TRzURLLabel;
    Panel1: TPanel;
    Label2: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label10: TLabel;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit8: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    edtPosIdQ: TWVEdit;
    btnDevQ: TBitBtn;
    Panel2: TPanel;
    btnBusiQ: TBitBtn;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    lvBusi: TRzListView;
    lblBusi: TLabel;
    Label3: TLabel;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    WVEdit3: TWVEdit;
    Label9: TLabel;
    Label11: TLabel;
    WVComboBox4: TWVComboBox;
    WVComboBox5: TWVComboBox;
    QueryRequest: TWVRequest;
    WorkView3: TWorkView;
    lblDev: TLabel;
    procedure btnQueryClick(Sender: TObject);
    procedure btnDelClick(Sender: TObject);
    procedure lblShowAllotClick(Sender: TObject);
    procedure btnDevQClick(Sender: TObject);
    procedure RzDBGrid1CellClick(Column: TColumn);
    procedure btnBusiQClick(Sender: TObject);
    procedure lvBusiClick(Sender: TObject);
    procedure lvDevClick(Sender: TObject);
  private
    { Private declarations }
    gbusiId:Integer;
    gbusiName:string;
    sserialNo:string;
    ssDevid:string;
    function ifSelectDev(lv:TRzListView): Integer;

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
  lblBusi.Caption := '';
  lblDev.Caption := '';
  //lblDevCount.Caption := '';
end;
procedure TfaqhDevBusiAllot.btnQueryClick(Sender: TObject);
begin
  {
  if ifSelectDev(lvDev)=1 then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫ������豸��');
    Exit;
  end;
  }
  if Application.MessageBox('��ȷ��Ҫ�����̻�����ѡ����豸��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  //devId := lvDev.Items.Item[i].SubItems[0];
  WorkView.FieldByName('��������').Data.SetString('A');
  WorkView.FieldByName('�豸���').Data.SetString(ssDevid);
  WorkView.FieldByName('�̻���').Data.SetInteger(gbusiId);
  WorkView.FieldByName('���к�').Data.SetString(sserialNo);
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  clearAllotDev(lvDev);
  Context.GetDialogSystem.ShowMessage('�̻��豸������ɣ�');
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

procedure TfaqhDevBusiAllot.btnDelClick(Sender: TObject);
var
  i:Integer;
  devId:string;
  busiId:string;
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
      devId := lvAllotDev.Items.Item[i].Caption;
      busiId := lvAllotDev.Items.Item[i].SubItems[2];
      WorkView.FieldByName('��������').Data.SetString('D');
      WorkView.FieldByName('�豸���').Data.SetString(devId);
      WorkView.FieldByName('���к�').Data.SetString(lvAllotDev.Items.Item[i].SubItems[1]);
      WorkView.FieldByName('�̻���').Data.SetInteger(StrToInt(busiId));
      MainRequest.SendCommand;
      Sleep(50);
    end;
  end;
  clearAllotDev(lvAllotDev);
  if Application.MessageBox('ѡ���豸ɾ����ɣ���Ҫˢ����ʾ�����',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  lblShowAllot.Click;

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
  pnlAllot.Caption :='';
  lvAllotDev.Items.Clear;
  //WorkView2.FieldByName('�豸���').Data.SetInteger(0);
  WorkView2.FieldByName('�̻���').Data.SetInteger(gbusiId);
  //WorkView3.FieldByName('ʹ��״̬').Data.SetString('1');
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView2.FieldByName('��ѯ�����').Data.AsObject);
  //devCount := tmpData.RecordCount;
  tmpdata.First;
  devCount:=0;
  while not tmpdata.eof do
  begin
    Inc(devCount);
    tmpItem := lvAllotDev.Items.Add;
    //�豸���
    tmpItem.Caption := tmpdata.fieldbyname('scert_no').AsString;
    //�豸����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sbankname').AsString);
    //�豸�ն����к�
    tmpItem.SubItems.Add(tmpdata.fieldbyname('scust_auth').AsString);
    //�̻����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('lvol0').AsString);
    //�̻�����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('snote').AsString);
    //�豸���к�
    tmpItem.SubItems.Add(tmpdata.fieldbyname('semail2').AsString);
    //�豸�ն˺�
    tmpItem.SubItems.Add(tmpdata.fieldbyname('semail').AsString);
    //�豸�ͺ�
    tmpItem.SubItems.Add(GetIdObjectName(216,tmpdata.fieldbyname('lvol2').AsString));
    //�豸����
    tmpItem.SubItems.Add(GetIdObjectName(221,tmpdata.fieldbyname('spost_code').AsString));
    //�����̻���
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname').AsString);
    //ʡ�̻���
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname2').AsString);
    //�̻�����
    tmpItem.SubItems.Add(GetIdObjectName(216,tmpdata.fieldbyname('sbranch_code0').AsString));
    tmpdata.Next;
  end;
  pnlAllot.Caption := '�̻�<'+gbusiName+'>�ѷ����豸:'+inttostr(devCount)+'̨ ';
end;

procedure TfaqhDevBusiAllot.btnDevQClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdata:TDataSet;
begin
  WorkView1.FieldByName('������־').Data.SetString('R');
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  lvDev.Items.Clear;

  tmpdata := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  tmpdata.First;
  while not tmpdata.eof do
  begin
    tmpItem := lvDev.Items.Add;
    //��������
    tmpItem.Caption := GetIdObjectName(229,tmpdata.fieldbyname('sstock_code').AsString);
    //�豸���
    tmpItem.SubItems.Add(tmpdata.fieldbyname('scert_no').AsString);
    //�豸����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sbankname').AsString);
    //�豸�ն˺�
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname').AsString);
    //�豸���к�
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname2').AsString);
    //�豸�ͺ�
    tmpItem.SubItems.Add(GetIdObjectName(223,tmpdata.fieldbyname('lvol2').AsString));
    //�豸����
    tmpItem.SubItems.Add(GetIdObjectName(221,tmpdata.fieldbyname('spost_code').AsString));
    //�豸��;
    tmpItem.SubItems.Add(GetIdObjectName(222,tmpdata.fieldbyname('lvol4').AsString));
    //�豸״̬
    tmpItem.SubItems.Add(GetIdObjectName(220,tmpdata.fieldbyname('sstatus0').AsString));
    //��������
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sdate0').AsString);
    tmpdata.Next;
  end;
end;

procedure TfaqhDevBusiAllot.RzDBGrid1CellClick(Column: TColumn);
begin
  {
  try
    gbusiId := RzDBGrid1.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('����'+e.Message);
    end;
  end;
  }
end;

procedure TfaqhDevBusiAllot.btnBusiQClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdata:TDataSet;
begin
  lvBusi.Items.Clear;
  WorkView3.FieldByName('������־').Data.SetString('R');
  try
    QueryRequest.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;

  if WorkView3.FieldByName('������').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView3.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  

  tmpdata := TDataSet(WorkView3.FieldByName('��ѯ�����').Data.AsObject);
  tmpdata.First;
  while not tmpdata.eof do
  begin
    tmpItem := lvBusi.Items.Add;
    //�̻����
    tmpItem.Caption := tmpdata.fieldbyname('lvol0').AsString;
    //�̻�����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sall_name').AsString);
    //�豸�ն����к�
    tmpItem.SubItems.Add(tmpdata.fieldbyname('scust_auth').AsString);
    //ʡ�̻����
    tmpItem.SubItems.Add(GetIdObjectName(221,tmpdata.fieldbyname('sstock_code').AsString));
    //�̻�����
    tmpItem.SubItems.Add(GetIdObjectName(239,tmpdata.fieldbyname('scurrency_type').AsString));
    //��ҵ����
    tmpItem.SubItems.Add(GetIdObjectName(217,tmpdata.fieldbyname('lvol1').AsString));
    tmpdata.Next;
  end;

end;

procedure TfaqhDevBusiAllot.lvBusiClick(Sender: TObject);
var
  i:Integer;
begin
  try
    i:=lvBusi.Selected.Index;
    gbusiId := StrToInt(lvBusi.Items.Item[i].Caption);
    gbusiName := lvBusi.Items.Item[i].SubItems[0];
    sserialNo := lvBusi.Items.Item[i].SubItems[1];
    lblBusi.Caption := '��ǰѡ���̻�-'+gbusiName;
  except

  end;
  //ShowMessage(IntToStr(gbusiId));
end;

procedure TfaqhDevBusiAllot.lvDevClick(Sender: TObject);
var
  i:Integer;
begin
  try
    i:=lvDev.Selected.Index;
    ssDevid := lvDev.Items.Item[i].SubItems[0];
    lblDev.Caption := '��ǰ�豸-'+lvDev.Items.Item[i].SubItems[1];
  except

  end;

end;

initialization
  TUIStdClassFactory.Create('�豸�̻���',TfaqhDevBusiAllot);

end.