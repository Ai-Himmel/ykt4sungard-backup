unit UPatchCardIssue;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, 
  RzDBGrid, ComCtrls, RzListVw, RzPrgres, Buttons, ImgList, RzStatus,
  RzPanel, UtCardDll, EditExts, FilterCombos;

type
  TfaqhPatchCardIssue = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnReleaseCard: TBitBtn;
    WVLabel4: TWVLabel;
    WVLabel5: TWVLabel;
    WVLabel8: TWVLabel;
    WVLabel2: TWVLabel;
    WVLabel10: TWVLabel;
    RzListView1: TRzListView;
    WVLabel12: TWVLabel;
    cbbType: TWVComboBox;
    Label4: TLabel;
    edtTicketNo: TWVEdit;
    chkSelect: TWVCheckBox;
    WVRFeeQuery: TWVRequest;
    WVFeeQuery: TWorkView;
    WVRReleaseCard: TWVRequest;
    WVReleaseCard: TWorkView;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    Label2: TLabel;
    WVEdit1: TWVEdit;
    Label3: TLabel;
    WVEdit2: TWVEdit;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVLabel1: TWVLabel;
    WVEdit3: TWVEdit;
    Label5: TLabel;
    WVComboBox1: TWVComboBox;
    WVLabel6: TWVLabel;
    WVLabel7: TWVLabel;
    WVComboBox3: TWVComboBox;
    cbbSpec: TWVComboBox;
    WVLabel9: TWVLabel;
    Label6: TLabel;
    WVLabel11: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVEdit5: TWVEdit;
    Label8: TLabel;
    WVLabel13: TWVLabel;
    cbbDept: TWVComboBox;
    WVEdit6: TWVEdit;
    ImageList1: TImageList;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    Label9: TLabel;
    WVEdit4: TWVEdit;
    WVLabel3: TWVLabel;
    cbbCardType: TWVComboBox;
    chkSaveM: TWVCheckBox;
    edtmoney: TWVDigitalEdit;
    cbb1: TKSFilterComboBox;
    cbb2: TKSFilterComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnReleaseCardClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
    procedure cbb1FilterItems(Sender: TObject);
    procedure cbb2FilterItems(Sender: TObject);
  private
    SuccessCount: Integer;
    FailCount: Integer;
    GivedCount: Integer;
    NewPCardID, PCardID: string;
    tmpdataset: TDataSet;
    CardIssueLog: TextFile;
    PacthLogDir: string;
    
    SortCol: Integer;
    SortWay: Integer;

    sBackReturnInfo:string;
    ShowCardNo,sendDate:string;

    Fdept,Fspec:TStringList;
    FDspDept,FDspSpec:TStringList;
    { Private declarations }
    function CreatePatchCardLog: string;
    function GetTimeString(TimeString: string): string;
    procedure WritePatchLog(LogInfo: string);
    function GreatePacthLogDir: string;
    {�õ���ǰѡ���˶�����Ҫ�����Ŀͻ���}
    function GetCheckedCustInfoNum: integer;

    function PublishOneCard(FNo: integer; FCardId: string; ErrorMsg: string):Boolean;
    {����ǰ�Ѿ�ѡ�еĿͻ��ı�־�ż��뵽�ַ��������б���}
    procedure CustomIdAddArray(CustomArray: TStringList);

    //�������������༭���е�ֵ
    procedure setEditValue;

    procedure getFeeResult;

  public
    tipInfo:string;
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPatchCardIssue: TfaqhPatchCardIssue;
  m_bSort:Boolean;//���ڿ������򼰽����ת��


implementation

uses KsFrameworks,KSClientConsts, KSDataDictionary,
   SmartCardCommon, UPatchCardHint,FileCtrl;

{$R *.DFM}
procedure TfaqhPatchCardIssue.CustomIdAddArray(CustomArray: TStringList);
var
  i: integer;
