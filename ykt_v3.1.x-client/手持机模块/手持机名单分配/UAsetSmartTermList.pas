unit UAsetSmartTermList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, ComCtrls,
  RzListVw, RzButton, RzRadChk, RzPanel, Buttons,smartterminterface;

type
  TfaqhsetSmartTermList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    rb1: TRzGroupBox;
    lvUnAllot: TRzListView;
    rb2: TRzGroupBox;
    lvAllot: TRzListView;
    btnAdd: TSpeedButton;
    btnDelete: TSpeedButton;
    pnl1: TPanel;
    Label11: TLabel;
    cbbDept: TWVComboBox;
    Label6: TLabel;
    cbbSpec: TWVComboBox;
    Label1: TLabel;
    cbbCustType: TWVComboBox;
    cbbCardType: TWVComboBox;
    Label10: TLabel;
    lbl2: TLabel;
    cbbDeviceId: TWVComboBox;
    Label9: TLabel;
    edtCardNo: TWVEdit;
    edtCustNo: TWVEdit;
    Label7: TLabel;
    Label3: TLabel;
    edtName: TWVEdit;
    edtNo: TWVEdit;
    Label5: TLabel;
    btnUnQuery: TSpeedButton;
    pnl2: TPanel;
    Label2: TLabel;
    cbbArea: TWVComboBox;
    Label8: TLabel;
    cbbgroup: TWVComboBox;
    cbbCust: TWVComboBox;
    Label12: TLabel;
    Label13: TLabel;
    cbbStatus: TWVComboBox;
    cbbStat: TWVComboBox;
    Label14: TLabel;
    Label15: TLabel;
    WVEdit4: TWVEdit;
    WVEdit1: TWVEdit;
    Label16: TLabel;
    Label17: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    Label18: TLabel;
    btnAllQuery: TSpeedButton;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVRequest3: TWVRequest;
    WorkView3: TWorkView;
    WVRequest4: TWVRequest;
    WorkView4: TWorkView;
    chkSelectAll: TRzCheckBox;
    chkDelSelectAll: TRzCheckBox;
    procedure chkSelectAllClick(Sender: TObject);
    procedure btnUnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnAllQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure lvUnAllotCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
    procedure cbbgroupChange(Sender: TObject);
    procedure chkDelSelectAllClick(Sender: TObject);
  private

    { Private declarations }
    tmpdataset:TDataSet;
    tmpDevice : string;
    selectDevice:string;
    procedure selectList;
    procedure delSelectList;
    function ShowTermError:String ;
    function checkIfSelect(listview:TRzListView): Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetSmartTermList: TfaqhsetSmartTermList;

implementation

uses KsFrameworks, KSClientConsts,KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetSmartTermList.Init;
begin
  inherited;
  {
  WorkView.FieldByName('学工号').DefaultValue := '';
  WorkView.FieldByName('客户类别').DefaultValue := 0;
  WorkView.FieldByName('收费类别').DefaultValue := 0;
  WorkView.FieldByName('姓名').DefaultValue := '';
  WorkView.FieldByName('卡号').DefaultValue := 0;
  WorkView.FieldByName('卡类型').DefaultValue := 0;
  WorkView.FieldByName('专业').DefaultValue := '';
  WorkView.FieldByName('客户号').DefaultValue := 0;
  WorkView.FieldByName('所属校区').DefaultValue := 0;

  WorkView1.FieldByName('客户类别').DefaultValue := 0;
  WorkView1.FieldByName('收费类别').DefaultValue := 0;
  WorkView1.FieldByName('姓名').DefaultValue := '';
  WorkView1.FieldByName('卡号').DefaultValue := 0;
  WorkView1.FieldByName('客户号').DefaultValue := 0;
  WorkView1.FieldByName('所属校区').DefaultValue := 0;
  WorkView1.Reset;
  WorkView.Reset;
  }
  cbbStatus.ItemIndex:=1;
  cbbgroup.ItemIndex := 0;
  selectDevice := Copy(cbbgroup.Text,1,Pos('-',cbbgroup.Text)-1);
