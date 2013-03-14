unit USMSetTreeParamsTemp_Dept;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USetParamsTemp
   <What>�������ò�������ģ��
   <Written By> Huang YanLai (������)
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
    <What>��Ӧ�˵���Ŀ
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
  // �������ý����״̬
  TSettingStatus = (
    ssBrowse,         // ���״̬
    ssAdd,            // ����״̬
    ssChange,         // �޸�״̬
    ssDelete,         // ɾ��״̬
    ssViewDetail      // ���ϸ������״̬
    );

  // ����ά����ʽ
  TParamMaintainType = (
    pmtCenter,        // �ܲ�ά������
    pmtDepartment     // Ӫҵ��ά������
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
    FCanEdit : Boolean;   //�������ӡ��޸ġ�ɾ��
    FCanDelete: Boolean;  // ����ɾ��
    FCanAdd: Boolean;     // ��������
    FCanChange: Boolean;  // �����޸�
    FLocalDepartment : string;  // ����Ӫҵ������

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
    procedure   EnableEditCtrls(AEnabled : Boolean); virtual; // ���ƿؼ��Ƿ���Ա༭
    procedure   BeforeAdd; virtual; // �̳и÷��������ӳ�ʼ������
    procedure   BeforeChange; virtual; // �̳и÷��������ӳ�ʼ������
    procedure   BeforeDelete; virtual; // �̳и÷��������ӳ�ʼ������
    procedure   BeforeViewDetail{(IsFirst : Boolean=True)}; virtual; // �̳и÷��������ӳ�ʼ������
    procedure   CancelEdit; virtual; // �̳и÷���������������ݲ���
    procedure   DoAdd; virtual; // �̳и÷���������EditRequest
    procedure   DoChange; virtual; // �̳и÷���������EditRequest
    procedure   DoDelete; virtual; // �̳и÷���������EditRequest
    procedure   SendEditCommand(Request : TWVRequest); virtual; // �̳и÷������������ã����ӡ��޸ġ�ɾ������������FEditSucceed
    function    GetCurrentRecordInfo : string; virtual; // �̳и÷���������һ�����ݵ�����������ɾ�����ݣ�
    procedure   DoQuery; virtual; // �̳и÷��������ò�ѯ����
    procedure   SendQueryCommand; virtual; // �̳и÷����������ѯ����
    procedure   EnableEdit(CanEdit : Boolean);  // �ϳ�
    procedure   UpdateButton; // ���°�����Enabled״̬
    function    InternalGetCanEdit : Boolean; virtual; // �ж��Ƿ�����޸ģ���������ά�����ͺ͵�ǰӪҵ������FCanEdit����
    procedure   InitEx; override;   // ����ĳ�ʼ����֧���Զ���ѯ
    procedure   StatusChanged; virtual; // �������״̬�����ı䣬���� DisplayData
    procedure   DisplayData; virtual;   // �����ݴ����ݼ�������ʾ������ͬ����������ͼ�������ʹ�����������Ŀؼ���Ҫ���ش˷�����
    procedure   SaveModifiedData; virtual;  // ���޸ĵ�����ͬ����������ͼ�����ʹ������Ŀؼ���Ҫ���ش˷�����
    function    ConfirmEdit : Boolean; virtual; // �����Ƿ������޸ġ��ڰ���ȷ�ϵ�ʱ�򱻵��á����������ﵯ���Ի�����ʾȷ�ϻ��߸��ˡ�

  public
    BranchName,IncludeName:string;
    FSingleSelect:Boolean;
    FWorkView:TWorkView;

    FDataSet:TDataSet;
    FDataSetFieldName:String; {���ڵ������ֶ���}
    FDataSetFieldID:String;{���ڵ�ID���ֶ���}
    FDataSetParentFieldID:String;{���ڵ�id�ֶ���}
    FWorkViewFieldName:String; {���ڵ������ֶ���}
    FWorkViewFieldID:String;{���ڵ�ID���ֶ���}
    FWorkViewParentFieldID:String;{���ڵ�id�ֶ���}
    FDefaultID:Integer;

    //FCurrentParentID:Integer; {��ǰ�༭�ڵ�ĸ�ID}
    //FCurrentID:Integer; {��ǰ�༭�ڵ��ID}
    FCurrentParentID:string; {��ǰ�༭�ڵ�ĸ�ID}
    FCurrentID:string; {��ǰ�༭�ڵ��ID}

    constructor Create(AOwner : TComponent); override;
    destructor Destroy;

    procedure   BuildTree;
    property    CanEdit : Boolean read FCanEdit write FCanEdit;
    procedure   InitTreeNode(TreeNode:TTreeNode);   //�������Ӫҵ��ѡ��״̬
    procedure   ClearTreeNode(TreeNode:TTreeNode);  //���������Ӫҵ��ѡ��״̬
    procedure   SelectTreeNode(TreeNode:TTreeNode); //ѡ�������������Ӫҵ��
    procedure   ClearParentAndBrotherNode(ParentNode,TreeNode:TTreeNode); //������и����ֵ�ѡ��״̬
    {�����ݼ��ж�ȡ���ṹ����Ϣ}
    procedure   ReadTreeInfoFromDataSet(DataSet: TDataSet;CInfoAdmin:TInfoAdmin);
    {�ϷŹ����и��ƽڵ�}
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

    {��DBGRID�ж�λָ����¼}
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
  else ShowMessage('���ݼ����ڹر�״̬�����������');
end;



procedure TfaSMSetTreeParamsTemp_Dept.CopyNodeUnder(treeview:TRzTreeview;sourcenode,targetnode:ttreenode);
var
  newnode:ttreenode;
  i:integer;
begin
  newnode:=treeview.items.addchildfirst(targetnode,''); //����Ŀ����
  newnode.assign(sourcenode); //����Դ������
  for i:=sourcenode.count-1 downto 0 do //�ݹ���ã��������ƶ�����������
  CopyNodeUnder (treeview,sourcenode.item[i],newnode);
  treeview.items.delete(sourcenode); //ɾ��Դ��
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
      LastNode := TKSMetaNode.Create;              //���ڵ�����ƺʹ��뼯��
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
        CInfoAdmin.StructureList.Add(Structure);  //���ϼ��ڵ���뼯��
        if (DataSet.FieldByName(FDataSetParentFieldID).AsString='') then  //
        begin
          Node.NodeType:=RootValue;
          Structure.ParentId := '';
          Structure.ChildId := Node.ID;
        end else
        begin
          Structure.ChildId := Node.ID;
          if Node.NodeType='' then Node.NodeType:=LeafValue;
          //�ϼ�Ӫҵ��
          LastNode:= CInfoAdmin.InfoList.Find(DataSet.FieldByName(FDataSetParentFieldID).AsString);
          if LastNode<>nil then
          begin
            Structure.ParentId := DataSet.FieldByName(FDataSetParentFieldID).AsString;
            if LastNode.NodeType<>RootValue then
            begin
              LastNode.NodeType:=GroupValue;
            end;
          end else         //Ӫҵ����¼
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
  if TreeNode=TreeView.Items.GetFirstNode then   //����Ǹ��ڵ�
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
  end else   //������Ǹ��ڵ�
  begin
    if (TreeNode.imageIndex=ClearIndex)and(TreeNode.GetFirstChild<>nil) then
    begin
      Include:=True;
      //ClearParentAndBrotherNode(TreeView1.Items.GetFirstNode,TreeNode);
      SelectTreeNode(TreeNode);
    end else
    begin
      if TreeNode.GetFirstChild<>nil then   //���Ӹ��ڵ�
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
      end else //Ҷ�ӽڵ�
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
  // ������Ӧ�����ݶ���
  InfoData := TTreeNodeInfoData.Create(AInfo.MetaNode);
  FList.Add(InfoData);
  Node := TreeView.Items.AddChildObject(Parent,InfoData.GetCaption,InfoData);
  Node.ImageIndex:=ClearIndex;
  // ��������ӽڵ㣬��������
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

  /// �¼���ͬ�����Ǽ̳е�ǰѡ��Ľڵ����Ϣ
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
  // ���״̬ת��
  if FStatus <> Value then
  begin
    FStatus := Value;
    if FStatus=ssBrowse then
    begin
      // ���״̬
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
  // ���е�������Ŀ���Ա༭
  EnableEditCtrls(True);
  // ��ʼ������������Ŀ
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaSMSetTreeParamsTemp_Dept.BeforeChange;
begin
  tsEdit.Caption := SChange;
  // ���е�������Ŀ���Ա༭
  // ���������ظ÷�������ֹ�������Ա༭
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp_Dept.BeforeDelete;
begin
  tsEdit.Caption := SDelete;
  // ���е�������Ŀ�������Ա༭
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp_Dept.btnDeleteClick(Sender: TObject);
begin
  {
  case Context.GetDialogSystem.Confirm(Format('ɾ��%s��',[GetCurrentRecordInfo])) of
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
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DoChange;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp_Dept.DoDelete;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
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
        Context.GetDialogSystem.ShowMessage('���������´򿪸ù���--'+e.Message);
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
  // ��������ά�����ͺ͵�ǰӪҵ������FCanEdit����
  // ��������������ظ÷������ṩ����Ŀ���
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
    //�޲�ѯ������ݣ���ֹ�޸ġ�ɾ������������
    FCanDelete := False;
    FCanChange := False;
    FCanAdd := True;
    btnViewDetail.Enabled := False;
  end else
  begin
    //�в�ѯ���ݣ�
    if (FDepartmentFieldName<>'') and (FMaintainType=pmtDepartment) then
    begin
      // �����Ӫҵ��ά�����ݣ���ô��Ҫ���ݷ������ݼ��Ӫҵ����ֻ���޸ĺ�ɾ����Ӫҵ��������
      DepartField:= DataSource.DataSet.FindField(FDepartmentFieldName);
      SameDepart := (DepartField<>nil) and (DepartField.AsString=FLocalDepartment);
    end else
      // ������Ҫ���Ӫҵ��������༭
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
  // ���е�������Ŀ�������Ա༭
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
  // �����ݴ�����Դͬ����������ͼ���ٵ����ֿؼ�����ע�⣺һЩ������Ҫ���ظ÷�������������ؼ�������ͬ����
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp_Dept.SaveModifiedData;
begin
  // ���޸ĵ�����ͬ����������ͼ�����ʹ������Ŀؼ���Ҫ���ش˷�����
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
      if DataSource.DataSet.RecNo mod 2<>0 then {�жϵ�ǰ��������������ż����}
      Canvas.brush.Color :=clInfoBk {����������У�DBGrid�����԰�ɫ��ʾ}
    else
      Canvas.brush.Color :=$00EBDED0; {�����ż����$00EBDED0��DBGrid������ǳ��ɫ��ʾ}
    end;
    DefaultDrawColumnCell(Rect, DataCol, Column, State); {���кܹؼ��ģ�һ����Ҫ��©��}
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
  targetnode:=TreeView.getnodeat(x,y); //���Դ�ڵ�
  sourcenode:=TreeView.selected; //���Ŀ��ڵ�
  //�޸����ݿ��е�ǰ�ڵ�ĸ��ڵ��parent_id��ʹ���Ŀ��ڵ��ʶ�ţ�
  TreeView.items.beginupdate; //����TreeView�ػ����
  try
    copynodeunder(TreeView,sourcenode,targetnode); //�����ƶ�����
    TreeView.selected:=targetnode;
  finally
    TreeView.items.endupdate; //��������
  end;
end;

procedure TfaSMSetTreeParamsTemp_Dept.TreeViewDragOver(Sender, Source: TObject;
  X, Y: Integer; State: TDragState; var Accept: Boolean);
var  targetnode,sourcenode:TTreenode;
begin
  targetnode:=TreeView.getnodeat(x,y);
  if (Source=Sender) and (targetnode<>nil) then //��֤�ƶ���TreeView�ϣ���Ŀ��ڵ㲻Ϊ��
  begin
  Accept:=true;
  sourcenode:=TreeView.selected;
  //���´����ֹ�û���һ��ѡ���ϵ��������ϣ���������ѡ��һ���ƶ���������ѭ����
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
      Context.GetDialogSystem.ShowMessage('����-'+e.Message);
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