begin
  if RzListView1.Items.Count = 0 then
    Exit;
  CustomArray.Clear;
  for i := 0 to RzListView1.Items.Count - 1 do
  begin
    if RzListView1.Items[i].Checked = True then
    begin
      CustomArray.Add(IntToStr(i));
    end;
  end;
end;

procedure TfaqhPatchCardIssue.Init;
begin
  inherited;
  cbbType.ItemIndex:=0;
  cbbCardType.itemindex := 0;
  PacthLogDir := GreatePacthLogDir;
  edtTicketNo.Enabled:=False;

  SuccessCount := 0;
  FailCount := 0;
  fillData2FilterCbb(Fdept,FDspDept,cbbDept);
  fillData2FilterCbb(Fspec,FDspSpec,cbbSpec);
end;

procedure TfaqhPatchCardIssue.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhPatchCardIssue.btnReleaseCardClick(Sender: TObject);
var
  LogFileName: string;
  IssueCount: integer;                                               
  TmpMsg: string;
  OneCardError: Boolean;
begin
  if PrepareReadCardInfo=False then
    Exit;
  SuccessCount := 0;
  FailCount := 0;
  GivedCount := 0;

  //��������������־�ļ�
  LogFileName := CreatePatchCardLog;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ��޷����д˲�����');
    Exit;
  end;
  if cbbType.ItemIndex = 0 then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ���ֵ��ʽ��');
    Exit;
  end;

  IssueCount := GetCheckedCustInfoNum;
  if IssueCount = 0 then
  begin
    showmessage('û����Ҫ���������Ŀͻ���');
    Exit;
  end
  else
  begin
    //RzProgressBar1.TotalParts := GetCheckedCustInfoNum;
    //RzProgressBar1.PartsComplete := 0;
    CurrentOperateRecordNo.Clear;
    CustomIdAddArray(CurrentOperateRecordNo);
  end;

  if CurrentOperateRecordNo.Count <= 0 then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��һ�����߶����Ҫ�����Ŀͻ���');
    Exit;
  end;
  try
    if strtofloat(edtMoney.text)<0 then
    begin
      Context.GetDialogSystem.ShowMessage('����Ľ���С��0�����������룡');
      Exit;
    end;
  except
    Context.GetDialogSystem.ShowMessage('��������Ч�Ľ�');
    Exit;
  end;
  WritePatchLog(DateToStr(Now)+'|'+TimeToStr(Now)+': ����ѡ����Ҫ���������Ŀͻ�Ϊ'+IntToStr(IssueCount) + ' ��');
  OneCardError := True;
  while CurrentOperateRecordNo.Count > 0 do
  begin
    getFeeResult;
    FrmPatchCardHint := TFrmPatchCardHint.Create(self);
    try                                           
      FrmPatchCardHint.PStuempNo :=
        RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[1];
      FrmPatchCardHint.PName :=
        RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[2];
      FrmPatchCardHint.PDept :=
        RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[6];
      FrmPatchCardHint.PCustType :=
        RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[3];

      FrmPatchCardHint.patchShowCardNo:=ShowCardNo;
      FrmPatchCardHint.patchEndDate:=sEndDate;
      FrmPatchCardHint.patchTipInfo:= tipInfo;

      if Trim(TmpMsg) = '' then
        FrmPatchCardHint.PWarning := '����������Ϣ�Ƿ���������Ҫ��������Ϣһ�£�'
      else
        FrmPatchCardHint.PWarning := TmpMsg;
      FrmPatchCardHint.PatchCardAccount := IssueCount;
      FrmPatchCardHint.PatchCardSuccess := self.SuccessCount;
      FrmPatchCardHint.PatchCardError := self.FailCount;
      FrmPatchCardHint.PatchCardGived := self.GivedCount;
      FrmPatchCardHint.PatchOneCardError := OneCardError;
      FrmPatchCardHint.PTotMoney := '�ϼ�'+edtMoney.Text+' Ԫ';
      FrmPatchCardHint.ShowModal;
      if FrmPatchCardHint.PatchOperaKind = 2 then
      begin
        setEditValue;
        CurrentOperateRecordNo.Clear;
        Exit;
      end;
      if FrmPatchCardHint.PatchOperaKind = 3 then
      begin
        seteditValue();
        OneCardError := True;
        GivedCount := GivedCount + 1;
        WritePatchLog('ѧ/����: ' + RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[1] +' ������������û�н��з�����');
        if CurrentOperateRecordNo.Count > 0 then
          CurrentOperateRecordNo.Delete(0);
        FrmPatchCardHint.Close;
        Continue;
      end
      else if FrmPatchCardHint.PatchOperaKind = 1 then
      begin
        setEditValue;
        NewPCardID := '';
        if SimpleReadCardPhyID(NewPCardID) <> 0 then
        begin
          TmpMsg := '���ڶ�д���Ϸ�����ȷ�Ŀ��Է��еĿ�Ƭ��';
          OneCardError := False;
          FrmPatchCardHint.Close;
          continue;
        end
        else
        begin
          TmpMsg := '';
          RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].Selected := True;
          //ShowWaiting(SWaitingPubCard);
          if PublishOneCard(StrToInt(CurrentOperateRecordNo.Strings[0]),NewPCardID, TmpMsg) then
          begin
            SuccessCount := SuccessCount + 1;
            OneCardError := True;
            WritePatchLog('ѧ/����: ' + RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[1] +' �����ɹ���');

            //�����ɹ�����ʾ��������һ
            //if (FrmPatchCardHint.edtShowCard.Text)<>'' then
            //begin
              //sShowCardNo:=IntToStr(StrToInt64(FrmPatchCardHint.edtShowCard.Text)+1);
            //end;
            sendDate:=FrmPatchCardHint.edtEndDate.Text;

            if CurrentOperateRecordNo.Count > 0 then CurrentOperateRecordNo.Delete(0);
            CloseWaiting;
          end
          else
          begin
            FailCount := FailCount + 1;
            OneCardError := False;
            WritePatchLog('ѧ/����: ' +RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[1] +' ��������');
            TmpMsg := 'Ϊ' + RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[0] +'�������̳���--��������Ч�����ڻ���ʾ����'+sBackReturnInfo;
            FrmPatchCardHint.Close;
            //CloseWaiting;
            Continue;
          end;
        end; {else end}
      end; {else if end}
    finally
      FrmPatchCardHint.Free;
    end;
  end;
  WritePatchLog(DateToStr(Now) + ' ' + TimeToStr(Now) + ': ���η����ɹ��� ' + IntToStr(SuccessCount) + ' ��');
  WritePatchLog(DateToStr(Now) + ' ' + TimeToStr(Now) + ': ���η��������� ' + IntToStr(GivedCount) + ' ��');
  WritePatchLog(DateToStr(Now) + ' ' + TimeToStr(Now) + ': ���η���ʧ���� ' + IntToStr(FailCount) + ' ��');
