unit KSBranchInfo;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSBranchInfo
   <What>从结果集中读取分支机构营业部层次关系
   <Written By> 周耀亮
   <History>
**********************************************}

interface

uses SysUtils, Classes, KSBranchTree, db, Dialogs;

procedure ReadBranchInfoFromDataSet(DataSet: TDataSet; InfoAdmin: TInfoAdmin);

implementation

procedure ReadBranchInfoFromDataSet(DataSet: TDataSet; InfoAdmin: TInfoAdmin);
var
  LastNode, Node: TKSMetaNode;
  Structure: TKSTreeStructure;
begin
  {  LastNode:=nil;
    try
      InfoAdmin.InfoList.Clear;
      InfoAdmin.StructureList.Clear;
      Assert(DataSet<>nil);
      DataSet.first;
      while not DataSet.Eof do
      begin
        LastNode := TKSMetaNode.Create;              //营业部代码和名称
        LastNode.ID := DataSet.FieldByName('lvol0').AsString;
        LastNode.Caption := DataSet.FieldByName('lvol0').AsString;
        LastNode.Description :='';
        LastNode.NodeType := '';
        InfoAdmin.InfoList.Add(LastNode);
        LastNode := nil;
        DataSet.Next;
      end;
      DataSet.first;
      while not DataSet.Eof do
      begin
        Node := InfoAdmin.InfoList.Find(DataSet.FieldByName('lvol0').AsString);
        if Node<>nil then
        begin
          Structure := TKSTreeStructure.Create;
          InfoAdmin.StructureList.Add(Structure);  //上级营业部集合
          if (DataSet.FieldByName('lvol1').AsString='') then
          begin
            Node.NodeType:=RootValue;
            Structure.ParentId := '';
            Structure.ChildId := Node.ID;
          end else
          begin
            Structure.ChildId := Node.ID;
            if Node.NodeType='' then Node.NodeType:=LeafValue;                               //上级营业部
            LastNode:= InfoAdmin.InfoList.Find(DataSet.FieldByName('lvol1').AsString);
            if LastNode<>nil then
            begin
              Structure.ParentId := DataSet.FieldByName('lvol1').AsString;
              if LastNode.NodeType<>RootValue then
              begin
                LastNode.NodeType:=GroupValue;
              end;
            end else         //营业部登录
            begin
              Node.NodeType:=RootValue;
              Structure.ParentId := DataSet.FieldByName('lvol1').AsString;
            end;
          end;
        end;
        Node:=nil;
        DataSet.Next;
      end
    finally
    end;
    InfoAdmin.Init;    }
end;

end.
