unit UAGateListDelete;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, ComCtrls,
  RzListVw, RzButton, RzRadChk, RzEdit, Buttons, ADODB;

type
  TfaqhGateListDelete = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    WVEdit4: TWVEdit;
    Label4: TLabel;
    Label7: TLabel;
    cbbCustType: TWVComboBox;
    WVEdit10: TWVEdit;
    Label10: TLabel;
    Label11: TLabel;
    WVComboBox6: TWVComboBox;
    cbbFeeType: TWVComboBox;
    cbbDep: TWVComboBox;
    WVEdit2: TWVEdit;
    Label2: TLabel;
    Label5: TLabel;
    Label8: TLabel;
    Label12: TLabel;
    Label9: TLabel;
    Label6: TLabel;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    lv1: TRzListView;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    btnDelete: TBitBtn;
    chkCustUnAllot: TRzCheckBox;
    pnl1: TPanel;
    mmo1: TRzMemo;
    btn1: TSpeedButton;
    btnInfo: TBitBtn;
    SpeedButton1: TSpeedButton;
    Label14: TLabel;
    edtTable: TWVEdit;
    btnOpen: TBitBtn;
    btnIMPQuery: TBitBtn;
    btnCloseConn: TBitBtn;
    btnDelList: TBitBtn;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    dlgOpen: TOpenDialog;
    Label13: TLabel;
    WVComboBox3: TWVComboBox;
    btnErrInfo: TBitBtn;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure chkCustUnAllotClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure btnInfoClick(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure btnOpenClick(Sender: TObject);
    procedure btnIMPQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnDelListClick(Sender: TObject);
    procedure btnErrInfoClick(Sender: TObject);
  private

    { Private declarations }
    fileName:string;
    procedure fillList(wv: TWorkView);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhGateListDelete: TfaqhGateListDelete;

implementation

uses KsFrameworks, 
     KSDataDictionary,gateComm,KSClientConsts;

{$R *.DFM}

procedure TfaqhGateListDelete.Init;
begin
  inherited;
  btnInfo.Caption := 'ɾ����Ϣ';
  btnInfo.Enabled := True;
end;

procedure TfaqhGateListDelete.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhGateListDelete.btnQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  //inherited;
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  {
  tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  tmpDataSet.First;
  lv1.Items.Clear;
  while not tmpDataSet.Eof do
  begin
    tmpItem := lv1.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail2').AsString);                            //�豸����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol2').AsString);                          //�ͻ���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);                          //ѧ����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //����
    tmpItem.SubItems.Add(GetIdObjectName(84,tmpdataset.fieldbyname('sstatus1').AsString));          //״̬
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lvol3').AsString));         //�ͻ����
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol4').AsString));         //�շ����                 
    tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('sstation0').AsString));       //Ժϵ
    tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('sstation1').AsString));       //רҵ
    tmpItem.SubItems.Add(GetIdObjectName(133,tmpdataset.fieldbyname('sstat_type').AsString));       //��������
    tmpdataset.Next;
  end;
  }
  fillList(WorkView1);

  btnDelete.Enabled := True;
end;

procedure TfaqhGateListDelete.chkCustUnAllotClick(Sender: TObject);
begin
  if listViewSelectAll(lv1,chkCustUnAllot)=False then
    Exit;
end;

procedure TfaqhGateListDelete.btnDeleteClick(Sender: TObject);
var
  i:Integer;
begin
  if (checkListViewSelect(lv1)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��ɾ������Ա������');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫɾ��ѡ����Ž���Ա��Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for i := 0 to lv1.Items.Count-1 do
  begin
    if lv1.Items[i].Checked then
    begin
      WorkView.FieldByName('�Ž����').Data.SetInteger(StrToInt(lv1.Items[i].caption));
      WorkView.FieldByName('�ͻ���').Data.SetInteger(StrToInt(lv1.Items[i].SubItems[1]));
      try
        //WorkView.FieldByName('״̬').Data.SetInteger(StrToInt(lv1.Items[i].SubItems[4]));
        //WorkView.FieldByName('��ɾ��־').Data.SetInteger(StrToInt(lv1.Items[i].SubItems[6]));
        WorkView.FieldByName('ʱ����').Data.SetInteger(StrToInt(lv1.Items[i].SubItems[8]));
      except
        //WorkView.FieldByName('״̬').Data.SetInteger(0);
        //WorkView.FieldByName('��ɾ��־').Data.SetInteger(0);
        WorkView.FieldByName('ʱ����').Data.SetInteger(0);
      end;
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          mmo1.Lines.Add('ѧ����['+lv1.Items[i].SubItems[2]+']����Ϊ['+lv1.Items[i].SubItems[3]+']������ɾ��ʧ��,ʧ��ԭ��--'+e.Message);
          Continue;
        end;
      end;
      mmo1.Lines.Add(WorkView.fieldbyname('������Ϣ').Data.AsString);
    end;
  end;
  btnInfo.Enabled := True;
  Context.GetDialogSystem.ShowMessage('�Ž���Ա����ɾ���ɹ���');
end;

procedure TfaqhGateListDelete.btn1Click(Sender: TObject);
begin
  pnl1.Visible := False;

end;

procedure TfaqhGateListDelete.btnInfoClick(Sender: TObject);
begin
  pnl1.Visible := True;

end;

procedure TfaqhGateListDelete.SpeedButton1Click(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ���ɾ��ʱ��������Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  mmo1.Lines.Clear;

end;

procedure TfaqhGateListDelete.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  lv1.Items.Clear;
  while not tmpDataSet.Eof do
  begin
    tmpItem := lv1.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail2').AsString);                            //�豸����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol2').AsString);                          //�ͻ���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);                          //ѧ����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol7').AsString);           //״̬
    tmpItem.SubItems.Add(GetIdObjectName(84,tmpdataset.fieldbyname('lvol7').AsString));          //״̬               //�ͻ���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol8').AsString);           //��ɾ��־
    tmpItem.SubItems.Add(GetIdObjectName(44,tmpdataset.fieldbyname('lvol8').AsString));           //��ɾ��־
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol9').AsString);           //ʱ����
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lvol3').AsString));         //�ͻ����                 //ѧ����
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol4').AsString));         //�շ����                  //ѧ����
    tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('sstation0').AsString));       //Ժϵ
    tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('sstation1').AsString));       //רҵ
    tmpdataset.Next;
  end;