end;

function TfaqhPatchCardIssue.CreatePatchCardLog: string;
var
  DateTime: TDateTime;
  Time: TDateTime;
  FileName: string;
begin
  DateTime := now;
  //���ʱ��
  Time := Frac(DateTime);
  FileName := 'Patch' + DateToStr(Now) + GetTimeString(TimeToStr(Time)) + '.txt';
  AssignFile(CardIssueLog, PacthLogDir + '\' + FileName); //��ֵ�ļ���
  Rewrite(CardIssueLog); //�����ļ�����
  CloseFile(CardIssueLog); //�ر��ļ�
  Result := FileName;
end;

function TfaqhPatchCardIssue.GetTimeString(TimeString: string): string;
begin
  if Length(TimeString) = 7 then //1:02:03�����
  begin
    Result := '0' + copy(TimeString, 1, 1) + copy(TimeString, 3, 2) +
      copy(TimeString, 6, 2);
  end;
  if Length(TimeString) = 8 then //11:02:03�����
  begin
    Result := copy(TimeString, 1, 2) + copy(TimeString, 4, 2) + copy(TimeString,
      7, 2);
  end;
end;

procedure TfaqhPatchCardIssue.WritePatchLog(LogInfo: string);
begin
  append(CardIssueLog);
  Writeln(CardIssueLog, LogInfo); //���ļ���д����
  CloseFile(CardIssueLog);
end;

function TfaqhPatchCardIssue.GreatePacthLogDir: string;
var
  path: string;
begin
  path := ExtractFileDir(application.ExeName);
  path := path + '\' + 'logs';
  if not DirectoryExists(path) then
    if not CreateDir(path) then
      raise Exception.Create('Cannot create ' + path);
  result := path;
end;

procedure TfaqhPatchCardIssue.btnQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
  cardType:Integer;
  //deptId:string;
  deptNo,specNo:string;
begin
  try
    RzListView1.Items.Clear;
  except
    on e:exception do
    begin
      showmessage(e.message);
    end;
  end;
  try
    deptNo := Trim(Copy(cbb1.Text,1,Pos('-',cbb1.Text)-1));
    specNo := Trim(Copy(cbb2.Text,1,Pos('-',cbb2.Text)-1));
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except

  end;

  WorkView.FieldByName('����').Data.SetString(deptNo);
  WorkView.FieldByName('רҵ').Data.SetString(specNo);
  
  WorkView.FieldByName('�������').Data.SetInteger(cardType);
  //deptid := trim( Copy(cbbDeptId.Text,1,Pos('-',cbbDeptId.Text)-1));
  inherited;
  tmpdataset := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    try
      tmpItem := RzListView1.Items.Add;
      //��������
      tmpItem.Caption := GetIdObjectName(-27,tmpdataset.fieldbyname('sbranch_code0').AsString);
      //�ͻ���
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
      //ѧ����
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString);
      //����
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);
      //�ͻ����
      tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lsafe_level2').AsString));
      //�շ�������
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol5').AsString);
      //�շ����
      tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol5').AsString));
      //����
      tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('scert_no').AsString));
      //רҵ
      tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('scert_no2').AsString));
      //��������
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('sdate3').AsString);
      //�������κ�
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_limit2').AsString);
      //֤������
      tmpItem.SubItems.Add(GetIdObjectName(87,tmpdataset.fieldbyname('smarket_code').AsString));
      //֤������
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail2').AsString);
      //tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail2').AsString);
    except
    end;
    
    tmpdataset.Next;
  end;

