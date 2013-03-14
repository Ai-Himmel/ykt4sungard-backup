unit USMSetTreeParamsTemp;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USetParamsTemp
   <What>参数设置操作界面模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, KSFrameWorks, KSFrames, KSClientConsts,
  ComCtrls, Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVDBBinders, WVCmdReq, WorkViews, Db, WVCommands, DBCtrls, DBActns,
  ActnList, RzDBGrid, RzTabs, RzDBNav, RzButton, RzRadChk, RzTreeVw,
  KsBranchTree,contnrs,Dialogs, Mask, WVCtrls;
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

  TfaSMSetTreeParamsTemp = class(TKSFrame)
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
    btnOK: TImageButton;
    btnCancel: TImageButton;
    DBNavigator: TRzDBNavigator;
    ImageButton1: TImageButton;
    ImageButton2: TImageButton;
    UIPanel1: TUIPanel;
    btnQuery: TImageButton;
    btnAdd: TImageButton;
    btnChange: TImageButton;
    btnDelete: TImageButton;
    btnViewDetail: TImageButton;
    ckAutoSetNewParams: TRzCheckBox;
    TreeView: TRzTreeView;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    Button1: TButton;
    WorkView: TWorkView;
    Grid: TRzDBGrid;
    procedure   btnAddClick(Sender: TObject);
    procedure   btnChangeClick(Sender: TObject);
    procedure   pcPagesChanging(Sender: TObject; var AllowChange: Boolean);
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
    procedure TreeViewClick(Sender: TObject);
    procedure TreeViewDragDrop(Sender, Source: TObject; X, Y: Integer);
    procedure TreeViewDragOver(Sender, Source: TObject; X, Y: Integer;
      State: TDragState; var Accept: Boolean);
    procedure Button1Click(Sender: TObject);
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

    FCurrentParentID:Integer; {当前编辑节点的父ID}
    FCurrentID:Integer; {当前编辑节点的ID}

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

    procedure   InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
    procedure   UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
    procedure   CheckImageIndex(AnItem: TTreeNode);
    procedure   SingleSelectTreeNode(ParentNode,TreeNode : TTreeNode);
    procedure   MultiSelectTreeNode(ParentNode,TreeNode : TTreeNode);


  public
    BranchName,IncludeName:string;
    FSingleSelect:Boolean;
    FWorkView:TWorkView;

    FDataSet:TDataSet;
    FDataSetFieldName:String; {树节点名称字段名}
    FDataSetFieldID:String;{树节点ID的字段名}
    FDataSetParentFieldID:String;{父节点id字段名}

    constructor Create(AOwner : TComponent); override;
    destructor Destroy;

    procedure   BuildTree;
    property    CanEdit : Boolean read FCanEdit write FCanEdit;
    procedure   InitTreeNode(TreeNode:TTreeNode);   //清空所有营业部选中状态
    procedure   ClearTreeNode(TreeNode:TTreeNode);  //清空所有子营业部选中状态
    procedure   SelectTreeNode(TreeNode:TTreeNode); //选中自身或所有子营业部
    procedure   ClearParentAndBrotherNode(ParentNode,TreeNode:TTreeNode); //清空所有父和兄弟选中状态
    {从数据集中读取树结构的信息}
    procedure   ReadTreeInfoFromDataSet(DataSet: TDataSet;InfoAdmin:TInfoAdmin);
    {拖放功能中复制节点}
    procedure   CopyNodeUnder(treeview:TRzTreeview;sourcenode,targetnode:ttreenode);

    procedure   CloseDataset; override;
    property    Status : TSettingStatus read FStatus write SetStatus;
    property    AutoRefresh : Boolean read FAutoRefresh write FAutoRefresh default True;
    property    CanAdd : Boolean read FCanAdd write SetCanAdd default True;
    property    CanChange : Boolean read FCanChange write SetCanChange default True;
    property    CanDelete : Boolean read FCanDelete write SetCanDelete default True;
    property    MaintainType : TParamMaintainType read FMaintainType;
  end;

var
  faSMSetTreeParamsTemp: TfaSMSetTreeParamsTemp;

implementation

uses KSFrameWorkUtils, DataUsageUtils, LogFile;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);

{ TfaSMSetTreeParamsTemp }

destructor TfaSMSetTreeParamsTemp.Destroy;
begin
  FList.Free;
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

