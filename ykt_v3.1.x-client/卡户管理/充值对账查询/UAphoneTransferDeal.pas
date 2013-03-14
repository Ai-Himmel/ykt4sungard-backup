unit UAphoneTransferDeal;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, ComCtrls,
  RzListVw, Buttons;

type
  TfaqhphoneTransferDeal = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    WVEdit1: TWVEdit;
    edtCustNo: TWVEdit;
    edtCardNo: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    cbbCustType: TWVComboBox;
    WVComboBox1: TWVComboBox;
    lvSerial: TRzListView;
    chkSelectAll: TCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    btnDeal: TImageButton;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    GroupBox1: TGroupBox;
    Label8: TLabel;
    dtpDate: TDateTimePicker;
    btnTrans: TImageButton;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
    procedure btnDealClick(Sender: TObject);
    procedure btnTransClick(Sender: TObject);
  private

    { Private declarations }
    procedure listViewSelectAll(inListView:TRzListView;chkBox:TCheckBox);
    function ifSelect:Boolean ;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhphoneTransferDeal: TfaqhphoneTransferDeal;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhphoneTransferDeal.Init;
begin
  inherited;
  WorkView.FieldByName('交易日期').DefaultValue := bAccountDate;
  {
  WorkView.FieldByName('客户号').DefaultValue := 0;
  WorkView.FieldByName('卡号').DefaultValue := 0;
  WorkView.FieldByName('手机号码').DefaultValue := '';
  WorkView.FieldByName('姓名').DefaultValue := '';
  WorkView.FieldByName('对账状态').DefaultValue := '';
  WorkView.FieldByName('处理状态').DefaultValue := '';
  btnDeal.Caption := '对账处理';
  btnTrans.Caption := '手工对账'; }
  WorkView.Reset; 
  dtpDate.Date := StrToDate(Copy(bAccountDate,1,4)+'-'+Copy(bAccountDate,5,2)+'-'+Copy(bAccountDate,7,2));
end;

procedure TfaqhphoneTransferDeal.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhphoneTransferDeal.btnQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  lvSerial.Items.Clear;
  inherited;
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvSerial.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lserial0').asstring;
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sorder0').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('stime0').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone').AsString);
    tmpItem.SubItems.Add(GetIdObjectName(93,tmpdataset.fieldbyname('sstatus1').AsString));
    tmpItem.SubItems.Add(GetIdObjectName(94,tmpdataset.fieldbyname('sstatus2').AsString));
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_limit').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sorder1').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('stime1').AsString);
    tmpdataset.Next;
  end;
end;

procedure TfaqhphoneTransferDeal.listViewSelectAll(inListView:TRzListView;chkBox:TCheckBox);
var
  i: integer;
begin
  if inListView.Items.Count = 0 then
    Exit;
  if chkBox.Checked = True then
  begin
    for i := 0 to inListView.Items.Count - 1 do
    begin
      inListView.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to inListView.Items.Count - 1 do
    begin
      inListView.Items[i].Checked := False;
    end;
  end;
end;

procedure TfaqhphoneTransferDeal.chkSelectAllClick(Sender: TObject);
begin
  listViewSelectAll(lvSerial,chkSelectAll);

end;

procedure TfaqhphoneTransferDeal.btnDealClick(Sender: TObject);
var
  tradeDate:string;
  seriId:string;
  cardId:string;
  operCode:string;
  i:Integer;
begin
  if lvSerial.Items.Count = 0 then
  begin
    ShowMessage('请先查询，然后再进行对账处理！');
    Exit;
  end;
  if ifSelect=False then
  begin
    ShowMessage('请先选择要进行对账处理的记录！');
    Exit;
  end;
  if Application.MessageBox('你确定进行对账处理吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for i := 0 to lvSerial.Items.Count-1 do
  begin
    if lvSerial.Items[i].Checked then
    begin
      seriId := lvSerial.Items[i].Caption;
      tradeDate := lvSerial.Items[i].SubItems[3];
      cardId := lvSerial.Items[i].SubItems[1];
      operCode := Context.ParamData(svOperatorNoName).AsString;

      WorkView1.FieldByName('交易日期').Data.SetString(tradeDate);
      WorkView1.FieldByName('卡号').Data.SetInteger(StrToInt(cardId));
      WorkView1.FieldByName('交易流水号').Data.SetInteger(StrToInt(seriId));
      WorkView1.FieldByName('操作员').Data.SetString(operCode);

      WVRequest1.SendCommand;
      if (WorkView1.FieldByName('返回码').Data.AsInteger <> 0) then
        Continue;
    end;
  end;
  ShowMessage('移动充值对账处理成功！');
end;

function TfaqhphoneTransferDeal.ifSelect: Boolean;
var
  i:Integer;
begin
  Result := False;
  for i :=0  to lvSerial.Items.Count-1 do
  begin
    if lvSerial.Items[i].Checked then
      Result := True;
  end;
end;

procedure TfaqhphoneTransferDeal.btnTransClick(Sender: TObject);
begin
  if Application.MessageBox('你确定进行手工对账处理吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView2.FieldByName('对账日期').Data.SetString(FormatDateTime('yyyymmdd',dtpDate.Date));

  WVRequest2.SendCommand;
  ShowMessage('移动充值对账处理成功！');
end;

initialization
  TUIStdClassFactory.Create('移动充值对账',TfaqhphoneTransferDeal);

end.