unit UAsetEquipPara2;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzSplit,
  ComCtrls, UIncrementComboBox, dxCntner, dxInspct, dxInspRw, RzButton,
  RzRadChk, Buttons;

type
  TfaqhsetEquipPara2 = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    RzSizePanel1: TRzSizePanel;
    pnl1: TRzPanel;
    pnl2: TRzPanel;
    RzSizePanel2: TRzSizePanel;
    pnl3: TRzPanel;
    lbl1: TLabel;
    cbbName: TWVComboBox;
    lvResult: TListView;
    lvEqu: TListView;
    WVDownEquipClock: TWorkView;
    WVRDownEquipClock: TWVRequest;
    WVUpEquipClock: TWorkView;
    WVRUpEquipClock: TWVRequest;
    btnClear: TBitBtn;
    WVEquipCompellOut: TWorkView;
    WVREquipCompellOut: TWVRequest;
    WVRDownShareMoney: TWVRequest;
    WVDownShareMoney: TWorkView;
    WVRDownMaxMoney: TWVRequest;
    WVDownMaxMoney: TWorkView;
    WVRCollectConsumeSer: TWVRequest;
    WVCollectConsumeSer: TWorkView;
    WVRCollectAddMoneySer: TWVRequest;
    WVCollectAddMoneySer: TWorkView;
    PnlCard: TRzSizePanel;
    PnlTask: TRzSizePanel;
    dxInspector1: TdxInspector;
    dxInsRowMoney: TdxInspectorTextCurrencyRow;
    dxInsRowBegin: TdxInspectorTextCurrencyRow;
    dxInsRowEnd: TdxInspectorTextCurrencyRow;
    dxInspector2: TdxInspector;
    pnl4: TRzPanel;
    dxInsCheck1: TdxInspectorTextCheckRow;
    QueryRequestCustomerKindByKey: TWVRequest;
    WorkViewCustomerKindByKey: TWorkView;
    WorkViewEquGroup: TWorkView;
    WVRequestEquGroup: TWVRequest;
    btnselectall: TBitBtn;
    btnselectno: TBitBtn;
    WorkViewQueryEquByKey: TWorkView;
    WVRequestQueryEquByKey: TWVRequest;
    WVRSetHisSumMoney: TWVRequest;
    WVSetHisSumMoney: TWorkView;
    Label4: TLabel;
    WVComboBox18: TWVComboBox;
    Label5: TLabel;
    WVComboBox17: TWVComboBox;
    WVGateOpen: TWorkView;
    WVRGateOpen: TWVRequest;
    dxInsRowGate: TdxInspectorTextPickRow;
    wvSetFeeType: TWorkView;
    wvrSetFeeType: TWVRequest;
    wvrDictQ: TWVRequest;
    wvDictQ: TWorkView;
    dxInsRowFeeType: TdxInspectorTextPickRow;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure cbbNameChange(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure lvEquClick(Sender: TObject);
    procedure btnselectallClick(Sender: TObject);
    procedure btnselectnoClick(Sender: TObject);
  private
     tmpdataset: TDataSet;
     procedure setInsBordSingle();
     procedure setInsBordNone();
     procedure showCardType();
     procedure showFeeType();
     //procedure showCCInfo();
     procedure hideCardType();
     procedure createInsContent();
     procedure setInsValue();
     function getTaskId(): Integer ;
     procedure executeTask();
     procedure showCustType;
     procedure AddListViewItem(FEquipID: string; FSuccess: string);
     //�´��豸ʱ��
     procedure downEquipClock();
     //�ϴ��豸ʱ��
     procedure upEquipClock();
     //ǿ���豸Ǩ��
     procedure EquipCompellOut();
     //�´����ѱ���
     procedure DownShareMoney();
     //�´���������޶�
     procedure DownMaxMoney();
     //�ɼ���ʷ������ˮ
     procedure CollectConsumeSer();
     //�ɼ��ֽ��ֵ��ˮ
     procedure CollectAddMoneySer();
     //�豸����������
     procedure setGroup();
     //�ۼ������޶�
     procedure setHisSumMoney();
     //�ʹ���Ϣ����
     //procedure setCCInfo();
     //�Ž���������
     procedure setGateOpen;
     //��������
     procedure setFeeType;
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetEquipPara2: TfaqhsetEquipPara2;

implementation

uses KsFrameworks, KSDataDictionary,
  UCMqhSubSystemImp;
     
{$R *.DFM}

procedure TfaqhsetEquipPara2.Init;
var
  i:Integer;
begin
  inherited;
  {
  WorkView.FieldByName('�豸����').Data.SetString('');
  WorkView.FieldByName('�ϼ��豸').Data.SetString('');
  WorkView.FieldByName('�豸������').Data.SetString('');
  WorkView.FieldByName('��ϵͳ').DefaultValue := 0;
  WorkView.Reset;
  }
  hideCardType;
  //cbxSelectAll.Visible := False;
  dxInspector1.Visible := False;
        for I := 0 to 3 do
        dxInspector1.Rows[I].Visible:=False;

end;

procedure TfaqhsetEquipPara2.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhsetEquipPara2.btnQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
begin
  MainRequest.SendCommand;
  lvEqu.Items.Clear;
  inherited;
  tmpdataset := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if tmpdataset.fieldbyname('lvol0').AsInteger=1 then
    begin
      tmpdataset.Next;
      Continue;
    end;
    tmpItem := lvEqu.Items.Add;
    //tmpItem.Caption := tmpdataset.fieldbyname('lvol0').AsString;//
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);//�豸���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);//�豸������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString); //�豸����
    tmpItem.SubItems.Add(GetIdObjectName(-31,tmpdataset.fieldbyname('damt6').AsString));//�ϼ��豸
    tmpItem.SubItems.Add(GetIdObjectName(47,tmpdataset.fieldbyname('sbank_code').AsString));//�豸����
    tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdataset.fieldbyname('lserial0').AsString));//������ϵͳ
    tmpdataset.Next;
  end;
