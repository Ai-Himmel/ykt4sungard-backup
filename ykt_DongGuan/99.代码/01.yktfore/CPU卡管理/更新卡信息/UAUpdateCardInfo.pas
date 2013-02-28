unit UAUpdateCardInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, WVCommands, RzStatus, RzPanel, RzEdit, RzButton, RzRadChk,
  Buttons, UIncrementComboBox,CardDll;

type
  TfaqhUpdateCardInfo = class(TfaqhSimpleQueryTemp)
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnReadCardQuery: TBitBtn;
    btnOK: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    grpCardInfo: TGroupBox;
    rzstspn1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    RzStatusPane9: TRzStatusPane;
    RzStatusPane20: TRzStatusPane;
    RzStatusPane21: TRzStatusPane;
    RzStatusPane22: TRzStatusPane;
    RzStatusPane23: TRzStatusPane;
    RzStatusPane28: TRzStatusPane;
    edtcCardNo: TRzEdit;
    edtcPhyId: TRzEdit;
    edtcStuempNo: TRzEdit;
    edtcShowNo: TRzEdit;
    edtcBalance: TRzEdit;
    edtcIdCard: TRzEdit;
    edtcName: TRzEdit;
    edtcEndDate: TRzEdit;
    edtCCustType: TRzEdit;
    edtCFeeType: TRzEdit;
    edtCDept: TRzEdit;
    edtCSex: TRzEdit;
    edtCardDptNum: TRzEdit;
    grpLibInfo: TGroupBox;
    RzStatusPane11: TRzStatusPane;
    RzStatusPane12: TRzStatusPane;
    RzStatusPane13: TRzStatusPane;
    RzStatusPane14: TRzStatusPane;
    RzStatusPane15: TRzStatusPane;
    RzStatusPane16: TRzStatusPane;
    RzStatusPane17: TRzStatusPane;
    RzStatusPane18: TRzStatusPane;
    RzStatusPane24: TRzStatusPane;
    RzStatusPane25: TRzStatusPane;
    RzStatusPane26: TRzStatusPane;
    RzStatusPane27: TRzStatusPane;
    RzStatusPane19: TRzStatusPane;
    RzStatusPane29: TRzStatusPane;
    edtCardNo: TRzEdit;
    edtPhyID: TRzEdit;
    edtNo: TRzEdit;
    edtIDCard: TRzEdit;
    edtBalance: TRzEdit;
    edtShowCardNo: TRzEdit;
    edtName: TRzEdit;
    edtEndDate: TRzEdit;
    edtCustType: TRzEdit;
    edtFeeType: TRzEdit;
    edtDept: TRzEdit;
    edtSex: TRzEdit;
    cbbRType: TWVComboBox;
    edtDptCnt: TRzEdit;
    RzStatusPane10: TRzStatusPane;
    edtCPatchNo: TRzEdit;
    RzStatusPane30: TRzStatusPane;
    edtPatchNo: TRzEdit;
    RzStatusPane31: TRzStatusPane;
    edtMaxcPerCount: TRzEdit;
    RzStatusPane32: TRzStatusPane;
    edtcMaxPerDay: TRzEdit;
    edtMaxPercount: TRzEdit;
    RzStatusPane33: TRzStatusPane;
    RzStatusPane34: TRzStatusPane;
    edtMaxPerDay: TRzEdit;
    rzstspn2: TRzStatusPane;
    edtCCertType: TRzEdit;
    rzstspn3: TRzStatusPane;
    edtCertType: TRzEdit;
    rzstspn4: TRzStatusPane;
    edtCPayCnt: TRzEdit;
    rzstspn5: TRzStatusPane;
    edtPayCnt: TRzEdit;
    imgPhoto: TImage;
    procedure btnOKClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure edtShowCardNoKeyPress(Sender: TObject; var Key: Char);
    procedure cbbRTypeChange(Sender: TObject);
  private
    tempPCardID:string;
    { Private declarations }
    custNo:string;
    endGetPhotoSign:Boolean;
    Function readCardInfo:Boolean;
    procedure edtEnabledT;                    //使编辑框为可用
    procedure resultQuery;                    //查询结果
    procedure clearEdt;                       //清空编辑框内容
    procedure getPhoto;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhUpdateCardInfo: TfaqhUpdateCardInfo;
  CardID: string;

implementation

uses KsFrameworks, KSClientConsts,KSDataDictionary,SmartCardCommon,filetrans;

{$R *.DFM}

