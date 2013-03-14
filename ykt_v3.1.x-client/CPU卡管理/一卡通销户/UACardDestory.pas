unit UACardDestory;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,LogFile,
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, CardDll,WaterDll,
  RM_Common, RM_Class;

type
  TfaqhCardDestory = class(TfaqhSimpleQueryTemp)
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnRenewCard: TBitBtn;
    WVRCardDestory: TWVRequest;
    WVCardDestory: TWorkView;
    btnReadCardNo: TBitBtn;
    wvrSmlPacket: TWVRequest;
    wvsmlpacket: TWorkView;
    btnReturnSmlBag: TBitBtn;
    chkPrint: TCheckBox;
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVLabel2: TWVLabel;
    Label7: TLabel;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVLabel8: TWVLabel;
    Label5: TLabel;
    Label4: TLabel;
    WVLabel4: TWVLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox3: TWVComboBox;
    WVEdit8: TWVEdit;
    WVComboBox2: TWVComboBox;
    WVComboBox5: TWVComboBox;
    WVEdit5: TWVEdit;
    edtCardNo: TWVEdit;
    WVEdit4: TWVEdit;
    WVComboBox4: TWVComboBox;
    rpt1: TRMReport;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnRenewCardClick(Sender: TObject);
    procedure btnReadCardNoClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnReturnSmlBagClick(Sender: TObject);
  private
    { Private declarations }
    smlCustId:integer;      //小钱包客户号
    smlCardNo:integer;      //小钱包卡号
    smlBal:Real;          //三九小钱包金额

    function readSmlPacket():integer;
    procedure printDestVoucher(rtn,custName,custId,cardNo,stempNO,lastDate,regDate:String);
    {
    function appendSmlSerial(wv:TWorkView;wvRequest:TWVRequest;
      custId:integer;packettype:integer;
      outCardId:integer;inCardId:integer;
      smlMoney:real):integer;
      }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardDestory: TfaqhCardDestory;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardDestory.Init;
begin
  inherited;
  smlCustId:=0;
  smlCardNo:=0;
  smlBal:=0;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhCardDestory.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardDestory.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('钱包号').Data.SetInteger(1);
  inherited;
end;

