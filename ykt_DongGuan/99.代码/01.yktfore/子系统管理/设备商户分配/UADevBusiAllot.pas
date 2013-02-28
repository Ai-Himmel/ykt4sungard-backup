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
    Context.GetDialogSystem.ShowMessage('请先选择要分配的设备！');
    Exit;
  end;
  }
  if Application.MessageBox('你确定要给该商户分配选择的设备吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  //devId := lvDev.Items.Item[i].SubItems[0];
  WorkView.FieldByName('操作类型').Data.SetString('A');
  WorkView.FieldByName('设备编号').Data.SetString(ssDevid);
  WorkView.FieldByName('商户号').Data.SetInteger(gbusiId);
  WorkView.FieldByName('序列号').Data.SetString(sserialNo);
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  clearAllotDev(lvDev);
  Context.GetDialogSystem.ShowMessage('商户设备分配完成！');
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

procedure TfaqhDevBusiAllot.btnDelClick(Sender: TObject);
var
  i:Integer;
  devId:string;
  busiId:string;
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
      devId := lvAllotDev.Items.Item[i].Caption;
      busiId := lvAllotDev.Items.Item[i].SubItems[2];
      WorkView.FieldByName('操作类型').Data.SetString('D');
      WorkView.FieldByName('设备编号').Data.SetString(devId);
      WorkView.FieldByName('序列号').Data.SetString(lvAllotDev.Items.Item[i].SubItems[1]);
      WorkView.FieldByName('商户号').Data.SetInteger(StrToInt(busiId));
      MainRequest.SendCommand;
      Sleep(50);
    end;
  end;
  clearAllotDev(lvAllotDev);
  if Application.MessageBox('选择设备删除完成，你要刷新显示结果吗？',PChar(Application.Title),mb_yesno+mb_iconquestion)=idno then
    Exit;
  lblShowAllot.Click;

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
  pnlAllot.Caption :='';
  lvAllotDev.Items.Clear;
  //WorkView2.FieldByName('设备编号').Data.SetInteger(0);
  WorkView2.FieldByName('商户号').Data.SetInteger(gbusiId);
  //WorkView3.FieldByName('使用状态').Data.SetString('1');
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView2.FieldByName('查询结果集').Data.AsObject);
  //devCount := tmpData.RecordCount;
  tmpdata.First;
  devCount:=0;
  while not tmpdata.eof do
  begin
    Inc(devCount);
    tmpItem := lvAllotDev.Items.Add;
    //设备编号
    tmpItem.Caption := tmpdata.fieldbyname('scert_no').AsString;
    //设备名称
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sbankname').AsString);
    //设备终端序列号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('scust_auth').AsString);
    //商户编号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('lvol0').AsString);
    //商户名称
    tmpItem.SubItems.Add(tmpdata.fieldbyname('snote').AsString);
    //设备序列号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('semail2').AsString);
    //设备终端号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('semail').AsString);
    //设备型号
    tmpItem.SubItems.Add(GetIdObjectName(216,tmpdata.fieldbyname('lvol2').AsString));
    //设备类型
    tmpItem.SubItems.Add(GetIdObjectName(221,tmpdata.fieldbyname('spost_code').AsString));
    //中心商户号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname').AsString);
    //省商户号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname2').AsString);
    //商户类型
    tmpItem.SubItems.Add(GetIdObjectName(216,tmpdata.fieldbyname('sbranch_code0').AsString));
    tmpdata.Next;
  end;
  pnlAllot.Caption := '商户<'+gbusiName+'>已分配设备:'+inttostr(devCount)+'台 ';
end;

procedure TfaqhDevBusiAllot.btnDevQClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdata:TDataSet;
begin
  WorkView1.FieldByName('操作标志').Data.SetString('R');
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  lvDev.Items.Clear;

  tmpdata := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
  tmpdata.First;
  while not tmpdata.eof do
  begin
    tmpItem := lvDev.Items.Add;
    //地区编码
    tmpItem.Caption := GetIdObjectName(229,tmpdata.fieldbyname('sstock_code').AsString);
    //设备编号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('scert_no').AsString);
    //设备名称
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sbankname').AsString);
    //设备终端号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname').AsString);
    //设备序列号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname2').AsString);
    //设备型号
    tmpItem.SubItems.Add(GetIdObjectName(223,tmpdata.fieldbyname('lvol2').AsString));
    //设备类型
    tmpItem.SubItems.Add(GetIdObjectName(221,tmpdata.fieldbyname('spost_code').AsString));
    //设备用途
    tmpItem.SubItems.Add(GetIdObjectName(222,tmpdata.fieldbyname('lvol4').AsString));
    //设备状态
    tmpItem.SubItems.Add(GetIdObjectName(220,tmpdata.fieldbyname('sstatus0').AsString));
    //启用日期
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
      Context.GetDialogSystem.ShowMessage('错误：'+e.Message);
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
  WorkView3.FieldByName('操作标志').Data.SetString('R');
  try
    QueryRequest.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;

  if WorkView3.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView3.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  

  tmpdata := TDataSet(WorkView3.FieldByName('查询结果集').Data.AsObject);
  tmpdata.First;
  while not tmpdata.eof do
  begin
    tmpItem := lvBusi.Items.Add;
    //商户编号
    tmpItem.Caption := tmpdata.fieldbyname('lvol0').AsString;
    //商户名称
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sall_name').AsString);
    //设备终端序列号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('scust_auth').AsString);
    //省商户编号
    tmpItem.SubItems.Add(GetIdObjectName(221,tmpdata.fieldbyname('sstock_code').AsString));
    //商户类型
    tmpItem.SubItems.Add(GetIdObjectName(239,tmpdata.fieldbyname('scurrency_type').AsString));
    //行业类型
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
    lblBusi.Caption := '当前选择商户-'+gbusiName;
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
    lblDev.Caption := '当前设备-'+lvDev.Items.Item[i].SubItems[1];
  except

  end;

end;

initialization
  TUIStdClassFactory.Create('设备商户绑定',TfaqhDevBusiAllot);

end.