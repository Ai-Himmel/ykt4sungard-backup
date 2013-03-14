unit UAPayInQuery_nju;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzTreeVw, RzPanel, RzSplit, UqhTreeSimQryTemp,KsBranchTree,contnrs;
type
  PMyRec = ^TMyRec;
  TMyRec = record
    id: Integer;
    name: string;
end;
type
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
  TfaqhBusiPayInQuery_nju = class(TfaqhTreeSimQryTemp)
    Panel1: TPanel;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    QueryRequest2: TWVRequest;
    WorkView2: TWorkView;
    lblBusiname: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure tvCustClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
    FList: TObjectList;
    strBDate:string;
    custId:integer;
    custName:string;
    //刷新商户树
    procedure RefreshCurrentTree();
    procedure   BuildTree();
    procedure   InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBusiPayInQuery_nju: TfaqhBusiPayInQuery_nju;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhBusiPayInQuery_nju.Init;
begin
  inherited;
  if FInfoAdmin<>nil then
  begin
    FInfoAdmin.Free ;
  end;
  FInfoAdmin := TInfoAdmin.Create;

  //TreeView.ControlStyle := TreeView.ControlStyle - [csDoubleClicks];
  FList := TObjectList.Create;
  RefreshCurrentTree;
  edtBeginDate.Text := FormatDateTime('yyyy',Date);
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

procedure TfaqhBusiPayInQuery_nju.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhBusiPayInQuery_nju.btnQueryClick(Sender: TObject);
begin
    if CheckInputDateFormat(edtBeginDate.Text+'0101')=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始日期输入不正确，格式：yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  WorkView.FieldByName('商户号').Data.SetInteger(custId);
  //MainRequest.SendCommand;
  inherited;
  strBDate := edtBeginDate.Text;

end;

procedure TfaqhBusiPayInQuery_nju.RefreshCurrentTree;
begin
  try
    WorkView2.FieldByName('商户标识').Data.SetInteger(0);
    QueryRequest2.SendCommand;

    self.FDataSetFieldID:='lvol3';
    self.FDataSetParentFieldID:='lvol1';
    self.FDataSetFieldName:='sall_name';
    self.FDataSet:= (WorkView2.FieldByName('查询结果集').Data.AsObject) as TDataSet;
    BuildTree;
  except
    on e:Exception do
      Context.GetDialogSystem.ShowMessage(e.Message);
  end;
end;

procedure TfaqhBusiPayInQuery_nju.tvCustClick(Sender: TObject);
begin
  if not tvTree.Selected.Selected then
    exit;
  try
    custId:=PMyRec(tvTree.Selected.Data)^.id;
    custName:=PMyRec(tvTree.Selected.Data)^.name;
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(ex.Message);
      Exit;
    end;
  end;
  lblBusiname.Caption := '当前选择的商户:'+inttostr(custid)+'--'+custName;
end;

procedure TfaqhBusiPayInQuery_nju.btnPrintClick(Sender: TObject);
begin
  self.DateSpotTitle:='解款年份：'+strBDate;
  inherited;

end;

procedure TfaqhBusiPayInQuery_nju.BuildTree;
begin
  tvTree.Items.BeginUpdate;
  try
    tvTree.Items.Clear;
    if FInfoAdmin=nil then Exit;
    ReadTreeInfoFromDataSet(FDataSet,FInfoAdmin);
    InternalBuildTree(FInfoAdmin.Root, nil);
    //tvTree.FullExpand ;
  finally
    tvTree.Items.EndUpdate;
  end;
end;

procedure TfaqhBusiPayInQuery_nju.InternalBuildTree(AInfo: TUIInfo;Parent: TTreeNode);
var
  I: Integer;
  Node: TTreeNode;
  InfoData: TTreeNodeInfoData;
  MyRecPtr: PMyRec;
begin
  // 创建对应的数据对象
  InfoData := TTreeNodeInfoData.Create(AInfo.MetaNode);
  FList.Add(InfoData);
  New(MyRecPtr);
  MyRecPtr^.id := StrToInt(InfoData.GetID);
  MyRecPtr^.name := InfoData.GetCaption;
  Node := tvTree.Items.AddChildObject(Parent,InfoData.GetCaption,MyRecPtr);
  // 如果包含子节点，构造它们
  if AInfo is TUIInfoGroup then
    for I := 0 to TUIInfoGroup(AInfo).Count - 1 do
      InternalBuildTree(TUIInfoGroup(AInfo).Items[I],Node);
end;

initialization
  TUIStdClassFactory.Create('商户解款查询_nju',TfaqhBusiPayInQuery_nju);

end.