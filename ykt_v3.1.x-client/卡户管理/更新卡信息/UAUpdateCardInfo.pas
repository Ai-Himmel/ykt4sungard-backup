unit UAUpdateCardInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, WVCommands, RzStatus, RzPanel, RzEdit, RzButton, RzRadChk,
  Buttons, UIncrementComboBox,UtCardDll;

type
  TfaqhUpdateCardInfo = class(TfaqhSimpleQueryTemp)
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnReadCardQuery: TBitBtn;
    btnOK: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    grp3: TGroupBox;
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
    edtCTradeNum: TRzEdit;
    grp1: TGroupBox;
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
    edtTradeNum: TRzEdit;
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
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure edtShowCardNoKeyPress(Sender: TObject; var Key: Char);
    procedure cbbRTypeChange(Sender: TObject);
  private
    tempPCardID:string;
    { Private declarations }

    Function readCardInfo:Boolean;
    procedure edtEnabledT;                    //使编辑框为可用
    procedure resultQuery;                    //查询结果
    procedure clearEdt;                       //清空编辑框内容
    procedure getInMoney;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhUpdateCardInfo: TfaqhUpdateCardInfo;
  CardID: string;

implementation

uses KsFrameworks, 
  KSClientConsts,KSDataDictionary;

{$R *.DFM}

procedure TfaqhUpdateCardInfo.Init;
begin
  inherited;
  btnok.Enabled := false;
  cbbRType.ItemIndex :=0;
  edtEndDate.Enabled := False;
  edtMaxPerDay.Enabled := True;
  edtMaxPercount.Enabled := True;
end;

procedure TfaqhUpdateCardInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhUpdateCardInfo.btnQueryClick(Sender: TObject);
begin
  clearEdt;
  inherited;
  try
    resultQuery;
    edtEnabledT;
  except
  end;
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
  cardID:string;            //身份证号
  depNo:string;             //部门代码
  sex:string;               //性别
  stuempNo:string;          //学工号
  cardBalance:Integer;      //卡余额
  cardpwd:string;           //卡密码
  isFormation:Char;         //是否格式化第一扇区
  cardTradeNum:Integer;     //卡交易次数
  patchNO:Integer;          //补助批次号
  maxPerCount:Integer;
  maxPerDay:Integer;

  PCM: TPublishCardMes;
  CardManage: TCardManage;
  cardmoney:LongInt;
  tradeNum:Integer;
  st,stPNo,rst:LongInt;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  rType:string;
