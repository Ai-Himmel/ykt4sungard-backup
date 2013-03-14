unit UACustPatchEdit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, RzStatus, RzPanel, ComCtrls, ADODB, Buttons,
  FilterCombos;

type
  TfaqhCustPatchEdit = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label11: TLabel;
    edtSheetName: TEdit;
    btnSelectFile: TBitBtn;
    btnImportQuery: TBitBtn;
    btnClear: TBitBtn;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    lv1: TListView;
    dlgOpen: TOpenDialog;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    chkSelect: TCheckBox;
    grp1: TGroupBox;
    chkCustType: TCheckBox;
    chkFeeType: TCheckBox;
    chkArea: TCheckBox;
    chkDept: TCheckBox;
    chkDestoryTime: TCheckBox;
    chkClass: TCheckBox;
    cbbCustType: TWVComboBox;
    cbbFeeType: TWVComboBox;
    cbbArea: TWVComboBox;
    cbbDept: TWVComboBox;
    edtClass: TWVEdit;
    edtDestoryTime: TWVEdit;
    btnPatchEdit: TBitBtn;
    ChangeRequest: TWVRequest;
    WorkView1: TWorkView;
    WVLabel2: TWVLabel;
    WVEdit2: TWVEdit;
    WVComboBox1: TWVComboBox;
    Label1: TLabel;
    WVComboBox8: TWVComboBox;
    Label8: TLabel;
    Label10: TLabel;
    WVEdit10: TWVEdit;
    Label3: TLabel;
    WVComboBox3: TWVComboBox;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    WVComboBox9: TWVComboBox;
    Label9: TLabel;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    Label13: TLabel;
    WVComboBox4: TWVComboBox;
    WVEdit4: TWVEdit;
    Label4: TLabel;
    Label6: TLabel;
    cbbQDept: TWVComboBox;
    WVLabel3: TWVLabel;
    WVEdit3: TWVEdit;
    chkFilter: TCheckBox;
    cbb1: TKSFilterComboBox;
    cbb2: TKSFilterComboBox;
    chkSpec: TCheckBox;
    cbbSpec: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnSelectFileClick(Sender: TObject);
    procedure btnImportQueryClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
    procedure btnPatchEditClick(Sender: TObject);
    procedure cbb1FilterItems(Sender: TObject);
    procedure cbb2FilterItems(Sender: TObject);
  private

    { Private declarations }
    Fdept,Fdept2:TStringList;
    FDspDept,FDspDept2:TStringList;
    sFileName:string;
    procedure fillList(wv:TWorkView);
    function findIndexLV(inLv:TListView;iId:string): Boolean;
    procedure checkSelectAll;
    function getCbbValue(cbbText:TWVComboBox):string ;
    function changeProj: Boolean;
    function changeCust: Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCustPatchEdit: TfaqhCustPatchEdit;

implementation

uses KsFrameworks,KSDataDictionary, 
  SmartCardCommon;

{$R *.DFM}

procedure TfaqhCustPatchEdit.Init;
begin
  inherited;
  edtDestoryTime.Text := FormatDateTime('yyyymmdd',(Date+365));
  WVComboBox1.ItemIndex := 0;
  WVComboBox3.ItemIndex := 0;
  WVComboBox4.ItemIndex := 0;
  fillData2FilterCbb(Fdept,FDspDept,cbbQDept);
  fillData2FilterCbb(Fdept2,FDspDept2,cbbDept);
end;

procedure TfaqhCustPatchEdit.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCustPatchEdit.btnQueryClick(Sender: TObject);
var
  deptNo:string;
begin
  if Application.MessageBox('��ѯʱ���ָ�����������������ٶȻ��������ȷ����ʼ��ѯ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  try
    deptNo := Trim(Copy(cbb1.Text,1,Pos('-',cbb1.Text)-1));
  except

  end;

  WorkView.FieldByName('��ϵ�˵�λ��').Data.SetString(deptNo);
  WorkView.FieldByName('��������').Data.SetString('R');
  inherited;
  fillList(WorkView);
end;

procedure TfaqhCustPatchEdit.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if chkFilter.Checked then
    begin
      if findIndexLV(lv1,tmpdataset.fieldbyname('lvol1').AsString)=True then
      begin
        tmpdataset.Next;
        Continue;
      end;
    end;
    tmpItem := lv1.Items.Add;
    //�ͻ���
    tmpItem.Caption := tmpdataset.fieldbyname('lvol1').AsString;
    //ѧ����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth2').AsString);
    //У������
    tmpItem.SubItems.Add(GetIdObjectName(-27,tmpdataset.fieldbyname('sbranch_code0').AsString));
    //�ͻ�����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname').AsString);
    //�Ա�����
    tmpItem.SubItems.Add(GetIdObjectName(39,tmpdataset.fieldbyname('smarket_code2').AsString));
    //�ͻ����
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lvol3').AsString));
    //�շ����
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol5').AsString));
    //����
    tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('scert_no').AsString));
    //רҵ
    tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('scust_no2').AsString));
    //�༶
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scard1').AsString);
    //֤������
    tmpItem.SubItems.Add(GetIdObjectName(87,tmpdataset.fieldbyname('smarket_code').AsString));
    //֤������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);
    //����
    tmpItem.SubItems.Add(GetIdObjectName(2001,tmpdataset.fieldbyname('scust_type2').AsString));
    //Ԥ��ע��ʱ��
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sdate2').AsString);
    //��ϵ�绰
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone').AsString);
    //��ϵ��ַ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scusttypes').AsString);

    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '��ѯ��'+inttostr(lv1.Items.Count)+'����¼';