end;

procedure TfaqhsetEquipPara2.createInsContent;
var
  taskId : Integer;
  I :Integer;
begin
  taskId := getTaskId;
  if taskId=0 then
    Exit;
  case taskId of
    3:
    begin
      showCardType;
      showCustType;
      pnl4.Caption := '�շ����';
      //cbxSelectAll.Visible := True;

      btnselectno.Click;
    end;
    //
    1,2,4,5:
    begin
      setInsValue;
      dxInsRowMoney.Visible := False;
      dxInsRowEnd.Visible := False;
      dxInsRowBegin.Visible := False;
      dxInsRowGate.Visible := False;
      dxInsRowFeeType.Visible := False;
      //cbxSelectAll.Visible := False;
      setInsBordNone;
      hideCardType;
    end;
    //������ѽ��
    6 :
    begin
      setInsValue;
      dxInsRowMoney.Visible := True;
      dxInsRowMoney.Caption := '��������޶�(Ԫ)';
      dxInsRowEnd.Visible := False;
      dxInsRowBegin.Visible := False;
      dxInsRowGate.Visible := False;
      dxInsRowFeeType.Visible := False;
      //cbxSelectAll.Visible := False;
      setInsBordSingle;
      hideCardType;
    end;
    //��ʷ������ˮ�ɼ�����ʷ��ֵ�����ˮ�ɼ�
    7,8:
    begin
      setInsValue;
      dxInsRowMoney.Visible := False;
      dxInsRowBegin.Visible := True;
      dxInsRowEnd.Visible := True;
      dxInsRowBegin.Caption := '��ʼ��ˮ��';
      dxInsRowEnd.Caption := '������ˮ��';
      dxInsRowGate.Visible := False;
      dxInsRowFeeType.Visible := False;
      //cbxSelectAll.Visible := False;
      setInsBordSingle;
      hideCardType;
    end;
    9 :
    begin
      setInsValue;
      dxInsRowMoney.Visible := True;
      dxInsRowMoney.Caption := '�ۼ������޶�(Ԫ)';
      dxInsRowEnd.Visible := False;
      dxInsRowBegin.Visible := False;
      dxInsRowFeeType.Visible := False;
      //cbxSelectAll.Visible := False;
      dxInsRowGate.Visible := False;
      setInsBordSingle;
      hideCardType;
    end;
    10:
    begin
      setInsValue;
      dxInsRowMoney.Visible := False;
      dxInsRowEnd.Visible := False;
      dxInsRowBegin.Visible := False;
      dxInsRowFeeType.Visible := False;
      dxInsRowGate.Visible := True;
      dxInsRowGate.Caption := '�Ž�״̬';
      //cbxSelectAll.Visible := False;
      setInsBordNone;
      hideCardType;
    end;
    11:
    begin
      setInsValue;
      showFeeType;
      dxInsRowMoney.Visible := False;
      dxInsRowEnd.Visible := False;
      dxInsRowBegin.Visible := False;
      dxInsRowFeeType.Visible := True;
      dxInsRowGate.Visible := False;
      dxInsRowFeeType.Caption := 'ˮ�ط���';
      //cbxSelectAll.Visible := False;
      setInsBordNone;
      hideCardType;
    end;
    else
    begin
      setInsValue();
      setInsBordNone;
      hideCardType;
      for I := 0 to 2 do
        dxInspector1.Rows[I].Visible:=False;
    end;
  end;

