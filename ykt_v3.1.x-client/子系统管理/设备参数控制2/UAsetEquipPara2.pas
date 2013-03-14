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
     //下传设备时钟
     procedure downEquipClock();
     //上传设备时钟
     procedure upEquipClock();
     //强制设备迁出
     procedure EquipCompellOut();
     //下传搭伙费比率
     procedure DownShareMoney();
     //下传大额消费限额
     procedure DownMaxMoney();
     //采集历史消费流水
     procedure CollectConsumeSer();
     //采集现金充值流水
     procedure CollectAddMoneySer();
     //设备卡分组设置
     procedure setGroup();
     //累计消费限额
     procedure setHisSumMoney();
     //餐次信息设置
     //procedure setCCInfo();
     //门禁常开设置
     procedure setGateOpen;
     //费率设置
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
  WorkView.FieldByName('设备名称').Data.SetString('');
  WorkView.FieldByName('上级设备').Data.SetString('');
  WorkView.FieldByName('设备物理编号').Data.SetString('');
  WorkView.FieldByName('子系统').DefaultValue := 0;
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
  tmpdataset := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
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
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);//设备编号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);//设备物理编号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString); //设备名称
    tmpItem.SubItems.Add(GetIdObjectName(-31,tmpdataset.fieldbyname('damt6').AsString));//上级设备
    tmpItem.SubItems.Add(GetIdObjectName(47,tmpdataset.fieldbyname('sbank_code').AsString));//设备机型
    tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdataset.fieldbyname('lserial0').AsString));//所属子系统
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
      pnl4.Caption := '收费类别';
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
    //最大消费金额
    6 :
    begin
      setInsValue;
      dxInsRowMoney.Visible := True;
      dxInsRowMoney.Caption := '大额消费限额(元)';
      dxInsRowEnd.Visible := False;
      dxInsRowBegin.Visible := False;
      dxInsRowGate.Visible := False;
      dxInsRowFeeType.Visible := False;
      //cbxSelectAll.Visible := False;
      setInsBordSingle;
      hideCardType;
    end;
    //历史消费流水采集，历史充值金额流水采集
    7,8:
    begin
      setInsValue;
      dxInsRowMoney.Visible := False;
      dxInsRowBegin.Visible := True;
      dxInsRowEnd.Visible := True;
      dxInsRowBegin.Caption := '起始流水号';
      dxInsRowEnd.Caption := '结束流水号';
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
      dxInsRowMoney.Caption := '累计消费限额(元)';
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
      dxInsRowGate.Caption := '门禁状态';
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
      dxInsRowFeeType.Caption := '水控费率';
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
  过程名:    TfaqhsetEquipPara2.upEquipClock下传设备时钟
  作者:      hanjiwei
  日期:      2006.07.05
  参数:      无
  返回值:    无
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
      WVDownEquipClock.FieldByName('终端设备ID').Data.SetString(EquID);
      WVDownEquipClock.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      //WVDownEquipClock.FieldByName('下传时钟').Data.SetString(DownDateTime);
      try
        WVRDownEquipClock.SendCommand;
        if WVDownEquipClock.FieldByName('返回码').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVDownEquipClock.FieldByName('返回信息').Data.AsString);
        end else
        begin
          DownDateTime:=WVDownEquipClock.FieldByName('下传时钟').Data.AsString;
          AddListViewItem(EquName, WVDownEquipClock.FieldByName('错误信息').Data.AsString+' '+DownDateTime);
        end;
      except
        AddListViewItem(EquName, '前后台传送失败');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhsetEquipPara2.upEquipClock上传设备时钟
  作者:      hanjiwei
  日期:      2006.07.05
  参数:      无
  返回值:    无
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
      WVUpEquipClock.FieldByName('终端设备ID').Data.SetString(EquID);
      WVUpEquipClock.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      try
        WVRUpEquipClock.SendCommand;
        UpDateTime := WVUpEquipClock.FieldByName('上传时钟').Data.AsString;
        OutMessage := WVUpEquipClock.FieldByName('错误信息').Data.AsString;
        AddListViewItem(EquName, OutMessage + ' ' + UpDateTime);
      except
        AddListViewItem(EquName, '前后台传送失败');
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
  过程名:    TfaqhsetEquipPara2.upEquipClock强制设备迁出
  作者:      hanjiwei
  日期:      2006.07.05
  参数:      无
  返回值:    无
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
      WVEquipCompellOut.FieldByName('终端设备ID').Data.SetString(EquID);
      WVEquipCompellOut.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      try
        WVREquipCompellOut.SendCommand;
        if WVEquipCompellOut.FieldByName('返回码').Data.AsInteger<>0 then
        begin
          AddListViewItem(EquName,WVEquipCompellOut.FieldByName('返回信息').Data.AsString);
        end else
        begin
          AddListViewItem(EquName,WVEquipCompellOut.FieldByName('错误信息').Data.AsString);
        end;
      except
        AddListViewItem(EquName, '前后台传送失败');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhsetEquipPara2.upEquipClock下传搭伙费比率
  作者:      hanjiwei
  日期:      2006.07.05
  参数:      无
  返回值:    无
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
      WVDownShareMoney.FieldByName('终端设备ID').Data.SetInteger(StrToInt(EquID));
      WVDownShareMoney.FieldByName('设备物理编号').Data.SetString(EquPhyId);
      try
        WVRDownShareMoney.SendCommand;
        if WVDownShareMoney.FieldByName('返回码').Data.AsInteger <> 0 then
          AddListViewItem(EquName, WVDownShareMoney.FieldByName('返回信息').Data.AsString)
        else
          AddListViewItem(EquName, '下载搭伙费成功！');
      except
        AddListViewItem(EquName, '前后台传送失败');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhsetEquipPara2.upEquipClock下传大额消费限额
  作者:      hanjiwei
  日期:      2006.07.05
  参数:      无
  返回值:    无
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
      WVDownMaxMoney.FieldByName('终端设备ID').Data.SetString(EquID);
      WVDownMaxMoney.FieldByName('大额消费限额').Data.SetInteger(Money);
      WVDownMaxMoney.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      try
        WVRDownMaxMoney.SendCommand;
        if WVDownMaxMoney.FieldByName('返回码').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVDownMaxMoney.FieldByName('返回信息').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, WVDownMaxMoney.FieldByName('错误信息').Data.AsString);
        end;
      except
        AddListViewItem(EquName, '前后台传送失败');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhsetEquipPara2.upEquipClock设置累计消费金额
  作者:      hanjiwei
  日期:      2006.07.05
  参数:      无
  返回值:    无
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
      WVSetHisSumMoney.FieldByName('终端设备ID').Data.SetString(EquID);
      WVSetHisSumMoney.FieldByName('累计消费限额').Data.SetInteger(Money);
      WVSetHisSumMoney.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      try
        WVRSetHisSumMoney.SendCommand;
        if WVSetHisSumMoney.FieldByName('返回码').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVSetHisSumMoney.FieldByName('返回信息').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, WVSetHisSumMoney.FieldByName('错误信息').Data.AsString);
        end;
      except
        AddListViewItem(EquName, '前后台传送失败');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhsetEquipPara2.upEquipClock采集历史消费流水
  作者:      hanjiwei
  日期:      2006.07.05
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.CollectConsumeSer;
var
  I:Integer;
  id,EquID,EquName: string;
  beginCode,endCode : Integer;
