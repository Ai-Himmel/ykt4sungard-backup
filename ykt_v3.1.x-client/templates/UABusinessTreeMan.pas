{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UtCardDll
   <What>实现树结构的构造

   <Written By>Yang ShiTao(杨士涛) Wang SuNa (王苏娜)
   <History>
**********************************************}


unit UABusinessTreeMan;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, WVDBBinders, WVCmdReq, WorkViews, Grids, DBGrids,
  StdCtrls, ImageCtrls, ExtCtrls, UICtrls, ComCtrls, ImgList,

  KSFrameWorks, KsBranchTree,KSClientConsts,Contnrs,KSFrames,
  USimpleQueryTemp;

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
    //wsn 20041214
    function    GetDescription :String;
    property    MetaNode: TKSMetaNode read FMetaNode;
  end;
                              
  TfaBusinessTreeMan = class(TKSFrame)
    ImageList: TImageList;
    TreeView: TTreeView;
    procedure TreeViewKeyPress(Sender: TObject; var Key: Char);
    procedure TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure TreeViewClick(Sender: TObject);
    procedure TreeViewDragDrop(Sender, Source: TObject; X, Y: Integer);
    procedure TreeViewDragOver(Sender, Source: TObject; X, Y: Integer;
      State: TDragState; var Accept: Boolean);
  private
    { Private declarations }
    FList: TObjectList;
    FCanEdit: Boolean;
    FBranchNo:string;
    Include:Boolean;

    protected
    { Proected declarations }
    procedure   InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
    procedure   UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
    procedure   CheckImageIndex(AnItem: TTreeNode);
    procedure   SingleSelectTreeNode(ParentNode,TreeNode : TTreeNode);
    procedure   MultiSelectTreeNode(ParentNode,TreeNode : TTreeNode);
  public
    { Public declarations }
    BranchName,IncludeName:string;
    FSingleSelect:Boolean;
    FWorkView:TWorkView;

    FDataSet:TDataSet;
    FDataSetFieldName:String; {树节点名称字段名}
    FDataSetFieldID:String;{树节点ID的字段名}
    FDataSetParentFieldID:String;{父节点id字段名}
    FDataSetFieldDes:String;{节点的描述信息}

    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    {构造树}
    procedure   BuildTree;
    property    CanEdit : Boolean read FCanEdit write FCanEdit;
    procedure   InitTreeNode(TreeNode:TTreeNode);   //清空所有营业部选中状态
    procedure   ClearTreeNode(TreeNode:TTreeNode);  //清空所有子营业部选中状态
    procedure   SelectTreeNode(TreeNode:TTreeNode); //选中自身或所有子营业部
    procedure   ClearParentAndBrotherNode(ParentNode,TreeNode:TTreeNode); //清空所有父和兄弟选中状态
    {从数据集中读取树结构的信息}
    procedure   ReadTreeInfoFromDataSet(DataSet: TDataSet;CInfoAdmin:TInfoAdmin);
    procedure   CopyNodeUnder(treeview:TTreeview;sourcenode,targetnode:ttreenode);
    {遍历数结构取出最小级别}
    procedure GetCurrentLevel(TreeNode:TTreeNode;var ACurrentLevel:Integer);
  end;

var
  faBusinessTreeMan: TfaBusinessTreeMan;

implementation
 uses SafeCode, KSFrameWorkUtils, KSKeyboard;

{$R *.DFM}

{ TfaAuth }


procedure TfaBusinessTreeMan.GetCurrentLevel(TreeNode:TTreeNode;var ACurrentLevel:Integer);
var
  Child : TTreeNode;
