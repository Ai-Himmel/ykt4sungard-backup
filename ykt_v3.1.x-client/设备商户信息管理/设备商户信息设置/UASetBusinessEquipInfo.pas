unit UASetBusinessEquipInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,
  ImgList,Menus,
  RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs, Buttons;

type
  TBusiAndEquipNode1 = class
  public
    BusiID3: Integer;  //�̻���ʶID
    BusiCaption3: String;  //�̻�����
    BusiParentID3: Integer;  //���̻���ʶID
    EquipID3: Integer;   //�豸��ʶ
    EquipCaption3: String;  //�豸����
    EquipIP3: String;  //�豸����ID
    EquipParentIP3: Integer;  //���豸����ID
    EquipType3:String;  //���ʹ���
    ENum3:Integer;  //���
    EBegDate3:String;
    EBegTime3:String;
    EEndDate3:String;
    EEndTime3:String;
    EComment3:String;
  end;

type
  TfaqhSetBusinessEquipInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    WVDigitalEdit2: TWVDigitalEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    WVDigitalEdit1: TWVDigitalEdit;
    WVDigitalEdit3: TWVDigitalEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    Label11: TLabel;
    Label12: TLabel;
    Label1: TLabel;
    Label13: TLabel;
    WVEdit5: TWVEdit;
    Label14: TLabel;
    WVEdit8: TWVEdit;
    UIPanel4: TUIPanel;
    QueryRequest3: TWVRequest;
    WorkView3: TWorkView;
    UIPanel5: TUIPanel;
    UIPanel3: TUIPanel;
    PopupMenu1: TPopupMenu;
    ChaDateTime1: TMenuItem;
    QueryRequest1: TWVRequest;
    WorkView1: TWorkView;
    UIPanel7: TUIPanel;
    Label15: TLabel;
    Label18: TLabel;
    Label17: TLabel;
    Label16: TLabel;
    ImageList1: TImageList;
    treevEquAndBusi2: TTreeView;
    btnAddEB1: TButton;
    btnBefChaEB2: TButton;
    btnBefDelEB2: TButton;
    WorkView5: TWorkView;
    QueryRequest5: TWVRequest;
    DelEquAndBus1: TMenuItem;
    btnReTree1: TButton;
    btnAdDlChOK3: TButton;
    btnAdDlChCcl3: TButton;
    Label19: TLabel;
    Label20: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    QueryRequest6: TWVRequest;
    QueryRequest4: TWVRequest;
    WorkView4: TWorkView;
    WorkView2: TWorkView;
    QueryRequest2: TWVRequest;
    EquipTreVw1: TTreeView;
    Splitter1: TSplitter;
    lbl1: TLabel;
    WVDigitalEdit4: TWVDigitalEdit;
    lbl2: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    {�����̻���Ϣ}
    procedure btnAddClick(Sender: TObject);
    {�޸��̻���Ϣ}
    procedure btnChangeClick(Sender: TObject);
    {��ѯ�̻���Ϣ}
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddEB1Click(Sender: TObject);
    procedure btnBefDelEB2Click(Sender: TObject);
    procedure btnBefChaEB2Click(Sender: TObject);
    procedure treevEquAndBusi2MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure EquipTreVw1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure treevEquAndBusi2MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ChaDateTime1Click(Sender: TObject);
    procedure DelEquAndBus1Click(Sender: TObject);
    procedure btnReTree1Click(Sender: TObject);
    procedure btnAdDlChCcl3Click(Sender: TObject);
    procedure KSFrameEnter(Sender: TObject);
    procedure pcPagesChanging(Sender: TObject; NewIndex: Integer;
      var AllowChange: Boolean);
    procedure tsQueryEnter(Sender: TObject);
    procedure btnAdDlChOK3Click(Sender: TObject);

  private
    used_equi_ary : array of integer;
    SelBusiText2:String;  //���ڼ�¼ѡ���̻��ڵ����ʾ�ı���
    AddMark2:Boolean;  //�����޸ģ�
    DelMark2:Boolean;  //�ж��Ƿ���̻�����ɾ���豸��
    SelEquipText2:String;  //��¼���豸�̻�����ɾ���Ľڵ㣬
    ChaMark2:Boolean;  //�ж��Ƿ���̻������޸��豸��
    NewBusiSel2:Boolean;
    NewEquipSel1:Boolean;
    DelEquSel2:Boolean;
    ChaEquSel2:Boolean;
    CurrentNode2:TTreeNode;
    AddEquList1:array of TBusiAndEquipNode1;
    InsDate2:String;  //���㿪ʼ���ڣ�
    InsDate3:String;  //����������ڣ�
    InsTime2:String;  //����ʱ�䣬
    QeyOneBsEpSet1:TDataSet;  //һ���豸�̻���¼��
    RootEquipName1:String;  //Ĭ�ϵĸ��ڵ��豸��
    {��̨��������CPack�ֶΣ�}
    {�̻���}
    BusiIdcpk:String;  //�̻���ʶ
    BusiNamecpk:String;  //�̻�����
    PareBusiIdcpk:String;  //���̻���ʶ
    {�豸��}
    EquipIdcpk:String;  //�豸��ʶ
    EquipNamecpk:String;  //�豸����
    EquipMaccpk:String;  //�豸����ID
    PareEquipMaccpk:String;  //���豸����ID
    EquipTypecpk:String;  //���ʹ���
    {��ѯ�豸�̻���CPack�ֶ�}
    QBEnumcpk:String;  //�豸�̻�,���
    QBEbusiIdcpk:String;  //�豸�̻�,�̻���ʶ
    QBEequipIdcpk:String;  //�豸�̻�,�豸��ʶ
    QBgnDatecpk:String;  //ʹ�ÿ�ʼ����
    QEndDatecpk:String;  //ʹ�ÿ�ʼ����
    QBenTimecpk:String;  //ʹ�ÿ�ʼʱ��
    QEndTimecpk:String;  //ʹ�ý���ʱ��
    {��ɾ��}
    BEnumcpk:String;  //�豸�̻�,���
    BEbusiIdcpk:String;  //�豸�̻�,�̻���ʶ
    BEequipIdcpk:String;  //�豸�̻�,�豸��ʶ
    BgnDatecpk:String;  //ʹ�ÿ�ʼ����
    EndDatecpk:String;  //ʹ�ÿ�ʼ����
    BenTimecpk:String;  //ʹ�ÿ�ʼʱ��
    EndTimecpk:String;  //ʹ�ý���ʱ��
    Commentcpk:String;  //��ע
    NoRecord:boolean;  //�Ƿ񷵻��޼�¼��
    {���µ����ݽṹ��ʾ�̻����ṹ}
    procedure ShowBusinessTree2;
    {���µ����ݽṹ��ʾ�豸���ṹ}
    procedure ShowEquipTree3;
    {��TreeView ����ʾ���Ʋ���ĳ���ڵ�}
    function FindCurrentNode4(P_id:String;PTree:TTreeView):TTreeNode;
    {�����豸��ʶ������ĳ���ӽڵ�}
    function FindChildNode2(P_id:integer;PNode:TTreeNode;PTree:TTreeView):TTreeNode;
    {���������̻���ʶĳ���ڵ�}
    function FindCurrentBusinessNode3(P_id:integer;PTree:TTreeView):TTreeNode;
    {���������豸��ʶĳ���ڵ�}
    function FindCurrentBusinessNode5(P_id:integer;PTree:TTreeView):TTreeNode;
    {�����豸����IDĳ���ڵ�}
    function FindCurrentBusinessNode4(P_id:String;PTree:TTreeView):TTreeNode;
    {ֻ����Ҷ���豸�����̻��� ���ӷ����豸}
    procedure AddEquipToBusiTree2(B_node2:TTreeNode;E_node1:TTreeNode);
    {���̻��� ����һ���豸}
    procedure AddOneEquip(B_node2:TTreeNode;E_node1:TTreeNode);
    {���������̻��� ɾ��һ���豸}
    procedure DelOneEquip3(B_node2:TTreeNode;E_node1:TTreeNode);
    {���̻��� ����һ���豸֮ǰ��׼��������}
    procedure Bef_AddEqu3(B_node2:TTreeNode;E_node1:TTreeNode);
    {���̻��� ɾ��һ���豸֮ǰ��׼��������}
    procedure Bef_DelEqu3(B_node2:TTreeNode;E_node1:TTreeNode);
    {���̻��� �޸�һ���豸}
    procedure ChaOneEquip1(B_node2:TTreeNode;E_node1:TTreeNode);
    {��ʼ���豸�̻��������η����豸}
    procedure InitEquipToBusiTree;
    {�ڵ��������Ƴ����豸��,�����豸��ʶ��}
    procedure MovedEquipList3(P_Node:TTreeNode;P_Tree:TTreeView);
    {�ͷ��豸�ڵ���}
    procedure FreeEquipParaTreeNode;
    {����һ���豸�̻���¼}
    procedure AddOneRecord(B_node2:TTreeNode;E_node1:TTreeNode);
    {ɾ��һ���豸�̻���¼�����ݱ�ţ�}
    procedure DelOneRecord1(EaB_ID1:integer);
    {�޸�һ���豸�̻���¼�����ݱ�ţ�}
    procedure ChaOneRecord1(EaB_ID1:integer);
    {��ѯһ���豸�̻���¼�����ݱ�ţ�}
    procedure QueryOneRec1(EaB_ID1:integer);
    {ת����ǰ�����ڡ�ʱ���ʽ}
    procedure DateTimeConv1;
    {��ȷ�� ��ť���ɾ��һ���豸��}
    procedure ADC_EB1;
    {�������󣬼��ÿһ���ʱ����Ƿ��ͻ��}
    function CheckDateTime2(B_ID:integer;E_ID:integer;B_D:String;B_T:String;E_D:String;E_T:String):Boolean;
    {�¼�����豸�ڵ㣬}
    function AddNewBusiEquiNode1(D1:TDataSet):TBusiAndEquipNode1;
    {�¼�����̻��ڵ㣬}
    function AddNewBusiNode2(B1:TDataSet):TBusiAndEquipNode1;
    {�¼����j�豸�̻��ڵ㣬}
    function AddNewB_ENode3(B_E3:TDataSet;ENode3:TTreeNode):TBusiAndEquipNode1;
    {�ֶ���WorkView��ֵ������WVEdit��}
    procedure GiveFieldToWVEdits;
    {������������}
    procedure BuildBusiTreeFromDataSet(ds: TDataSet;nodes : TTreeNodes);
    {�����豸��Ϣ����}
    procedure BuildEquiTreeFromDataSet(ds: TDataSet;nodes : TTreeNodes);
    {}
    procedure BuildBusiEquiTreeFromDataSet(ds:TDataSet;nodes : TTreeNodes);
    function CreateNewBusiEquiNodeData(ds : TDataSet;
      insert_node: TTreeNode):TBusiAndEquipNode1;
    {�� yyyymmdd ��ʽ�����ڷָ�� yyyy-mm-dd ��ʽ}
    function SpliteDateStr(str: string):string;
    {�ͷ�������Data}
    procedure FreeTreeNodeData(nodes : TTreeNodes);
    {�����ѷ�����豸ͼ��}
    procedure UpdateAssignedEquiIcon;
    {����û�����������Ƿ���ȷ}
    function CheckInputDateFormat(input:string):boolean;
    {����û������ʱ���Ƿ���ȷ}
    function CheckInputTimeFormat(input:string):boolean;
    { Private declarations }
  public
    {�����ܺ�ĳ�ʼ������}
    procedure Init; override;
    destructor Destroy;override;
    { Public declarations }
  end;

