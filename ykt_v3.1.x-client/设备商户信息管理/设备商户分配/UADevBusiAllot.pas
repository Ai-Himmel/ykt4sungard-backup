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
  lblBusiName.Caption := '请选择商户';
  WorkView1.FieldByName('使用结束时间').Data.SetString('235959');
  WorkView1.FieldByName('启用日期').Data.SetString(FormatDateTime('yyyymmdd',Date));
  WorkView1.FieldByName('停用日期').Data.SetString('99991231');
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
  
  tmpdata := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  tmpdata.First;
  while not tmpdata.eof do
  begin
    tmpItem := lvDev.Items.Add;
    //所属区域
    tmpItem.Caption := GetIdObjectName(-28,tmpdata.fieldbyname('lserial1').AsString);
    //设备标示
    tmpItem.SubItems.Add(tmpdata.fieldbyname('lvol0').AsString);
    //设备名称
    tmpItem.SubItems.Add(tmpdata.fieldbyname('scert_no').AsString);
    //物理编号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sphone3').AsString);
    //机型代码
    tmpItem.SubItems.Add(GetIdObjectName(47,tmpdata.fieldbyname('sbank_code').AsString));
    //所属子系统
    tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdata.fieldbyname('lserial0').AsString));
    //设备用途
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
    WorkView2.FieldByName('商户标识').Data.SetInteger(0);
    try
      QueryRequest2.SendCommand;
      HasDataSet:=1;
    finally
      CloseWaiting;
    end;
    if HasDataSet=0 then
    begin
       Context.GetDialogSystem.ShowMessage('商户信息查询出错，请重新执行该操作！');
       Exit;
    end;
    DataSet:=(WorkView2.FieldByName('查询结果集').Data.AsObject) as TDataSet;
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
    lblBusiName.Caption := '商户：'+gbusiName;
    //pnlAllot.Caption := '商户<'+gbusiname+'>已分配设备';
  except
  end;
  //查询已经分配过的设备列表
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
    Context.GetDialogSystem.ShowMessage('请先选择要分配的设备！');
    Exit;
  end;
  if ifSelectBusi=1 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要分配设备的商户！');
    Exit;
  end;
  if checkDateAndTime=1 then
    Exit;
  if Application.MessageBox('你确定要给该商户分配选择的设备吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  errList := nil;
  try
    errList := TStringList.Create;
    for i := 0 to lvDev.Items.Count-1 do
    begin
      if lvDev.Items[i].Checked then
      begin
        devId := lvDev.Items.Item[i].SubItems[0];
        WorkView1.FieldByName('操作标志').Data.SetString('A');
        WorkView1.FieldByName('编号').Data.SetInteger(0);
        WorkView1.FieldByName('设备标识').Data.SetInteger(StrToInt(devId));
        WorkView1.FieldByName('商户标识').Data.SetInteger(gbusiId);
        AddRequest.SendCommand;
        if WorkView1.FieldByName('返回码').Data.AsInteger<>0 then
        begin
          errList.Add('设备标识为:'+devId+'的设备分配失败，错误码：'+WorkView1.FieldByName('返回码').Data.AsString+',错误信息：'+WorkView1.FieldByName('返回信息').Data.AsString);
        end;
        Sleep(50);
      end;
    end;
    clearAllotDev(lvDev);
    if errList.Count>0 then
    begin
      errList.SaveToFile('..\bin\logs\商户设备分配失败列表'+formatdatetime('yyyymmddhhmmss',Now)+'.txt');
      Context.GetDialogSystem.ShowMessage('商户设备分配完成,共有失败信息'+inttostr(errlist.Count)+'条，存在安装目录\logs下');
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage('商户设备分配完成！');
    end;
  finally
    errList.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhDevBusiAllot.ifSelectDev是否选择要操作的设备
  作者:      hanjiwei
  日期:      2008.12.17
  参数:      无
  返回值:    Integer，0正常，1不正常
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
    Context.GetDialogSystem.ShowMessage('请先选择要修改的设备！');
    Exit;
  end;
  if checkDateAndTime=1 then
    Exit;
  if Application.MessageBox('你确定要修改选择的设备的参数吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  for i := 0 to lvAllotDev.Items.Count-1 do
  begin
    if lvAllotDev.Items[i].Checked then
    begin
      busiDevId := lvAllotDev.Items.Item[i].SubItems[0];
      WorkView1.FieldByName('操作标志').Data.SetString('U');
      WorkView1.FieldByName('编号').Data.SetInteger(StrToInt(busiDevId));
      WorkView1.FieldByName('设备标识').Data.SetInteger(0);
      WorkView1.FieldByName('商户标识').Data.SetInteger(0);
      AddRequest.SendCommand;
      Sleep(50);
    end;
  end;
  clearAllotDev(lvAllotDev);
  //Context.GetDialogSystem.ShowMessage('商户设备修改完成！');
  if Application.MessageBox('选择设备修改完成，你要刷新显示结果吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
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
    Context.GetDialogSystem.ShowMessage('请先选择要删除的设备！');
    Exit;
  end;
  if Application.MessageBox('你确定要删除选择的设备吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  for i := 0 to lvAllotDev.Items.Count-1 do
  begin
    if lvAllotDev.Items[i].Checked then
    begin
      busiDevId := lvAllotDev.Items.Item[i].SubItems[0];
      WorkView1.FieldByName('操作标志').Data.SetString('D');
      WorkView1.FieldByName('编号').Data.SetInteger(StrToInt(busiDevId));
      WorkView1.FieldByName('设备标识').Data.SetInteger(0);
      WorkView1.FieldByName('商户标识').Data.SetInteger(0);
      AddRequest.SendCommand;
      Sleep(50);
    end;
  end;
  clearAllotDev(lvAllotDev);
  if Application.MessageBox('选择设备删除完成，你要刷新显示结果吗？',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  lblShowAllot.Click;

end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhDevBusiAllot.checkDateAndTime判断日期和时间格式是否正确
  作者:      hanjiwei
  日期:      2008.12.17
  参数:      无
  返回值:    Integer
-------------------------------------------------------------------------------}
function TfaqhDevBusiAllot.checkDateAndTime: Integer;
begin
  Result := 0;
  if Trim(edtStartDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('启用日期不能为空，请输入！');
    Result := 1;
    Exit;
  end;

  if Trim(edtStopDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('停用日期不能为空，请输入！');
    Result := 1;
    Exit;
  end;

  if Trim(edtEndTime.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('结束时间不能为空，请输入！');
    Result := 1;
    Exit;
  end;
  if (Trim(edtStartDate.Text)<>'') and (CheckInputDateFormat(edtStartDate.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('启用日期输入格式不正确！');
    //edtStartDate.SetFocus;
    Result := 1;
    Exit;
  end;
  if (Trim(edtStopDate.Text)<>'') and (CheckInputDateFormat(edtStopDate.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('停用日期输入格式不正确！');
    //edtStopDate.SetFocus;
    Result := 1;
    Exit;
  end;
  if (Trim(edtEndTime.Text)<>'') and (CheckInputTimeFormat(edtEndTime.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('结束时间输入格式不正确！');
    //edtEndTime.SetFocus;
    Result := 1;
    Exit;
  end;

end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhDevBusiAllot.clearAllotDev清空已经选择的设备
  作者:      hanjiwei
  日期:      2008.12.17
  参数:      lv: TRzListView
  返回值:    无
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
  WorkView3.FieldByName('设备标识').Data.SetInteger(0);
  WorkView3.FieldByName('商户编号').Data.SetInteger(gbusiId);
  WorkView3.FieldByName('使用状态').Data.SetString('1');
  WVRequest1.SendCommand;
  if WorkView3.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView3.FieldByName('查询结果集').Data.AsObject);
  //devCount := tmpData.RecordCount;
  lvAllotDev.Items.Clear;
  tmpdata.First;
  while not tmpdata.eof do
  begin
    Inc(devCount);
    tmpItem := lvAllotDev.Items.Add;
    //所属区域
    tmpItem.Caption := '';//GetIdObjectName(-28,tmpdata.fieldbyname('lserial1').AsString);
    //编号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('lvol0').AsString);
    //设备名称
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sbankname').AsString);
    //商户名称
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sall_name').AsString);
    //开始时间
    tmpItem.SubItems.Add(tmpdata.fieldbyname('stime1').AsString);
    //结束时间
    tmpItem.SubItems.Add(tmpdata.fieldbyname('stime2').AsString);
    //启用日期
    tmpItem.SubItems.Add(tmpdata.fieldbyname('Sdate1').AsString);
    //结束日期
    tmpItem.SubItems.Add(tmpdata.fieldbyname('Sdate2').AsString);
    tmpdata.Next;
  end;
  pnlAllot.Caption := '商户<'+gbusiName+'>已分配设备:'+inttostr(devCount)+'台 ';
end;

initialization
  TUIStdClassFactory.Create('设备商户关系设置',TfaqhDevBusiAllot);

end.