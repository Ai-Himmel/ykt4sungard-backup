unit UAReleaseCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  RzSplit, Menus, UIncrementComboBox, CardDll,WaterDll,
  EditExts;

type
  TfaqhReleaseCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label5: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit5: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    Label6: TLabel;
    WVEdit6: TWVEdit;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    btnReleaseCard: TBitBtn;
    grpReleaseCard: TGroupBox;
    WVLabel11: TWVLabel;
    cbbType: TWVComboBox;
    Label10: TLabel;
    edtTicketNo: TWVEdit;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVLabel9: TWVLabel;
    WVComboBox7: TWVComboBox;
    WVFeeQuery: TWorkView;
    WVRFeeQuery: TWVRequest;
    Label4: TLabel;
    Label8: TLabel;
    WVRReleaseCard: TWVRequest;
    WVReleaseCard: TWorkView;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    lblMoney: TLabel;
    edtEndDate: TWVEdit;
    Label9: TLabel;
    WVEdit4: TWVEdit;
    WVLabel7: TWVLabel;
    cbbCardType: TWVComboBox;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    grpWater: TGroupBox;
    Label11: TLabel;
    edtWaterMoney: TWVDigitalEdit;
    Label12: TLabel;
    WVLabel3: TWVLabel;
    cbbPhyType: TWVComboBox;
    imgPhoto: TImage;
    WVRWaterPrice: TWVRequest;
    WVWaterPrice: TWorkView;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure cbbCardTypeChange(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
    procedure btnReleaseCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure WVComboBox4Change(Sender: TObject);
  private
    { Private declarations }
    selectSign:Boolean;
    sReturnInfo:string;
    fMoney:Real;

    endGetPhotoSign:Boolean;
    //procedure initCustInsColInfo;
    //procedure getCustInfoValue;

    procedure getFeeResult();
    function judgeValue: Boolean;

    procedure getPhoto;

    //procedure setWaterPrice(wvWater: TWorkView;wvrWater:TWVRequest;feeType:Integer);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhReleaseCard: TfaqhReleaseCard;
  IsBackCard: integer;

implementation

uses KsFrameworks,KSDataDictionary,filetrans, 
  KSClientConsts, SmartCardCommon,DataTypes;

{$R *.DFM}

procedure TfaqhReleaseCard.Init;
var
  filePath:string;
begin
  inherited;
  //initCustInsColInfo;
  cbbCardType.ItemIndex := 0;
  cbbType.ItemIndex := 0;
  cbbPhyType.ItemIndex := 0;
  edtTicketNo.Enabled := False;
  edtWaterMoney.Text := '0';
  if waterIfDef = 0 then
    grpWater.Visible := False
  else
    grpWater.Visible := True;
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    endGetPhotoSign := True;
    filePath := sAppPath+'nophoto.jpg';
    imgPhoto.Picture.LoadFromFile(filePath);
  except

  end;

  try
    if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
      Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
  except
    on e:Exception do
      Context.GetDialogSystem.ShowMessage(e.Message);
  end;

end;

procedure TfaqhReleaseCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhReleaseCard.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
  cardType:Integer;
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  if judgeValue=False then
    if Application.MessageBox('����������ѯ�ٶȿ��ܻ��������ȷ��Ҫ����������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;
  cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  WorkView.FieldByName('�������').Data.SetInteger(cardType);
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  tmpData.Last;
  tmpData.First;
  selectSign := False;
  //Sleep(100);
  //getFeeResult;
end;

procedure TfaqhReleaseCard.getFeeResult();
var
  feeType, cardType,custId: Integer;
  custName:string;
  tmpData:TDataSet;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  try
    tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
    //tmpData.First;
    feeType := tmpData.FieldByName('lvol5').AsInteger;
    custId := tmpData.FieldByName('lvol1').AsInteger;
    custName := tmpData.fieldbyname('sall_name').AsString;
    //sEndDate := tmpData.FieldByName('sdate3').AsString;
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('���Ȳ�ѯ�����ݣ�������Ϣ��'+ex.Message);
      Exit;
    end;
  end;
  WVFeeQuery.FieldByName('�շ����').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('������').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('���ܺ�').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('�ͻ���').Data.SetInteger(custId);
  WVFeeQuery.FieldByName('�Ƿ񲻼�����').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  //ShowMessage('11');
  if WVFeeQuery.FieldByName('������').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('�շ���Ϣ').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('�ܷ���').Data.AsFloat;
    if bjopen=1 then
    begin
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'W');
      bj(bjcomport,'&C11������'+trim(custName)+'$');
      bj(bjcomport,floattostr(fMoney)+'J');
    end;
    if chkSaveMoney.Checked=False then
      edtMoney.Text := floattostr(fMoney);
    edtEndDate.Text := WVFeeQuery.fieldbyname('����Ч��').Data.AsString;
    RzStatusPane1.Caption := sReturnInfo;
    selectSign := True;
  end
  else
  begin
    RzStatusPane1.Caption := WVFeeQuery.fieldbyname('������Ϣ').Data.AsString;
  end;
end;

procedure TfaqhReleaseCard.cbbCardTypeChange(Sender: TObject);
begin
  inherited;
  //getFeeResult;
end;

procedure TfaqhReleaseCard.cbbTypeChange(Sender: TObject);
begin
  if cbbType.ItemIndex=0 then
  begin
    edtTicketNo.Text := '';
    edtTicketNo.Enabled := False;
  end
  else
  begin
    edtTicketNo.Enabled := True;
  end;
end;

procedure TfaqhReleaseCard.btnReleaseCardClick(Sender: TObject);
var
  showCardNo:string;
  pCardID:string;
  custId:Integer;
  cardType:Integer;
  cardPhyType:integer;
  cardSelfType:integer;
  feeType:string;
  tipInfo:string;
  custName:string;
  cardTypeName:string;
  fillMoney:Real;
  reCode : Integer;

  //waterCard:TWATERCOMMPACK;
  cardNo:Integer;
  cardEndDate:string;
  custType:Integer;
  st:Integer;
  rst:integer;
  payCnt,dptCnt:Integer;
  cm:TCM;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ����Ȳ�ѯ��Ȼ���ٽ��в�����');
    Exit;
  end;
  if selectSign=False then
  begin
    Context.GetDialogSystem.ShowMessage('���ȵ���ѡ��һ����¼��Ȼ���ٷ�����');
    exit;
  end;
  if Trim(edtEndDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�����뿨��Ч�ڣ�');
    edtEndDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtEndDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('����Ч���������󣬸�ʽyyyymmdd��');
    edtEndDate.SetFocus;
    Exit;
  end;
  try
    custName := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
    //ȡ�ͻ���
    custId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
  except
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫ���еļ�¼��Ȼ���ٽ��в�����');
    Exit;
  end;
  cardTypeName := Copy(cbbCardType.Text,Pos('-',cbbCardType.Text)+1,Length(cbbCardType.Text));
  tipInfo := '���Ƿ�ȷ��Ҫ��������Ϊ��'+custname+'��,�������'+cardtypename+'���Ŀ���';
  if Application.MessageBox(PChar(tipInfo),PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if relCardJudge=False then
    Exit;
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
  }
  cm := nil;
  try
    cm := tcm.Create;
    rst := cm.card(pCardID);
    if rst<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
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
      
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      //ȡ����ʾ����
      showCardNo:=cm.getShowCardNo;
    end;
  finally
    cm.Destroy;
  end;

  //ȡ���ڲ�����
  try
    cardSelfType := ks_cardtype();
  except
    cardSelfType := 0;
  end;
  {
  //ȡ������
  pCardID := readCardOneInfo(CARD_SERI_NO);
  if pCardID='' then
  begin
    Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
    exit;
  end;
  }
  try
    //��������
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    //����������
    cardPhyType := 0;//StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
  except
    cardType := 0;
    cardPhyType := 0;
  end;
  //�շѷ�ʽ
  feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  WVReleaseCard.FieldByName('����Ա').Data.SetString(Context.ParamData(svOperatorNoName).AsString);
  WVReleaseCard.FieldByName('��ʾ����').Data.SetString(showCardNo);        //
  WVReleaseCard.FieldByName('������').Data.SetString(pCardID);           //
  WVReleaseCard.FieldByName('�շѷ�ʽ').Data.SetInteger(StrToInt(feeType));
  WVReleaseCard.FieldByName('Ʊ�ݺ���').Data.SetString(edtTicketNo.Text);
  WVReleaseCard.FieldByName('��������').Data.SetString(edtEndDate.Text);
  WVReleaseCard.FieldByName('������').Data.SetInteger(cardType);
  WVReleaseCard.FieldByName('����������').Data.SetInteger(cardPhyType);
  WVReleaseCard.FieldByName('���ڲ�����').Data.SetInteger(cardSelfType);
  WVReleaseCard.FieldByName('�ͻ���').Data.SetInteger(custId);
  WVReleaseCard.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
  WVReleaseCard.FieldByName('���Ѵ���').Data.SetInteger(payCnt);
  try
    WVReleaseCard.FieldByName('�շѽ��').Data.SetFloat(StrToFloat(edtMoney.Text));
  except
    Context.GetDialogSystem.ShowMessage('���ֵ����Ϊ�գ������룡');
    edtmoney.SetFocus;
    Exit;
  end;
  WVReleaseCard.FieldByName('�Ƿ񲻼�����').Data.SetString('0');
  WVRReleaseCard.SendCommand;
  if (WVReleaseCard.FieldByName('������').Data.AsInteger = 0) then
  begin
    if waterStrings.Count = 0 then
    begin
      //����ʼ��ˮ�ؿ�
      RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,1,reCode);
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
        }
        //ShowMessage(IntToStr(waterStrings.Count));
        setWaterPrice(WVWaterPrice,WVRWaterPrice,custType);
        st := pubSmlBag(cardno,custId,custType,cardEndDate,pCardID);
        KNG_beep;
        if (st<>0) then
          Context.GetDialogSystem.ShowMessage('ˮ��Ǯ����ʼ��ʧ�ܣ������³�ʼ��ˮ��Ǯ��-'+inttostr(st));
      end;
    end;
  end
  else
  begin
    getReturn('',WVReleaseCard);
    RzStatusPane1.Caption:=WVReleaseCard.FieldByName('������Ϣ').Data.AsString;
  end;
  if bjopen=1 then
  begin
    {
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11������'+trim(custName)+'$');
    bj(bjcomport,'&C21Ӧ��:'+floattostr(fMoney)+'$');
    bj(bjcomport,'&C31ʵ��:'+edtmoney.Text+'$');
    try
      fillMoney := StrToFloat(edtmoney.Text)-fmoney;
      bj(bjcomport,'&C41��ֵ:'+floattostr(fillMoney)+'$');
    except
    end;
    }
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11��  ��:'+trim(custName)+'$');
    bj(bjcomport,'&C21Ӧ  ��:'+floattostr(fMoney)+'?$');
    bj(bjcomport, 'B');    //������Ԥ��
    bj(bjcomport, floattostr(fMoney)+'P');//����������Ǯ
    try
      fillMoney := StrToFloat(edtmoney.Text)-fmoney;
    except
    end;

    bj(bjcomport,'&C31��  ֵ:'+floattostr(fillMoney)+'?$');

    bj(bjcomport, 't'); //�������˻����
    bj(bjcomport, floattostr(fillMoney)+'P');   //����������Ǯ
    bj(bjcomport,'&C41лл'+'X');

  end;
  btnQuery.Click;
