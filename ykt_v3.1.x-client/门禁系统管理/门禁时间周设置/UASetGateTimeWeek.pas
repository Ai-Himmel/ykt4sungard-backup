unit UASetGateTimeWeek;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, ComCtrls,
  RzListVw, RzPanel, RzSplit, RzButton, RzRadChk, Buttons;

type
  TfaqhSetGateTimeWeek = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    RzSizePanel1: TRzSizePanel;
    RzPanel1: TRzPanel;
    rzpnl1: TRzPanel;
    lvGate: TRzListView;
    Label7: TLabel;
    WVEdit3: TWVEdit;
    Label12: TLabel;
    WVComboBox7: TWVComboBox;
    WVComboBox5: TWVComboBox;
    Label11: TLabel;
    Label18: TLabel;
    WVEdit6: TWVEdit;
    WVComboBox8: TWVComboBox;
    Label15: TLabel;
    Label16: TLabel;
    Label14: TLabel;
    WVComboBox9: TWVComboBox;
    cbbScode: TWVComboBox;
    rzpnl2: TRzPanel;
    Label19: TLabel;
    WVEdit8: TWVEdit;
    btnWeekQuery: TBitBtn;
    lvWeek: TRzListView;
    btnDevquery: TBitBtn;
    WVRequest5: TWVRequest;
    WorkView5: TWorkView;
    chkGateUnAllot: TRzCheckBox;
    chkDevSelectAll: TRzCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnWeekQueryClick(Sender: TObject);
    procedure btnDevqueryClick(Sender: TObject);
    procedure chkGateUnAllotClick(Sender: TObject);
    procedure chkDevSelectAllClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    function findIndexLV(inLv:TRzListView;iId:string): Boolean;
    function listViewSelectAll(inListView:TRzListView;chkBox:TRzCheckBox):Boolean;
    function selectItem(inListView:TRzListView):Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetGateTimeWeek: TfaqhSetGateTimeWeek;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhSetGateTimeWeek.Init;
begin
  inherited;
  {
  WorkView1.FieldByName('设备名称').DefaultValue := '';
  WorkView1.FieldByName('三九设备注册号').DefaultValue := '';
  WorkView1.FieldByName('设备物理ID').DefaultValue := '';
  WorkView1.FieldByName('机号').DefaultValue := 0;
  WorkView1.FieldByName('机型代码').DefaultValue := '';
  WorkView1.FieldByName('上级设备物理ID').DefaultValue :='' ;
  WorkView1.FieldByName('设备状态').DefaultValue := 0;
  WorkView1.FieldByName('设备物理型号').DefaultValue := 0;
  WorkView1.FieldByName('所属子系统').DefaultValue := 0;
  WorkView1.FieldByName('设备所在区域').DefaultValue := 0;
  WorkView1.FieldByName('负责人员工号').DefaultValue := '';
  WorkView1.Reset;
  WorkView5.FieldByName('查询.时间段组编号').DefaultValue := 0;
  WorkView5.FieldByName('查询.周一组编号').DefaultValue := 0;
  WorkView5.FieldByName('查询.周二组编号').DefaultValue := 0;
  WorkView5.FieldByName('查询.周三组编号').DefaultValue := 0;
  WorkView5.FieldByName('查询.周四组编号').DefaultValue := 0;
  WorkView5.FieldByName('查询.周五组编号').DefaultValue := 0;
  WorkView5.FieldByName('查询.周六组编号').DefaultValue := 0;
  WorkView5.FieldByName('查询.周日组编号').DefaultValue := 0;
  WorkView5.FieldByName('时间段组编号').DefaultValue := 0;
  WorkView5.FieldByName('周一组编号').DefaultValue := 0;
  WorkView5.FieldByName('周二组编号').DefaultValue := 0;
  WorkView5.FieldByName('周三组编号').DefaultValue := 0;
  WorkView5.FieldByName('周四组编号').DefaultValue := 0;
  WorkView5.FieldByName('周五组编号').DefaultValue := 0;
  WorkView5.FieldByName('周六组编号').DefaultValue := 0;
  WorkView5.FieldByName('周日组编号').DefaultValue := 0;
  WorkView5.Reset;
  }
  btnDevquery.Caption := '设备查询';
  btnWeekQuery.Caption := '周查询';
  btnQuery.Caption := '设 置';
end;

procedure TfaqhSetGateTimeWeek.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhSetGateTimeWeek.btnWeekQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  lvWeek.Items.Clear;
  WorkView5.FieldByName('交易类型').Data.SetString('R');
  WVRequest5.SendCommand;
  if WorkView5.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView5.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView5.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvWeek.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //设备标识
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //设备名称
    tmpdataset.Next;
  end;