procedure TfaqhUpdateCardInfo.Init;
begin
  inherited;
  btnok.Enabled := false;
  cbbRType.ItemIndex :=0;
  edtEndDate.Enabled := False;
  edtMaxPerDay.Enabled := True;
  edtMaxPercount.Enabled := True;
  try
    KSG_uninit;
    KSG_init(PChar(scIp),scPort,scFuncNo);
    endGetPhotoSign := True;
    //filePath := sAppPath+'nophoto.jpg';
    imgPhoto.Picture.LoadFromFile(sAppPath+'nophoto.jpg');
  except

  end;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhUpdateCardInfo.btnOKClick(Sender: TObject);
var
  PCardID: string;
  CardNo:Integer;           //交易卡号
  showCardNo:string;        //显示卡号
  cardEndDate:string;       //卡使用截至日期
  feeType:Integer;          //收费类别
  custType:Integer;         //客户类别
  custName:string;          //客户姓名
  IDCard:string;            //身份证号
  deptNo:string;             //部门代码
  sex:string;               //性别
  stuempNo:string;          //学工号
  cardBalance:Integer;      //卡余额
  cardpwd:string;           //卡密码
  cardTradeNum:Integer;     //卡交易次数
  patchNO:Integer;          //补助批次号
  certType:string;          //证件类型
  maxPerCount:Integer;
  maxPerDay:Integer;
  tradeDate,tradeTime:string;

  cm: TCM;
  cardmoney:LongInt;
  payCnt,dptCnt,subsidyNo:Integer;
  st,stPNo:LongInt;
  rType:string;
  Tof:Integer;
  reError:array[0..128] of char;
  function setCardBalance: Integer;
  var
    tp:TTRANSPACK;
  begin
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //设置卡余额
    //终端交易序列号
    tp.TermSeqno := 1;
    //终端编号
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //交易卡号
    tp.CardNo := CardNo;
    //物理编号
    StrCopy(@tp.CardPhyID,PChar(PCardID));
    //交易日期
    StrCopy(@tp.TransDate,PChar(tradeDate));
    //交易时间
    StrCopy(@tp.TransTime,PChar(tradeTime));
    //交易后金额
    tp.AftBalance := cardBalance;
    //交易前金额
    tp.BefBalance := cardmoney;
    //交易前充值次数
    tp.DptCardCnt := dptCnt;
    //交易前消费次数
    tp.PayCardCnt := payCnt;
    //交易前补助次数
    tp.SubsidyNo := subsidyNo;

    Result := ks_setcardbal(@tp);
  end;
