unit UAconsumeBalance;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzSplit, ComCtrls, RzTreeVw, Buttons;

type
  PMyRec = ^TMyRec;
  TMyRec = record
    id: Integer;
    name: string;
end;
type
  TfaqhconsumeBalance = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    rzszpnl1: TRzSizePanel;
    tvCust: TRzTreeView;
    WorkView2: TWorkView;
    QueryRequest2: TWVRequest;
    Label3: TLabel;
    lblName: TLabel;
    rb1: TRzGroupBox;
    Label1: TLabel;
    edtOperCode: TWVEdit;
    WVEdit2: TWVEdit;
    Label2: TLabel;
    Label4: TLabel;
    WVEdit4: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure tvCustClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    custId:integer;
    custName:string;
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
  faqhconsumeBalance: TfaqhconsumeBalance;

implementation

uses KsFrameworks,KSClientConsts;
     
{$R *.DFM}

procedure TfaqhconsumeBalance.AddDataToTree(TreeView: TRZTreeView;
  DataSet: TDataSet);
var
  MyRecPtr: PMyRec;
  parentId:TTreeNode;
begin
  TreeView.Items.Clear;
  DataSet.First;
  New(MyRecPtr);
  MyRecPtr^.id := DataSet.fieldbyname('lvol5').AsInteger;
  MyRecPtr^.name := DataSet.fieldbyname('scard1').AsString;
  TreeView.Items.AddObject(nil,DataSet.fieldbyname('scard1').AsString,MyRecPtr);
  DataSet.Next;
  while not DataSet.Eof do
  begin
    New(MyRecPtr);
    MyRecPtr^.id := DataSet.fieldbyname('lvol5').AsInteger;
    MyRecPtr^.name := DataSet.fieldbyname('scard1').AsString;
    parentId:=findParent(DataSet.fieldbyname('lvol1').AsInteger);
    if parentId<>nil then
      TreeView.Items.AddChildObject(parentId,DataSet.fieldbyname('scard1').AsString,MyRecPtr)
    else
      TreeView.Items.AddObject(nil,DataSet.fieldbyname('scard1').AsString,MyRecPtr);
    DataSet.Next;
  end;
end;

function TfaqhconsumeBalance.findParent(parentId: Integer): TTreeNode;
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

procedure TfaqhconsumeBalance.Init;
begin
  inherited;
  {
  WorkView.FieldByName('����Ա��').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('�̻��˺�').DefaultValue := '';
  WorkView.FieldByName('���').DefaultValue := 0.00;
  WorkView.Reset;
  }
  RefreshCurrentTree;
  edtOperCode.Text := Context.ParamData(svOperatorNoName).AsString;

end;

procedure TfaqhconsumeBalance.RefreshCurrentTree;
var
  HasDataSet:Integer;
  DataSet:TDataSet;
begin
  DataSet := nil;
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

procedure TfaqhconsumeBalance.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhconsumeBalance.tvCustClick(Sender: TObject);
begin
  if not tvCust.Selected.Selected then
    exit;
  //if tvCust.Selected.HasChildren then
    //exit;
  custId:=PMyRec(Tvcust.selected.Data)^.id;
  custName:=PMyRec(Tvcust.selected.Data)^.name;
  lblName.Caption:=custName;
end;

procedure TfaqhconsumeBalance.btnQueryClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ�������ѽ��������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView.FieldByName('�̻��˺�').Data.SetString(IntToStr(custId));
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger=0 then
    ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString);
end;

initialization
  TUIStdClassFactory.Create('���ѽ���',TfaqhconsumeBalance);

end.