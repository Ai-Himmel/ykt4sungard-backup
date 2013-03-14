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
    BusiID3: Integer;  //商户标识ID
    BusiCaption3: String;  //商户名称
    BusiParentID3: Integer;  //父商户标识ID
    EquipID3: Integer;   //设备标识
    EquipCaption3: String;  //设备名称
    EquipIP3: String;  //设备物理ID
    EquipParentIP3: Integer;  //父设备物理ID
    EquipType3:String;  //机型代码
    ENum3:Integer;  //编号
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
    {增加商户信息}
    procedure btnAddClick(Sender: TObject);
    {修改商户信息}
    procedure btnChangeClick(Sender: TObject);
    {查询商户信息}
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
    SelBusiText2:String;  //用于记录选中商户节点的显示文本，
    AddMark2:Boolean;  //允许修改，
    DelMark2:Boolean;  //判断是否从商户树上删除设备，
    SelEquipText2:String;  //记录从设备商户树上删除的节点，
    ChaMark2:Boolean;  //判断是否从商户树上修改设备，
    NewBusiSel2:Boolean;
    NewEquipSel1:Boolean;
    DelEquSel2:Boolean;
    ChaEquSel2:Boolean;
    CurrentNode2:TTreeNode;
    AddEquList1:array of TBusiAndEquipNode1;
    InsDate2:String;  //计算开始日期，
    InsDate3:String;  //计算结束日期，
    InsTime2:String;  //计算时间，
    QeyOneBsEpSet1:TDataSet;  //一条设备商户记录，
    RootEquipName1:String;  //默认的根节点设备，
    {后台传过来的CPack字段，}
    {商户表}
    BusiIdcpk:String;  //商户标识
    BusiNamecpk:String;  //商户名称
    PareBusiIdcpk:String;  //父商户标识
    {设备表}
    EquipIdcpk:String;  //设备标识
    EquipNamecpk:String;  //设备名称
    EquipMaccpk:String;  //设备物理ID
    PareEquipMaccpk:String;  //父设备物理ID
    EquipTypecpk:String;  //机型代码
    {查询设备商户的CPack字段}
    QBEnumcpk:String;  //设备商户,编号
    QBEbusiIdcpk:String;  //设备商户,商户标识
    QBEequipIdcpk:String;  //设备商户,设备标识
    QBgnDatecpk:String;  //使用开始日期
    QEndDatecpk:String;  //使用开始日期
    QBenTimecpk:String;  //使用开始时间
    QEndTimecpk:String;  //使用结束时间
    {增删改}
    BEnumcpk:String;  //设备商户,编号
    BEbusiIdcpk:String;  //设备商户,商户标识
    BEequipIdcpk:String;  //设备商户,设备标识
    BgnDatecpk:String;  //使用开始日期
    EndDatecpk:String;  //使用开始日期
    BenTimecpk:String;  //使用开始时间
    EndTimecpk:String;  //使用结束时间
    Commentcpk:String;  //备注
    NoRecord:boolean;  //是否返回无记录，
    {按新的数据结构显示商户树结构}
    procedure ShowBusinessTree2;
    {按新的数据结构显示设备树结构}
    procedure ShowEquipTree3;
    {按TreeView 的显示名称查找某个节点}
    function FindCurrentNode4(P_id:String;PTree:TTreeView):TTreeNode;
    {依据设备标识，查找某个子节点}
    function FindChildNode2(P_id:integer;PNode:TTreeNode;PTree:TTreeView):TTreeNode;
    {查找依据商户标识某个节点}
    function FindCurrentBusinessNode3(P_id:integer;PTree:TTreeView):TTreeNode;
    {查找依据设备标识某个节点}
    function FindCurrentBusinessNode5(P_id:integer;PTree:TTreeView):TTreeNode;
    {查找设备物理ID某个节点}
    function FindCurrentBusinessNode4(P_id:String;PTree:TTreeView):TTreeNode;
    {只分配叶子设备，给商户树 增加分配设备}
    procedure AddEquipToBusiTree2(B_node2:TTreeNode;E_node1:TTreeNode);
    {给商户树 增加一个设备}
    procedure AddOneEquip(B_node2:TTreeNode;E_node1:TTreeNode);
    {仅仅给给商户树 删除一个设备}
    procedure DelOneEquip3(B_node2:TTreeNode;E_node1:TTreeNode);
    {给商户树 增加一个设备之前的准备工作，}
    procedure Bef_AddEqu3(B_node2:TTreeNode;E_node1:TTreeNode);
    {给商户树 删除一个设备之前的准备工作，}
    procedure Bef_DelEqu3(B_node2:TTreeNode;E_node1:TTreeNode);
    {给商户树 修改一个设备}
    procedure ChaOneEquip1(B_node2:TTreeNode;E_node1:TTreeNode);
    {初始化设备商户树，初次分配设备}
    procedure InitEquipToBusiTree;
    {节点链，被移除的设备链,根据设备标识，}
    procedure MovedEquipList3(P_Node:TTreeNode;P_Tree:TTreeView);
    {释放设备节点链}
    procedure FreeEquipParaTreeNode;
    {增加一条设备商户记录}
    procedure AddOneRecord(B_node2:TTreeNode;E_node1:TTreeNode);
    {删除一条设备商户记录，依据编号，}
    procedure DelOneRecord1(EaB_ID1:integer);
    {修改一条设备商户记录，依据编号，}
    procedure ChaOneRecord1(EaB_ID1:integer);
    {查询一条设备商户记录，依据编号，}
    procedure QueryOneRec1(EaB_ID1:integer);
    {转换当前的日期、时间格式}
    procedure DateTimeConv1;
    {在确认 按钮里，增删改一个设备，}
    procedure ADC_EB1;
    {按新需求，检查每一天的时间段是否冲突了}
    function CheckDateTime2(B_ID:integer;E_ID:integer;B_D:String;B_T:String;E_D:String;E_T:String):Boolean;
    {新加入的设备节点，}
    function AddNewBusiEquiNode1(D1:TDataSet):TBusiAndEquipNode1;
    {新加入的商户节点，}
    function AddNewBusiNode2(B1:TDataSet):TBusiAndEquipNode1;
    {新加入的j设备商户节点，}
    function AddNewB_ENode3(B_E3:TDataSet;ENode3:TTreeNode):TBusiAndEquipNode1;
    {手动把WorkView的值，赋与WVEdit，}
    procedure GiveFieldToWVEdits;
    {生成商务树形}
    procedure BuildBusiTreeFromDataSet(ds: TDataSet;nodes : TTreeNodes);
    {生成设备信息树形}
    procedure BuildEquiTreeFromDataSet(ds: TDataSet;nodes : TTreeNodes);
    {}
    procedure BuildBusiEquiTreeFromDataSet(ds:TDataSet;nodes : TTreeNodes);
    function CreateNewBusiEquiNodeData(ds : TDataSet;
      insert_node: TTreeNode):TBusiAndEquipNode1;
    {将 yyyymmdd 格式的日期分割成 yyyy-mm-dd 格式}
    function SpliteDateStr(str: string):string;
    {释放树结点的Data}
    procedure FreeTreeNodeData(nodes : TTreeNodes);
    {更新已分配的设备图标}
    procedure UpdateAssignedEquiIcon;
    {检查用户输入的日期是否正确}
    function CheckInputDateFormat(input:string):boolean;
    {检查用户输入的时间是否正确}
    function CheckInputTimeFormat(input:string):boolean;
    { Private declarations }
  public
    {进入框架后的初始化工作}
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
  ParentBusiNode2:TTreeNode;  //用于插入商户的父节点，
  OwnBusiNode2:TTreeNode;  //用于查本商户节点，
  RootBusinessParaTreeNode2:TBusiAndEquipNode1;
  NodeText1:String;  //节点的显示文本，
  tmpNode:TTreeNode;
