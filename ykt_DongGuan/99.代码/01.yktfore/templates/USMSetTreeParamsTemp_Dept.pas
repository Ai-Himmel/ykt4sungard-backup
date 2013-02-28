unit USMSetTreeParamsTemp_Dept;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USetParamsTemp
   <What>参数设置操作界面模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks,
  KSFrames, KSClientConsts,
  ComCtrls, Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVDBBinders, WVCmdReq, WorkViews, Db, WVCommands, DBCtrls, DBActns,
  ActnList, RzDBGrid, RzTabs, RzDBNav, RzButton, RzRadChk, RzTreeVw,
  KsBranchTree,contnrs,Dialogs, Mask, WVCtrls, Buttons;
{
const
  TabMargin = 3;
}

const

  selectIndex = 0;
 // NoSelectIndex = 1;
  ClearIndex =1;
  NotAllSelectIndex=2;

type 
{
    <Class>TTreeNodeMenuData
    <What>对应菜单项目
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TTreeNodeInfoData = class
  private
    FMetaNode: TKSMetaNode;

  protected

  public
    constructor Create(AMetaNode: TKSMetaNode);
    function    GetCaption : string;
    function    GetID : string;
    property    MetaNode: TKSMetaNode read FMetaNode;
  end;




type
  // 参数设置界面的状态
  TSettingStatus = (
    ssBrowse,         // 浏览状态
    ssAdd,            // 增加状态
    ssChange,         // 修改状态
    ssDelete,         // 删除状态
    ssViewDetail      // 浏览细节数据状态
    );

  // 数据维护形式
  TParamMaintainType = (
    pmtCenter,        // 总部维护数据
    pmtDepartment     // 营业部维护数据
    );

  TfaSMSetTreeParamsTemp_Dept = class(TKSFrame)
    DataSource: TDataSource;
    QueryRequest: TWVRequest;
    QueryBinder: TWVDBBinder;
    AddRequest: TWVRequest;
    DeleteRequest: TWVRequest;
    ChangeRequest: TWVRequest;
    WVDataSource: TWVDataSource;
    alDatasetActions: TActionList;
    DataSetFirst: TDataSetFirst;
    DataSetPrior: TDataSetPrior;
    DataSetNext: TDataSetNext;
    DataSetLast: TDataSetLast;
    pcPages: TRzPageControl;
    tsQuery: TRzTabSheet;
    tsEdit: TRzTabSheet;
    UIPanel2: TUIPanel;
    btnOK: TBitBtn;
    btnCancel: TBitBtn;
    DBNavigator: TRzDBNavigator;
    UIPanel1: TUIPanel;
    btnQuery: TBitBtn;
    btnAdd: TBitBtn;
    btnChange: TBitBtn;
    btnDelete: TBitBtn;
    btnViewDetail: TBitBtn;
    ckAutoSetNewParams: TRzCheckBox;
    TreeView: TRzTreeView;
    WorkView: TWorkView;
    Grid: TRzDBGrid;
    RBtnAddBrother: TRzRadioButton;
    RbtnAddChild: TRzRadioButton;
    procedure   btnAddClick(Sender: TObject);
    procedure   btnChangeClick(Sender: TObject);
    procedure   btnQueryClick(Sender: TObject);
    procedure   btnDeleteClick(Sender: TObject);
    procedure   btnOKClick(Sender: TObject);
    procedure   btnCancelClick(Sender: TObject);
    procedure   CheckReturnData(Request: TWVRequest;
      Command: TWVCommand);
    procedure   pcPagesDrawTab(Control: TCustomTabControl; TabIndex: Integer;
      const Rect: TRect; Active: Boolean);
    procedure   DataSourceDataChange(Sender: TObject; Field: TField);
    procedure   DataSourceStateChange(Sender: TObject);
    procedure   btnViewDetailClick(Sender: TObject);
    procedure   GridDblClick(Sender: TObject);
    procedure   CheckEditFieldValid(WorkField: TWVField);
    procedure   DBNavigatorClick(Sender: TObject; Button: TNavigateBtn);
    procedure   GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure   GridKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure alDatasetActionsExecute(Action: TBasicAction;
      var Handled: Boolean);
    procedure alDatasetActionsUpdate(Action: TBasicAction;
      var Handled: Boolean);
    procedure TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure TreeViewDragDrop(Sender, Source: TObject; X, Y: Integer);
    procedure TreeViewDragOver(Sender, Source: TObject; X, Y: Integer;
      State: TDragState; var Accept: Boolean);
    procedure TreeViewDblClick(Sender: TObject);
    procedure TreeViewClick(Sender: TObject);
    procedure pcPagesChanging(Sender: TObject; NewIndex: Integer;
      var AllowChange: Boolean);
    procedure pcPagesPaintTabBackground(Sender: TObject; ACanvas: TCanvas;
      ATabIndex: Integer; const ARect: TRect; var Handled: Boolean);
  private
    FStatus:    TSettingStatus;
    FAutoRefresh : Boolean;
    FCanEdit : Boolean;   //允许增加、修改、删除
    FCanDelete: Boolean;  // 允许删除
    FCanAdd: Boolean;     // 允许增加
    FCanChange: Boolean;  // 允许修改
    FLocalDepartment : string;  // 发起营业部代码

    FList: TObjectList;
    FBranchNo:string;
    Include:Boolean;

    procedure   SetStatus(const Value: TSettingStatus);
    procedure   SetCanAdd(const Value: Boolean);
    procedure   SetCanChange(const Value: Boolean);
    procedure   SetCanDelete(const Value: Boolean);
    procedure   CheckDataCanEdit;

  protected
    FEditSucceed : Boolean;
    FDepartmentFieldName : string;
    FDepartmentWVField : TWVField;
    FMaintainType: TParamMaintainType;
    
    procedure   Init; override;
    procedure   EnableEditCtrls(AEnabled : Boolean); virtual; // 控制控件是否可以编辑
    procedure   BeforeAdd; virtual; // 继承该方法，增加初始化部分
    procedure   BeforeChange; virtual; // 继承该方法，增加初始化部分
    procedure   BeforeDelete; virtual; // 继承该方法，增加初始化部分
    procedure   BeforeViewDetail{(IsFirst : Boolean=True)}; virtual; // 继承该方法，增加初始化部分
    procedure   CancelEdit; virtual; // 继承该方法，增加清除数据部分
    procedure   DoAdd; virtual; // 继承该方法，设置EditRequest
    procedure   DoChange; virtual; // 继承该方法，设置EditRequest
    procedure   DoDelete; virtual; // 继承该方法，设置EditRequest
    procedure   SendEditCommand(Request : TWVRequest); virtual; // 继承该方法，处理设置（增加、修改、删除）错误，设置FEditSucceed
    function    GetCurrentRecordInfo : string; virtual; // 继承该方法，返回一行数据的描述（用于删除数据）
    procedure   DoQuery; virtual; // 继承该方法，设置查询数据
    procedure   SendQueryCommand; virtual; // 继承该方法，处理查询错误
    procedure   EnableEdit(CanEdit : Boolean);  // 废除
    procedure   UpdateButton; // 更新按键的Enabled状态
    function    InternalGetCanEdit : Boolean; virtual; // 判断是否可以修改：根据数据维护类型和当前营业部控制FCanEdit属性
    procedure   InitEx; override;   // 特殊的初始化，支持自动查询
    procedure   StatusChanged; virtual; // 界面操作状态发生改变，调用 DisplayData
    procedure   DisplayData; virtual;   // 将数据从数据集里面显示出来（同步到工作视图）。如果使用特殊的特殊的控件需要重载此方法。
    procedure   SaveModifiedData; virtual;  // 将修改的数据同步到工作视图。如果使用特殊的控件需要重载此方法。
    function    ConfirmEdit : Boolean; virtual; // 返回是否允许修改。在按下确认的时候被调用。可以在这里弹出对话框提示确认或者复核。

  public
    BranchName,IncludeName:string;
    FSingleSelect:Boolean;
    FWorkView:TWorkView;

    FDataSet:TDataSet;
    FDataSetFieldName:String; {树节点名称字段名}
    FDataSetFieldID:String;{树节点ID的字段名}
    FDataSetParentFieldID:String;{父节点id字段名}
    FWorkViewFieldName:String; {树节点名称字段名}
    FWorkViewFieldID:String;{树节点ID的字段名}
    FWorkViewParentFieldID:String;{父节点id字段名}
    FDefaultID:Integer;

    //FCurrentParentID:Integer; {当前编辑节点的父ID}
    //FCurrentID:Integer; {当前编辑节点的ID}
    FCurrentParentID:string; {当前编辑节点的父ID}
    FCurrentID:string; {当前编辑节点的ID}

    constructor Create(AOwner : TComponent); override;
    destructor Destroy;

    procedure   BuildTree;
    property    CanEdit : Boolean read FCanEdit write FCanEdit;
    procedure   InitTreeNode(TreeNode:TTreeNode);   //清空所有营业部选中状态
    procedure   ClearTreeNode(TreeNode:TTreeNode);  //清空所有子营业部选中状态
    procedure   SelectTreeNode(TreeNode:TTreeNode); //选中自身或所有子营业部
    procedure   ClearParentAndBrotherNode(ParentNode,TreeNode:TTreeNode); //清空所有父和兄弟选中状态
    {从数据集中读取树结构的信息}
    procedure   ReadTreeInfoFromDataSet(DataSet: TDataSet;CInfoAdmin:TInfoAdmin);
    {拖放功能中复制节点}
    procedure   CopyNodeUnder(treeview:TRzTreeview;sourcenode,targetnode:ttreenode);
    procedure   InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
    procedure   UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
    procedure   CheckImageIndex(AnItem: TTreeNode);
    procedure   SingleSelectTreeNode(ParentNode,TreeNode : TTreeNode);
    procedure   MultiSelectTreeNode(ParentNode,TreeNode : TTreeNode);

    procedure   CloseDataset; override;
    property    Status : TSettingStatus read FStatus write SetStatus;
    property    AutoRefresh : Boolean read FAutoRefresh write FAutoRefresh default True;
    property    CanAdd : Boolean read FCanAdd write SetCanAdd default True;
    property    CanChange : Boolean read FCanChange write SetCanChange default True;
    property    CanDelete : Boolean read FCanDelete write SetCanDelete default True;
    property    MaintainType : TParamMaintainType read FMaintainType;

    {在DBGRID中定位指定纪录}
    procedure   GetCurrentDbGrid(CurrentTreeId:string);
  end;

var
  faSMSetTreeParamsTemp_Dept: TfaSMSetTreeParamsTemp_Dept;

implementation

uses KSFrameWorkUtils, DataUsageUtils, LogFile, SmartCardCommon,TypInfo, DBAIntf,DataTypes;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

{ TfaSMSetTreeParamsTemp }



destructor TfaSMSetTreeParamsTemp_Dept.Destroy;
begin
  FList.Free;
  FInfoAdmin.Free ;
  FDataSet.Free;
  inherited;
end;


constructor TTreeNodeInfoData.Create(AMetaNode: TKSMetaNode);
begin
  Assert(AMetaNode<>nil);
  inherited Create;
  FMetaNode := AMetaNode;
end;




function TTreeNodeInfoData.GetCaption: string;
begin
  Result := FMetaNode.Caption;
end;

function TTreeNodeInfoData.GetID: string;
begin
  Result := FMetaNode.Id ;
end;


procedure   TfaSMSetTreeParamsTemp_Dept.GetCurrentDbGrid(CurrentTreeId:string);
begin
  FSearchOptions.FieldName := FDataSetFieldID;
  FSearchOptions.SearchValue := CurrentTreeId;
  FSearchOptions.IsUpperLowercase := True;
  FSearchOptions.IsFromFirst := True;
  FSearchOptions.IsForward := True;
  FSearchOptions.IsFirst:=True;

  if DataGrid.DataSource.DataSet<>nil then
    SearchDataset(DataGrid.DataSource.DataSet,FSearchOptions)
  else ShowMessage('数据集处于关闭状态！请检查操作！');
end;



procedure TfaSMSetTreeParamsTemp_Dept.CopyNodeUnder(treeview:TRzTreeview;sourcenode,targetnode:ttreenode);
var
  newnode:ttreenode;
  i:integer;
begin
  newnode:=treeview.items.addchildfirst(targetnode,''); //建立目标项
  newnode.assign(sourcenode); //复制源项属性
  for i:=sourcenode.count-1 downto 0 do //递归调用，按倒序移动其所有子项
  CopyNodeUnder (treeview,sourcenode.item[i],newnode);
  treeview.items.delete(sourcenode); //删除源项
end;

procedure TfaSMSetTreeParamsTemp_Dept.ReadTreeInfoFromDataSet(DataSet: TDataSet;CInfoAdmin:TInfoAdmin);
var
  LastNode,Node: TKSMetaNode;
  Structure:TKSTreeStructure;
begin
  LastNode:=nil;
  try
    CInfoAdmin.InfoList.Clear;
    CInfoAdmin.StructureList.Clear;
    Assert(DataSet<>nil);
    DataSet.first;
    while not DataSet.Eof do
    begin
      LastNode := TKSMetaNode.Create;              //树节点的名称和代码集合
      LastNode.ID := DataSet.FieldByName(FDataSetFieldID).AsString;
      LastNode.Caption := DataSet.FieldByName(FDataSetFieldName).AsString; //
      LastNode.Description :='';
      LastNode.NodeType := '';
      CInfoAdmin.InfoList.Add(LastNode);
      LastNode := nil;
      DataSet.Next;
    end;
    DataSet.first;
    while not DataSet.Eof do
    begin
      Node := CInfoAdmin.InfoList.Find(DataSet.FieldByName(FDataSetFieldID).AsString);   //
      if Node<>nil then
      begin
        Structure := TKSTreeStructure.Create;
        CInfoAdmin.StructureList.Add(Structure);  //树上级节点代码集合
        if (DataSet.FieldByName(FDataSetParentFieldID).AsString='') then  //
        begin
          Node.NodeType:=RootValue;
          Structure.ParentId := '';
          Structure.ChildId := Node.ID;
        end else
        begin
          Structure.ChildId := Node.ID;
          if Node.NodeType='' then Node.NodeType:=LeafValue;
          //上级营业部
          LastNode:= CInfoAdmin.InfoList.Find(DataSet.FieldByName(FDataSetParentFieldID).AsString);
          if LastNode<>nil then
          begin
            Structure.ParentId := DataSet.FieldByName(FDataSetParentFieldID).AsString;
            if LastNode.NodeType<>RootValue then
            begin
              LastNode.NodeType:=GroupValue;
            end;
          end else         //营业部登录
          begin
            Node.NodeType:=RootValue;
            Structure.ParentId := DataSet.FieldByName(FDataSetParentFieldID).AsString;
          end;
        end;
      end;
      Node:=nil;
      DataSet.Next;
    end
  finally
  end;
  CInfoAdmin.Init;
end;




procedure TfaSMSetTreeParamsTemp_Dept.ClearParentAndBrotherNode(ParentNode,TreeNode: TTreeNode);
var
  Child: TTreeNode;
begin
  if (ParentNode<>nil) and (ParentNode<>TreeNode) then
  begin
    ParentNode.imageIndex:=ClearIndex ;
    ParentNode.SelectedIndex :=ClearIndex;
    Child := ParentNode.GetFirstChild;
    while (Child<>nil)do
    begin
      Child.imageIndex:=ClearIndex;
      Child.SelectedIndex :=ClearIndex;
      ClearParentAndBrotherNode(Child,TreeNode);
      Child := ParentNode.GetNextChild(Child);
    end;
  end else if ParentNode=TreeNode then
  begin
    ParentNode.imageIndex:=SelectIndex ;
    ParentNode.SelectedIndex :=SelectIndex;
  end;
end;



procedure TfaSMSetTreeParamsTemp_Dept.SelectTreeNode(TreeNode: TTreeNode);
var
  Child : TTreeNode;
begin
  if TreeNode<>nil then
  begin
    TreeNode.imageIndex:=SelectIndex ;
    TreeNode.SelectedIndex :=SelectIndex;
  end;
  Child := TreeNode.GetFirstChild;
  while Child<>nil do
  begin
    Child.imageIndex:=SelectIndex;
    Child.SelectedIndex :=SelectIndex;
    SelectTreeNode(Child);
    Child := TreeNode.GetNextChild(Child);
  end;
end;


procedure TfaSMSetTreeParamsTemp_Dept.ClearTreeNode(TreeNode: TTreeNode);
var
  Child : TTreeNode;
begin
if TreeNode<>nil then
  begin
    TreeNode.imageIndex:=ClearIndex ;
    TreeNode.SelectedIndex :=ClearIndex;
  end;
  Child := TreeNode.GetFirstChild;
  while Child<>nil do
  begin
    Child.imageIndex:=ClearIndex;
    Child.SelectedIndex :=ClearIndex;
    ClearTreeNode(Child);
    Child := TreeNode.GetNextChild(Child);
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.InitTreeNode(TreeNode:TTreeNode);
var
  Child : TTreeNode;
begin
  if TreeNode<>nil then
  begin
    TreeNode.imageIndex:=ClearIndex ;
    TreeNode.SelectedIndex :=ClearIndex;
  end;
  Child := TreeNode.GetFirstChild;
  while Child<>nil do
  begin
    Child.imageIndex:=ClearIndex;
    Child.SelectedIndex :=ClearIndex;
    InitTreeNode(Child);
    Child := TreeNode.GetNextChild(Child);
  end;
end;



procedure TfaSMSetTreeParamsTemp_Dept.MultiSelectTreeNode(ParentNode,
  TreeNode: TTreeNode);
begin
  if TreeNode=TreeView.Items.GetFirstNode then   //如果是根节点
  begin
    if TreeNode.imageIndex=ClearIndex then
    begin
      SelectTreeNode(TreeNode);
      Include:=True;
    end else
    begin
      if TreeNode.GetFirstChild<>nil then
      begin
        if TreeNode.GetFirstChild.ImageIndex=ClearIndex then
        begin
          SelectTreeNode(TreeNode);
          Include:=True;
        end else
        begin
          Include:=False;
          ClearTreeNode(TreeNode);
        end;
      end;
    end;
  end else   //如果不是根节点
  begin
    if (TreeNode.imageIndex=ClearIndex)and(TreeNode.GetFirstChild<>nil) then
    begin
      Include:=True;
      //ClearParentAndBrotherNode(TreeView1.Items.GetFirstNode,TreeNode);
      SelectTreeNode(TreeNode);
    end else
    begin
      if TreeNode.GetFirstChild<>nil then   //是子跟节点
      begin
        if TreeNode.GetFirstChild.ImageIndex=ClearIndex then
        begin
          Include:=True;
          //ClearParentAndBrotherNode(TreeView1.Items.GetFirstNode,TreeNode);
          SelectTreeNode(TreeNode);
        end else
        begin
          Include:=False;
          ClearParentAndBrotherNode(TreeView.Items.GetFirstNode,TreeNode);
          ClearTreeNode(TreeNode);
        end;
      end else //叶子节点
      begin
        //Include:=False;
        //ClearParentAndBrotherNode(TreeView1.Items.GetFirstNode,TreeNode);
        if TreeNode.ImageIndex=ClearIndex then
        begin
          //Include:=True;
          //ClearParentAndBrotherNode(TreeView1.Items.GetFirstNode,TreeNode);
          SelectTreeNode(TreeNode);
        end else
        begin
          Include:=False;
          //ClearParentAndBrotherNode(TreeView1.Items.GetFirstNode,TreeNode);
          ClearTreeNode(TreeNode);
        end;
      end;
    end;
  end;
end;



procedure TfaSMSetTreeParamsTemp_Dept.SingleSelectTreeNode(ParentNode,TreeNode: TTreeNode);
var
  Child : TTreeNode;
begin
  if ParentNode<>nil then
  begin
    if ParentNode<>TreeNode then
    begin
      ParentNode.imageIndex:=ClearIndex;
      ParentNode.SelectedIndex :=ClearIndex;
    end else
    begin
      ParentNode.SelectedIndex :=SelectIndex;
      ParentNode.imageIndex:=SelectIndex;
    end;
  end;
  Child := ParentNode.GetFirstChild;
  while Child<>nil do
  begin
    if Child<>TreeNode then
    begin
      Child.imageIndex:=ClearIndex;
      Child.SelectedIndex :=ClearIndex;
    end else
    begin
      Child.imageIndex:=SelectIndex;
      Child.SelectedIndex :=SelectIndex;
    end;
    SingleSelectTreeNode(Child,TreeNode);
    Child := ParentNode.GetNextChild(Child);
  end

end;

procedure TfaSMSetTreeParamsTemp_Dept.CheckImageIndex(AnItem: TTreeNode);
var
  Father: TTreeNode;
  Child:  TTreeNode;
begin
        if  AnItem.Parent=nil then exit;
        Father:= AnItem.Parent;
        Child := Father.GetFirstChild;
        TreeView.Items.BeginUpdate;
     try
           begin
              if  Child.ImageIndex=ClearIndex then
                begin
                    Child:= Father.GetNextChild(Child);
                      Father.ImageIndex :=ClearIndex;
                  while (Child <>nil) do
                  begin
                    if ((Child.ImageIndex=SelectIndex) or (Child.ImageIndex=NotAllSelectIndex)) then
                       Father.ImageIndex:= NotAllSelectIndex ;

                      Child:= Father.GetNextChild(Child);
                  end;
                end  else
                if  Child.ImageIndex=selectIndex then
                begin
                      Child:= Father.GetNextChild(Child);
                      Father.ImageIndex :=selectIndex;
                  while (Child <>nil) do
                  begin
                    if ((Child.ImageIndex=ClearIndex) or (Child.ImageIndex=NotAllSelectIndex)) then
                       Father.ImageIndex:= NotAllSelectIndex;

                       Child:= Father.GetNextChild(Child);
                  end;
                end  else
                if   Child.ImageIndex=NotAllSelectIndex then
                       Father.ImageIndex:= NotAllSelectIndex;
           end;
    finally
      TreeView.Items.EndUpdate;
                 if  AnItem.parent.Parent<>nil then
          CheckImageIndex(Father);
    end;

end;



procedure TfaSMSetTreeParamsTemp_Dept.UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
begin
  if not FCanEdit then Exit;
  if (AnItem<>nil) and ([htOnStateIcon,htOnIcon,htOnItem]*MyHitTest<>[]) then
  begin
    TreeView.Items.BeginUpdate;
    try
      begin
           if ((AnItem.ImageIndex =ClearIndex) or (AnItem.ImageIndex =NotAllSelectIndex)) then
                SelectTreeNode(AnItem)
           else if   AnItem.ImageIndex =SelectIndex then
            ClearTreeNode(AnItem);
      end;
    finally
      TreeView.Items.EndUpdate;
    end;
  end;
end;



procedure TfaSMSetTreeParamsTemp_Dept.InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
var
  I: Integer;
  Node: TTreeNode;
  InfoData: TTreeNodeInfoData;
begin
  // 创建对应的数据对象
  InfoData := TTreeNodeInfoData.Create(AInfo.MetaNode);
  FList.Add(InfoData);
  Node := TreeView.Items.AddChildObject(Parent,InfoData.GetCaption,InfoData);
  Node.ImageIndex:=ClearIndex;
  // 如果包含子节点，构造它们
  if AInfo is TUIInfoGroup then
    for I := 0 to TUIInfoGroup(AInfo).Count - 1 do
      InternalBuildTree(TUIInfoGroup(AInfo).Items[I],Node);
end;


procedure TfaSMSetTreeParamsTemp_Dept.BuildTree;
begin
  TreeView.Items.BeginUpdate;
  try
    TreeView.Items.Clear;
    if FInfoAdmin=nil then Exit;
    ReadTreeInfoFromDataSet(FDataSet,FInfoAdmin);
    InternalBuildTree(FInfoAdmin.Root, nil);
    TreeView.FullExpand ;
  finally
    TreeView.Items.EndUpdate;
  end;
end;


constructor TfaSMSetTreeParamsTemp_Dept.Create(AOwner: TComponent);
begin
  inherited;
  if FInfoAdmin<>nil then
  begin
    FInfoAdmin.Free ;
  end;
  FInfoAdmin := TInfoAdmin.Create;

  DataGrid := Grid;
  FStatus := ssBrowse;
  FCanEdit := True;
  FCanDelete := True;
  FCanAdd := True;
  FCanChange := True;
  FAutoRefresh := True;
  TreeView.ControlStyle := TreeView.ControlStyle - [csDoubleClicks];
  FList := TObjectList.Create;
  FCanEdit := True;
  FSingleSelect:=False;
  Include:=False;
  FBranchNo:='';

  FDataSet:=TDataSet.Create(nil);
end;



procedure TfaSMSetTreeParamsTemp_Dept.btnAddClick(Sender: TObject);
var
  curr : TTreeNode;
begin
  curr := TreeView.Selected;
  if curr=nil then exit;

  /// 下级与同级都是继承当前选择的节点的信息
  if RbtnAddChild.Checked then
  begin
    //FCurrentID:=StrToInt(TTreeNodeInfoData(curr.Data).GetID)
    FCurrentID:=TTreeNodeInfoData(curr.Data).GetID
  end
  else
  if RBtnAddBrother.Checked then
  begin
    //FCurrentID:=StrToInt(TTreeNodeInfoData(TreeView.Selected.Data).GetID);
    if( curr.Parent <> nil ) then
      FCurrentID:=TTreeNodeInfoData(curr.Parent.Data).GetID
    else
      FCurrentID:=TTreeNodeInfoData(curr.Data).GetID
  end
  else Exit;

  GetCurrentDbGrid(FCurrentID);
  WorkView.FieldByName(FWorkViewParentFieldID).Data.SetString(FCurrentID);
  WorkView.SynchronizeCtrlsToFields;
  Status := ssAdd;
end;



procedure TfaSMSetTreeParamsTemp_Dept.Init;
var
  iwv:Integer;
  icomp:Integer;
  wv:TWorkView;
begin
  inherited;
  //FAutoRefresh := False;
  FAutoRefresh := True;
  ckAutoSetNewParams.Checked := True;
  FDepartmentFieldName := 'sbranch_code0';
  FDepartmentWVField := nil;
  FLocalDepartment := Context.ParamData(svDepartNoName).AsString;
  FMaintainType := pmtCenter;
  pcPages.ActivePageIndex := 0;
  //pcPages.OwnerDraw := True;
  tsEdit.Caption := SSet;
  TWinControlAccess(tsQuery).SelectFirst;
  CheckDataCanEdit; 
  //hanjiwei add it 20080422
  for icomp := 0 to Self.ComponentCount-1 do
  begin
    if Self.Components[icomp] is TWorkView then
    begin
      wv := TWorkView(Self.Components[icomp]);
      for iwv := 0 to wv.FieldCount-1 do
      begin
        if (wv.Fields[iwv].DataType = kdtInteger) or (wv.Fields[iwv].DataType = kdtFloat) then
          wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := 0
        else if wv.Fields[iwv].DataType = kdtstring then
          wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := '';
      end;
      wv.Reset;
    end;
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.btnChangeClick(Sender: TObject);
begin
  if TreeView.Selected=nil then exit;
  try
  FCurrentID:=TTreeNodeInfoData(TreeView.Selected.Data).GetID;
  GetCurrentDbGrid(FCurrentID);
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('Error-'+e.Message);
    end;
  end;
  Status := ssChange;
end;

procedure TfaSMSetTreeParamsTemp_Dept.SetStatus(const Value: TSettingStatus);
begin
  // 完成状态转换
  if FStatus <> Value then
  begin
    FStatus := Value;
    if FStatus=ssBrowse then
    begin
      // 浏览状态
      tsQuery.Enabled := True;
      tsEdit.Enabled := False;
      tsEdit.Caption := SSet;
      pcPages.ActivePageIndex := 0;
      TWinControlAccess(tsQuery).SelectFirst;
    end else
    begin
      tsQuery.Enabled := False;
      tsEdit.Enabled := True;
      pcPages.ActivePageIndex := 1;
      case Status of
        ssAdd : BeforeAdd;
        ssChange : BeforeChange;
        ssDelete : BeforeDelete;
        ssViewDetail : BeforeViewDetail{(True)};
      end;
      TWinControlAccess(tsEdit).SelectFirst;

    end;
    btnOK.Visible := Status in [ssAdd,ssChange,ssDelete];
    DBNavigator.Visible := Status = ssViewDetail;
    WorkView.CheckValid;
    StatusChanged;
    if (Status = ssDelete) and btnOK.Enabled and btnOK.Visible then btnOK.SetFocus;
  end;
end;


procedure TfaSMSetTreeParamsTemp_Dept.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSMSetTreeParamsTemp_Dept.BeforeAdd;
begin
  tsEdit.Caption := SAdd;
  // 所有的输入项目可以编辑
  EnableEditCtrls(True);
  // 初始化所有输入项目
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaSMSetTreeParamsTemp_Dept.BeforeChange;
begin
  tsEdit.Caption := SChange;
  // 所有的输入项目可以编辑
  // 由子类重载该方法，禁止主键可以编辑
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp_Dept.BeforeDelete;
begin
  tsEdit.Caption := SDelete;
  // 所有的输入项目都不可以编辑
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp_Dept.btnDeleteClick(Sender: TObject);
begin
  {
  case Context.GetDialogSystem.Confirm(Format('删除%s吗？',[GetCurrentRecordInfo])) of
    uaYes : DoDelete;
    uaNo : ;
    uaCancel : ;
  end;
  }
  if TreeView.Selected=nil then exit;
  FCurrentID:=TTreeNodeInfoData(TreeView.Selected.Data).GetID;
  GetCurrentDbGrid(FCurrentID);
  Status := ssDelete;
end;

function TfaSMSetTreeParamsTemp_Dept.GetCurrentRecordInfo: string;
begin
  Result := '';
end;

procedure TfaSMSetTreeParamsTemp_Dept.CancelEdit;
begin
  Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DoAdd;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DoChange;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DoDelete;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(DeleteRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DoQuery;
begin
  try
    CloseDataSet;
    WorkView.SynchronizeCtrlsToFields;
    SendQueryCommand;
  except
    //ShowMessage('hanjiwei --0');
    HandleException;
    //ShowMessage('hanjiwei --1');
    CloseDataSet;
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.SendQueryCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    QueryRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.btnOKClick(Sender: TObject);
var
  NeedDoRefresh : Boolean;
begin
  WorkView.SynchronizeCtrlsToFields;
  TWinControlAccess(tsEdit).SelectFirst;
  if btnOk.Enabled and ConfirmEdit then
  begin
    NeedDoRefresh := True;
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

          {
          Status := ssBrowse;
          NeedDoRefresh := False; // not Refresh
          }
        end;
    else
    begin
      Assert(False);
    end;
    end;
    //ShowMessage('hanjiwei --000');
    try
    if (Status=ssBrowse) and NeedDoRefresh and AutoRefresh then
    begin
      DoQuery;
    end;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('出错，请重新打开该功能--'+e.Message);
      end;
    end;
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.btnCancelClick(Sender: TObject);
begin
  CancelEdit;
end;

procedure TfaSMSetTreeParamsTemp_Dept.SendEditCommand(Request : TWVRequest);
begin
  FEditSucceed := True;
  try
    ShowWaiting(SWaitingOperation);
    Request.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.EnableEdit(CanEdit: Boolean);
begin
  //FCanEdit := CanEdit;
  //UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp_Dept.CheckReturnData(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TfaSMSetTreeParamsTemp_Dept.pcPagesDrawTab(Control: TCustomTabControl;
  TabIndex: Integer; const Rect: TRect; Active: Boolean);
var
  ARect : TRect;
begin
  if pcPages.Pages[TabIndex].Enabled then
    Control.Canvas.Font.Color := clWindowText else
    Control.Canvas.Font.Color := clGrayText;
  ARect := Rect;
  Windows.DrawText(Control.Canvas.Handle,PChar(pcPages.Pages[TabIndex].Caption),-1,
    ARect,DT_CENTER or DT_VCENTER or DT_SINGLELINE);
end;

procedure TfaSMSetTreeParamsTemp_Dept.EnableEditCtrls(AEnabled: Boolean);
{
var
  I : Integer;
  Ctrl : TControl;
}
begin
  {
  for I:=0 to tsEdit.ControlCount-1 do
  begin
    Ctrl := tsEdit.Controls[I];
    if not (Ctrl is TPageControl) then
      Ctrl.Enabled := AEnabled;
  end;
  UIPanel2.Enabled := True;
  }
  MakeChildrenReadOnly(tsEdit,not AEnabled);
  UIPanel2.Enabled := True;
  MakeChildrenReadOnly(UIPanel2,False);
end;

procedure TfaSMSetTreeParamsTemp_Dept.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  if Field=nil then
  begin
    CheckDataCanEdit;
    if Status=ssViewDetail then
      DisplayData;
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.SetCanAdd(const Value: Boolean);
begin
  FCanAdd := Value;
  UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp_Dept.SetCanChange(const Value: Boolean);
begin
  FCanChange := Value;
  UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp_Dept.SetCanDelete(const Value: Boolean);
begin
  FCanDelete := Value;
  UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp_Dept.UpdateButton;
begin
  FCanEdit := InternalGetCanEdit;
  btnAdd.Enabled := FCanEdit and CanAdd;
  btnDelete.Enabled := FCanEdit and CanDelete;
  btnChange.Enabled := FCanEdit and CanChange;
end;

procedure TfaSMSetTreeParamsTemp_Dept.CloseDataset;
begin
  inherited;
  if QueryBinder.Field<>nil then
    QueryBinder.Field.Data.Clear;
end;

function TfaSMSetTreeParamsTemp_Dept.InternalGetCanEdit: Boolean;
begin
  // 根据数据维护类型和当前营业部控制FCanEdit属性
  // 少数子类可以重载该方法，提供特殊的控制
{  case FMaintainType of
    pmtCenter : Result := IsCenterDepartment;
    pmtDepartment : Result := (FDepartmentWVField<>nil) and (FLocalDepartment=FDepartmentWVField.Data.AsString);
  else
    Result := False;
  end;
  }
  Result:=True;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DataSourceStateChange(Sender: TObject);
begin
  CheckDataCanEdit;
end;

procedure TfaSMSetTreeParamsTemp_Dept.CheckDataCanEdit;
var
  DepartField : TField;
  SameDepart : Boolean;
begin
  if (DataSource.DataSet=nil) or (DataSource.DataSet.IsEmpty) or not DataSource.DataSet.Active then
  begin
    //无查询结果数据，禁止修改、删除，允许增加
    FCanDelete := False;
    FCanChange := False;
    FCanAdd := True;
    btnViewDetail.Enabled := False;
  end else
  begin
    //有查询数据，
    if (FDepartmentFieldName<>'') and (FMaintainType=pmtDepartment) then
    begin
      // 如果是营业部维护数据，那么需要根据返回数据检查营业部，只能修改和删除本营业部的数据
      DepartField:= DataSource.DataSet.FindField(FDepartmentFieldName);
      SameDepart := (DepartField<>nil) and (DepartField.AsString=FLocalDepartment);
    end else
      // 否则不需要检查营业部，允许编辑
      SameDepart := True;
    FCanAdd := True;
    FCanDelete := SameDepart;
    FCanChange := SameDepart;
    btnViewDetail.Enabled := True;
  end;
  UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp_Dept.BeforeViewDetail{(IsFirst : Boolean=True)};
begin
  tsEdit.Caption := SViewDetail;
  // 所有的输入项目都不可以编辑
  EnableEditCtrls(False);
end;

procedure TfaSMSetTreeParamsTemp_Dept.btnViewDetailClick(Sender: TObject);
begin
  if (DataSource.DataSet<>nil) and (not DataSource.DataSet.IsEmpty) then
  begin
    if TreeView.Selected=nil then exit;
    FCurrentID:=TTreeNodeInfoData(TreeView.Selected.Data).GetID;
    GetCurrentDbGrid(FCurrentID);

    Status := ssViewDetail;
  end;
  if datasource.DataSet.RecNo = datasource.DataSet.RecordCount then
    datasource.DataSet.Last;
end;

procedure TfaSMSetTreeParamsTemp_Dept.GridDblClick(Sender: TObject);
begin
  if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
    Status := ssViewDetail;
end;

procedure TfaSMSetTreeParamsTemp_Dept.CheckEditFieldValid(WorkField: TWVField);
begin
  if not (status in [ssAdd, ssChange]) then
    WorkField.Valid := True;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DBNavigatorClick(Sender: TObject;
  Button: TNavigateBtn);
begin
  BeforeViewDetail;
  DisplayData;
end;

procedure TfaSMSetTreeParamsTemp_Dept.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSMSetTreeParamsTemp_Dept.StatusChanged;
begin
  if (Status in [ssChange,ssDelete,ssViewDetail]) then
    DisplayData
  else if (Status=ssAdd) and
    ckAutoSetNewParams.Checked and
    (WVDataSource.DataSource<>nil) and
    (WVDataSource.DataSource.Dataset<>nil) and
    not WVDataSource.DataSource.Dataset.IsEmpty
  then
    DisplayData;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DisplayData;
begin
  // 将数据从数据源同步到工作视图（再到各种控件）。注意：一些子类需要重载该方法，控制特殊控件的数据同步。
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp_Dept.SaveModifiedData;
begin
  // 将修改的数据同步到工作视图。如果使用特殊的控件需要重载此方法。
  WorkView.SynchronizeCtrlsToFields;
end;


procedure TfaSMSetTreeParamsTemp_Dept.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
    with Grid do
  begin
    if ((State = [gdSelected]) or (State=[gdSelected,gdFocused])) then
    begin
      Canvas.Font.Color :=ClYellow;
      Canvas.Brush.Color :=ClNavy;
    end
    else
    begin
      if DataSource.DataSet.RecNo mod 2<>0 then {判断当前数据是奇数还是偶数行}
      Canvas.brush.Color :=clInfoBk {如果是奇数行，DBGrid背景以白色显示}
    else
      Canvas.brush.Color :=$00EBDED0; {如果是偶数行$00EBDED0，DBGrid背景以浅灰色显示}
    end;
    DefaultDrawColumnCell(Rect, DataCol, Column, State); {这行很关键的，一定不要遗漏了}
  end;
  DBGridRecordSize(Column);

  if FDepartmentWVField=nil then Exit;
  if FDepartmentWVField.Data.AsString=CenterDepartNo then
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,'')
  else
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,FDepartmentFieldName);
end;

