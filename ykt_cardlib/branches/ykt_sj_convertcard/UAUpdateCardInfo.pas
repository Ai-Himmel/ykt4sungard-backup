unit UAUpdateCardInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, WVCommands, RzStatus, RzPanel;

type
  TfaqhUpdateCardInfo = class(TfaqhSimpleQueryTemp)
    btnOK: TImageButton;
    btnReadCardQuery: TImageButton;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp3: TGroupBox;
    Label2: TLabel;
    edtcCardNo: TWVEdit;
    edtcPhyId: TWVEdit;
    WVLabel6: TWVLabel;
    edtcStuempNo: TWVEdit;
    WVLabel8: TWVLabel;
    WVLabel11: TWVLabel;
    edtcShowNo: TWVEdit;
    edtcBalance: TWVEdit;
    WVLabel14: TWVLabel;
    WVLabel15: TWVLabel;
    edtcIdCard: TWVEdit;
    WVLabel17: TWVLabel;
    WVLabel18: TWVLabel;
    WVLabel20: TWVLabel;
    edtcBookId: TWVEdit;
    edtcName: TWVEdit;
    edtcEndDate: TWVEdit;
    grp1: TGroupBox;
    Label1: TLabel;
    WVLabel2: TWVLabel;
    WVLabel9: TWVLabel;
    WVLabel7: TWVLabel;
    WVLabel16: TWVLabel;
    WVLabel19: TWVLabel;
    WVLabel10: TWVLabel;
    WVLabel1: TWVLabel;
    WVLabel5: TWVLabel;
    edtCardNo: TWVEdit;
    edtCardID: TWVEdit;
    edtNo: TWVEdit;
    edtIDCard: TWVEdit;
    edtBalance: TWVEdit;
    edtShowCardNo: TWVEdit;
    edtBookID: TWVEdit;
    edtName: TWVEdit;
    edtEndDate: TWVEdit;
    chkmoney: TCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure chkmoneyClick(Sender: TObject);
    procedure edtShowCardNoKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }

    CardKind:Integer;
    DepartNo,sex:string;
    feetype:Integer;                          //收费类别
    tempPCardID:string;                       //卡物理编号
    cardPwd:string;                           //卡密码
    cardTreadNum:Integer;                         //卡的交易次数
    patchNum:Integer;                         //补助批次号

    //广州大学城增加内容
    area_code : string;                       //院校代码
    cut_id : Integer;                         //客户ID号
    certificate_type : string;                //证件类型
    people:string;                            //民族
    nationality:string;                       //国籍
    open_card_flag : string;                  //是否已经开卡,0未开卡,1已开卡
    card_version : string;                    //制卡版本号
    pub_card_flag:string;                     //发卡注册标识号
    ser_flag:string;                          //服务注册标识号
    pwd_open_flag : string;                   //启用密码开关0启用,1未启用

    Function readCardInfo:Boolean;
    procedure edtEnabledF;                    //使编辑框为不可用
    procedure edtEnabledT;                    //使编辑框为可用
    procedure resultQuery;                    //查询结果
    procedure clearEdt;                       //清空编辑框内容
  public
    sOperID,sOperPWD,sSign:string;
    imoney:Integer;
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhUpdateCardInfo: TfaqhUpdateCardInfo;
  CardID: string;

implementation

uses KsFrameworks, 
  KSClientConsts, UtCardDll;

{$R *.DFM}

procedure TfaqhUpdateCardInfo.Init;
begin
  inherited;
  WorkView.FieldByName('卡标识').DefaultValue := 0;
  btnReadCardQuery.caption:='&I读卡查询';
  btnQuery.caption:='&Q条件查询';
  edtEnabledF;
  WorkView.Reset;
  btnok.Enabled := false;
  imoney:=2;
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
  OperatorNoName:string;
  CusName: string;
  DutyID: string;
  ReadBookCardID: string;
  CertifiNo: string;
  SOWNo: string;
  sShowCardNo: string;
  FDeadLineDate: string;
  PCardID: string;
  CardInfo: TPublishCardMes;
  CardManage: TCardManage;
  cardmoney:LongInt;
  st:LongInt;