procedure TfaqhCardDestory.btnRenewCardClick(Sender: TObject);
var
  cardBalance: Integer; //元、分、卡中余额（字符）
  CardID: integer;
  CardState: string;
  CardNo: string;
  cm:TCM;
  //ResInt2,ResInt3: longint;
  patchNo:Integer;//补助批次号
  payCnt,dptCnt:Integer;
  phyid:string;

  tmpData:TDataSet;
  custName:string;
  custType,regDate,stuempNo,custId,rtnInfo:string;
  money:Real;
  totMoney:Real;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  //rtnMoney:string;
  //subsidyNo:Integer;
  st:integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('没有数据，无法进行此操作！');
    Exit;
  end;
  if preReadCard=False then
    Exit;
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  //判断是否是正常卡
  CardState := tmpData.FieldByName('sserial0').AsString;
  CardID := tmpData.FieldByName('lvol0').AsInteger;
  custName := tmpData.fieldbyname('sall_name').AsString;
  custType := GetIdObjectName(-34,tmpData.fieldbyname('lsafe_level2').AsString);
  regDate := tmpData.fieldbyname('sdate1').AsString;
  stuempNo := tmpData.fieldbyname('spager').AsString;
  custId := tmpData.fieldbyname('lvol1').AsString;
  money := tmpData.fieldbyname('damt5').AsFloat;
  //如果是正常卡才去读卡，否则不读卡
  cm := nil;
  try
    cm := TCM.Create;
    if Copy(CardState,1,4) = '1000' then
    begin
      smlBal:=0;
      //判断小钱包金额是否为零，不为零要提示先退小钱包，然后再操作
      if waterStrings.Count>0 then
      begin
        if (readSmlPacket)=0 then
        begin
          if (smlBal>0) then
          begin
            Context.GetDialogSystem.ShowMessage('小钱包金额不为零，请先退小钱包，然后再销户！');
            Exit;
          end;
        end;
      end;
      st := cm.card(phyId);
      if st<>0 then
      begin
        context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡，然后再操作！');
        exit;
      end;
      //先清除所有的读取权限
      cm.clearallfieldreadmode;
      //设置要读取内容的权限
      setOperReadMode(cm);
      if cm.readCard(phyId)<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
        Exit;
      end;

      CardNo := cm.getCardNo;
      if CardNo = '' then
      begin
        Context.GetDialogSystem.ShowMessage('读取卡号错误,请放置好该卡!');
        Exit;
      end;

      //比较卡号是否相符
      if CardID <> StrToInt(CardNo) then
      begin
        Context.GetDialogSystem.ShowMessage('该卡的卡号和所选择记录的卡号不相符，不能进行退卡操作！');
        Exit;
      end;

      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      cardBalance := StrToInt(cm.getCardBalance);
      //AccUseNum:=StrToInt(cm.getCardCnt);
      try
        patchNo := StrToInt(cm.getPatchNo);
      except
        patchNo := 0;
      end;

      WVCardDestory.FieldByName('卡物理编号').Data.SetString(phyId);
      WVCardDestory.FieldByName('卡余额').Data.SetInteger(cardBalance);
      WVCardDestory.FieldByName('卡号').Data.SetInteger(CardID);
      WVCardDestory.FieldByName('交易次数').Data.SetInteger(dptCnt);
      WVCardDestory.FieldByName('充值次数').Data.SetInteger(payCnt);
      WVCardDestory.FieldByName('补助批次号').Data.SetInteger(patchNo);
      WVCardDestory.FieldByName('是否有卡').Data.SetInteger(1);
    end
    else
    begin
      //CardID := tmpData.FieldByName('lvol0').AsInteger;
      WVCardDestory.FieldByName('卡号').Data.SetInteger(CardID);
      WVCardDestory.FieldByName('卡余额').Data.SetInteger(0);
      WVCardDestory.FieldByName('卡物理编号').Data.SetString('');
      WVCardDestory.FieldByName('交易次数').Data.SetInteger(0);
      WVCardDestory.FieldByName('补助批次号').Data.SetInteger(0);
      WVCardDestory.FieldByName('是否有卡').Data.SetInteger(0);
    end;
    WVCardDestory.FieldByName('金额精度').Data.SetInteger(0);
    WVRCardDestory.SendCommand;
    if WVCardDestory.FieldByName('返回码').Data.AsInteger = 0 then
    begin
      if (Copy(CardState,1,4) = '1000') then
      begin
        try
          st := cm.clearCard(WVCardDestory);
          if st=0 then
            cm.beep
          else
          begin
            reSt := ks_geterrmsg(PChar(@reErrMsg));
            Context.GetDialogSystem.ShowMessage('在退卡时没有清空卡信息-'+reSt);
          end;
        except
          on e:Exception do
          begin
            Context.GetDialogSystem.ShowMessage('在退卡时没有清空卡信息'+e.Message);
          end;
        end;
      end
      else
        ConText.GetDialogSystem.ShowWarning('在退卡时没有清空卡信息！');

      if bjopen=1 then
      try
        //tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
        bj(bjcomport,'&Sc$');
        bj(bjcomport,'&C11姓  名：'+trim(custName)+'$');
        bj(bjcomport,'&C21卡余额:'+floattostr(money)+'元$');
        try
          totMoney := WVCardDestory.fieldbyname('退款金额').Data.AsFloat;
        except
          totMoney := money;
        end;
        bj(bjcomport,'&C31共退款:'+floattostr(totMoney)+'元$');
      except
      end;
      rtnInfo := WVCardDestory.FieldByName('返回信息').Data.AsString;
      //rtnMoney := WVCardDestory.fieldbyname('退款金额').Data.AsString;
      Context.GetDialogSystem.ShowMessage(rtnInfo);
      RzStatusPane1.caption:=rtnInfo;
      try
        if chkPrint.Checked then
          printDestVoucher(rtnInfo,custName,custId,IntToStr(CardID),stuempNo,custType,regDate);
      except

      end;
    end
    else
    begin
      getReturn('收回卡失败--',WVCardDestory);
      RzStatusPane1.caption:=WVCardDestory.FieldByName('返回信息').Data.AsString;
    end;
    btnQueryClick(Sender);
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardDestory.btnReadCardNoClick(Sender: TObject);
var
  cardNo:string;