begin
  // BusiTreeDataSet:=TDataSet.Create(nil);
  Try
    WorkView2.FieldByName('商户标识').Data.SetInteger(0);
    QueryRequest2.SendCommand;
    BusiTreeDataSet:=TDataSet(WorkView2.FieldByName('查询结果集').Data.AsObject);
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

{按新的数据结构显示设备树结构}
procedure TfaqhSetBusinessEquipInfo.ShowEquipTree3;
var
  EquipTreeDataSet3 : TDataSet;
begin
  EquipTreeDataSet3:=TDataSet.Create(nil);
  Try
    WorkView3.FieldByName('设备标识').Data.SetInteger(0);
    QueryRequest3.SendCommand;
    EquipTreeDataSet3:=(WorkView3.FieldByName('查询结果集').Data.AsObject) as TDataSet;

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

{修改商户信息}
procedure TfaqhSetBusinessEquipInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WVDigitalEdit1.Enabled:=false;
  Edit1.ReadOnly:=true;
end;

{查询商户信息}
procedure TfaqhSetBusinessEquipInfo.btnQueryClick(Sender: TObject);
begin
  //检查日期，
  if WVEdit5.Text>WVEdit8.Text then
  begin
    ShowMessage('您输入的“使用开始日期”大于“使用结束日期”，请重新输入');
    WVEdit8.Text:='';
  end
  else
  begin
    inherited;
  end;
end;

