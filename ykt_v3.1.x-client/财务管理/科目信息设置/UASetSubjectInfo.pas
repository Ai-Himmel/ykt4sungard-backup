unit UASetSubjectInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,
  UIncrementComboBox, RzDBNav, RzButton, RzRadChk, RzDBGrid,
  RzTabs, USMSetTreeParamsTemp, RzTreeVw,WVCommands, Buttons;


type
  TfaqhSetSubjectInfo = class(TfaSMSetTreeParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label25: TLabel;
    WVEdit2: TWVEdit;
    Label26: TLabel;
    WVComboBox8: TWVComboBox;
    Label27: TLabel;
    WVComboBox9: TWVComboBox;
    edtBusiId: TWVEdit;
    Label30: TLabel;
    Splitter1: TSplitter;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label9: TLabel;
    WVComboBox1: TWVComboBox;
    Label17: TLabel;
    WVComboBox2: TWVComboBox;
    Label2: TLabel;
    Label3: TLabel;
    WVComboBox3: TWVComboBox;
    edtSubjNo: TWVEdit;
    Label4: TLabel;
    Label5: TLabel;
    WVComboBox4: TWVComboBox;
    WVEdit3: TWVEdit;
    Label6: TLabel;
    WVComboBox5: TWVComboBox;
    Label7: TLabel;
    WVComboBox6: TWVComboBox;
    Label8: TLabel;
    edtId: TWVEdit;
    Label10: TLabel;
    edtPId: TWVEdit;
    Label11: TLabel;
    edtSubjName: TWVEdit;
    Label12: TLabel;
    WVComboBox7: TWVComboBox;
    Label13: TLabel;
    WVComboBox10: TWVComboBox;
    Label14: TLabel;
    WVComboBox11: TWVComboBox;
    procedure btnAddClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure TreeViewDblClick(Sender: TObject);
    procedure TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure GridCellClick(Column: TColumn);
  private
    treeSign:Integer;

    {刷新树视图结构}
    procedure CreatebusinessTree;
    {保存前检查}
    function SaveCheckBussiness:String;

    procedure findTree(ss: string);

  public

    procedure Init; override;

    { Public declarations }
  end;

var
  faqhSetSubjectInfo: TfaqhSetSubjectInfo;

implementation

uses KsFrameworks, KSClientConsts, SmartCardCommon;

{$R *.DFM}


procedure TfaqhSetSubjectInfo.CreatebusinessTree;
begin
  //WorkView1.FieldByName('商户标识').Data.SetInteger(0);
  WorkView1.FieldByName('标志').Data.SetString('R');
  WVRequest1.SendCommand;
  self.HandleNeeded;
  self.TreeView.HandleNeeded;

  self.FDataSetFieldID:='lvol0';
  self.FDataSetParentFieldID:='lserial0';
  self.FDataSetFieldName:='sall_name';
  self.FWorkViewFieldID:='序列号';
  self.FWorkViewFieldName:='科目名称';
  self.FWorkViewParentFieldID:='上级科目';
  self.FDefaultID:=0;
  self.FDataSet:= (WorkView1.FieldByName('查询结果集').Data.AsObject) as TDataSet;
  self.BuildTree;  
end;

procedure TfaqhSetSubjectInfo.Init;
begin
  inherited;
  treeSign := 0;
end;

procedure TfaqhSetSubjectInfo.btnAddClick(Sender: TObject);
var
  endBusi:Integer;
begin
  if TreeView.Selected=nil then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择上级科目！');
    Exit;
  end;
  {
  if RBtnAddBrother.Checked then
  begin
    if TreeView.Selected.Level=0 then
    begin
      Context.GetDialogSystem.ShowMessage('不能为根科目增加下级！');
      Exit;
    end;
  end;
  }
  endBusi := 0;
  if (WorkView.FieldByName('查询结果集').Data.IsEmpty=False) and (RbtnAddChild.Checked) then
  begin
    try
      endBusi := Grid.DataSource.DataSet.FieldByName('lvol5').AsInteger;
    except
    end;
    if endBusi=1 then
    begin
      Context.GetDialogSystem.ShowMessage('该科目是末级科目，不能再增加下级！');
      Exit;
    end;
  end;
  Inherited;
  edtPId.Text:=IntToStr(FCurrentID);
  //ShowMessage(FCurrentID);
  edtPId.Enabled:=False;
  edtId.Text:='0';
  edtId.Enabled := False;
  WorkView.FieldByName('上级科目').Data.SetInteger(FCurrentID);
  WorkView.FieldByName('标志').Data.SetString('A');
  WorkView.SynchronizeCtrlsToFields;
  treeSign := 0;
  //cbbBusiType.Enabled := True;
end;



function TfaqhSetSubjectInfo.SaveCheckBussiness:String;
begin
  Result:='';
  if Trim(edtsubjno.Text)='' then
  Begin
    Result:='请输入科目号！';
    edtsubjno.SetFocus;
    edtsubjno.SelectAll;
    Exit;
  end;
  if Trim(edtSubjName.Text)='' then
  Begin
    Result:='请输入科目名称！';
    edtSubjName.SetFocus;
    edtSubjName.SelectAll;
    Exit;
  end;
end;

procedure TfaqhSetSubjectInfo.btnOKClick(Sender: TObject);
var
  TmpMsg:String;
begin
  {
  if (self.Status = ssAdd)or (self.Status = ssChange) then
  begin
    if cbbEmpRateType.Enabled then
      if (cbbEmpRateType.Text='')or(cbbEmpRateType.Text='-') then
      begin
        Context.GetDialogSystem.ShowMessage('请选择佣金类型！');
        Exit;
      end;
    if (cbbBusiType.Text='') or (cbbBusiType.Text = '-') then
    begin
      Context.GetDialogSystem.ShowMessage('请选择商户类型！');
      Exit;
    end;
    if (Copy(cbbBusiType.Text,1,Pos('-',cbbBusiType.Text)-1))='1' then
      if (cbbDhf.Text='')or(cbbDhf.Text='-') then
      begin
        Context.GetDialogSystem.ShowMessage('请选择是否收搭伙费！');
        cbbDhf.SetFocus;
        Exit;
      end;
  end;
  }
  if treeview.Selected.HasChildren then
  begin
    //WVDigitalEdit18.Enabled:=false;
  end;
  if (self.Status = ssAdd)or (self.Status = ssChange) then
  begin
     TmpMsg:='';
     TmpMsg:=SaveCheckBussiness;
     if Trim(TmpMsg)<>'' then
     begin
      Context.GetDialogSystem.ShowMessage(TmpMsg);
      Exit;
     end;
  end;
  //inherited;

  WorkView.SynchronizeCtrlsToFields;
  if btnOk.Enabled and ConfirmEdit then
  begin
    case Status of
      ssAdd :
        DoAdd;
      ssChange :
        DoChange;
      ssDelete :
        DoDelete;
      ssViewDetail :
      begin
        Assert(False,'never run into there!');
      end;
    else
    begin
      Assert(False);
    end;
  end;
  end;

  if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowError(WorkView.Fieldbyname('返回信息').Data.AsString);
    Exit;
  end
  else
  begin
    Context.GetDialogSystem.ShowMessage(WorkView.Fieldbyname('返回信息').Data.AsString);
    //WorkView.FieldByName('查询.商户标识').Data.SetInteger(0);
    WorkView.FieldByName('标志').Data.SetString('R');
    btnQueryClick(Sender);
    self.CreatebusinessTree;
  end;
end;

procedure TfaqhSetSubjectInfo.btnDeleteClick(Sender: TObject);
begin
  if TreeView.Items.Count=0 then Exit;
  if TreeView.Selected = nil then Exit;
  if TreeView.Selected.Level=0 then
  begin
    Context.GetDialogSystem.ShowMessage('不能注销根节点！');
    Exit;
  end;
  if TreeView.Selected.HasChildren then
  begin
    Context.GetDialogSystem.ShowMessage('请先注销下属所有科目！');
    Exit;
  end;
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
  treeSign := 0;
end;

procedure TfaqhSetSubjectInfo.btnQueryClick(Sender: TObject);
var
  ss:string;
begin
  if edtBusiId.Text = '' then
    edtBusiId.Text := '0';
  ShowWaiting(SWaitingQuery);
  TreeView.Enabled:=True;
  if treeSign = 0 then
  begin
    CreatebusinessTree;
    treeSign := 9;
  end;
  CloseWaiting;
  WorkView.FieldByName('标志').Data.SetString('R');
  inherited;
  try
    ss := Grid.DataSource.DataSet.fieldbyname('lvol0').AsString;
    findTree(ss);
  except
  end;
end;

procedure TfaqhSetSubjectInfo.btnChangeClick(Sender: TObject);
begin
  if TreeView.Items.Count=0 then Exit;
  if TreeView.Selected = nil then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择需要修改的科目！');
    Exit;
  end;
  if TreeView.Selected.Level=0 then
  begin
    Context.GetDialogSystem.ShowMessage('不能对根科目信息进行修改！');
    Exit;
  end;
  inherited;
  WorkView.FieldByName('标志').Data.SetString('U');
  if treeview.Selected.HasChildren then
  begin
  end;
  treeSign := 0;
  //cbbBusiType.Enabled := False;
end;


procedure TfaqhSetSubjectInfo.btnCancelClick(Sender: TObject);
begin
  Inherited;
  //WorkView.FieldByName('查询.商户标识').Data.SetInteger(0);
  WorkView.FieldByName('标志').Data.SetString('R');
  btnQueryClick(Sender);
end;


procedure TfaqhSetSubjectInfo.TreeViewDblClick(Sender: TObject);
begin
  btnChangeClick(btnChange);
end;

procedure TfaqhSetSubjectInfo.TreeViewMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var AnItem : TTreeNode;
begin
  if Button = mbLeft then
  begin
    AnItem := TreeView.GetNodeAt(X, Y);
    if AnItem = nil then Exit;
  end;
  inherited;
end;

procedure TfaqhSetSubjectInfo.findTree(ss: string);
var
  i:Integer;
begin
  TreeView.SetFocus;
  for i := 0 to TreeView.Items.Count-1 do
  begin
    if TTreeNodeInfoData(TreeView.Items[i].Data).GetID=ss then
    begin
      TreeView.Items[i].Selected := True;
      Exit;
    end;
  end;
end;

procedure TfaqhSetSubjectInfo.GridCellClick(Column: TColumn);
var
  ss : string;
begin
  try
    ss := Grid.DataSource.DataSet.fieldbyname('lvol0').AsString;
    findTree(ss);
  except
  end;
end;

initialization
  TUIStdClassFactory.Create('科目信息设置',TfaqhSetSubjectInfo);

end.