end;

procedure TfaqhsetSmartTermList.selectList;
var
  i: integer;
begin
  if lvUnAllot.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelectAll.Checked = True then
  begin
    for i := 0 to lvUnAllot.Items.Count - 1 do
    begin
      lvUnAllot.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvUnAllot.Items.Count - 1 do
    begin
      lvUnAllot.Items[i].Checked := False;
    end;
  end;
end;

procedure TfaqhsetSmartTermList.chkSelectAllClick(Sender: TObject);
begin
  selectList;
end;

procedure TfaqhsetSmartTermList.btnUnQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
begin
  if Trim(edtCardNo.Text)='' then
    WorkView.FieldByName('卡号').Data.SetInteger(0);
  if Trim(edtCustNo.Text)='' then
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  if
  (WorkView.FieldByName('学工号').Data.AsString = '') and
  (WorkView.FieldByName('客户类别').Data.AsInteger = 0) and
  (WorkView.FieldByName('姓名').Data.AsString = '')and
  (WorkView.FieldByName('院系').Data.AsString = '')and
  (WorkView.FieldByName('卡号').Data.AsInteger = 0) and
  (WorkView.FieldByName('卡类型').Data.AsInteger = 0) and
  (WorkView.FieldByName('专业').Data.AsString = '')and
  (WorkView.FieldByName('客户号').Data.AsInteger = 0) then
  begin
    ShowMessage('请先输入查询条件，否则查询的速度会很慢！');
    Exit;
  end;

  MainRequest.SendCommand;
  lvUnAllot.Items.Clear;
  tmpdataset := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvUnAllot.Items.Add;                                                           //姓名
    tmpItem.Caption := tmpdataset.fieldbyname('semail').AsString;
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('Lvol0').AsString);                             //卡号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);                        //学工号
    tmpItem.SubItems.Add(GetIdObjectName(18,tmpdataset.fieldbyname('Lvol1').AsString));         //卡类别
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('Lvol2').AsString));        //客户类别
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('Lvol5').AsString));        //收费类别
    tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('sstation0').AsString));    //院系
    tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('sstation1').AsString));    //专业
    tmpdataset.Next;
  end;
  chkSelectAll.Checked:=False;
end;