var
  faqhSetBusinessEquipInfo: TfaqhSetBusinessEquipInfo;

implementation

uses
  KsFrameworks, KSFrameWorkUtils;

{$R *.DFM}


procedure TfaqhSetBusinessEquipInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSetBusinessEquipInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetBusinessEquipInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WVDigitalEdit1.Text:='';
  WVDigitalEdit1.Enabled:=false;
  WVEdit2.Text:='';
  WVEdit3.Text:='';
  WVDigitalEdit2.Text:='';
  WVEdit6.Text:='';
  WVDigitalEdit3.Text:='';
  WVEdit7.Text:='';
  WVEdit1.Text:='';
end;

procedure TfaqhSetBusinessEquipInfo.ShowBusinessTree2;
var
  BusiTreeDataSet:TDataSet;
  TempBusinessParaNode2:TBusiAndEquipNode1;
  ParentBusiNode2:TTreeNode;  //���ڲ����̻��ĸ��ڵ㣬
  OwnBusiNode2:TTreeNode;  //���ڲ鱾�̻��ڵ㣬
  RootBusinessParaTreeNode2:TBusiAndEquipNode1;
  NodeText1:String;  //�ڵ����ʾ�ı���
  tmpNode:TTreeNode;
begin
  // BusiTreeDataSet:=TDataSet.Create(nil);
  Try
    WorkView2.FieldByName('�̻���ʶ').Data.SetInteger(0);
    QueryRequest2.SendCommand;
    BusiTreeDataSet:=TDataSet(WorkView2.FieldByName('��ѯ�����').Data.AsObject);
    try
      treevEquAndBusi2.Items.BeginUpdate;
      treevEquAndBusi2.Items.Clear;
      BuildBusiTreeFromDataSet(BusiTreeDataSet,treevEquAndBusi2.Items);
      treevEquAndBusi2.FullCollapse;
    finally
      treevEquAndBusi2.Items.EndUpdate;
    end;
  except
    //ShowMessage('fetch dataset busi');
  end;
end;

{���µ����ݽṹ��ʾ�豸���ṹ}
procedure TfaqhSetBusinessEquipInfo.ShowEquipTree3;
var
  EquipTreeDataSet3 : TDataSet;