end;

procedure TfaqhPatchCardIssue.chkSelectClick(Sender: TObject);
var
  i: integer;
begin
  if RzListView1.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelect.Checked = True then
  begin
    for i := 0 to RzListView1.Items.Count - 1 do
    begin
      RzListView1.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to RzListView1.Items.Count - 1 do
    begin
      RzListView1.Items[i].Checked := False;
    end;
  end;
end;

function TfaqhPatchCardIssue.GetCheckedCustInfoNum: integer;
var
  i: integer;
begin
  Result := 0;
  if RzListView1.Items.Count = 0 then
  begin
    Result := 0;
  end;
  for i := 0 to RzListView1.Items.Count - 1 do
  begin
    if RzListView1.Items[i].Checked = True then
    begin
      Result := Result + 1;
    end;
  end;
end;

function TfaqhPatchCardIssue.PublishOneCard(FNo: integer; FCardId: string;ErrorMsg: string): boolean;
var
  custId: Integer;
  OperatorNoName: string;
  CardManage: TCardManage;
  cardType:Integer;
  feeType:string;
begin
  Result := True;
  //FrmPatchCardHint.edtshowcard.text := readShowCarNo;
  showCardNo := readShowCarNo;
  if showCardNo='-1' then
  begin
    ErrorMsg := '������Ϣʧ�ܣ��ÿ�����û�г�ʼ��';
    Result := False;
    Exit;
  end;
  CardManage := nil;

  //ȡ�ͻ���
  custId := StrToInt(RzListView1.Items.Item[FNo].SubItems[0]);
  //��������
  cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  //�շѷ�ʽ
  feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  //��������
  //endDate := RzListView1.Items.Item[FNo].SubItems[8];
  try
    CardManage := TCardManage.Create;
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      ErrorMsg := '�������к�ʧ�ܣ�';
      Result := False;
      exit;
    end;
    OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
    WVReleaseCard.SynchronizeCtrlsToFields;
    WVReleaseCard.FieldByName('����Ա').Data.SetString(OperatorNoName);
    WVReleaseCard.FieldByName('��ʾ����').Data.SetString(showCardNo);        //
    WVReleaseCard.FieldByName('������').Data.SetString(pCardID);           //
    WVReleaseCard.FieldByName('�շѷ�ʽ').Data.setinteger(strtoint(feeType));
    WVReleaseCard.FieldByName('Ʊ�ݺ���').Data.SetString(edtTicketNo.Text);
    WVReleaseCard.FieldByName('��������').Data.SetString(sendDate);
    WVReleaseCard.FieldByName('������').Data.SetInteger(cardType);
    WVReleaseCard.FieldByName('�ͻ���').Data.SetInteger(custId);
    WVReleaseCard.FieldByName('�շѽ��').Data.SetFloat(StrToFloat(edtMoney.Text));
    WVReleaseCard.FieldByName('�Ƿ񲻼�����').Data.SetString('0');
    WVRReleaseCard.SendCommand;
    if (WVReleaseCard.FieldByName('������').Data.AsInteger = 0) then
    begin
      try
        sBackReturnInfo:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,0);
      except
        ErrorMsg := 'д������ʧ�ܣ����Ժ������־����д����Ϣ��';
        Result := False;
      end;
    end
    else
    begin
      sBackReturnInfo:=WVReleaseCard.fieldbyname('������Ϣ').Data.AsString;
      Result := False;
    end;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhPatchCardIssue.setEditValue;