procedure TfaSMSetTreeParamsTemp.CopyNodeUnder(treeview:TRzTreeview;sourcenode,targetnode:ttreenode);
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

procedure TfaSMSetTreeParamsTemp.ReadTreeInfoFromDataSet(DataSet: TDataSet;InfoAdmin:TInfoAdmin);
var
  LastNode,Node: TKSMetaNode;
  Structure:TKSTreeStructure;
begin
  LastNode:=nil;
  try
    InfoAdmin.InfoList.Clear;
    InfoAdmin.StructureList.Clear;
    Assert(DataSet<>nil);
    DataSet.first;
    while not DataSet.Eof do
    begin
      LastNode := TKSMetaNode.Create;              //树节点的名称和代码集合
      LastNode.ID := DataSet.FieldByName(FDataSetFieldID).AsString;
      LastNode.Caption := DataSet.FieldByName(FDataSetFieldName).AsString; //
      LastNode.Description :='';
      LastNode.NodeType := '';
      InfoAdmin.InfoList.Add(LastNode);
      LastNode := nil;
      DataSet.Next;
    end;
    DataSet.first;
    while not DataSet.Eof do
    begin
      Node := InfoAdmin.InfoList.Find(DataSet.FieldByName(FDataSetFieldID).AsString);   //
      if Node<>nil then
      begin
        Structure := TKSTreeStructure.Create;
        InfoAdmin.StructureList.Add(Structure);  //树上级节点代码集合
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
          LastNode:= InfoAdmin.InfoList.Find(DataSet.FieldByName(FDataSetParentFieldID).AsString); 
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
  InfoAdmin.Init;
end;




procedure TfaSMSetTreeParamsTemp.ClearParentAndBrotherNode(ParentNode,TreeNode: TTreeNode);
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



procedure TfaSMSetTreeParamsTemp.SelectTreeNode(TreeNode: TTreeNode);
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


procedure TfaSMSetTreeParamsTemp.ClearTreeNode(TreeNode: TTreeNode);
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

procedure TfaSMSetTreeParamsTemp.InitTreeNode(TreeNode:TTreeNode);
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



