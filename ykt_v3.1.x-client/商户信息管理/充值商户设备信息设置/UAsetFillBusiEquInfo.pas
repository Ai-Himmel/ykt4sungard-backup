unit UAsetFillBusiEquInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  RzListVw, Buttons;

type
  TfaqhsetFillBusiEquInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    WVComboBox1: TWVComboBox;
    grp1: TGroupBox;
    cbbBusiName: TWVComboBox;
    Label5: TLabel;
    lvEqu: TRzListView;
    WorkView1: TWorkView;
    MainRequest: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure GridDblClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
    procedure fillEquList;
    function getBusiStr: string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetFillBusiEquInfo: TfaqhsetFillBusiEquInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhsetFillBusiEquInfo.fillEquList;
var
  tmpDataSet : TDataSet;
  tmpItem: TListItem;
begin
  WorkView1.FieldByName('机型代码').Data.SetString('0201');
  MainRequest.SendCommand;
  try
    tmpDataSet := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
    tmpDataSet.First;
    lvEqu.Items.Clear;
    while not tmpDataSet.Eof do
    begin
      tmpItem := lvEqu.Items.Add;
      tmpItem.Caption := tmpdataset.fieldbyname('lvol0').AsString;         //设备编号
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString);   //设备名称
      tmpItem.SubItems.Add(GetIdObjectName(5,tmpdataset.fieldbyname('lvol4').AsString));      //状态
      tmpItem.SubItems.Add(GetIdObjectName(-28,tmpdataset.fieldbyname('lserial1').AsString)); //所在区域       //所属校区
      tmpdataset.Next;
    end;
  except
  end;
end;

procedure TfaqhsetFillBusiEquInfo.Init;
begin
  inherited;
  fillEquList;
end;

procedure TfaqhsetFillBusiEquInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhsetFillBusiEquInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetFillBusiEquInfo.GridDblClick(Sender: TObject);
begin
  //inherited;

end;

function TfaqhsetFillBusiEquInfo.getBusiStr: string;
var
  i:Integer;
  ss:string;
begin
  for i := 0 to lvEqu.Items.Count-1 do
  begin
    if lvEqu.Items[i].Checked then
      ss := ss+lvequ.Items[i].Caption+',';
  end;
  Result := ss;
end;

procedure TfaqhsetFillBusiEquInfo.btnOKClick(Sender: TObject);
var
  busiSS:string;
begin
  if (Trim(cbbBusiName.Text)='')or(cbbBusiName.Text='-') then
  begin
    ShowMessage('请选择要分配的充值商户');
    Exit;
  end;
  busiSs := getBusiStr;
  if Trim(busiSS)='' then
  begin
    ShowMessage('请选择要分配的设备！');
    Exit;
  end;
  WorkView.FieldByName('设备编号').Data.SetString(getBusiStr);
  inherited;

end;

procedure TfaqhsetFillBusiEquInfo.btnDeleteClick(Sender: TObject);
var
  equId:string;
begin
  //inherited;
  if Application.MessageBox('你确定要删除该设备吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  equId := Grid.DataSource.DataSet.fieldbyname('saddr').AsString;
  WorkView.FieldByName('商户号').Data.SetInteger(0);
  WorkView.FieldByName('设备编号').Data.SetString(equId);
  DeleteRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger=0 then
    ShowMessage('删除充值商户设备成功！');
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('充值商户设备信息设置',TfaqhsetFillBusiEquInfo);

end.