begin
  edtCardNo.Text:='';
  try
    cardNo := readCardOneInfo(CARD_NO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，卡号为零或不存在!');
    Exit;
  end;
  edtCardNo.Text:=cardNo;
  btnQuery.Click();
end;

procedure TfaqhCardDestory.GridCellClick(Column: TColumn);
var
  tmpData:TDataSet;
  custName:string;
  money:Real;
begin
  //inherited;
  if bjopen=1 then
    try
      tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
      custName := tmpData.fieldbyname('sall_name').AsString;
      money := tmpData.fieldbyname('damt5').AsFloat;
      bj(bjcomport,'W');
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'&C11姓  名：'+trim(custName)+'$');
      bj(bjcomport,'&C21卡余额:'+floattostr(money)+'元s$');
    except
    end;
end;

function TfaqhCardDestory.readSmlPacket:integer;
var
  phyId:string;
  st:SmallInt;
  waterPack:TWATERCOMMPACK;
  i:Integer;
  smlbgNo:Integer;
begin
  //读小钱包信息
  st := mfcard(phyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('小钱包寻卡失败！');
    Result := -1;
    Exit;
  end;
  preCommWaterPack(waterPack);
  //读取小钱包金额
  if waterStrings.Count>0 then
  begin
    for i:= 0 to waterStrings.Count-1 do
    begin
      try
        smlbgNo := StrToInt(waterStrings[i]);
      except
        smlbgNo := 0;
      end;
      st := ks_water_readmoney(smlbgNo,@waterpack);
      if st<>0 then
        smlBal := 0
      else
        smlBal := waterPack.money;                 //小钱包金额
      if smlBal>0 then
        Break;
    end;
  end;
  result := 0;
end;

procedure TfaqhCardDestory.btnReturnSmlBagClick(Sender: TObject);
var
  cm:TCM;
  st:Integer;
  phyId,mfPhyid:string;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  CardState:string;
  waterPack:TWATERCOMMPACK;
  cardNo:Integer;
  payCnt,dptCnt,balance:Integer;
  rCardNo:Integer;
  OutMoney: Integer;
  rTradeDate:string;
  rTradeTime:string;
  tp:TTRANSPACK;
  i:Integer;
  smlBagNo:Integer;
  //ifMoney:Integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('没有数据，无法进行此操作！');
    Exit;
  end;
  dptCnt:=0;
  payCnt := 0;
  cardNo := 0;
  balance := 0;
  if preReadCard=False then
    Exit;
  st := -1;
  //判断是否是正常卡
  CardState := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  cm := nil;
  try
    if waterStrings.Count>0 then
    begin
      for i:=0 to waterStrings.Count-1 do
      begin
        try
          smlBagNo := StrToInt(waterStrings[i])
        except
          smlBagNo := 0;
        end;
        cm := TCM.Create;
        if Copy(CardState,1,4) = '1000' then
        begin
          st := cm.card(phyId);
          if st<>0 then
          begin
            context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡，然后再操作！');
            exit;
          end;
          //先清除所有的读取权限
          cm.clearallfieldreadmode;
          //设置要读取内容的权限
          cm.setfieldreadmode(DPT_CARD_CNT);
          cm.setfieldreadmode(PAY_CARD_CNT);
          cm.setfieldreadmode(CARD_NO);
          cm.setfieldreadmode(CARD_BALANCE);
          //setOperReadMode(cm);
          if cm.readCard(phyId)<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
            Exit;
          end;
          try
            dptCnt:=StrToInt(cm.getDptCardCnt);
            payCnt := StrToInt(cm.getPayCardCnt);
            cardNo := StrToInt(cm.getCardNo);
            balance := StrToInt(cm.getCardBalance);
          except
          end;
          wvsmlpacket.FieldByName('终端号').Data.SetInteger(0);
          wvsmlpacket.FieldByName('有无卡标志').Data.SetInteger(1);
          wvsmlpacket.FieldByName('物理卡号').Data.SetString(phyId);
          wvsmlpacket.FieldByName('卡号').Data.SetInteger(cardNo);
          wvsmlpacket.FieldByName('主钱包充值次数').Data.SetInteger(payCnt);
          wvsmlpacket.FieldByName('主钱包消费次数').Data.SetInteger(dptCnt);
          wvsmlpacket.FieldByName('主钱包余额').Data.SetInteger(balance);
          wvsmlpacket.FieldByName('钱包号').Data.SetInteger(smlBagNo);
          //读小钱包信息
          st := mfcard(mfPhyid);
          if st<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('水控钱包寻卡失败--'+inttostr(st));
            Exit;
          end;
          if mfPhyid<>phyId then
          begin
            Context.GetDialogSystem.ShowMessage('请使用同一张卡进行操作--'+inttostr(st));
            Exit;
          end;
          preCommWaterPack(waterPack);
          st := ks_water_readmoney(smlBagNo,@waterpack);
          if st<>0 then
          begin
            reSt := ks_geterrmsg(PChar(@reErrMsg));
            Context.GetDialogSystem.ShowMessage('读取小钱包失败,该钱包已经回收-'+reSt);
            Exit;
          end;
          if waterPack.money=0 then
            Continue;
          wvsmlpacket.FieldByName('小钱包消费次数').Data.SetInteger(0);
          wvsmlpacket.FieldByName('小钱包余额').Data.SetInteger(waterPack.money);
        end
        else
        begin
          cardNo := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
          wvsmlpacket.FieldByName('终端号').Data.SetInteger(0);
          wvsmlpacket.FieldByName('有无卡标志').Data.SetInteger(0);
          wvsmlpacket.FieldByName('物理卡号').Data.SetString('');
          wvsmlpacket.FieldByName('卡号').Data.SetInteger(cardNo);
          wvsmlpacket.FieldByName('主钱包充值次数').Data.SetInteger(0);
          wvsmlpacket.FieldByName('主钱包消费次数').Data.SetInteger(0);
          wvsmlpacket.FieldByName('主钱包余额').Data.SetInteger(0);
          wvsmlpacket.FieldByName('小钱包消费次数').Data.SetInteger(0);
          wvsmlpacket.FieldByName('小钱包余额').Data.SetInteger(0);
          wvsmlpacket.FieldByName('钱包号').Data.SetInteger(smlBagNo);
        end;
        wvrSmlPacket.SendCommand;
        if wvsmlpacket.FieldByName('返回码').Data.AsInteger = 0 then
        begin
          if (Copy(CardState,1,4) = '1000') then
          begin
            //销户成功，设置大钱包金额
            OutMoney := wvsmlpacket.FieldByName('r主钱包余额').Data.AsInteger;
            rCardNo := wvsmlpacket.FieldByName('r卡号').Data.AsInteger;
            rTradeDate := wvsmlpacket.FieldByName('r记账日期').Data.AsString;
            rtradetime := wvsmlpacket.FieldByName('r记账时间').Data.AsString;
            ZeroMemory(@tp,SizeOf(tp));
            //终端交易序列号
            tp.TermSeqno := 1;
            //终端编号
            StrCopy(@tp.Termno,PChar(scSiteNo));
            //交易卡号
            tp.CardNo := rCardNo;
            //物理编号
            StrCopy(@tp.CardPhyID,PChar(phyId));
            //交易日期
            StrCopy(@tp.TransDate,PChar(rTradeDate));
            //交易时间
            StrCopy(@tp.TransTime,PChar(rtradeTime));
            //交易前金额
            tp.BefBalance := balance;
            //交易后金额
            tp.AftBalance := OutMoney;
            //交易前充值次数
            tp.DptCardCnt := dptCnt;
            //交易前消费次数
            tp.PayCardCnt := payCnt;
            //交易前补助次数
            //tp.SubsidyNo := subsidyNo;
            st := ks_water_recyclecard(smlBagNo);
            if st<>0 then
              //Context.GetDialogSystem.ShowMessage('小钱包回收失败-'+inttostr(st))
              WriteLog('小钱包['+inttostr(smlBagNo)+']回收失败-'+inttostr(st),0)
            else
            begin
              st := cm.card(phyId);
              if st<>0 then
              begin
                context.GetDialogSystem.ShowMessage('寻卡失败，请先调整卡余额，然后再销户！');
                exit;
              end;
              //修改设置金额方式
              st := setCardBal(tp,cm,phyId);
              if st<>0 then
              begin

              end;
              cm.beep;
            end;
          end
          else
            WriteLog('小钱包['+inttostr(smlBagNo)+']回收失败-'+inttostr(st),0);
        end
        else
        begin
          Context.GetDialogSystem.ShowMessage(wvsmlpacket.FieldByName('返回信息').Data.AsString);
          Exit;
        end;
      end;
    end;
    Context.GetDialogSystem.ShowMessage('退小钱包完成，可以销户！');
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardDestory.printDestVoucher(rtn,custName,custId,cardNo,stempNO,lastDate,regDate:String);
begin
  try
    //qckrp1.qr
    {
    frmDestCard := TfrmDestCard.Create(nil);
    frmDestCard.qrlblRptTitle.Caption := rptTitle;
    frmDestCard.qrlblPrintDate.Caption := '打印日期:'+formatdatetime('yyyy-mm-dd',Date);
    frmDestCard.qrlblCustNo.Caption := custId;
    frmDestCard.qrlblCardNo.Caption := cardNo;
    frmDestCard.qrlblStuempNo.Caption := stempNO;
    frmDestCard.qrlblCustName.Caption := custName;
    frmDestCard.qrlblRegDate.Caption := regDate;
    frmDestCard.qrlblRMoney.Caption := lastDate;
    //qrmRstInfo.Caption := rtn;
    frmDestCard.qrlblRtn.Caption := rtn;
    frmDestCard.qrlblOperName.Caption := Context.ParamData(svOperatorNameName).AsString;
    //qckrp1.Page.Orientation:= poLandscape;
    frmDestCard.qckrp1.Preview;
    frmDestCard.Destroy;
    }

    rpt1.LoadFromFile(sPreAppPath+'report\销户凭证.rmf');
    rpt1.Dictionary.Variables.AsString['rtnInfo'] := rtn;
    rpt1.Dictionary.Variables.AsString['custName'] := custName;
    rpt1.Dictionary.Variables.AsString['custId'] := custId;
    rpt1.Dictionary.Variables.AsString['cardNo'] := cardNo;
    rpt1.Dictionary.Variables.AsString['stuempNo'] := stempNO;
    rpt1.Dictionary.Variables.AsString['custType'] := lastDate;
    rpt1.Dictionary.Variables.AsString['regDate'] := regDate;
    rpt1.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rpt1.Dictionary.Variables.AsString['operName'] := Context.ParamData(svOperatorNameName).AsString;
    rpt1.DoublePass := True;
    //rpt1.Preview := rmprvwP;
    rpt1.ShowReport;
    
  except
    Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
  end;

end;

initialization
  TUIStdClassFactory.Create('一卡通销户', TfaqhCardDestory);

end.