begin
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

  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行该操作！');
    Exit;
  end;
  {
  if (Trim(edtShowCardNo.Text)<>'') and (Length(Trim(edtShowCardNo.Text))<>10) then
  begin
    Context.GetDialogSystem.ShowMessage('请输入有效的显示卡号！');
    Exit;
  end;
  }
  //重新读取物理卡号，判断是否和要更新的物理卡号一致
  CardManage := TCardManage.Create;
  if CardManage.ReadCardPhyID(PCardID)=0 then
  begin
    if PCardID<>trim(tempPCardID) then
    begin
      Context.GetDialogSystem.ShowMessage('更新时请使用同一张卡！');
      CardManage.Destroy;
      Exit;
    end;
  end;

  //取操作员号，框架中的方法
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;

  WorkView1.FieldByName('卡号').Data.SetInteger(strtoint(edtcCardNo.text));
  WorkView1.FieldByName('物理卡号').Data.Setstring(edtCardID.Text);
  WorkView1.FieldByName('显示卡号').Data.Setstring(edtShowCardNo.text);
  WorkView1.FieldByName('操作员号').Data.Setstring(OperatorNoName);
  WorkView1.FieldByName('工作站号').Data.SetInteger(SmartCardSubSystemNo);
  WorkView1.FieldByName('截至日期').Data.Setstring(edtEndDate.Text);
  WorkView1.FieldByName('复核员号').Data.Setstring('0');
  WorkView1.FieldByName('复核员密码').Data.Setstring('0');
  WorkView1.FieldByName('是否写卡余额').Data.setinteger(imoney);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
  begin
    //卡使用截止日期
    FDeadLineDate := edtEndDate.text;
    CusName := edtName.Text;
    //职务代码 DutyID
    DutyID:='0';
    //图书证号
    ReadBookCardID := edtBookID.Text;
    //身份证号
    CertifiNo := edtIDCard.text;
    //学工号
    SOWNo := edtNo.text;
    //显示卡号
    sshowCardNo := edtShowCardNo.text;
    //卡中金额
    if trim(edtbalance.Text) = '' then
      cardmoney:=0
    else
      cardmoney := round(strtofloat(edtbalance.text)*100);
    ShowWaiting(SWaitingOperation);

    //将信息写入卡中，调用dll函数
    strcopy(@CardInfo.DeadLineDate, PChar(FDeadLineDate));
    CardInfo.CardRightType := feetype;                              //收费类别
    strcopy(@CardInfo.CardNo, PChar(edtCardNo.Text));
    //showmessage(CardInfo.CardNo);
    strcopy(@CardInfo.ucName, PChar(CusName));
    strcopy(@CardInfo.ucDutyNo, PChar(DutyID));
    strcopy(@CardInfo.ucCertificateNo, PChar(CertifiNo));           //身份证号
    strcopy(@CardInfo.ucDepartmentNo, PChar(DepartNo));
    strcopy(@CardInfo.ucLibraryNo, PChar(ReadBookCardID));
    strcopy(@CardInfo.ucSexNo, PChar(sex));                         //图书证号
    strcopy(@CardInfo.ucIdentifyNo, PChar(IntToStr(CardKind)));     //客户类别  cardPwd
    strcopy(@CardInfo.ucCardNo, PChar(SOWNo));
    strcopy(@CardInfo.ucPwd, PChar(cardPwd));
    //ShowMessage(CardInfo.ucPwd);

    strcopy(@CardInfo.ShowCardNo, PChar(sshowCardNo));
    ///showmessage(CardInfo.ShowCardNo);
    CardInfo.cut_id := cut_id;                                       //客户ID号
    strcopy(@CardInfo.area_code, PChar(area_code));                  //院校代码
    strcopy(@CardInfo.certificate_type, PChar(certificate_type));    //证件类型
    strcopy(@CardInfo.people, PChar(people));                        //民族
    strcopy(@CardInfo.nationality, PChar(nationality));              //国籍
    strcopy(@CardInfo.card_version, PChar(card_version));            //制卡版本号
    strcopy(@CardInfo.pub_card_flag, PChar(pub_card_flag));          //发卡注册标识号
    strcopy(@CardInfo.ser_flag, PChar(ser_flag));                    //服务注册标识号
    try
      if chkmoney.checked then
      begin
        st := CardManage.UpdateCardBasicInfo(CardInfo);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('更新卡信息失败--'+inttostr(st));
          CardManage.Destroy;
          exit;
        end;
        //ShowMessage(IntToStr(patchNum));
        if CardManage.UpdateMoneyAndTxCnt(Cardmoney,cardTreadNum,patchNum)<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('更新卡余额失败！');
          CardManage.Destroy;
          exit;
        end;
      end
      else
      begin
        st := CardManage.UpdateCardBasicInfo(CardInfo);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('更新卡信息失败--'+inttostr(st));
          CardManage.Destroy;
          exit;
        end;
      end;
      CardManage.ControlBuzzer;
      edtEnabledF;
      clearEdt;
      Context.GetDialogSystem.ShowSuccess('更新卡信息成功！');
    finally
      CloseWaiting;
      btnok.Enabled := false;
    end;
  end
  else
  begin
    getreturn('',workview1);
  end;
  CardManage.Destroy;
