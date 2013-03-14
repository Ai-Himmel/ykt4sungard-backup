unit USMSetTreeParamsTemp;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>USetParamsTemp
   <What>�������ò�������ģ��
   <Written By> Huang YanLai (������)
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
    FCanEdit : Boolean;   //�������ӡ��޸ġ�ɾ��
    FCanDelete: Boolean;  // ����ɾ��
    FCanAdd: Boolean;     // ��������
    FCanChange: Boolean;  // �����޸�
    FLocalDepartment : string;  // ����Ӫҵ������

    FList: TObjectList;
    FBranchNo:string;
    Include:Boolean;

    FCurrentParentID:Integer; {��ǰ�༭�ڵ�ĸ�ID}
    FCurrentID:Integer; {��ǰ�༭�ڵ��ID}

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
    FDataSetFieldName:String; {���ڵ������ֶ���}
    FDataSetFieldID:String;{���ڵ�ID���ֶ���}
    FDataSetParentFieldID:String;{���ڵ�id�ֶ���}

    constructor Create(AOwner : TComponent); override;
    destructor Destroy;

    procedure   BuildTree;
    property    CanEdit : Boolean read FCanEdit write FCanEdit;
    procedure   InitTreeNode(TreeNode:TTreeNode);   //�������Ӫҵ��ѡ��״̬
    procedure   ClearTreeNode(TreeNode:TTreeNode);  //���������Ӫҵ��ѡ��״̬
    procedure   SelectTreeNode(TreeNode:TTreeNode); //ѡ�������������Ӫҵ��
    procedure   ClearParentAndBrotherNode(ParentNode,TreeNode:TTreeNode); //������и����ֵ�ѡ��״̬
    {�����ݼ��ж�ȡ���ṹ����Ϣ}
    procedure   ReadTreeInfoFromDataSet(DataSet: TDataSet;InfoAdmin:TInfoAdmin);
    {�ϷŹ����и��ƽڵ�}
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
  newnode:=treeview.items.addchildfirst(targetnode,''); //����Ŀ����
  newnode.assign(sourcenode); //����Դ������
  for i:=sourcenode.count-1 downto 0 do //�ݹ���ã��������ƶ�����������
  CopyNodeUnder (treeview,sourcenode.item[i],newnode);
  treeview.items.delete(sourcenode); //ɾ��Դ��
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
      LastNode := TKSMetaNode.Create;              //���ڵ�����ƺʹ��뼯��
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
        InfoAdmin.StructureList.Add(Structure);  //���ϼ��ڵ���뼯��
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
          LastNode:= InfoAdmin.InfoList.Find(DataSet.FieldByName(FDataSetParentFieldID).AsString); 
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
  // ���е�������Ŀ���Ա༭
  EnableEditCtrls(True);
  // ��ʼ������������Ŀ
  WorkView.Reset(WVDataSource.GroupIndex);
end;

procedure TfaSMSetTreeParamsTemp.BeforeChange;
begin
  tsEdit.Caption := SChange;
  // ���е�������Ŀ���Ա༭
  // ���������ظ÷�������ֹ�������Ա༭
  EnableEditCtrls(True);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp.BeforeDelete;
begin
  tsEdit.Caption := SDelete;
  // ���е�������Ŀ�������Ա༭
  EnableEditCtrls(False);
  //WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp.btnDeleteClick(Sender: TObject);
begin
  {
  case Context.GetDialogSystem.Confirm(Format('ɾ��%s��',[GetCurrentRecordInfo])) of
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
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(AddRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp.DoChange;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
  SaveModifiedData;
  SendEditCommand(ChangeRequest);
  if FEditSucceed then
    Status := ssBrowse;
end;

procedure TfaSMSetTreeParamsTemp.DoDelete;
begin
  // ͬ���޸ĵ����ݵ�������ͼ���ύ��������ɹ�(FEditSucceed=True����û�������׳�)���ָ�״̬Ϊ���
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

procedure TfaSMSetTreeParamsTemp.BeforeViewDetail{(IsFirst : Boolean=True)};
begin
  tsEdit.Caption := SViewDetail;
  // ���е�������Ŀ�������Ա༭
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
  // �����ݴ�����Դͬ����������ͼ���ٵ����ֿؼ�����ע�⣺һЩ������Ҫ���ظ÷�������������ؼ�������ͬ����
  WorkView.Reset(WVDataSource.GroupIndex);
  if DataSource.Dataset<>nil then
    WVDataSource.DataSourceToWorkView;
end;

procedure TfaSMSetTreeParamsTemp.SaveModifiedData;
begin
  // ���޸ĵ�����ͬ����������ͼ�����ʹ������Ŀؼ���Ҫ���ش˷�����
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

procedure TfaSMSetTreeParamsTemp.TreeViewDragOver(Sender, Source: TObject;
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

procedure TfaSMSetTreeParamsTemp.Button1Click(Sender: TObject);
var TreedateSet:TDataSet;
begin
  InfoAdmin:=TInfoAdmin.Create;

  TreedateSet:=TDataSet.Create(nil);
  Try
    TreedateSet:=(WorkView.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;
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
