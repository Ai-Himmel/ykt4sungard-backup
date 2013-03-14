unit UAallotCustGate;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzTabs, ComCtrls, RzListVw,
  RzPanel, RzSplit, UIncrementComboBox, Buttons, RzEdit, ADODB, RzButton,
  RzRadChk, ImgList;

type
  TfaqhallotCustGate = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    rzpc1: TRzPageControl;
    rztsCust: TRzTabSheet;
    rztsHoliday: TRzTabSheet;
    rztsGateGroup: TRzTabSheet;
    rztsOk: TRzTabSheet;
    pnl1: TPanel;
    btnPre: TBitBtn;
    btnNext: TBitBtn;
    btnFinish: TBitBtn;
    rzszpnl1: TRzSizePanel;
    rzszpnl2: TRzSizePanel;
    lvCust: TRzListView;
    lvCustUnAllot: TRzListView;
    pnl2: TPanel;
    Label6: TLabel;
    WVComboBox6: TWVComboBox;
    WVComboBox3: TWVComboBox;
    Label3: TLabel;
    WVEdit10: TWVEdit;
    Label10: TLabel;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    Label1: TLabel;
    WVComboBox1: TWVComboBox;
    edtCustNo: TWVEdit;
    WVLabel2: TWVLabel;
    Label4: TLabel;
    WVEdit4: TWVEdit;
    pnl3: TPanel;
    rztsGate: TRzTabSheet;
    Panel3: TPanel;
    btnSelect: TSpeedButton;
    Panel6: TPanel;
    SpeedButton2: TSpeedButton;
    Panel7: TPanel;
    pnl4: TPanel;
    pnl5: TPanel;
    Panel14: TPanel;
    Label17: TLabel;
    WVEdit7: TWVEdit;
    lvHoliday: TRzListView;
    Panel15: TPanel;
    Panel16: TPanel;
    Label19: TLabel;
    WVEdit8: TWVEdit;
    lvWeek: TRzListView;
    Panel17: TPanel;
    btnCustQuery: TBitBtn;
    SpeedButton8: TSpeedButton;
    SpeedButton9: TSpeedButton;
    btnImportQuery: TSpeedButton;
    SpeedButton11: TSpeedButton;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    WVRequest3: TWVRequest;
    WorkView3: TWorkView;
    WVRequest4: TWVRequest;
    WorkView4: TWorkView;
    btnHolidayQuery: TBitBtn;
    btnWeekQuery: TBitBtn;
    WVRequest5: TWVRequest;
    WorkView5: TWorkView;
    Label20: TLabel;
    lblHolidayID: TLabel;
    lblHolidayName: TLabel;
    lblWeekName: TLabel;
    lblWeekId: TLabel;
    Label23: TLabel;
    pnl6: TPanel;
    mmoError: TRzMemo;
    dlgOpen: TOpenDialog;
    qrySource: TADOQuery;
    conSource: TADOConnection;
    edtSheet: TEdit;
    lbl1: TLabel;
    chkCustUnAllot: TRzCheckBox;
    btnClear: TSpeedButton;
    btnSaveAs: TSpeedButton;
    dlgSaveError: TSaveDialog;
    btnInit: TBitBtn;
    btnClearSele: TSpeedButton;
    Panel9: TPanel;
    Label8: TLabel;
    WVEdit9: TWVEdit;
    btnGroupQuery: TBitBtn;
    lvGateGroup: TRzListView;
    Panel18: TPanel;
    chkGateGroup: TRzCheckBox;
    Panel11: TPanel;
    Label7: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label18: TLabel;
    WVEdit3: TWVEdit;
    WVComboBox5: TWVComboBox;
    WVComboBox7: TWVComboBox;
    cbbScode: TWVComboBox;
    WVComboBox8: TWVComboBox;
    WVComboBox9: TWVComboBox;
    WVEdit6: TWVEdit;
    btnEquQuery: TBitBtn;
    Panel12: TPanel;
    chkGateUnAllot: TRzCheckBox;
    lvGate: TRzListView;
    il1: TImageList;
    Label9: TLabel;
    Label13: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    SpeedButton1: TSpeedButton;
    pnlImportError: TPanel;
    mmoImportError: TRzMemo;
    SpeedButton3: TSpeedButton;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnPreClick(Sender: TObject);
    procedure btnNextClick(Sender: TObject);
    procedure SpeedButton8Click(Sender: TObject);
    procedure btnSelectClick(Sender: TObject);
    procedure btnCustQueryClick(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
    procedure SpeedButton11Click(Sender: TObject);
    procedure btnEquQueryClick(Sender: TObject);
    procedure btnGroupQueryClick(Sender: TObject);
    procedure btnHolidayQueryClick(Sender: TObject);
    procedure btnWeekQueryClick(Sender: TObject);
    procedure lvHolidayChange(Sender: TObject; Item: TListItem;
      Change: TItemChange);
    procedure lvWeekChange(Sender: TObject; Item: TListItem;
      Change: TItemChange);
    procedure SpeedButton9Click(Sender: TObject);
    procedure btnImportQueryClick(Sender: TObject);
    procedure chkCustUnAllotClick(Sender: TObject);
    procedure btnFinishClick(Sender: TObject);
    procedure btnSaveAsClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure btnInitClick(Sender: TObject);
    procedure chkGateUnAllotClick(Sender: TObject);
    procedure btnClearSeleClick(Sender: TObject);
    procedure chkGateGroupClick(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton3Click(Sender: TObject);
  private

    { Private declarations }
    iSelect:Integer;
    sBtn:string;
    sFileName:string;
    procedure selectRzts;
    function findIndexLV(inLv:TRzListView;iId:string): Boolean;
    function addListToLv(sourLv,destLv:TRzListView): Boolean;
    function delListFromLo(destLv:TRzListView): Boolean;
    procedure clearListView(inLv:TRzListView);
    procedure allotFinish;
    function ifAddCondition(pnl:TPanel):Boolean ;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhallotCustGate: TfaqhallotCustGate;

implementation

uses KsFrameworks,KSDataDictionary, gateComm,TypInfo, DBAIntf;
     
{$R *.DFM}

procedure TfaqhallotCustGate.Init;
begin
  inherited;
  iSelect := 1;
  sBtn := 'next';
  selectRzts;
  mmoError.Lines.Clear;
end;

procedure TfaqhallotCustGate.selectRzts;
begin
  case iSelect of
    1:
      begin
        rzpc1.ActivePage:=rztsCust;
        rztsCust.TabEnabled := True;
        rztsGateGroup.TabEnabled := False;
        rztsGate.TabEnabled := False;
        rztsHoliday.TabEnabled := False;
        rztsOk.TabEnabled := False;
        btnNext.Enabled := True;
        btnPre.Enabled := False;
        btnFinish.Enabled := False;
        btnInit.Enabled := False;
      end;
    2:
      begin
        rzpc1.ActivePage:=rztsGateGroup;
        rztsCust.TabEnabled := False;
        rztsGateGroup.TabEnabled := True;
        rztsGate.TabEnabled := False;
        rztsHoliday.TabEnabled := False;
        rztsOk.TabEnabled := False;
        btnNext.Enabled := True;
        btnPre.Enabled := True;
        btnFinish.Enabled := False;
        btnInit.Enabled := False;
      end;
    3:
      begin
        rzpc1.ActivePage:=rztsGate;
        rztsCust.TabEnabled := False;
        rztsGateGroup.TabEnabled := False;
        rztsGate.TabEnabled := True;
        rztsHoliday.TabEnabled := False;
        rztsOk.TabEnabled := False;
        btnNext.Enabled := True;
        btnPre.Enabled := True;
        btnFinish.Enabled := False;
        btnInit.Enabled := False;
      end;
    4:
      begin
        rzpc1.ActivePage:=rztsHoliday;
        rztsCust.TabEnabled := False;
        rztsGateGroup.TabEnabled := False;
        rztsGate.TabEnabled := False;
        rztsHoliday.TabEnabled := True;
        rztsOk.TabEnabled := False;
        btnNext.Enabled := True;
        btnPre.Enabled := True;
        btnFinish.Enabled := False;
        btnInit.Enabled := False;
      end;
    5:
      begin
        rzpc1.ActivePage:=rztsOk;
        rztsCust.TabEnabled := False;
        rztsGateGroup.TabEnabled := False;
        rztsGate.TabEnabled := False;
        rztsHoliday.TabEnabled := False;
        rztsOk.TabEnabled := True;
        btnNext.Enabled := False;
        btnPre.Enabled := True;
        btnFinish.Enabled := True;
        btnInit.Enabled := False;
      end;
    6:
      begin
        rzpc1.ActivePage:=rztsOk;
        rztsCust.TabEnabled := False;
        rztsGateGroup.TabEnabled := False;
        rztsGate.TabEnabled := False;
        rztsHoliday.TabEnabled := False;
        rztsOk.TabEnabled := True;
        btnNext.Enabled := False;
        btnPre.Enabled := False;
        btnFinish.Enabled := False;
        btnInit.Enabled := True;
      end;
  end;
        
end;

procedure TfaqhallotCustGate.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhallotCustGate.btnPreClick(Sender: TObject);
begin
  if iSelect>0 then
    iSelect := iSelect - 1;
  selectRzts;
end;

procedure TfaqhallotCustGate.btnNextClick(Sender: TObject);
begin
  if iSelect<5 then
    iSelect := iSelect +1;
  selectRzts;

end;

{-------------------------------------------------------------------------------
  ������:    TfaqhallotCustGate.findIndexLV������listview���Ƿ���ڼ�¼�����ڷ���true
  ����:      hanjiwei
  ����:      2007.04.09
  ����:      inLv: TRzListView; iId: Integer
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function TfaqhallotCustGate.findIndexLV(inLv: TRzListView;iId: string): Boolean;
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

function TfaqhallotCustGate.addListToLv(sourLv,destLv: TRzListView): Boolean;
var
  col,i:Integer;
  tmpItem: TListItem;
begin
  for i := 0 to sourLv.Items.Count-1 do
  begin
    //�����Ƿ���ڣ������������
    if sourLv.Items[i].Checked=True then
    begin
      if findIndexLV(destLv,sourLv.Items[i].Caption)=True then
        Continue;
      tmpItem := destLv.Items.Add;
      tmpItem.Caption := sourLv.Items[i].Caption;
      for col := 0 to sourLv.Columns.Count-2 do
      begin
        tmpItem.SubItems.Add(sourLv.Items[i].SubItems[col]);
      end;
    end;
  end;
end;

function TfaqhallotCustGate.delListFromLo(destLv: TRzListView): Boolean;
var
  i:Integer;
begin
  if Application.MessageBox('��ȷ��Ҫɾ��ѡ����б���Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for i := destLv.Items.Count-1 downto 0 do
  begin
    if destLv.Items[i].Selected=True then
      destLv.Items.Delete(i);
  end;
end;

procedure TfaqhallotCustGate.SpeedButton8Click(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ����б���Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  clearListView(lvCustUnAllot);
end;

procedure TfaqhallotCustGate.clearListView(inLv: TRzListView);
var
  i:Integer;
begin
  for i := inLv.Items.Count-1 downto 0 do
    inLv.Items.Delete(i);
end;

procedure TfaqhallotCustGate.btnSelectClick(Sender: TObject);
begin
  if checkListViewSelect(lvCustUnAllot)=False then
  begin
    ShowMessage('����ѡ��Ҫ�������Ա��');
    Exit;
  end;
  addListToLv(lvCustUnAllot,lvCust);

end;

procedure TfaqhallotCustGate.btnCustQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;

begin
  if (ifAddCondition(pnl2)=False) and (edtCustNo.Text='0') then
    if Application.MessageBox('����������κ�������ѯ��ϵͳ�����������ȷ������������ѯ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
      Exit;
  WVRequest1.SendCommand;
  tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  if WorkView1.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if findIndexLV(lvCustUnAllot,tmpdataset.fieldbyname('lvol1').AsString)=True then
    begin
      tmpdataset.Next;
      Continue;
    end;
    tmpItem := lvCustUnAllot.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol1').AsString;                                //�ͻ���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth2').AsString);                       //ѧ����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname').AsString);                             //����
    tmpItem.SubItems.Add(GetIdObjectName(-27,tmpdataset.fieldbyname('sbranch_code0').AsString));        //����У��
    tmpdataset.Next;
  end;
end;

procedure TfaqhallotCustGate.SpeedButton2Click(Sender: TObject);
begin
  delListFromLo(lvCust);
end;

procedure TfaqhallotCustGate.SpeedButton11Click(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ����б���Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  clearListView(lvCust);
end;

procedure TfaqhallotCustGate.btnEquQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
  sCode:string;
begin
  //lvGate.Items.Clear;
  sCode := Copy(cbbScode.Text,1,Pos('-',cbbScode.Text)-1);
  WorkView2.FieldByName('���ʹ���').Data.SetString(sCode);
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView2.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView2.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if findIndexLV(lvGate,tmpdataset.fieldbyname('lvol0').asstring)=True then
    begin
      tmpDataSet.Next;
      Continue;
    end;
    tmpItem := lvGate.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString);                            //�豸����
    //tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);                          //�豸���
    //tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdataset.fieldbyname('lserial0').AsString));       //������ϵͳ
    //tmpItem.SubItems.Add(GetIdObjectName(-28,tmpdataset.fieldbyname('lserial1').AsString));       //��������
    tmpdataset.Next;
  end;
end;

procedure TfaqhallotCustGate.btnGroupQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  WVRequest3.SendCommand;
  if WorkView3.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView3.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView3.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if findIndexLV(lvGateGroup,tmpdataset.fieldbyname('lvol0').asstring)=True then
    begin
      tmpDataSet.Next;
      Continue;
    end;
    tmpItem := lvGateGroup.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //�豸����
    tmpdataset.Next;
  end;
end;

procedure TfaqhallotCustGate.btnHolidayQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  lvHoliday.Items.Clear;
  WorkView4.FieldByName('��������').Data.SetString('R');
  WVRequest4.SendCommand;
  if WorkView4.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView4.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView4.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvHoliday.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //�豸����
    tmpdataset.Next;
  end;
end;

procedure TfaqhallotCustGate.btnWeekQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  lvWeek.Items.Clear;
  WorkView5.FieldByName('��������').Data.SetString('R');
  WVRequest5.SendCommand;
  if WorkView5.FieldByName('������').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView5.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  tmpDataSet := TDataSet(WorkView5.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvWeek.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //�豸��ʶ
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //�豸����
    tmpdataset.Next;
  end;
end;

procedure TfaqhallotCustGate.lvHolidayChange(Sender: TObject;
  Item: TListItem; Change: TItemChange);
var
  i:Integer;
begin
  i:=lvHoliday.Items.IndexOf(lvHoliday.Selected);
  if i<0 then
    Exit;
  lblholidayId.Caption := lvHoliday.Items[i].Caption;
  lblHolidayName.Caption := lvHoliday.Items[i].SubItems[0];
end;

procedure TfaqhallotCustGate.lvWeekChange(Sender: TObject; Item: TListItem;
  Change: TItemChange);
var
  i:Integer;
begin
  i:=lvWeek.Items.IndexOf(lvWeek.Selected);
  if i<0 then
    Exit;
  lblWeekId.Caption := lvWeek.Items[i].Caption;
  lblWeekName.Caption := lvWeek.Items[i].SubItems[0];
end;

procedure TfaqhallotCustGate.SpeedButton9Click(Sender: TObject);
begin
  dlgOpen.Title := '��ѡ����Ӧ��Excel�ļ�';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  try
    if dlgOpen.Execute then
    begin
      sFileName := dlgOpen.FileName;
      //btnImportQuery.Enabled := True;
    end;
  except
    ShowMessage('��Excel�ļ�ʧ�ܣ������ļ��Ƿ���ڻ��ڴ�״̬��');
  end;
end;

procedure TfaqhallotCustGate.btnImportQueryClick(Sender: TObject);
var
  sqlstr:string;
  sStuEmpNo,sArea,sCustId,sName:string;
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(sFileName)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtSheet.Text)+'$] where 1>0';
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    qrySource.Open;
  except
    ShowMessage('�����ݱ�ʧ�ܣ�����򿪵�Excel�ļ��Ƿ���ȷ��');
    Exit;
  end;
  if qrySource.RecordCount<=0 then
  begin
    ShowMessage('û�м�¼������򿪵�Excel�Ƿ���ȷ��');
    Exit;
  end;
  try
  qrySource.First;
  while not qrySource.Eof do
  begin
    sStuEmpNo := qrySource.FieldByName('ѧ/����').AsString;
    sArea := qrySource.FieldByName('��������').AsString;
    sCustId := qrySource.FieldByName('�ͻ���').AsString;
    sName := qrySource.FieldByName('����').AsString;
    if Trim(sStuEmpNo)='####' then
      Break;
    if (Trim(sStuEmpNo)='') and (Trim(sCustId)='') then
    begin
      mmoImportError.Lines.Add('����Ϊ��'+sname+'����Ա�����ѯʧ�ܣ�');
      qrySource.Next;
      Continue;
    end;
    if Trim(sCustId)='' then
      sCustId := '0';
    WorkView1.FieldByName('��ϵ��ѧ����').Data.SetString(sStuEmpNo);
    WorkView1.FieldByName('�ͻ���������').Data.SetString(sArea);
    WorkView1.FieldByName('�ͻ���').Data.SetInteger(StrToInt(sCustId));
    WorkView1.FieldByName('�ͻ����').Data.SetInteger(0);
    WorkView1.FieldByName('�շ����').Data.SetInteger(0);
    //WorkView1.FieldByName('�ͻ�״̬').Data.SetInteger(0);
    //WorkView1.FieldByName('��ϵ������').Data.SetInteger(0);
    WVRequest1.SendCommand;

    if WorkView1.FieldByName('������').Data.AsInteger<>0 then
    begin
      mmoImportError.Lines.Add(WorkView1.FieldByName('������Ϣ').Data.AsString);
      qrySource.Next;
      Continue;
    end;
    tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
    tmpdataset.First;
    while not tmpdataset.eof do
    begin
      if findIndexLV(lvCustUnAllot,tmpdataset.fieldbyname('lvol1').AsString)=True then
      begin
        tmpdataset.Next;
        Continue;
      end;
      tmpItem := lvCustUnAllot.Items.Add;
      tmpItem.Caption := tmpdataset.fieldbyname('lvol1').AsString;                                //�ͻ���
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth2').AsString);                        //ѧ����
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);                             //����
      tmpItem.SubItems.Add(GetIdObjectName(-27,tmpdataset.fieldbyname('sbranch_code0').AsString));        //����У��
      tmpdataset.Next;
    end;
    qrySource.Next;
  end;
  finally
    qrySource.Recordset.Close;
    qrySource.Close;
    conSource.Connected:=false;
    //btnImportQuery.Enabled := False;
  end;
end;

procedure TfaqhallotCustGate.chkCustUnAllotClick(Sender: TObject);
begin
  if listViewSelectAll(lvCustUnAllot,chkCustUnAllot)=False then
    Exit;
end;

procedure TfaqhallotCustGate.btnFinishClick(Sender: TObject);
var
  icust,iGateGroup,iGate:Integer;
  i,k:Integer;
begin
  icust := lvCust.Items.Count;
  iGate := lvGate.Items.Count;
  iGateGroup := lvGateGroup.Items.Count;
  if icust=0 then
  begin
    ShowMessage('��ѡ��Ҫ�·�����Ա�����б�');
    Exit;
  end;
  if (checkListViewSelect(lvGateGroup)=False) and (checkListViewSelect(lvGate)=False) then
  begin
    ShowMessage('��ѡ��Ҫ�·����Ž�����Ž����б�');
    Exit;
  end;

  if Trim(lblWeekId.Caption)='' then
  begin
    ShowMessage('��ѡ��Ҫ�·�����ʱ��Σ�');
    Exit;
  end;
  if Trim(lblHolidayID.Caption)='' then
    WorkView.FieldByName('�ڼ���').Data.SetInteger(-1)
  else
    WorkView.FieldByName('�ڼ���').Data.SetInteger(StrToInt(lblHolidayID.Caption));

  WorkView.FieldByName('��ʱ���').Data.SetInteger(StrToInt(lblWeekId.Caption));
  //����Ž��鲻Ϊ�գ����·��Ž������Ա����
  if iGateGroup>0 then
  begin
    for i := 0 to iGateGroup-1 do
    begin
      if lvGateGroup.Items[i].Checked = True then
      begin
        WorkView.FieldByName('�Ž����').Data.SetInteger(StrToInt(lvGateGroup.Items[i].Caption));
        WorkView.FieldByName('��־').Data.SetInteger(1);
        for k := 0 to icust-1 do
        begin
          WorkView.FieldByName('�ͻ���').Data.SetInteger(StrToInt(lvCust.Items[k].Caption));
          MainRequest.SendCommand;
          //��¼������Ϣ
          if WorkView.FieldByName('������').Data.AsInteger<>0 then
          begin
            ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString+'--�����ж�');
            Exit;
          end;
          mmoError.Lines.Add(WorkView.fieldbyname('������Ϣ').Data.AsString);
        end;
      end;
    end;
  end;
  if iGate>0 then
  begin
    for i := 0 to iGate-1 do
    begin
      if lvGate.Items[i].Checked = True then
      begin
        WorkView.FieldByName('�Ž����').Data.SetInteger(StrToInt(lvGate.Items[i].Caption));
        WorkView.FieldByName('��־').Data.SetInteger(0);
        for k := 0 to icust-1 do
        begin
          WorkView.FieldByName('�ͻ���').Data.SetInteger(StrToInt(lvCust.Items[k].Caption));
          MainRequest.SendCommand;
          if WorkView.FieldByName('������').Data.AsInteger<>0 then
          begin
            ShowMessage(WorkView.fieldbyname('������Ϣ').Data.AsString+'--�����ж�');
            Exit;
          end;
          //��¼������Ϣ
          mmoError.Lines.Add(WorkView.fieldbyname('������Ϣ').Data.AsString);
        end;
      end;
    end;
  end;
  //allotFinish;
  if iSelect<6 then
    iSelect := iSelect + 1;
  selectRzts;
  ShowMessage('������Ա������ɣ������뿴������Ϣ��');
  //�������룬ȥ����ʼ����ť
  //allotFinish;
  //selectRzts;
end;

procedure TfaqhallotCustGate.btnSaveAsClick(Sender: TObject);
begin
  if Trim(mmoError.Text)='' then
    Exit;
  if dlgSaveError.Execute then
    mmoError.Lines.SaveToFile(dlgSaveError.FileName+'.txt');
end;

procedure TfaqhallotCustGate.btnClearClick(Sender: TObject);
begin
  if Trim(mmoError.Text)='' then
    Exit;
  if Application.MessageBox('��ȷ��Ҫ��մ�����Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  mmoError.Lines.Clear;
end;

procedure TfaqhallotCustGate.allotFinish;
begin
  if Application.MessageBox('��ȷ��Ҫ���ص���ʼ��״̬��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  clearListView(lvCustUnAllot);
  clearListView(lvCust);
  clearListView(lvGateGroup);
  clearListView(lvGate);
  clearListView(lvHoliday);
  clearListView(lvWeek);
  lblWeekId.Caption := '';
  lblHolidayID.Caption := '';
  lblHolidayName.Caption := '';
  lblWeekName.Caption := '';
  chkGateUnAllot.Checked := False;
  chkCustUnAllot.Checked := False;
  chkGateGroup.Checked := False;
  mmoError.Lines.Clear;
  iSelect := 1;
end;

procedure TfaqhallotCustGate.btnInitClick(Sender: TObject);
begin
  allotFinish;
  selectRzts;
end;

procedure TfaqhallotCustGate.chkGateUnAllotClick(Sender: TObject);
begin
  if listViewSelectAll(lvGate,chkGateUnAllot)=False then
    Exit;
end;

procedure TfaqhallotCustGate.btnClearSeleClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ���ѡ��Ľڼ�����Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  lblHolidayID.Caption := '';
  lblHolidayName.Caption := '';
end;

procedure TfaqhallotCustGate.chkGateGroupClick(Sender: TObject);
begin
  if listViewSelectAll(lvGateGroup,chkGateGroup)=False then
    exit;
end;

procedure TfaqhallotCustGate.SpeedButton1Click(Sender: TObject);
begin
  pnlImportError.Visible := True;

end;

procedure TfaqhallotCustGate.SpeedButton3Click(Sender: TObject);
begin
  pnlImportError.Visible := False;

end;

{-------------------------------------------------------------------------------
  ������:    TfaqhallotCustGate.ifAddCondition�Ƿ�������������û�з���false
  ����:      hanjiwei
  ����:      2007.04.13
  ����:      pnl: TPanel
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function TfaqhallotCustGate.ifAddCondition(pnl: TPanel): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i :=0  to pnl.ControlCount-1 do
  begin
    if pnl.Controls[i] is TWVEdit then
      if (TWVEdit(pnl.Controls[i]).Tag=1) and (Trim(TWVEdit(pnl.Controls[i]).Text)<>'') then
      begin
        Result := True;
        Exit;
      end;
    if pnl.Controls[i] is TWVComboBox then
      if (TWVComboBox(pnl.Controls[i]).Tag=1) and (Trim(TWVComboBox(pnl.Controls[i]).Text)<>'')
        and (Trim(TWVComboBox(pnl.Controls[i]).Text)<>'-') then
      begin
        Result := True;
        Exit;
      end;
  end;
end;

initialization
  TUIStdClassFactory.Create('�Ž���Ա��������',TfaqhallotCustGate);

end.