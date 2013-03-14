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
    {得到当前选中了多少需要发卡的客户数}
    function GetCheckedCustInfoNum: integer;

    function PublishOneCard(FNo: integer; ErrorMsg: string):Boolean;
    {将当前已经选中的客户的标志号加入到字符串数组中保存}
    procedure CustomIdAddArray(CustomArray: TStringList);

    //设置批量发卡编辑框中的值
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
  m_bSort:Boolean;//用于控制升序及降序的转换


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
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
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

  //生成批量发卡日志文件
  LogFileName := CreatePatchCardLog;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;
  if cbbType.ItemIndex = 0 then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择充值方式！');
    Exit;
  end;

  IssueCount := GetCheckedCustInfoNum;
  if IssueCount = 0 then
  begin
    showmessage('没有需要批量发卡的客户！');
    Exit;
  end
  else
  begin
    CurrentOperateRecordNo.Clear;
    CustomIdAddArray(CurrentOperateRecordNo);
  end;

  if CurrentOperateRecordNo.Count <= 0 then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择一个或者多个需要发卡的客户！');
    Exit;
  end;
  try
    if strtofloat(edtAddmoney.text)<0 then
    begin
      Context.GetDialogSystem.ShowMessage('输入的金额不能小于0，请重新输入！');
      Exit;
    end;
  except
    Context.GetDialogSystem.ShowMessage('请输入有效的金额！');
    Exit;
  end;
  WritePatchLog(DateToStr(Now)+'|'+TimeToStr(Now)+': 本次选中需要批量发卡的客户为'+IntToStr(IssueCount) + ' 个');
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
        FrmPatchCardHint.PWarning := '请检查以上信息是否与您即将要发卡的信息一致！'
      else
        FrmPatchCardHint.PWarning := TmpMsg;
      FrmPatchCardHint.PatchCardAccount := IssueCount;
      FrmPatchCardHint.PatchCardSuccess := self.SuccessCount;
      FrmPatchCardHint.PatchCardError := self.FailCount;
      FrmPatchCardHint.PatchCardGived := self.GivedCount;
      FrmPatchCardHint.PatchOneCardError := OneCardError;
      FrmPatchCardHint.PTotMoney := '合计'+edtaddMoney.Text+' 元';
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
        WritePatchLog('学/工号: ' + RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[1] +' 被跳过，本次没有进行发卡！');
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
          WritePatchLog('学/工号: ' + RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[1] +' 发卡成功！');

          sendDate:=FrmPatchCardHint.edtEndDate.Text;

          if CurrentOperateRecordNo.Count > 0 then CurrentOperateRecordNo.Delete(0);
          CloseWaiting;
        end
        else
        begin
          FailCount := FailCount + 1;
          OneCardError := False;
          WritePatchLog('学/工号: ' +RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[1] +' 发卡出错！');
          TmpMsg := '为' + RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[0] +'发卡过程出错--请输入有效的日期或显示卡号'+sBackReturnInfo;
          FrmPatchCardHint.Close;
          //CloseWaiting;
          Continue;
        end;
      end; {else if end}
    finally
      FrmPatchCardHint.Free;
    end;
  end;
  WritePatchLog(DateToStr(Now) + ' ' + TimeToStr(Now) + ': 本次发卡成功数 ' + IntToStr(SuccessCount) + ' 个');
  WritePatchLog(DateToStr(Now) + ' ' + TimeToStr(Now) + ': 本次发卡跳过数 ' + IntToStr(GivedCount) + ' 个');
  WritePatchLog(DateToStr(Now) + ' ' + TimeToStr(Now) + ': 本次发卡失败数 ' + IntToStr(FailCount) + ' 个');
end;

function TfaqhPatchCardIssue.CreatePatchCardLog: string;
var
  DateTime: TDateTime;
  Time: TDateTime;
  FileName: string;