end;

function TfaqhCustPatchEdit.findIndexLV(inLv: TListView;
  iId: string): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to inLv.Items.Count-1 do
  begin
    if inLv.Items[i].Caption = iId then
    begin
      Result := True;
      Exit;
    end;
  end;
end;

procedure TfaqhCustPatchEdit.btnSelectFileClick(Sender: TObject);
begin
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  try
    if dlgOpen.Execute then
    begin
      sFileName := dlgOpen.FileName;
      RzStatusPane1.Caption := sFileName;
      //btnImportQuery.Enabled := True;
    end;
  except
    Context.GetDialogSystem.ShowMessage('��Excel�ļ�ʧ�ܣ������ļ��Ƿ���ڻ��ڴ�״̬��');
  end;
end;

procedure TfaqhCustPatchEdit.btnImportQueryClick(Sender: TObject);
var
  sqlstr:string;
  sCustId:string;
  sempNo:string;
begin
  try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(sFileName)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtSheetName.Text)+'$] where 1>0';
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    qrySource.Open;
  except
    Context.GetDialogSystem.ShowMessage('�����ݱ�ʧ�ܣ�����򿪵�Excel�ļ��Ƿ���ȷ��');
    Exit;
  end;
  if qrySource.RecordCount<=0 then
  begin
    Context.GetDialogSystem.ShowMessage('û�м�¼������򿪵�Excel�Ƿ���ȷ��');
    Exit;
  end;
  try
  qrySource.First;
  while not qrySource.Eof do
  begin
    sCustId := qrySource.FieldByName('�ͻ���').AsString;
    sempNo := qrySource.FieldByName('ѧ����').AsString;
    if Trim(sCustId)='####' then
      Break;
      {
    if (Trim(sCustId)='')then
    begin
      qrySource.Next;
      Continue;
    end;
    }
    if Trim(sCustId)='' then
      sCustId := '0';
    WorkView.FieldByName('�ͻ���').Data.SetInteger(StrToInt(sCustId));
    WorkView.FieldByName('�ͻ����').DefaultValue := 0;
    WorkView.FieldByName('�շ����').DefaultValue := 0;
    WorkView.FieldByName('�ͻ�״̬').DefaultValue := 0;
    //WorkView.FieldByName('�ͻ���������').DefaultValue := '';
    //WorkView.FieldByName('�ͻ�����').DefaultValue := '';
    WorkView.FieldByName('��ϵ��ѧ����').Data.SetString(sempNo);
    //WorkView.FieldByName('��ϵ�˵�λ��').DefaultValue := '';
    //WorkView.FieldByName('��ϵ���Ա�').DefaultValue := '';
    WorkView.FieldByName('��ϵ������').DefaultValue := 0;
    //WorkView.FieldByName('��ϵ�����֤��').DefaultValue := '';
    //WorkView.FieldByName('��ϵ�绰').DefaultValue := '';
    WorkView.FieldByName('��������').Data.SetString('R');
    MainRequest.SendCommand;

    if WorkView.FieldByName('������').Data.AsInteger<>0 then
    begin
      qrySource.Next;
      Continue;
    end;
    fillList(WorkView);
    qrySource.Next;
  end;
  finally
    qrySource.Recordset.Close;
    qrySource.Close;
    conSource.Connected:=false;
    //btnImportQuery.Enabled := False;
  end;
end;

procedure TfaqhCustPatchEdit.btnClearClick(Sender: TObject);
var
  i:Integer;
