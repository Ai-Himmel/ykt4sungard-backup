unit UAsetBusiCC;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs, RzTreeVw;
type
  PMyRec = ^TMyRec;
  TMyRec = record
    id: Integer;
    name: string;
end;

type
  TfaqhsetBusiCC = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    WVDigitalEdit1: TWVDigitalEdit;
    pnl1: TPanel;
    pnl2: TPanel;
    tvCust: TRzTreeView;
    grp1: TGroupBox;
    Label7: TLabel;
    edtTime1: TWVEdit;
    edtTime2: TWVEdit;
    Label8: TLabel;
    Label9: TLabel;
    edtTime3: TWVEdit;
    QueryRequest2: TWVRequest;
    WorkView2: TWorkView;
    lbl1: TLabel;
    lblBusi: TLabel;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure tvCustClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure btnViewDetailClick(Sender: TObject);
  private

    { Private declarations }
    busiId:integer;
    custName:string;
    OperatorNoName:string;
    //ˢ���̻���
    procedure RefreshCurrentTree();
    //�����̻�������ӵ���
    procedure AddDataToTree(TreeView:TRZTreeView;DataSet:TDataSet);
    //���Ҹ��ڵ�
    function findParent(parentId:Integer):TTreeNode;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetBusiCC: TfaqhsetBusiCC;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhsetBusiCC.AddDataToTree(TreeView: TRZTreeView;
  DataSet: TDataSet);
var
  MyRecPtr: PMyRec;
  parentId:TTreeNode;
begin
  TreeView.Items.Clear;
  DataSet.First;
  New(MyRecPtr);
  MyRecPtr^.id := DataSet.fieldbyname('lvol3').AsInteger;
  MyRecPtr^.name := DataSet.fieldbyname('sall_name').AsString;
  TreeView.Items.AddObject(nil,DataSet.fieldbyname('sall_name').AsString,MyRecPtr);
  DataSet.Next;
  while not DataSet.Eof do
  begin
    New(MyRecPtr);
    MyRecPtr^.id := DataSet.fieldbyname('lvol3').AsInteger;
    MyRecPtr^.name := DataSet.fieldbyname('sall_name').AsString;
    parentId:=findParent(DataSet.fieldbyname('lvol1').AsInteger);
    if parentId<>nil then
      TreeView.Items.AddChildObject(parentId,DataSet.fieldbyname('sall_name').AsString,MyRecPtr)
    else
      TreeView.Items.AddObject(nil,DataSet.fieldbyname('sall_name').AsString,MyRecPtr);
    DataSet.Next;
  end;
end;

function TfaqhsetBusiCC.findParent(parentId: Integer): TTreeNode;
var
  i:Integer;
begin
  Result:=nil;
  for i := 0 to tvcust.Items.Count-1 do
  begin
    if Integer(tvcust.Items[i].Data^)=parentId then
    begin
      Result:=tvcust.Items[i];
      Exit;
    end;
  end;
end;

procedure TfaqhsetBusiCC.Init;
begin
  inherited;
  {
  WorkView.FieldByName('��ѯ.�̻����').DefaultValue := 0;
  WorkView.FieldByName('��ѯ.��ͽ���ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��ͽ���ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ѯ.��ͽ���ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ѯ.ҹ������ʱ��').DefaultValue := '';
  WorkView.FieldByName('�̻����').DefaultValue := 0;
  WorkView.FieldByName('��ͽ���ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ͽ���ʱ��').DefaultValue := '';
  WorkView.FieldByName('��ͽ���ʱ��').DefaultValue := '';
  WorkView.FieldByName('ҹ������ʱ��').DefaultValue := '';
  WorkView.Reset;
  }
  RefreshCurrentTree;
end;

procedure TfaqhsetBusiCC.RefreshCurrentTree;
var
  HasDataSet:Integer;
  DataSet:TDataSet;
begin
  Try
    HasDataSet:=0;
    WorkView2.FieldByName('�̻���ʶ').Data.SetInteger(0);
    try
      QueryRequest2.SendCommand;
      HasDataSet:=1;
    finally
      CloseWaiting;
    end;
    if HasDataSet=0 then
    begin
       Context.GetDialogSystem.ShowMessage('�̻���Ϣ��ѯ����������ִ�иò�����');
       Exit;
    end;
    DataSet:=(WorkView2.FieldByName('��ѯ�����').Data.AsObject) as TDataSet;
    AddDataToTree(tvCust,DataSet);
    tvCust.Items[0].Selected:=true;
    //tvCust.FullExpand;
  Finally
    DataSet.Free;
  end;
end;

procedure TfaqhsetBusiCC.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhsetBusiCC.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetBusiCC.tvCustClick(Sender: TObject);
var
  DataSet:TDataSet;
  tmpItem: TListItem;
begin
  if not tvCust.Selected.Selected then
    exit;
  if tvCust.Selected.HasChildren then
    exit;
  busiId:=PMyRec(Tvcust.selected.Data)^.id;
  custName:=PMyRec(Tvcust.selected.Data)^.name;
  lblBusi.Caption:=custName;
end;

procedure TfaqhsetBusiCC.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('�������').Data.SetString('R');
  inherited;

end;

procedure TfaqhsetBusiCC.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('�������').Data.SetString('A');
end;

procedure TfaqhsetBusiCC.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('�������').Data.SetString('D');
  busiId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  lblBusi.Caption := Grid.DataSource.DataSet.fieldbyname('vsvarstr1').AsString;
end;

procedure TfaqhsetBusiCC.btnOKClick(Sender: TObject);
begin
  if busiId<=0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ���Ӳʹε��̻���');
    Exit;
  end;
  if (Trim(edtTime1.Text)<>'') and (CheckInputTimeFormat(edtTime1.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('��͵�ʱ���ʽ����ȷ�����������룡');
    edtTime1.SetFocus;
    Exit;
  end;
  if (Trim(edtTime2.Text)<>'') and (CheckInputTimeFormat(edtTime2.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('��͵�ʱ���ʽ����ȷ�����������룡');
    edtTime2.SetFocus;
    Exit;
  end;
  if (Trim(edtTime3.Text)<>'') and (CheckInputTimeFormat(edtTime3.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('��͵�ʱ���ʽ����ȷ�����������룡');
    edtTime3.SetFocus;
    Exit;
  end;
  WorkView.FieldByName('�̻����').Data.SetInteger(busiId);
  inherited;
  busiId := 0;
  btnQuery.Click;
end;

procedure TfaqhsetBusiCC.btnCancelClick(Sender: TObject);
begin
  inherited;
  busiId := 0;
end;

procedure TfaqhsetBusiCC.GridDblClick(Sender: TObject);
begin
  inherited;
  lblBusi.Caption := Grid.DataSource.DataSet.fieldbyname('vsvarstr1').AsString;

end;

procedure TfaqhsetBusiCC.btnViewDetailClick(Sender: TObject);
begin
  inherited;
  lblBusi.Caption := Grid.DataSource.DataSet.fieldbyname('vsvarstr1').AsString;

end;

initialization
  TUIStdClassFactory.Create('�̻��ʹ���Ϣ����',TfaqhsetBusiCC);

end.