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
      Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
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
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  if judgeValue=False then
    if Application.MessageBox('不加条件查询速度可能会很慢，你确定要继续操作吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;
  cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  WorkView.FieldByName('发卡类别').Data.SetInteger(cardType);
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
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
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  try
    tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
    //tmpData.First;
    feeType := tmpData.FieldByName('lvol5').AsInteger;
    custId := tmpData.FieldByName('lvol1').AsInteger;
    custName := tmpData.fieldbyname('sall_name').AsString;
    //sEndDate := tmpData.FieldByName('sdate3').AsString;
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('请先查询出数据，错误信息：'+ex.Message);
      Exit;
    end;
  end;
  WVFeeQuery.FieldByName('收费类别').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('卡类型').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('功能号').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('客户号').Data.SetInteger(custId);
  WVFeeQuery.FieldByName('是否不记名卡').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  //ShowMessage('11');
  if WVFeeQuery.FieldByName('返回码').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('收费信息').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('总费用').Data.AsFloat;
    if bjopen=1 then
    begin
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'W');
      bj(bjcomport,'&C11姓名：'+trim(custName)+'$');
      bj(bjcomport,floattostr(fMoney)+'J');
    end;
    if chkSaveMoney.Checked=False then
      edtMoney.Text := floattostr(fMoney);
    edtEndDate.Text := WVFeeQuery.fieldbyname('卡有效期').Data.AsString;
    RzStatusPane1.Caption := sReturnInfo;
    selectSign := True;
  end
  else
  begin
    RzStatusPane1.Caption := WVFeeQuery.fieldbyname('返回信息').Data.AsString;
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
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，请先查询，然后再进行操作！');
    Exit;
  end;
  if selectSign=False then
  begin
    Context.GetDialogSystem.ShowMessage('请先单击选择一条记录，然后再发卡！');
    exit;
  end;
  if Trim(edtEndDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入卡有效期！');
    edtEndDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtEndDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('卡有效期输入有误，格式yyyymmdd！');
    edtEndDate.SetFocus;
    Exit;
  end;
  try
    custName := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
    //取客户号
    custId := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
  except
    Context.GetDialogSystem.ShowMessage('请先选中要发行的记录，然后再进行操作！');
    Exit;
  end;
  cardTypeName := Copy(cbbCardType.Text,Pos('-',cbbCardType.Text)+1,Length(cbbCardType.Text));
  tipInfo := '你是否确定要发行姓名为【'+custname+'】,发卡类别【'+cardtypename+'】的卡？';
  if Application.MessageBox(PChar(tipInfo),PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if relCardJudge=False then
    Exit;
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
  }
  cm := nil;
  try
    cm := tcm.Create;
    rst := cm.card(pCardID);
    if rst<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
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
      
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      //取得显示卡号
      showCardNo:=cm.getShowCardNo;
    end;
  finally
    cm.Destroy;
  end;

  //取卡内部编码
  try
    cardSelfType := ks_cardtype();
  except
    cardSelfType := 0;
  end;
  {
  //取物理卡号
  pCardID := readCardOneInfo(CARD_SERI_NO);
  if pCardID='' then
  begin
    Context.GetDialogSystem.ShowMessage('读卡序列号失败，请重新把卡放置到读写器上！');
    exit;
  end;
  }
  try
    //发卡类型
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    //卡物理类型
    cardPhyType := 0;//StrToInt(Copy(cbbPhyType.Text,1,Pos('-',cbbPhyType.Text)-1));
  except
    cardType := 0;
    cardPhyType := 0;
  end;
  //收费方式
  feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  WVReleaseCard.FieldByName('操作员').Data.SetString(Context.ParamData(svOperatorNoName).AsString);
  WVReleaseCard.FieldByName('显示卡号').Data.SetString(showCardNo);        //
  WVReleaseCard.FieldByName('物理卡号').Data.SetString(pCardID);           //
  WVReleaseCard.FieldByName('收费方式').Data.SetInteger(StrToInt(feeType));
  WVReleaseCard.FieldByName('票据号码').Data.SetString(edtTicketNo.Text);
  WVReleaseCard.FieldByName('到期日期').Data.SetString(edtEndDate.Text);
  WVReleaseCard.FieldByName('卡类型').Data.SetInteger(cardType);
  WVReleaseCard.FieldByName('卡物理类型').Data.SetInteger(cardPhyType);
  WVReleaseCard.FieldByName('卡内部编码').Data.SetInteger(cardSelfType);
  WVReleaseCard.FieldByName('客户号').Data.SetInteger(custId);
  WVReleaseCard.FieldByName('充值次数').Data.SetInteger(dptCnt);
  WVReleaseCard.FieldByName('消费次数').Data.SetInteger(payCnt);
  try
    WVReleaseCard.FieldByName('收费金额').Data.SetFloat(StrToFloat(edtMoney.Text));
  except
    Context.GetDialogSystem.ShowMessage('金额值不能为空，请输入！');
    edtmoney.SetFocus;
    Exit;
  end;
  WVReleaseCard.FieldByName('是否不记名卡').Data.SetString('0');
  WVRReleaseCard.SendCommand;
  if (WVReleaseCard.FieldByName('返回码').Data.AsInteger = 0) then
  begin
    if waterStrings.Count = 0 then
    begin
      //不初始化水控卡
      RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,1,reCode);
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
          Context.GetDialogSystem.ShowMessage('水控钱包初始化失败，请重新初始化水控钱包-'+inttostr(st));
      end;
    end;
  end
  else
  begin
    getReturn('',WVReleaseCard);
    RzStatusPane1.Caption:=WVReleaseCard.FieldByName('返回信息').Data.AsString;
  end;
  if bjopen=1 then
  begin
    {
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11姓名：'+trim(custName)+'$');
    bj(bjcomport,'&C21应收:'+floattostr(fMoney)+'$');
    bj(bjcomport,'&C31实收:'+edtmoney.Text+'$');
    try
      fillMoney := StrToFloat(edtmoney.Text)-fmoney;
      bj(bjcomport,'&C41充值:'+floattostr(fillMoney)+'$');
    except
    end;
    }
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11姓  名:'+trim(custName)+'$');
    bj(bjcomport,'&C21应  收:'+floattostr(fMoney)+'?$');
    bj(bjcomport, 'B');    //发声，预收
    bj(bjcomport, floattostr(fMoney)+'P');//发声，多少钱
    try
      fillMoney := StrToFloat(edtmoney.Text)-fmoney;
    except
    end;

    bj(bjcomport,'&C31充  值:'+floattostr(fillMoney)+'?$');

    bj(bjcomport, 't'); //发声，账户余额
    bj(bjcomport, floattostr(fillMoney)+'P');   //发声，多少钱
    bj(bjcomport,'&C41谢谢'+'X');

  end;
  btnQuery.Click;
