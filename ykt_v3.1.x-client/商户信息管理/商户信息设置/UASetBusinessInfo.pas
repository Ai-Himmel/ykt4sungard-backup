unit UASetBusinessInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,
  UIncrementComboBox, RzDBNav, RzButton, RzRadChk, RzDBGrid,
  RzTabs, USMSetTreeParamsTemp, RzTreeVw,WVCommands, Buttons;


type
  TfaqhSetBusinessInfo = class(TfaSMSetTreeParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    WVEdit10: TWVEdit;
    WVEdit11: TWVEdit;
    WVEdit15: TWVEdit;
    WVEdit16: TWVEdit;
    cbbBusiType: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    Label25: TLabel;
    WVEdit2: TWVEdit;
    Label26: TLabel;
    WVComboBox8: TWVComboBox;
    Label27: TLabel;
    WVComboBox9: TWVComboBox;
    edtBusiId: TWVEdit;
    edtId: TWVEdit;
    Label30: TLabel;
    Bevel1: TBevel;
    Splitter1: TSplitter;
    Label32: TLabel;
    WVComboBox13: TWVComboBox;
    edtPId: TWVEdit;
    Label4: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    WVEdit5: TWVEdit;
    cbbCheckSelf: TWVComboBox;
    Label31: TLabel;
    WVComboBox12: TWVComboBox;
    Label5: TLabel;
    Label14: TLabel;
    WVEdit14: TWVEdit;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label22: TLabel;
    edtBankAccNo: TWVEdit;
    Label37: TLabel;
    cbbEmpRateType: TWVComboBox;
    Label35: TLabel;
    edtEmpRate: TWVEdit;
    Label36: TLabel;
    Label18: TLabel;
    edtFee: TWVEdit;
    Label24: TLabel;
    Label38: TLabel;
    edtBankAccName: TWVEdit;
    Bevel2: TBevel;
    WVEdit4: TWVEdit;
    Label3: TLabel;
    cbbBankCode: TWVComboBox;
    Label8: TLabel;
    cbbDhf: TWVComboBox;
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
    procedure TreeViewClick(Sender: TObject);
    procedure cbbBusiTypeChange(Sender: TObject);
    procedure cbbCheckSelfChange(Sender: TObject);
  private
    {
    IsFirst:Boolean;
    IsFromFirst:Boolean;
    IsForward:Boolean;
    IsUpperLowercase:Boolean;}
    treeSign:Integer;

    {刷新树视图结构}
    procedure CreatebusinessTree;
    {保存前检查}
    function SaveCheckBussiness:String;

    procedure findTree(ss: string);

    //procedure SearchDataset(DataSet: TDataSet);

    //procedure fillBusiRate;
    { Private declarations }
  public

    procedure Init; override;

    { Public declarations }
  end;

var
  faqhSetBusinessInfo: TfaqhSetBusinessInfo;

implementation

uses KsFrameworks, KSClientConsts, SmartCardCommon,UWorkerNum,UCMqhBusinessManageImp;

{$R *.DFM}


procedure TfaqhSetBusinessInfo.CreatebusinessTree;
begin
  WorkView1.FieldByName('商户标识').Data.SetInteger(0);
  WorkView1.FieldByName('操作标志').Data.SetString('R');
  WVRequest1.SendCommand;
  self.HandleNeeded;
  self.TreeView.HandleNeeded;

  self.FDataSetFieldID:='lvol3';
  self.FDataSetParentFieldID:='lvol1';
  self.FDataSetFieldName:='sall_name';
  self.FWorkViewFieldID:='商户标识';
  self.FWorkViewFieldName:='商户名称';
  self.FWorkViewParentFieldID:='父商户标识';
  self.FDefaultID:=0;
  self.FDataSet:= (WorkView1.FieldByName('查询结果集').Data.AsObject) as TDataSet;
  self.BuildTree;  
end;

procedure TfaqhSetBusinessInfo.Init;
begin
  inherited;
  treeSign := 0;
end;

procedure TfaqhSetBusinessInfo.btnAddClick(Sender: TObject);
var
  endBusi:Integer;
begin
  if TreeView.Selected=nil then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择父商户！');
    Exit;
  end;
  if RBtnAddBrother.Checked then
  begin
    if TreeView.Selected.Level=0 then
    begin
      Context.GetDialogSystem.ShowMessage('不能为根商户增加同级商户！');
      Exit;
    end;
  end;
  if (WorkView.FieldByName('查询结果集').Data.IsEmpty=False) and (RbtnAddChild.Checked) then
  begin
    try
      endBusi := Grid.DataSource.DataSet.FieldByName('smain_flag2').AsInteger;
    except
    end;
    if endBusi=1 then
    begin
      Context.GetDialogSystem.ShowMessage('该商户是末级商户，不能再增加下级！');
      Exit;
    end;
  end;
  Inherited;
  edtPId.Text:=IntToStr(FCurrentID);
  //ShowMessage(FCurrentID);
  edtPId.Enabled:=False;
  edtId.Text:='0';
  edtId.Enabled := False;
  cbbBusiTypeChange(Sender);
  cbbCheckSelfChange(Sender);
  WorkView.FieldByName('父商户标识').Data.SetInteger(FCurrentID);
  WorkView.FieldByName('操作标志').Data.SetString('A');
  WorkView.SynchronizeCtrlsToFields;
  treeSign := 0;
  cbbBusiType.Enabled := True;
end;



function TfaqhSetBusinessInfo.SaveCheckBussiness:String;
begin
  Result:='';
  if Trim(WVEdit5.Text)='' then
  Begin
    Result:='请输入商户的名称！';
    WVEdit5.SetFocus;
    WVEdit5.SelectAll;
    Exit;
  end;
  if (Trim(WVComboBox12.Text)='-')or(Trim(WVComboBox12.Text)='') then
  begin
    Result:='请选择校区信息！';
    WVComboBox12.SetFocus;
    WVComboBox12.SelectAll;
    Exit;
  end;

  if (Trim(cbbBusiType.Text)='-')or (Trim(cbbBusiType.Text)='') then
  begin
    Result:='请选择商户类别！';
    cbbBusiType.SetFocus;
    cbbBusiType.SelectAll;
    Exit;
  end;

  if ((Trim(cbbCheckSelf.Text)='')or(Trim(cbbCheckSelf.Text)='-')) and
     (cbbCheckSelf.Enabled) then
  begin
    Result:='请为这个商户定义是否为独立核算方式！';
    cbbCheckSelf.SetFocus;
    cbbCheckSelf.SelectAll;
    Exit;
  end;
end;

procedure TfaqhSetBusinessInfo.btnOKClick(Sender: TObject);
var
  TmpMsg:String;
begin
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
    WorkView.FieldByName('查询.商户标识').Data.SetInteger(0);
    WorkView.FieldByName('操作标志').Data.SetString('R');
    btnQueryClick(Sender);
    self.CreatebusinessTree;
  end;
end;

procedure TfaqhSetBusinessInfo.btnDeleteClick(Sender: TObject);
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
    Context.GetDialogSystem.ShowMessage('请先注销下属所有商户信息！');
    Exit;
  end;
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
  treeSign := 0;
end;

procedure TfaqhSetBusinessInfo.btnQueryClick(Sender: TObject);
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
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;
  try
    ss := Grid.DataSource.DataSet.fieldbyname('lvol3').AsString;
    findTree(ss);
  except
  end;
end;

procedure TfaqhSetBusinessInfo.btnChangeClick(Sender: TObject);
begin
  if TreeView.Items.Count=0 then Exit;
  if TreeView.Selected = nil then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择需要修改的商户！');
    Exit;
  end;
  if TreeView.Selected.Level=0 then
  begin
    Context.GetDialogSystem.ShowMessage('不能对根商户信息进行修改！');
    Exit;
  end;
  inherited;
  cbbBusiTypeChange(Sender);
  cbbCheckSelfChange(Sender);
  WorkView.FieldByName('操作标志').Data.SetString('U');
  if treeview.Selected.HasChildren then
  begin
  end;
  treeSign := 0;
  cbbBusiType.Enabled := False;
end;


procedure TfaqhSetBusinessInfo.btnCancelClick(Sender: TObject);
begin
  Inherited;
  WorkView.FieldByName('查询.商户标识').Data.SetInteger(0);
  WorkView.FieldByName('操作标志').Data.SetString('R');
  btnQueryClick(Sender);
end;


procedure TfaqhSetBusinessInfo.TreeViewDblClick(Sender: TObject);
begin
  btnChangeClick(btnChange);
end;

procedure TfaqhSetBusinessInfo.TreeViewMouseDown(Sender: TObject;
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

procedure TfaqhSetBusinessInfo.findTree(ss: string);
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

procedure TfaqhSetBusinessInfo.GridCellClick(Column: TColumn);
var
  ss : string;
begin
  try
    ss := Grid.DataSource.DataSet.fieldbyname('lvol3').AsString;
    findTree(ss);
  except
  end;
end;

procedure TfaqhSetBusinessInfo.TreeViewClick(Sender: TObject);
{var
  SelectNode:string;
  bookmark:TBookMark;}
begin
  {
  SelectNode := TTreeNodeInfoData(TreeView.Selected.Data).GetID;
  bookmark:=self.DataSource.DataSet.GetBookmark;
  DataSource.DataSet.First;
  while not DataSource.DataSet.Eof do
  begin
    if self.DataSource.DataSet.FieldByName('lvol3').AsString= SelectNode then
    begin
       bookmark:=self.DataSource.DataSet.GetBookmark;
       Break;
    end;
    self.DataSource.DataSet.Next;
  end;
  self.DataSource.DataSet.GotoBookmark(pointer(bookmark));
  //WorkView.FieldByName('查询.商户标识').Data.SetInteger(StrToInt(SelectNode));
  //QueryRequest.SendCommand;
  //SearchDataset(DataGrid.DataSource.DataSet);
  }
  inherited;
end;
{
procedure TfaqhSetBusinessInfo.SearchDataset(DataSet: TDataSet);
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
  Field := DataSet.FindField('lvol3');
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

procedure TfaqhSetBusinessInfo.fillBusiRate;
var
  ss:Real;
begin
  try
    if ckAutoSetNewParams.Checked then
    begin
      ss := Grid.DataSource.DataSet.fieldbyname('drate0').AsFloat;
      edtEmpRate.Text := FloatToStr(ss);
    end
    else
    begin
      edtEmpRate.Text := '0';
    end;
  except
  end;
end;
}
procedure TfaqhSetBusinessInfo.cbbBusiTypeChange(Sender: TObject);
var
  busiType:string;
begin
  busiType := Copy(cbbBusiType.Text,1,Pos('-',cbbBusiType.Text)-1);
  if busiType='1' then
  begin
    edtFee.Enabled := false;
    edtFee.Text := '0';
    edtEmpRate.Enabled := True;
    cbbEmpRateType.Enabled := True;
    cbbDhf.Enabled := True;
  end
  else if busiType='0' then
  begin
    edtFee.Enabled := False;
    edtEmpRate.Text := '0';
    edtEmpRate.Enabled := False;
    cbbEmpRateType.Enabled := False;
    cbbDhf.Enabled := False;
    cbbDhf.ItemIndex := 0;
  end
  else
  begin
    edtFee.Enabled := True;
    edtEmpRate.Text := '0';
    edtEmpRate.Enabled := False;
    cbbEmpRateType.Enabled := False;
    cbbDhf.Enabled := False;
    cbbDhf.ItemIndex := 0;
  end;
  inherited;

end;

procedure TfaqhSetBusinessInfo.cbbCheckSelfChange(Sender: TObject);
var
  checkSelf:string;
begin
  checkSelf := Copy(cbbCheckSelf.Text,1,Pos('-',cbbCheckSelf.Text)-1);
  //如果是独立核算商户(1)，可以编辑银行相关信息
  if checkSelf = '1' then
  begin
    edtBankAccNo.Enabled := True;
    cbbBankCode.Enabled := True;
    edtBankAccName.Enabled := True;
  end
  else
  begin
    edtBankAccNo.Text := '';
    edtBankAccName.Text := '';
    cbbBankCode.ItemIndex := 0;
    edtBankAccNo.Enabled := False;
    cbbBankCode.Enabled := False;
    edtBankAccName.Enabled := False;
  end;
end;

initialization
  TUIStdClassFactory.Create('商户信息设置',TfaqhSetBusinessInfo);

end.