procedure TfaqhsetSmartTermList.btnAddClick(Sender: TObject);
var
  operatorNoName:string;
  cardNO:string;
  stuemp_no:string;
  i: integer;
  sdevId:string;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    context.GetDialogSystem.ShowMessage('没有要分配的人员名单！');
    Exit;
  end;
  //取操作员号，框架中的方法
  if (Trim(cbbgroup.Text)='')or((Trim(cbbgroup.Text)='-')) then
  begin
    ShowMessage('设备编号不能为空，请输入选择！');
    cbbgroup.SetFocus;
    Exit;
  end;
  if checkIfSelect(lvUnAllot)=False then
  begin
    ShowMessage('请先选择要分配的人员名单！');
    Exit;
  end;
  if Application.MessageBox('你确定要开始分配人员名单吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  if lvUnAllot.Items.Count = 0 then
    Exit;
  for i := 0 to lvUnAllot.Items.Count - 1 do
  begin
    if lvUnAllot.Items[i].Checked = True then
    begin
      cardNo:=lvUnAllot.Items[i].SubItems[0];
      stuemp_no:=lvUnAllot.Items[i].SubItems[1];
      sdevId:=Copy(cbbgroup.Text,1,Pos('-',cbbgroup.Text)-1);
      WorkView2.SynchronizeCtrlsToFields;
      WorkView2.FieldByName('操作员号').Data.SetString(OperatorNoName);
      WorkView2.FieldByName('卡号').Data.SetInteger(StrToInt(cardNO));
      WorkView2.FieldByName('学工号').Data.SetString(stuemp_no);
      WorkView2.FieldByName('设备编号').Data.SetString(selectDevice);
      WVRequest2.SendCommand;
      if WorkView2.FieldByName('返回码').Data.AsInteger<>0 then
      begin
        ShowMessage(WorkView2.fieldbyname('返回信息').Data.AsString);
        Exit;
      end;
    end;
  end;
  btnAllQuery.Click;
  Context.GetDialogSystem.ShowMessage('分配人员名单成功！');
  chkSelectAll.Checked:=False;
  selectList;
end;

procedure TfaqhsetSmartTermList.btnAllQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
begin
  if cbbgroup.Text='' then
  begin
    ShowMessage('请选择设备编号！');
    Exit;
  end;
  
  if Trim(edtCardNo.Text)='' then
    WorkView1.FieldByName('卡号').Data.SetInteger(0);
  if Trim(edtCustNo.Text)='' then
    WorkView1.FieldByName('客户号').Data.SetInteger(0);
  if Trim(cbbCust.Text)='' then
    WorkView1.FieldByName('客户类别').Data.SetInteger(0);
  WorkView1.FieldByName('收费类别').Data.SetInteger(0);
  if Trim(cbbArea.Text)='' then
    WorkView1.FieldByName('所属校区').Data.SetInteger(0);
  WorkView1.FieldByName('设备编号').Data.SetString(selectDevice);
  WVRequest1.SendCommand;
  lvAllot.Items.Clear;
  tmpdataset := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvAllot.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('semail').AsString;                               //姓名
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('Lvol1').AsString);                             //卡号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);                        //学工号
    tmpItem.SubItems.Add(GetIdObjectName(67,tmpdataset.fieldbyname('sstatus0').AsString));      //增删状态                    //批次号
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('Lvol3').AsString));        //客户类别
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('Lvol4').AsString));        //收费类别
    tmpItem.SubItems.Add(GetIdObjectName(-27,tmpdataset.fieldbyname('lvol5').AsString));        //校区
    tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('sstation0').AsString));    //院系
    tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('sstation1').AsString));    //专业
    tmpdataset.Next;
  end;
  chkDelSelectAll.Checked:=False;
end;

procedure TfaqhsetSmartTermList.btnDeleteClick(Sender: TObject);
var
  i:Integer;
  cardNo:Integer;
  operatorNoName:string;
  equID:string;
