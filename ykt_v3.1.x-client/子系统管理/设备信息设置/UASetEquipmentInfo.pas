unit UASetEquipmentInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,
  UIncrementComboBox,RzDBNav,
  RzButton, RzRadChk, RzDBGrid, RzTabs, Buttons, USetParamsTemp, RzPanel;
type
  TEquipParaTreeNode = class
  public
    CEquipID: Integer;       {�豸��ʶ} //�� �豸�̻��� �� �豸�������Ψһ�ֶΣ�
    CNodeID: String;        {�豸����ID}
    CNodeCaption: String;   {�豸����}
    CNodeKind: String;     {����ID}
    CParentNodeID: String;  {���豸����ID}
    CParentNodeCaption: String;  {���豸����}
    CNodeKindCaption:String; {��������}
    CEquipRegNo : String ;  {�����豸ע���}
    CEquipSubSystem: string;  {�豸������ϵͳ}

end;

type
  TfaqhSetEquipmentInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    WVLabel11: TWVLabel;
    WVLabel29: TWVLabel;
    WVLabel44: TWVLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    WVComboBox18: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox17: TWVComboBox;
    WVComboBox20: TWVComboBox;
    WVLabel14: TWVLabel;
    WVComboBox3: TWVComboBox;
    Label5: TLabel;
    WVComboBox19: TWVComboBox;
    WVRequest1: TWVRequest;
    RzPanel1: TRzPanel;
    pnl1: TRzPanel;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    WVLabel4: TWVLabel;
    edtEquName: TWVEdit;
    WVLabel43: TWVLabel;
    lblPhyNo: TWVLabel;
    edtPhyNo: TWVEdit;
    lblUEqu: TWVLabel;
    lblSerPortNo: TWVLabel;
    edtSerPortNo: TWVEdit;
    edtSerPortNum: TWVEdit;
    lblSerPortNum: TWVLabel;
    lblMachineNo: TWVLabel;
    edtMachineNo: TWVEdit;
    cbbChildSys: TWVComboBox;
    WVLabel42: TWVLabel;
    cbbMachineType: TWVComboBox;
    lblMachineType: TWVLabel;
    lbl3: TWVLabel;
    cbbUseType: TWVComboBox;
    cbbEquPhyType: TWVComboBox;
    WVLabel40: TWVLabel;
    WVLabel17: TWVLabel;
    edtIP: TWVEdit;
    WVLabel2: TWVLabel;
    cbbComm: TWVComboBox;
    lblPort: TWVLabel;
    edtCommPortNo: TWVEdit;
    Label6: TLabel;
    WVEdit4: TWVEdit;
    Label7: TLabel;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    Label8: TLabel;
    cbbArea: TWVComboBox;
    edtUEqu: TWVEdit;
    btnOpen: TSpeedButton;
    btnClose: TSpeedButton;
    edtParName: TEdit;
    WVRequest2: TWVRequest;
    WorkView1: TWorkView;
    WVLabel3: TWVLabel;
    WVComboBox4: TWVComboBox;
    Label9: TLabel;
    WVEdit2: TWVEdit;
    WVLabel5: TWVLabel;
    WVEdit3: TWVEdit;
    TreeView1: TTreeView;
    Label10: TLabel;
    WVEdit7: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnChangeClick(Sender: TObject);
    procedure btnViewDetailClick(Sender: TObject);
    procedure DBNavigatorClick(Sender: TObject; Button: TNavigateBtn);
    procedure GridDblClick(Sender: TObject);
    procedure cbbCommChange(Sender: TObject);
    procedure btnOpenClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure TreeView1Exit(Sender: TObject);
    procedure TreeView1DblClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure edtUEquChange(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
  private
    EquipParaTreeNodeList: array of TEquipParaTreeNode;
    { Private declarations }
    procedure ShowEquipTree();
    function CreateEquiNodeData(ds:TDataSet):TEquipParaTreeNode;
    procedure FreeEquipParaTreeNode;
    {��������}
    procedure QuickSortEquipNode;
    {��鵱ǰ��һ��A����Ƿ���B���ĸ��׻�������,�ǣ�FALSE ; ��TRUE}
    function CheckAYesOrNoBParent(PTree:TTreeView;A_code:String;B_code:string):boolean;
    {���豸��ʶ����ĳ���ڵ�}
    function FindCurrentEquipNode(P_id:String;PTree:TTreeView):TTreeNode;

    function getParentDevName(pId:Integer): string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetEquipmentInfo: TfaqhSetEquipmentInfo;
  FEquipSubSystemID:string;

implementation

uses KsFrameworks,TypInfo, DBAIntf,SmartCardCommon,KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSetEquipmentInfo.Init;
begin
  inherited;
end;

procedure TfaqhSetEquipmentInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetEquipmentInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetEquipmentInfo.btnChangeClick(Sender: TObject);
var
  tempDataset:TDataset;
  sequtype:string;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  tempDataset:=WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
  if (tempDataset.FieldByName('lvol4').Asinteger=5) then
  begin
   Context.GetDialogSystem.ShowWarning('���ܶ�״̬Ϊע�����豸������Ϣ�޸ģ�');
   Exit;
  end;
  {bug927�м���ԭ��
  if (tempDataset.FieldByName('sbank_pwd2').AsString='FFFFFFFF') then
  begin
   Context.GetDialogSystem.ShowWarning('���ܶԸ��豸������Ϣ�޸ģ�');
   Exit;
  end;
  }
  if (tempDataset.FieldByName('lvol0').AsInteger=1) then
  begin
   Context.GetDialogSystem.ShowWarning('���ܶԸ��豸������Ϣ�޸ģ�');
   Exit;
  end;
  inherited;
  sEquType:=Grid.DataSource.DataSet.fieldbyname('sbank_code').AsString;
  edtParName.Text := GetIdObjectName(-31,Grid.DataSource.DataSet.fieldbyname('damt6').AsString);
end;

procedure TfaqhSetEquipmentInfo.btnViewDetailClick(Sender: TObject);
var
  sEquType:string;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  inherited;
  if datasource.DataSet.RecNo = datasource.DataSet.RecordCount then
    datasource.DataSet.Last;
  sEquType:=Grid.DataSource.DataSet.fieldbyname('sbank_code').AsString;
  edtParName.Text := GetIdObjectName(-31,Grid.DataSource.DataSet.fieldbyname('damt6').AsString);
end;

procedure TfaqhSetEquipmentInfo.DBNavigatorClick(Sender: TObject;
  Button: TNavigateBtn);
begin
  inherited;
  if datasource.DataSet.RecNo = datasource.DataSet.RecordCount then
  begin
    datasource.DataSet.Last;
  end;
  if datasource.DataSet.RecNo = 1 then
  begin
    datasource.DataSet.First;
  end;

end;

procedure TfaqhSetEquipmentInfo.GridDblClick(Sender: TObject);
begin
  inherited;
  btnViewDetail.Click();
end;
procedure TfaqhSetEquipmentInfo.cbbCommChange(Sender: TObject);
var
  port:string;
begin
  port := cbbComm.Text;
  inherited;
end;

procedure TfaqhSetEquipmentInfo.btnOpenClick(Sender: TObject);
begin
  TreeView1.Left:= btnOpen.Left;
  TreeView1.Top:= btnOpen.Top+btnOpen.Height;
  TreeView1.Width:=240;
  TreeView1.Height:=321;
  btnOpen.Enabled := False;
  ShowEquipTree;
  TreeView1.Visible:=True;
  btnOpen.Enabled := True;
  btnOpen.Visible:=False;
  btnClose.Visible:=True;
end;

procedure TfaqhSetEquipmentInfo.ShowEquipTree;
  function FindNodeParent(parent_id : string;
    parent_node: TTreeNode) : TTreeNode;
  var
    curr : TTreeNode;
    curr_data : TEquipParaTreeNode;
  begin
    {�ú������ڲ���parent_id�ŵĽڵ�}
    Result := nil;
    if parent_node = nil then Exit;
    curr := parent_node;
    while curr <> nil do
    begin
      Application.ProcessMessages;
      curr_data := TEquipParaTreeNode(curr.Data);
      // �Ƚ�����
      if (curr_data <> nil)
        and (curr_data.CNodeID = parent_id)  // Ϊ�����
        then
      begin
        Result := curr;
        Exit;
      end
      else
      begin
        // �ݹ����
        Result := FindNodeParent(parent_id,curr.getFirstChild);
        if( Result <> nil ) then
        begin
          Exit;
        end;
        curr := curr.getNextSibling;
      end;
    end;
  end;
  procedure RecursiveBuild(nodes:TTreeNodes);
  var
    parent_id , curr_id :string;
    curr_caption: string;
    parent_node_data , node_data : TEquipParaTreeNode;
    curr_node ,parent_node: TTreeNode;
    i : Integer;
  begin
    parent_node := nil;
    curr_node := nil;
    i := 0;
    //ds.first;
    // �ڵ�����
    while i < Length(EquipParaTreeNodeList)  do
    begin
      // ������Ϣ
      Application.ProcessMessages;
      curr_id := EquipParaTreeNodeList[i].CNodeID;
      parent_id := EquipParaTreeNodeList[i].CParentNodeID;
      // �жϽڵ�
      { ˵����
        ������һ�β��ҵ��ĸ��ڵ㣬�ڱ��β���ʱ�����ж��Ƿ�Ҳ�ǵ�ǰ��
        ���ڵ㣬����ǾͲ���Ҫ�����ˡ�
        �����ѯ�����Ľڵ㰴�ո��ڵ�����򣬽�����������.
      }
      if parent_node <> nil then
      begin
        parent_node_data := TEquipParaTreeNode(parent_node.Data);
        if (parent_node_data <> nil)
          and (parent_node_data.CNodeID = parent_id) then
          parent_node := curr_node.Parent
        else
          parent_node := nil;
      end;
      if parent_node = nil then
        parent_node := FindNodeParent(parent_id,nodes.GetFirstNode);
      // ����ڵ㵽����
      node_data := EquipParaTreeNodeList[i];
      curr_caption := node_data.CNodeCaption;
      curr_node := nodes.AddChildObject(parent_node,curr_caption,node_data);
      curr_node.ImageIndex := 0;
      curr_node.SelectedIndex := 0;
      Inc(i);
    end;
  end;
var
  i:Integer;
  len:integer;
  TreeDataSet:TDataSet;
begin
  Try
    WorkView.FieldByName('��ѯ.���ʹ���').Data.SetString('');
    WorkView.FieldByName('��ѯ.�豸�����ͺ�').Data.SetInteger(0);
    WorkView.FieldByName('��ѯ.��������').Data.SetInteger(0);
    WorkView.FieldByName('��ѯ.������ϵͳ').Data.SetInteger(0);
    WVRequest1.SendCommand;
    // ��������
    TreeDataSet:=TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
    i:=0;
    len := 0;
    TreeDataSet.Last;
    len := TreeDataSet.RecNo;
    SetLength(EquipParaTreeNodeList,len);
    TreeDataSet.First;
    while Not TreeDataSet.eof do
    begin
      EquipParaTreeNodeList[i]:= CreateEquiNodeData(TreeDataSet);
      TreeDataSet.Next;
      Inc(i);
    end;
  except
    on ex : Exception do
    begin
      ShowMessage(ex.Message);
    end;
  end;
  QuickSortEquipNode;
  try
    TreeView1.Items.BeginUpdate;
    try
      // �ͷ�ԭ�����ڴ�
      FreeEquipParaTreeNode;
      //�����豸��
      RecursiveBuild(TreeView1.Items);
      TreeView1.FullCollapse;
      TreeView1.Items.GetFirstNode.Expand(False);
    except
      on ex : Exception do
      begin
        ShowMessage(ex.Message);
      end;
    end;
  finally
    TreeView1.Items.EndUpdate;
    SetLength(EquipParaTreeNodeList,0);
  end;
end;

function TfaqhSetEquipmentInfo.CreateEquiNodeData(
  ds: TDataSet): TEquipParaTreeNode;
var temp : TEquipParaTreeNode;
begin
  Result := nil;
  if ds = nil then
  begin
    raise Exception.Create('���ݼ�Ϊ��!');
    exit;
  end;

  temp := TEquipParaTreeNode.Create;
  try
    temp.CEquipID:=ds.fieldbyname('lvol0').AsInteger ;
    temp.CNodeID:=ds.fieldbyname('sphone3').AsString;
    temp.CNodeCaption:=ds.fieldbyname('scert_no').AsString;
    temp.CNodeKind:=ds.fieldbyname('sbank_code').AsString;
    temp.CParentNodeID:=ds.fieldbyname('sdate1').AsString;
    temp.CNodeKindCaption:=ds.fieldbyname('sbank_code').AsString;
    temp.CEquipRegNo:=ds.fieldbyname('sbank_pwd').AsString;
    temp.CParentNodeCaption := ds.fieldbyname('scert_no').AsString;
    //�豸������ϵͳ
    temp.CEquipSubSystem:=ds.fieldbyname('lserial0').AsString;
    Result := temp;
  except
    on ex :Exception do
    begin
      ShowMessage(ex.Message);
      temp.Free;
    end;
  end;
end;

procedure TfaqhSetEquipmentInfo.QuickSortEquipNode;
  function CompareToNode(s,d: TEquipParaTreeNode):integer;
  begin
    Result := StrComp(PChar(s.CNodeID),PChar(d.CNodeID));
  end;
  procedure QuickSortNodeData(var node_ary : array of TEquipParaTreeNode;
    lo,hi:Integer);
  var
    tmp,anchor : TEquipParaTreeNode;
    lo_tmp,hi_tmp : Integer;
  begin
    //showmessage(inttostr((lo + hi) div 2 + 1));
    if( lo >= hi ) then
      Exit;
    anchor := node_ary[(lo + hi) div 2 + 1];
    lo_tmp := lo;
    hi_tmp := hi;
    while (lo_tmp <= hi_tmp) do
    begin
      while ((CompareToNode(node_ary[lo_tmp],anchor) < 0)
        and (lo_tmp < hi))do
        Inc(lo_tmp);
      while ((CompareToNode(node_ary[hi_tmp],anchor) > 0 )
        and (hi_tmp > lo)) do
        Dec(hi_tmp);
      if ( lo_tmp <= hi_tmp ) then
      begin
        tmp := node_ary[lo_tmp];
        node_ary[lo_tmp] := node_ary[hi_tmp];
        node_ary[hi_tmp] := tmp;
        Inc(lo_tmp);
        Dec(hi_tmp);
      end;
    end;
    if ( lo_tmp < hi ) then
      QuickSortNodeData(node_ary,lo_tmp,hi);
    if ( hi_tmp > lo ) then
      QuickSortNodeData(node_ary,lo,hi_tmp);
  end;
begin
  //showmessage(inttostr(Length(EquipParaTreeNodeList)-1));
  if Length(EquipParaTreeNodeList) <= 1 then
    Exit;

  QuickSortNodeData(EquipParaTreeNodeList,0,Length(EquipParaTreeNodeList)-1);
end;

procedure TfaqhSetEquipmentInfo.FreeEquipParaTreeNode;
  procedure RecursiveFreeNodeData(node : TTreeNode);
  var curr : TTreeNode;
      curr_data : TEquipParaTreeNode;
  begin
    curr := node;
    while curr <> nil do
    begin
      curr_data := TEquipParaTreeNode(curr.Data);
      if curr_data <> nil then
      begin
        curr.Data := nil;
        curr_data.Free;
      end;
      // �ݹ��ӽڵ�
      RecursiveFreeNodeData(curr.getFirstChild);
      curr := curr.getNextSibling;
    end;
  end;
begin
  RecursiveFreeNodeData(TreeView1.Items.GetFirstNode);
  TreeView1.Items.Clear;
end;

procedure TfaqhSetEquipmentInfo.btnCloseClick(Sender: TObject);
var
  id1:Integer;
begin

  if TreeView1.Selected<>nil then
  begin
    edtUEqu.ReadOnly:=False;
    //id1:=TEquipParaTreeNode(TreeView1.Selected.Data).CNodeID;
    id1:=TEquipParaTreeNode(TreeView1.Selected.Data).CEquipID;
    FEquipSubSystemID:=TEquipParaTreeNode(TreeView1.Selected.Data).CEquipSubSystem;
    edtUEqu.Text:=IntToStr(id1);
    edtParName.Text := TEquipParaTreeNode(TreeView1.Selected.Data).CParentNodeCaption;
    edtUEqu.ReadOnly:=True;
  end;
  TreeView1.Visible:=False;
  btnOpen.Visible:=True;
  btnClose.Visible:=False;
end;

procedure TfaqhSetEquipmentInfo.TreeView1Exit(Sender: TObject);
begin
  inherited;
  TreeView1.Visible:=False;
  btnOpen.Visible:=False;
end;

procedure TfaqhSetEquipmentInfo.TreeView1DblClick(Sender: TObject);
var
  id1:string;
begin
  if TreeView1.Selected<>nil then
  begin
    if Trim(edtPhyNo.Text)<>'' then
    begin
      if CheckAYesOrNoBParent(TreeView1,Trim(edtPhyNo.Text),TEquipParaTreeNode(TreeView1.Selected.Data).CNodeID) then
      begin
        edtUEqu.ReadOnly:=False;
        id1:=TEquipParaTreeNode(TreeView1.Selected.Data).CNodeID;
        edtUEqu.Text:=id1;
        edtUEqu.ReadOnly:=True;

        FEquipSubSystemID:=TEquipParaTreeNode(TreeView1.Selected.Data).CEquipSubSystem;
        WorkView.FieldByName('������ϵͳ').Data.SetInteger(StrToInt(FEquipSubSystemID));
        TreeView1.Visible:=False;
        btnOpen.Visible:=False;
      end
     else
     begin
       Context.GetDialogSystem.ShowWarning('��ǰѡ��ĸ��豸�������߼���');
       Exit;
     end;
    end;
  end;
end;

function TfaqhSetEquipmentInfo.CheckAYesOrNoBParent(PTree: TTreeView;
  A_code, B_code: string): boolean;
var
  p_node:TTreeNode;
  Anode,Bnode:TTreeNode;
begin
  result:=True;
  ANode:=FindCurrentEquipNode(A_code,pTree);
  BNode:=FindCurrentEquipNode(B_code,pTree);
  p_node:=BNode;
  while p_node<>nil do
  begin
    if (TEquipParaTreeNode(p_node.Data).CNodeID=A_code) then
    begin
      Result:=False;
      Break;
    end
    else p_node:=p_node.Parent;
  end;
end;

function TfaqhSetEquipmentInfo.FindCurrentEquipNode(P_id: String;
  PTree: TTreeView): TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  p_node:=PTree.Items.item[0];
  for i:=0 to PTree.Items.Count-1 do
  begin
    if (p_node<>nil) and (TEquipParaTreeNode(p_node.Data).CNodeID=P_id) then
    begin
      Result:=p_node;
      break;
    end
    else p_node:=p_node.GetNext;
  end;
end;

procedure TfaqhSetEquipmentInfo.btnOKClick(Sender: TObject);
var
  equType:string;
  tmpMsg:string;
begin
  if Trim(edtEquName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�������豸���ƣ�');
    edtEquName.SetFocus;
    exit;
  end;
  if Trim(cbbEquPhyType.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���豸���ͣ�');
    cbbEquPhyType.SetFocus;
    exit;
  end;
  if Trim(cbbMachineType.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���豸���ͣ�');
    cbbMachineType.SetFocus;
    exit;
  end;
  if Trim(cbbUseType.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���豸��;��');
    cbbUseType.SetFocus;
    exit;
  end;
  if Trim(cbbArea.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���豸��������');
    cbbArea.SetFocus;
    exit;
  end;
  if Trim(cbbChildSys.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���豸������ϵͳ��');
    cbbChildSys.SetFocus;
    exit;
  end;
  if Trim(edtUEqu.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���ϼ��豸��');
    Exit;
  end;
  {
  if (Trim(edtIP.Text)<>'') then
  begin
    tmpMsg := CheckIpAddress(edtIP.Text);
    if tmpMsg<>'' then
    begin
      if Application.MessageBox(PChar(tmpMsg+',��Ҫ����������'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
        Exit;
    end;
  end;
  }
  if Trim(edtSerPortNo.Text)='' then
    edtSerPortNo.Text := '0';
  if Trim(edtSerPortNum.Text)='' then
    edtSerPortNum.Text := '0';
  if Trim(edtMachineNo.Text)='' then
    edtMachineNo.Text := '0';
  WorkView.FieldByName('�Ƿ�֧�ֿ�Ŀ�շ�').Data.SetString('0');
  WorkView.FieldByName('�ϼ��豸�����').Data.SetFloat(StrToFloat(edtUEqu.Text));
  inherited;
  QueryRequest.SendCommand;
end;

procedure TfaqhSetEquipmentInfo.btnCancelClick(Sender: TObject);
begin
  inherited;
  QueryRequest.SendCommand;
end;

function TfaqhSetEquipmentInfo.getParentDevName(pId: Integer): string;
var
  TreeDataSet : TDataSet;
begin
  WorkView1.FieldByName('�豸��ʶ').Data.SetInteger(pId);
  WVRequest2.SendCommand;
  // ��������
  TreeDataSet:=TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  Result := TreeDataSet.fieldbyname('scert_no').AsString;
end;

procedure TfaqhSetEquipmentInfo.edtUEquChange(Sender: TObject);
begin
  {
  if edtUEqu.Text='' then
    Exit;
  edtParName.Text := getParentDevName(StrToInt(edtUEqu.Text));
  }
end;

procedure TfaqhSetEquipmentInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  edtParName.Text := GetIdObjectName(-31,Grid.DataSource.DataSet.fieldbyname('damt6').AsString);

end;

procedure TfaqhSetEquipmentInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  try
    edtParName.Text := GetIdObjectName(-31,Grid.DataSource.DataSet.fieldbyname('damt6').AsString);
  except

  end;
end;

initialization
  TUIStdClassFactory.Create('�豸��Ϣ����',TfaqhSetEquipmentInfo);
end.