begin
  if (dxInsRowBegin.Text='')or(dxInsRowEnd.Text='') then
  begin
    ShowMessage('请输入起始流水号和结束流水号！');
    Exit;
  end;
  beginCode := StrToInt(dxInsRowBegin.Text);
  endCode := StrToInt(dxInsRowEnd.Text);
  if beginCode>endCode then
  begin
    ShowMessage('系统提示：开始流水号不能大于结束流水号！');
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
      WVCollectConsumeSer.FieldByName('终端设备ID').Data.SetString(EquID);
      WVCollectConsumeSer.FieldByName('收数起始流水号').Data.SetInteger(beginCode);
      WVCollectConsumeSer.FieldByName('收数结束流水号').Data.SetInteger(endCode);
      WVCollectConsumeSer.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      try
        WVRCollectConsumeSer.SendCommand;
        if WVCollectConsumeSer.FieldByName('返回码').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVCollectConsumeSer.FieldByName('返回信息').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, '采集历史流水成功！');
        end;
      except
        AddListViewItem(EquName, '前后台传送失败');
      end;
    end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhsetEquipPara2.upEquipClock采集现金充值消费流水
  作者:      hanjiwei
  日期:      2006.07.05
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfaqhsetEquipPara2.CollectAddMoneySer;
var
  I:Integer;
  id,EquID,EquName: string;
  beginCode,endCode : Integer;
