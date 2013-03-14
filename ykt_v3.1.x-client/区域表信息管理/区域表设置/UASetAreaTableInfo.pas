unit UASetAreaTableInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  DBActns, ActnList, WorkViews, WVDBBinders, WVCmdReq,
  Db, DBCtrls, Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  ComCtrls, UIncrementComboBox, WVCtrls, Mask,UABusinessTreeMan, 
  RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs,USMSetTreeParamsTemp,
  RzTreeVw, Buttons;

const
  AreaCount = 5;

type
  TfaSetAreaTable =  class(TfaSMSetTreeParamsTemp)
    UIPanel3: TUIPanel;
    WVLabel2: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel4: TWVLabel;
    WVEdit1: TWVEdit;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVEdit3: TWVEdit;
    WVLabel7: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVEdit4: TWVEdit;
    WVLabel9: TWVLabel;
    WVEdit5: TWVEdit;
    WVLabel10: TWVLabel;
    WVEdit6: TWVEdit;
    WVLabel11: TWVLabel;
    WVComboBox3: TWVComboBox;
    cbbAreaNo: TWVComboBox;
    Splitter1: TSplitter;
    procedure btnAddClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
  private
    //FfaBusinessTreeMan:TfaBusinessTreeMan;
    procedure CreateAreaTree;
    procedure findtree(s:string);
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faSetAreaTable: TfaSetAreaTable;

  
implementation
uses KSFrameWorks,KSDataDictionary, UCMqhAreaTableImp;

{$R *.DFM}

procedure TfaSetAreaTable.CreateAreaTree;
begin
  self.FDataSetFieldID:='lvol0';
  self.FDataSetParentFieldID:='lvol1';
  self.FDataSetFieldName:='scard0';
  self.FWorkViewFieldID:='查询.区域号';
  self.FWorkViewFieldName:='区域名称';
  self.FWorkViewParentFieldID:='父区域号';
  self.FDefaultID:=0;
  self.FDataSet:= (WorkView.FieldByName('查询结果集').Data.AsObject) as TDataSet;
  self.BuildTree;
end;

procedure TfaSetAreaTable.Init;
begin
  inherited;
end;

procedure TfaSetAreaTable.btnAddClick(Sender: TObject);
var
  //strName:string;
  AreaLevel,NewAreaLevel:integer;
  //TmpDataSet:TDataSet;
begin
  WVComboBox2.Enabled:=True;
  if TreeView.Selected=nil then
  begin
    Context.GetDialogSystem.ShowMessage('请选择父区域！');
    Exit;
  end;
  if TreeView.Selected.Level=0 then
  begin
    if RBtnAddBrother.Checked=True then
    begin
      Context.GetDialogSystem.ShowMessage('不能为根区域添加同级区域！');
      Exit;
    end;
  end;

  NewAreaLevel:=0;
  if (TDataset(WorkView.FieldByName('查询结果集').Data.AsObject)= nil) then
  begin
    showmessage('null');
  end
  else AreaLevel:=TDataset(WorkView.FieldByName('查询结果集').Data.AsObject).FieldByName('lvol2').AsInteger;

  //showmessage('区域级别'+inttostr(AreaLevel));
  if RbtnAddChild.Checked=True then
  begin
    NewAreaLevel:=AreaLevel+1;
    if NewAreaLevel>AreaCount then
    begin
      COntext.GetDialogSystem.ShowWarning('不能为该区域级别（最低级别）设置下级区域！');
      Exit;
    end;
  end;
  if RBtnAddBrother.Checked=True then
  begin
    NewAreaLevel:=AreaLevel;
  end;
  Inherited;

  WorkView.FieldByName('父区域号').Data.SetInteger(FCurrentID);
  WorkView.FieldByName('区域级别').Data.SetInteger(NewAreaLevel);
  WorkView.SynchronizeCtrlsToFields;
  cbbAreaNo.Enabled:=False;
  WVComboBox2.Enabled:=False;