begin
  if not preReadCard then
    Exit;
  cm := nil;
  try
    //重新读取物理卡号，判断是否和要更新的物理卡号一致
    cm := TCM.Create;
    st := cm.card(PCardID);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    cm.readCard(PCardID);
    //PCardID := cm.getCardSeriNo;
    if PCardID<>trim(tempPCardID) then
    begin
      Context.GetDialogSystem.ShowMessage('更新时请使用同一张卡！');
      Exit;
    end;

    rType := Copy(cbbRType.Text,1,Pos('-',cbbRType.Text)-1);
    if (rType='') or (rType='-') then
    begin
      Context.GetDialogSystem.ShowMessage('请选择更新类型！');
      cbbRType.SetFocus;
      Exit;
    end;

    try
      cardmoney := StrToInt(cm.getCardBalance);
      payCnt := StrToInt(cm.getPayCardCnt);
      dptCnt := StrToInt(cm.getDptCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);

    except
      cardmoney := 0;
      payCnt := 0;
      dptCnt := 0;
      subsidyNo := 0;
      RzStatusPane1.Caption :='读取卡信息失败！';
    end;

    WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('物理卡号').Data.Setstring(PCardID);
    WorkView.FieldByName('卡到期日期').Data.Setstring(edtEndDate.text);
    WorkView.FieldByName('卡余额').Data.SetInteger(cardmoney);
    WorkView.FieldByName('交易次数').Data.SetInteger(payCnt);
    WorkView.FieldByName('充值次数').Data.SetInteger(dptCnt);
    WorkView.FieldByName('更新类型').Data.Setstring(rType);
    if maxPer=1 then
    begin
      try
        WorkView.FieldByName('入单次限额').Data.SetFloat(StrToFloat(edtMaxPercount.text));
        WorkView.FieldByName('入日限额').Data.SetFloat(StrToFloat(edtMaxPerDay.Text));
      except
        Context.GetDialogSystem.ShowMessage('请输入有效的单次限额和日限额！');
        Exit;
      end;
    end
    else
    begin
      WorkView.FieldByName('单次限额').Data.SetInteger(0);
      WorkView.FieldByName('日限额').Data.SetInteger(0);
    end;
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger=0 then
    begin
      CardNo:=WorkView.fieldbyname('卡号').Data.AsInteger;
      showCardNo:=WorkView.fieldbyname('显示卡号').Data.AsString;
      cardEndDate:=WorkView.fieldbyname('卡到期日期').Data.AsString;
      feeType:=WorkView.fieldbyname('收费类别').Data.AsInteger;
      custType:=WorkView.fieldbyname('客户类别').Data.AsInteger;
      custName:=WorkView.fieldbyname('姓名').Data.AsString;
      certType:=WorkView.fieldbyname('证件类型').Data.AsString;
      IDCard:=WorkView.fieldbyname('证件号码').Data.AsString;
      deptNo:=WorkView.fieldbyname('部门代码').Data.AsString;
      sex:=WorkView.fieldbyname('性别').Data.AsString;
      stuempNo:=WorkView.fieldbyname('学工号').Data.AsString;
      cardBalance:=WorkView.fieldbyname('卡余额').Data.AsInteger;
      //isFormation := Char('N');
      cardTradeNum := WorkView.fieldbyname('交易次数').Data.AsInteger;
      patchNO  := WorkView.fieldbyname('补助批次号').Data.AsInteger;
      cardpwd := WorkView.fieldbyname('卡密码').Data.AsString;
      tradeDate:=WorkView.fieldbyname('交易日期').Data.AsString;
      tradeTime:=WorkView.fieldbyname('交易时间').Data.AsString;
      if rType='1' then
      begin
        cm.clearallfieldwritemode;
        //setOperWriteMode(cm);
        cm.setCardNo(IntToStr(CardNo));
        cm.setShowCardNo(showCardNo);
        cm.setDeadLineDate(cardEndDate);
        cm.setCardLimitType(IntToStr(feeType));
        cm.setCustType(IntToStr(custType));
        cm.setCertType(certType);
        cm.setCertNo(IDCard);
        cm.setDeptNo(deptNo);
        cm.setCustSex(sex);
        cm.setStuempNo(stuempNo);
        cm.setCustName(custName);
        //cm.setBlackCardSign(IntToStr(NORMAL_CARD));

        //st := CardManage.UpdateCardBasicInfo(PCM);
        //设置单次消费限额和日消费限额
        if maxper=1 then
        begin
          maxPerCount := WorkView.fieldbyname('单次限额').Data.AsInteger;
          maxPerDay := WorkView.fieldbyname('日限额').Data.AsInteger;
          cm.setMaxPerCount(IntToStr(maxPerCount));
          cm.setMaxPerDay(IntToStr(maxPerDay));
          //rst := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
        end;
        st := cm.writeData(PCardID);
        //tof := setcardbalance;
        if (st<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('更新卡信息失败--'+ks_geterrmsg(PChar(@reError)));
          exit;
        end;
      end
      else if rType='2' then  //更新有效期
      begin
        cm.clearallfieldwritemode;
        cm.setfieldwritemode(DEADLINE_DATE);
        cm.setDeadLineDate(cardEndDate);
        st := cm.writeData(PCardID);
        if (st<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('更新卡有效期失败--'+inttostr(st));
          exit;
        end;
      end
      else if rType='3' then  //更新卡余额，补助批次号
      begin
        cm.clearallfieldwritemode;
        cm.setfieldwritemode(CARD_CNT);
        cm.setCardCnt(IntToStr(cardTradeNum));
        cm.setPatchNo(IntToStr(patchNO));
        st := cm.writeData(PCardID);
        tof := setcardbalance;
        if (st<>0)or(Tof<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('更新卡余额失败--'+inttostr(st));
          exit;
        end;
        if stPNo<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('更新卡补助批次号失败--'+inttostr(st));
          exit;
        end;
      end
      else if rType='4' then  //重写卡信息
      begin
        cm.clearallfieldwritemode;
        setOperWriteMode(cm);

        cm.setCardNo(IntToStr(CardNo));
        cm.setShowCardNo(showCardNo);
        cm.setDeadLineDate(cardEndDate);
        cm.setCardLimitType(IntToStr(feeType));
        cm.setCustType(IntToStr(custType));
        cm.setCertType(certType);
        cm.setCertNo(IDCard);
        cm.setDeptNo(deptNo);
        cm.setCustSex(sex);
        cm.setStuempNo(stuempNo);
        cm.setPatchNo(IntToStr(patchNO));
        cm.setCustName(custName);
        st := cm.writeData(PCardID);
        tof := setcardbalance;
        if (st<>0)or(Tof<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('重写卡余额失败，请执行更新类型为4的操作--'+inttostr(st));
          exit;
        end;
        if stPNo<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('重写卡基本信息失败,请重写--'+inttostr(st));
          exit;
        end;

      end
      else if rType='5' then  //清空卡信息
      begin
        {st := cm.clearCard;
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('清空卡信息失败--'+inttostr(st));
          Exit;
        end;}
        Context.GetDialogSystem.ShowMessage('没有清空卡信息功能！');
        Exit;
      end;
      cm.beep;
      clearEdt;
      imgPhoto.Picture.Assign(nil);
      Context.GetDialogSystem.ShowSuccess('更新卡信息成功！');
    end
    else
    begin
      getreturn('',workview1);
    end;
  finally
    btnok.Enabled := false;
    cm.Destroy;
  end;
end;

procedure TfaqhUpdateCardInfo.btnReadCardQueryClick(Sender: TObject);
begin
  clearEdt;  
  if preReadCard=False then
    Exit;
  if readCardInfo=False then
    Exit;
  custNo := '';
  //getInMoney;
  WorkView1.FieldByName('卡号').Data.SetInteger(0);
  WorkView1.FieldByName('客户号').Data.SetInteger(0);
  WorkView1.FieldByName('客户类别').Data.SetInteger(0);
  WorkView1.FieldByName('收费类别').Data.SetInteger(0);
  WorkView1.FieldByName('钱包号').Data.SetInteger(0);
  WorkView1.FieldByName('物理卡号').Data.SetString(edtcPhyId.Text);
  WVRequest1.SendCommand;
  if WorkView1.fieldbyname('返回码').data.AsInteger<>0 then
  begin
    getreturn('',WorkView1);
    exit;
  end;
  resultQuery;
  getPhoto;
  edtEnabledT;
  btnok.enabled := true;
end;

Function TfaqhUpdateCardInfo.readCardInfo():Boolean;
var
  cm: TCM;
  phycardid,cardNo:string;
  st:integer;
  //maxPerCount,maxPerDay:Integer;
begin
  Result := True;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phycardid);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      Result := False;
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    if cm.readCard(phycardid)<>0 then
    begin
      context.GetDialogSystem.ShowMessage('读取卡信息失败，请重试！');
      Result := False;
      Exit;
    end;
    {
    phycardid := cm.getCardSeriNo;
    if phycardid='' then
    begin
      context.GetDialogSystem.ShowMessage('读物理卡号失败，该卡已经损坏！');
      Result:=False;
      Exit;
    end;
    }
    //读取交易卡号
    cardNo := cm.getCardNo;
    if cardNo = '' then
      RzStatusPane1.Caption := '读取交易卡号失败！'
    else
      edtcCardNo.Text := cardNo;
    tempPCardID := phycardid;
    //姓名
    edtcName.Text := cm.getCustName;
    //物理卡号
    edtcPhyId.Text := phycardid;
    //证件类型
    edtcCertType.Text := cm.getCertType;
    //证件号码
    edtcIdCard.Text := cm.getCertNo;
    //学工号
    edtcStuempNo.Text := cm.getStuempNo;
    //截至日期
    edtcEndDate.Text := cm.getDeadLineDate;
    //显示卡号
    edtcShowNo.Text := cm.getShowCardNo;
    //收费类别
    edtcFeeType.Text := GetIdObjectName(-43,Trim(cm.getCardLimitType));
    //客户类别
    edtCCustType.Text := GetIdObjectName(-34,Trim(cm.getCustType));
    //部门
    edtCDept.Text := GetIdObjectName(-22,Trim(cm.getDeptNo));
    //性别
    edtCSex.Text := GetIdObjectName(39,Trim(cm.getCustSex));

    edtcBalance.Text := format('%f', [strtoint(cm.getCardBalance) / 100.0]);
    edtCardDptNum.Text := cm.getDptCardCnt;
    edtCPayCnt.Text := cm.getPayCardCnt;
    edtCPatchNo.Text := cm.getPatchNo;
    if maxPer=1 then
    begin
      edtMaxcPerCount.Text := FloatToStr(StrToFloat(cm.getMaxPerCount)/100);
      edtcMaxPerDay.Text := FloatToStr(StrToFloat(cm.getMaxPerDay)/100);
    end
    else
    begin
      edtMaxcPerCount.Text := '无';
      edtcMaxPerDay.Text := '无';
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhUpdateCardInfo.edtEnabledT;
begin
  //edtEndDate.Enabled:=True;
  edtEndDate.Color:=clwhite;
end;

procedure TfaqhUpdateCardInfo.resultQuery;
var
  tempDataSet: TDataSet;
begin
  try
    tempDataSet := WorkView1.FieldByName('查询结果集').Data.AsObject as TDataSet;
    //客户号
    custNo := tempDataSet.FieldByName('lvol1').AsString;
    //交易卡号
    edtCardNo.Text := tempDataSet.FieldByName('lvol0').AsString;
    //卡使用截止日期
    edtEndDate.Text := tempDataSet.FieldByName('sdate2').AsString;
    //姓名
    edtName.Text := tempDataSet.FieldByName('sall_name').AsString;
    //证件类型
    edtCertType.Text := tempDataSet.FieldByName('smarket_code').AsString;
    //证件号码
    edtIDCard.Text := tempDataSet.FieldByName('semail2').AsString;
    //学工号
    edtNo.Text := tempDataSet.FieldByName('spager').AsString;
    //显示卡号
    edtShowCardNo.Text := tempDataSet.FieldByName('sorder0').AsString;
    //卡余额
    edtBalance.Text := tempDataSet.FieldByName('damt5').AsString;
    //物理编号
    edtPhyID.Text := tempDataSet.FieldByName('sstation1').AsString;
    //客户类别
    edtCustType.Text:= GetIdObjectName(-34,tempDataSet.FieldByName('lsafe_level2').AsString);
    //收费类别
    edtFeeType.Text:=GetIdObjectName(-43,tempDataSet.FieldByName('lvol5').AsString);
    //部门编号
    edtDept.Text := GetIdObjectName(-22,tempDataSet.FieldByName('scert_no').AsString);
    //性别
    edtSex.Text := GetIdObjectName(39,tempDataSet.FieldByName('smarket_code2').AsString);
    //物理卡号
    edtPhyID.Text := tempDataSet.fieldbyname('sstation1').AsString;
    //充值次数
    edtDptCnt.Text := tempDataSet.fieldbyname('lvol7').AsString;
    //消费次数
    edtPayCnt.Text := tempDataSet.fieldbyname('lvol8').AsString;
    //补助批次号
    edtPatchNo.Text :=  tempDataSet.fieldbyname('lvol10').AsString;
    if maxPer=1 then
    begin
      //日限额
      edtMaxPerDay.Text :=  tempDataSet.fieldbyname('damt12').AsString;
      //单次限额
      edtMaxPercount.Text :=  tempDataSet.fieldbyname('damt11').AsString;
    end
    else
    begin
      edtMaxPerCount.Text := '无';
      edtMaxPerDay.Text := '无';
    end;
  except
    on ex:Exception do
      context.GetDialogSystem.ShowMessage(ex.Message);
  end;
end;

procedure TfaqhUpdateCardInfo.clearEdt;
var
  i:Integer;
begin
  for i := 0 to grpCardInfo.ControlCount-1 do
  begin
    if grpCardInfo.Controls[i] is TRzEdit then
      TRzEdit(grpCardInfo.Controls[i]).Text := '';
  end;
  for i := 0 to grpLibInfo.ControlCount-1 do
  begin
    if grpLibInfo.Controls[i] is TRzEdit then
      TRzEdit(grpLibInfo.Controls[i]).Text := '';
  end;
end;

procedure TfaqhUpdateCardInfo.edtShowCardNoKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;
end;

procedure TfaqhUpdateCardInfo.cbbRTypeChange(Sender: TObject);
var
  rType:string;
begin
  rType := Copy(cbbRType.Text,1,Pos('-',cbbRType.Text)-1);
  if rType='1' then
  begin
    if maxPer=1 then
    begin
      edtMaxPerCount.Enabled := True;
      edtMaxPerDay.Enabled := True;
    end;
  end
  else
  begin
      edtMaxPerCount.Enabled := False;
      edtMaxPerDay.Enabled := False;
  end;
  if rType='2' then
    edtEndDate.Enabled := True
  else
    edtEndDate.Enabled := False;
end;

procedure TfaqhUpdateCardInfo.getPhoto;
var
  dFile:string;
  ret:Integer;
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
  TUIStdClassFactory.Create('卡信息更新', TfaqhUpdateCardInfo);

end.