{按TreeView 的显示名称查找某个节点}
function TfaqhSetBusinessEquipInfo.FindCurrentNode4(P_id:String;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  if PTree.Items.Count=0 then
  begin
    //ShowMessage(' 是空树！ ');
    exit;
  end
  else
  begin
    p_node:=PTree.Items.item[0];
    for i:=0 to PTree.Items.Count-1 do
    begin
      if (PTree.Items.item[i]<>nil) and (PTree.Items.item[i].Text=P_id) then      //用 TreeView ，
      begin
        Result:=PTree.Items.item[i];
        exit;
      end
      else
      begin
        //p_node:=p_node.GetNext;
        //ShowMessage(' 不是您要找的节点 ');
      end;
    end;
  end;
end;


{依据设备标识，查找某个子节点}
function TfaqhSetBusinessEquipInfo.FindChildNode2(P_id:integer;PNode:TTreeNode;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  ShowMessage('a2321 开始在设备商户树上搜索该商户 '+PNode.Text);
  PNode:=FindCurrentNode4(PNode.Text,PTree);
  ShowMessage('a2322已找到该商户是 '+PNode.Text);
  if PNode.Count=0 then
  begin
    exit;
  end
  else
  begin
    p_node:=PNode.item[0];
    ShowMessage('a2323 该节点含有的子节点数是 '+IntToStr(PNode.Count));
    for i:=0 to PNode.Count-1 do
    begin
      ShowMessage('a2324 要搜索的设备标识是 '+IntToStr(P_id));
      ShowMessage('a2325 设备商户树上本设备 '+PNode.item[i].Text+' 的设备标识是 '+IntToStr(TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3));
      if (PNode.item[i]<>nil) and (TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3=P_id) then      //用 TreeView ，
      begin
        Result:=PNode.item[i];
        ShowMessage('a2326 找到的设备是 '+PNode.item[i].Text);
        exit;
      end
      else
      begin
        ;
      end;
    end;
  end;
end;


{查找商户标识某个节点}
function TfaqhSetBusinessEquipInfo.FindCurrentBusinessNode3(P_id:integer;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  if PTree.Items.Count=0 then
  begin
    //ShowMessage('被搜索的树没有节点，');
    exit;
  end
  else
  begin
    p_node:=PTree.Items[0];
    for i:=0 to PTree.Items.Count-1 do
    begin
      //ShowMessage('被搜索的商户名称是，'+PTree.Items[i].Text);
      if  PTree.Items[i].Data<>nil then
      begin
        //ShowMessage('比较前被搜索的商户标识是，'+IntToStr(TBusiAndEquipNode1(PTree.Items[i].Data).BusiID3));
        //ShowMessage('比较前 要搜索的父商户标识是，'+IntToStr(P_id));
        if (PTree.Items[i]<>nil) and (TBusiAndEquipNode1(PTree.Items[i].Data).BusiID3=P_id) then
        begin
          Result:=PTree.Items[i];
          exit;
        end
        else
        begin
          ;//ShowMessage('被搜索的树没有匹配的节点，');
        end;
      end
      else
      begin
        ;//ShowMessage('被搜索的节点 属性为空，');
      end;
    end;
  end;
end;


{查找依据设备标识某个节点}
function TfaqhSetBusinessEquipInfo.FindCurrentBusinessNode5(P_id:integer;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  if PTree.Items.Count=0 then
  begin
    //ShowMessage('被搜索的树没有节点，');
    exit;
  end
  else
  begin
    p_node:=PTree.Items[0];
    for i:=0 to PTree.Items.Count-1 do
    begin
      //ShowMessage('被搜索的商户名称是，'+PTree.Items[i].Text);
      if  PTree.Items[i].Data<>nil then
      begin
        //ShowMessage('比较前被搜索的设备标识是，'+IntToStr(TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3));
        //ShowMessage('比较前 要搜索的父商户标识是，'+IntToStr(P_id));
        //if (PTree.Items[i]<>nil) and (TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3=P_id) then
        if (TBusiAndEquipNode1(PTree.Items[i].Data).EquipID3=P_id) then
        begin
          Result:=PTree.Items[i];
          exit;
        end
        else
        begin
          //ShowMessage('被搜索的树没有匹配的节点，');
        end;
      end
      else
      begin
        //ShowMessage('被搜索的节点 属性为空，');
      end;
    end;
  end;
end;

{查找设备物理ID某个节点}
function TfaqhSetBusinessEquipInfo.FindCurrentBusinessNode4(P_id:String;PTree:TTreeView):TTreeNode;
var
  i:integer;
  p_node:TTreeNode;
begin
  result:=nil;
  if PTree.Items.Count=0 then
  begin
    //ShowMessage('被搜索的树没有节点，');
    exit;
  end;
  p_node:=PTree.Items[0];
  for i:=0 to PTree.Items.Count-1 do
  begin
    //if (p_node<>nil) and (TBusinessParaTreeNode(p_node.Data).CNodeID=P_id) then
    //测试用：
    //ShowMessage('被搜索的商户名称是，'+PTree.Items[i].Text);
   if  PTree.Items[i].Data<>nil then
   begin
      //测试用：
      //ShowMessage('比较前被搜索的商户标识是，'+IntToStr(TBusiAndEquipNode1(PTree.Items[i].Data).BusiID3));
      //ShowMessage('比较前 要搜索的父商户标识是，'+IntToStr(P_id));
      if (PTree.Items[i]<>nil) and (TBusiAndEquipNode1(PTree.Items[i].Data).EquipIP3=P_id) then
      begin
        Result:=PTree.Items[i];
        exit;
      end;
      //else
        //ShowMessage('被搜索的树没有匹配的节点，');
   end;
   //else
     //ShowMessage('被搜索的节点 属性为空，');
    //else p_node:=p_node.GetNext;
  end;
end;





{只分配叶子设备，给商户树 增加分配设备}
procedure TfaqhSetBusinessEquipInfo.AddEquipToBusiTree2(B_node2:TTreeNode;E_node1:TTreeNode);
var
  BusiNode2:TTreeNode;  //用于记录选中的商户信息，
  EquipNode1:TTreeNode;  //用于记录选中的设备信息，
  EquipNode2:TTreeNode;
  Exist2:Boolean;
  CompareBusiNode3:TTreeNode;
  BusiAndEquSet2:TDataSet;
  AddBusiAndEquPara1:TBusiAndEquipNode1;
  EtoB:TTreeNode;
  i:integer;
begin
  BusiNode2:=B_node2;
  //判断是否是商户
  if TBusiAndEquipNode1(BusiNode2.Data).EquipCaption3='' then
  begin
    if (BusiNode2.getFirstChild=nil) or (TBusiAndEquipNode1(BusiNode2.getFirstChild.Data).EquipCaption3<>'') then
    begin
      {
      if E_node1.getFirstChild <> nil then
      begin
        ShowMessage('该设备不能分配！');
      end;
      }
      AddOneRecord(B_node2,E_node1);
      AddOneEquip(B_node2,E_node1);
      ShowMessage('分配设备成功！');
      //else
      //begin
      // TODO : 增加递归处理的功能
      //  MovedEquipList3(E_node1,EquipTreVw1);
      //end;

    end
    else
    begin
      ShowMessage(' 不是叶子商户 ');
    end;  //(BusiNode2.getFirstChild=nil)
  end
  else
  begin
    ShowMessage(' 不是商户节点 ');
  end;
end;


{给商户树 增加一个设备}
procedure TfaqhSetBusinessEquipInfo.AddOneEquip(B_node2:TTreeNode;E_node1:TTreeNode);
var
  AddBusiAndEquPara1:TBusiAndEquipNode1;
  BusiAndEquSet2:TDataSet;
begin
  if B_node2<>nil then
  begin
    if E_node1<>nil then
    begin
      //ShowMessage('已选中了设备 ');
      //ShowMessage('开始添加设备 ');
      treevEquAndBusi2.Items.BeginUpdate;
      AddBusiAndEquPara1:=TBusiAndEquipNode1.Create;
      try
        //ShowMessage(' 转换当前的日期、时间格式 ');
        DateTimeConv1;
        //支持从树节点，增加设备商户记录必须的信息:商户标识，
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
        //AddBusiAndEquPara1.EComment3:='这是 '+DateToStr(Date)+' '+TimeToStr(Time)+' 新增的设备';
        //ShowMessage(' 开始检查时间段是否冲突！ ');
        if CheckDateTime2(TBusiAndEquipNode1(B_node2.Data).BusiID3,TBusiAndEquipNode1(E_node1.Data).EquipID3,InsDate2,'000000',InsDate3,'235959')=true then
        begin
          ShowMessage(' 不能再增加该设备节点！已被分配！ ');
          //ShowMessage(' 退出前结束更新！ ');
          treevEquAndBusi2.Items.EndUpdate;
          exit;
        end
        else
        begin
          ;//ShowMessage(' 可增加该设备节点！ ');
        end;
        //ShowMessage(' 增加节点， ');
        treevEquAndBusi2.Items.AddChild(B_node2,E_node1.Text+' ('+DateTimeToStr(DBStrDateToDateTime(AddBusiAndEquPara1.EBegDate3))+' -> '+DateTimeToStr(DBStrDateToDateTime(AddBusiAndEquPara1.EEndDate3))+')');
        //ShowMessage(' 存储设备商户信息， ');
        B_node2.Item[B_node2.Count-1].Data:=AddBusiAndEquPara1;
        CurrentNode2:=B_node2.Item[B_node2.Count-1];
        //ShowMessage('把设备商户编号填进去， ');
        WorkView.FieldByName('编号').Data.SetInteger(0);
        //ShowWaiting('');
        QueryRequest.SendCommand;
        //CloseWaiting;
        BusiAndEquSet2:=(WorkView.FieldByName('查询结果集').Data.AsObject) as TDataSet;
        BusiAndEquSet2.Last;
        TBusiAndEquipNode1(B_node2.Item[B_node2.Count-1].Data).ENum3:=BusiAndEquSet2.fieldbyname(EquipIdcpk).AsInteger;
        treevEquAndBusi2.FullExpand;
        treevEquAndBusi2.Items.EndUpdate;
        //ShowMessage('添加设备成功');
      finally
        ;//ShowMessage(' 创建临时节点失败！ ');
      end;
    end
    else
    begin
      ;//ShowMessage('请在右边选择设备');
    end;
  end
  else
  begin
    ;//ShowMessage('您还没有选择商户');
  end;
end;


{仅仅给给商户树 删除一个设备}
procedure TfaqhSetBusinessEquipInfo.DelOneEquip3(B_node2:TTreeNode;E_node1:TTreeNode);
begin
  treevEquAndBusi2.Items.BeginUpdate;
  B_node2.Delete;
  treevEquAndBusi2.Items.EndUpdate;
end;


{给商户树 增加一个设备之前的准备工作，}
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
            //ShowMessage(' 隐藏编号框， ');
            WVDigitalEdit1.Visible:=False;
            btnOK.visible:=False;
            btnCancel.visible:=False;
            //ShowMessage(' 第一次修改标记， ');
            tsQuery.TabVisible:=false;
            tsEdit.TabVisible:=true;
            tsEdit.Show;
            WVDigitalEdit1.enabled:=false;
            WVDigitalEdit2.enabled:=false;
            WVDigitalEdit3.enabled:=false;
            WVDigitalEdit2.Text:=IntToStr(TBusiAndEquipNode1(E_node1.Data).EquipID3);
            WVDigitalEdit3.Text:=IntToStr(TBusiAndEquipNode1(B_node2.Data).BusiID3);
            //ShowMessage(' 添加设备名称、商户名称 ');
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
            WVEdit1.Text:='这是 '+DateToStr(Date)+' '+TimeToStr(Time)+' 新增的设备';
            //ShowMessage(' 修改允许增加的标记 ');
            AddMark2:=True;
          end
          else
          begin
            ShowMessage(' LPort不能被分配! ');
          end;
        end
        else
        begin
          ShowMessage(' 不能分配根商户! ');
        end;
      end
      else
      begin
        ShowMessage('非叶子商户不能分配设备！');
      end;
    end
    else if TBusiAndEquipNode1(B_node2.Data).EquipCaption3<>'' then
    begin
      ShowMessage('请在左边选择商户！');
    end;
  end
  else
  begin
    ShowMessage('您还未选择设备！');
  end;
end;

{给商户树 删除一个设备之前的准备工作，}
procedure TfaqhSetBusinessEquipInfo.Bef_DelEqu3(B_node2:TTreeNode;E_node1:TTreeNode);
var
  EquipDataSet2:TDataSet;
  DelEquipID2:Integer;
  ParentBusiID5:Integer;
begin
  if B_node2<>nil then
  begin
    //ShowMessage(' 查询出该条被删除的设备商户记录 ');
    QueryOneRec1(TBusiAndEquipNode1(B_node2.Data).ENum3);
    btnOK.visible:=False;
    btnCancel.visible:=False;
    //ShowMessage(' 添加设备名称、商户名称 ');
    Edit1.Text:=TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).EquipCaption3;
    Edit2.Text:=TBusiAndEquipNode1(treevEquAndBusi2.Selected.Parent.Data).BusiCaption3;
    GiveFieldToWVEdits;
    //ShowMessage(' 第一次修改标记， ');
    tsQuery.TabVisible:=false;
    tsEdit.TabVisible:=true;
    tsEdit.Show;
    //ShowMessage(' 修改允许删除的标记 ');
    DelMark2:=True;
  end
  else
  begin
    ShowMessage('请在左边选择设备');
  end;
end;


{给商户树 修改一个设备}
procedure TfaqhSetBusinessEquipInfo.ChaOneEquip1(B_node2:TTreeNode;E_node1:TTreeNode);
var
  BusiID4:integer;
  BusiDataSet4:TDataSet;
  ChaBusiCap4:String;
  ChaParentBusiNode4:TTreeNode;
begin
  //ShowMessage(' 修改设备节点的信息， ');
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EBegDate3:=WVEdit2.Text;
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EBegTime3:=WVEdit6.Text;
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EEndDate3:=WVEdit3.Text;
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EEndTime3:=WVEdit7.Text;
  TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data). EComment3:=WVEdit1.Text;
  //ShowMessage(' 显示信息的修改，设备节点的信息， ');
  treevEquAndBusi2.Selected.Text:=Edit1.Text+' ('
        +DateTimeToStr(DBStrDateToDateTime(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).EBegDate3))
        +' -> '+DateTimeToStr(DBStrDateToDateTime(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).EEndDate3))+')';