procedure TfaSMSetTreeParamsTemp.MultiSelectTreeNode(ParentNode,
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



procedure TfaSMSetTreeParamsTemp.SingleSelectTreeNode(ParentNode,TreeNode: TTreeNode);
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

procedure TfaSMSetTreeParamsTemp.CheckImageIndex(AnItem: TTreeNode);
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



procedure TfaSMSetTreeParamsTemp.UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
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



procedure TfaSMSetTreeParamsTemp.InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
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


procedure TfaSMSetTreeParamsTemp.BuildTree;
begin
  TreeView.Items.BeginUpdate;
  try
    TreeView.Items.Clear;
    ReadTreeInfoFromDataSet(Self.FDataSet,InfoAdmin);
    InternalBuildTree(InfoAdmin.Root, nil);
    TreeView.FullExpand ;
  finally
    TreeView.Items.EndUpdate;
  end;
end;


constructor TfaSMSetTreeParamsTemp.Create(AOwner: TComponent);
begin
  inherited;
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
end;

procedure TfaSMSetTreeParamsTemp.btnAddClick(Sender: TObject);
begin
  if TreeView.Selected=nil then exit;
  Status := ssAdd;
//  AddMark:=False;
  FCurrentParentID:=StrToInt(TTreeNodeInfoData(TreeView.Selected.Data).GetID);
  inherited;
end;

procedure TfaSMSetTreeParamsTemp.Init;
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
end;

procedure TfaSMSetTreeParamsTemp.btnChangeClick(Sender: TObject);
begin
  Status := ssChange;
  FCurrentID:=StrToInt(TTreeNodeInfoData(TreeView.Selected.Data).GetID);
  inherited;
end;

procedure TfaSMSetTreeParamsTemp.SetStatus(const Value: TSettingStatus);
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

procedure TfaSMSetTreeParamsTemp.pcPagesChanging(Sender: TObject;
  var AllowChange: Boolean);
begin
  if ((pcPages.ActivePageIndex=0) and (Status=ssBrowse))
    or ((pcPages.ActivePageIndex=1) and (Status<>ssBrowse)) then
    AllowChange := False;
end;

procedure TfaSMSetTreeParamsTemp.btnQueryClick(Sender: TObject);
begin
  WorkView.SynchronizeCtrlsToFields;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSMSetTreeParamsTemp.BeforeAdd;
begin
  tsEdit.Caption := SAdd;
  // 所有的输入项目可以编辑
  EnableEditCtrls(True);
  // 初始化所有输入项目
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaSMSetTreeParamsTemp.BeforeChange;
begin
  tsEdit.Caption := SChange;
  // 所有的输入项目可以编辑
  // 由子类重载该方法，禁止主键可以编辑
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp.BeforeDelete;
begin
  tsEdit.Caption := SDelete;
  // 所有的输入项目都不可以编辑
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp.btnDeleteClick(Sender: TObject);
begin
  {
  case Context.GetDialogSystem.Confirm(Format('删除%s吗？',[GetCurrentRecordInfo])) of
    uaYes : DoDelete;
    uaNo : ;
    uaCancel : ;
  end;
  }
  Status := ssDelete;
end;

function TfaSMSetTreeParamsTemp.GetCurrentRecordInfo: string;
begin
  Result := '';
end;

procedure TfaSMSetTreeParamsTemp.CancelEdit;
begin
  Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp.DoAdd;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp.DoChange;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp.DoDelete;
begin
  // 同步修改的数据到工作视图，提交请求，如果成功(FEditSucceed=True而且没有意外抛出)，恢复状态为浏览
  SaveModifiedData;
  SendEditCommand(DeleteRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp.DoQuery;
begin
  try
    CloseDataSet;
    WorkView.SynchronizeCtrlsToFields;
    SendQueryCommand;
  except
    HandleException;
    CloseDataSet;
  end;
end;

procedure TfaSMSetTreeParamsTemp.SendQueryCommand;
begin
  try
    ShowWaiting(SWaitingQuery);
    QueryRequest.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSMSetTreeParamsTemp.btnOKClick(Sender: TObject);
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
    else  Assert(False);
    end;
    if (Status=ssBrowse) and NeedDoRefresh and AutoRefresh then
      DoQuery;
  end;
end;

procedure TfaSMSetTreeParamsTemp.btnCancelClick(Sender: TObject);
begin
  CancelEdit;
end;

procedure TfaSMSetTreeParamsTemp.SendEditCommand(Request : TWVRequest);
begin
  FEditSucceed := True;
  try
    ShowWaiting(SWaitingOperation);
    Request.SendCommand;
  finally
    CloseWaiting;
  end;
end;

procedure TfaSMSetTreeParamsTemp.EnableEdit(CanEdit: Boolean);
begin
  //FCanEdit := CanEdit;
  //UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp.CheckReturnData(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TfaSMSetTreeParamsTemp.pcPagesDrawTab(Control: TCustomTabControl;
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

procedure TfaSMSetTreeParamsTemp.EnableEditCtrls(AEnabled: Boolean);
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

procedure TfaSMSetTreeParamsTemp.DataSourceDataChange(Sender: TObject;
  Field: TField);
begin
  if Field=nil then
  begin
    CheckDataCanEdit;
    if Status=ssViewDetail then
      DisplayData;
  end;
end;

procedure TfaSMSetTreeParamsTemp.SetCanAdd(const Value: Boolean);
begin
  FCanAdd := Value;
  UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp.SetCanChange(const Value: Boolean);
begin
  FCanChange := Value;
  UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp.SetCanDelete(const Value: Boolean);
begin
  FCanDelete := Value;
  UpdateButton;
end;

procedure TfaSMSetTreeParamsTemp.UpdateButton;
begin
  FCanEdit := InternalGetCanEdit;
  btnAdd.Enabled := FCanEdit and CanAdd;
  btnDelete.Enabled := FCanEdit and CanDelete;
  btnChange.Enabled := FCanEdit and CanChange;
end;

procedure TfaSMSetTreeParamsTemp.CloseDataset;
begin
  inherited;
  if QueryBinder.Field<>nil then
    QueryBinder.Field.Data.Clear;
end;

function TfaSMSetTreeParamsTemp.InternalGetCanEdit: Boolean;
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

procedure TfaSMSetTreeParamsTemp.DataSourceStateChange(Sender: TObject);
begin
  CheckDataCanEdit;
end;

procedure TfaSMSetTreeParamsTemp.CheckDataCanEdit;
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

procedure TfaSMSetTreeParamsTemp.BeforeViewDetail{(IsFirst : Boolean=True)};
begin
  tsEdit.Caption := SViewDetail;
  // 所有的输入项目都不可以编辑
  EnableEditCtrls(False);
end;

procedure TfaSMSetTreeParamsTemp.btnViewDetailClick(Sender: TObject);
begin
  if (DataSource.DataSet<>nil) and (not DataSource.DataSet.IsEmpty) then
    Status := ssViewDetail;
end;

procedure TfaSMSetTreeParamsTemp.GridDblClick(Sender: TObject);
begin
  if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
    Status := ssViewDetail;
end;

procedure TfaSMSetTreeParamsTemp.CheckEditFieldValid(WorkField: TWVField);
begin
  if not (status in [ssAdd, ssChange]) then
    WorkField.Valid := True;
end;

procedure TfaSMSetTreeParamsTemp.DBNavigatorClick(Sender: TObject;
  Button: TNavigateBtn);
begin
  //BeforeViewDetail(False);
  //DisplayData;
end;

procedure TfaSMSetTreeParamsTemp.InitEx;
begin
  inherited;
  if btnQuery.Enabled then
    DoQuery;
end;

procedure TfaSMSetTreeParamsTemp.StatusChanged;
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

procedure TfaSMSetTreeParamsTemp.DisplayData;
begin
  // 将数据从数据源同步到工作视图（再到各种控件）。注意：一些子类需要重载该方法，控制特殊控件的数据同步。
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp.SaveModifiedData;
begin
  // 将修改的数据同步到工作视图。如果使用特殊的控件需要重载此方法。
  WorkView.SynchronizeCtrlsToFields;
end;


procedure TfaSMSetTreeParamsTemp.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  if FDepartmentWVField=nil then Exit;
  if FDepartmentWVField.Data.AsString=CenterDepartNo then
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,'')
  else
    DrawCellForSysParams(TDBGrid(Sender),Rect,DataCol,Column,State,FDepartmentFieldName);
end;

procedure TfaSMSetTreeParamsTemp.GridKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key=VK_RETURN) and ([ssCtrl]=Shift) then
  begin
    Key := 0;
    if (DataSource.DataSet<>nil) and not DataSource.DataSet.IsEmpty and DataSource.DataSet.Active then
      Status := ssViewDetail;
  end;
