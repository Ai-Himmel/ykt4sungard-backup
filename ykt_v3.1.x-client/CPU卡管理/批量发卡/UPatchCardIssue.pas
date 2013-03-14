unit UPatchCardIssue;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, 
  RzDBGrid, ComCtrls, RzListVw, RzPrgres, Buttons, ImgList, RzStatus,
  RzPanel, CardDll, EditExts, FilterCombos,WaterDll;

type
  TfaqhPatchCardIssue = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnReleaseCard: TBitBtn;
    WVLabel8: TWVLabel;
    WVLabel2: TWVLabel;
    WVLabel10: TWVLabel;
    RzListView1: TRzListView;
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
    grp1: TGroupBox;
    chkSelect: TWVCheckBox;
    cbbType: TWVComboBox;
    WVLabel12: TWVLabel;
    Label4: TLabel;
    edtTicketNo: TWVEdit;
    WVLabel4: TWVLabel;
    edtAddmoney: TWVDigitalEdit;
    WVLabel5: TWVLabel;
    chkSaveM: TWVCheckBox;
    grpWater: TGroupBox;
    Label11: TLabel;
    Label12: TLabel;
    edtWaterMoney: TWVDigitalEdit;
    WVLabel14: TWVLabel;
    cbbPhyType: TWVComboBox;
    imgPhoto: TImage;
    WVWaterPrice: TWorkView;
    WVRWaterPrice: TWVRequest;
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
    PCardID: string;
    tmpdataset: TDataSet;
    CardIssueLog: TextFile;
    PacthLogDir: string;

    sBackReturnInfo:string;
    ShowCardNo,sendDate:string;

    endGetPhotoSign:Boolean;

    Fdept,Fspec:TStringList;
    FDspDept,FDspSpec:TStringList;
    { Private declarations }
    function CreatePatchCardLog: string;
    function GetTimeString(TimeString: string): string;
    procedure WritePatchLog(LogInfo: string);
    function GreatePacthLogDir: string;
    {�õ���ǰѡ���˶�����Ҫ�����Ŀͻ���}
    function GetCheckedCustInfoNum: integer;

    function PublishOneCard(FNo: integer; ErrorMsg: string):Boolean;
    {����ǰ�Ѿ�ѡ�еĿͻ��ı�־�ż��뵽�ַ��������б���}
    procedure CustomIdAddArray(CustomArray: TStringList);

    //�������������༭���е�ֵ
    procedure setEditValue;

    procedure getFeeResult;
    procedure getPhoto(custNo:string);

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
   SmartCardCommon, UPatchCardHint,FileCtrl,filetrans;

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
  cbbPhyType.ItemIndex := 0;
  cbbCardType.itemindex := 0;
  PacthLogDir := GreatePacthLogDir;
  edtTicketNo.Enabled:=False;
  if waterIfDef = 0 then
    grpWater.Visible := False
  else
    grpWater.Visible := True;
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    endGetPhotoSign := True;
    //filePath := ;
    imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
  except

  end;

  SuccessCount := 0;
  FailCount := 0;
  fillData2FilterCbb(Fdept,FDspDept,cbbDept);
  fillData2FilterCbb(Fspec,FDspSpec,cbbSpec);
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
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
  if preReadCard=False then
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
    CurrentOperateRecordNo.Clear;
    CustomIdAddArray(CurrentOperateRecordNo);
  end;

  if CurrentOperateRecordNo.Count <= 0 then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��һ�����߶����Ҫ�����Ŀͻ���');
    Exit;
  end;
  try
    if strtofloat(edtAddmoney.text)<0 then
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
    getPhoto(RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[0]);
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
      FrmPatchCardHint.PTotMoney := '�ϼ�'+edtaddMoney.Text+' Ԫ';
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
        TmpMsg := '';
        RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].Selected := True;
        //ShowWaiting(SWaitingPubCard);
        if PublishOneCard(StrToInt(CurrentOperateRecordNo.Strings[0]),TmpMsg) then
        begin
          SuccessCount := SuccessCount + 1;
          OneCardError := True;
          WritePatchLog('ѧ/����: ' + RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[1] +' �����ɹ���');

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
  //deptNo,specNo:string;