end;


{给商户树 增加分配设备}
procedure TfaqhSetBusinessEquipInfo.InitEquipToBusiTree;
var
  BusiAndEquipSet1:TDataSet;
begin
  //以下获取所有设备商户记录，
  WorkView.FieldByName('编号').Data.SetInteger(0);
  //ShowMessage(' 调用框架查询设备商户表记录， ');
  //QueryRequest.SendCommand;
  //ShowMessage(' 不调用框架查询设备商户表记录， ');
  BusiAndEquipSet1 := TDataSet.Create(nil);
  try
    QueryRequest6.SendCommand;
    BusiAndEquipSet1:=(WorkView.FieldByName('查询结果集').Data.AsObject) as TDataSet;
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
      // 释放内存
      SetLength(used_equi_ary,0);
    end;
  except
    on ex : Exception do
    begin
      Context.GetDialogSystem.ShowMessage (Ex.Message);
    end;
  end;
end;


{节点链，被移除的设备链,根据设备标识，}
procedure TfaqhSetBusinessEquipInfo.MovedEquipList3(P_Node:TTreeNode;P_Tree:TTreeView);
var
  TempNode1:TTreeNode;  //用于记录在设备树上找到的节点，
  TempNode2:TTreeNode;
  CurrentEquID1:integer;  //当前用于判断链的增长是否结束的设备标识，
  CurrentId:integer;  //记录设备链的下标，
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
  //ShowMessage('添加 '+AddEquList1[i].EquipCaption3+' 到设备链上 '+IntToStr(i)+' 位置成功');

  CurrentEquID1:=AddEquList1[CurrentId].EquipID3;

  //依据显示的设备标识，到设备树里，去找到该设备节点，前提：保证搜索算法正确，
  TempNode1:=FindCurrentBusinessNode5(CurrentEquID1,P_Tree);

  //如果在设备树上找到，如果有子设备，把它的第一级子设备添加到设备链中，
  if TempNode1<>nil then
  begin
    //ShowMessage('该设备已找到在设备树上');
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
      //ShowMessage('添加 '+AddEquList1[i].EquipCaption3+' 到设备链上 '+IntToStr(i)+' 位置成功');

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
        //ShowMessage('添加 '+AddEquList1[i].EquipCaption3+' 到设备链上 '+IntToStr(i)+' 位置成功');

      end;  //TempNode2.getNextSibling<>nil
    end;
  end  //TempNode1<>nil
  else
  begin
    ShowMessage('该设备不存在于设备树上！');
  end;

  //动态增加 设备链的设备节点，
  //ShowMessage('当前标记的设备标识是 '+IntToStr(CurrentEquID1));
  While CurrentEquID1<>AddEquList1[length(AddEquList1)-1].EquipID3 do
  begin
    //移动当前用于判断链结束的设备名称，
    CurrentId:=CurrentId+1;
    CurrentEquID1:=AddEquList1[CurrentId].EquipID3;

    //到设备树上去找到该设备节点，如果有子设备，把它的第一级子设备添加到设备链中，
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
        //ShowMessage('添加 '+AddEquList1[i].EquipCaption3+' 到设备链上 '+IntToStr(i)+' 位置成功');

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
          //ShowMessage('添加 '+AddEquList1[i].EquipCaption3+' 到设备链上 '+IntToStr(i)+' 位置成功');

        end;  //TempNode2.getNextSibling<>nil
      end;
    end;  //TempNode1<>nil
  end;  //While CurrentEquID1<>