end;

procedure TfaSetAreaTable.btnOKClick(Sender: TObject);
var
  TmpMsg:String;

begin
  if (self.Status = ssAdd)or (self.Status = ssChange) then
  begin
    if Trim(WVEdit3.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('请输入这个区域的名称！');
      WVEdit3.SetFocus;
      Exit;
    end;
    if WVComboBox2.ItemIndex=-1 then
    begin
      Context.GetDialogSystem.ShowMessage('请为这个区域定义区域级别！');
      WVComboBox2.SetFocus;
      Exit;
    end;
    if WVComboBox2.ItemIndex<>-1 then
    begin
      TmpMsg:= Trim(WVComboBox2.Text);
      if Copy(TmpMsg,Pos('-',TmpMsg)+1,Length(TmpMsg)-Pos('-',TmpMsg))='根' then
      begin
        Context.GetDialogSystem.ShowMessage('这个区域不能定义为根区域！请重新定义！');
        WVComboBox2.SetFocus;
        Exit;
      end;
    end;
  end;
  //更新到数据库，
  //WorkView.SynchronizeCtrlsToFields;
  inherited;
  {
  try
    FreeIdObjects(-28);
    WVComboBox1.ItemsDataEntry:='-28';
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('错误，请重新打开该功能--'+e.Message);
    end;
  end;
  }
  btnQuery.Click;
  //sleep(100);
  //CreateAreaTree;

end;

procedure TfaSetAreaTable.btnDeleteClick(Sender: TObject);
begin
  if TreeView.Items.Count=0 then Exit;
  if TreeView.Selected = nil then Exit;
  if TreeView.Selected.Level=0 then
  begin
    Context.GetDialogSystem.ShowMessage('不能注销根节点的信息！');
    Exit;
  end;
  if TreeView.Selected.HasChildren then
  begin
    Context.GetDialogSystem.ShowMessage('请先注销下属所有区域信息！');
    Exit;
  end;
  inherited;
end;

procedure TfaSetAreaTable.btnQueryClick(Sender: TObject);
var
  ss:string;
begin
  TreeView.Enabled:=True;
  btnAdd.Enabled:=True;
  WorkView.FieldByName('查询.区域号').Data.SetInteger(0);
  //WorkView.SynchronizeCtrlsToFields;
  inherited;
  CreateAreaTree;
  try
    ss := Grid.DataSource.DataSet.fieldbyname('scert_no').AsString;
    findTree(ss);
  except
  end;
end;


procedure TfaSetAreaTable.btnChangeClick(Sender: TObject);
begin
  WVComboBox2.Enabled:=True;
  cbbAreaNo.Enabled:=True;
  if TreeView.Items.Count=0 then Exit;
  if TreeView.Selected = nil then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择需要修改的区域！');
    Exit;
  end;
  if TreeView.Selected.Level=0 then
  begin
    Context.GetDialogSystem.ShowMessage('不能对根区域信息进行修改！');
    Exit;
  end;
  inherited;
  cbbAreaNo.Enabled:=False;
  WVComboBox2.Enabled:=False;
end;

procedure TfaSetAreaTable.btnCancelClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  inherited; 
  btnQueryClick(Sender);
end;

procedure TfaSetAreaTable.GridCellClick(Column: TColumn);
var
  ss : string;
begin
  ss := Grid.DataSource.DataSet.fieldbyname('lvol0').AsString;
  findTree(ss);
end;

procedure TfaSetAreaTable.findtree(s: string);
var
  i:Integer;
begin
  try
  TreeView.SetFocus;
  for i := 0 to TreeView.Items.Count-1 do
  begin
    if TTreeNodeInfoData(TreeView.Items[i].Data).GetID=s then
    begin
      TreeView.Items[i].Selected := True;
      Exit;
    end;
  end;
  except
  end;
end;

initialization
  TUIStdClassFactory.Create('区域设置',TfaSetAreaTable);

end.