begin
  try
    RzListView1.Items.Clear;
  except
    on e:exception do
    begin
      showmessage(e.message);
    end;
  end;
  {
  try
    deptNo := Trim(Copy(cbb1.Text,1,Pos('-',cbb1.Text)-1));
    specNo := Trim(Copy(cbb2.Text,1,Pos('-',cbb2.Text)-1));
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except

  end;

  WorkView.FieldByName('����').Data.SetString(deptNo);
  WorkView.FieldByName('רҵ').Data.SetString(specNo);
  }
  cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
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
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('spost_code').AsString);
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

function TfaqhPatchCardIssue.PublishOneCard(FNo: integer;ErrorMsg: string): boolean;
var
  custId: Integer;
  OperatorNoName: string;
  cardType:Integer;
  cardPhyType:integer;
  cardSelfType:integer;
  feeType:string;
  reCode:Integer;

  //waterCard:TWATERCOMMPACK;
  cardNo:Integer;
  cardEndDate:string;
  custType:Integer;
  st:Integer;
  cm:TCM;
begin
  Result := True;
  if relCardJudge=False then
  begin
    Result := False;
    Exit;
  end;

  cm := nil;
  try
    cm := tcm.Create;
    st := cm.card(PCardID);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(APP_TYPE);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(SHOW_CARDNO);
    if cm.readCard(pCardID)<>0 then
    begin
      context.GetDialogSystem.ShowMessage('�ÿ�û�г�ʼ�������ȳ�ʼ����');
      exit;
    end
    else
    begin
      {
      if (cm.getAppType='') or (cm.getAppType='0') then
      begin
        context.GetDialogSystem.ShowMessage('�ÿ���ʼ�������ȷ�������³�ʼ��-'+cm.getAppType);
        exit;
      end;
      }
      if (cm.getCardBalance='') or (cm.getCardBalance<>'0') then
      begin
        context.GetDialogSystem.ShowMessage('�ÿ���Ϊ�㣬�Ȼ��ոÿ���');
        exit;
      end;
      //ȡ����ʾ����
      showCardNo:=cm.getShowCardNo;
    end;
  finally
    cm.Destroy;
  end;


  {
  if readCardOneInfo(APP_TYPE)='0' then
  begin
    context.GetDialogSystem.ShowMessage('�ÿ�û�г�ʼ�������ȳ�ʼ����');
    exit;
  end;
  if readCardOneInfo(CARD_BALANCE)<>'0' then
  begin
    context.GetDialogSystem.ShowMessage('�ÿ���Ϊ�㣬�Ȼ��ոÿ���');
    exit;
  end;
  //FrmPatchCardHint.edtshowcard.text := readShowCarNo;
  showCardNo := readCardOneInfo(SHOW_CARDNO);
  }
  //ȡ�ͻ���
  custId := StrToInt(RzListView1.Items.Item[FNo].SubItems[0]);
  try
    //��������
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    //�շѷ�ʽ
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    //����������
    cardPhyType := 0;//StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
  except
    cardType := 0;
    feeType := '0';
    cardPhyType := 0;
  end;
  //��������
  //endDate := RzListView1.Items.Item[FNo].SubItems[8];
  {
  PCardID := readCardOneInfo(CARD_SERI_NO);
  if PCardID = '' then
  begin
    ErrorMsg := '�������к�ʧ�ܣ�';
    Result := False;
    exit;
  end;
  }
  //ȡ���ڲ�����
  try
    cardSelfType := ks_cardtype();
  except
    cardSelfType := 0;
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
  WVReleaseCard.FieldByName('����������').Data.SetInteger(cardPhyType);
  WVReleaseCard.FieldByName('���ڲ�����').Data.SetInteger(cardSelfType);
  WVReleaseCard.FieldByName('�ͻ���').Data.SetInteger(custId);
  WVReleaseCard.FieldByName('�շѽ��').Data.SetFloat(StrToFloat(edtaddMoney.Text));
  WVReleaseCard.FieldByName('�Ƿ񲻼�����').Data.SetString('0');
  WVRReleaseCard.SendCommand;
  if (WVReleaseCard.FieldByName('������').Data.AsInteger = 0) then
  begin
    try
      if waterStrings.Count = 0 then
      begin
        sBackReturnInfo:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,0,reCode);
        if reCode = 0 then
          KNG_beep;
      end
      else
      begin
        //��ʼ��ˮ�ؿ�
        RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,0,reCode);

        if reCode >= 0 then
        begin
          cardNo:=WVReleaseCard.fieldbyname('����').Data.AsInteger;
          cardEndDate:=WVReleaseCard.fieldbyname('��������').Data.AsString;
          custType := WVReleaseCard.fieldbyname('�շ����').Data.AsInteger;
          {
          st := mfcard(pCardID);
          //ShowMessage(IntToStr(st));
          waterCard.cardno := cardNo;
          waterCard.custno := custId;
          watercard.custtype := custType;
          StrCopy(@waterCard.expireddate,PChar(cardEndDate));
          waterCard.lockflag := 255;
          waterCard.money := 0;
          waterCard.totalmoney := 0;
          StrCopy(@waterCard.addtime,PChar('00000000000000'));
          waterCard.addcount := 0;
          waterCard.price1 := cpuWaterPrice1;
          waterCard.price2 := cpuWaterPrice2;
          waterCard.price3 := cpuWaterPrice3;
          st := ks_water_publishcard(4,@waterCard);
          //sti := ks_water_publishcard(hdWater,@waterCard);
          }
          setWaterPrice(WVWaterPrice,WVRWaterPrice,custType);
          st := pubSmlBag(cardno,custId,custType,cardEndDate,pCardID);
          KNG_beep;
          if (st<>0)  then
            Context.GetDialogSystem.ShowMessage('ˮ��Ǯ����ʼ��ʧ�ܣ������³�ʼ��ˮ��Ǯ��-'+inttostr(st));
        end;
      end;
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
      edtaddMoney.Text := floattostr(fMoney);
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