end;


{释放设备节点链}
procedure TfaqhSetBusinessEquipInfo.FreeEquipParaTreeNode;
var
  i:integer;
  len:integer;
begin
  len:=Length(AddEquList1);
  for i:=0 to len-1 do
    AddEquList1[i].Free;
  SetLength(AddEquList1,0);
  //测试用：
  //ShowMessage('已把设备节点链清空');
end;


{增加一条设备商户记录}
procedure TfaqhSetBusinessEquipInfo.AddOneRecord(B_node2:TTreeNode;E_node1:TTreeNode);
begin
  //ShowMessage(' 插入一条记录： ');
  WorkView.FieldByName('设备标识').Data.SetInteger(TBusiAndEquipNode1(E_node1.Data).EquipID3);
  WorkView.FieldByName('商户标识').Data.SetFloat(TBusiAndEquipNode1(B_node2.Data).BusiID3);
  //ShowMessage(' 重新计算时间， ');
  DateTimeConv1;
  WorkView.FieldByName('使用开始日期').Data.SetString(WVEdit2.Text);
  //WorkView.FieldByName('使用开始日期').Data.SetString(InsDate2);
  //WorkView.FieldByName('使用开始时间').Data.SetString(InsTime2);
  WorkView.FieldByName('使用开始时间').Data.SetString(WVEdit6.Text);
  //WorkView.FieldByName('使用开始时间').Data.SetString('000000');
  InsDate3:=Copy(InsDate2,1,3)+IntToStr(StrToInt(Copy(InsDate2,4,1))+5)+Copy(InsDate2,5,4);
  WorkView.FieldByName('使用结束日期').Data.SetString(WVEdit3.Text);
  //WorkView.FieldByName('使用结束日期').Data.SetString(InsDate3);
  //WorkView.FieldByName('使用结束时间').Data.SetString(InsTime2);
  WorkView.FieldByName('使用结束时间').Data.SetString(WVEdit7.Text);
  //WorkView.FieldByName('使用结束时间').Data.SetString('235959');
  WorkView.FieldByName('备注').Data.SetString(WVEdit1.Text);
  //WorkView.FieldByName('备注').Data.SetString('这是 '+DateToStr(Date)+' '+TimeToStr(Time)+' 新增的设备');
  //ShowMessage(' 开始检查时间是否冲突 ');
  if CheckDateTime2(TBusiAndEquipNode1(B_node2.Data).BusiID3,TBusiAndEquipNode1(E_node1.Data).EquipID3,InsDate2,'000000',InsDate3,'235959')=true then
  begin
    ShowMessage(' 该设备在该时间段已被分配！ ');
    exit;
  end
  else
  begin
    ;//ShowMessage(' 该设备在该时间段可分配！ ');
  end;

  //ShowWaiting('');
  AddRequest.SendCommand;
  //CloseWaiting;
  //ShowMessage('插入设备 '+TBusiAndEquipNode1(E_node1.Data).EquipCaption3+' 商户 '+TBusiAndEquipNode1(B_node2.Data).BusiCaption3+' 记录成功');
end;


{删除一条设备商户记录，依据编号，}
procedure TfaqhSetBusinessEquipInfo.DelOneRecord1(EaB_ID1:integer);
begin
  //ShowMessage('待删除记录的设备名称是 '+SelEquipText2);
  WorkView.FieldByName('编号').Data.SetInteger(EaB_ID1);
  //测试用：
  //ShowMessage('待删除设备的编号是 ');
  //ShowWaiting('');
  DeleteRequest.SendCommand;
  //CloseWaiting;
end;


{修改一条设备商户记录，依据编号，}
procedure TfaqhSetBusinessEquipInfo.ChaOneRecord1(EaB_ID1:integer);
begin
  WorkView.FieldByName('编号').data.SetInteger(EaB_ID1);
  WorkView.FieldByName('设备标识').data.SetInteger(StrToInt(Trim(WVDigitalEdit2.Text)));
  WorkView.FieldByName('商户标识').data.SetFloat(StrToFloat(Trim(WVDigitalEdit3.Text)));
  WorkView.FieldByName('使用开始日期').data.SetString(Trim(WVEdit2.Text));
  WorkView.FieldByName('使用开始时间').data.SetString(Trim(WVEdit6.Text));
  WorkView.FieldByName('使用结束日期').data.SetString(Trim(WVEdit3.Text));
  WorkView.FieldByName('使用结束时间').data.SetString(Trim(WVEdit7.Text));
  WorkView.FieldByName('备注').data.SetString(Trim(WVEdit1.Text));
  //ShowMessage('数据已发送！ ');
  //ShowWaiting('');
  ChangeRequest.SendCommand;
  //CloseWaiting;
  //ShowMessage('修改执行完毕！ ');
end;


{查询一条设备商户记录，依据编号，}
procedure TfaqhSetBusinessEquipInfo.QueryOneRec1(EaB_ID1:integer);
begin
  WorkView.FieldByName('编号').Data.SetInteger(EaB_ID1);
  //ShowMessage('待修改设备的编号是 '+IntToStr(EaB_ID1));
  //ShowWaiting('');
  QueryRequest.SendCommand;
  //CloseWaiting;
  //ShowMessage('要修改设备商户记录已经查到');
  QeyOneBsEpSet1:=(WorkView.FieldByName('查询结果集').Data.AsObject) as TDataSet;
end;


{在确认 按钮里，增删改一个设备，}
procedure TfaqhSetBusinessEquipInfo.ADC_EB1;
begin
end;


{转换当前的日期、时间格式}
procedure TfaqhSetBusinessEquipInfo.DateTimeConv1;
begin
  if length(DateToStr(Date))>=10 then
  begin
    InsDate2:=Copy(DateToStr(Date),1,4)+Copy(DateToStr(Date),6,2)+Copy(DateToStr(Date),9,2);
  end
  else if length(DateToStr(Date))<=8 then
  begin  //比如2005-1-1
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
  begin  //比如2005-1-1
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