begin
  EquipTreeDataSet3:=TDataSet.Create(nil);
  Try
    WorkView3.FieldByName('�豸��ʶ').Data.SetInteger(0);
    QueryRequest3.SendCommand;
    EquipTreeDataSet3:=(WorkView3.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;

    try
      EquipTreVw1.Items.BeginUpdate;
      EquipTreVw1.Items.Clear;
      BuildEquiTreeFromDataSet(EquipTreeDataSet3,EquipTreVw1.Items);
      EquipTreVw1.FullCollapse;
    finally
      EquipTreVw1.Items.EndUpdate;
    end;
  except
    //ShowMessage('fetch data equi');
  end;
end;

{�޸��̻���Ϣ}
procedure TfaqhSetBusinessEquipInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WVDigitalEdit1.Enabled:=false;
  Edit1.ReadOnly:=true;
end;

{��ѯ�̻���Ϣ}
procedure TfaqhSetBusinessEquipInfo.btnQueryClick(Sender: TObject);
begin
  //������ڣ�
  if WVEdit5.Text>WVEdit8.Text then
  begin
    ShowMessage('������ġ�ʹ�ÿ�ʼ���ڡ����ڡ�ʹ�ý������ڡ�������������');
    WVEdit8.Text:='';
  end
  else
  begin
    inherited;
  end;
end;

{��TreeView ����ʾ���Ʋ���ĳ���ڵ�}
function TfaqhSetBusinessEquipInfo.FindCurrentNode4(P_id:String;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  if PTree.Items.Count=0 then
  begin
    //ShowMessage(' �ǿ����� ');
    exit;
  end
  else
  begin
    p_node:=PTree.Items.item[0];
    for i:=0 to PTree.Items.Count-1 do
    begin
      if (PTree.Items.item[i]<>nil) and (PTree.Items.item[i].Text=P_id) then      //�� TreeView ��
      begin
        Result:=PTree.Items.item[i];
        exit;
      end
      else
      begin
        //p_node:=p_node.GetNext;
        //ShowMessage(' ������Ҫ�ҵĽڵ� ');
      end;
    end;
  end;
end;


{�����豸��ʶ������ĳ���ӽڵ�}
function TfaqhSetBusinessEquipInfo.FindChildNode2(P_id:integer;PNode:TTreeNode;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  ShowMessage('a2321 ��ʼ���豸�̻������������̻� '+PNode.Text);
  PNode:=FindCurrentNode4(PNode.Text,PTree);
  ShowMessage('a2322���ҵ����̻��� '+PNode.Text);
  if PNode.Count=0 then
  begin
    exit;
  end
  else
  begin
    p_node:=PNode.item[0];
    ShowMessage('a2323 �ýڵ㺬�е��ӽڵ����� '+IntToStr(PNode.Count));
    for i:=0 to PNode.Count-1 do
    begin
      ShowMessage('a2324 Ҫ�������豸��ʶ�� '+IntToStr(P_id));
      ShowMessage('a2325 �豸�̻����ϱ��豸 '+PNode.item[i].Text+' ���豸��ʶ�� '+IntToStr(TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3));
      if (PNode.item[i]<>nil) and (TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3=P_id) then      //�� TreeView ��
      begin
        Result:=PNode.item[i];
        ShowMessage('a2326 �ҵ����豸�� '+PNode.item[i].Text);
        exit;
      end
      else
      begin
        ;
      end;
    end;
  end;
end;


{�����̻���ʶĳ���ڵ�}
function TfaqhSetBusinessEquipInfo.FindCurrentBusinessNode3(P_id:integer;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  if PTree.Items.Count=0 then
  begin
    //ShowMessage('����������û�нڵ㣬');
    exit;
  end
  else
  begin
    p_node:=PTree.Items[0];
    for i:=0 to PTree.Items.Count-1 do
    begin
      //ShowMessage('���������̻������ǣ�'+PTree.Items[i].Text);
      if  PTree.Items[i].Data<>nil then
      begin
        //ShowMessage('�Ƚ�ǰ���������̻���ʶ�ǣ�'+IntToStr(TBusiAndEquipNode1(PTree.Items[i].Data).BusiID3));
        //ShowMessage('�Ƚ�ǰ Ҫ�����ĸ��̻���ʶ�ǣ�'+IntToStr(P_id));
        if (PTree.Items[i]<>nil) and (TBusiAndEquipNode1(PTree.Items[i].Data).BusiID3=P_id) then
        begin
          Result:=PTree.Items[i];
          exit;
        end
        else
        begin
          ;//ShowMessage('����������û��ƥ��Ľڵ㣬');
        end;
      end
      else
      begin
        ;//ShowMessage('�������Ľڵ� ����Ϊ�գ�');
      end;
    end;
  end;
end;


{���������豸��ʶĳ���ڵ�}
function TfaqhSetBusinessEquipInfo.FindCurrentBusinessNode5(P_id:integer;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  if PTree.Items.Count=0 then
  begin
    //ShowMessage('����������û�нڵ㣬');
    exit;
  end
  else
  begin
    p_node:=PTree.Items[0];
    for i:=0 to PTree.Items.Count-1 do
    begin
      //ShowMessage('���������̻������ǣ�'+PTree.Items[i].Text);
      if  PTree.Items[i].Data<>nil then
      begin
        //ShowMessage('�Ƚ�ǰ���������豸��ʶ�ǣ�'+IntToStr(TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3));
        //ShowMessage('�Ƚ�ǰ Ҫ�����ĸ��̻���ʶ�ǣ�'+IntToStr(P_id));
        //if (PTree.Items[i]<>nil) and (TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3=P_id) then
        if (TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3=P_id) then
        begin
          Result:=PTree.Items[i];
          exit;
        end
        else
        begin
          //ShowMessage('����������û��ƥ��Ľڵ㣬');
        end;
      end
      else
      begin
        //ShowMessage('�������Ľڵ� ����Ϊ�գ�');
      end;
    end;
  end;
end;

{�����豸����IDĳ���ڵ�}
function TfaqhSetBusinessEquipInfo.FindCurrentBusinessNode4(P_id:String;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  if PTree.Items.Count=0 then
  begin
    //ShowMessage('����������û�нڵ㣬');
    exit;
  end;
  p_node:=PTree.Items[0];
  for i:=0 to PTree.Items.Count-1 do
  begin
    //if (p_node<>nil) and (TBusinessParaTreeNode(p_node.Data).CNodeID=P_id) then
    //�����ã�
    //ShowMessage('���������̻������ǣ�'+PTree.Items[i].Text);
   if  PTree.Items[i].Data<>nil then
   begin
      //�����ã�
      //ShowMessage('�Ƚ�ǰ���������̻���ʶ�ǣ�'+IntToStr(TBusiAndEquipNode1(PTree.Items[i].Data).BusiID3));
      //ShowMessage('�Ƚ�ǰ Ҫ�����ĸ��̻���ʶ�ǣ�'+IntToStr(P_id));
      if (PTree.Items[i]<>nil) and (TBusiAndEquipNode1(PTree.Items[i].Data).EquipIP3=P_id) then
      begin
        Result:=PTree.Items[i];
        exit;
      end;
      //else
        //ShowMessage('����������û��ƥ��Ľڵ㣬');
   end;
   //else
     //ShowMessage('�������Ľڵ� ����Ϊ�գ�');
    //else p_node:=p_node.GetNext;
  end;
end;





{ֻ����Ҷ���豸�����̻��� ���ӷ����豸}
procedure TfaqhSetBusinessEquipInfo.AddEquipToBusiTree2(B_node2:TTreeNode;E_node1:TTreeNode);
var
  BusiNode2:TTreeNode;  //���ڼ�¼ѡ�е��̻���Ϣ��
  EquipNode1:TTreeNode;  //���ڼ�¼ѡ�е��豸��Ϣ��
  EquipNode2:TTreeNode;
  Exist2:Boolean;
  CompareBusiNode3:TTreeNode;
  BusiAndEquSet2:TDataSet;
  AddBusiAndEquPara1:TBusiAndEquipNode1;
  EtoB:TTreeNode;
  i:integer;
begin
  BusiNode2:=B_node2;
  //�ж��Ƿ����̻�
  if TBusiAndEquipNode1(BusiNode2.Data).EquipCaption3='' then
  begin
    if (BusiNode2.getFirstChild=nil) or (TBusiAndEquipNode1(BusiNode2.getFirstChild.Data).EquipCaption3<>'') then
    begin
      {
      if E_node1.getFirstChild <> nil then
      begin
        ShowMessage('���豸���ܷ��䣡');
      end;
      }
      AddOneRecord(B_node2,E_node1);
      AddOneEquip(B_node2,E_node1);
      ShowMessage('�����豸�ɹ���');
      //else
      //begin
      // TODO : ���ӵݹ鴦��Ĺ���
      //  MovedEquipList3(E_node1,EquipTreVw1);
      //end;

    end
    else
    begin
      ShowMessage(' ����Ҷ���̻� ');
    end;  //(BusiNode2.getFirstChild=nil)
  end
  else
  begin
    ShowMessage(' �����̻��ڵ� ');
  end;
end;


{���̻��� ����һ���豸}
procedure TfaqhSetBusinessEquipInfo.AddOneEquip(B_node2:TTreeNode;E_node1:TTreeNode);
var
  AddBusiAndEquPara1:TBusiAndEquipNode1;
  BusiAndEquSet2:TDataSet;
begin
  if B_node2<>nil then
  begin
    if E_node1<>nil then
    begin
      //ShowMessage('��ѡ�����豸 ');
      //ShowMessage('��ʼ����豸 ');
      treevEquAndBusi2.Items.BeginUpdate;
      AddBusiAndEquPara1:=TBusiAndEquipNode1.Create;
      try
        //ShowMessage(' ת����ǰ�����ڡ�ʱ���ʽ ');
        DateTimeConv1;
        //֧�ִ����ڵ㣬�����豸�̻���¼�������Ϣ:�̻���ʶ��
        AddBusiAndEquPara1.BusiID3:=TBusiAndEquipNode1(B_node2.Data).BusiID3;
        AddBusiAndEquPara1.EquipID3:=TBusiAndEquipNode1(E_node1.Data).EquipID3;
        AddBusiAndEquPara1.EquipCaption3:=TBusiAndEquipNode1(E_node1.Data).EquipCaption3;
        AddBusiAndEquPara1.EquipIP3:=TBusiAndEquipNode1(E_node1.Data).EquipIP3;
        AddBusiAndEquPara1.EquipParentIP3:=TBusiAndEquipNode1(E_node1.Data).EquipParentIP3;
        AddBusiAndEquPara1.EquipType3:=TBusiAndEquipNode1(E_node1.Data).EquipType3;
        AddBusiAndEquPara1.EBegDate3:=WVEdit2.Text;
        //AddBusiAndEquPara1.EBegDate3:=InsDate2;
        //AddBusiAndEquPara1.EBegTime3:=InsTime2;
        AddBusiAndEquPara1.EBegTime3:=WVEdit6.Text;
        //AddBusiAndEquPara1.EBegTime3:='000000';
        //AddBusiAndEquPara1.EEndDate3:=InsDate3;
        InsDate3:=Copy(InsDate2,1,3)+IntToStr(StrToInt(Copy(InsDate2,4,1))+5)+Copy(InsDate2,5,4);
        AddBusiAndEquPara1.EEndDate3:=WVEdit3.Text;
        //AddBusiAndEquPara1.EEndDate3:=Copy(InsDate2,1,3)+IntToStr(StrToInt(Copy(InsDate2,4,1))+5)+Copy(InsDate2,5,4);
        //AddBusiAndEquPara1.EEndTime3:=InsTime2;
        AddBusiAndEquPara1.EEndTime3:=WVEdit7.Text;
        //AddBusiAndEquPara1.EEndTime3:='235959';
        AddBusiAndEquPara1.EComment3:=WVEdit1.Text;
        //AddBusiAndEquPara1.EComment3:='���� '+DateToStr(Date)+' '+TimeToStr(Time)+' �������豸';
        //ShowMessage(' ��ʼ���ʱ����Ƿ��ͻ�� ');
        if CheckDateTime2(TBusiAndEquipNode1(B_node2.Data).BusiID3,TBusiAndEquipNode1(E_node1.Data).EquipID3,InsDate2,'000000',InsDate3,'235959')=true then
        begin
          ShowMessage(' ���������Ӹ��豸�ڵ㣡�ѱ����䣡 ');
          //ShowMessage(' �˳�ǰ�������£� ');
          treevEquAndBusi2.Items.EndUpdate;
          exit;
        end
        else
        begin
          ;//ShowMessage(' �����Ӹ��豸�ڵ㣡 ');
        end;
        //ShowMessage(' ���ӽڵ㣬 ');
        treevEquAndBusi2.Items.AddChild(B_node2,E_node1.Text+' ('+DateTimeToStr(DBStrDateToDateTime(AddBusiAndEquPara1.EBegDate3))+' -> '+DateTimeToStr(DBStrDateToDateTime(AddBusiAndEquPara1.EEndDate3))+')');
        //ShowMessage(' �洢�豸�̻���Ϣ�� ');
        B_node2.Item[B_node2.Count-1].Data:=AddBusiAndEquPara1;
        CurrentNode2:=B_node2.Item[B_node2.Count-1];
        //ShowMessage('���豸�̻�������ȥ�� ');
        WorkView.FieldByName('���').Data.SetInteger(0);
        //ShowWaiting('');
        QueryRequest.SendCommand;
        //CloseWaiting;
        BusiAndEquSet2:=(WorkView.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;
        BusiAndEquSet2.Last;
        TBusiAndEquipNode1(B_node2.Item[B_node2.Count-1].Data).ENum3:=BusiAndEquSet2.fieldbyname(EquipIdcpk).AsInteger;
        treevEquAndBusi2.FullExpand;
        treevEquAndBusi2.Items.EndUpdate;
        //ShowMessage('����豸�ɹ�');
      finally
        ;//ShowMessage(' ������ʱ�ڵ�ʧ�ܣ� ');
      end;
    end
    else
    begin
      ;//ShowMessage('�����ұ�ѡ���豸');
    end;
  end
  else
  begin
    ;//ShowMessage('����û��ѡ���̻�');
  end;
end;


{���������̻��� ɾ��һ���豸}
procedure TfaqhSetBusinessEquipInfo.DelOneEquip3(B_node2:TTreeNode;E_node1:TTreeNode);
begin
  treevEquAndBusi2.Items.BeginUpdate;
  B_node2.Delete;
  treevEquAndBusi2.Items.EndUpdate;
end;


{���̻��� ����һ���豸֮ǰ��׼��������}
procedure TfaqhSetBusinessEquipInfo.Bef_AddEqu3(B_node2:TTreeNode;E_node1:TTreeNode);
begin
  if E_node1<>nil then
  begin
    if TBusiAndEquipNode1(B_node2.Data).EquipCaption3='' then
    begin
      if (B_node2.getFirstChild=nil) or ((B_node2.getFirstChild<>nil) and (TBusiAndEquipNode1(B_node2.getFirstChild.Data).EquipCaption3<>'')) then
      begin
        if TBusiAndEquipNode1(E_node1.Data).EquipType3<>'0000' then
        begin
          if TBusiAndEquipNode1(E_node1.Data).EquipType3<>'5301' then
          begin
            //ShowMessage(' ���ر�ſ� ');
            WVDigitalEdit1.Visible:=False;
            btnOK.visible:=False;
            btnCancel.visible:=False;
            //ShowMessage(' ��һ���޸ı�ǣ� ');
            tsQuery.TabVisible:=false;
            tsEdit.TabVisible:=true;
            tsEdit.Show;
            WVDigitalEdit1.enabled:=false;
            WVDigitalEdit2.enabled:=false;
            WVDigitalEdit3.enabled:=false;
            WVDigitalEdit2.Text:=IntToStr(TBusiAndEquipNode1(E_node1.Data).EquipID3);
            WVDigitalEdit3.Text:=IntToStr(TBusiAndEquipNode1(B_node2.Data).BusiID3);
            //ShowMessage(' ����豸���ơ��̻����� ');
            Edit1.Text:=TBusiAndEquipNode1(E_node1.Data).EquipCaption3;
            Edit2.Text:=TBusiAndEquipNode1(B_node2.Data).BusiCaption3;
            DateTimeConv1;
            WVEdit2.Text:=InsDate2;
            //WVEdit3.Text:=InsDate3;
            WVEdit3.Text:=Copy(InsDate2,1,3)+IntToStr(StrToInt(Copy(InsDate2,4,1))+5)+Copy(InsDate2,5,4);
            //WVEdit6.Text:=InsTime2;
            WVEdit6.Text:='000000';
            //WVEdit7.Text:=InsTime2;
            WVEdit7.Text:='235959';
            WVEdit1.Text:='���� '+DateToStr(Date)+' '+TimeToStr(Time)+' �������豸';
            //ShowMessage(' �޸��������ӵı�� ');
            AddMark2:=True;
          end
          else
          begin
            ShowMessage(' LPort���ܱ�����! ');
          end;
        end
        else
        begin
          ShowMessage(' ���ܷ�����̻�! ');
        end;
      end
      else
      begin
        ShowMessage('��Ҷ���̻����ܷ����豸��');
      end;
    end
    else if TBusiAndEquipNode1(B_node2.Data).EquipCaption3<>'' then
    begin
      ShowMessage('�������ѡ���̻���');
    end;
  end
  else
  begin
    ShowMessage('����δѡ���豸��');
  end;
end;

{���̻��� ɾ��һ���豸֮ǰ��׼��������}
procedure TfaqhSetBusinessEquipInfo.Bef_DelEqu3(B_node2:TTreeNode;E_node1:TTreeNode);
var
  EquipDataSet2:TDataSet;
  DelEquipID2:Integer;
  ParentBusiID5:Integer;
begin
  if B_node2<>nil then
  begin
    //ShowMessage(' ��ѯ��������ɾ�����豸�̻���¼ ');
    QueryOneRec1(TBusiAndEquipNode1(B_node2.Data).ENum3);
    btnOK.visible:=False;
    btnCancel.visible:=False;
    //ShowMessage(' ����豸���ơ��̻����� ');
    Edit1.Text:=TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).EquipCaption3;
    Edit2.Text:=TBusiAndEquipNode1(treevEquAndBusi2.Selected.Parent.Data).BusiCaption3;
    GiveFieldToWVEdits;
    //ShowMessage(' ��һ���޸ı�ǣ� ');
    tsQuery.TabVisible:=false;
    tsEdit.TabVisible:=true;
    tsEdit.Show;
    //ShowMessage(' �޸�����ɾ���ı�� ');
    DelMark2:=True;
  end
  else
  begin
    ShowMessage('�������ѡ���豸');
  end;
end;


{���̻��� �޸�һ���豸}
procedure TfaqhSetBusinessEquipInfo.ChaOneEquip1(B_node2:TTreeNode;E_node1:TTreeNode);
var
  BusiID4:integer;
  BusiDataSet4:TDataSet;
  ChaBusiCap4:String;
  ChaParentBusiNode4:TTreeNode;
begin
  //ShowMessage(' �޸��豸�ڵ����Ϣ�� ');
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EBegDate3:=WVEdit2.Text;
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EBegTime3:=WVEdit6.Text;
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EEndDate3:=WVEdit3.Text;
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EEndTime3:=WVEdit7.Text;
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EComment3:=WVEdit1.Text;
  //ShowMessage(' ��ʾ��Ϣ���޸ģ��豸�ڵ����Ϣ�� ');
  treevEquAndBusi2.Selected.Text:=Edit1.Text+' ('
        +DateTimeToStr(DBStrDateToDateTime(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).EBegDate3))
        +' -> '+DateTimeToStr(DBStrDateToDateTime(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).EEndDate3))+')';
end;


{���̻��� ���ӷ����豸}
procedure TfaqhSetBusinessEquipInfo.InitEquipToBusiTree;
var
  BusiAndEquipSet1:TDataSet;
begin
  //���»�ȡ�����豸�̻���¼��
  WorkView.FieldByName('���').Data.SetInteger(0);
  //ShowMessage(' ���ÿ�ܲ�ѯ�豸�̻����¼�� ');
  //QueryRequest.SendCommand;
  //ShowMessage(' �����ÿ�ܲ�ѯ�豸�̻����¼�� ');
  BusiAndEquipSet1 := TDataSet.Create(nil);
  try
    QueryRequest6.SendCommand;
    BusiAndEquipSet1:=(WorkView.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;
    try
      treevEquAndBusi2.Items.BeginUpdate;
      BuildBusiEquiTreeFromDataSet(BusiAndEquipSet1,
        treevEquAndBusi2.Items);
      treevEquAndBusi2.FullCollapse;
    finally
      treevEquAndBusi2.Items.EndUpdate;
    end;
    try
      UpdateAssignedEquiIcon;
    finally
      // �ͷ��ڴ�
      SetLength(used_equi_ary,0);
    end;
  except
    on ex : Exception do
    begin
      Context.GetDialogSystem.ShowMessage (Ex.Message);
    end;
  end;
end;


{�ڵ��������Ƴ����豸��,�����豸��ʶ��}
procedure TfaqhSetBusinessEquipInfo.MovedEquipList3(P_Node:TTreeNode;P_Tree:TTreeView);
var
  TempNode1:TTreeNode;  //���ڼ�¼���豸�����ҵ��Ľڵ㣬
  TempNode2:TTreeNode;
  CurrentEquID1:integer;  //��ǰ�����ж����������Ƿ�������豸��ʶ��
  CurrentId:integer;  //��¼�豸�����±꣬
  i:integer;
begin
  i:=0;
  CurrentId:=0;

  FreeEquipParaTreeNode;

  SetLength(AddEquList1,i+1);
  AddEquList1[i]:=TBusiAndEquipNode1.create;
  AddEquList1[i].BusiID3:=0;
  AddEquList1[i].EquipID3:=TBusiAndEquipNode1(P_Node.Data).EquipID3;
  AddEquList1[i].EquipCaption3:=TBusiAndEquipNode1(P_Node.Data).EquipCaption3;
  AddEquList1[i].EquipIP3:=TBusiAndEquipNode1(P_Node.Data).EquipIP3;
  AddEquList1[i].EquipParentIP3:=TBusiAndEquipNode1(P_Node.Data).EquipParentIP3;
  AddEquList1[i].EquipType3:=TBusiAndEquipNode1(P_Node.Data).EquipType3;
  AddEquList1[i].EBegDate3:='';
  AddEquList1[i].EBegTime3:='';
  AddEquList1[i].EEndDate3:='';
  AddEquList1[i].EEndTime3:='';
  AddEquList1[i].EComment3:='';
  //ShowMessage('��� '+AddEquList1[i].EquipCaption3+' ���豸���� '+IntToStr(i)+' λ�óɹ�');

  CurrentEquID1:=AddEquList1[CurrentId].EquipID3;

  //������ʾ���豸��ʶ�����豸���ȥ�ҵ����豸�ڵ㣬ǰ�᣺��֤�����㷨��ȷ��
  TempNode1:=FindCurrentBusinessNode5(CurrentEquID1,P_Tree);

  //������豸�����ҵ�����������豸�������ĵ�һ�����豸��ӵ��豸���У�
  if TempNode1<>nil then
  begin
    //ShowMessage('���豸���ҵ����豸����');
    If TempNode1.getFirstChild<>nil then
    begin
      TempNode2:=TempNode1.getFirstChild;

      i:=i+1;
      SetLength(AddEquList1,i+1);
      AddEquList1[i]:=TBusiAndEquipNode1.create;
      AddEquList1[i].BusiID3:=0;
      AddEquList1[i].EquipID3:=TBusiAndEquipNode1(TempNode2.Data).EquipID3;
      AddEquList1[i].EquipCaption3:=TBusiAndEquipNode1(TempNode2.Data).EquipCaption3;
      AddEquList1[i].EquipIP3:=TBusiAndEquipNode1(TempNode2.Data).EquipIP3;
      AddEquList1[i].EquipParentIP3:=TBusiAndEquipNode1(TempNode2.Data).EquipParentIP3;
      AddEquList1[i].EquipType3:=TBusiAndEquipNode1(TempNode2.Data).EquipType3;
      AddEquList1[i].EBegDate3:='';
      AddEquList1[i].EBegTime3:='';
      AddEquList1[i].EEndDate3:='';
      AddEquList1[i].EEndTime3:='';
      AddEquList1[i].EComment3:='';
      //ShowMessage('��� '+AddEquList1[i].EquipCaption3+' ���豸���� '+IntToStr(i)+' λ�óɹ�');

      While TempNode2.getNextSibling<>nil do
      begin
        TempNode2:=TempNode2.getNextSibling;

        i:=i+1;
        SetLength(AddEquList1,i+1);
        AddEquList1[i]:=TBusiAndEquipNode1.create;
        AddEquList1[i].BusiID3:=0;
        AddEquList1[i].EquipID3:=TBusiAndEquipNode1(TempNode2.Data).EquipID3;
        AddEquList1[i].EquipCaption3:=TBusiAndEquipNode1(TempNode2.Data).EquipCaption3;
        AddEquList1[i].EquipIP3:=TBusiAndEquipNode1(TempNode2.Data).EquipIP3;
        AddEquList1[i].EquipParentIP3:=TBusiAndEquipNode1(TempNode2.Data).EquipParentIP3;
        AddEquList1[i].EquipType3:=TBusiAndEquipNode1(TempNode2.Data).EquipType3;
        AddEquList1[i].EBegDate3:='';
        AddEquList1[i].EBegTime3:='';
        AddEquList1[i].EEndDate3:='';
        AddEquList1[i].EEndTime3:='';
        AddEquList1[i].EComment3:='';
        //ShowMessage('��� '+AddEquList1[i].EquipCaption3+' ���豸���� '+IntToStr(i)+' λ�óɹ�');

      end;  //TempNode2.getNextSibling<>nil
    end;
  end  //TempNode1<>nil
  else
  begin
    ShowMessage('���豸���������豸���ϣ�');
  end;

  //��̬���� �豸�����豸�ڵ㣬
  //ShowMessage('��ǰ��ǵ��豸��ʶ�� '+IntToStr(CurrentEquID1));
  While CurrentEquID1<>AddEquList1[length(AddEquList1)-1].EquipID3 do
  begin
    //�ƶ���ǰ�����ж����������豸���ƣ�
    CurrentId:=CurrentId+1;
    CurrentEquID1:=AddEquList1[CurrentId].EquipID3;

    //���豸����ȥ�ҵ����豸�ڵ㣬��������豸�������ĵ�һ�����豸��ӵ��豸���У�
    TempNode1:=FindCurrentBusinessNode5(CurrentEquID1,P_Tree);

    if TempNode1<>nil then
    begin
      If TempNode1.getFirstChild<>nil then
      begin
        TempNode2:=TempNode1.getFirstChild;

        i:=i+1;
        SetLength(AddEquList1,i+1);
        AddEquList1[i]:=TBusiAndEquipNode1.create;
        AddEquList1[i].BusiID3:=0;
        AddEquList1[i].EquipID3:=TBusiAndEquipNode1(TempNode2.Data).EquipID3;
        AddEquList1[i].EquipCaption3:=TBusiAndEquipNode1(TempNode2.Data).EquipCaption3;
        AddEquList1[i].EquipIP3:=TBusiAndEquipNode1(TempNode2.Data).EquipIP3;
        AddEquList1[i].EquipParentIP3:=TBusiAndEquipNode1(TempNode2.Data).EquipParentIP3;
        AddEquList1[i].EquipType3:=TBusiAndEquipNode1(TempNode2.Data).EquipType3;
        AddEquList1[i].EBegDate3:='';
        AddEquList1[i].EBegTime3:='';
        AddEquList1[i].EEndDate3:='';
        AddEquList1[i].EEndTime3:='';
        AddEquList1[i].EComment3:='';
        //ShowMessage('��� '+AddEquList1[i].EquipCaption3+' ���豸���� '+IntToStr(i)+' λ�óɹ�');

        While TempNode2.getNextSibling<>nil do
        begin
          TempNode2:=TempNode2.getNextSibling;

          i:=i+1;
          SetLength(AddEquList1,i+1);
          AddEquList1[i]:=TBusiAndEquipNode1.create;
          AddEquList1[i].BusiID3:=0;
          AddEquList1[i].EquipID3:=TBusiAndEquipNode1(TempNode2.Data).EquipID3;
          AddEquList1[i].EquipCaption3:=TBusiAndEquipNode1(TempNode2.Data).EquipCaption3;
          AddEquList1[i].EquipIP3:=TBusiAndEquipNode1(TempNode2.Data).EquipIP3;
          AddEquList1[i].EquipParentIP3:=TBusiAndEquipNode1(TempNode2.Data).EquipParentIP3;
          AddEquList1[i].EquipType3:=TBusiAndEquipNode1(TempNode2.Data).EquipType3;
          AddEquList1[i].EBegDate3:='';
          AddEquList1[i].EBegTime3:='';
          AddEquList1[i].EEndDate3:='';
          AddEquList1[i].EEndTime3:='';
          AddEquList1[i].EComment3:='';
          //ShowMessage('��� '+AddEquList1[i].EquipCaption3+' ���豸���� '+IntToStr(i)+' λ�óɹ�');

        end;  //TempNode2.getNextSibling<>nil
      end;
    end;  //TempNode1<>nil
  end;  //While CurrentEquID1<>

end;


{�ͷ��豸�ڵ���}
procedure TfaqhSetBusinessEquipInfo.FreeEquipParaTreeNode;
var
  i:integer;
  len:integer;
begin
  len:=Length(AddEquList1);
  for i:=0 to len-1 do
    AddEquList1[i].Free;
  SetLength(AddEquList1,0);
  //�����ã�
  //ShowMessage('�Ѱ��豸�ڵ������');
end;


{����һ���豸�̻���¼}
procedure TfaqhSetBusinessEquipInfo.AddOneRecord(B_node2:TTreeNode;E_node1:TTreeNode);
begin
  //ShowMessage(' ����һ����¼�� ');
  WorkView.FieldByName('�豸��ʶ').Data.SetInteger(TBusiAndEquipNode1(E_node1.Data).EquipID3);
  WorkView.FieldByName('�̻���ʶ').Data.SetFloat(TBusiAndEquipNode1(B_node2.Data).BusiID3);
  //ShowMessage(' ���¼���ʱ�䣬 ');
  DateTimeConv1;
  WorkView.FieldByName('ʹ�ÿ�ʼ����').Data.SetString(WVEdit2.Text);
  //WorkView.FieldByName('ʹ�ÿ�ʼ����').Data.SetString(InsDate2);
  //WorkView.FieldByName('ʹ�ÿ�ʼʱ��').Data.SetString(InsTime2);
  WorkView.FieldByName('ʹ�ÿ�ʼʱ��').Data.SetString(WVEdit6.Text);
  //WorkView.FieldByName('ʹ�ÿ�ʼʱ��').Data.SetString('000000');
  InsDate3:=Copy(InsDate2,1,3)+IntToStr(StrToInt(Copy(InsDate2,4,1))+5)+Copy(InsDate2,5,4);
  WorkView.FieldByName('ʹ�ý�������').Data.SetString(WVEdit3.Text);
  //WorkView.FieldByName('ʹ�ý�������').Data.SetString(InsDate3);
  //WorkView.FieldByName('ʹ�ý���ʱ��').Data.SetString(InsTime2);
  WorkView.FieldByName('ʹ�ý���ʱ��').Data.SetString(WVEdit7.Text);
  //WorkView.FieldByName('ʹ�ý���ʱ��').Data.SetString('235959');
  WorkView.FieldByName('��ע').Data.SetString(WVEdit1.Text);
  //WorkView.FieldByName('��ע').Data.SetString('���� '+DateToStr(Date)+' '+TimeToStr(Time)+' �������豸');
  //ShowMessage(' ��ʼ���ʱ���Ƿ��ͻ ');
  if CheckDateTime2(TBusiAndEquipNode1(B_node2.Data).BusiID3,TBusiAndEquipNode1(E_node1.Data).EquipID3,InsDate2,'000000',InsDate3,'235959')=true then
  begin
    ShowMessage(' ���豸�ڸ�ʱ����ѱ����䣡 ');
    exit;
  end
  else
  begin
    ;//ShowMessage(' ���豸�ڸ�ʱ��οɷ��䣡 ');
  end;

  //ShowWaiting('');
  AddRequest.SendCommand;
  //CloseWaiting;
  //ShowMessage('�����豸 '+TBusiAndEquipNode1(E_node1.Data).EquipCaption3+' �̻� '+TBusiAndEquipNode1(B_node2.Data).BusiCaption3+' ��¼�ɹ�');
end;


{ɾ��һ���豸�̻���¼�����ݱ�ţ�}
procedure TfaqhSetBusinessEquipInfo.DelOneRecord1(EaB_ID1:integer);
begin
  //ShowMessage('��ɾ����¼���豸������ '+SelEquipText2);
  WorkView.FieldByName('���').Data.SetInteger(EaB_ID1);
  //�����ã�
  //ShowMessage('��ɾ���豸�ı���� ');
  //ShowWaiting('');
  DeleteRequest.SendCommand;
  //CloseWaiting;
end;


{�޸�һ���豸�̻���¼�����ݱ�ţ�}
procedure TfaqhSetBusinessEquipInfo.ChaOneRecord1(EaB_ID1:integer);
begin
  WorkView.FieldByName('���').data.SetInteger(EaB_ID1);
  WorkView.FieldByName('�豸��ʶ').data.SetInteger(StrToInt(Trim(WVDigitalEdit2.Text)));
  WorkView.FieldByName('�̻���ʶ').data.SetFloat(StrToFloat(Trim(WVDigitalEdit3.Text)));
  WorkView.FieldByName('ʹ�ÿ�ʼ����').data.SetString(Trim(WVEdit2.Text));
  WorkView.FieldByName('ʹ�ÿ�ʼʱ��').data.SetString(Trim(WVEdit6.Text));
  WorkView.FieldByName('ʹ�ý�������').data.SetString(Trim(WVEdit3.Text));
  WorkView.FieldByName('ʹ�ý���ʱ��').data.SetString(Trim(WVEdit7.Text));
  WorkView.FieldByName('��ע').data.SetString(Trim(WVEdit1.Text));
  //ShowMessage('�����ѷ��ͣ� ');
  //ShowWaiting('');
  ChangeRequest.SendCommand;
  //CloseWaiting;
  //ShowMessage('�޸�ִ����ϣ� ');
end;


{��ѯһ���豸�̻���¼�����ݱ�ţ�}
procedure TfaqhSetBusinessEquipInfo.QueryOneRec1(EaB_ID1:integer);
begin
  WorkView.FieldByName('���').Data.SetInteger(EaB_ID1);
  //ShowMessage('���޸��豸�ı���� '+IntToStr(EaB_ID1));
  //ShowWaiting('');
  QueryRequest.SendCommand;
  //CloseWaiting;
  //ShowMessage('Ҫ�޸��豸�̻���¼�Ѿ��鵽');
  QeyOneBsEpSet1:=(WorkView.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;
end;


{��ȷ�� ��ť���ɾ��һ���豸��}
procedure TfaqhSetBusinessEquipInfo.ADC_EB1;
begin
end;


{ת����ǰ�����ڡ�ʱ���ʽ}
procedure TfaqhSetBusinessEquipInfo.DateTimeConv1;
begin
  if length(DateToStr(Date))>=10 then
  begin
    InsDate2:=Copy(DateToStr(Date),1,4)+Copy(DateToStr(Date),6,2)+Copy(DateToStr(Date),9,2);
  end
  else if length(DateToStr(Date))<=8 then
  begin  //����2005-1-1
    InsDate2:=Copy(DateToStr(Date),1,4)+Copy(DateToStr(Date),6,1)+Copy(DateToStr(Date),8,1);
  end
  else
  begin
    if Copy(DateToStr(Date),7,1)='-' then
    begin
      InsDate2:=Copy(DateToStr(Date),1,4)+'0'+Copy(DateToStr(Date),6,1)+Copy(DateToStr(Date),8,2);
    end
    else
    begin
      InsDate2:=Copy(DateToStr(Date),1,4)+Copy(DateToStr(Date),6,2)+'0'+Copy(DateToStr(Date),9,1);
    end;
  end;

  if length(DateToStr(Date+1))>=10 then
  begin
    InsDate3:=Copy(DateToStr(Date+1),1,4)+Copy(DateToStr(Date+1),6,2)+Copy(DateToStr(Date+1),9,2);
  end
  else if length(DateToStr(Date+1))<=8 then
  begin  //����2005-1-1
    InsDate3:=Copy(DateToStr(Date+1),1,4)+'0'+Copy(DateToStr(Date+1),6,1)+'0'+Copy(DateToStr(Date+1),8,1);
  end
  else
  begin
    if Copy(DateToStr(Date+1),7,1)='-' then
    begin
      InsDate3:=Copy(DateToStr(Date+1),1,4)+'0'+Copy(DateToStr(Date+1),6,1)+Copy(DateToStr(Date+1),8,2);
    end
    else
    begin
      InsDate3:=Copy(DateToStr(Date+1),1,4)+Copy(DateToStr(Date+1),6,2)+'0'+Copy(DateToStr(Date+1),9,1);
    end;
  end;

  if length(TimeToStr(Time))>=6 then
  begin
    InsTime2:=Copy(TimeToStr(Time),1,2)+Copy(TimeToStr(Time),4,2)+Copy(TimeToStr(Time),7,2);
  end
  else
  begin
    InsTime2:='0'+Copy(TimeToStr(Time),1,1)+Copy(TimeToStr(Time),3,2)+Copy(TimeToStr(Time),6,2);
  end;
end;


{�������󣬼��ÿһ���ʱ����Ƿ��ͻ��,��ĳһ�豸���жϣ��������ж����ĸ��̻���}
function TfaqhSetBusinessEquipInfo.CheckDateTime2(B_ID:integer;E_ID:integer;B_D:String;B_T:String;E_D:String;E_T:String):Boolean;
var
  BusiAndEquipSet1:TDataSet;
begin
  result:=false;
  //���»�ȡ�����豸�̻���¼��
  WorkView.FieldByName('���').Data.SetInteger(0);
  try
    QueryRequest.SendCommand;
  except
    exit;//ShowMessage(' �̻��豸���޼�¼�� ');
  end;
  BusiAndEquipSet1:=(WorkView.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;
  if BusiAndEquipSet1.RecordCount<=1 then
  begin
    //ShowMessage(' �̻��豸���޼�¼�� ');
    exit;
  end
  else
  begin
    BusiAndEquipSet1.First;
    While not BusiAndEquipSet1.Eof do
    begin
      //ShowMessage(' ������¼���Ƚϣ� ');
      if BusiAndEquipSet1.fieldbyname(BEnumcpk).AsInteger<>TBusiAndEquipNode1(treevEquAndBusi2.Selected.data).Enum3 then
      begin
        if BusiAndEquipSet1.fieldbyname(BEequipIdcpk).AsInteger=E_ID then
        begin
          //ShowMessage(' ���жϿ�ʼ�ģ� ');
          if BusiAndEquipSet1.fieldbyname(BgnDatecpk).AsString<B_D then
          begin
            if B_D<BusiAndEquipSet1.fieldbyname(EndDatecpk).AsString then
            begin
              if BusiAndEquipSet1.fieldbyname(BenTimecpk).AsString<B_T then
              begin
                if B_T<BusiAndEquipSet1.fieldbyname(EndTimecpk).AsString then
                begin
                  result:=True;
                  exit;
                end;
              end;  //if BusiAndEquipSet1.fieldbyname(BenTimecpk)
            end;
          end;
          //ShowMessage(' ���жϽ����ģ� ');
          if BusiAndEquipSet1.fieldbyname(BgnDatecpk).AsString<E_D then
          begin
            if E_D<BusiAndEquipSet1.fieldbyname(EndDatecpk).AsString then
            begin
              if BusiAndEquipSet1.fieldbyname(BenTimecpk).AsString<E_T then
              begin
                if E_T<BusiAndEquipSet1.fieldbyname(EndTimecpk).AsString then
                begin
                  result:=True;
                  exit;
                end;
              end;
            end;
          end;
        end;
      end
      else
      begin
        ;//ShowMessage(' ������¼����Ҫ�޸� ');
      end;
      BusiAndEquipSet1.next;
    end;
  end;
end;


{�¼�����豸�ڵ㣬}
function TfaqhSetBusinessEquipInfo.AddNewBusiEquiNode1(D1:TDataSet):TBusiAndEquipNode1;
var
  TempBusinessParaNode3:TBusiAndEquipNode1;  //��ʱ�ڵ㣬
  str : string;
begin
  TempBusinessParaNode3:=TBusiAndEquipNode1.Create;
  try
    if D1<>nil then
    begin
      //ShowMessage(' �豸��ʶ�� '+D1.fieldbyname(EquipIdcpk).AsString);
      TempBusinessParaNode3.BusiID3:=0;
      TempBusinessParaNode3.BusiCaption3:='';
      TempBusinessParaNode3.BusiParentID3:=0;
      TempBusinessParaNode3.EquipID3:=D1.fieldbyname(EquipIdcpk).AsInteger;  //�豸��ʶ
      TempBusinessParaNode3.EquipCaption3:=D1.fieldbyname(EquipNamecpk).AsString;  //�豸����
      TempBusinessParaNode3.EquipIP3:=D1.fieldbyname(EquipMaccpk).AsString;  //�豸����ID
      TempBusinessParaNode3.EquipParentIP3:=D1.fieldbyname(PareEquipMaccpk).AsInteger;  //���豸����ID
      TempBusinessParaNode3.EquipType3:=D1.fieldbyname(EquipTypecpk).AsString;  //���豸����ID;
    end
    else
    begin
      //ShowMessage(' ��Ӹ��豸 ');
      TempBusinessParaNode3.BusiID3:=0;
      TempBusinessParaNode3.BusiCaption3:='';
      TempBusinessParaNode3.BusiParentID3:=0;
      TempBusinessParaNode3.EquipID3:=0;
      //ShowMessage(' ��Ӹ��ڵ��豸����, ');
      TempBusinessParaNode3.EquipCaption3:=RootEquipName1;
      TempBusinessParaNode3.EquipIP3:='FFFFFFFF';
      TempBusinessParaNode3.EquipParentIP3:=1;
      //ShowMessage(' ���ڵ��̨������, ');
      TempBusinessParaNode3.EquipType3:='0000';
    end;
    result:=TempBusinessParaNode3;
  except
    result:=nil;
    //ShowMessage(' �������ݼ�ʧ�ܣ� ');
  end;
end;


{�¼�����̻��ڵ㣬}
function TfaqhSetBusinessEquipInfo.AddNewBusiNode2(B1:TDataSet):TBusiAndEquipNode1;
var
  TempBusinessParaNode2:TBusiAndEquipNode1;  //��ʱ�ڵ㣬
begin
  TempBusinessParaNode2:=TBusiAndEquipNode1.Create;
  try
    if B1<>nil then
    begin
      //ShowMessage('�Ϻ���ѧ ���̻���ʶ�� '+B1.fieldbyname(BusiIdcpk).AsString);
      TempBusinessParaNode2.BusiID3:=B1.fieldbyname(BusiIdcpk).AsInteger;
      TempBusinessParaNode2.BusiCaption3:=B1.fieldbyname(BusiNamecpk).AsString;
      TempBusinessParaNode2.BusiParentID3:=B1.fieldbyname(PareBusiIdcpk).AsInteger;
      TempBusinessParaNode2.EquipID3:=0;
      TempBusinessParaNode2.EquipCaption3:='';
      TempBusinessParaNode2.EquipIP3:='';
      TempBusinessParaNode2.EquipParentIP3:=1;
      TempBusinessParaNode2.EquipType3:='';
    end
    else
    begin
      ;
    end;
    result:=TempBusinessParaNode2;
  except
    result:=nil;
    //ShowMessage(' �������ݼ�ʧ�ܣ� ');
  end;
end;


{�¼����j�豸�̻��ڵ㣬}
function TfaqhSetBusinessEquipInfo.AddNewB_ENode3(B_E3:TDataSet;ENode3:TTreeNode):TBusiAndEquipNode1;
var
  InitBusiAndEquPara1:TBusiAndEquipNode1;
begin
  InitBusiAndEquPara1:=TBusiAndEquipNode1.Create;
  //֧�ִ����ڵ㣬�����豸�̻���¼�������Ϣ:�̻���ʶ��
  InitBusiAndEquPara1.BusiID3:=B_E3.fieldbyname(BEbusiIdcpk).AsInteger;
  InitBusiAndEquPara1.EquipID3:=TBusiAndEquipNode1(ENode3.Data).EquipID3;
  InitBusiAndEquPara1.EquipCaption3:=TBusiAndEquipNode1(ENode3.Data).EquipCaption3;
  InitBusiAndEquPara1.EquipIP3:=TBusiAndEquipNode1(ENode3.Data).EquipIP3;
  InitBusiAndEquPara1.EquipParentIP3:=TBusiAndEquipNode1(ENode3.Data).EquipParentIP3;
  InitBusiAndEquPara1.EquipType3:=TBusiAndEquipNode1(ENode3.Data).EquipType3;
  InitBusiAndEquPara1.ENum3:=B_E3.fieldbyname(EquipIdcpk).AsInteger;
  InitBusiAndEquPara1.EBegDate3:=B_E3.fieldbyname(BgnDatecpk).AsString;
  InitBusiAndEquPara1.EBegTime3:=B_E3.fieldbyname(BenTimecpk).AsString;
  InitBusiAndEquPara1.EEndDate3:=B_E3.fieldbyname(EndDatecpk).AsString;
  InitBusiAndEquPara1.EEndTime3:=B_E3.fieldbyname(EndTimecpk).AsString;
  InitBusiAndEquPara1.EComment3:=B_E3.fieldbyname(Commentcpk).AsString;
end;


{�ֶ���WorkView��ֵ������WVEdit��}
procedure TfaqhSetBusinessEquipInfo.GiveFieldToWVEdits;
begin
  WVDigitalEdit1.Text:=QeyOneBsEpSet1.fieldbyname(BEnumcpk).AsString;
  WVDigitalEdit2.Text:=QeyOneBsEpSet1.fieldbyname(BEequipIdcpk).AsString;
  WVDigitalEdit3.Text:=IntToStr(QeyOneBsEpSet1.fieldbyname(BEbusiIdcpk).AsInteger);
  WVEdit2.Text:=QeyOneBsEpSet1.fieldbyname(BgnDatecpk).AsString;
  WVEdit3.Text:=QeyOneBsEpSet1.fieldbyname(EndDatecpk).AsString;
  WVEdit6.Text:=QeyOneBsEpSet1.fieldbyname(BenTimecpk).AsString;
  WVEdit7.Text:=QeyOneBsEpSet1.fieldbyname(EndTimecpk).AsString;
  WVEdit1.Text:=QeyOneBsEpSet1.fieldbyname(Commentcpk).AsString;
end;


{�����ܺ�ĳ�ʼ������}
procedure TfaqhSetBusinessEquipInfo.Init;
begin
  inherited;
  //ShowMessage(' ����TabSheet�Ŀɼ��ԣ� ');
  tsQuery.TabVisible:=true;
  tsEdit.TabVisible:=False;
  //ShowMessage(' ��ʼ����ѯ�޼�¼��־�� ');
  NoRecord:=False;
  //ShowMessage(' �޸ı�־�� ');
  NewBusiSel2:=False;
  NewEquipSel1:=False;
  DelEquSel2:=False;
  //ShowMessage(' Ĭ�ϵĸ��豸 ');
  RootEquipName1:='�Ϻ���ѧ��ѧ';
  //ShowMessage(' ���Label ');
  Label16.Caption:='';
  Label17.Caption:='';
  //ShowMessage(' ��ʼ��Cpack�ֶΣ�',);
  BusiIdcpk:='lvol5';  //�̻���ʶ
  BusiNamecpk:='scard1';  //�̻�����
  PareBusiIdcpk:='lvol1';  //���̻���ʶ
  //ShowMessage(' �豸��Cpack�ֶΣ�');
  EquipIdcpk:='lvol1';  //�豸��ʶ
  EquipNamecpk:='scert_no';  //�豸����
  EquipMaccpk:='sdate0';  //�豸����ID
  PareEquipMaccpk:='lvol2';  //���豸����ID  sdate1
  EquipTypecpk:='sname2';  //���ʹ���

  //��ѯ�豸�̻���CPack�ֶ�,���ܺ�847164,
  QBEnumcpk:='lvol5';  //�豸�̻�,���
  QBEbusiIdcpk:='lvol0';  //�豸�̻�,�̻���ʶ
  QBEequipIdcpk:='lvol2';  //�豸�̻�,�豸��ʶ
  QBgnDatecpk:='sdate0';  //ʹ�ÿ�ʼ����
  QEndDatecpk:='sdate1';  //ʹ�ÿ�ʼ����
  QBenTimecpk:='scust_no';  //ʹ�ÿ�ʼʱ��
  QEndTimecpk:='scust_no2';  //ʹ�ý���ʱ��
  //��ɾ��
  BEnumcpk:='lvol1';  //�豸�̻�,���
  BEbusiIdcpk:='damt0';  //�豸�̻�,�̻���ʶ
  BEequipIdcpk:='lvol0';  //�豸�̻�,�豸��ʶ
  BgnDatecpk:='scust_no';  //ʹ�ÿ�ʼ����
  EndDatecpk:='scust_no2';  //ʹ�ÿ�ʼ����
  BenTimecpk:='sholder_ac_no';  //ʹ�ÿ�ʼʱ��
  EndTimecpk:='sholder_ac_no2';  //ʹ�ý���ʱ��
  Commentcpk:='scusttypes';  //��ע
  //��ʼ�����ڷ��ͺͷ������ݵ�WorkView��
  WorkView.FieldByName('��ѯ.���').DefaultValue :=0;
  WorkView.FieldByName('���').DefaultValue := 0;
  WorkView.FieldByName('�豸��ʶ').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.�豸��ʶ').DefaultValue := 0;
  WorkView.FieldByName('�̻���ʶ').DefaultValue :=0;
  WorkView.FieldByName('��ѯ.�̻���ʶ').DefaultValue :=0;
  WorkView.FieldByName('ʹ�ÿ�ʼ����').DefaultValue := '';
  WorkView.FieldByName('ʹ�ÿ�ʼʱ��').DefaultValue := '';
  WorkView.FieldByName('ʹ�ý���ʱ��').DefaultValue := '';
  WorkView.FieldByName('ʹ�ý�������').DefaultValue := '';
  WorkView.FieldByName('��ע').DefaultValue := '';
  WorkView.FieldByName('�շѿ�Ŀ').DefaultValue := 0;
  WorkView.Reset;
  //���³�ʼ����������ѯ �̻���¼��
  WorkView1.FieldByName('�̻���ʶ').DefaultValue := 0;
  WorkView1.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView1.FieldByName('���̻���ʶ').DefaultValue := 0;
  WorkView1.FieldByName('�̻�����').DefaultValue := '';
  WorkView1.FieldByName('�̻����').DefaultValue := 0;
  WorkView1.FieldByName('�Ƿ�ΪҶ�ڵ�').DefaultValue := '';
  WorkView1.FieldByName('�̻�״̬').DefaultValue := 0;
  WorkView1.FieldByName('������Ա����').DefaultValue := '';
  WorkView1.FieldByName('����������').DefaultValue := '';
  WorkView1.FieldByName('�������Ա�').DefaultValue := '';
  WorkView1.FieldByName('����������').DefaultValue := 0;
  WorkView1.FieldByName('���������֤��').DefaultValue := '';
  WorkView1.FieldByName('��ϵ�绰').DefaultValue := '';
  WorkView1.FieldByName('��ϵ��ַ').DefaultValue := '';
  WorkView1.FieldByName('�Ƿ���ȡ�����').DefaultValue := '';
  WorkView1.FieldByName('��ȡ���ѹ���ѱ���').DefaultValue := 0.00;
  //WorkView1.FieldByName('�̻�����Ѽ��㷽ʽ').DefaultValue := 0;
  //WorkView1.FieldByName('�̻�˰�Ѽ��㷽ʽ').DefaultValue := 0;
  WorkView1.FieldByName('ע��ʱ��').DefaultValue := '';
  WorkView1.FieldByName('��ע').DefaultValue := '';
  WorkView1.Reset;
  //���³�ʼ����������ѯ �豸��¼��
  WorkView4.FieldByName('�豸����').DefaultValue := '';
  WorkView4.FieldByName('�����豸ע���').DefaultValue := '';
  WorkView4.FieldByName('�豸����ID').DefaultValue := '';
  WorkView4.FieldByName('����').DefaultValue := 0;
  WorkView4.FieldByName('���ʹ���').DefaultValue := '';
  WorkView4.FieldByName('�ϼ��豸����ID').DefaultValue :='' ;
  WorkView4.FieldByName('�豸״̬').DefaultValue := 0;
  WorkView4.FieldByName('�豸�����ͺ�').DefaultValue := 0;
  WorkView4.FieldByName('������ϵͳ').DefaultValue := 0;
  WorkView4.FieldByName('�豸��������').DefaultValue := 0;
  WorkView4.FieldByName('������Ա����').DefaultValue := '';  
  WorkView4.Reset;    
  SelBusiText2:='';
  //���豸���̻��ڵ㹲�ýṹ����ʾ�̻�����
  ShowBusinessTree2;
  //treevEquAndBusi2.Refresh;
  //���豸���̻��ڵ㹲�ýṹ����ʾ�豸����
  ShowEquipTree3;
  //ShowMessage(' ��ʼ��ʱ�������豸�̻�����豸�ҵ��̻����ϣ� ');
  InitEquipToBusiTree;
end;


{����������豸����ť����ʼ�����豸���̻�������豸�̻���¼}
procedure TfaqhSetBusinessEquipInfo.btnAddEB1Click(Sender: TObject);
var
  tmp_data : TBusiAndEquipNode1;
begin
  //ShowMessage(' �����豸ǰ��׼������ ');
  if treevEquAndBusi2.Selected<>nil then
  begin
    if EquipTreVw1.Selected<>nil then
    begin
      {�ж��豸����}
      tmp_data := TBusiAndEquipNode1(EquipTreVw1.Selected.Data);
      if (tmp_data.EquipType3 = '5301') or
        (EquipTreVw1.Selected.Parent = nil) then
      begin
        ShowMessage('�������豸�����Է��䣡');
        Exit;
      end;
      Bef_AddEqu3(treevEquAndBusi2.Selected,EquipTreVw1.Selected);
    end
    else
    begin
      ShowMessage(' ��ѡ���豸�� ');;
    end;
  end
  else
  begin
    ShowMessage(' ����ѡ���̻� ');;
  end;
  WVEdit2.Text:='20050106';
  WVEdit3.Text:='20100106';
end;


procedure TfaqhSetBusinessEquipInfo.btnBefDelEB2Click(Sender: TObject);
var
  tmp : TTreeNode;
begin
  tmp := treevEquAndBusi2.Selected;
  if tmp <>nil then
  begin
    if tmp.getFirstChild=nil then
    begin
      Bef_DelEqu3(tmp,nil);
    end
    else
    begin
      ShowMessage(' �뽫ɾ�����豸�����������豸��');
      MovedEquipList3(tmp,treevEquAndBusi2);
      //ShowMessage(' ɾ�����豸�����������豸�ڵ㣡');
      tmp.Delete;
    end;
  end
  else
  begin
    ShowMessage(' ���ȴ��豸�̻�����ѡ���豸��');
  end;
end;

procedure TfaqhSetBusinessEquipInfo.btnBefChaEB2Click(Sender: TObject);
var
  SelEquipText4:String;
  EquipDataSet4:TDataSet;
  ChaEquipID4:Integer;
  ParentBusiID4:Integer;
  TempBusinessParaNode5:TBusiAndEquipNode1;
begin
  if treevEquAndBusi2.Selected.Parent=nil then
  begin
    showmessage('���̻�û���豸�ɹ��޸ģ�');
    exit;
  end;
  if (treevEquAndBusi2.Selected<>nil) then
  begin
    //ShowMessage('��ѯһ���豸�̻���¼�����ݱ�ţ�');
    QueryOneRec1(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).ENum3);
    //ShowMessage(' �����༭�豸�̻���Ϣ�Ľ��棬 ');
    GiveFieldToWVEdits;
    //ShowMessage(' ����豸���ơ��̻����� ');
    Edit1.Text:=TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).EquipCaption3;
    Edit2.Text:=TBusiAndEquipNode1(treevEquAndBusi2.Selected.Parent.Data).BusiCaption3;
    //ShowMessage(' ��һ���޸ı�ǣ� ');
    tsQuery.TabVisible:=false;
    tsEdit.TabVisible:=true;
    tsEdit.Show;
    btnOK.visible:=False;
    btnCancel.visible:=False;
    Edit1.ReadOnly:=true;
    //ShowMessage(' ���������޸ı�ǣ� ');
    ChaMark2:=True;
  end
  else
  begin
    ShowMessage('�������ѡ���豸');
  end;
end;


procedure TfaqhSetBusinessEquipInfo.treevEquAndBusi2MouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  temp : TTreeNode;
  temp_data : TBusiAndEquipNode1;
begin
  temp := treevEquAndBusi2.Selected;
  if temp <>nil then
  begin
    temp_data := TBusiAndEquipNode1(temp.Data);
    if temp_data.EquipCaption3='' then
    begin
      Label16.Caption:=temp.Text;
      Label16.font.color:=clWindowText;
      NewBusiSel2:=True;
      {
      if temp_data.EquipCaption3='' then
      begin
        temp.SelectedIndex:=3;
      end;
      if temp_data.EquipIP3='' then
      begin
        temp.SelectedIndex:=3;
      end;
      if temp_data.EquipParentIP3='' then
      begin
        temp.SelectedIndex:=3;
      end;
      }
    end
    else if temp_data.EquipCaption3<>'' then
    begin
      DelEquSel2:=True;
      ChaEquSel2:=True;
      Label16.Caption:='����δѡ���̻���';
      Label16.font.color:=clRed;
    end;
  end
  else
  begin
    ;//ShowMessage(' û��ѡ�еĽڵ㣬 ');
  end;
end;

procedure TfaqhSetBusinessEquipInfo.EquipTreVw1MouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  inherited;
  Label17.Caption:=EquipTreVw1.Selected.Text;
  Label18.Visible:=True;
  NewEquipSel1:=True;
end;


procedure TfaqhSetBusinessEquipInfo.treevEquAndBusi2MouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  DelEquSel2:=False;
end;

procedure TfaqhSetBusinessEquipInfo.ChaDateTime1Click(Sender: TObject);
var
  BusiAndEquipSet2:TDataSet;
begin
  //ShowMessage(' ���޸�һ���豸�ڵ�ǰ�Ĺ����� ');
  btnBefChaEB2Click(nil);
  //ShowMessage(' �ڲ˵��ﴦ�����ڡ�ʱ�䣬 ');

end;


procedure TfaqhSetBusinessEquipInfo.DelEquAndBus1Click(Sender: TObject);
begin

  btnBefDelEB2Click(nil);

end;

procedure TfaqhSetBusinessEquipInfo.btnReTree1Click(Sender: TObject);
begin
  //ShowMessage(' ˢ����ʾ�豸���� ');
  try
    try
      btnReTree1.Enabled := False;
      // ɾ��ԭ���Ľڵ��ڴ�����
      FreeTreeNodeData(EquipTreVw1.Items);
      FreeTreeNodeData(treevEquAndBusi2.Items);
      // ������
      ShowBusinessTree2;
      ShowEquipTree3;
      InitEquipToBusiTree;
    except
      // FIXME : �������ڴ�й©�Ĵ����д����
    end;
  finally
    btnReTree1.Enabled := True;
  end;
end;

procedure TfaqhSetBusinessEquipInfo.btnAdDlChCcl3Click(Sender: TObject);
begin
  //ShowMessage(' �޸�TabSheet�Ŀɼ��ԣ� ');
  tsQuery.TabVisible:=true;
  tsEdit.TabVisible:=false;
  tsQuery.show;
end;


procedure TfaqhSetBusinessEquipInfo.KSFrameEnter(Sender: TObject);
begin
  Label16.Caption:='';
  Label17.Caption:='';
end;

procedure TfaqhSetBusinessEquipInfo.pcPagesChanging(Sender: TObject;
  NewIndex: Integer; var AllowChange: Boolean);
begin
  //ShowMessage(' �ȼ̳п�ܵķ����� ');
  //inherited;
  //ShowMessage(' ���������ñ�ǣ� ');
  If (AddMark2=true) or (DelMark2=true) or (ChaMark2=true) then
  begin
    AllowChange:=true;
  end
  else
  begin
    ;
  end;
end;

procedure TfaqhSetBusinessEquipInfo.tsQueryEnter(Sender: TObject);
begin
  //inherited;
  ////ShowMessage(' ����������ɾ�ĵı�ǣ� ');
  AddMark2:=false;
  DelMark2:=false;
  ChaMark2:=false;
end;

procedure TfaqhSetBusinessEquipInfo.BuildBusiTreeFromDataSet(ds: TDataSet;
  nodes: TTreeNodes);
function FindNodeParent(parent_id : Integer;
    parent_node: TTreeNode) : TTreeNode;
  var
    curr : TTreeNode;
    curr_data : TBusiAndEquipNode1;
  begin
    Result := nil;
    if parent_node = nil then Exit;
    //showmessage(parent_node.text);
    curr := parent_node;
    while curr <> nil do
    begin
      Application.ProcessMessages;
      curr_data := TBusiAndEquipNode1(curr.Data);
      //showmessage(Format('%d : %d',[curr_data.BusiID3,parent_id]));
      if curr_data.BusiID3 = parent_id then
      begin
        Result := curr;
        Exit;
      end
      else
      begin
        Result := FindNodeParent(parent_id,curr.getFirstChild);
        if( Result <> nil ) then
        begin
          Exit;
        end;
        curr := curr.getNextSibling;
      end;
    end;
  end;
  procedure RecursiveBuild;
  var
    parent_id , curr_id :Integer;
    curr_caption: string;
    parent_node_data , node_data : TBusiAndEquipNode1;
    curr_node ,parent_node: TTreeNode;
  begin
    parent_node := nil;
    curr_node := nil;
    ds.first;
    // �ڵ�����
    while not ds.Eof do
    begin
      // ������Ϣ
      Application.ProcessMessages;
      curr_id := ds.FieldByName(BusiIdcpk).AsInteger;
      parent_id := ds.FieldByName(PareBusiIdcpk).AsInteger;
      curr_caption := ds.FieldByName(BusiNamecpk).AsString;
      // �жϽڵ�
      if parent_node <> nil then
      begin
        parent_node_data := TBusiAndEquipNode1(parent_node.Data);
        if (parent_node_data <> nil)
          and (parent_node_data.BusiID3 = parent_id) then
          parent_node := curr_node.Parent
        else
          parent_node := nil;
      end;
      if parent_node = nil then
        parent_node := FindNodeParent(parent_id,nodes.GetFirstNode);
      node_data := AddNewBusiNode2(ds);
      curr_node := nodes.AddChildObject(parent_node,curr_caption,node_data);
      curr_node.ImageIndex := 1;
      curr_node.SelectedIndex := 1;
      ds.Next;
    end;
  end;
begin
  // ͨ�� DataSet ������ Tree
  if ds = nil then
  begin
    raise Exception.Create('DataSet Ϊ��');
    exit;
  end;
  try
    RecursiveBuild;
  except
  end;

end;

procedure TfaqhSetBusinessEquipInfo.BuildEquiTreeFromDataSet(ds: TDataSet;
  nodes: TTreeNodes);
  function FindNodeParent(parent_id : Integer;
    parent_node: TTreeNode) : TTreeNode;
  var
    curr : TTreeNode;
    curr_data : TBusiAndEquipNode1;
  begin
    Result := nil;
    if parent_node = nil then Exit;
    //showmessage(parent_node.text);
    curr := parent_node;
    while curr <> nil do
    begin
      Application.ProcessMessages;
      curr_data := TBusiAndEquipNode1(curr.Data);
      if (curr_data.EquipID3=parent_id) then
      begin
        Result := curr;
        Exit;
      end
      else
      begin
        Result := FindNodeParent(parent_id,curr.getFirstChild);
        if( Result <> nil ) then
        begin
          Exit;
        end;
        curr := curr.getNextSibling;
      end;
    end;
  end;
  procedure RecursiveBuild;
  var
    curr_id :string;
    parent_id:Integer;
    curr_caption: string;
    parent_node_data , node_data : TBusiAndEquipNode1;
    curr_node ,parent_node: TTreeNode;
  begin
    parent_node := nil;
    curr_node := nil;
    ds.first;
    // �ڵ�����
    while not ds.Eof do
    begin
      // ������Ϣ
      Application.ProcessMessages;
      curr_id := ds.FieldByName(EquipMaccpk).AsString;
      parent_id := ds.FieldByName(PareEquipMaccpk).AsInteger;
      curr_caption := ds.FieldByName(EquipNamecpk).AsString;
      //showmessage(curr_id + ':' + parent_id);
      // �жϽڵ�
      if parent_node <> nil then
      begin
        parent_node_data := TBusiAndEquipNode1(parent_node.Data);
        if (parent_node_data <> nil)
          and (parent_node_data.EquipID3=parent_id) then
          parent_node := curr_node.Parent
        else
          parent_node := nil;
      end;
      if parent_node = nil then
        parent_node := FindNodeParent(parent_id,nodes.GetFirstNode);
      node_data := AddNewBusiEquiNode1(ds);
      curr_node := nodes.AddChildObject(parent_node,curr_caption,node_data);
      curr_node.ImageIndex := 0;
      curr_node.SelectedIndex := 0;
      ds.Next;
    end;
  end;
begin
  // ͨ�� DataSet ������ Tree
  if ds = nil then
  begin
    raise Exception.Create('DataSet Ϊ��');
    exit;
  end;
  try
    RecursiveBuild;
  except
  end;

end;

procedure TfaqhSetBusinessEquipInfo.FreeTreeNodeData(nodes: TTreeNodes);
  procedure RecursiveFree(node : TTreeNode);
  var
    curr : TTreeNode;
    node_data : TBusiAndEquipNode1;
  begin
    curr := node;
    while curr <> nil do
    begin

      if curr.Data <>  nil then
      begin
        // �ͷ��ڴ�
        node_data := TBusiAndEquipNode1(curr.Data);
        curr.Data := nil;
        node_data.Free;
      end;
      // ɾ���ӽڵ�
      RecursiveFree(node.getFirstChild);
      // ��һ���ֵ�
      curr := curr.getNextSibling;
    end;
  end;
begin
  RecursiveFree(nodes.GetFirstNode);
end;

destructor TfaqhSetBusinessEquipInfo.Destroy;
begin
  inherited;
  // �ڹر�ʱ�����ͷ����ṹ�Ľڵ������ڴ棡��
  FreeTreeNodeData(treevEquAndBusi2.Items);
  FreeTreeNodeData(EquipTreVw1.Items);
end;

procedure TfaqhSetBusinessEquipInfo.BuildBusiEquiTreeFromDataSet(
  ds: TDataSet; nodes: TTreeNodes);
  function FindNodeParent(parent_id : Integer;
    parent_node: TTreeNode) : TTreeNode;
  var
    curr : TTreeNode;
    curr_data : TBusiAndEquipNode1;
  begin
    Result := nil;
    curr := parent_node;
    while curr <> nil do
    begin
      Application.ProcessMessages;
      curr_data := TBusiAndEquipNode1(curr.Data);
      if (curr_data <> nil)
        and (curr_data.BusiID3 = parent_id)  // Ϊ�����
        and ((curr_data.EquipCaption3 = '')
          or (curr_data.BusiCaption3 = ''))  // �����豸�̻����
        then
      begin
        Result := curr;
        Exit;
      end
      else
      begin
        Result := FindNodeParent(parent_id,curr.getFirstChild);
        if( Result <> nil ) then
        begin
          Exit;
        end;
        curr := curr.getNextSibling;
      end;
    end;
  end;
  procedure RecursiveBuild;
  var
    parent_id , curr_id :integer;
    curr_caption: string;
    parent_node_data , node_data : TBusiAndEquipNode1;
    curr_node ,parent_node: TTreeNode;
    i , rec_count: Integer;
  begin
    parent_node := nil;
    curr_node := nil;
    ds.first;
    i := 0;
    rec_count := 0;
    // ȡ�ü�¼��
    ds.Last;
    rec_count := ds.RecNo;
    // �ڵ�����
    ds.First;
    SetLength(used_equi_ary,rec_count);
    while not ds.eof do
    begin
      // ������Ϣ
      Application.ProcessMessages;
      curr_id := ds.FieldByName(BEnumcpk).AsInteger;
      parent_id := ds.FieldByName(BEbusiIdcpk).AsInteger;
      // �жϽڵ�
      if parent_node <> nil then
      begin
        parent_node_data := TBusiAndEquipNode1(parent_node.Data);
        if (parent_node_data <> nil)
          and (parent_node_data.BusiID3 = parent_id) then
          parent_node := curr_node.Parent
        else
          parent_node := nil;
      end;
      if parent_node = nil then
        parent_node := FindNodeParent(parent_id,nodes.GetFirstNode);
      // ��Ȼû���ҵ��̻��ڵ㣡�����϶����������ݣ����˵���
      if parent_node = nil then
      begin
        ds.Next;
        Continue;
      end;
      node_data := CreateNewBusiEquiNodeData(ds,parent_node);
      if node_data <> nil then
      begin
        curr_caption := Format('%s(%s --> %s)',
          [node_data.EquipCaption3
          ,SpliteDateStr(node_data.EBegDate3)
          ,SpliteDateStr(node_data.EEndDate3)]);
        curr_node := nodes.AddChildObject(parent_node,curr_caption,node_data);
        curr_node.ImageIndex := 0;
        curr_node.SelectedIndex := 0;
        used_equi_ary[i] := node_data.EquipID3;
      end;
      ds.Next;
      Inc(i);
    end;
  end;
begin
  // ͨ�� DataSet ������ Tree
  if ds = nil then
  begin
    raise Exception.Create('DataSet Ϊ��');
    exit;
  end;
  try
    RecursiveBuild;
  except
  end;
end;

function TfaqhSetBusinessEquipInfo.CreateNewBusiEquiNodeData(
  ds: TDataSet; insert_node: TTreeNode):TBusiAndEquipNode1;
var
  temp : TBusiAndEquipNode1;
begin
  if (ds = nil)  then
  begin
    raise Exception.Create('DataSet Ϊ�գ�');
    exit;
  end;

  Result := nil;
  temp := TBusiAndEquipNode1.Create;
  try
    //WriteLog('1',lcKSClientStart);
    temp.BusiID3:=ds.fieldbyname(BEbusiIdcpk).AsInteger;
    //WriteLog('2',lcKSClientStart);
    temp.EquipID3:=ds.fieldbyname('lvol0').AsInteger;
    //WriteLog('3',lcKSClientStart);
    temp.EquipCaption3:=ds.fieldbyname('sbankname2').AsString;
    //WriteLog('4',lcKSClientStart);
    //temp.EquipIP3:=TBusiAndEquipNode1(insert_node.Data).EquipIP3;
    //temp.EquipParentIP3:=TBusiAndEquipNode1(insert_node.Data).EquipParentIP3;
    //temp.EquipType3:=TBusiAndEquipNode1(insert_node.Data).EquipType3;
    temp.ENum3:=ds.fieldbyname(EquipIdcpk).AsInteger;
    //WriteLog('5',lcKSClientStart);
    temp.EBegDate3:=ds.fieldbyname(BgnDatecpk).AsString;
    //WriteLog('6',lcKSClientStart);
    temp.EBegTime3:=ds.fieldbyname(BenTimecpk).AsString;
    //WriteLog('7',lcKSClientStart);
    temp.EEndDate3:=ds.fieldbyname(EndDatecpk).AsString;
    //WriteLog('8',lcKSClientStart);
    temp.EEndTime3:=ds.fieldbyname(EndTimecpk).AsString;
    //WriteLog('8',lcKSClientStart);
    temp.EComment3:=ds.fieldbyname(Commentcpk).AsString;
    //WriteLog('9',lcKSClientStart);
    Result := temp;
  except
    on ex : Exception do
    begin
      //ShowMessage('create node error : ' + ex.Message);
      temp.Free;
    end;
  end;
end;

function TfaqhSetBusinessEquipInfo.SpliteDateStr(str: string): string;
begin
  Result := '';
  if length(str) <> 8 then
    Exit;
  Result := Format('%s-%s-%s',
    [Copy(str,1,4),Copy(str,5,2),Copy(str,7,2)]);
end;

procedure TfaqhSetBusinessEquipInfo.UpdateAssignedEquiIcon;
  function IsEquiAssigned(data : TBusiAndEquipNode1):boolean;
  var
    i : integer;
  begin
    Result := False;
    for i := low(used_equi_ary) to high(used_equi_ary) do
    begin
      if data.EquipID3 = used_equi_ary[i] then
      begin
        Result := True;
        exit;
      end;
    end;
  end;
  procedure RecursiveUpdate(node:TTreeNode);
  var
    curr : TTreeNode;
    node_data : TBusiAndEquipNode1;
  begin
    curr := node;
    while curr <> nil do
    begin
      node_data := TBusiAndEquipNode1(curr.Data);
      if(node_data <> nil) and
        IsEquiAssigned(node_data) then
      begin
        curr.ImageIndex := 2;
        curr.SelectedIndex := 2;
      end;
      // �ȸ����ӽ��
      RecursiveUpdate(curr.getFirstChild);
      curr := curr.getNextSibling;
    end;
  end;

begin
  //
  try
    try
    EquipTreVw1.Items.BeginUpdate;
    RecursiveUpdate(EquipTreVw1.Items.GetFirstNode);
    except
      //ShowMessage('error3');
    end;
  finally
    EquipTreVw1.Items.EndUpdate;
  end;
end;

function TfaqhSetBusinessEquipInfo.CheckInputDateFormat(
  input: string): boolean;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('ʱ�䲻��Ϊ�գ������룡');
    Result := False;
    Exit;
  end;
  if length(input) = 8 then
  begin
    try
      StrToDateTime(SpliteDateStr(input));
      Result := True;
    except
      ;
      // ������ȷ�����ڸ�ʽ
    end;
  end;
  if not Result then
     ShowMessage(Format('�����������[%s]��ʽ����ȷ!'#13
      + '���Ҫ����2005��6��18��,������20050618',[input]));
end;

function TfaqhSetBusinessEquipInfo.CheckInputTimeFormat(
  input: string): boolean;
  function SpliteTimeStr(input: string) : string;
  begin
    Result := '';
    if length(input) <> 6 then
      Exit;
    Result := Format('%s:%s:%s',
      [Copy(input,1,2),Copy(input,3,2),Copy(input,5,2)]);
  end;
begin
  Result := False;
  if trim(input) = '' then
  begin
    Showmessage('���ڲ���Ϊ�գ������룡');
    Result := False;
    exit;
  end;
  Result := True;
end;

procedure TfaqhSetBusinessEquipInfo.btnAdDlChOK3Click(Sender: TObject);
var
  EquipDataSet2:TDataSet;
  DelEquipID2:Integer;
  ParentBusiID5:Integer;
begin
  if not CheckInputDateFormat(WVEdit2.Text) then
    Exit;
  if not CheckInputDateFormat(WVEdit3.Text) then
    Exit;
  if not CheckInputTimeFormat(WVEdit6.Text) then
    Exit;
  if not CheckInputTimeFormat(WVEdit7.Text) then
    Exit;
  if (AddMark2=True) and (DelMark2=False) and (ChaMark2=False) then
  begin
    AddEquipToBusiTree2(treevEquAndBusi2.Selected,EquipTreVw1.Selected);
    tsQuery.TabVisible:=true;
    tsEdit.TabVisible:=false;
    tsQuery.Show;
    AddMark2:=False;
  end
  else if (AddMark2=False) and (DelMark2=True) and (ChaMark2=False) then
  begin
    ShowMessage(' ɾ��һ���豸�̻���¼!');
    DelOneRecord1(StrToInt(WVDigitalEdit1.text));
    //ShowMessage(' ɾ��һ���豸 ');
    DelOneEquip3(treevEquAndBusi2.Selected,nil);
    //ShowMessage(' ������ѯ���棬 ');
    //ShowMessage(' �޸�TabSheet�Ŀɼ��ԣ� ');
    tsQuery.TabVisible:=true;
    tsEdit.TabVisible:=false;
    tsQuery.Show;
    //ShowMessage(' �޸�����ɾ���ı�ǣ� ');
    DelMark2:=False;
  end
  else if (AddMark2=False) and (DelMark2=False) and (ChaMark2=True) then
  begin
    //ShowMessage(' ��ʼ�޸ģ� ');
    if CheckDateTime2(StrToInt(WVDigitalEdit3.Text),StrToInt(WVDigitalEdit2.Text),WVEdit2.Text,WVEdit6.Text,WVEdit3.Text,WVEdit7.Text)=True then
    begin
      ShowMessage('ʹ��ʱ���ͻ�������޸ģ� ');
      exit;
    end
    else
    begin
      //ShowMessage(' �޸�һ���豸�̻���¼�ı�ţ� '+IntToStr(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).Enum3));
      ChaOneRecord1(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).Enum3);
      //ShowMessage(' �޸�һ���豸 ');
      ChaOneEquip1(nil,nil);
      //ShowMessage(' ������ѯ���棬 ');
      //ShowMessage(' �޸�TabSheet�Ŀɼ��ԣ� ');
      tsQuery.TabVisible:=true;
      tsEdit.TabVisible:=false;
      tsQuery.Show;
      //ShowMessage(' �޸������޸ĵı�ǣ� ');
      ChaMark2:=False;
    end;
  end
  else
  begin
    ShowMessage(' ��������ɾ���豸 ');
  end;
end;

initialization
  TUIStdClassFactory.Create('�豸�̻���ϵ����',TfaqhSetBusinessEquipInfo);

end.
