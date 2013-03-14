unit UABusiGatherReport;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzSplit, ComCtrls, RzTreeVw, Buttons,
  UReportMachineTemp, RM_Common, RM_Class, RM_e_main, RM_e_Xls,
  RM_Designer, RM_Dataset, ImgList, RM_Preview, RzButton,
  ZAbstractRODataset, ZAbstractDataset, ZAbstractTable, ZDataset,
  RM_e_Jpeg, RM_e_Graphic, RM_e_bmp, RM_e_htm, UTreeRptTemp,KsBranchTree,contnrs,
  UIncrementComboBox;
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
  TfaqhBusiGatherReport = class(TfaTreeRptTemp)
    WorkView2: TWorkView;
    QueryRequest2: TWVRequest;
    Panel1: TPanel;
    edtBeginDate: TWVEdit;
    lbl1: TLabel;
    Label1: TLabel;
    edtEndDate: TWVEdit;
    pnl1: TPanel;
    lbl2: TLabel;
    cbbleave: TComboBox;
    ztbl1: TZTable;
    Label2: TLabel;
    cbbType: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure tvtreeClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    FList: TObjectList;
    strBDate,strEDate:string;
    custId:integer;
    custName:string;
    //ˢ���̻���
    procedure RefreshCurrentTree();
    procedure getLeval;
    procedure   BuildTree();
    procedure   InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBusiGatherReport: TfaqhBusiGatherReport;

implementation

uses KsFrameworks,KSClientConsts,SmartCardCommon, UCMqhReportImp, UrptTbl;
     
{$R *.DFM}

procedure TfaqhBusiGatherReport.Init;
begin
  inherited;
  if FInfoAdmin<>nil then
  begin
    FInfoAdmin.Free ;
  end;
  FInfoAdmin := TInfoAdmin.Create;

  FList := TObjectList.Create;
  RefreshCurrentTree;
  getLeval;
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
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


procedure TfaqhBusiGatherReport.RefreshCurrentTree;
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

procedure TfaqhBusiGatherReport.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhBusiGatherReport.tvtreeClick(Sender: TObject);
begin
  if not tvTree.Selected.Selected then
    exit;
  custId:=PMyRec(tvTree.Selected.Data)^.id;
  custName:=PMyRec(tvTree.Selected.Data)^.name;
  pnl1.Caption := ' '+inttostr(custid)+'--'+custName;
end;

procedure TfaqhBusiGatherReport.btnQueryClick(Sender: TObject);
var
  //subId,subName:string;
  tmpData:TDataSet;
  qry:TZQuery;

begin
  if (Trim(edtBeginDate.Text)='') or (Trim(edtEndDate.Text)='') then
  begin
    Context.GetDialogSystem.ShowMessage('�����뿪ʼ���ںͽ������ڣ�');
    Exit;
  end;
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
  WorkView.FieldByName('�̻��˺�').Data.SetInteger(custId);
  WorkView.FieldByName('����').Data.SetInteger(cbbleave.ItemIndex+1);
  MainRequest.SendCommand;
  strBDate := edtBeginDate.Text;
  strEDate := edtEndDate.Text;

  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  if tmpData.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('����ͳ�Ʊ�û����ؼ�¼��������ָ������');
    Exit;
  end;
  if execSQL_SLite(delrptdailyacc)<>0 then
    Exit;
  //execSQL(delrptdailyacc);
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := dmReportImp.conSLite;
    if execSQL_SLite(beginTrans)<>0 then
      Exit;
    tmpData.First;
    while not tmpData.Eof do
    begin
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(irptDailyAccSql(tmpData));
      qry.ExecSQL;
      tmpData.Next;
    end;
    if execSQL_SLite(commitTrans)<>0 then
      Exit;
  finally
    qry.Close;
    qry.Destroy;
  end;
  try
    rptReport.LoadFromFile(sPreAppPath+'report\�̻����ܽ����.rmf');
    //ztbl1.TableName := 't_rptsysstat';
    if ztbl1.Active=True then
      ztbl1.Active := False;
    ztbl1.Active := True;
    rptReport.Dictionary.Variables.AsString['dateRange'] := 'ͳ�����ڣ�'+strBDate+'��'+strEDate;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
  end;

end;

procedure TfaqhBusiGatherReport.getLeval;
var
  i,j:integer;
  currlevel:integer;
  totlevel:integer;
begin
  totlevel:=0;
  for i := 0 to tvTree.Items.Count-1 do
  begin
    currlevel:=tvTree.Items[i].Level;
    if totlevel<currlevel then
      totlevel := currlevel;
  end;
  cbbleave.Items.Clear;
  for j := 1 to totlevel+1 do
    cbbleave.Items.Add('��'+inttostr(j)+'��');

  cbbleave.ItemIndex:=0;
end;

procedure TfaqhBusiGatherReport.BuildTree;
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

procedure TfaqhBusiGatherReport.InternalBuildTree(AInfo: TUIInfo;Parent: TTreeNode);
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
  //Node.ImageIndex:=ClearIndex;
  // ��������ӽڵ㣬��������
  if AInfo is TUIInfoGroup then
    for I := 0 to TUIInfoGroup(AInfo).Count - 1 do
      InternalBuildTree(TUIInfoGroup(AInfo).Items[I],Node);
end;

initialization
  TUIStdClassFactory.Create('�̻����ܽ����',TfaqhBusiGatherReport);

end.