{按新需求，检查每一天的时间段是否冲突了,以某一设备来判断，而不必判断是哪个商户，}
function TfaqhSetBusinessEquipInfo.CheckDateTime2(B_ID:integer;E_ID:integer;B_D:String;B_T:String;E_D:String;E_T:String):Boolean;
var
  BusiAndEquipSet1:TDataSet;
begin
  result:=false;
  //以下获取所有设备商户记录，
  WorkView.FieldByName('编号').Data.SetInteger(0);
  try
    QueryRequest.SendCommand;
  except
    exit;//ShowMessage(' 商户设备表无记录， ');
  end;
  BusiAndEquipSet1:=(WorkView.FieldByName('查询结果集').Data.AsObject) as TDataSet;
  if BusiAndEquipSet1.RecordCount<=1 then
  begin
    //ShowMessage(' 商户设备表无记录， ');
    exit;
  end
  else
  begin
    BusiAndEquipSet1.First;
    While not BusiAndEquipSet1.Eof do
    begin
      //ShowMessage(' 本条记录不比较， ');
      if BusiAndEquipSet1.fieldbyname(BEnumcpk).AsInteger<>TBusiAndEquipNode1(treevEquAndBusi2.Selected.data).Enum3 then
      begin
        if BusiAndEquipSet1.fieldbyname(BEequipIdcpk).AsInteger=E_ID then
        begin
          //ShowMessage(' 先判断开始的， ');
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
          //ShowMessage(' 再判断结束的， ');
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
        ;//ShowMessage(' 本条记录不需要修改 ');
      end;
      BusiAndEquipSet1.next;
    end;
  end;
end;


{新加入的设备节点，}
function TfaqhSetBusinessEquipInfo.AddNewBusiEquiNode1(D1:TDataSet):TBusiAndEquipNode1;
var
  TempBusinessParaNode3:TBusiAndEquipNode1;  //临时节点，
  str : string;
begin
  TempBusinessParaNode3:=TBusiAndEquipNode1.Create;
  try
    if D1<>nil then
    begin
      //ShowMessage(' 设备标识是 '+D1.fieldbyname(EquipIdcpk).AsString);
      TempBusinessParaNode3.BusiID3:=0;
      TempBusinessParaNode3.BusiCaption3:='';
      TempBusinessParaNode3.BusiParentID3:=0;
      TempBusinessParaNode3.EquipID3:=D1.fieldbyname(EquipIdcpk).AsInteger;  //设备标识
      TempBusinessParaNode3.EquipCaption3:=D1.fieldbyname(EquipNamecpk).AsString;  //设备名称
      TempBusinessParaNode3.EquipIP3:=D1.fieldbyname(EquipMaccpk).AsString;  //设备物理ID
      TempBusinessParaNode3.EquipParentIP3:=D1.fieldbyname(PareEquipMaccpk).AsInteger;  //父设备物理ID
      TempBusinessParaNode3.EquipType3:=D1.fieldbyname(EquipTypecpk).AsString;  //父设备物理ID;
    end
    else
    begin
      //ShowMessage(' 添加根设备 ');
      TempBusinessParaNode3.BusiID3:=0;
      TempBusinessParaNode3.BusiCaption3:='';
      TempBusinessParaNode3.BusiParentID3:=0;
      TempBusinessParaNode3.EquipID3:=0;
      //ShowMessage(' 添加根节点设备名称, ');
      TempBusinessParaNode3.EquipCaption3:=RootEquipName1;
      TempBusinessParaNode3.EquipIP3:='FFFFFFFF';
      TempBusinessParaNode3.EquipParentIP3:=1;
      //ShowMessage(' 根节点后台定死的, ');
      TempBusinessParaNode3.EquipType3:='0000';
    end;
    result:=TempBusinessParaNode3;
  except
    result:=nil;
    //ShowMessage(' 创建数据集失败！ ');
  end;
end;


{新加入的商户节点，}
function TfaqhSetBusinessEquipInfo.AddNewBusiNode2(B1:TDataSet):TBusiAndEquipNode1;
var
  TempBusinessParaNode2:TBusiAndEquipNode1;  //临时节点，
begin
  TempBusinessParaNode2:=TBusiAndEquipNode1.Create;
  try
    if B1<>nil then
    begin
      //ShowMessage('上海大学 的商户标识是 '+B1.fieldbyname(BusiIdcpk).AsString);
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
    //ShowMessage(' 创建数据集失败！ ');
  end;
end;


{新加入的j设备商户节点，}
function TfaqhSetBusinessEquipInfo.AddNewB_ENode3(B_E3:TDataSet;ENode3:TTreeNode):TBusiAndEquipNode1;
var
  InitBusiAndEquPara1:TBusiAndEquipNode1;
begin
  InitBusiAndEquPara1:=TBusiAndEquipNode1.Create;
  //支持从树节点，增加设备商户记录必须的信息:商户标识，
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


{手动把WorkView的值，赋与WVEdit，}
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


