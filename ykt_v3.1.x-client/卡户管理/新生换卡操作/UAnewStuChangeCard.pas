unit UAnewStuChangeCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzStatus, RzPanel, Buttons, UtCardDll, UIncrementComboBox;

type
  TfaqhnewStuChangeCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnReadCardQuery: TBitBtn;
    btnPatchCard: TBitBtn;
    grp1: TGroupBox;
    lbl1: TLabel;
    edtEndDate: TWVEdit;
    Label1: TLabel;
    edtCustNo: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVLabel6: TWVLabel;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    WVEdit4: TWVEdit;
    WVLabel9: TWVLabel;
    Label5: TLabel;
    WVEdit5: TWVEdit;
    WVComboBox2: TWVComboBox;
    WVLabel1: TWVLabel;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    WVEdit2: TWVEdit;
    Label2: TLabel;
    Label7: TLabel;
    WVLabel5: TWVLabel;
    WVLabel8: TWVLabel;
    Label6: TLabel;
    edtCardNo: TWVEdit;
    WVComboBox5: TWVComboBox;
    WVComboBox6: TWVComboBox;
    WVEdit8: TWVEdit;
    WorkViewOK: TWorkView;
    WVRequestOK: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnPrintClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure btnPatchCardClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure edtShowCardKeyPress(Sender: TObject; var Key: Char);
  private
    PCM: TPublishCardMes;
    { Private declarations }
    //operType,oPhyId,nPhyId,nShowCardNo,nEndDate,operDate:string;
    //oCardNo,oCardBalance,oTradeNum,seriNo,stationId:integer

    //procedure setWVvalues(operType,oPhyId,nPhyId,nShowCardNo,nEndDate,operDate:string;
    //  oCardNo,oCardBalance,oTradeNum,seriNo,stationId:integer);
    procedure replaceNewCard(phyCardId:string;cardNo:Integer;operType:string);//更换新生卡信息
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhnewStuChangeCard: TfaqhnewStuChangeCard;

implementation

uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaqhnewStuChangeCard.Init;
begin
  inherited;
  edtEndDate.Text:=FormatDateTime('yyyymmdd',Date()+1461);
  {
  btnQuery.Caption:='条件查询';
  btnPrint.Caption:='换 卡';
  btnReadCardQuery.Caption:='读卡查询';
  btnPatchCard.Caption:='新生卡补写';
  }
end;

procedure TfaqhnewStuChangeCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhnewStuChangeCard.btnPrintClick(Sender: TObject);
var
  nPacketNo: smallint;
  LPI: LOOPPURSEINFO;
  cardManage:TCardManage;
  Tof:Boolean;

  //读卡信息
  rmoney:Integer;
  rTrade:Integer;
  rPatchNo:Integer;
  PCardId:string;

  cardNo:string;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('没有数据，无法进行此操作！');
    Exit;
  end;

  //读卡获得相关信息
  cardManage := nil;
  try
    cardManage:=TCardManage.Create();
    //取物理卡号
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡序列号失败，请重新把卡放置到读写器上！');
      exit;
    end;

    TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo); //读卡中消费信息
    if TOF = false then
    begin
      Context.GetDialogSystem.ShowWarning('读用户卡消费信息失败！');
      Exit;
    end
    else
    begin
      rmoney:=LPI.RemainMoney;
      rTrade:=LPI.DealTimes;
      rPatchNo := LPI.DealTimes_CurDay;
    end;
    //老卡的卡号
    cardNo:=readCardNo;

    //清空前先给后台发送清除卡信息消息，发送成功后再情况卡信息 847122
    WorkViewOK.FieldByName('操作类型').Data.SetString('S');

    WorkViewOK.FieldByName('原卡号').Data.SetInteger(StrToInt((cardNo)));
    WorkViewOK.FieldByName('原物理编号').Data.SetString(PCardID);
    WorkViewOK.FieldByName('原卡余额').Data.SetInteger(rmoney);
    WorkViewOK.FieldByName('原卡交易次数').Data.SetInteger(rTrade);
    WorkViewOK.FieldByName('补助批次号').Data.SetInteger(rPatchNo);

    WorkViewOK.FieldByName('新卡物理编号').Data.SetString('');
    WorkViewOK.FieldByName('显示卡号').Data.SetString('');
    WorkViewOK.FieldByName('到期日期').Data.SetString('');
    
    WorkViewOK.FieldByName('业务日期').Data.SetString('');
    WorkViewOK.FieldByName('流水号').Data.SetInteger(0);
    WorkViewOK.FieldByName('终端编号').Data.SetInteger(0);
    //operType,oPhyId,nPhyId,nShowCardNo,nEndDate,operDate:string;
    //oCardNo,oCardBalance,oTradeNum,seriNo,stationId:integer
    WVRequestOK.SendCommand;
    if WorkViewOK.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      getReturn('清空卡失败--',WorkViewOK);
      RzStatusPane1.Caption:=WorkViewOK.FieldByName('返回信息').Data.AsString;
      Exit;
    end;
    //清空新生临时卡信息，清除成功后把信息送到后台，后台把清空该卡标志写上
    if cardManage.ClearCard<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('旧卡内容已清除失败，请检查该卡是否可用！');
      Exit;
    end
    else
    begin
      cardManage.ControlBuzzer;
      Context.GetDialogSystem.ShowMessage('旧卡内容已清除成功，请先把要更换的卡放置好！');

      //开始把卡信息写到新卡上去
      replaceNewCard(PCardID,StrToInt(cardNo),'C');
    end;
  finally
    cardManage.Destroy;
  end;