end;

procedure TfaqhsetEquipPara2.cbbNameChange(Sender: TObject);
begin
  //inherited;
  createInsContent;
end;

procedure TfaqhsetEquipPara2.setInsValue;
begin
  dxInspector1.Visible := True;
  dxInsRowBegin.Text:='';
  dxInsRowEnd.Text:='';
  dxInsRowMoney.Text:='';
end;

procedure TfaqhsetEquipPara2.btnPrintClick(Sender: TObject);
begin
  //inherited;
  executeTask;
end;

procedure TfaqhsetEquipPara2.executeTask;
var
  taskId : Integer;
begin
  taskId := getTaskId;
  if taskId=1 then
    downEquipClock()
  else if taskId=2 then
    upEquipClock
  else if taskId=3 then
    setGroup
  else if taskId=4 then
    EquipCompellOut
  else if taskId=5 then
    DownShareMoney
  else if taskId=6 then
    DownMaxMoney
  else if taskId=7 then
    CollectConsumeSer
  else if taskId=8 then
    CollectAddMoneySer
  else if taskId=9 then
    setHisSumMoney
  else if taskId=10 then
    setGateOpen
  else if taskId=11 then
    setFeeType;
end;

function TfaqhsetEquipPara2.getTaskId(): Integer ;
begin
  try
    Result := StrToInt(Copy(cbbName.Text,0,Pos('-',cbbName.Text)-1));
  except
    Result := 0;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.upEquipClock�´��豸ʱ��
  ����:      hanjiwei
  ����:      2006.07.05
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.downEquipClock;
var
  I:Integer;
  DownDateTime,Id, EquID,EquName: string;
begin
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      Id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVDownEquipClock.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WVDownEquipClock.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      //WVDownEquipClock.FieldByName('�´�ʱ��').Data.SetString(DownDateTime);
      try
        WVRDownEquipClock.SendCommand;
        if WVDownEquipClock.FieldByName('������').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVDownEquipClock.FieldByName('������Ϣ').Data.AsString);
        end else
        begin
          DownDateTime:=WVDownEquipClock.FieldByName('�´�ʱ��').Data.AsString;
          AddListViewItem(EquName, WVDownEquipClock.FieldByName('������Ϣ').Data.AsString+' '+DownDateTime);
        end;
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.upEquipClock�ϴ��豸ʱ��
  ����:      hanjiwei
  ����:      2006.07.05
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.upEquipClock;
var
  I:Integer;
  UpDateTime, OutMessage,Id,EquID,EquName: string;
begin
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      Id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVUpEquipClock.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WVUpEquipClock.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      try
        WVRUpEquipClock.SendCommand;
        UpDateTime := WVUpEquipClock.FieldByName('�ϴ�ʱ��').Data.AsString;
        OutMessage := WVUpEquipClock.FieldByName('������Ϣ').Data.AsString;
        AddListViewItem(EquName, OutMessage + ' ' + UpDateTime);
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

procedure TfaqhsetEquipPara2.AddListViewItem(FEquipID, FSuccess: string);
var TmpItem: TListItem;
begin
  TmpItem := lvResult.Items.Add;
  TmpItem.Caption := cbbName.Text;
  //TmpItem.SubItems.Add(cbbName.Text);
  TmpItem.SubItems.Add(FormatDateTime('yyyy-mm-dd hh:MM:ss',Now));
  TmpItem.SubItems.Add(FEquipID);
  TmpItem.SubItems.Add(FSuccess);
end;

procedure TfaqhsetEquipPara2.btnClearClick(Sender: TObject);
begin
  //inherited;
  lvResult.Items.Clear;
end;
{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.upEquipClockǿ���豸Ǩ��
  ����:      hanjiwei
  ����:      2006.07.05
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}