{进入框架后的初始化工作}
procedure TfaqhSetBusinessEquipInfo.Init;
begin
  inherited;
  //ShowMessage(' 控制TabSheet的可见性， ');
  tsQuery.TabVisible:=true;
  tsEdit.TabVisible:=False;
  //ShowMessage(' 初始化查询无记录标志， ');
  NoRecord:=False;
  //ShowMessage(' 修改标志， ');
  NewBusiSel2:=False;
  NewEquipSel1:=False;
  DelEquSel2:=False;
  //ShowMessage(' 默认的根设备 ');
  RootEquipName1:='上海大学大学';
  //ShowMessage(' 清空Label ');
  Label16.Caption:='';
  Label17.Caption:='';
  //ShowMessage(' 初始化Cpack字段，',);
  BusiIdcpk:='lvol5';  //商户标识
  BusiNamecpk:='scard1';  //商户名称
  PareBusiIdcpk:='lvol1';  //父商户标识
  //ShowMessage(' 设备表Cpack字段，');
  EquipIdcpk:='lvol1';  //设备标识
  EquipNamecpk:='scert_no';  //设备名称
  EquipMaccpk:='sdate0';  //设备物理ID
  PareEquipMaccpk:='lvol2';  //父设备物理ID  sdate1
  EquipTypecpk:='sname2';  //机型代码

  //查询设备商户的CPack字段,功能号847164,
  QBEnumcpk:='lvol5';  //设备商户,编号
  QBEbusiIdcpk:='lvol0';  //设备商户,商户标识
  QBEequipIdcpk:='lvol2';  //设备商户,设备标识
  QBgnDatecpk:='sdate0';  //使用开始日期
  QEndDatecpk:='sdate1';  //使用开始日期
  QBenTimecpk:='scust_no';  //使用开始时间
  QEndTimecpk:='scust_no2';  //使用结束时间
  //增删改
  BEnumcpk:='lvol1';  //设备商户,编号
  BEbusiIdcpk:='damt0';  //设备商户,商户标识
  BEequipIdcpk:='lvol0';  //设备商户,设备标识
  BgnDatecpk:='scust_no';  //使用开始日期
  EndDatecpk:='scust_no2';  //使用开始日期
  BenTimecpk:='sholder_ac_no';  //使用开始时间
  EndTimecpk:='sholder_ac_no2';  //使用结束时间
  Commentcpk:='scusttypes';  //备注
  //初始化用于发送和返回数据的WorkView，
  WorkView.FieldByName('查询.编号').DefaultValue :=0;
  WorkView.FieldByName('编号').DefaultValue := 0;
  WorkView.FieldByName('设备标识').DefaultValue := 0;
  WorkView.FieldByName('查询.设备标识').DefaultValue := 0;
  WorkView.FieldByName('商户标识').DefaultValue :=0;
  WorkView.FieldByName('查询.商户标识').DefaultValue :=0;
  WorkView.FieldByName('使用开始日期').DefaultValue := '';
  WorkView.FieldByName('使用开始时间').DefaultValue := '';
  WorkView.FieldByName('使用结束时间').DefaultValue := '';
  WorkView.FieldByName('使用结束日期').DefaultValue := '';
  WorkView.FieldByName('备注').DefaultValue := '';
  WorkView.FieldByName('收费科目').DefaultValue := 0;
  WorkView.Reset;
  //以下初始化非主键查询 商户记录，
  WorkView1.FieldByName('商户标识').DefaultValue := 0;
  WorkView1.FieldByName('客户号').DefaultValue := 0;
  WorkView1.FieldByName('父商户标识').DefaultValue := 0;
  WorkView1.FieldByName('商户名称').DefaultValue := '';
  WorkView1.FieldByName('商户类别').DefaultValue := 0;
  WorkView1.FieldByName('是否为叶节点').DefaultValue := '';
  WorkView1.FieldByName('商户状态').DefaultValue := 0;
  WorkView1.FieldByName('负责人员工号').DefaultValue := '';
  WorkView1.FieldByName('负责人姓名').DefaultValue := '';
  WorkView1.FieldByName('负责人性别').DefaultValue := '';
  WorkView1.FieldByName('负责人民族').DefaultValue := 0;
  WorkView1.FieldByName('负责人身份证号').DefaultValue := '';
  WorkView1.FieldByName('联系电话').DefaultValue := '';
  WorkView1.FieldByName('联系地址').DefaultValue := '';
  WorkView1.FieldByName('是否收取管理费').DefaultValue := '';
  WorkView1.FieldByName('收取消费管理费比例').DefaultValue := 0.00;
  //WorkView1.FieldByName('商户管理费计算方式').DefaultValue := 0;
  //WorkView1.FieldByName('商户税费计算方式').DefaultValue := 0;
  WorkView1.FieldByName('注册时间').DefaultValue := '';
  WorkView1.FieldByName('备注').DefaultValue := '';
  WorkView1.Reset;
  //以下初始化非主键查询 设备记录，
  WorkView4.FieldByName('设备名称').DefaultValue := '';
  WorkView4.FieldByName('三九设备注册号').DefaultValue := '';
  WorkView4.FieldByName('设备物理ID').DefaultValue := '';
  WorkView4.FieldByName('机号').DefaultValue := 0;
  WorkView4.FieldByName('机型代码').DefaultValue := '';
  WorkView4.FieldByName('上级设备物理ID').DefaultValue :='' ;
  WorkView4.FieldByName('设备状态').DefaultValue := 0;
  WorkView4.FieldByName('设备物理型号').DefaultValue := 0;
  WorkView4.FieldByName('所属子系统').DefaultValue := 0;
  WorkView4.FieldByName('设备所在区域').DefaultValue := 0;
  WorkView4.FieldByName('负责人员工号').DefaultValue := '';  
  WorkView4.Reset;    
  SelBusiText2:='';
  //用设备与商户节点共用结构，显示商户树，
  ShowBusinessTree2;
  //treevEquAndBusi2.Refresh;
  //用设备与商户节点共用结构，显示设备树，
  ShowEquipTree3;
  //ShowMessage(' 初始化时，依据设备商户表把设备挂到商户树上， ');
  InitEquipToBusiTree;
end;


{点击“增加设备”按钮，开始增加设备到商户，添加设备商户记录}
procedure TfaqhSetBusinessEquipInfo.btnAddEB1Click(Sender: TObject);
var
  tmp_data : TBusiAndEquipNode1;
begin
  //ShowMessage(' 增加设备前的准备工作 ');
  if treevEquAndBusi2.Selected<>nil then
  begin
    if EquipTreVw1.Selected<>nil then
    begin
      {判断设备类型}
      tmp_data := TBusiAndEquipNode1(EquipTreVw1.Selected.Data);
      if (tmp_data.EquipType3 = '5301') or
        (EquipTreVw1.Selected.Parent = nil) then
      begin
        ShowMessage('该类型设备不可以分配！');
        Exit;
      end;
      Bef_AddEqu3(treevEquAndBusi2.Selected,EquipTreVw1.Selected);
    end
    else
    begin
      ShowMessage(' 请选择设备！ ');;
    end;
  end
  else
  begin
    ShowMessage(' 请先选择商户 ');;
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
      ShowMessage(' 请将删除该设备及其所有子设备！');
      MovedEquipList3(tmp,treevEquAndBusi2);
      //ShowMessage(' 删除该设备及其所有子设备节点！');
      tmp.Delete;
    end;
  end
  else
  begin
    ShowMessage(' 请先从设备商户树上选中设备！');
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
    showmessage('根商户没有设备可供修改！');
    exit;
  end;
  if (treevEquAndBusi2.Selected<>nil) then
  begin
    //ShowMessage('查询一条设备商户记录，依据编号，');
    QueryOneRec1(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).ENum3);
    //ShowMessage(' 跳到编辑设备商户信息的界面， ');
    GiveFieldToWVEdits;
    //ShowMessage(' 添加设备名称、商户名称 ');
    Edit1.Text:=TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).EquipCaption3;
    Edit2.Text:=TBusiAndEquipNode1(treevEquAndBusi2.Selected.Parent.Data).BusiCaption3;
    //ShowMessage(' 第一次修改标记， ');
    tsQuery.TabVisible:=false;
    tsEdit.TabVisible:=true;
    tsEdit.Show;
    btnOK.visible:=False;
    btnCancel.visible:=False;
    Edit1.ReadOnly:=true;
    //ShowMessage(' 打上允许修改标记， ');
    ChaMark2:=True;
  end
  else
  begin
    ShowMessage('请在左边选择设备');
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
      Label16.Caption:='您还未选择商户！';
      Label16.font.color:=clRed;
    end;
  end
  else
  begin
    ;//ShowMessage(' 没有选中的节点， ');
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
  //ShowMessage(' 作修改一个设备节点前的工作， ');
  btnBefChaEB2Click(nil);
  //ShowMessage(' 在菜单里处理日期、时间， ');