begin
  if (dxInsRowBegin.Text='')or(dxInsRowEnd.Text='') then
  begin
    ShowMessage('请输入起始流水号和结束流水号！');
    Exit;
  end;
  beginCode := StrToInt(dxInsRowBegin.Text);
  endCode := StrToInt(dxInsRowEnd.Text);
  if beginCode>endCode then
  begin
    ShowMessage('系统提示：开始流水号不能大于结束流水号！');
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
      WVCollectAddMoneySer.FieldByName('终端设备ID').Data.SetString(EquID);
      WVCollectAddMoneySer.FieldByName('收数起始流水号').Data.SetInteger(beginCode);
      WVCollectAddMoneySer.FieldByName('收数结束流水号').Data.SetInteger(endCode);
      WVCollectAddMoneySer.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      try
        WVRCollectAddMoneySer.SendCommand;
        if WVCollectAddMoneySer.FieldByName('返回码').Data.AsInteger<>0 then
        begin
          AddListViewItem(EquName, WVCollectAddMoneySer.FieldByName('返回信息').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, '成功！');
        end;
      except
        AddListViewItem(EquName, '前后台传送失败');
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
  tempDataSet := TDataSet(WorkViewCustomerKindByKey.FieldByName('查询结果集').Data.AsObject);
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
  过程名:    TfaqhsetEquipPara2.setGroup设置卡权限分组
  作者:      hanjiwei
  日期:      2006.07.11
  参数:      无
  返回值:    无
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
        ShowMessage('提示信息：一次只能下一个设备！');
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
      WorkViewEquGroup.FieldByName('设备编号').Data.SetInteger(EquID);
      WorkViewEquGroup.FieldByName('分组权限').Data.SetString(groupStr);
      try
        WVRequestEquGroup.SendCommand;
        if WorkViewEquGroup.FieldByName('返回码').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WorkViewEquGroup.FieldByName('返回信息').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, WorkViewEquGroup.FieldByName('错误信息').Data.AsString);
        end;
      except
        AddListViewItem(EquName, '前后台传送失败');
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
          ShowMessage('提示信息：一次只能下一个设备！');
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
    WorkViewQueryEquByKey.FieldByName('设备标识').Data.SetInteger(equid);
    WVRequestQueryEquByKey.SendCommand;
    tempdataset := TDataSet(WorkViewQueryEquByKey.FieldByName('查询结果集').Data.AsObject);
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
    ShowMessage('提示信息：该功能不能全选设备！');
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
  WVCCQuery.FieldByName('操作标志').Data.setstring('R');
  WVRCCQuery.SendCommand;
  tempDataSet := TDataSet(WVCCQuery.FieldByName('查询结果集').Data.AsObject);
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
  过程名:    TfaqhsetEquipPara2.setCCInfo餐次信息设置
  作者:      hanjiwei
  日期:      2007.08.09
  参数:      无
  返回值:    无
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
      WVCCInfo.FieldByName('设备编号').Data.SetInteger(EquID);
      WVCCInfo.FieldByName('餐次信息').Data.SetString(groupStr);
      try
        WVRCCInfo.SendCommand;
        if WVCCInfo.FieldByName('返回码').Data.AsInteger <> 0 then
        begin
          AddListViewItem(EquName, WVCCInfo.FieldByName('返回信息').Data.AsString);
        end else
        begin
          AddListViewItem(EquName, WVCCInfo.FieldByName('错误信息').Data.AsString);
        end;
      except
        AddListViewItem(EquName, '前后台传送失败');
      end;
    end;
  end;
end;
}
{-------------------------------------------------------------------------------
  过程名:    TfaqhsetEquipPara2.setGateOpen门禁常开设置
  作者:      hanjiwei
  日期:      2007.11.26
  参数:      无
  返回值:    无
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
    ShowMessage('请先选择门禁状态，然后再下传参数！');
    exit;
  end;
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      Id := lvEqu.Items[i].SubItems[0];
      EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      WVGateOpen.FieldByName('终端设备ID').Data.SetString(EquID);
      WVGateOpen.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      WVGateOpen.FieldByName('标志').Data.SetInteger(StrToInt(gateSign));
      try
        WVRGateOpen.SendCommand;
        if WVGateOpen.FieldByName('返回码').Data.AsInteger <> 0 then
          AddListViewItem(EquName, WVGateOpen.FieldByName('返回信息').Data.AsString)
        else
          AddListViewItem(EquName, WVGateOpen.FieldByName('返回信息').Data.AsString);
      except
        AddListViewItem(EquName, '前后台传送失败');
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
  wvDictQ.FieldByName('数据字典条目').Data.SetInteger(-63);
  wvrDictQ.SendCommand;
  tempDataSet := TDataSet(wvDictQ.FieldByName('查询结果集').Data.AsObject);
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
    ShowMessage('请先选择费率类型，然后再下传参数！');
    exit;
  end;
  for I := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
    begin
      Id := lvEqu.Items[i].SubItems[0];
      //EquID := lvEqu.Items[i].SubItems[1];
      EquName := lvEqu.Items[i].SubItems[2];
      //wvSetFeeType.FieldByName('终端设备ID').Data.SetString(EquID);
      wvSetFeeType.FieldByName('设备编号').Data.SetInteger(StrToInt(id));
      wvSetFeeType.FieldByName('标志').Data.SetInteger(StrToInt(feeType));
      try
        wvrSetFeeType.SendCommand;
        if wvSetFeeType.FieldByName('返回码').Data.AsInteger <> 0 then
          AddListViewItem(EquName, wvSetFeeType.FieldByName('返回信息').Data.AsString)
        else
          AddListViewItem(EquName, wvSetFeeType.FieldByName('返回信息').Data.AsString);
      except
        on e:Exception do
        begin
          AddListViewItem(EquName, '前后台传送失败-'+e.Message);
        end;
      end;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('设备参数控制',TfaqhsetEquipPara2);

end.