begin
  DateTime := now;
  //获得时间
  Time := Frac(DateTime);
  FileName := 'Patch' + DateToStr(Now) + GetTimeString(TimeToStr(Time)) + '.txt';
  AssignFile(CardIssueLog, PacthLogDir + '\' + FileName); //赋值文件名
  Rewrite(CardIssueLog); //创建文件并打开
  CloseFile(CardIssueLog); //关闭文件
  Result := FileName;
end;

function TfaqhPatchCardIssue.GetTimeString(TimeString: string): string;
begin
  if Length(TimeString) = 7 then //1:02:03的情况
  begin
    Result := '0' + copy(TimeString, 1, 1) + copy(TimeString, 3, 2) +
      copy(TimeString, 6, 2);
  end;
  if Length(TimeString) = 8 then //11:02:03的情况
  begin
    Result := copy(TimeString, 1, 2) + copy(TimeString, 4, 2) + copy(TimeString,
      7, 2);
  end;
end;

procedure TfaqhPatchCardIssue.WritePatchLog(LogInfo: string);
begin
  append(CardIssueLog);
  Writeln(CardIssueLog, LogInfo); //在文件中写数据
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

  WorkView.FieldByName('部门').Data.SetString(deptNo);
  WorkView.FieldByName('专业').Data.SetString(specNo);
  }
  cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  WorkView.FieldByName('发卡类别').Data.SetInteger(cardType);
  //deptid := trim( Copy(cbbDeptId.Text,1,Pos('-',cbbDeptId.Text)-1));
  inherited;
  tmpdataset := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    try
      tmpItem := RzListView1.Items.Add;
      //所属区域
      tmpItem.Caption := GetIdObjectName(-27,tmpdataset.fieldbyname('sbranch_code0').AsString);
      //客户号
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
      //学工号
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString);
      //姓名
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);
      //客户类别
      tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lsafe_level2').AsString));
      //收费类别代码
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol5').AsString);
      //收费类别
      tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol5').AsString));
      //部门
      tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('scert_no').AsString));
      //专业
      tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('scert_no2').AsString));
      //截至日期
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('sdate3').AsString);
      //导入批次号
      tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_limit2').AsString);
      //证件类型
      tmpItem.SubItems.Add(GetIdObjectName(87,tmpdataset.fieldbyname('smarket_code').AsString));
      //证件号码
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
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(APP_TYPE);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(SHOW_CARDNO);
    if cm.readCard(pCardID)<>0 then
    begin
      context.GetDialogSystem.ShowMessage('该卡没有初始化，请先初始化！');
      exit;
    end
    else
    begin
      {
      if (cm.getAppType='') or (cm.getAppType='0') then
      begin
        context.GetDialogSystem.ShowMessage('该卡初始化类别不正确，请重新初始化-'+cm.getAppType);
        exit;
      end;
      }
      if (cm.getCardBalance='') or (cm.getCardBalance<>'0') then
      begin
        context.GetDialogSystem.ShowMessage('该卡金额不为零，先回收该卡！');
        exit;
      end;
      //取得显示卡号
      showCardNo:=cm.getShowCardNo;
    end;
  finally
    cm.Destroy;
  end;


  {
  if readCardOneInfo(APP_TYPE)='0' then
  begin
    context.GetDialogSystem.ShowMessage('该卡没有初始化，请先初始化！');
    exit;
  end;
  if readCardOneInfo(CARD_BALANCE)<>'0' then
  begin
    context.GetDialogSystem.ShowMessage('该卡金额不为零，先回收该卡！');
    exit;
  end;
  //FrmPatchCardHint.edtshowcard.text := readShowCarNo;
  showCardNo := readCardOneInfo(SHOW_CARDNO);
  }
  //取客户号
  custId := StrToInt(RzListView1.Items.Item[FNo].SubItems[0]);
  try
    //发卡类型
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    //收费方式
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    //卡物理类型
    cardPhyType := 0;//StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
  except
    cardType := 0;
    feeType := '0';
    cardPhyType := 0;
  end;
  //到期日期
  //endDate := RzListView1.Items.Item[FNo].SubItems[8];
  {
  PCardID := readCardOneInfo(CARD_SERI_NO);
  if PCardID = '' then
  begin
    ErrorMsg := '读卡序列号失败！';
    Result := False;
    exit;
  end;
  }
  //取卡内部编码
  try
    cardSelfType := ks_cardtype();
  except
    cardSelfType := 0;
  end;

  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  WVReleaseCard.SynchronizeCtrlsToFields;
  WVReleaseCard.FieldByName('操作员').Data.SetString(OperatorNoName);
  WVReleaseCard.FieldByName('显示卡号').Data.SetString(showCardNo);        //
  WVReleaseCard.FieldByName('物理卡号').Data.SetString(pCardID);           //
  WVReleaseCard.FieldByName('收费方式').Data.setinteger(strtoint(feeType));
  WVReleaseCard.FieldByName('票据号码').Data.SetString(edtTicketNo.Text);
  WVReleaseCard.FieldByName('到期日期').Data.SetString(sendDate);
  WVReleaseCard.FieldByName('卡类型').Data.SetInteger(cardType);
  WVReleaseCard.FieldByName('卡物理类型').Data.SetInteger(cardPhyType);
  WVReleaseCard.FieldByName('卡内部编码').Data.SetInteger(cardSelfType);
  WVReleaseCard.FieldByName('客户号').Data.SetInteger(custId);
  WVReleaseCard.FieldByName('收费金额').Data.SetFloat(StrToFloat(edtaddMoney.Text));
  WVReleaseCard.FieldByName('是否不记名卡').Data.SetString('0');
  WVRReleaseCard.SendCommand;
  if (WVReleaseCard.FieldByName('返回码').Data.AsInteger = 0) then
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
        //初始化水控卡
        RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,0,reCode);

        if reCode >= 0 then
        begin
          cardNo:=WVReleaseCard.fieldbyname('卡号').Data.AsInteger;
          cardEndDate:=WVReleaseCard.fieldbyname('到期日期').Data.AsString;
          custType := WVReleaseCard.fieldbyname('收费类别').Data.AsInteger;
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
            Context.GetDialogSystem.ShowMessage('水控钱包初始化失败，请重新初始化水控钱包-'+inttostr(st));
        end;
      end;
    except
      ErrorMsg := '写卡过程失败！请稍候查阅日志并补写卡信息！';
      Result := False;
    end;
  end
  else
  begin
    sBackReturnInfo:=WVReleaseCard.fieldbyname('返回信息').Data.AsString;
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
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  feeType := StrToInt(RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[4]);
  custId := StrToInt(RzListView1.Items.Item[StrToInt(CurrentOperateRecordNo.Strings[0])].SubItems[0]);
  //sEndDate := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sdate3').AsString;
  try
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except
    Exit;
  end;
  WVFeeQuery.FieldByName('收费类别').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('卡类型').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('功能号').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('客户号').Data.SetInteger(custId);
  WVFeeQuery.FieldByName('是否不记名卡').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('返回码').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('收费信息').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('总费用').Data.AsFloat;
    if chkSaveM.Checked=False then
      edtaddMoney.Text := floattostr(fMoney);
    sendDate := wvfeequery.fieldbyname('卡有效期').data.asstring;
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
  //查询照片前先清空以前的照片信息
  imgPhoto.Picture := nil;

  if endGetPhotoSign=false then
    Exit;
  {
  try
    //从后台取得照片的名称，照片名为客户号
    custNo := Grid.DataSource.DataSet.fieldbyname('lvol1').asstring;
  except
    Context.GetDialogSystem.ShowMessage('请先选择一条记录，然后再取照片！');
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
        //Context.GetDialogSystem.ShowMessage('该客户没有照片信息-'+inttostr(ret));
        Exit;
      end;
    except
      on e:Exception do
      begin        
        Context.GetDialogSystem.ShowMessage('下载照片信息失败，该客户可能没有拍照-'+e.Message);
        Exit;
      end;
    end;
  finally
    endGetPhotoSign:=True;
  end;
  //加载照片完成后删除
  //在本地查找是否存在dFile的照片，存在则删除
  try
    if FileExists(sAppPath+dFile) then
      DeleteFile(sAppPath+dFile);
  except
    //WriteLog('删除 photo999999.jpg 失败，该文件不存在！');
  end;
end;

initialization
  TUIStdClassFactory.Create('批量发行卡', TfaqhPatchCardIssue);

end.