end;


procedure TfaqhSetBusinessEquipInfo.DelEquAndBus1Click(Sender: TObject);
begin

  btnBefDelEB2Click(nil);

end;

procedure TfaqhSetBusinessEquipInfo.btnReTree1Click(Sender: TObject);
begin
  //ShowMessage(' 刷新显示设备树， ');
  try
    try
      btnReTree1.Enabled := False;
      // 删除原来的节点内存数据
      FreeTreeNodeData(EquipTreVw1.Items);
      FreeTreeNodeData(treevEquAndBusi2.Items);
      // 更新树
      ShowBusinessTree2;
      ShowEquipTree3;
      InitEquipToBusiTree;
    except
      // FIXME : 可能有内存泄漏的错误，有待检查
    end;
  finally
    btnReTree1.Enabled := True;
  end;
end;

procedure TfaqhSetBusinessEquipInfo.btnAdDlChCcl3Click(Sender: TObject);
begin
  //ShowMessage(' 修改TabSheet的可见性， ');
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
  //ShowMessage(' 先继承框架的方法， ');
  //inherited;
  //ShowMessage(' 再重新设置标记， ');
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
  ////ShowMessage(' 重置允许增删改的标记， ');
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
    // 节点数据
    while not ds.Eof do
    begin
      // 处理消息
      Application.ProcessMessages;
      curr_id := ds.FieldByName(BusiIdcpk).AsInteger;
      parent_id := ds.FieldByName(PareBusiIdcpk).AsInteger;
      curr_caption := ds.FieldByName(BusiNamecpk).AsString;
      // 判断节点
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
  // 通过 DataSet 来生成 Tree
  if ds = nil then
  begin
    raise Exception.Create('DataSet 为空');
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
    // 节点数据
    while not ds.Eof do
    begin
      // 处理消息
      Application.ProcessMessages;
      curr_id := ds.FieldByName(EquipMaccpk).AsString;
      parent_id := ds.FieldByName(PareEquipMaccpk).AsInteger;
      curr_caption := ds.FieldByName(EquipNamecpk).AsString;
      //showmessage(curr_id + ':' + parent_id);
      // 判断节点
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
  // 通过 DataSet 来生成 Tree
  if ds = nil then
  begin
    raise Exception.Create('DataSet 为空');
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
        // 释放内存
        node_data := TBusiAndEquipNode1(curr.Data);
        curr.Data := nil;
        node_data.Free;
      end;
      // 删除子节点
      RecursiveFree(node.getFirstChild);
      // 下一个兄弟
      curr := curr.getNextSibling;
    end;
  end;
begin
  RecursiveFree(nodes.GetFirstNode);
end;

destructor TfaqhSetBusinessEquipInfo.Destroy;
begin
  inherited;
  // 在关闭时必须释放树结构的节点数据内存！！
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
        and (curr_data.BusiID3 = parent_id)  // 为父结点
        and ((curr_data.EquipCaption3 = '')
          or (curr_data.BusiCaption3 = ''))  // 不是设备商户结点
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
    // 取得记录数
    ds.Last;
    rec_count := ds.RecNo;
    // 节点数据
    ds.First;
    SetLength(used_equi_ary,rec_count);
    while not ds.eof do
    begin
      // 处理消息
      Application.ProcessMessages;
      curr_id := ds.FieldByName(BEnumcpk).AsInteger;
      parent_id := ds.FieldByName(BEbusiIdcpk).AsInteger;
      // 判断节点
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
      // 居然没有找到商户节点！！！肯定是垃圾数据，过滤掉！
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
  // 通过 DataSet 来生成 Tree
  if ds = nil then
  begin
    raise Exception.Create('DataSet 为空');
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
    raise Exception.Create('DataSet 为空！');
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
      // 先更新子结点
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
    Showmessage('时间不能为空，请输入！');
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
      // 不是正确的日期格式
    end;
  end;
  if not Result then
     ShowMessage(Format('您输入的日期[%s]格式不正确!'#13
      + '如果要输入2005年6月18日,请输入20050618',[input]));
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
    Showmessage('日期不能为空，请输入！');
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
    ShowMessage(' 删除一条设备商户记录!');
    DelOneRecord1(StrToInt(WVDigitalEdit1.text));
    //ShowMessage(' 删除一个设备 ');
    DelOneEquip3(treevEquAndBusi2.Selected,nil);
    //ShowMessage(' 跳到查询界面， ');
    //ShowMessage(' 修改TabSheet的可见性， ');
    tsQuery.TabVisible:=true;
    tsEdit.TabVisible:=false;
    tsQuery.Show;
    //ShowMessage(' 修改允许删除的标记， ');
    DelMark2:=False;
  end
  else if (AddMark2=False) and (DelMark2=False) and (ChaMark2=True) then
  begin
    //ShowMessage(' 开始修改， ');
    if CheckDateTime2(StrToInt(WVDigitalEdit3.Text),StrToInt(WVDigitalEdit2.Text),WVEdit2.Text,WVEdit6.Text,WVEdit3.Text,WVEdit7.Text)=True then
    begin
      ShowMessage('使用时间冲突，不能修改！ ');
      exit;
    end
    else
    begin
      //ShowMessage(' 修改一条设备商户记录的编号， '+IntToStr(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).Enum3));
      ChaOneRecord1(TBusiAndEquipNode1(treevEquAndBusi2.Selected.Data).Enum3);
      //ShowMessage(' 修改一个设备 ');
      ChaOneEquip1(nil,nil);
      //ShowMessage(' 跳到查询界面， ');
      //ShowMessage(' 修改TabSheet的可见性， ');
      tsQuery.TabVisible:=true;
      tsEdit.TabVisible:=false;
      tsQuery.Show;
      //ShowMessage(' 修改允许修改的标记， ');
      ChaMark2:=False;
    end;
  end
  else
  begin
    ShowMessage(' 不允许增删改设备 ');
  end;
end;

initialization
  TUIStdClassFactory.Create('设备商户关系设置',TfaqhSetBusinessEquipInfo);

end.
