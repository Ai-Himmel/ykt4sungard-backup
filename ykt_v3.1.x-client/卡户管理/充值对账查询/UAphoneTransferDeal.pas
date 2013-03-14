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
  WorkView.FieldByName('��������').DefaultValue := bAccountDate;
  {
  WorkView.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView.FieldByName('����').DefaultValue := 0;
  WorkView.FieldByName('�ֻ�����').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('����״̬').DefaultValue := '';
  WorkView.FieldByName('����״̬').DefaultValue := '';
  btnDeal.Caption := '���˴���';
  btnTrans.Caption := '�ֹ�����'; }
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
  tmpDataSet := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
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
    ShowMessage('���Ȳ�ѯ��Ȼ���ٽ��ж��˴���');
    Exit;
  end;
  if ifSelect=False then
  begin
    ShowMessage('����ѡ��Ҫ���ж��˴���ļ�¼��');
    Exit;
  end;
  if Application.MessageBox('��ȷ�����ж��˴�����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for i := 0 to lvSerial.Items.Count-1 do
  begin
    if lvSerial.Items[i].Checked then
    begin
      seriId := lvSerial.Items[i].Caption;
      tradeDate := lvSerial.Items[i].SubItems[3];
      cardId := lvSerial.Items[i].SubItems[1];
      operCode := Context.ParamData(svOperatorNoName).AsString;

      WorkView1.FieldByName('��������').Data.SetString(tradeDate);
      WorkView1.FieldByName('����').Data.SetInteger(StrToInt(cardId));
      WorkView1.FieldByName('������ˮ��').Data.SetInteger(StrToInt(seriId));
      WorkView1.FieldByName('����Ա').Data.SetString(operCode);

      WVRequest1.SendCommand;
      if (WorkView1.FieldByName('������').Data.AsInteger <> 0) then
        Continue;
    end;
  end;
  ShowMessage('�ƶ���ֵ���˴���ɹ���');
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
  if Application.MessageBox('��ȷ�������ֹ����˴�����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView2.FieldByName('��������').Data.SetString(FormatDateTime('yyyymmdd',dtpDate.Date));

  WVRequest2.SendCommand;
  ShowMessage('�ƶ���ֵ���˴���ɹ���');
end;

initialization
  TUIStdClassFactory.Create('�ƶ���ֵ����',TfaqhphoneTransferDeal);

end.