procedure TfaqhPatchCardIssue.getPhoto(custNo:string);
var
  dFile:string;
  ret:Integer;
  //custNo:string;
begin
  if showphoto=0 then
    Exit;
  //��ѯ��Ƭǰ�������ǰ����Ƭ��Ϣ
  imgPhoto.Picture := nil;

  if endGetPhotoSign=false then
    Exit;
  {
  try
    //�Ӻ�̨ȡ����Ƭ�����ƣ���Ƭ��Ϊ�ͻ���
    custNo := Grid.DataSource.DataSet.fieldbyname('lvol1').asstring;
  except
    Context.GetDialogSystem.ShowMessage('����ѡ��һ����¼��Ȼ����ȡ��Ƭ��');
    Exit;
  end;
  }
  dFile := 'photo999999.jpg';
  try
    try
      endGetPhotoSign:=false;
      ret := KSG_Downloadphoto_File(custNo,dFile);
      if ret = KSG_SUCCESS then
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+dFile);
      end
      else
      begin
        imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
        //Context.GetDialogSystem.ShowMessage('�ÿͻ�û����Ƭ��Ϣ-'+inttostr(ret));
        Exit;
      end;
    except
      on e:Exception do
      begin        
        Context.GetDialogSystem.ShowMessage('������Ƭ��Ϣʧ�ܣ��ÿͻ�����û������-'+e.Message);
        Exit;
      end;
    end;
  finally
    endGetPhotoSign:=True;
  end;
  //������Ƭ��ɺ�ɾ��
  //�ڱ��ز����Ƿ����dFile����Ƭ��������ɾ��
  try
    if FileExists(sAppPath+dFile) then
      DeleteFile(sAppPath+dFile);
  except
    //WriteLog('ɾ�� photo999999.jpg ʧ�ܣ����ļ������ڣ�');
  end;
end;

initialization
  TUIStdClassFactory.Create('�������п�', TfaqhPatchCardIssue);

end.