end;

procedure TfaqhGateListDelete.btnOpenClick(Sender: TObject);
begin
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    fileName := dlgOpen.FileName;
end;

procedure TfaqhGateListDelete.btnIMPQueryClick(Sender: TObject);
var
  sqlstr:string;
  i:Integer;
  stuempNo,custName:string;
begin
  //inherited;
  try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(fileName)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where ѧ����<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    try
      qrySource.Open;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('��ѯ����--'+e.Message);
        Exit;
      end;
    end;
  except
    on ex:exception do
    begin
      Context.GetDialogSystem.ShowMessage('�����ݱ�ʧ��--'+ex.message);
      Exit;
    end;
  end;
  if qrySource.RecordCount<=0 then
  begin
    Context.GetDialogSystem.ShowMessage('�򿪵�Excelû�м�¼����鿴�򿪵�·���ͱ����Ƿ���ȷ!');
    Exit;
  end;
  
  try
    qrySource.First;
    while not qrySource.Eof do
    begin
      stuempNo := Trim(qrySource.FieldByName('ѧ����').AsString);
      custName := Trim(qrySource.FieldByName('����').AsString);
      //if Trim(sCustId)='####' then
      //  Exit;
      WorkView1.FieldByName('�Ž�������').Data.SetString('');// := '';
      WorkView1.FieldByName('�Ž��豸���').Data.SetInteger(0);// := 0;
      WorkView1.FieldByName('ѧ����').Data.SetString(stuempNo);// := '';
      WorkView1.FieldByName('����').Data.SetString('');// := '';
      WorkView1.FieldByName('Ժϵ����').Data.SetString('');// := '';
      WorkView1.FieldByName('�ͻ���').Data.SetInteger(0);// 0;
      WorkView1.FieldByName('�ͻ�����').Data.SetInteger(0);// := 0;
      WorkView1.FieldByName('�շ�����').Data.SetInteger(0);// := 0;
      //WorkView1.FieldByName('ҽԺ�շѷ�ʽ').Data.SetInteger(0);// := 0;
      WorkView1.FieldByName('�༶').Data.SetString('');// := '';
      WorkView1.FieldByName('רҵ����').Data.SetString('');// := '';
      WorkView1.FieldByName('״̬').Data.SetInteger(0);// := 0;
      WorkView1.FieldByName('����Ա').DefaultValue := Context.ParamData(svOperatorNoName).AsString;
      try
        WVRequest1.SendCommand;
        if WorkView1.FieldByName('������').Data.AsInteger<>0 then
        begin
          mmo1.Lines.Add('ѧ����['+stuempNo+']����Ϊ['+custName+']�����������ѯʧ��,ʧ��ԭ��--'+WorkView1.FieldByName('������Ϣ').Data.AsString);
          qrySource.Next;
          Continue;
        end;
      except
        on e:Exception do
        begin
          mmo1.Lines.Add('ѧ����['+stuempNo+']����Ϊ['+custName+']�����������ѯʧ��,ʧ��ԭ��--'+e.Message);
          qrySource.Next;
          Continue;
        end;
      end;
      fillList(WorkView1);
      qrySource.Next;
    end;
    btnDelete.Enabled := True;
  finally
    qrySource.Recordset.Close;
    qrySource.Close;
    conSource.Connected:=false;
  end;
end;

procedure TfaqhGateListDelete.btnPrintClick(Sender: TObject);
begin
  if conSource.Connected=True then
  begin
    qrySource.Recordset.Close;
    qrySource.Close;
    conSource.Connected:=false;
  end;
end;

procedure TfaqhGateListDelete.btnDelListClick(Sender: TObject);
var
  i:Integer;
begin
  for i := lv1.Items.Count-1 downto 0 do
    lv1.Items.Delete(i);
end;

procedure TfaqhGateListDelete.btnErrInfoClick(Sender: TObject);
begin
  pnl1.Visible := True;

end;

initialization
  TUIStdClassFactory.Create('�Ž���Ա����ɾ��',TfaqhGateListDelete);

end.