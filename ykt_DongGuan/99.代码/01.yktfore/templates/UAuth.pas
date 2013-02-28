unit UAuth;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UAuth
   <What>权限树控件
   <Written By> 程用明
   <History>
   20030617 增加保存权限树到文本文件 黄燕来

**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ImgList, ComCtrls, WVCmdReq, WorkViews, KSMenuAdmin, Contnrs;

const
  NonLeafSelected = 11;
  NonLeafSelectedTick  = 0;
  NonLeafSelectedCross = 1;
  NonLeafSelectedOther = 2;

  LeafSelected = 12;
  LeafSelectedTick     = 3;
  LeafSelectedCross    = 4;
  LeafSelectedOther    = 5;

  TreeStateTick        = 6;
  TreeStateCross       = 7;

  FunctionSelected    = 8;
  FunctionStateTick    = 9;
  FunctionStateCross   = 10;
  FunctionStateNull    = -1;

  LineBreak = #13#10;
  GroupMenuTypeString = '+';
  MenuItemTypeString = '-';
  FunctionTypeString = '*';

  PermitStateString = '[V]';
  ForbidStateString = '[X]';
  MixStateString = '[?]';
  NoneStateString = '[ ]';

  ImageCount = 14;
  StateStringsForImageIndex : array[-1..ImageCount-1] of string
    = (
      NoneStateString,
      PermitStateString,
      ForbidStateString,
      MixStateString,
      PermitStateString,
      ForbidStateString,
      MixStateString,
      PermitStateString,
      ForbidStateString,
      NoneStateString,
      PermitStateString,
      ForbidStateString,
      NoneStateString,
      NoneStateString,
      MixStateString
      );

  CommentChar = '#';