begin
  {
  if TreeNode<>nil then
  begin
    if (TreeNode.Level<ACurrentLevel ) and
       (TreeNode.ImageIndex=selectIndex) then
    begin
      ACurrentLevel:= TreeNode.Level;
    end;
  end;
  //ShowMessage(TreeNode.text);
  if ( TreeNode = nil ) then
    Exit;
  {
  Child := TreeNode.GetFirstChild;
  while Child<>nil do
  begin
    GetCurrentLevel(Child,ACurrentLevel);
    Child := TreeNode.GetNextChild(Child);
  end;
  }
  Child := TreeNode;
  while Child <> nil do
  begin
    if (Child.Level<ACurrentLevel ) and
       (Child.ImageIndex=selectIndex) then
    begin
      ACurrentLevel:= Child.Level;
      Exit;
    end;
    GetCurrentLevel(Child.getFirstChild,ACurrentLevel);
    Child := Child.getNextSibling;
  end;

end;




procedure TfaBusinessTreeMan.CopyNodeUnder(treeview:TTreeview;sourcenode,targetnode:ttreenode);
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


procedure TfaBusinessTreeMan.ReadTreeInfoFromDataSet(DataSet: TDataSet;CInfoAdmin:TInfoAdmin);
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
      if FDataSetFieldDes<>'' then
        LastNode.Description :=DataSet.FieldByName(FDataSetFieldDes).AsString;
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



constructor TfaBusinessTreeMan.Create(AOwner: TComponent);
begin
  inherited;
  CheckObject(InfoAdmin,'Error : InfoAdmin not init');
  TreeView.ControlStyle := TreeView.ControlStyle - [csDoubleClicks];
  FList := TObjectList.Create;
  FCanEdit := True;
  FSingleSelect:=False;
  Include:=False;
  FBranchNo:='';
end;



destructor TfaBusinessTreeMan.Destroy;
begin
  FList.Free;
  //InfoAdmin.Free;
  inherited;
end;

procedure TfaBusinessTreeMan.BuildTree;
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

procedure TfaBusinessTreeMan.InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
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

procedure TfaBusinessTreeMan.TreeViewKeyPress(Sender: TObject; var Key: Char);
begin
{  Edit1.text:=TreeView.Selected.Text;
  if Key = ' ' then
    UpdateStateIndex(TreeView.Selected, [htOnStateIcon]);
  Key := #0;
}
end;

procedure TfaBusinessTreeMan.TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
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

procedure TfaBusinessTreeMan.CheckImageIndex(AnItem: TTreeNode);
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



procedure TfaBusinessTreeMan.UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
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

procedure TfaBusinessTreeMan.SingleSelectTreeNode(ParentNode,TreeNode: TTreeNode);
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

procedure TfaBusinessTreeMan.InitTreeNode(TreeNode:TTreeNode);
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

{ TTreeNodeInfoData }

constructor TTreeNodeInfoData.Create(AMetaNode: TKSMetaNode);
begin
  Assert(AMetaNode<>nil);
  inherited Create;
  FMetaNode := AMetaNode;
end;

function  TTreeNodeInfoData.GetDescription :String;
begin
  Result := FMetaNode.Description;
end;

function TTreeNodeInfoData.GetCaption: string;
begin
  Result := FMetaNode.Caption;
end;

function TTreeNodeInfoData.GetID: string;
begin
  Result := FMetaNode.Id ;
end;

procedure TfaBusinessTreeMan.MultiSelectTreeNode(ParentNode,
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

procedure TfaBusinessTreeMan.ClearTreeNode(TreeNode: TTreeNode);
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

procedure TfaBusinessTreeMan.SelectTreeNode(TreeNode: TTreeNode);
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

procedure TfaBusinessTreeMan.ClearParentAndBrotherNode(ParentNode,TreeNode: TTreeNode);
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

procedure TfaBusinessTreeMan.TreeViewClick(Sender: TObject);
begin
  if TreeView.Items.Count=0 then Exit;
  if TreeView.Selected=nil then Exit;
end;

procedure TfaBusinessTreeMan.TreeViewDragDrop(Sender, Source: TObject; X,
  Y: Integer);
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

procedure TfaBusinessTreeMan.TreeViewDragOver(Sender, Source: TObject; X,
  Y: Integer; State: TDragState; var Accept: Boolean);
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


initialization
  TUIStdClassFactory.Create('商户树',TfaBusinessTreeMan);

end.