procedure TfaqhsetEquipPara2.EquipCompellOut;
var
  I:Integer;
  id,EquID,EquName: string;
begin
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVEquipCompellOut.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WVEquipCompellOut.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      try
        WVREquipCompellOut.SendCommand;
        if WVEquipCompellOut.FieldByName('������').Data.AsInteger<>0 then
        begin
          AddListViewItem(EquName,WVEquipCompellOut.FieldByName('������Ϣ').Data.AsString);
        end else
        begin
          AddListViewItem(EquName,WVEquipCompellOut.FieldByName('������Ϣ').Data.AsString);
        end;
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.upEquipClock�´����ѱ���
  ����:      hanjiwei
  ����:      2006.07.05
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.DownShareMoney;
var
  I:Integer;
  EquID,EquPhyId,EquName: string;
begin
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      EquID := lvEqu.Items[i].SubItems[0];
      EquPhyId := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVDownShareMoney.FieldByName('�ն��豸ID').Data.SetInteger(StrToInt(EquID));
      WVDownShareMoney.FieldByName('�豸������').Data.SetString(EquPhyId);
      try
        WVRDownShareMoney.SendCommand;
        if WVDownShareMoney.FieldByName('������').Data.AsInteger <> 0 then
          AddListViewItem(EquName, WVDownShareMoney.FieldByName('������Ϣ').Data.AsString)
        else
          AddListViewItem(EquName, '���ش��ѳɹ���');
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.upEquipClock�´���������޶�
  ����:      hanjiwei
  ����:      2006.07.05
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.DownMaxMoney;
var
  I:Integer;
  id,EquID,EquName: string;
  Money : Integer;
begin
  if dxInsRowMoney.Text='' then
    Money := 1*100
  else
    Money := StrToInt(dxInsRowMoney.Text)*100;
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVDownMaxMoney.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WVDownMaxMoney.FieldByName('��������޶�').Data.SetInteger(Money);
      WVDownMaxMoney.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      try
        WVRDownMaxMoney.SendCommand;
        if WVDownMaxMoney.FieldByName('������').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVDownMaxMoney.FieldByName('������Ϣ').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, WVDownMaxMoney.FieldByName('������Ϣ').Data.AsString);
        end;
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.upEquipClock�����ۼ����ѽ��
  ����:      hanjiwei
  ����:      2006.07.05
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.setHisSumMoney;
var
  I:Integer;
  id,EquID,EquName: string;
  Money : Integer;
begin
  if dxInsRowMoney.Text='' then
    Money := 1*100
  else
    Money := StrToInt(dxInsRowMoney.Text)*100;
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVSetHisSumMoney.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WVSetHisSumMoney.FieldByName('�ۼ������޶�').Data.SetInteger(Money);
      WVSetHisSumMoney.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      try
        WVRSetHisSumMoney.SendCommand;
        if WVSetHisSumMoney.FieldByName('������').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVSetHisSumMoney.FieldByName('������Ϣ').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, WVSetHisSumMoney.FieldByName('������Ϣ').Data.AsString);
        end;
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.upEquipClock�ɼ���ʷ������ˮ
  ����:      hanjiwei
  ����:      2006.07.05
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.CollectConsumeSer;
var
  I:Integer;
  id,EquID,EquName: string;
  beginCode,endCode : Integer;
begin
  if (dxInsRowBegin.Text='')or(dxInsRowEnd.Text='') then
  begin
    ShowMessage('��������ʼ��ˮ�źͽ�����ˮ�ţ�');
    Exit;
  end;
  beginCode := StrToInt(dxInsRowBegin.Text);
  endCode := StrToInt(dxInsRowEnd.Text);
  if beginCode>endCode then
  begin
    ShowMessage('ϵͳ��ʾ����ʼ��ˮ�Ų��ܴ��ڽ�����ˮ�ţ�');
    Exit;
  end;
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVCollectConsumeSer.SynchronizeCtrlsToFields;
      WVCollectConsumeSer.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WVCollectConsumeSer.FieldByName('������ʼ��ˮ��').Data.SetInteger(beginCode);
      WVCollectConsumeSer.FieldByName('����������ˮ��').Data.SetInteger(endCode);
      WVCollectConsumeSer.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      try
        WVRCollectConsumeSer.SendCommand;
        if WVCollectConsumeSer.FieldByName('������').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVCollectConsumeSer.FieldByName('������Ϣ').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, '�ɼ���ʷ��ˮ�ɹ���');
        end;
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.upEquipClock�ɼ��ֽ��ֵ������ˮ
  ����:      hanjiwei
  ����:      2006.07.05
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.CollectAddMoneySer;
var
  I:Integer;
  id,EquID,EquName: string;
  beginCode,endCode : Integer;