type
  {
    <Class>TUserPrivilege
    <What>保存用户的菜单权限和功能权限位串，提供给TTreeNodeData对象使用
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TUserPrivilege = class
  private
    FMenuSet: string;
    FAuthSet: string;
    procedure   SetAuthSet(const Value: string);
    procedure   SetMenuSet(const Value: string);
  public
    constructor Create;
    property    AuthSet: string read FAuthSet write SetAuthSet;
    property    MenuSet: string read FMenuSet write SetMenuSet;
  end;

  // 子节点的状态
  TChildrenState = (
    csNone,       // 不确定
    csAllOk,      // 全部有效
    csAllBad,     // 全部无效
    csOkAndBad    // 部分有效，部分无效
    );

  {
    <Class>TTreeNodeData
    <What>抽象类。
    一个该类的实例对应一个TreeNode。
    该类管理一个菜单/功能的权限，包括显示和设置
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TTreeNodeData = class
  private
    FPrivilege: TUserPrivilege;
    FChildrenState: TChildrenState;
  protected

  public
    constructor Create(APrivilege : TUserPrivilege);
    function    GetImageIndex : Integer; virtual; abstract;
    function    GetStateIndex : Integer; virtual; abstract;
    function    GetCaption : string; virtual; abstract;
    function    HaveAuth : Integer; virtual; abstract;
    procedure   SetAuth(Authed : Integer); virtual; abstract;
    function    CanAuth : Boolean; virtual; abstract;
    property    Privilege : TUserPrivilege read FPrivilege;
    property    ChildrenState : TChildrenState read FChildrenState write FChildrenState;
  end;

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
  TTreeNodeMenuData = class(TTreeNodeData)
  private
    FMetaMenu: TKSMetaMenu;

  protected

  public
    constructor Create(APrivilege : TUserPrivilege; AMetaMenu: TKSMetaMenu);
    function    GetImageIndex : Integer; override;
    function    GetStateIndex : Integer; override;
    function    GetCaption : string; override;
    function    HaveAuth : Integer; override;
    procedure   SetAuth(AuthNo : Integer); override;
    function    CanAuth : Boolean; override;
    property    MetaMenu: TKSMetaMenu read FMetaMenu;

  end;

  {
    <Class>TTreeNodeFunctionData
    <What>对应功能项目
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TTreeNodeFunctionData = class(TTreeNodeData)
  private
    FMetaFunction: TKSMetaFunction;
  protected

  public
    constructor Create(APrivilege : TUserPrivilege; AMetaFunction: TKSMetaFunction);
    function    GetImageIndex : Integer; override;
    function    GetStateIndex : Integer; override;
    function    GetCaption : string; override;
    function    HaveAuth : Integer; override;
    procedure   SetAuth(AuthNO : Integer); override;
    function    CanAuth : Boolean; override;
    property    MetaFunction: TKSMetaFunction read FMetaFunction;
  end;

  TfaAuth = class(TFrame)
    TreeView: TTreeView;
    ImageList: TImageList;
    procedure TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure TreeViewKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
    FList: TObjectList;
    FCanEdit: Boolean;
    FDefaultStation: Boolean;
    FPrivilege: TUserPrivilege;
    procedure   SetAuthSet(const Value: string);
    procedure   SetMenuSet(const Value: string);
    function    GetAuthSet: string;
    function    GetMenuSet: string;
  protected
    { Proected declarations }
    procedure   InternalBuildTree(AMenu: TUIMenu; Parent: TTreeNode);
    procedure   UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
    // 根据TreeNode对应的TTreeNodeData更新TreeNode的显示
    procedure   UpdateTreeNodeDisplay(TreeNode : TTreeNode);
    // 修改TreeNode对应的TTreeNodeData的对应的菜单/功能权限, Recurse是否递归
    procedure   SetTreeNodeAuth(TreeNode : TTreeNode; Authed:integer;Recurse: Boolean);
    // 将TreeNode对应的TTreeNodeData的对应的菜单/功能权限反转
    procedure   ReverseTreeNode(TreeNode : TTreeNode; Recurse: Boolean);
    // 更新状态全部节点的状态
    procedure   UpdateState;
    //  更新状态一个节点的状态。主要计算ChildrenState
    procedure   UpdateTreeNodeState(TreeNode : TTreeNode);
    // 更新整个树的显示(图标)
    procedure   UpdateDisplay;
    function    IsLeaf(TreeNode : TTreeNode) :Boolean;
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    // 构造树
    procedure   BuildTree(const DefaultStation: Boolean=False; MainMenuAdmin : TMenuAdmin = nil);
    procedure   SetAuth(MenuSet, AuthSet: string); // // should remove to private!
    procedure   RefreshTreeDisplay;
    // 返回权限树的文本表示
    function    GetTreeText : string;
    property    CanEdit : Boolean read FCanEdit write FCanEdit;
    property    AuthSet: string read GetAuthSet write SetAuthSet;
    property    MenuSet: string read GetMenuSet write SetMenuSet;
    property    Privilege : TUserPrivilege read FPrivilege;
  end;

// 保存一组权限树到文件。文件名由用户通过对话框选择。
// 如果设置了OpenFile，那么保存以后打开这个文件
// 返回True表示成功保存了文件,False表示用户取消保存
function  SaveAuthTreeToFile(const BaseName : string;
  const Auths : array of TfaAuth; OpenFile : Boolean=False) : Boolean;

// 调用SaveAuthTreeToFile，根据用户是否按下CTRL确定是否打开保存好的文件
function  SaveAuthTreeToFileEx(const BaseName : string;
  const Auths : array of TfaAuth) : Boolean;

// 保存一组权限树到文件。需要在输入参数里面指定文件名  
procedure SaveAuthTreeToFile2(const BaseName, FileName : string;
  const Auths : array of TfaAuth);

implementation

uses SafeCode, KSFrameWorks, KSFrameWorkUtils, KSKeyboard, KSClientConsts, LogFile,
  TextUtils, ExtUtils;

{$R *.DFM}

{ TUserPrivilege }

constructor TUserPrivilege.Create;
begin
  FormatAuth(FAuthSet);
  FormatAuth(FMenuSet);
end;

procedure TUserPrivilege.SetAuthSet(const Value: string);
begin
  FAuthSet := Value;
  FormatAuth(FAuthSet);
end;

procedure TUserPrivilege.SetMenuSet(const Value: string);
begin
  FMenuSet := Value;
  FormatAuth(FMenuSet);
end;

{ TTreeNodeData }

constructor TTreeNodeData.Create(APrivilege : TUserPrivilege);
begin
  Assert(APrivilege<>nil);
  inherited Create;
  //FSelected  := '0';
  FPrivilege := APrivilege;
end;

{ TTreeNodeMenuData }

constructor TTreeNodeMenuData.Create(APrivilege: TUserPrivilege;
  AMetaMenu: TKSMetaMenu);
begin
  Assert(AMetaMenu<>nil);
  inherited Create(APrivilege);
  FMetaMenu := AMetaMenu;
end;

function TTreeNodeMenuData.CanAuth: Boolean;
begin
  Result := FMetaMenu.CanAuth;
end;

function TTreeNodeMenuData.GetCaption: string;
begin
  Result := FMetaMenu.Caption;
end;

function TTreeNodeMenuData.GetImageIndex: Integer;
var
  IsGroup : Boolean;
begin
  IsGroup := MetaMenu.MenuType<>LeafValue;
  case ChildrenState of
    csNone :
      if IsGroup then
        Result := NonLeafSelected else
        Result := LeafSelected;
    csAllOk :
      if IsGroup then
        Result := NonLeafSelectedTick else
        Result := LeafSelectedTick;
    csAllBad :
      if IsGroup then
        Result := NonLeafSelectedCross else
        Result := LeafSelectedCross;
    csOkAndBad :
      if IsGroup then
        Result := NonLeafSelectedOther else
        Result := LeafSelectedOther;
  else
    Result := 13;
  end;
end;

function TTreeNodeMenuData.GetStateIndex: Integer;
begin
  if not FMetaMenu.CanAuth then
    Result := -1
  else if HaveAuth=1 then
    Result := TreeStateTick
  else
    Result := TreeStateCross;
end;

function TTreeNodeMenuData.HaveAuth: Integer;
begin
  Result := FMetaMenu.HaveAuth(FPrivilege.MenuSet);
end;

procedure TTreeNodeMenuData.SetAuth(AuthNo: Integer);
begin
  FMetaMenu.SetAuth(FPrivilege.FMenuSet,AuthNo);
end;

{ TTreeNodeFunctionData }

constructor TTreeNodeFunctionData.Create(APrivilege: TUserPrivilege;
  AMetaFunction: TKSMetaFunction);
begin
  Assert(AMetaFunction<>nil);
  inherited Create(APrivilege);
  FMetaFunction := AMetaFunction;
end;

function TTreeNodeFunctionData.CanAuth: Boolean;
begin
  Result := True;
end;

function TTreeNodeFunctionData.GetCaption: string;
begin
  Result := FMetaFunction.Caption;
end;

function TTreeNodeFunctionData.GetImageIndex: Integer;
begin
  Result := FunctionSelected;
end;

function TTreeNodeFunctionData.GetStateIndex: Integer;
begin
  if HaveAuth=1 then
    Result := FunctionStateTick
  else if HaveAuth=0 then
    Result := FunctionStateNull
  else Result := FunctionStateCross
end;

function TTreeNodeFunctionData.HaveAuth: Integer;
begin
  Result := FMetaFunction.HaveAuth(FPrivilege.FAuthSet);
end;

procedure TTreeNodeFunctionData.SetAuth(AuthNo: Integer);
begin
  FMetaFunction.SetAuth(FPrivilege.FAuthSet,AuthNo);
end;

{ TfaAuth }

constructor TfaAuth.Create(AOwner: TComponent);
begin
  inherited;
  CheckObject(MenuAdmin,'Error : MenuAdmin not init');
  TreeView.ControlStyle := TreeView.ControlStyle - [csDoubleClicks];
  FPrivilege := TUserPrivilege.Create;
  FList := TObjectList.Create;
  FCanEdit := True;
end;

destructor TfaAuth.Destroy;
begin
  FList.Free;
  FPrivilege.Free;
  inherited;
end;

procedure TfaAuth.BuildTree(const DefaultStation: Boolean=False; MainMenuAdmin : TMenuAdmin = nil);
begin
//wlj 20031212 为了能前台指定采用哪棵树进行设置，将菜单结构作为输入参数。
  FDefaultStation := DefaultStation;
  TreeView.Items.BeginUpdate;
  try
    TreeView.Items.Clear;
    if  MainMenuAdmin = nil then
    begin
        InternalBuildTree(MenuAdmin.Root, nil);
    end
    else
    begin
        InternalBuildTree(MainMenuAdmin.Root, nil);
    end;
    TreeView.Items[0].Expand(false);
  finally
    TreeView.Items.EndUpdate;
  end;
end;

procedure TfaAuth.InternalBuildTree(AMenu: TUIMenu; Parent: TTreeNode);
var I: Integer;
    Node{, Func}: TTreeNode;
    MenuData: TTreeNodeMenuData;
    FunctionData: TTreeNodeFunctionData;
begin
  // 过滤掉隐藏的菜单
  if AMenu.MetaMenu.HideInManageTree then
    Exit;
  if AMenu.Parent <> nil then
    if (AMenu.MetaMenu.Id = '总部菜单') and ((not IsCenterDepartment) or FDefaultStation)  then
      Exit;
  // 创建对应的数据对象
  MenuData := TTreeNodeMenuData.Create(FPrivilege,AMenu.MetaMenu);
  FList.Add(MenuData);
  Node := TreevIew.Items.AddChildObject(Parent,MenuData.GetCaption,MenuData);
  // 如果是叶菜单，构造功能节点
  if AMenu is TUIMenuItem then
  begin
    for I := 0 to TUIMenuItem(AMenu).count - 1 do
    begin
      FunctionData := TTreeNodeFunctionData.Create(Privilege,TUIMenuItem(AMenu).Items[I].MetaFunction);
      Flist.Add(FunctionData);
      {Func := }TreevIew.Items.AddChildObject(Node,FunctionData.GetCaption,FunctionData);
    end;
  end;
  // 如果包含子节点，构造它们
  if AMenu is TUIMenuGroup then
    for I := 0 to TUIMenuGroup(AMenu).Count - 1 do
      InternalBuildTree(TUIMenuGroup(AMenu).Items[I],Node);
end;

procedure TfaAuth.TreeViewKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = ' ' then
    UpdateStateIndex(TreeView.Selected, [htOnStateIcon]);
  Key := #0;
end;

procedure TfaAuth.TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
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


procedure TfaAuth.UpdateStateIndex(AnItem: TTreeNode; MyHitTest: THitTests);
begin
  if not FCanEdit then Exit;
  if (AnItem<>nil) and ([htOnStateIcon,htOnIcon]*MyHitTest<>[]) then
  begin
    ReverseTreeNode(AnItem, not Keyboard.IsDown(VK_CONTROL));
    RefreshTreeDisplay;
  end;
  if Keyboard.IsDown(VK_SHIFT) then
  begin
    if TObject(AnItem.Data) is TTreeNodeMenuData then
      ShowMessage(IntToStr(TTreeNodeMenuData(AnItem.Data).MetaMenu.AuthNo));
    if TObject(AnItem.Data) is TTreeNodeFunctionData then
      ShowMessage(IntToStr(TTreeNodeFunctionData(AnItem.Data).MetaFunction.No));
  end;
end;

procedure TfaAuth.SetAuth(MenuSet, AuthSet: string);
begin
  FPrivilege.MenuSet := MenuSet;
  FPrivilege.AuthSet:= AuthSet;
  RefreshTreeDisplay;
end;


procedure TfaAuth.SetAuthSet(const Value: string);
begin
  FPrivilege.AuthSet := Value;
end;

procedure TfaAuth.SetMenuSet(const Value: string);
begin
  FPrivilege.MenuSet := Value;
end;

function TfaAuth.GetAuthSet: string;
begin
  Result := FPrivilege.AuthSet;
end;

function TfaAuth.GetMenuSet: string;
begin
  Result := FPrivilege.MenuSet;
end;

procedure TfaAuth.UpdateTreeNodeDisplay(TreeNode: TTreeNode);
var
  NodeData : TTreeNodeData;
begin
  Assert(TreeNode<>nil);
  NodeData := TTreeNodeData(TreeNode.Data);
  Assert(NodeData<>nil);
  TreeNode.ImageIndex := NodeData.GetImageIndex;
  TreeNode.SelectedIndex := TreeNode.ImageIndex;
  TreeNode.StateIndex := NodeData.GetStateIndex;
end;

procedure TfaAuth.SetTreeNodeAuth(TreeNode : TTreeNode; Authed:integer;Recurse: Boolean);
var
  NodeData : TTreeNodeData;
  Child : TTreeNode;
begin
  Assert(TreeNode<>nil);
  NodeData := TTreeNodeData(TreeNode.Data);
  Assert(NodeData<>nil);
  NodeData.SetAuth(Authed);
  if Recurse then
  begin
    Child := TreeNode.GetFirstChild;
    while Child<>nil do
    begin
      SetTreeNodeAuth(Child,Authed,Recurse);
      Child := TreeNode.GetNextChild(Child);
    end;
  end;
end;

procedure TfaAuth.UpdateDisplay;
var
  Node : TTreeNode;
begin
  Node := TreeView.Items.GetFirstNode;
  while Node<>nil do
  begin
    UpdateTreeNodeDisplay(Node);
    Node := Node.GetNext;
  end;
end;

procedure TfaAuth.UpdateState;
var
  Node : TTreeNode;
begin
  Node := TreeView.Items.GetFirstNode;
  if Node<>nil then
  begin
    UpdateTreeNodeState(Node);
  end;
end;

procedure TfaAuth.UpdateTreeNodeState(TreeNode: TTreeNode);
var
  NodeData : TTreeNodeData;
  Child : TTreeNode;
  ChildrenState : TChildrenState;
  ChildState : TChildrenState;
begin
  Assert(TreeNode<>nil);
  NodeData := TTreeNodeData(TreeNode.Data);
  Assert(NodeData<>nil);
  {三态注意点}
  if NodeData.CanAuth then
  begin
    if NodeData.HaveAuth=1 then      //判断一下是否子节点，修改HaveAuth
      ChildrenState := csAllOK
    else if (NodeData.HaveAuth=0) or (NodeData.HaveAuth=2)then
      ChildrenState := csAllBad;
  end else
    ChildrenState := csNone;
  Child := TreeNode.GetFirstChild;
  while Child<>nil do
  begin
    UpdateTreeNodeState(Child);
    ChildState := TTreeNodeData(Child.Data).ChildrenState;
    if ChildrenState=csNone then
      ChildrenState := ChildState
    else if ChildrenState<>csOkAndBad then
    begin
      if (ChildState<>csNone) and (ChildState<>ChildrenState) then
        ChildrenState := csOkAndBad;
    end;
    Child := TreeNode.GetNextChild(Child);
  end;
  NodeData.ChildrenState := ChildrenState;
end;

procedure TfaAuth.ReverseTreeNode(TreeNode: TTreeNode; Recurse: Boolean);
var
  NodeData : TTreeNodeData;
  Parent : TTreeNode;
  Child : TTreeNode;
  Authed : Integer;
begin
  Assert(TreeNode<>nil);
  NodeData := TTreeNodeData(TreeNode.Data);
  Assert(NodeData<>nil);
  if NodeData.CanAuth then
  begin
    if IsLeaf(TreeNode) then
    begin
      if NodeData.HaveAuth>2 then
        SetTreeNodeAuth(TreeNode,0,Recurse);
      if NodeData.HaveAuth=0 then SetTreeNodeAuth(TreeNode,1,Recurse)
      else if NodeData.HaveAuth=1 then SetTreeNodeAuth(TreeNode,0,Recurse)
      else
        SetTreeNodeAuth(TreeNode,0,Recurse);
      //else if NodeData.HaveAuth=2 then SetTreeNodeAuth(TreeNode,0,Recurse);
    end else
    begin
      if NodeData.HaveAuth=0 then SetTreeNodeAuth(TreeNode,1,Recurse)
      else if NodeData.HaveAuth=1 then SetTreeNodeAuth(TreeNode,0,Recurse);
    end;
  end else
  begin
    if NodeData.ChildrenState<>csAllOK then SetTreeNodeAuth(TreeNode,1,Recurse)
    else SetTreeNodeAuth(TreeNode,0,Recurse);
  end;

  if TreeNode.Level=0 then Exit;

  Parent:= TreeNode.Parent;
  while Parent.Level <> 0 do
  begin
    Child := Parent.GetFirstChild;
    Authed := 0;
    while Child<>nil do
    begin
      NodeData := TTreeNodeData(Child.Data);
      if NodeData.HaveAuth=1 then
      begin
        Authed:= 1;
        Break;
      end;
      Child := Parent.GetNextChild(Child);
    end;
    NodeData := TTreeNodeData(Parent.Data);
    if (NodeData<>nil) and (NodeData.CanAuth) then
      NodeData.SetAuth(Authed);
    Parent:= Parent.Parent;
  end;
end;

procedure TfaAuth.RefreshTreeDisplay;
begin
  TreeView.Items.BeginUpdate;
  try
    UpdateState;
    UpdateDisplay;
  finally
    TreeView.Items.EndUpdate;
  end;
end;


function TfaAuth.IsLeaf(TreeNode : TTreeNode): Boolean;
begin
  if TreeNode.getFirstChild=nil then Result:=True
  else Result:=False;
end;

function TfaAuth.GetTreeText: string;
var
  Node : TTreeNode;
  Indent, TypeString, StateString1, StateString2 : string;
  Data : TTreeNodeData;
begin
  //RefreshTreeDisplay;
  Result := '';
  Node := TreeView.Items.GetFirstNode;
  while Node<>nil do
  begin
    Indent := StringOfChar(' ',Node.Level*2);
    Data := TTreeNodeData(Node.Data);
    StateString1 := StateStringsForImageIndex[Data.GetStateIndex];
    StateString2 := StateStringsForImageIndex[Data.GetImageIndex];
    if Data is TTreeNodeFunctionData then
    begin
      TypeString := FunctionTypeString;
      StateString2 := '';
    end
    else
    begin
      if (Data as TTreeNodeMenuData).MetaMenu.MenuType=LeafValue then
        TypeString := MenuItemTypeString else
        TypeString := GroupMenuTypeString;
    end;
    Result := Result
     + Indent + TypeString + StateString1 + StateString2
     + Node.Text
     + LineBreak;
    Node := Node.GetNext;
  end;
end;

function  SaveAuthTreeToFile(const BaseName : string;
  const Auths : array of TfaAuth; OpenFile : Boolean) : Boolean;
var
  SaveDialog : TSaveDialog;
begin
  Result := False;
  SaveDialog := TSaveDialog.Create(nil);
  try
    SaveDialog.Options := SaveDialog.Options+[ofOverwritePrompt];
    SaveDialog.Filter := '文本文件|*.txt|所有文件|*.*';
    SaveDialog.DefaultExt := 'txt';
    SaveDialog.FileName := Format('%s%s-%s.txt',
    [
      Context.GetDir(dkOutput),
      BaseName,
      FormatDateTime('yyyymmdd',Now)
    ]);
    if SaveDialog.Execute then
    begin
      SaveAuthTreeToFile2(BaseName, SaveDialog.FileName, Auths);
      Result := True;
      if OpenFile then
        ShellOpenFile(SaveDialog.FileName);
    end;
  finally
    SaveDialog.Free;
  end;
end;

procedure SaveAuthTreeToFile2(const BaseName, FileName : string;
  const Auths : array of TfaAuth);
var
  Writer : TTextWriter;
  I : Integer;
begin
  Writer := TTextWriter.Create(FileName);
  try
    Writer.Println(CommentChar+BaseName);
    for I:=Low(Auths) to High(Auths) do
    begin
      Writer.Println(CommentChar+Auths[I].Hint);
      Writer.Println(Auths[I].GetTreeText);
      Writer.Println('');
    end;
  finally
    Writer.Free;
  end;
end;

function  SaveAuthTreeToFileEx(const BaseName : string;
  const Auths : array of TfaAuth) : Boolean;
begin
  Result := SaveAuthTreeToFile(BaseName,Auths,TKSKeyboard.IsDown(VK_CONTROL));
end;

end.