begin
  if Application.MessageBox('��ȷ��Ҫ����б���Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for i := lv1.Items.Count-1 downto 0 do
    lv1.Items.Delete(i);
end;

procedure TfaqhCustPatchEdit.checkSelectAll;
var
  i:Integer;
begin
  if chkSelect.Checked then
    for i := 0 to lv1.Items.Count-1 do
      lv1.Items[i].Checked := True
  else
    for i := 0 to lv1.Items.Count-1 do
      lv1.Items[i].Checked := False;
end;

procedure TfaqhCustPatchEdit.chkSelectClick(Sender: TObject);
begin
  checkSelectAll;
end;

procedure TfaqhCustPatchEdit.btnPatchEditClick(Sender: TObject);
var
  i:Integer;
  scustType,sfeeType,sArea,sdept,sSpec:string;
begin
  if changeCust=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ�޸ĵ���Ա�����б�Ȼ���ٲ�����');
    Exit;
  end;
  if changeProj=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ�����޸ĵ���Ŀ��Ȼ���ٲ�����');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ�����޸�ѡ��Ŀͻ���Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if chkDestoryTime.Checked then
    if Trim(edtDestoryTime.Text)<>'' then
      if CheckInputDateFormat(edtDestoryTime.Text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('��������Ч�����ڣ���ʽ(yyyymmdd)!');
        Exit;
      end;
  scustType := getCbbValue(cbbCustType);
  sfeeType := getCbbValue(cbbFeeType);
  sArea := getCbbValue(cbbArea);
  sdept := Trim(Copy(cbb2.Text,0,Pos('-',cbb2.Text)-1));
  sSpec := Trim(Copy(cbbSpec.Text,0,Pos('-',cbbSpec.Text)-1));
  for i := 0 to lv1.Items.Count-1 do
  begin
    if lv1.Items[i].Checked then
    begin

      WorkView1.FieldByName('��������').Data.SetString('U');
      WorkView1.FieldByName('������־').Data.SetString('1');
      WorkView1.FieldByName('�ͻ���').Data.SetInteger(StrToInt(lv1.Items[i].Caption));
      if chkCustType.Checked then
        WorkView1.FieldByName('�ͻ����').Data.SetInteger(StrToInt(scustType))
      else
        WorkView1.FieldByName('�ͻ����').Data.SetInteger(0);
      if chkFeeType.Checked then
        WorkView1.FieldByName('�շ����').Data.SetInteger(StrToInt(sfeeType))
      else
        WorkView1.FieldByName('�շ����').Data.SetInteger(0);
      if chkArea.Checked then
        WorkView1.FieldByName('�ͻ���������').Data.SetString(sArea);
      if chkDept.Checked then
        WorkView1.FieldByName('��ϵ�˰༶���ź�').Data.SetString(sdept);
      if chkDestoryTime.Checked then
        WorkView1.FieldByName('Ԥ��ע��ʱ��').Data.SetString(edtDestoryTime.Text);
      if chkClass.Checked then
        WorkView1.FieldByName('��ϵ�˰༶��������').Data.SetString(edtClass.Text);
      if chkSpec.Checked then
        WorkView1.FieldByName('רҵ').Data.SetString(sSpec);
      ChangeRequest.SendCommand;
    end;
  end;
  Context.GetDialogSystem.ShowMessage('�ͻ���Ϣ�����޸ĳɹ���');
end;

function TfaqhCustPatchEdit.getCbbValue(cbbText: TWVComboBox): string;
begin
  Result := Copy(cbbText.Text,0,Pos('-',cbbText.Text)-1);
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhCustPatchEdit.changeProj�޸���Ŀ�жϣ����û��ѡ�񷵻�false,ѡ�з���true
  ����:      hanjiwei
  ����:      2008.11.21
  ����:      ��
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function TfaqhCustPatchEdit.changeProj: Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to grp1.ControlCount-1 do
  begin
    if grp1.Controls[i] is TCheckBox then
      if TCheckBox(grp1.Controls[i]).Checked then
      begin
        Result := True;
        Exit;
      end;
  end;

end;

{-------------------------------------------------------------------------------
  ������:    TfaqhCustPatchEdit.changeCustû��ѡ����Ա����false�����򷵻�true
  ����:      hanjiwei
  ����:      2008.11.21
  ����:      ��
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function TfaqhCustPatchEdit.changeCust: Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to lv1.Items.Count-1 do
  begin
    if lv1.Items[i].Checked then
    begin
      Result := True;
      Exit;
    end;
  end;
end;

procedure TfaqhCustPatchEdit.cbb1FilterItems(Sender: TObject);
begin
  cbbFilterItem( Fdept,FDspDept,sender);

end;

procedure TfaqhCustPatchEdit.cbb2FilterItems(Sender: TObject);
begin
    cbbFilterItem( Fdept2,FDspDept2,sender);


end;

initialization
  TUIStdClassFactory.Create('�ͻ���Ϣ�����޸�', TfaqhCustPatchEdit);

end.