begin
  RzStatusPane1.Caption :='';
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowWarning('请先打开串口！');
    Exit;
  end;
  if not SmartCardAuthStatus then
  begin
    Context.GetDialogSystem.ShowWarning('请先为读写器授权！');
    Exit;
  end;
  CardManage := nil;
  try
    //重新读取物理卡号，判断是否和要更新的物理卡号一致
    CardManage := TCardManage.Create;
    if CardManage.ReadCardPhyID(PCardID)=0 then
    begin
      if PCardID<>trim(tempPCardID) then
      begin
        Context.GetDialogSystem.ShowMessage('更新时请使用同一张卡！');
        Exit;
      end;
    end;
    rType := Copy(cbbRType.Text,1,Pos('-',cbbRType.Text)-1);
    if (rType='') or (rType='-') then
    begin
      Context.GetDialogSystem.ShowMessage('请选择更新类型！');
      cbbRType.SetFocus;
      Exit;
    end;

    if CardManage.ReadCardConsumeInfo(LPI, nPacketNo)=True then
    begin
      cardmoney := LPI.RemainMoney;
      tradeNum := LPI.DealTimes;
    end
    else
    begin
      cardmoney := 0;
      tradeNum := 0;
      RzStatusPane1.Caption :='读取钱包信息失败！';
    end;

    WorkView.FieldByName('卡号').Data.SetInteger(strtoint(edtcCardNo.text));
    WorkView.FieldByName('物理卡号').Data.Setstring(PCardID);
    WorkView.FieldByName('卡到期日期').Data.Setstring(edtEndDate.text);
    WorkView.FieldByName('卡余额').Data.SetInteger(cardmoney);
    WorkView.FieldByName('交易次数').Data.SetInteger(tradeNum);
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
      cardID:=WorkView.fieldbyname('证件号码').Data.AsString;
      depNo:=WorkView.fieldbyname('部门代码').Data.AsString;
      sex:=WorkView.fieldbyname('性别').Data.AsString;
      stuempNo:=WorkView.fieldbyname('学工号').Data.AsString;
      cardBalance:=WorkView.fieldbyname('卡余额').Data.AsInteger;
      isFormation := Char('N');
      cardTradeNum := WorkView.fieldbyname('交易次数').Data.AsInteger;
      patchNO  := WorkView.fieldbyname('补助批次号').Data.AsInteger;
      cardpwd := WorkView.fieldbyname('卡密码').Data.AsString;

      if rType='1' then
      begin
        strcopy(@PCM.CardNo, PChar(IntToStr(CardNo)));              //交易卡号
        strcopy(@PCM.ShowCardNo, PChar(showCardNo));                //显示卡号
        strcopy(@PCM.DeadLineDate, PChar(cardEndDate));             //截止日期
        PCM.CardRightType := feeType;                               //收费类型
        strcopy(@PCM.ucIdentifyNo, PChar(IntToStr(custType)));      //客户类型
        strcopy(@PCM.ucName, PChar(custName));                      //姓名
        strcopy(@PCM.ucCertificateNo, PChar(cardID));               //身份证号
        strcopy(@PCM.ucDepartmentNo, PChar(depNo));                 //部门
        strcopy(@PCM.ucSexNo, PChar(sex));                          //性别
        strcopy(@PCM.ucCardNo, PChar(stuempNo));                    //学工号
        strcopy(@PCM.ucPwd, PChar(cardpwd));                        //卡密码
        //PCM.Money := cardBalance;                                 //卡余额
        PCM.isFormat := isFormation;                                //是否格式化第一扇区
        
        st := CardManage.UpdateCardBasicInfo(PCM);
        //设置单次消费限额和日消费限额
        if maxper=1 then
        begin
          maxPerCount := WorkView.fieldbyname('单次限额').Data.AsInteger;
          maxPerDay := WorkView.fieldbyname('日限额').Data.AsInteger;
          rst := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
        end;

        if (st<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('更新卡信息失败--'+inttostr(st));
          exit;
        end;
        if (rst<>0) then
        begin
          Context.GetDialogSystem.ShowMessage('更新卡单次限额和当日限额失败--'+inttostr(rst));
          Exit;
        end;
      end
      else if rType='2' then  //更新有效期
      begin
        st := CardManage.ChangeDeadLineDate(cardEndDate);
      end
      else if rType='3' then  //更新卡余额，补助批次号
      begin
        stPNo := CardManage.changePatchNo(patchNO);
        st := CardManage.PacketSetMoney2(cardBalance,cardTradeNum);
        if st<>0 then
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
        strcopy(@PCM.CardNo, PChar(IntToStr(CardNo)));              //交易卡号
        strcopy(@PCM.ShowCardNo, PChar(showCardNo));                //显示卡号
        strcopy(@PCM.DeadLineDate, PChar(cardEndDate));             //截止日期
        PCM.CardRightType := feeType;                               //收费类型
        strcopy(@PCM.ucIdentifyNo, PChar(IntToStr(custType)));      //客户类型
        strcopy(@PCM.ucName, PChar(custName));                      //姓名
        strcopy(@PCM.ucCertificateNo, PChar(cardID));               //身份证号
        strcopy(@PCM.ucDepartmentNo, PChar(depNo));                 //部门
        strcopy(@PCM.ucSexNo, PChar(sex));                          //性别
        strcopy(@PCM.ucCardNo, PChar(stuempNo));                    //学工号
        strcopy(@PCM.ucPwd, PChar(cardpwd));                        //卡密码
        PCM.Money := cardBalance;                                   //卡余额
        PCM.isFormat := isFormation;                                //是否格式化第一扇区
        
        st := CardManage.PublishACard(PCM);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('重写卡基本信息失败,请重写--'+inttostr(st));
          exit;
        end;

        //设置单次消费限额和日消费限额
        //设置单次消费限额和日消费限额
        if maxper=1 then
        begin
          maxPerCount := WorkView.fieldbyname('单次限额').Data.AsInteger;
          maxPerDay := WorkView.fieldbyname('日限额').Data.AsInteger;
          rst := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
        end;

        if (rst<>0) then
        begin
          Context.GetDialogSystem.ShowMessage('更新卡单次限额和当日限额失败--'+inttostr(rst));
          Exit;
        end;

        stPNo := CardManage.changePatchNo(patchNO);
        st := CardManage.PacketSetMoney2(cardBalance,cardTradeNum);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('重写卡余额失败，请执行更新类型为4的操作--'+inttostr(st));
          exit;
        end;
        if stPNo<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('重写卡补助批次号失败，请执行更新类型为4的操作--'+inttostr(st));
          exit;
        end;

      end
      else if rType='5' then  //清空卡信息
      begin
        st := CardManage.ClearCard;
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('清空卡信息失败--'+inttostr(st));
          Exit;
        end;
      end;
      CardManage.ControlBuzzer;
      clearEdt;
      Context.GetDialogSystem.ShowSuccess('更新卡信息成功！');
    end
    else
    begin
      getreturn('',workview1);
    end;
  finally
    btnok.Enabled := false;
    CardManage.Destroy;
  end;
end;

procedure TfaqhUpdateCardInfo.btnReadCardQueryClick(Sender: TObject);
begin
  RzStatusPane1.Caption :='';
  if PrepareReadCardInfo=False then
    Exit;
  if readCardInfo=False then
    Exit;
  getInMoney;
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
  //try
    resultQuery;
    edtEnabledT;
    btnok.enabled := true;
  //except
    
  //end;
end;

Function TfaqhUpdateCardInfo.readCardInfo():Boolean;
var
  CardManage: TCardManage;
  PCM: TPublishCardMes;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  phycardid,cardNo:string;
  maxPerCount,maxPerDay:Integer;
  //st : longint;
begin
  Result := True;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    if CardManage.ReadCardPhyID(phycardid) <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('读物理卡号失败，该卡已经损坏！');
      Result:=False;
      Exit;
    end;
  
    //读取交易卡号
    if CardManage.ReadExCardID(cardNo) <> 0 then
      RzStatusPane1.Caption := '读取交易卡号失败！'
    else
      edtcCardNo.Text := cardNo;
    tempPCardID := phycardid;
    //读取卡中信息
    if CardManage.ReadCardInfo(PCM) = 0 then
    begin
      //姓名
      edtcName.Text := PCM.ucName;
      //物理卡号
      edtcPhyId.Text := phycardid;
      //证件号码
      edtcIdCard.Text := PCM.ucCertificateNo;
      //学工号
      edtcStuempNo.Text := PCM.ucCardNo;
      //截至日期
      edtcEndDate.Text := PCM.DeadLineDate;
      //显示卡号
      edtcShowNo.Text := PCM.ShowCardNo;
      //收费类别
      edtcFeeType.Text := GetIdObjectName(-43,IntToStr(PCM.CardRightType));
      //客户类别
      edtCCustType.Text := GetIdObjectName(-34,Trim(PCM.ucIdentifyNo));
      //部门
      edtCDept.Text := GetIdObjectName(-22,Trim(PCM.ucDepartmentNo));
      //性别
      edtCSex.Text := GetIdObjectName(39,Trim(PCM.ucSexNo));
      
      if CardManage.ReadCardConsumeInfo(LPI, nPacketNo)=True then
      begin
        edtcBalance.Text := format('%f', [LPI.RemainMoney / 100.0]);
        edtCTradeNum.Text := format('%d', [LPI.DealTimes]);
        edtCPatchNo.Text := Format('%d',[LPI.DealTimes_CurDay]);
      end
      else
      begin
        RzStatusPane1.Caption :='读取钱包信息失败！';
      end;
    end
    else
    begin
      RzStatusPane1.Caption :='读取卡信息基本失败！';
      Result:=False;
    end;
    if maxPer=1 then
    begin
      if CardManage.ReadConsumeLimit(maxPerCount,maxPerDay)=0 then
      begin
        edtMaxcPerCount.Text := FloatToStr(maxPerCount/100);
        edtcMaxPerDay.Text := FloatToStr(maxPerDay/100);
      end
      else
      begin
        RzStatusPane1.Caption :='读取卡单次限额和日限额失败！';
      end;
    end
    else
    begin
      edtMaxcPerCount.Text := '无';
      edtcMaxPerDay.Text := '无';
    end;
  finally
    CardManage.Destroy;
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
    //交易卡号
    edtCardNo.Text := tempDataSet.FieldByName('lvol0').AsString;
    //卡使用截止日期
    edtEndDate.Text := tempDataSet.FieldByName('sdate2').AsString;
    //姓名
    edtName.Text := tempDataSet.FieldByName('sall_name').AsString;
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
    //交易次数
    edtTradeNum.Text := tempDataSet.fieldbyname('lvol6').AsString;
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
  for i := 0 to UIPanel1.ControlCount-1 do
    if (UIPanel1.Controls[i] is TWVEdit)and (TWVEdit(UIPanel1.Controls[i]).tag<>15) then
      TWVEdit(UIPanel1.Controls[i]).Text:='';
end;

procedure TfaqhUpdateCardInfo.edtShowCardNoKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;
end;

procedure TfaqhUpdateCardInfo.getInMoney;
var
  cardManage:TCardManage;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  TOF: boolean;
begin
  cardManage := nil;
  try
    cardManage := TCardManage.Create;
    TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
    if TOF = false then
    begin
      RzStatusPane1.Caption := '读用户卡消费信息失败！';
      //cardTradeNum := 0;
      //cardTradeMoney := 0;
      Exit;
    end
    else
    begin
      edtcBalance.Text := format('%f', [LPI.RemainMoney / 100.0]);
      edtCTradeNum.Text := format('%d', [LPI.DealTimes]);
    end;
  finally
    cardManage.Destroy;
  end;
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

initialization
  TUIStdClassFactory.Create('卡信息更新', TfaqhUpdateCardInfo);

end.