begin
  if (dxInsRowBegin.Text='')or(dxInsRowEnd.Text='') then
  begin
    ShowMessage('��������ʼ��ˮ�źͽ�����ˮ�ţ�');
    Exit;
  end;
  beginCode := StrToInt(dxInsRowBegin.Text);
  endCode := StrToInt(dxInsRowEnd.Text);
  if beginCode>endCode then
  begin
    ShowMessage('ϵͳ��ʾ����ʼ��ˮ�Ų��ܴ��ڽ�����ˮ�ţ�');
    Exit;
  end;
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVCollectAddMoneySer.SynchronizeCtrlsToFields;
      WVCollectAddMoneySer.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WVCollectAddMoneySer.FieldByName('������ʼ��ˮ��').Data.SetInteger(beginCode);
      WVCollectAddMoneySer.FieldByName('����������ˮ��').Data.SetInteger(endCode);
      WVCollectAddMoneySer.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      try
        WVRCollectAddMoneySer.SendCommand;
        if WVCollectAddMoneySer.FieldByName('������').Data.AsInteger<>0 then
        begin
          AddListViewItem(EquName, WVCollectAddMoneySer.FieldByName('������Ϣ').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, '�ɹ���');
        end;
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

procedure TfaqhsetEquipPara2.hideCardType;
begin
  PnlCard.Visible:=False;
  PnlTask.HotSpotVisible:=False;
  dxInspector1.Visible := True;
end;

procedure TfaqhsetEquipPara2.showCardType;
begin
  PnlCard.Visible:=True;
  PnlTask.HotSpotVisible:=False;
  dxInspector1.Visible := False;
end;

procedure TfaqhsetEquipPara2.setInsBordSingle;
begin
  dxInspector1.BorderStyle := bsSingle;
end;

procedure TfaqhsetEquipPara2.setInsBordNone;
begin
  dxInspector1.BorderStyle := bsNone;
end;

procedure TfaqhsetEquipPara2.showCustType;
var
  tempDataSet : TDataSet;
  custType : string;
  custTypeCode : Integer;
  i:Integer;
begin
  for i := 0 to 255 do
    dxInspector2.Rows[i].Visible:=False;
  WorkViewCustomerKindByKey.FieldByName('lcert_code').Data.setstring('-43');
  QueryRequestCustomerKindByKey.SendCommand;
  tempDataSet := TDataSet(WorkViewCustomerKindByKey.FieldByName('��ѯ�����').Data.AsObject);
  tempDataSet.First;
  while not tempDataSet.Eof do
  begin
    custType := tempDataSet.fieldbyname('sall_name').AsString;
    custTypeCode := tempDataSet.fieldbyname('sname').AsInteger;

    dxInspector2.Rows[custTypeCode].Visible:=True;
    dxInspector2.Rows[custTypeCode].Caption := IntToStr(custTypeCode)+'-'+custtype;
    tempDataSet.Next;
  end;
end;

procedure TfaqhsetEquipPara2.btn1Click(Sender: TObject);
var
  i:Integer;
  ss:string;
begin
  for i := 1 to 254 do
    if (dxInspector2.Rows[i].DisplayText='True') then
      ss := ss+'1'
    else
      ss := ss+'0';
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.setGroup���ÿ�Ȩ�޷���
  ����:      hanjiwei
  ����:      2006.07.11
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.setGroup;
var
  groupStr : string;
  EquID : Integer;
  I :Integer;
  J :Integer;
  //K :Integer;
  EquName :string;
  //selectId :Integer;
begin
  //selectId := 0;
  for i := 1 to 254 do
    if (dxInspector2.Rows[i].DisplayText='True') then
      groupStr := groupStr+'1'
    else
      groupStr := groupStr+'0';
    {
  for K := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[K].Checked then
    begin
      selectId := selectId+1;
      if selectId>1 then
      begin
        ShowMessage('��ʾ��Ϣ��һ��ֻ����һ���豸��');
        Exit;
      end;
    end;
  end;  }
  for J := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[J].Checked then
    begin
      EquID := StrToInt(lvEqu.Items[J].SubItems[0]);
      EquName := lvEqu.Items[J].SubItems[2];
      WorkViewEquGroup.FieldByName('�豸���').Data.SetInteger(EquID);
      WorkViewEquGroup.FieldByName('����Ȩ��').Data.SetString(groupStr);
      try
        WVRequestEquGroup.SendCommand;
        if WorkViewEquGroup.FieldByName('������').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WorkViewEquGroup.FieldByName('������Ϣ').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, WorkViewEquGroup.FieldByName('������Ϣ').Data.AsString);
        end;
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