begin
  {
  if trim(FrmPatchCardHint.edtshowcard.text)<>'' then
    showcardno:=inttostr(strtoint64(FrmPatchCardHint.edtshowcard.text)+1)
  else
    showcardno:=FrmPatchCardHint.edtshowcard.text;
  }
  senddate:=FrmPatchCardHint.edtenddate.text
end;

procedure TfaqhPatchCardIssue.cbbTypeChange(Sender: TObject);
begin
  inherited;
  if (cbbType.ItemIndex=0)or(cbbType.ItemIndex=1) then
    edtTicketNo.Enabled:=False
  else
    edtTicketNo.Enabled:=True;
  edtTicketNo.Text:='';

end;

procedure TfaqhPatchCardIssue.getFeeResult;
var
  feeType, cardType,custId: Integer;
  //sEndDate:string;
  sReturnInfo:string;
  fMoney : Real;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  feeType := StrToInt(RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[4]);
  custId := StrToInt(RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[0]);
  //sEndDate := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sdate3').AsString;
  try
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except
    Exit;
  end;
  WVFeeQuery.FieldByName('�շ����').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('������').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('���ܺ�').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('�ͻ���').Data.SetInteger(custId);
  WVFeeQuery.FieldByName('�Ƿ񲻼�����').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('������').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('�շ���Ϣ').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('�ܷ���').Data.AsFloat;
    if chkSaveM.Checked=False then
      edtMoney.Text := floattostr(fMoney);
    sendDate := wvfeequery.fieldbyname('����Ч��').data.asstring;
    RzStatusPane1.Caption := sReturnInfo;
    tipInfo := sReturnInfo;
  end;
end;

procedure TfaqhPatchCardIssue.cbb1FilterItems(Sender: TObject);
begin
  cbbFilterItem( Fdept,FDspDept,sender);

end;

procedure TfaqhPatchCardIssue.cbb2FilterItems(Sender: TObject);
begin
  cbbFilterItem( Fspec,FDspSpec,sender);

end;

initialization
  TUIStdClassFactory.Create('�������п�', TfaqhPatchCardIssue);

end.