end;

procedure TfaqhnewStuChangeCard.btnReadCardQueryClick(Sender: TObject);
begin
  //FCurrentCardNo := readCardNo;
  edtCardNo.Text:= readCardNo;
  btnQueryClick(Sender);
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhnewStuChangeCard.replaceNewCard更换新生卡信息
  作者:      Administrator
  日期:      2005.07.29
  参数:      无
  返回值:    Boolean
-------------------------------------------------------------------------------}
procedure TfaqhnewStuChangeCard.replaceNewCard(phyCardId:string;cardNo:Integer;operType:string);
var
  cardManage:TCardManage;
  newphyCardNo:string;
  inShowCardNo:string;

  tradeCardNo:Integer;      //交易卡号
  showCardNo:string;        //显示卡号
  tradeNum:Integer;         //交易次数
  cardEndDate:string;       //卡使用截至日期
  limitType:Integer;        //卡使用权限
  custType:Integer;         //客户类别
  custName:string;          //客户姓名
  dutyNo:string;            //职务代码
  cardID:string;            //身份证号
  depNo:string;             //部门代码
  bookID:string;            //图书证号
  sex:string;               //性别
  ID:string;                //学工号
  cardBalance:Integer;      //卡余额
  cardPWD:string;           //卡密码
  isFormation:Char;         //是否格式化第一扇区
  sOperDate:string;         //操作日期
  stationId:Integer;        //终端编号
  backTradeID:Integer;      //后台交易流水号
  maxPerCount:Integer;      //单次限额
  maxPerDay:Integer;        //日限额
  re,ret:Integer;
  ResInt:Integer;
  patchNo:Integer;
  sNewCardNo:string;

  i:Integer;
  tryNum:Integer;
  tmpPhyId:string;
