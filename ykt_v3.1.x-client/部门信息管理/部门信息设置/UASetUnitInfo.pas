unit UASetUnitInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,
  UIncrementComboBox, RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs,USMSetTreeParamsTemp_Dept,
  RzTreeVw, Buttons;

type
  TfaqhSetUnitInfo = class(TfaSMSetTreeParamsTemp_Dept)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
	  WVEdit1: TWVEdit;
    edtDeptNO: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVLabel2: TWVLabel;
    WVEdit3: TWVEdit;
    WVLabel4: TWVLabel;
    WVEdit6: TWVEdit;
    WVComboBox3: TWVComboBox;
    Splitter1: TSplitter;
    lbl1: TLabel;
    edtDeptNo11: TWVEdit;
    edtdeptName: TWVEdit;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label3: TLabel;
    WVComboBox1: TWVComboBox;
    Label7: TLabel;
    WVEdit2: TWVEdit;
    Label8: TLabel;
    WVEdit7: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure TreeViewClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnCancelClick(Sender: TObject);
  private
    SFCurrentID:string;
    SFCurrNode:TTreeNode;
    IsFirst:Boolean;
    IsFromFirst:Boolean;
    IsForward:Boolean;
    IsUpperLowercase:Boolean;

    treeSign : Integer;
    procedure SearchDataset(DataSet: TDataSet);

    {刷新树视图结构}
    procedure CreateUnitTree;

    procedure findTree(ss:string);
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetUnitInfo: TfaqhSetUnitInfo;

implementation

uses KsFrameworks, KSDataDictionary, UCMqhUnitInfoImp,KSClientConsts,KSBranchTree;
     
{$R *.DFM}

procedure TfaqhSetUnitInfo.Init;
begin
  inherited;
  btnAdd.Enabled:=False;
  ckAutoSetNewParams.Checked:=True;
  treeSign := 0;
end;

procedure TfaqhSetUnitInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetUnitInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetUnitInfo.btnDeleteClick(Sender: TObject);
begin
  if TreeView.Items.Count=0 then Exit;
  if TreeView.Selected = nil then Exit;
  if TreeView.Selected.Level=0 then
  begin
    Context.GetDialogSystem.ShowMessage('不能删除根节点的信息！');
    Exit;
  end;
  if TreeView.Selected.HasChildren then
  begin
    Context.GetDialogSystem.ShowMessage('请先删除下属所有单位信息！');
    Exit;
  end;
  SFCurrNode := TreeView.Selected;
  SFCurrentID:=TTreeNodeInfoData(TreeView.Selected.Parent.Data).GetID;
  WorkView.FieldByName('上级单位').Data.SetString(SFCurrentID);
  WorkView.SynchronizeCtrlsToFields;
  WorkView.FieldByName('操作类别').Data.SetString('D');
  Status := ssDelete;
  edtDeptNO.ReadOnly:=False;
  treeSign := 0;
end;

procedure TfaqhSetUnitInfo.btnChangeClick(Sender: TObject);
begin
  if TreeView.Selected=nil then
  begin
    Context.GetDialogSystem.ShowWarning('请先选择一个单位节点！');
    exit;
  end;
  if TreeView.Selected.Level=0 then
  begin
    Context.GetDialogSystem.ShowMessage('不能对根区域信息进行修改！');
    Exit;
  end;
  //inherited;
  SFCurrNode := TreeView.Selected;
  SFCurrentID:=TTreeNodeInfoData(TreeView.Selected.Parent.Data).GetID;
  WorkView.FieldByName('上级单位').Data.SetString(SFCurrentID);
  WorkView.SynchronizeCtrlsToFields;
  WorkView.FieldByName('操作类别').Data.SetString('U');
  Status := ssChange;
  WorkView.FieldByName('上级单位').Data.SetString(SFCurrentID);
  edtDeptNO.ReadOnly:=True;
  treeSign := 0;
end;

procedure TfaqhSetUnitInfo.btnAddClick(Sender: TObject);
begin
  if TreeView.Selected=nil then
  begin
    Context.GetDialogSystem.ShowWarning('请先选择一个单位节点！');
    exit;
  end;
  //inherited;
  SFCurrNode := TreeView.Selected;
  if RbtnAddChild.Checked then
  begin
    SFCurrentID:=TTreeNodeInfoData(TreeView.Selected.Data).GetID; //增加下级
  end
  else
  if RBtnAddBrother.Checked then
  begin
    SFCurrentID:=TTreeNodeInfoData(TreeView.Selected.Parent.Data).GetID;//增加同级
  end
  else
  begin
    Exit;
  end;
  WorkView.FieldByName('操作类别').Data.SetString('A');
  WorkView.FieldByName('上级单位').Data.SetString(SFCurrentID);
  WorkView.SynchronizeCtrlsToFields;
  Status := ssAdd;
  edtDeptNO.ReadOnly:=True;
  edtDeptNO.Text:='';
  WVEdit4.Text:='';
  WorkView.FieldByName('上级单位').Data.SetString(SFCurrentID);
  treeSign := 0;