procedure TfaqhsetEquipPara2.lvEquClick(Sender: TObject);
{
var
  cbbcode : string;
  K:Integer;
  selectId:Integer;
  equid:Integer;
  tempdataset:TDataSet;
  scardtype : string;
  i:Integer;
  poscardtype : string; }
begin
  {
  selectId := 0;
  equid := 0;
  cbbcode:= Copy(cbbName.Text,0,Pos('-',cbbName.Text)-1);
  if cbbcode='3' then
  begin
    for K := 0 to lvEqu.Items.Count-1 do
    begin
      if lvEqu.Items[K].Checked then
      begin
        selectId := selectId+1;
        if selectId>1 then
        begin
          ShowMessage('��ʾ��Ϣ��һ��ֻ����һ���豸��');
          btnselectno.Click;
          Exit;
        end;
      end;
    end;

    {
    for K := 0 to lvEqu.Items.Count-1 do
    begin
      if lvEqu.Items[K].Checked then
        equid := StrToInt(lvEqu.Items[K].SubItems[0]);
    end;
    WorkViewQueryEquByKey.FieldByName('�豸��ʶ').Data.SetInteger(equid);
    WVRequestQueryEquByKey.SendCommand;
    tempdataset := TDataSet(WorkViewQueryEquByKey.FieldByName('��ѯ�����').Data.AsObject);
    scardtype := tempdataset.fieldbyname('saddr').AsString;
    for i := 1 to 254 do
    begin
      poscardtype := Copy(scardtype,i,1);
      if poscardtype='1' then
        dxInspector2.Rows[i].EditText:='True'
      else
        dxInspector2.Rows[i].EditText:='False';
    end;
    
  end; }
end;

procedure TfaqhsetEquipPara2.btnselectallClick(Sender: TObject);
var
  i:Integer;
  cbbcode:string;
begin
  cbbcode:= Copy(cbbName.Text,0,Pos('-',cbbName.Text)-1);
  if cbbcode='3' then
  begin
    ShowMessage('��ʾ��Ϣ���ù��ܲ���ȫѡ�豸��');
    Exit;
  end;
  for i := 0 to lvEqu.Items.Count-1 do
  begin
    lvEqu.Items[i].Checked:=True;
  end;
end;

procedure TfaqhsetEquipPara2.btnselectnoClick(Sender: TObject);
var
  i:Integer;
begin
  for i := 0 to lvEqu.Items.Count-1 do
  begin
    lvEqu.Items[i].Checked:=False;
  end;
end;
{
procedure TfaqhsetEquipPara2.showCCInfo;
var
  tempDataSet : TDataSet;
  name : string;
  id : Integer;
  i:Integer;
begin
  for i := 0 to 255 do
    dxInspector2.Rows[i].Visible:=False;
  WVCCQuery.FieldByName('������־').Data.setstring('R');
  WVRCCQuery.SendCommand;
  tempDataSet := TDataSet(WVCCQuery.FieldByName('��ѯ�����').Data.AsObject);
  tempDataSet.First;
  while not tempDataSet.Eof do
  begin
    Name := tempDataSet.fieldbyname('sall_name').AsString;
    Id := tempDataSet.fieldbyname('lvol0').AsInteger;

    dxInspector2.Rows[Id].Visible:=True;
    dxInspector2.Rows[Id].Caption := IntToStr(id)+'-'+name;
    tempDataSet.Next;
  end;
end;
}
{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.setCCInfo�ʹ���Ϣ����
  ����:      hanjiwei
  ����:      2007.08.09
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
{
procedure TfaqhsetEquipPara2.setCCInfo;
var
  groupStr : string;
  EquID : Integer;
  I :Integer;
  J :Integer;
  EquName :string;
  //selectId :Integer;
  ccId:string;
begin
  //selectId := 0;
  for i := 1 to 254 do
  begin
    if (dxInspector2.Rows[i].DisplayText='True') then
    begin
      ccId := Copy(dxInspector2.Rows[i].Caption,1,Pos('-',dxInspector2.Rows[i].Caption)-1);
      groupStr := groupStr+' '+ccId;
    end;
  end;


  for J := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[J].Checked then
    begin
      EquID := StrToInt(lvEqu.Items[J].SubItems[0]);
      EquName := lvEqu.Items[J].SubItems[2];
      WVCCInfo.FieldByName('�豸���').Data.SetInteger(EquID);
      WVCCInfo.FieldByName('�ʹ���Ϣ').Data.SetString(groupStr);
      try
        WVRCCInfo.SendCommand;
        if WVCCInfo.FieldByName('������').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVCCInfo.FieldByName('������Ϣ').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, WVCCInfo.FieldByName('������Ϣ').Data.AsString);
        end;
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;
}
{-------------------------------------------------------------------------------
  ������:    TfaqhsetEquipPara2.setGateOpen�Ž���������
  ����:      hanjiwei
  ����:      2007.11.26
  ����:      ��
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.setGateOpen;
var
  I:Integer;
  Id, EquID,EquName: string;
  gateSign:string;
begin
  gateSign := Copy(dxInsRowGate.Text,1,Pos('-',dxInsRowGate.Text)-1);
  if (gateSign='') or (gateSign='-') then
  begin
    ShowMessage('����ѡ���Ž�״̬��Ȼ�����´�������');
    exit;
  end;
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      Id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVGateOpen.FieldByName('�ն��豸ID').Data.SetString(EquID);
      WVGateOpen.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      WVGateOpen.FieldByName('��־').Data.SetInteger(StrToInt(gateSign));
      try
        WVRGateOpen.SendCommand;
        if WVGateOpen.FieldByName('������').Data.AsInteger <> 0 then
          AddListViewItem(EquName, WVGateOpen.FieldByName('������Ϣ').Data.AsString)
        else
          AddListViewItem(EquName, WVGateOpen.FieldByName('������Ϣ').Data.AsString);
      except
        AddListViewItem(EquName, 'ǰ��̨����ʧ��');
      end;
    end;
  end;
end;

procedure TfaqhsetEquipPara2.showFeeType;
var
  tempDataSet : TDataSet;
  feeTypeName : string;
  feeType : string;
  //i:Integer;
begin
  wvDictQ.FieldByName('�����ֵ���Ŀ').Data.SetInteger(-63);
  wvrDictQ.SendCommand;
  tempDataSet := TDataSet(wvDictQ.FieldByName('��ѯ�����').Data.AsObject);
  tempDataSet.First;
  while not tempDataSet.Eof do
  begin
    feeTypeName := tempDataSet.fieldbyname('sall_name').AsString;
    feeType := tempDataSet.fieldbyname('sname').AsString;
    dxInsRowFeeType.Items.Add(feeType+'-'+feeTypeName);
    //dxInspector2.Rows[custTypeCode].Caption := IntToStr(custTypeCode)+'-'+custtype;
    tempDataSet.Next;
  end;
end;

procedure TfaqhsetEquipPara2.setFeeType;
var
  I:Integer;
  Id, EquName: string;
  feeType:string;
begin
  feeType := Copy(dxInsRowFeeType.Text,1,Pos('-',dxInsRowFeeType.Text)-1);
  if (feeType='') or (feeType='-') then
  begin
    ShowMessage('����ѡ��������ͣ�Ȼ�����´�������');
    exit;
  end;
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      Id := lvEqu.Items[i].SubItems[0];
      //EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      //wvSetFeeType.FieldByName('�ն��豸ID').Data.SetString(EquID);
      wvSetFeeType.FieldByName('�豸���').Data.SetInteger(StrToInt(id));
      wvSetFeeType.FieldByName('��־').Data.SetInteger(StrToInt(feeType));
      try
        wvrSetFeeType.SendCommand;
        if wvSetFeeType.FieldByName('������').Data.AsInteger <> 0 then
          AddListViewItem(EquName, wvSetFeeType.FieldByName('������Ϣ').Data.AsString)
        else
          AddListViewItem(EquName, wvSetFeeType.FieldByName('������Ϣ').Data.AsString);
      except
        on e:Exception do
        begin
          AddListViewItem(EquName, 'ǰ��̨����ʧ��-'+e.Message);
        end;
      end;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('�豸��������',TfaqhsetEquipPara2);

end.