end;

procedure TfaqhUpdateCardInfo.btnReadCardQueryClick(Sender: TObject);
//var
  //CardManage: TCardManage;
  //ResInt: SmallInt;
  //cardNo:string;
begin
  if PrepareReadCardInfo=False then
    Exit;
  if readCardInfo=False then
    Exit;
  {
  CardManage := TCardManage.Create;
  //读取交易卡号
  ResInt := CardManage.ReadExCardID(CardID);
  if ResInt <> 0 then
    edtCardNo.Text := '0'
  else
    edtCardNo.Text := CardID;
  else
  begin
    if CardID='0' then
    begin
      Context.GetDialogSystem.ShowMessage('该卡没有发行，请先发卡！');
      CardManage.Destroy;
      Exit;
    end
    else
    begin
      WVEdit1.Text := CardID;
      CardManage.Destroy;
    end;
  end;
  }
  //inherited;
  WorkView.FieldByName('卡标识').Data.SetInteger(StrToInt(edtcCardNo.Text));
  WorkView.FieldByName('物理卡号').Data.SetString(edtcPhyId.Text);
  MainRequest.SendCommand;
  if WorkView.fieldbyname('返回码').data.asinteger<>0 then
  begin
    getreturn('',WorkView);
    exit;
  end;
  try
    resultQuery;
    edtEnabledT;
    btnok.enabled := true;
  except
  end;
end;

Function TfaqhUpdateCardInfo.readCardInfo():Boolean;
var
  CardManage: TCardManage;
  PCM: TPublishCardMes;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  phycardid,cardNo:string;
  st : longint;
begin
  Result := True;
  CardManage := TCardManage.Create;
  if CardManage.ReadCardPhyID(phycardid) <> 0 then
  begin
    context.GetDialogSystem.ShowMessage('读物理卡号失败，该卡已经损坏！');
    CardManage.Destroy;
    Result:=False;
    Exit;
  end;
  //读取交易卡号

  if CardManage.ReadExCardID(cardNo) <> 0 then
  begin
    edtcCardNo.Text := '0';
    //读取不到卡号，则开始初始化该卡
    st :=cardmanage.InitCard('');
    if st<>0 then
    begin
      showmessage('初始化卡失败，请重新进行读卡查询，如果还不能初始化该卡，则该卡已经损坏！');
      exit;
    end;
  end
  else
    edtcCardNo.Text := cardNo;
    
  //读取卡中信息
  if CardManage.ReadCardInfo(PCM) = 0 then
  begin
    edtcName.Text := PCM.ucName;                                  //姓名
    edtcPhyId.Text := phycardid;                                  //物理卡号
    edtcIdCard.Text := PCM.ucCertificateNo;                       //身份证号
    edtcStuempNo.Text := PCM.ucCardNo;                            //学工号
    edtcBookId.Text := PCM.ucLibraryNo;                           //图书证号
    edtcEndDate.Text := PCM.DeadLineDate;                         //截至日期
    edtcShowNo.Text := Copy(PCM.ShowCardNo,1,10);                 //显示卡号

    open_card_flag := Copy(PCM.open_card_flag,1,1);               //是否已经开卡,0未开卡,1已开卡
    card_version := Copy(PCM.card_version,1,1);                   //制卡版本号
    pub_card_flag:=Copy(PCM.pub_card_flag,1,10);                  //发卡注册标识号
    ser_flag:=Copy(PCM.ser_flag,1,10);                            //服务注册标识号
    pwd_open_flag := Copy(PCM.pwd_open_flag,1,1);                 //启用密码开关0启用,1未启用

    if CardManage.ReadCardConsumeInfo(LPI, nPacketNo)=True then
    begin
      edtcBalance.Text := format('%f', [LPI.RemainMoney / 100.0]);
    end
    else
    begin
      Context.GetDialogSystem.ShowWarning('读取钱包信息失败！');
      Result := False;
      Exit;
    end;
    CardManage.Destroy;
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('读取卡信息基本失败！');
    CardManage.Destroy;
    Result:=False;
  end;
