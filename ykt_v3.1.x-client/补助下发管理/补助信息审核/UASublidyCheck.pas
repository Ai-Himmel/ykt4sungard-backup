unit UASublidyCheck;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, Buttons,CardDll, ComCtrls, RzListVw;

type
  TfaqhSublidyCheck = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label8: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    edtPatchNo: TWVEdit;
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    cbbType: TWVComboBox;
    Label10: TLabel;
    edtCustNo: TWVEdit;
    Label9: TLabel;
    edtCardno: TWVEdit;
    btnCheck: TBitBtn;
    Label33: TLabel;
    edtCPatchNo: TWVEdit;
    Label6: TLabel;
    edtCPwd: TWVEdit;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    lbl1: TLabel;
    cbbDept: TWVComboBox;
    Label7: TLabel;
    WVComboBox1: TWVComboBox;
    lvCustList: TRzListView;
    btnChkReturn: TBitBtn;
    chkSelect: TCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnChkReturnClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
  private

    { Private declarations }
    procedure fillList();
    function checkListViewSelect(inlv:TRzListView):Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSublidyCheck: TfaqhSublidyCheck;

implementation

uses KsFrameworks,SmartCardCommon,KSClientConsts,KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSublidyCheck.Init;
begin
  inherited;
end;

procedure TfaqhSublidyCheck.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSublidyCheck.btnQueryClick(Sender: TObject);
begin
  if Trim(edtEDate.Text)<>'' then
    if CheckInputDateFormat(edtEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�������������,��ʽ:yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����뿪ʼ����,��ʽ:yyyymmdd');
      edtBDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEDate.Text)<>'') and (Trim(edtBDate.Text)<>'') then
    if Trim(edtBDate.Text)>Trim(edtEDate.Text) then
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ�������!');
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtPatchNo.Text)='' then
    edtPatchNo.Text := '0';
  if Trim(edtCardno.Text)='' then
    edtCardno.Text := '0';
  WorkView.FieldByName('��������').Data.SetString('R');
  lvCustList.Items.Clear;
  inherited;
  fillList;
end;

procedure TfaqhSublidyCheck.btnCheckClick(Sender: TObject);
var
  operPwd,operCode:string;
begin
  if Trim(edtCPatchNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('������Ҫ��˲��������ĵ������κţ�');
    edtCPatchNo.SetFocus;
    Exit;
  end;
  if Trim(edtCPwd.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��������˲���Ա���룡');
    edtCPwd.SetFocus;
    Exit;
  end;
  operCode := Context.ParamData(svOperatorNoName).AsString;
  operPwd := encOperPwd(operCode,Trim(edtCPwd.Text));
  if Application.MessageBox('��ȷ��Ҫ���ͨ�������κŵĲ���������',PChar(Application.Title),MB_YESNO)=idno then
    Exit;
  WorkView1.FieldByName('��������').Data.SetString('C');
  WorkView1.FieldByName('�������κ�').Data.SetString(Trim(edtCPatchNo.Text));
  WorkView1.FieldByName('����').Data.SetString(operPwd);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsString='0' then
  begin
    edtCPwd.Text := '';
    Context.GetDialogSystem.ShowMessage('��˳ɹ���');
  end
  else
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
end;

procedure TfaqhSublidyCheck.fillList;
var
  tmpData:TDataSet;
  tmpItem: TListItem;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  tmpData.First;
  while not tmpData.Eof do
  begin
    try
      tmpItem := lvCustList.Items.Add;
      //
      tmpItem.Caption := '';
      //�������κ�
      tmpItem.SubItems.Add(tmpData.fieldbyname('scust_limit').AsString);
      //˳���
      tmpItem.SubItems.Add(tmpData.fieldbyname('lvol1').AsString);
      //�ͻ���
      tmpItem.SubItems.Add(tmpData.fieldbyname('lvol0').AsString);
      //ѧ����
      tmpItem.SubItems.Add(tmpData.fieldbyname('scust_auth').AsString);
      //����
      tmpItem.SubItems.Add(tmpData.fieldbyname('sall_name').AsString);
      //�������κ�
      tmpItem.SubItems.Add(tmpData.fieldbyname('lvol10').AsString);
      //������
      tmpItem.SubItems.Add(tmpData.fieldbyname('damt0').AsString);
      //״̬
      tmpItem.SubItems.Add(GetIdObjectName(76,tmpData.fieldbyname('sstatus1').AsString));
      //���״̬
      tmpItem.SubItems.Add(GetIdObjectName(160,tmpData.fieldbyname('lsafe_level2').AsString));
      //������Ϣ
      tmpItem.SubItems.Add(tmpData.fieldbyname('vsvarstr0').AsString);
      //��������
      tmpItem.SubItems.Add(tmpData.fieldbyname('sdate2').AsString);
      //����ʱ��
      tmpItem.SubItems.Add(tmpData.fieldbyname('stime2').AsString);
      //�������Ա
      tmpItem.SubItems.Add(tmpData.fieldbyname('semp_no').AsString);
    except
    end;
    
    tmpData.Next;
  end;
end;

procedure TfaqhSublidyCheck.btnChkReturnClick(Sender: TObject);
var
  operPwd,operCode:string;
  patchNo:string;
  i,sNo:Integer;
begin
  {
  if Trim(edtCPatchNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('������Ҫ��˲��������ĵ������κţ�');
    edtCPatchNo.SetFocus;
    Exit;
  end;
  }
  if checkListViewSelect(lvCustList)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ��ص���Ա������');
    Exit;
  end;
  if Trim(edtCPwd.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��������˲���Ա���룡');
    edtCPwd.SetFocus;
    Exit;
  end;
  operCode := Context.ParamData(svOperatorNoName).AsString;
  operPwd := encOperPwd(operCode,Trim(edtCPwd.Text));
  if Application.MessageBox('��ȷ��Ҫ��˴��ѡ��Ĳ���������',PChar(Application.Title),MB_YESNO)=idno then
    Exit;
  for i:=0 to lvCustList.Items.Count-1 do
  begin
    if lvCustList.Items[i].Checked then
    begin
      sNo := StrToInt(lvCustList.Items[i].SubItems[1]);
      patchNo := lvCustList.Items[i].SubItems[0];
      WorkView1.FieldByName('��������').Data.SetString('T');
      WorkView1.FieldByName('�������κ�').Data.SetString(patchNo);
      WorkView1.FieldByName('˳���').Data.SetInteger(sNo);
      WorkView1.FieldByName('����').Data.SetString(operPwd);
      WVRequest1.SendCommand;
      if WorkView1.FieldByName('������').Data.AsString<>'0' then
        Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
    end;
  end;
  edtCPwd.Text := '';
  Context.GetDialogSystem.ShowMessage('��˴�ز�����ɣ�');
end;

procedure TfaqhSublidyCheck.chkSelectClick(Sender: TObject);
var
  i: integer;
begin
  if lvCustList.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelect.Checked = True then
  begin
    for i := 0 to lvCustList.Items.Count - 1 do
    begin
      lvCustList.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvCustList.Items.Count - 1 do
    begin
      lvCustList.Items[i].Checked := False;
    end;
  end;
end;

function TfaqhSublidyCheck.checkListViewSelect(inlv: TRzListView): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i :=0  to inLv.Items.Count-1 do
    if inLv.Items[i].Checked = True then
    begin
      Result := True;
      Exit;
    end;
end;

initialization
  TUIStdClassFactory.Create('������Ϣ���',TfaqhSublidyCheck);

end.