end;

procedure TfaSMSetTreeParamsTemp.alDatasetActionsExecute(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  if Action.HandlesTarget(DataSource) then
    Action.ExecuteTarget(DataSource);
end;

procedure TfaSMSetTreeParamsTemp.alDatasetActionsUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  Action.UpdateTarget(DataSource);
end;

function TfaSMSetTreeParamsTemp.ConfirmEdit: Boolean;
begin
  Result := True;
end;



procedure TfaSMSetTreeParamsTemp.TreeViewMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  MyHitTest : THitTests;
  AnItem: TTreeNode;
begin
  if Button <> mbLeft then Exit;
  MyHitTest := TreeView.GetHitTestInfoAt(X,Y);
  AnItem := TreeView.GetNodeAt(X, Y);
  UpdateStateIndex(AnItem,MyHitTest);
  CheckImageIndex(AnItem);
//    Edit1.text:=TreeView.Selected.Text;

end;

procedure TfaSMSetTreeParamsTemp.TreeViewClick(Sender: TObject);
begin
  if TreeView.Items.Count=0 then Exit;
  if TreeView.Selected=nil then Exit;  
end;

procedure TfaSMSetTreeParamsTemp.TreeViewDragDrop(Sender, Source: TObject;
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

procedure TfaSMSetTreeParamsTemp.TreeViewDragOver(Sender, Source: TObject;
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

procedure TfaSMSetTreeParamsTemp.Button1Click(Sender: TObject);
var TreedateSet:TDataSet;
begin
  InfoAdmin:=TInfoAdmin.Create;

  TreedateSet:=TDataSet.Create(nil);
  Try
    TreedateSet:=(WorkView.FieldByName('查询结果集').Data.AsObject) as TDataSet;
    faSMSetTreeParamsTemp.FDataSetFieldID:='power_id';
    faSMSetTreeParamsTemp.FDataSetParentFieldID:='power_level';
    faSMSetTreeParamsTemp.FDataSetFieldName:='power_item';
    faSMSetTreeParamsTemp.FDataSet:= TreedateSet;
    faSMSetTreeParamsTemp.BuildTree;
  Finally
    TreedateSet.Free;
  end;
end;

end.