end;
procedure TfaqhUpdateCardInfo.edtEnabledF;
begin
  edtCardID.Enabled:=False;
  edtCardID.Color:=clScrollBar;
end;

procedure TfaqhUpdateCardInfo.edtEnabledT;
begin
  edtShowCardNo.Enabled:=True;
  edtEndDate.Enabled:=True;
  edtshowCardNo.Color:=clwhite;
  edtEndDate.Color:=clwhite;
end;

procedure TfaqhUpdateCardInfo.resultQuery;
var
  tempDataSet: TDataSet;
begin
  tempDataSet := WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet;
  //交易卡号
  edtCardNo.Text := tempDataSet.FieldByName('lvol0').AsString;
  //卡使用截止日期
  edtEndDate.Text := tempDataSet.FieldByName('sdate0').AsString;
  //姓名
  edtName.Text := tempDataSet.FieldByName('sname').AsString;
  //图书证号
  edtBookID.text := tempDataSet.FieldByName('sname2').AsString;
  //身份证号
  edtIDCard.Text := tempDataSet.FieldByName('scust_auth2').AsString;
  //学工号
  edtNo.Text := tempDataSet.FieldByName('scust_limit').AsString;
  //显示卡号
  edtShowCardNo.Text := tempDataSet.FieldByName('scust_no').AsString;
  //卡余额
  edtBalance.Text := tempDataSet.FieldByName('damt0').AsString;
  //物理编号
  edtCardID.Text := tempDataSet.FieldByName('sbank_acc').AsString;
  //客户类别
  cardkind:= tempDataSet.FieldByName('lvol1').asinteger;
  //收费类别
  feetype:=tempDataSet.FieldByName('lvol5').asinteger;
  //部门编号
  DepartNo := tempDataSet.FieldByName('sserial0').AsString;
  //性别
  Sex := tempDataSet.FieldByName('scust_type').AsString;
  //物理卡号
  tempPCardID := tempDataSet.fieldbyname('sbank_acc').AsString;
  
  //院校代码
  area_code := tempDataSet.fieldbyname('sbranch_code0').AsString;
  //客户ID号
  cut_id := tempDataSet.fieldbyname('sholder_ac_no').AsInteger;
  //证件类型
  certificate_type := tempDataSet.fieldbyname('sstat_type').AsString;
  //民族
  people:=tempDataSet.fieldbyname('sstat_type2').AsString;
  //国籍
  nationality:=tempDataSet.fieldbyname('snation_code').AsString;
  //卡密码
  cardPwd :=  tempDataSet.fieldbyname('sbank_acc2').AsString;
  //卡交易次数
  cardTreadNum := tempDataSet.fieldbyname('lvol10').AsInteger;
  //补助批次号
  patchNum := tempDataSet.fieldbyname('lvol11').AsInteger;
end;

procedure TfaqhUpdateCardInfo.clearEdt;
var
  i:Integer;
begin
  chkmoney.Checked:=False;
  for i := 0 to UIPanel1.ControlCount-1 do
    if (UIPanel1.Controls[i] is TWVEdit)and (TWVEdit(UIPanel1.Controls[i]).tag<>15) then
      TWVEdit(UIPanel1.Controls[i]).Text:='';
end;

procedure TfaqhUpdateCardInfo.chkmoneyClick(Sender: TObject);
begin
  if chkmoney.Checked then
    imoney := 1
  else
    imoney := 2;
end;

procedure TfaqhUpdateCardInfo.edtShowCardNoKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;
end;

initialization
  TUIStdClassFactory.Create('卡信息更新', TfaqhUpdateCardInfo);

end.