end;

procedure TfaqhReleaseCard.GridCellClick(Column: TColumn);
begin
  getFeeResult;
  getPhoto;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhReleaseCard.judgeValue�ж��Ƿ����е�ֵΪ�գ����Ϊ���򷵻�false
  ����:      hanjiwei
  ����:      2008.09.24
  ����:      ��
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function TfaqhReleaseCard.judgeValue: Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to WorkView.FieldCount-1 do
  begin
    if (WorkView.Fields[i].DataType= kdtInteger) or (WorkView.Fields[i].DataType= kdtFloat)  then
    begin
      if WorkView.Fields[i].Data.Value>0 then
        Result := True;
    end;
    if WorkView.Fields[i].DataType= kdtstring then
      if WorkView.Fields[i].Data.Value<>'' then
        Result := True;
  end;

end;

procedure TfaqhReleaseCard.getPhoto;
var
  dFile:string;
  ret:Integer;
  custNo:string;
begin
  if showphoto=0 then
    Exit;
  //��ѯ��Ƭǰ�������ǰ����Ƭ��Ϣ
  imgPhoto.Picture := nil;

  if endGetPhotoSign=false then
    Exit;
  try
    //�Ӻ�̨ȡ����Ƭ�����ƣ���Ƭ��Ϊ�ͻ���
    custNo := Grid.DataSource.DataSet.fieldbyname('lvol1').asstring;
  except
    Context.GetDialogSystem.ShowMessage('����ѡ��һ����¼��Ȼ����ȡ��Ƭ��');
    Exit;
  end;
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

