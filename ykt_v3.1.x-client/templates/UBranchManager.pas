unit UBranchManager;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation
   <Unit>UBranchManager
   <What>营业部管理控件
   <Written By> 周耀亮
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ImgList, ComCtrls, WVCmdReq, WorkViews, KsBranchTree,Contnrs;

const

  selectIndex = 0;
  NoSelectIndex = 1;
  ClearIndex = -1;

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

  TfaBranchMan = class(TFrame)
    TreeView: TTreeView;
    ImageList: TImageList;
    procedure TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure TreeViewKeyPress(Sender: TObject; var Key: Char);
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
    procedure   SingleSelectTreeNode(ParentNode,TreeNode : TTreeNode);
    procedure   MultiSelectTreeNode(ParentNode,TreeNode : TTreeNode);
  public
    { Public declarations }
    BranchName,IncludeName:string;
    FSingleSelect:Boolean;
    FWorkView:TWorkView;
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    // 构造树
    procedure   BuildTree;
    property    CanEdit : Boolean read FCanEdit write FCanEdit;
    procedure   InitTreeNode(TreeNode:TTreeNode);   //清空所有营业部选中状态
    procedure   ClearTreeNode(TreeNode:TTreeNode);  //清空所有子营业部选中状态
    procedure   SelectTreeNode(TreeNode:TTreeNode); //选中自身或所有子营业部
    procedure   ClearParentAndBrotherNode(ParentNode,TreeNode:TTreeNode); //清空所有父和兄弟选中状态
    procedure   SynchronizeData;
  end;

implementation

uses SafeCode, KSFrameWorkUtils, KSKeyboard, KSClientConsts;

{$R *.DFM}

{ TfaAuth }

constructor TfaBranchMan.Create(AOwner: TComponent);
begin
  inherited;
  CheckObject(InfoAdmin,'Error : InfoAdmin not init');
  TreeView.ControlStyle := TreeView.ControlStyle - [csDoubleClicks];
  FList := TObjectList.Create;
  FCanEdit := True;
  FSingleSelect:=True;
  Include:=False;
  FBranchNo:='';
//  BranchName:='营业部';
//  IncludeName:='包含子营业部';
end;

destructor TfaBranchMan.Destroy;
begin
  FList.Free;
  inherited;
end;

procedure TfaBranchMan.BuildTree;
begin
  TreeView.Items.BeginUpdate;
  try
    TreeView.Items.Clear;
    InternalBuildTree(InfoAdmin.Root, nil);
    TreeView.FullExpand ;
  finally
    TreeView.Items.EndUpdate;
  end;
end;

procedure TfaBranchMan.InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
var
  I: Integer;
  Node: TTreeNode;
  InfoData: TTreeNodeInfoData;
begin
  // 创建对应的数据对象
  InfoData := TTreeNodeInfoData.Create(AInfo.MetaNode);
  FList.Add(InfoData);
  Node := TreevIew.Items.AddChildObject(Parent,InfoData.GetCaption,InfoData);
  // 如果包含子节点，构造它们
  if AInfo is TUIInfoGroup then
    for I := 0 to TUIInfoGroup(AInfo).Count - 1 do
      InternalBuildTree(TUIInfoGroup(AInfo).Items[I],Node);
end;

procedure TfaBranchMan.TreeViewKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = ' ' then
    UpdateStateIndex(TreeView.Selected, [htOnStateIcon]);
  Key := #0;
end;

procedure TfaBranchMan.TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  MyHitTest : THitTests;
  AnItem: TTreeNode;
begin
  if Button <> mbLeft then Exit;
  MyHitTest := TreeView.GetHitTestInfoAt(X,Y);
  AnItem := TreeView.GetNodeAt(X, Y);
  UpdateStateIndex(AnItem,MyHitTest);
end;


procedure TfaBranchMan.UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
begin
  if not FCanEdit then Exit;
  if (AnItem<>nil) and ([htOnStateIcon,htOnIcon,htOnItem]*MyHitTest<>[]) then
  begin
    TreeView.Items.BeginUpdate;
    try
      if TreeView.Items.Count<=1 then
      begin
        Include:=False;
        FBranchNo:=TTreeNodeInfoData(AnItem.Data).GetID;
        SingleSelectTreeNode(TreeView.Items.GetFirstNode,AnItem);
      end else
      begin
        if FSingleSelect then
        begin
          Include:=False;
          FBranchNo:=TTreeNodeInfoData(AnItem.Data).GetID;
          SingleSelectTreeNode(TreeView.Items.GetFirstNode,AnItem);
        end else
        begin
          FBranchNo:=TTreeNodeInfoData(AnItem.Data).GetID;
          MultiSelectTreeNode(TreeView.Items.GetFirstNode,AnItem);
        end;
      end;
      SynchronizeData;
    finally
      TreeView.Items.EndUpdate;
    end;
  end;
{  showmessage(FBranchNo);
  if include then showmessage('true')
  else showmessage('False');}
end;

procedure TfaBranchMan.SingleSelectTreeNode(ParentNode,TreeNode: TTreeNode);
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

procedure TfaBranchMan.InitTreeNode(TreeNode:TTreeNode);
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

function TTreeNodeInfoData.GetCaption: string;
begin
  Result := FMetaNode.Caption;
end;

function TTreeNodeInfoData.GetID: string;
begin
  Result := FMetaNode.Id ;
end;

procedure TfaBranchMan.MultiSelectTreeNode(ParentNode,
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
      ClearParentAndBrotherNode(TreeView.Items.GetFirstNode,TreeNode);
      SelectTreeNode(TreeNode);
    end else
    begin
      if TreeNode.GetFirstChild<>nil then   //是子跟节点
      begin
        if TreeNode.GetFirstChild.ImageIndex=ClearIndex then
        begin
          Include:=True;
          ClearParentAndBrotherNode(TreeView.Items.GetFirstNode,TreeNode);
          SelectTreeNode(TreeNode);
        end else
        begin
          Include:=False;
          ClearParentAndBrotherNode(TreeView.Items.GetFirstNode,TreeNode);
          ClearTreeNode(TreeNode);
        end;
      end else //叶子节点
      begin
        Include:=False;
        ClearParentAndBrotherNode(TreeView.Items.GetFirstNode,TreeNode);
      end;
    end;
  end;
end;

procedure TfaBranchMan.ClearTreeNode(TreeNode: TTreeNode);
var
  Child : TTreeNode;
begin
  Child := TreeNode.GetFirstChild;
  while Child<>nil do
  begin
    Child.imageIndex:=ClearIndex;
    Child.SelectedIndex :=ClearIndex;
    ClearTreeNode(Child);
    Child := TreeNode.GetNextChild(Child);
  end;
end;

procedure TfaBranchMan.SelectTreeNode(TreeNode: TTreeNode);
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

procedure TfaBranchMan.ClearParentAndBrotherNode(ParentNode,TreeNode: TTreeNode);
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

procedure TfaBranchMan.SynchronizeData;
begin
  if FWorkView<>nil then
  begin
    if FWorkView.FindField(BranchName)<>nil  then
       FWorkView.FieldByName(BranchName).Data.Value:=FBranchNo;
    if FWorkView.FindField(IncludeName)<>nil then
    begin
      if Include then FWorkView.FieldByName(IncludeName).Data.Value:=1
      else  FWorkView.FieldByName(IncludeName).Data.Value:=0;
    end;
  end
end;

end.

