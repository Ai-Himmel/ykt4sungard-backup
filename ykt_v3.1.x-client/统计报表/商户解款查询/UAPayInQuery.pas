unit UAPayInQuery;

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
  TfaqhBusiPayInQuery = class(TfaqhTreeSimQryTemp)
    Panel1: TPanel;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    WVLabel2: TWVLabel;
    edtEndDate: TWVEdit;
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
    strBDate,strEDate:string;
    custId:integer;
    custName:string;
    //ˢ���̻���
    procedure RefreshCurrentTree();
    procedure   BuildTree();
    procedure   InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBusiPayInQuery: TfaqhBusiPayInQuery;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhBusiPayInQuery.Init;
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
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
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

procedure TfaqhBusiPayInQuery.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhBusiPayInQuery.btnQueryClick(Sender: TObject);
begin
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ�');
  WorkView.FieldByName('�̻���').Data.SetInteger(custId);
  //MainRequest.SendCommand;
  inherited;
  strBDate := edtBeginDate.Text;
  strEDate := edtEndDate.Text;

end;

procedure TfaqhBusiPayInQuery.RefreshCurrentTree;
begin
  try
    WorkView2.FieldByName('�̻���ʶ').Data.SetInteger(0);
    QueryRequest2.SendCommand;

    self.FDataSetFieldID:='lvol3';
    self.FDataSetParentFieldID:='lvol1';
    self.FDataSetFieldName:='sall_name';
    self.FDataSet:= (WorkView2.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;
    BuildTree;
  except
    on e:Exception do
      Context.GetDialogSystem.ShowMessage(e.Message);
  end;
end;

procedure TfaqhBusiPayInQuery.tvCustClick(Sender: TObject);
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
  lblBusiname.Caption := '��ǰѡ����̻�:'+inttostr(custid)+'--'+custName;
end;

procedure TfaqhBusiPayInQuery.btnPrintClick(Sender: TObject);
begin
  self.DateSpotTitle:='��ʼ���ڣ�'+strBDate+' ~ �������ڣ�'+strEDate;
  inherited;

end;

procedure TfaqhBusiPayInQuery.BuildTree;
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

procedure TfaqhBusiPayInQuery.InternalBuildTree(AInfo: TUIInfo;Parent: TTreeNode);
var
  I: Integer;
  Node: TTreeNode;
  InfoData: TTreeNodeInfoData;
  MyRecPtr: PMyRec;
begin
  // ������Ӧ�����ݶ���
  InfoData := TTreeNodeInfoData.Create(AInfo.MetaNode);
  FList.Add(InfoData);
  New(MyRecPtr);
  MyRecPtr^.id := StrToInt(InfoData.GetID);
  MyRecPtr^.name := InfoData.GetCaption;
  Node := tvTree.Items.AddChildObject(Parent,InfoData.GetCaption,MyRecPtr);
  // ��������ӽڵ㣬��������
  if AInfo is TUIInfoGroup then
    for I := 0 to TUIInfoGroup(AInfo).Count - 1 do
      InternalBuildTree(TUIInfoGroup(AInfo).Items[I],Node);
end;

initialization
  TUIStdClassFactory.Create('�̻�����ѯ',TfaqhBusiPayInQuery);

end.