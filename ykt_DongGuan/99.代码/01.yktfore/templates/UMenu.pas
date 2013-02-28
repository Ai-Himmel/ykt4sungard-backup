unit UMenu;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UMenu
   <What>菜单树控件
   <Written By> 程用明
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ImgList, ComCtrls, WVCmdReq, WorkViews, KSMenuAdmin, Contnrs;

type
  TfaMenu = class(TFrame)
    TreeView: TTreeView;
    ImageList: TImageList;
    procedure TreeViewKeyPress(Sender: TObject; var Key: Char);
    procedure TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    { Private declarations }
    FList: TObjectList;
    FCanEdit: Boolean;
    FMenuSet: string;
  protected
    { Proected declarations }
    procedure   BuildTree(AMenu: TUIMenu; Parent: TTreeNode);
    procedure   UpdateChildren(TreeNode: TTreeNode; Authed : Boolean);
    procedure   ShowAuth(TreeNode: TTreeNode);
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure   SetMenuSet(value: string); // should remove to private!
    property    CanEdit : Boolean read FCanEdit write FCanEdit;
    property    MenuSet : string read FMenuSet write SetMenuSet;
  end;

implementation

uses SafeCode, KSFrameWorkUtils, KSKeyboard;

{$R *.DFM}

constructor TfaMenu.Create(AOwner: TComponent);
//var I: Integer;
begin
  inherited;
  {
  for I := 1 to 800 do
    MenuSet := MenuSet + '0';
  }
  FormatAuth(FMenuSet);
  CheckObject(MenuAdmin,'Error : MenuAdmin not init');
  FList := TObjectList.Create;
  TreeView.Items.BeginUpdate;
  TreeView.Items.Clear;
  BuildTree(MenuAdmin.Root, nil);
  TreeView.Items[0].Expand(false);
  TreeView.Items.EndUpdate;
  TreeView.ControlStyle := TreeView.ControlStyle - [csDoubleClicks];
  FCanEdit := True;
end;

procedure TfaMenu.BuildTree(AMenu: TUIMenu; Parent: TTreeNode);
var I: Integer;
    Node: TTreeNode;
    TreeNodeData: TTreeNodeMenuData;
begin
  if AMenu.MetaMenu.HideInManageTree then
    Exit;
  if AMenu.Parent <> nil then
    if (AMenu.MetaMenu.Id = '总部菜单') and (not IsCenterDepartment) then
      Exit;
  TreeNodeData := TTreeNodeMenuData.Create;
  FList.Add(TreeNodeData);
  TreeNodeData.MetaMenu := AMenu.MetaMenu;
  if AMenu.Parent = nil then
    AMenu.MetaMenu.Caption := '证券业务';
  Node := TreevIew.Items.AddChildObject(Parent,AMenu.MetaMenu.Caption,TreeNodeData);
  if AMenu is TUIMenuGroup then
  begin
    Node.SelectedIndex := 0;
    Node.ImageIndex := 0;
    Node.StateIndex := 3;
  end;
  if AMenu is TUIMenuItem then
  begin
    Node.SelectedIndex := 1;
    Node.ImageIndex := 1;
    Node.StateIndex := 3;
  end;

  if AMenu is TUIMenuGroup then
    for I := 0 to TUIMenuGroup(AMenu).Count - 1 do
      BuildTree(TUIMenuGroup(AMenu).Items[I], Node);
end;


procedure TfaMenu.TreeViewKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = #13 then
end;

procedure TfaMenu.TreeViewMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  MyHitTest : THitTests;
  AnItem: TTreeNode;
  Authed : Boolean;
begin
  Authed := False;
  if not FCanEdit then Exit;
  if Button <> mbLeft then Exit;
  MyHitTest := TreeView.GetHitTestInfoAt(X,Y);
  AnItem := TreeView.GetNodeAt(X, Y);
  if (AnItem<>nil) and (htOnStateIcon in MyHitTest) then
  begin
    case AnItem.StateIndex of
      2 :
        begin
          Authed := True;
          AnItem.StateIndex:=3;
          TTreeNodeMenuData(AnItem.Data).Selected := '1';
          //MenuSet[TTreeNodeMenuData(AnItem.Data).MetaMenu.AuthNo + 2] := '1';
          TTreeNodeMenuData(AnItem.Data).MetaMenu.SetAuth(FMenuSet,True);
        end;
      3 :
        begin
          Authed := False;
          AnItem.StateIndex:=2;
          TTreeNodeMenuData(AnItem.Data).Selected := '0';
          //MenuSet[TTreeNodeMenuData(AnItem.Data).MetaMenu.AuthNo + 2] := '0';
          TTreeNodeMenuData(AnItem.Data).MetaMenu.SetAuth(FMenuSet,False);
        end;
    else
      Assert(False);
    end;
    if not Keyboard.IsDown(VK_CONTROL) then
      UpdateChildren(AnItem, Authed);

    ShowAuth(TreeView.Items[0]);
  end;
end;

procedure TfaMenu.SetMenuSet(value: string);
{var
   I: Integer; }
begin
  FMenuSet := value;
  {
  if Length(value) < 800 then
    for I := Length(value) + 1 to 800 do
      MenuSet := MenuSet + '0';
  }
  FormatAuth(FMenuSet);
  ShowAuth(TreeView.Items[0]);
end;

procedure TfaMenu.ShowAuth(TreeNode: TTreeNode);
var
  I: Integer;
begin
  if TreeNode <> nil then
  begin
    {
    if MenuSet[TTreeNodeMenuData(TreeNode.Data).MetaMenu.AuthNo + 2] = '0' then
    }
    with TTreeNodeMenuData(TreeNode.Data).MetaMenu do
      if CanAuth then
        if not HaveAuth(FMenuSet) then
          TreeNode.StateIndex := 2
        else
          TreeNode.StateIndex := 3;

    for I := 0 to TreeNode.Count - 1 do
      ShowAuth(TreeNode.Item[I]);
  end;
end;

destructor TfaMenu.Destroy;
begin
  FList.Free;
  inherited;
end;

procedure TfaMenu.UpdateChildren(TreeNode: TTreeNode; Authed : Boolean);
var
  I: Integer;
begin
  if TreeNode <> nil then
    for I := 0 to TreeNode.Count - 1 do
    begin
      TreeNode.Item[I].StateIndex := TreeNode.StateIndex;
      TTreeNodeMenuData(TreeNode.Item[I].Data).Selected := TTreeNodeMenuData(TreeNode.Data).Selected;
      //if TTreeNodeMenuData(TreeNode.Data).Selected = '0' then
      if not Authed then
      begin
        TTreeNodeMenuData(TreeNode.Item[I].Data).Selected := '0';
        //MenuSet[TTreeNodeMenuData(TreeNode.Item[I].Data).MetaMenu.AuthNo + 2] := '0';
        TTreeNodeMenuData(TreeNode.Item[I].Data).MetaMenu.SetAuth(FMenuSet,False);
      end
      else
      begin
        TTreeNodeMenuData(TreeNode.Item[I].Data).Selected := '1';
        //MenuSet[TTreeNodeMenuData(TreeNode.Item[I].Data).MetaMenu.AuthNo + 2] := '1';
        TTreeNodeMenuData(TreeNode.Item[I].Data).MetaMenu.SetAuth(FMenuSet,True);
      end;
      UpdateChildren(TreeNode.Item[I], Authed);
    end;
end;

end.

