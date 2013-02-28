unit UABindingOperCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  ComCtrls, RzListVw, Mask, RzLstBox, RzPanel, RzSplit, RzChkLst, Buttons,CardDll;

type
  TBindingOperCard = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVComboBox1: TWVComboBox;
    chkSelectAll: TRzCheckBox;
    pnl1: TPanel;
    rzszpnl1: TRzSizePanel;
    lst1: TRzCheckList;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    Panel2: TPanel;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVLabel2: TWVLabel;
    Label7: TLabel;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVLabel8: TWVLabel;
    Label6: TLabel;
    Label5: TLabel;
    WVLabel3: TWVLabel;
    edtCustNo: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVEdit8: TWVEdit;
    WVComboBox4: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit4: TWVEdit;
    WVComboBox7: TWVComboBox;
    lvQPubCard: TRzListView;
    btnCardQuery: TBitBtn;
    wvQPubCard: TWorkView;
    wvrQPubCard: TWVRequest;
    cbbErrOperNo: TWVComboBox;
    lbl1: TLabel;
    edtPwd: TWVEdit;
    lbl2: TLabel;
    Label8: TLabel;
    cbbDelOper: TWVComboBox;
    Label9: TLabel;
    edtDelPwd: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure btnCardQueryClick(Sender: TObject);
    procedure lvQPubCardCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
  private

    { Private declarations }
    OperatorNoName:string;
    procedure noSelect;
    procedure fillCheckListBox;

    procedure fillList(wv: TWorkView);
    procedure listViewSelectAll(inListView:TRzListView);
    function checkListViewSelect(inLv:TRzListView): Boolean;
    function checkListSelcet(incheckList:TRzCheckList): Boolean;

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  BindingOperCard: TBindingOperCard;

implementation

uses KsFrameworks,USetParamsTemp,KSDataDictionary, KSClientConsts;
     
{$R *.DFM}

procedure TBindingOperCard.Init;
begin
  inherited;
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  fillCheckListBox;
end;

procedure TBindingOperCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TBindingOperCard.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TBindingOperCard.btnAddClick(Sender: TObject);
var
  i:Integer;
begin
  WorkView.FieldByName('卡号').Data.SetInteger(0);
  WorkView.FieldByName('操作员号').Data.SetString('');
  inherited;
  cbbErrOperNo.ItemIndex := 0;
  edtPwd.Text := '';
  lvQPubCard.Items.Clear;
  for i:=0 to lst1.Items.Count-1 do
  begin
    if lst1.ItemChecked[i] then              
      lst1.ItemChecked[i] := False;
  end;
end;

procedure TBindingOperCard.btnQueryClick(Sender: TObject);
begin
  //queryType(operatorNoName,WorkView);
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;

end;

procedure TBindingOperCard.btnDeleteClick(Sender: TObject);
var
  operCode:string;
  operPwd:string;
begin
  if Application.MessageBox('你确定要删除该条记录吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  operCode := Copy(cbbDelOper.Text,1,Pos('-',cbbDelOper.Text)-1);
  operPwd := encOperPwd(operCode,Trim(edtDelPwd.Text));
  WorkView.FieldByName('操作员号').Data.SetString(Grid.DataSource.DataSet.fieldbyname('sname').AsString);
  WorkView.FieldByName('卡号').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WorkView.FieldByName('交易类型').Data.SetString('D');
  WorkView.FieldByName('授权密码').Data.SetString(operPwd);
  DeleteRequest.SendCommand;
  btnQuery.Click;
end;

procedure TBindingOperCard.btnOKClick(Sender: TObject);
var
  i ,k: Integer;
  groupId:string;
  equNO:string;
  operCode:string;
  operPwd:string;

begin
  if checkListViewSelect(lvQPubCard)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要绑定的卡,每次只能选择一张卡！');
    exit;
  end;
  if checkListSelcet(lst1)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要绑定的操作员，每次只能选择一个操作员！');
    Exit;
  end;

  operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
  operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
  for k := 0 to lst1.Items.Count-1 do
  begin
    if lst1.Itemchecked[k] then
    begin
      groupId := Copy(lst1.Items.Strings[k],1,Pos('-',lst1.Items.Strings[k])-1);
      for i := 0 to lvQPubCard.Items.Count - 1 do
      begin
        if lvQPubCard.Items[i].Checked = True then
        begin
          equNO:=lvQPubCard.Items[i].SubItems[3];
          WorkView.SynchronizeCtrlsToFields;
          WorkView.FieldByName('操作员号').Data.SetString(groupId);
          WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(equNO));
          WorkView.FieldByName('交易类型').Data.SetString('A');
          WorkView.FieldByName('授权密码').Data.SetString(operPwd);

          AddRequest.SendCommand;
        end;
      end;
    end;
  end;
  edtPwd.Text := '';
  WorkView.FieldByName('操作员号').Data.SetString('');
  //inherited;
  Status := ssBrowse;
  noSelect;
  btnQuery.Click;