begin
  if PrepareReadCardInfo=False then
    Exit;
  re := 0;
  ResInt := 0;
  stationId := 0;
  backTradeID := 0;
  sNewCardNo := '0';
  cardManage := nil;
  tryNum := 2;
  //检测是否有卡，无卡则退出
  for i := 1 to tryNum do
  begin
    if StrToInt(readCardNo)=0 then
      Break
    else
      Context.GetDialogSystem.ShowMessage('该卡的卡号已经存在，请放置一张新卡！');
  end;

  try
    cardManage := TCardManage.Create();
    if CardManage.ReadCardPhyID(newphyCardNo) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡序列号失败，请先撤销换卡，然后准备好新卡重新操作！');
      Exit;
    end;
    inShowCardNo := readShowCarNo;
    if inShowCardNo='-1' then
      Exit;
    //把新卡的物理编号及相关信息传入后台
    WorkViewOK.FieldByName('操作类型').Data.SetString(operType);
    WorkViewOK.FieldByName('原卡号').Data.SetInteger(cardNo);
    WorkViewOK.FieldByName('原物理编号').Data.SetString(phyCardId);
    WorkViewOK.FieldByName('原卡余额').Data.SetInteger(0);
    WorkViewOK.FieldByName('原卡交易次数').Data.SetInteger(0);
    WorkViewOK.FieldByName('补助批次号').Data.SetInteger(0);

    WorkViewOK.FieldByName('新卡物理编号').Data.SetString(newphyCardNo);
    WorkViewOK.FieldByName('显示卡号').Data.SetString(inShowCardNo);
    WorkViewOK.FieldByName('到期日期').Data.SetString(Trim(edtEndDate.Text));
    
    WorkViewOK.FieldByName('业务日期').Data.SetString('');
    WorkViewOK.FieldByName('流水号').Data.SetInteger(0);
    WorkViewOK.FieldByName('终端编号').Data.SetInteger(0);
    try
      WVRequestOK.SendCommand;
    except
      on ex:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(ex.Message);
        exit;
      end;
    end;
    if WorkViewOK.FieldByName('返回码').Data.AsInteger=0 then
    begin
      //开始发行新卡，失败则发送冲正交易
      try
        tradeCardNo:=WorkViewOK.fieldbyname('卡号').Data.AsInteger;

        showCardNo:=WorkViewOK.fieldbyname('显示卡号').Data.AsString;
        cardEndDate:=WorkViewOK.fieldbyname('到期日期').Data.AsString;
        limitType:=WorkViewOK.fieldbyname('收费类别').Data.AsInteger;
        custType:=WorkViewOK.fieldbyname('客户类别').Data.AsInteger;
        custName:=WorkViewOK.fieldbyname('客户姓名').Data.AsString;
        dutyNo:='';
        cardID:=WorkViewOK.fieldbyname('证件号码').Data.AsString;
        depNo:=WorkViewOK.fieldbyname('部门代码').Data.AsString;
        bookID:='';
        sex:=WorkViewOK.fieldbyname('性别').Data.AsString;
        ID:=WorkViewOK.fieldbyname('学工号').Data.AsString;
        cardBalance:=WorkViewOK.fieldbyname('出卡值').Data.AsInteger;
        cardPWD:=WorkViewOK.fieldbyname('卡密码').Data.AsString;
        isFormation := Char('N');

        backTradeID:=WorkViewOK.fieldbyname('流水号').Data.AsInteger;
        sOperDate := WorkViewOK.fieldbyname('业务日期').Data.AsString;
        stationId := WorkViewOK.fieldbyname('终端编号').Data.AsInteger;
        tradeNum := WorkViewOK.fieldbyname('交易次数').Data.AsInteger;
        patchNo := WorkViewOK.fieldbyname('补助批次号').Data.AsInteger;
      except
        on ex:Exception do
        begin
          Context.GetDialogSystem.ShowMessage('后台返回数据有误--'+ex.Message);
          Exit;
        end;
      end;
      strcopy(@PCM.CardNo, PChar(IntToStr(tradeCardNo)));         //交易卡号
      strcopy(@PCM.ShowCardNo, PChar(showCardNo));                //显示卡号
      strcopy(@PCM.DeadLineDate, PChar(cardEndDate));             //截止日期
      PCM.CardRightType := limitType;                             //收费类型
      strcopy(@PCM.ucIdentifyNo, PChar(IntToStr(custType)));      //客户类型
      strcopy(@PCM.ucName, PChar(custName));                      //姓名
      strcopy(@PCM.ucDutyNo, PChar(dutyNo));                      //职务
      strcopy(@PCM.ucCertificateNo, PChar(cardID));               //身份证号
      strcopy(@PCM.ucDepartmentNo, PChar(depNo));                 //部门
      strcopy(@PCM.ucLibraryNo, PChar(bookID));                   //图书证号
      strcopy(@PCM.ucSexNo, PChar(sex));                          //性别
      strcopy(@PCM.ucCardNo, PChar(ID));                          //学工号
      //PCM.Money := cardBalance;                                   //卡余额
      strcopy(@PCM.ucPwd, PChar(cardPWD));                        //卡密码
      PCM.isFormat := isFormation;                                //是否格式化第一扇区

      re := CardManage.PublishACard(PCM);
      //设置单次消费限额和日消费限额
      if maxper=1 then
      begin
        maxPerCount := WorkViewOK.fieldbyname('单次限额').Data.AsInteger;
        maxPerDay := WorkViewOK.fieldbyname('日限额').Data.AsInteger;
        ret := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
      end;
      //写补助批次号
      if cardManage.changePatchNo(patchNo)<>0 then
        Context.GetDialogSystem.ShowMessage('卡补助批次号写入失败，请到更新卡信息中更新补助批次号！');
      //设置卡交易次数及卡余额
      if CardManage.PacketSetMoney2(cardBalance,TradeNum)<>0 then
        Context.GetDialogSystem.ShowMessage('卡交易次数写入失败，请到更新卡信息中更新卡交易次数！');

      //发卡成功，读卡号成功，读取卡号大于零才确定该卡已经发行成功，否则重新发行
      ResInt := CardManage.ReadExCardID(sNewCardNo);
      if ((re <> 0) or (ResInt<>0) or (StrToInt(sNewCardNo)=0))or(ret<>0) then
      begin
        if Application.MessageBox(PChar('写卡失败，请使用同一张卡并正确放置到读写器上，你要重试一次吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
          Exit;
        //读卡物理编号，和以前的物理编号比较，不一样则不行
        if CardManage.ReadCardPhyID(tmpPhyId) <> 0 then
        begin
          Context.GetDialogSystem.ShowMessage('读卡物理编号失败，请把该卡先撤销换卡，然后重新做换卡交易！');
          Exit;
        end;
        if tmpPhyId<>newphyCardNo then
        begin
          Context.GetDialogSystem.ShowMessage('和刚才放置的不是同一张卡，请把该卡先撤销换卡，然后重新做换卡交易！');
          Exit;
        end;
        //写卡交易次数
        if CardManage.changeTradeNum(tradeNum)<>0 then
        begin

        end;
        //重新写一次卡
        re := CardManage.PublishACard(PCM);
        //设置单次消费限额和日消费限额
        if maxper=1 then
        begin
          maxPerCount := WorkViewOK.fieldbyname('单次限额').Data.AsInteger;
          maxPerDay := WorkViewOK.fieldbyname('日限额').Data.AsInteger;
          ret := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
        end;
        //发卡成功，读卡号成功，读取卡号大于零才确定该卡已经发行成功，否则重新发行
        ResInt := CardManage.ReadExCardID(sNewCardNo);
        //写补助批次号
        if cardManage.changePatchNo(patchNo)<>0 then
          Context.GetDialogSystem.ShowMessage('卡补助批次号写入失败，请到更新卡信息中更新补助批次号！');
        //设置卡交易次数及卡余额
        if CardManage.PacketSetMoney2(cardBalance,TradeNum)<>0 then
          Context.GetDialogSystem.ShowMessage('卡交易次数写入失败，请到更新卡信息中更新卡交易次数！');

      end;
    end
    else
    begin
      getReturn('',WorkViewOK);
      RzStatusPane1.Caption:=WorkViewOK.FieldByName('返回信息').Data.AsString;
    end;
  finally
    cardManage.Destroy;
    if ((re = 0) and (ResInt=0) and (StrToInt(sNewCardNo)>0))and (ret=0) then
    begin
      if operType='D' then
        Context.GetDialogSystem.ShowMessage('该卡已经撤销换卡成功  '+WorkViewOK.FieldByName('返回信息').Data.AsString)
      else
        Context.GetDialogSystem.ShowMessage('该卡已经换卡成功  '+WorkViewOK.FieldByName('返回信息').Data.AsString);
    end

    else
    begin
      WorkViewOK.FieldByName('操作类型').Data.SetString('V');

      WorkViewOK.FieldByName('原卡号').Data.SetInteger(0);
      WorkViewOK.FieldByName('原物理编号').Data.SetString('');
      WorkViewOK.FieldByName('原卡余额').Data.SetInteger(0);
      WorkViewOK.FieldByName('原卡交易次数').Data.SetInteger(0);

      WorkViewOK.FieldByName('新卡物理编号').Data.SetString('');
      WorkViewOK.FieldByName('显示卡号').Data.SetString('');
      WorkViewOK.FieldByName('到期日期').Data.SetString('');

      WorkViewOK.FieldByName('业务日期').Data.SetString(sOperDate);
      WorkViewOK.FieldByName('流水号').Data.SetInteger(backTradeID);
      WorkViewOK.FieldByName('终端编号').Data.SetInteger(stationId);
      WVRequestOK.SendCommand;
      //if WorkViewOK.FieldByName('返回码').Data.AsInteger<>0 then
        //Context.GetDialogSystem.ShowMessage('换卡冲正失败--'+WorkViewOK.FieldByName('返回信息').Data.AsString);
    end;

  end;
end;

procedure TfaqhnewStuChangeCard.btnPatchCardClick(Sender: TObject);
var
  tmpdata:TDataSet;
  phyCardId,tmpPhyId:string;
  cardNo:Integer;
  cardManage:TCardManage;
begin
  //inherited;
  try
    tmpdata:=WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet;
    phyCardId := tmpdata.fieldbyname('sstation1').AsString;
    cardNo := tmpdata.fieldbyname('lvol0').AsInteger;
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('错误信息：'+ex.Message+' 可能没有查询结果');
      Exit;
    end;
  end;
  if PrepareReadCardInfo=False then
    Exit;
  //读卡获得相关信息
  cardManage := nil;
  try
    cardManage:=TCardManage.Create();
    //取物理卡号
    if CardManage.ReadCardPhyID(tmpPhyId) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡序列号失败，请重新把卡放置到读写器上！');
      exit;
    end;
    if tmpPhyId<>phyCardId then
    begin
      Context.GetDialogSystem.ShowMessage('要撤销的卡和查询出的卡不是同一张卡！');
      Exit;
    end;
  finally
    cardManage.Destroy;
  end;
  //ShowMessage(IntToStr(cardNo));
  replaceNewCard(phyCardId,cardNo,'D');
end;

procedure TfaqhnewStuChangeCard.btnQueryClick(Sender: TObject);
begin
  if (edtCardNo.Text)='' then
    edtCardNo.Text:='0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text:='0';
  inherited;
end;

procedure TfaqhnewStuChangeCard.edtShowCardKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;

end;

initialization
  TUIStdClassFactory.Create('新生换卡操作',TfaqhnewStuChangeCard);

end.