procedure TfaqhReleaseCard.WVComboBox4Change(Sender: TObject);
begin
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  getFeeResult;
end;
{
procedure TfaqhReleaseCard.setWaterPrice(wvWater: TWorkView;wvrWater:TWVRequest;feeType:Integer);
var
  //feeType:Integer;
  tempData:TDataSet;
begin
  //feeType:=wvFee.fieldbyname('�շ����').Data.asinteger;
  wvWater.FieldByName('�շ����').Data.SetInteger(feeType);
  wvWater.FieldByName('������־').Data.SetString('R');
  try
    wvrWater.SendCommand;
    if wvWater.FieldByName('������').Data.AsString<>'0' then
    begin
      cpuWaterPrice1 := 0;
      cpuWaterPrice2 := 0;
      cpuWaterPrice3 := 0;
    end;
    tempData := TDataSet(wvWater.FieldByName('��ѯ�����').Data.AsObject);
    cpuWaterPrice1 := tempData.fieldbyname('lvol0').AsInteger;
    cpuWaterPrice2 := tempData.fieldbyname('lvol1').AsInteger;
    cpuWaterPrice3 := tempData.fieldbyname('lvol2').AsInteger;
  except
    cpuWaterPrice1 := 0;
    cpuWaterPrice2 := 0;
    cpuWaterPrice3 := 0;
  end;
end;
}
initialization
  TUIStdClassFactory.Create('���п�����', TfaqhReleaseCard);

end.