end;

procedure TBindingOperCard.noSelect;
var
  i:Integer;
begin
  for i := 0 to lvQPubCard.Items.Count - 1 do
  begin
    lvQPubCard.Items[i].Checked := False;
  end;
  chkSelectAll.Checked:=false;
end;

procedure TBindingOperCard.chkSelectAllClick(Sender: TObject);
begin

  listViewSelectAll(lvQPubCard);
     //Context.GetDialogSystem.ShowMessage('请先查询要绑定！');
  //chkReSelect.Checked := False;
end;

procedure TBindingOperCard.GridDblClick(Sender: TObject);
begin
  //inherited;
end;

procedure TBindingOperCard.fillCheckListBox;
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

procedure TBindingOperCard.btnCardQueryClick(Sender: TObject);
begin
  if trim(edtCustNo.Text) = '' then
  begin
    wvQPubCard.FieldByName('客户号').Data.SetInteger(0);
  end;
  wvQPubCard.FieldByName('钱包号').Data.SetInteger(1);
  lvQPubCard.items.clear;
  wvrQPubCard.SendCommand;
  fillList(wvQPubCard);
end;

procedure TBindingOperCard.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvQPubCard.Items.Add;
    tmpItem.Caption := GetIdObjectName(-27,tmpdataset.fieldbyname('sbranch_code0').AsString);     //所属区域
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);                               //客户号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString);                              //学工号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);                           //姓名
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);                               //卡号
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lsafe_level2').AsString));   //客户类别
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol5').AsString));          //客户状态
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('vsvarstr0').AsString);                           //部门
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt5').AsString);                               //卡余额
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);                               //帐户余额
    tmpdataset.Next;
  end;
end;

procedure TBindingOperCard.listViewSelectAll(inListView: TRzListView);
var
  i: integer;
begin
  if inListView.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelectAll.Checked = True then
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
end;

function TBindingOperCard.checkListViewSelect(inLv: TRzListView): Boolean;
var
  i,a:Integer;
begin
  Result := False;
  a := 0;
  for i :=0  to inLv.Items.Count-1 do
  begin
    if inLv.Items[i].Checked = True then
    begin
     // Result := True;
      Inc(a);
      //Exit;
    end;
  end;
  if a=1 then
    Result := True;
end;

function TBindingOperCard.checkListSelcet(incheckList: TRzCheckList): Boolean;
var
  i,a:Integer;
begin
  Result := False;
  a := 0;
  for i := 0 to incheckList.Items.Count-1 do
  begin
    if incheckList.ItemChecked[i] then
    begin
      //Result := True;
      //Exit;
      Inc(a);
    end;
  end;
  if a=1 then
    Result := True;
end;

procedure TBindingOperCard.lvQPubCardCustomDrawItem(
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

initialization
  TUIStdClassFactory.Create('充值操作员绑定卡',TBindingOperCard);

end.