end;

procedure TfaqhReleaseCard.GridCellClick(Column: TColumn);
begin
  getFeeResult;
  getPhoto;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhReleaseCard.judgeValue判断是否所有的值为空，如果为空则返回false
  作者:      hanjiwei
  日期:      2008.09.24
  参数:      无
  返回值:    Boolean
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
  //查询照片前先清空以前的照片信息
  imgPhoto.Picture := nil;

  if endGetPhotoSign=false then
    Exit;
  try
    //从后台取得照片的名称，照片名为客户号
    custNo := Grid.DataSource.DataSet.fieldbyname('lvol1').asstring;
  except
    Context.GetDialogSystem.ShowMessage('请先选择一条记录，然后再取照片！');
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

procedure TfaqhReleaseCard.WVComboBox4Change(Sender: TObject);
begin
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  getFeeResult;
end;
{
procedure TfaqhReleaseCard.setWaterPrice(wvWater: TWorkView;wvrWater:TWVRequest;feeType:Integer);
var
  //feeType:Integer;
  tempData:TDataSet;
begin
  //feeType:=wvFee.fieldbyname('收费类别').Data.asinteger;
  wvWater.FieldByName('收费类别').Data.SetInteger(feeType);
  wvWater.FieldByName('操作标志').Data.SetString('R');
  try
    wvrWater.SendCommand;
    if wvWater.FieldByName('返回码').Data.AsString<>'0' then
    begin
      cpuWaterPrice1 := 0;
      cpuWaterPrice2 := 0;
      cpuWaterPrice3 := 0;
    end;
    tempData := TDataSet(wvWater.FieldByName('查询结果集').Data.AsObject);
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
  TUIStdClassFactory.Create('发行卡操作', TfaqhReleaseCard);

end.