end;

procedure TfaqhSetUnitInfo.CreateUnitTree;
begin
  WorkView1.FieldByName('单位代码').Data.SetString('');
  WVRequest1.SendCommand;
  self.FDataSetFieldID:='scert_no';
  self.FDataSetParentFieldID:='semail2';
  self.FDataSetFieldName:='scusttypes';
  self.FWorkViewFieldID:='单位代码';
  self.FWorkViewFieldName:='单位名称';
  self.FWorkViewParentFieldID:='上级单位';
  self.FDefaultID:=0;
  self.FDataSet:= (WorkView1.FieldByName('查询结果集').Data.AsObject) as TDataSet;
  self.BuildTree;
end;

procedure TfaqhSetUnitInfo.btnQueryClick(Sender: TObject);
var
  ss:string;
begin
  //ShowWaiting(SWaitingQuery);
  TreeView.Enabled:=True;
  if treeSign = 0 then
  begin
    CreateUnitTree;
    treeSign := 9;
  end;
  WorkView.FieldByName('操作类别').Data.SetString('R');
  inherited;
  //CloseWaiting;
  try
  ss := Grid.DataSource.DataSet.fieldbyname('scert_no').AsString;
  findTree(ss);
  except
  end;
end;

procedure TfaqhSetUnitInfo.btnOKClick(Sender: TObject);
begin

  if (self.Status = ssAdd)or (self.Status = ssChange) then
  begin
    {
    if trim(WVEdit2.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('单位代码不能为空！');
      Exit;
    end;
    }
    if trim(WVEdit4.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('部门名称不能为空！');
      Exit;
    end;
  end;

  inherited;
  {
  WVComboBox3.ItemIndex:=0;
  FreeIdObjects(-22);
  WVComboBox3.ItemsDataEntry := '';
  WVComboBox3.ItemsDataEntry := '-22';
  }
  WorkView.FieldByName('操作类别').Data.SetString('R');
  btnQuery.Click;
end;

procedure TfaqhSetUnitInfo.SearchDataset(DataSet: TDataSet);
var
  Field : TField;
  I: Integer;
  SelectNode:string;
begin
  IsFirst:=True;
  IsFromFirst:=True;
  IsForward:=True;
  IsUpperLowercase:=True;
  SelectNode := TTreeNodeInfoData(TreeView.Selected.Data).GetID;
  Field := DataSet.FindField('scert_no');
  if (Field = nil) or (SelectNode = '')then
  begin
    IsFirst := False;
    Exit;
  end;
  Dataset.DisableControls;
  try
    if IsFromFirst and IsFirst then
      Dataset.First;
    if IsForward then  //向前搜寻
    begin
      if not IsFirst then
        DataSet.Next;
      while not DataSet.Eof do
      begin
        if IsUpperLowercase then //区分大小写
          I := CompareStr(Field.AsString, SelectNode)
        else
          I := CompareText(Field.AsString, SelectNode);
        if I = 0 then
        begin
          Break;
        end;
        DataSet.Next;
      end
    end
    else                             //向后搜寻
    begin
    if not IsFirst then
      DataSet.Prior;
    while not DataSet.Bof do
    begin
      if IsUpperLowercase then //区分大小写
        I := CompareStr(Field.AsString, SelectNode)
      else
        I := CompareText(Field.AsString, SelectNode);
      if I = 0 then
      begin
        Break;
      end;
      DataSet.Prior;
    end;
  end;
  finally
    DataSet.EnableControls;
    IsFirst := False;
  end;
end;

procedure TfaqhSetUnitInfo.TreeViewClick(Sender: TObject);
var
  SelectNode:string;
begin
  inherited;
  {
  if DataGrid.DataSource.DataSet<>nil then
  begin
    SearchDataset(DataGrid.DataSource.DataSet);
  end
  else ShowMessage('数据集处于关闭状态！请检查操作！');

  SelectNode := TTreeNodeInfoData(TreeView.Selected.Data).GetID;
  WorkView.FieldByName('查询.单位代码').Data.SetString(SelectNode);
  QueryRequest.SendCommand;
  SearchDataset(DataGrid.DataSource.DataSet);
  }
end;

procedure TfaqhSetUnitInfo.GridCellClick(Column: TColumn);
var
  ss : string;
begin
  ss := Grid.DataSource.DataSet.fieldbyname('scert_no').AsString;
  findTree(ss);
end;

procedure TfaqhSetUnitInfo.findTree(ss: string);
var
  i:Integer;
begin
  try
  TreeView.SetFocus;
  for i := 0 to TreeView.Items.Count-1 do
  begin
    if TTreeNodeInfoData(TreeView.Items[i].Data).GetID=ss then
    begin
      TreeView.Items[i].Selected := True;
      Exit;
    end;
  end;
  except
  end;
end;

procedure TfaqhSetUnitInfo.btnCancelClick(Sender: TObject);
begin
  inherited;
  treeSign := 0;
end;

initialization
  TUIStdClassFactory.Create('部门信息设置',TfaqhSetUnitInfo);

end.