end;

procedure TfaqhSetGateTimeWeek.btnDevqueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
  //sCode:string;
begin
  lvGate.Items.Clear;
  //sCode := Copy(cbbScode.Text,1,Pos('-',cbbScode.Text)-1);
  //WorkView2.FieldByName('机型代码').Data.SetString(sCode);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView1.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if findIndexLV(lvGate,tmpdataset.fieldbyname('lvol0').asstring)=True then
    begin
      tmpDataSet.Next;
      Continue;
    end;
    tmpItem := lvGate.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //设备标识
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString);                            //设备名称
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt6').AsString);                          //设备编号
    tmpItem.SubItems.Add(GetIdObjectName(-31,tmpdataset.fieldbyname('damt6').AsString));                          //设备编号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sbank_code').AsString);                          //设备编号
    tmpItem.SubItems.Add(GetIdObjectName(47,tmpdataset.fieldbyname('lserial1').AsString));       //所在区域
    tmpdataset.Next;
  end;
end;

function TfaqhSetGateTimeWeek.findIndexLV(inLv: TRzListView;iId: string): Boolean;
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

procedure TfaqhSetGateTimeWeek.chkGateUnAllotClick(Sender: TObject);
begin
  //inherited;
  if listViewSelectAll(lvWeek,chkGateUnAllot)=False then
    Exit;

end;

function TfaqhSetGateTimeWeek.listViewSelectAll(inListView: TRzListView;
  chkBox: TRzCheckBox): Boolean;
var
  i: integer;
begin
  //Result := False;
  if inListView.Items.Count = 0 then
  begin
    Result := False;
    Exit;
  end;
  if chkBox.Checked = True then
  begin
    for i := 0 to inListView.Items.Count - 1 do
    begin
      inListView.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to inListView.Items.Count - 1 do
    begin
      inListView.Items[i].Checked := False;
    end;
  end;
  Result := True;

end;

procedure TfaqhSetGateTimeWeek.chkDevSelectAllClick(Sender: TObject);
begin
  if listViewSelectAll(lvGate,chkDevSelectAll)=False then
    Exit;
end;

procedure TfaqhSetGateTimeWeek.btnQueryClick(Sender: TObject);
var
  i,k:Integer;
  errList:TStringList;
  weekId,devId:string;
begin
  //判断是否有选择的设备和时间周
  if selectItem(lvWeek)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要设置的时间周！');
    Exit;
  end;
  if selectItem(lvGate)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要设置的门禁设备！');
    Exit;
  end;
  if Application.MessageBox('你确定要设置所选择的门禁时间周吗？',PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  errList := nil;
  WorkView.FieldByName('操作标志').Data.SetString('A');
  try
    errList := TStringList.Create;
    for i := 0 to lvWeek.Items.Count-1 do
    begin
      if lvWeek.Items[i].Checked then
      begin
        weekId := lvWeek.Items[i].Caption;
        WorkView.FieldByName('时间周编号').Data.SetInteger(StrToInt(weekId));
        for k := 0 to lvGate.Items.Count-1 do
        begin
          if lvGate.Items[k].Checked then
          begin
            devId := lvGate.Items[k].Caption;
            WorkView.FieldByName('控制器编号').Data.SetInteger(StrToInt(lvGate.Items[k].SubItems[1]));
            WorkView.FieldByName('设备编号').Data.SetInteger(StrToInt(devId));
            WorkView.FieldByName('机型代码').Data.SetString((lvGate.Items[k].SubItems[3]));
            try
              MainRequest.SendCommand;
            except
              on e:Exception do
              begin
                errList.Add('设备编号-'+devid+',时间周编号-'+weekid+'设置失败，原因-'+e.Message);
              end;
            end;
          end;
        end;
      end;
    end;
    if errList.Count>0 then
    begin
      errList.SaveToFile('c:\门禁时间周设置失败列表.txt');
      Context.GetDialogSystem.ShowMessage('门禁时间周设置完成,设置失败信息保存在[c:\门禁时间周设置失败列表.txt]');
    end;
    Context.GetDialogSystem.ShowMessage('门禁时间周设置完成！');
  finally
    errList.Free;
  end;
end;

function TfaqhSetGateTimeWeek.selectItem(inListView: TRzListView): Boolean;
var
  i:Integer;
begin
  for i:= 0 to inListView.Items.Count-1 do
  begin
    if inListView.Items[i].Checked then
    begin
      Result := True;
      Exit;
    end;
  end;
  Result := False;
end;

initialization
  TUIStdClassFactory.Create('门禁时间周设置',TfaqhSetGateTimeWeek);

end.