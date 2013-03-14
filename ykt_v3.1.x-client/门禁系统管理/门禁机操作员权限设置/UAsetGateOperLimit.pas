unit UAsetGateOperLimit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  ComCtrls, RzListVw, Mask, RzLstBox, RzPanel, RzSplit, RzChkLst, Buttons;

type
  TfaqhsetGateOperLimit = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVComboBox1: TWVComboBox;
    MainRequest2: TWVRequest;
    WorkView2: TWorkView;
    chkSelectAll: TRzCheckBox;
    pnl1: TPanel;
    rzszpnl1: TRzSizePanel;
    Panel2: TPanel;
    Label1: TLabel;
    Label6: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label7: TLabel;
    WVEdit1: TWVEdit;
    cbbScode: TWVComboBox;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    WVComboBox5: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnEquQuery: TBitBtn;
    lvGate: TRzListView;
    lst1: TRzCheckList;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    chkReSelect: TRzCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
    procedure btnEquQueryClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure lvGateCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
    procedure chkReSelectClick(Sender: TObject);
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
  faqhsetGateOperLimit: TfaqhsetGateOperLimit;

implementation

uses KsFrameworks,USetParamsTemp,KSDataDictionary, 
     KSClientConsts, gateComm;
     
{$R *.DFM}

procedure TfaqhsetGateOperLimit.Init;
begin
  inherited;
  {
  WorkView.FieldByName('查询.门禁机编号').DefaultValue := 0;
  WorkView.FieldByName('查询.操作员号').DefaultValue := '';
  WorkView.FieldByName('交易类型').DefaultValue := '';
  WorkView.FieldByName('门禁机编号').DefaultValue := 0;
  WorkView.FieldByName('操作员号').DefaultValue := '';
  WorkView.Reset;
  WorkView2.FieldByName('机号').DefaultValue := 0;
  WorkView2.FieldByName('机型代码').DefaultValue := '';
  WorkView2.FieldByName('上级设备物理ID').DefaultValue :='' ;
  WorkView2.FieldByName('设备状态').DefaultValue := 0;
  WorkView2.FieldByName('设备物理型号').DefaultValue := 0;
  WorkView2.FieldByName('所属子系统').DefaultValue := 0;
  WorkView2.FieldByName('设备所在区域').DefaultValue := 0;
  WorkView2.FieldByName('负责人员工号').DefaultValue := '';
  WorkView2.Reset;
  }
  btnEquQuery.caption := '设备查询';
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  fillCheckListBox;
end;

procedure TfaqhsetGateOperLimit.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetGateOperLimit.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhsetGateOperLimit.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('门禁机编号').Data.SetInteger(0);
  addType(operatorNoName,WorkView);
  lvGate.Items.Clear;
end;

procedure TfaqhsetGateOperLimit.btnQueryClick(Sender: TObject);
begin
  queryType(operatorNoName,WorkView);
  inherited;

end;

procedure TfaqhsetGateOperLimit.btnDeleteClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该条记录吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView.FieldByName('操作员号').Data.SetString(Grid.DataSource.DataSet.fieldbyname('scust_limit').AsString);
  WorkView.FieldByName('门禁机编号').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WorkView.FieldByName('交易类型').Data.SetString('D');
  DeleteRequest.SendCommand;
  btnQuery.Click;
end;

procedure TfaqhsetGateOperLimit.btnOKClick(Sender: TObject);
var
  i ,k: Integer;
  groupId:string;
  equNO:string;
begin
  if checkListViewSelect(lvGate)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要分配权限的门禁机！');
    exit;
  end;
  {
  if (Trim(cbbOperCode.Text)='')or(Trim(cbbOperCode.Text)='-') then
  begin
    ShowMessage('请选择要分配的操作员！');
    cbbOperCode.SetFocus;
    Exit;
  end;
  }
  if checkListSelcet(lst1)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要分配的操作员！');
    Exit;
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
          WorkView.FieldByName('操作员号').Data.SetString(groupId);
          WorkView.FieldByName('门禁机编号').Data.SetInteger(StrToInt(equNO));
          WorkView.FieldByName('交易类型').Data.SetString('A');

          AddRequest.SendCommand;
        end;
      end;
    end;
  end;
  //inherited;
  Status := ssBrowse;
  noSelect;
  btnQuery.Click;
end;

procedure TfaqhsetGateOperLimit.addGateToLV;
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
  sCode:string;
begin
  lvGate.Items.Clear;
  sCode := Copy(cbbScode.Text,1,Pos('-',cbbScode.Text)-1);
  WorkView2.FieldByName('机型代码').Data.SetString(sCode);
  MainRequest2.SendCommand;
  if WorkView2.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView2.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView2.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvGate.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //设备标识
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString);                            //设备名称
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);                          //设备编号
    tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdataset.fieldbyname('lserial0').AsString));       //所属子系统
    tmpItem.SubItems.Add(GetIdObjectName(-28,tmpdataset.fieldbyname('lserial1').AsString));       //所在区域
    tmpdataset.Next;
  end;
end;

procedure TfaqhsetGateOperLimit.noSelect;
var
  i:Integer;
begin
  for i := 0 to lvGate.Items.Count - 1 do
  begin
    lvGate.Items[i].Checked := False;
  end;
  chkSelectAll.Checked:=false;
end;

procedure TfaqhsetGateOperLimit.chkSelectAllClick(Sender: TObject);
begin
  if listViewSelectAll(lvGate,chkSelectAll)=False then
     Context.GetDialogSystem.ShowMessage('请先查询要分配的设备！');
  //chkReSelect.Checked := False;
end;

procedure TfaqhsetGateOperLimit.btnEquQueryClick(Sender: TObject);
begin
  addGateToLV;
end;

procedure TfaqhsetGateOperLimit.GridDblClick(Sender: TObject);
begin
  //inherited;
end;

procedure TfaqhsetGateOperLimit.lvGateCustomDrawItem(
  Sender: TCustomListView; Item: TListItem; State: TCustomDrawState;
  var DefaultDraw: Boolean);
begin
  inherited;
  DefaultDraw:=false;
  if Item.Index mod 2 <>0 then
    Sender.Canvas.Brush.Color := clInfoBk
  else
    Sender.Canvas.Brush.Color := $00EBDED0;
  Sender.Canvas.Font.Color := clBlack;
  DefaultDraw:=true;
end;

procedure TfaqhsetGateOperLimit.fillCheckListBox;
var
  tmpDataSet : TDataSet;
  operCode,operName:string;
begin
  WorkView1.FieldByName('操作类别').Data.SetString('R');
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
  begin
    tmpDataSet := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
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

procedure TfaqhsetGateOperLimit.chkReSelectClick(Sender: TObject);
begin
  if listViewReSelect(lvGate)=False then
    Context.GetDialogSystem.ShowMessage('请先查询要分配的设备！');
  //chkSelectAll.Checked := False;
end;

initialization
  TUIStdClassFactory.Create('门禁机操作员权限设置',TfaqhsetGateOperLimit);

end.