begin
  if WorkView1.FieldByName('查询结果集').Data.IsEmpty then
  begin
    context.GetDialogSystem.ShowMessage('没有要删除的人员名单！');
    Exit;
  end;
  equID := Copy(cbbgroup.Text,1,Pos('-',cbbgroup.Text)-1);
  if length(equid)<2 then
  begin
    showmessage('请先选择要删除名单的设备！');
    exit;
  end;
  if checkIfSelect(lvAllot)=False then
  begin
    ShowMessage('请先选择要删除的人员名单！');
    Exit;
  end;
  if Application.MessageBox('你确定要删除选定的人员名单吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  for i := 0 to lvAllot.Items.Count - 1 do
  begin
    if lvAllot.Items[i].Checked = True then
    begin
      OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
      cardNo:=StrToInt(lvAllot.Items[i].SubItems[0]);
      WorkView3.FieldByName('操作员号').Data.SetString(OperatorNoName);
      WorkView3.FieldByName('卡号').Data.SetInteger(cardno);
      WorkView3.FieldByName('设备编号').Data.SetString(equID);
      WVRequest3.SendCommand;
      if WorkView3.FieldByName('返回码').Data.AsInteger<>0 then
      begin
        ShowMessage(WorkView3.fieldbyname('返回信息').Data.AsString);
        Exit;
      end;
    end;
  end;
  btnAllQuery.Click;
  Context.GetDialogSystem.ShowMessage('人员名单删除成功！');
  chkDelSelectAll.Checked:=False;
end;

procedure TfaqhsetSmartTermList.btnQueryClick(Sender: TObject);
var
  i:integer;
  cardNo:integer;
  currTime : String;
  TermInfo : SMART_TERMINAL_T;
begin
  ZeroMemory(@TermInfo,SizeOf(TermInfo));
  if MBLReadTermInfo(@TermInfo) <> 0 then
  begin
    showmessage('请先连接手持机读取手持机编号，然后再分配！');
    Exit;
  end;
  Hex2Str(TermInfo.phyid,SizeOf(TermInfo.phyid),tmpDevice);

  if selectDevice<>tmpDevice then
  begin
    ShowMessage('你查询出的结果和你要下传的设备不相配！');
    Exit;
  end;
  for i := 0 to lvAllot.Items.Count - 1 do
  begin
    currTime := formatdatetime('yymmddhhmmss',now());
    if lvAllot.Items[i].Checked then
    begin
      cardNo := strtoint(lvAllot.items[i].SubItems[0]);
      if Trim(lvAllot.items[i].SubItems[2])='正常' then
      begin
        if MBLSetWhiteCardList(cardNo,pchar(currTime),1)<>0 then
        begin
          showmessage('卡号为：['+inttostr(cardNo)+']名单上传失败，请重新上传--'+ShowTermError);
          Continue;
        end;
      end
      else if  Trim(lvAllot.items[i].SubItems[2])='删除' then
      begin
        if MBLSetWhiteCardList(cardNo,pchar(currTime),0)<>0 then
        begin
          showmessage('卡号为：['+inttostr(cardNo)+']名单删除失败，请重新删除--'+ShowTermError);
          Continue;
        end;
      end
      else
      begin
        ShowMessage('卡号为：'+inttostr(cardNo)+'人员的状态不正常，将跳过该人员名单下载');
        Continue;
      end;
      WorkView4.FieldByName('设备号').Data.SetString(selectDevice);
      WorkView4.FieldByName('卡号').Data.SetInteger(cardNo);
      WVRequest4.SendCommand;
      sleep(2000);
    end;
  end;
  showmessage('下发手持机人员名单成功！');
end;

function TfaqhsetSmartTermList.ShowTermError: String;
var
  msgbuf : array[0..512] of char;
begin
  if MBLGetErrno <> 0 then
  begin
    ZeroMemory(@msgbuf,SizeOf(msgbuf));
    MBLGetErrMsg(msgbuf);
    result := msgbuf;
  end;
end;

procedure TfaqhsetSmartTermList.lvUnAllotCustomDrawItem(
  Sender: TCustomListView; Item: TListItem; State: TCustomDrawState;
  var DefaultDraw: Boolean);
begin
  {
  inherited;
  DefaultDraw:=false;
  if Item.Index mod 2 <>0 then
    Sender.Canvas.Brush.Color := clInfoBk
  else
    Sender.Canvas.Brush.Color := $00EBDED0;
  Sender.Canvas.Font.Color := clBlack;
  DefaultDraw:=true;
  }
end;

procedure TfaqhsetSmartTermList.cbbgroupChange(Sender: TObject);
begin
  selectDevice := Copy(cbbgroup.Text,1,Pos('-',cbbgroup.Text)-1);
  btnAllQuery.Click;
end;

procedure TfaqhsetSmartTermList.delSelectList;
var
  i: integer;
begin
  if lvAllot.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkDelSelectAll.Checked = True then
  begin
    for i := 0 to lvAllot.Items.Count - 1 do
    begin
      lvAllot.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvAllot.Items.Count - 1 do
    begin
      lvAllot.Items[i].Checked := False;
    end;
  end;
end;

procedure TfaqhsetSmartTermList.chkDelSelectAllClick(Sender: TObject);
begin
  inherited;
  delSelectList;
end;

function TfaqhsetSmartTermList.checkIfSelect(listview: TRzListView): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to listview.Items.Count - 1 do
  begin
    if listview.Items[i].Checked = True then
    begin
      Result := True;
      Exit;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('手持机名单分配',TfaqhsetSmartTermList);

end.