procedure TfaSMSetTreeParamsTemp_Dept.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_F8) then
  begin
     DBGridAutoSize(Grid);
  end;

  if (Key=VK_RETURN) and ([ssCtrl]=Shift) then
  begin
    Key := 0;
    if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
      Status := ssViewDetail;
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.alDatasetActionsExecute(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  if Action.HandlesTarget(DataSource) then
    Action.ExecuteTarget(DataSource);
end;

procedure TfaSMSetTreeParamsTemp_Dept.alDatasetActionsUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  Action.UpdateTarget(DataSource);
end;

function TfaSMSetTreeParamsTemp_Dept.ConfirmEdit: Boolean;
begin
  Result := True;
end;



procedure TfaSMSetTreeParamsTemp_Dept.TreeViewMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  MyHitTest : THitTests;
  AnItem: TTreeNode;
begin
  if Button <> mbLeft then Exit;
  MyHitTest := TreeView.GetHitTestInfoAt(X,Y);
  AnItem := TreeView.GetNodeAt(X, Y);
  if AnItem <> nil then
  begin
    UpdateStateIndex(AnItem,MyHitTest);
    CheckImageIndex(AnItem);
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.TreeViewDragDrop(Sender, Source: TObject;
  X, Y: Integer);
var   targetnode,sourcenode:TTreenode;
begin
  targetnode:=TreeView.getnodeat(x,y); //获得源节点
  sourcenode:=TreeView.selected; //获得目标节点
  //修改数据库中当前节点的父节点号parent_id，使其等目标节点标识号；
  TreeView.items.beginupdate; //禁用TreeView重绘操作
  try
    copynodeunder(TreeView,sourcenode,targetnode); //启动移动过程
    TreeView.selected:=targetnode;
  finally
    TreeView.items.endupdate; //重新设置
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.TreeViewDragOver(Sender, Source: TObject;
  X, Y: Integer; State: TDragState; var Accept: Boolean);
var  targetnode,sourcenode:TTreenode;
begin
  targetnode:=TreeView.getnodeat(x,y);
  if (Source=Sender) and (targetnode<>nil) then //保证移动在TreeView上，且目标节点不为空
  begin
  Accept:=true;
  sourcenode:=TreeView.selected;
  //以下代码防止用户将一个选项拖到其子项上（它会随着选项一起移动，导致死循环）
  while (targetnode.parent<>nil) and (targetnode <> sourcenode) do
  targetnode:=targetnode.parent;
  if (targetnode = sourcenode) then Accept:=false;
  end
  else Accept:=false;
end;

procedure TfaSMSetTreeParamsTemp_Dept.TreeViewDblClick(Sender: TObject);
begin
  btnViewDetailClick(Sender);
end;

procedure TfaSMSetTreeParamsTemp_Dept.TreeViewClick(Sender: TObject);
begin
  //ShowMessage('hanjiwei --000');
  Try
    FCurrentID:=TTreeNodeInfoData(TreeView.Selected.Data).GetID;
    GetCurrentDbGrid(FCurrentID);
  Except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('错误-'+e.Message);
    end;
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.pcPagesChanging(Sender: TObject;
  NewIndex: Integer; var AllowChange: Boolean);
begin
  if ((pcPages.ActivePageIndex=0) and (Status=ssBrowse))
    or ((pcPages.ActivePageIndex=1) and (Status<>ssBrowse)) then
    AllowChange := False;
end;

procedure TfaSMSetTreeParamsTemp_Dept.pcPagesPaintTabBackground(Sender: TObject;
  ACanvas: TCanvas; ATabIndex: Integer; const ARect: TRect;
  var Handled: Boolean);
var
  Rect : TRect;
begin
  if pcPages.Pages[ATabIndex].Enabled then
    ACanvas.Font.Color := clWindowText else
    ACanvas.Font.Color := clGrayText;
  Rect := ARect;
  Windows.DrawText(ACanvas.Handle,PChar(pcPages.Pages[ATabIndex].Caption),-1,
    Rect,DT_CENTER or DT_VCENTER or DT_SINGLELINE);

end;

end.
