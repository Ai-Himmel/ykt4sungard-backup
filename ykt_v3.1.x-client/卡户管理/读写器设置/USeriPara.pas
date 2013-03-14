unit USeriPara;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVCtrls,Db, Mask, RzEdit, RzCmboBx, RzStatus, RzPanel, Buttons, UtCardDll;

type
  TfaMachinePara = class(TfaInputTemp)
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVLabel1: TWVLabel;
    rgcom: TRadioGroup;
    grpCardInfo: TGroupBox;
    edtPhyID: TRzEdit;
    edtCardNo: TRzEdit;
    edtShowNo: TRzEdit;
    lblOper: TLabel;
    edtVerNo: TRzEdit;
    edtBalack: TRzEdit;
    edtMoney: TRzEdit;
    edtTreadeNum: TRzEdit;
    edtPwd: TRzEdit;
    cbbBit: TRzComboBox;
    stat1: TRzStatusBar;
    rzstspn1: TRzStatusPane;
    rzstspn2: TRzStatusPane;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane16: TRzStatusPane;
    RzStatusPane17: TRzStatusPane;
    RzStatusPane18: TRzStatusPane;
    RzStatusPane20: TRzStatusPane;
    RzStatusPane23: TRzStatusPane;
    grpOper: TGroupBox;
    btnOpen: TBitBtn;
    btnAuth: TBitBtn;
    btnClose: TBitBtn;
    btnReadCard: TBitBtn;
    grpCustInfo: TGroupBox;
    RzStatusPane14: TRzStatusPane;
    RzStatusPane13: TRzStatusPane;
    RzStatusPane12: TRzStatusPane;
    RzStatusPane10: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    edtStuempNo: TRzEdit;
    edtName: TRzEdit;
    edtSex: TRzEdit;
    edtIDCard: TRzEdit;
    edtFeeType: TRzEdit;
    edtDept: TRzEdit;
    edtCustType: TRzEdit;
    RzStatusPane15: TRzStatusPane;
    edtEndDate: TRzEdit;
    edtPatchNo: TRzEdit;
    RzStatusPane21: TRzStatusPane;
    edtTradeDate: TRzEdit;
    RzStatusPane7: TRzStatusPane;
    edtMaxPerCount: TRzEdit;
    RzStatusPane8: TRzStatusPane;
    edtmaxPerDay: TRzEdit;
    WVLabel2: TWVLabel;
    lblVer: TWVLabel;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    RzStatusPane9: TRzStatusPane;
    edtCardStatus: TRzEdit;
    procedure btnOKClick(Sender: TObject);
    procedure btnOpenClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure btnAuthClick(Sender: TObject);
    procedure SaveToINI;
    procedure OPenFormINI;
    procedure CloseFormINI;
    procedure btnReadCardClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
  private
   { Private declarations }
   procedure initCardInfoPosi;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faMachinePara: TfaMachinePara;

implementation
uses KSFrameWorks, INIFiles,KSClientConsts,KSDataDictionary,
  UCMqhCardImp;

{$R *.DFM}

procedure TfaMachinePara.btnOKClick(Sender: TObject);
begin
  SaveToINI;
end;

procedure TfaMachinePara.Init;
var
  my: tinifile;
  tempBit: integer;
  tempCom: integer;
  sPath:string;
  cardManage:TCardManage;
  reVer:string;
begin
  inherited;
  lblVer.Caption := '';
  cardManage := nil;
  try
    try
      cardManage := TCardManage.Create;
      cardManage.readCardDllVer(reVer);
      lblVer.Caption := reVer;
    except
      lblVer.Caption := '读版本失败';
    end;
  finally
    cardManage.Destroy;
  end;
  
  stat1.Font.Color := clBlue;
  initCardInfoPosi;
  btnOpen.Caption := '&O 打开串口';
  btnOpen.Width := 120;
  btnClose.Caption := '&C 关闭串口';
  btnClose.Width := 120;
  btnAuth.Caption := '&A 读写器授权';
  btnAuth.Width := 120;
  btnReadCard.Caption := '&R 读取卡信息';
  btnReadCard.Width := 120;
  sPath := ExtractFilePath(Application.ExeName);
  if fileexists(spath+'..\configs\setPara.ini') = false then
  begin
    context.GetDialogSystem.ShowWarning('读取配置文件错误');
  end
  else
  begin
    try
      my := tinifile.Create(spath+'..\configs\setPara.ini');
      tempBit := my.ReadInteger('CardPara', 'bit', -1);
      tempCom := my.ReadInteger('CardPara', 'com', -1);
      my.Free;
    except
      context.GetDialogSystem.ShowWarning('读串口设置配置信息发生错误');
    end;
  end;
  cbbBit.Text := IntToStr(tempBit);
  try
    rgcom.ItemIndex := tempCom-1;
  except
  end;
end;

procedure TfaMachinePara.btnOpenClick(Sender: TObject);
begin
  rzstspn1.Caption := '';
  if SmartCardPortStatus then
  begin
    rzstspn1.Caption :='串口已经打开！';
    Exit;
  end;
  SaveToINI;
  OPenFormINI;
end;

procedure TfaMachinePara.btnCloseClick(Sender: TObject);
begin
  rzstspn1.Caption := '';
  if not SmartCardPortStatus then
  begin
    rzstspn1.Caption :='没有需要关闭的串口！';
    Exit;
  end;
  CloseFormINI;
end;

procedure TfaMachinePara.btnAuthClick(Sender: TObject);
var
  re: longint;
  CardManage: TCardManage;
  OutMainKey: string;
  cardLimit:Byte;
  PCM: TPublishCardMes;
  rcardLimit:Integer;
  cardNo:Integer;
  flag:String;
  rDate:string;
  tmpDataSet:TDataset;
begin
  rzstspn1.Caption := '';
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('请先打开串口！');
     Exit;
  end;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    re := CardManage.ReadAuthCardInfo(PCM);
    if re<>0 then
    begin
      rzstspn1.Caption := '读取授权卡失败！';
      Exit;
    end;
    //lblOper.Caption:=PCM.ucLibraryNo;
    {
    if Trim(lblOper.Caption) <>Trim(lblOperCode.Caption) then
    begin
      ShowMessage('该授权卡和登录者不是同一人！');
      Exit;
    end;
    }
    cardNo:=StrToInt(PCM.CardNo);

    WorkView1.FieldByName('交易卡号').Data.SetInteger(cardNo);
    WorkView1.FieldByName('状态').Data.SetInteger(0);
    WVRequest1.SendCommand;
    tmpDataSet:= TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
    try
      flag:=tmpDataSet.fieldbyname('sserial0').AsString;
      rcardLimit:= tmpDataSet.fieldbyname('lvol1').AsInteger;
      rDate := tmpDataSet.fieldbyname('sdate0').AsString;
    except
      rzstspn1.Caption := '无效的授权卡，授权失败！';
      Exit;
    end;
    if Copy(flag,1,2)<>'10' then
    begin
      rzstspn1.Caption := '该卡不是有效的授权卡，授权失败！';
      Exit;
    end;

    if rcardLimit and 2 = 0 then
    begin
      rzstspn1.Caption := '该卡没有在管理中心授权的权限，授权失败！';
      Exit;
    end;

    if rdate<formatdatetime('yyyymmdd',date()) then
    begin
      rzstspn1.Caption := '该授权卡已经过期，授权失败！';
      Exit;
    end;
    re := CardManage.SMT_ReadAuthorWorkKeyAndFlag(OutMainKey,cardLimit);

    if re<>0 then
    begin
      rzstspn1.Caption := '读卡器授权失败！';
      Exit;
    end;
    re := CardManage.ReadMachineAuth(PChar(OutMainKey));
    if re<>0 then
    begin
      rzstspn1.Caption := '读写器授权失败！';
      Exit;
    end;
    SmartCardAuthStatus := True;
    CardManage.ControlBuzzer;
    rzstspn1.Caption := '读卡器授权成功！';
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaMachinePara.SaveToINI;
var
  my: tinifile;
  tempBit: integer;
  tempCom: integer;
  spath : string;
begin
  try
    tempBit := StrToInt(cbbBit.Text);
    tempCom := rgcom.ItemIndex+1;
  except
  end;
  sPath := ExtractFilePath(Application.ExeName);
  if fileexists(spath+'..\configs\setPara.ini') = false then
  begin
    context.GetDialogSystem.ShowWarning('读取配置文件错误');
  end
  else
  begin
    try
      my := tinifile.Create(spath+'..\configs\setPara.ini');
      my.WriteInteger('CardPara', 'bit', tempBit);
      my.WriteInteger('CardPara', 'com', tempCom);
      my.Free;
    except
      context.GetDialogSystem.ShowWarning('写配置文件错误,请将配置文件设置为可写状态！');
    end;
  end;

end;

procedure TfaMachinePara.OPenFormINI;
var
  my: tinifile;
  BaudRate: longint;
  tempCom: integer;
  tempRe: smallint;
  CardManage: TCardManage;
  spath:string;
begin
  sPath := ExtractFilePath(Application.ExeName);
  CardManage := TCardManage.Create;
  if fileexists(spath+'..\configs\setPara.ini') = false then
  begin
    context.GetDialogSystem.ShowError('读取配置文件错误！');
  end
  else
  begin
    try
      my := tinifile.Create(spath+'..\configs\setPara.ini');
      BaudRate := my.ReadInteger('CardPara', 'bit', -1);
      tempCom := my.ReadInteger('CardPara', 'com', -1);
      my.Free;
    except
      context.GetDialogSystem.ShowWarning('读串口设置初始化信息发生错误');
    end;
  end;

  try
    //先关闭串口，然后再打开
    //tempRess := CardManage.CloseSerialPort;

    tempRe := CardManage.IniSerialPort(tempCom, BaudRate);
  finally
    if tempRe = 0 then
    begin
      rzstspn1.Caption := '打开串口成功!';
      SmartCardPortStatus := True;
    end
    else
    begin
      rzstspn1.Caption :='打开串口失败，请检查读写器是否打开以及选择正确的串口和波特率！';
    end;
  end;
  CardManage.Destroy;
end;

procedure TfaMachinePara.CloseFormINI;
var
  tempRe: smallint;
  CardManage: TCardManage;
begin
  CardManage := TCardManage.Create;
  try
    tempRe := CardManage.CloseSerialPort;
  finally
    if tempRe = 0 then
    begin
      rzstspn1.Caption := '串口已经关闭!';
      SmartCardPortStatus := False;
    end
    else
    begin
      rzstspn1.Caption := '关闭串口失败!';
    end;
  end;
  CardManage.Destroy;
end;

procedure TfaMachinePara.btnReadCardClick(Sender: TObject);
var
  PCM: TPublishCardMes;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  st: smallint;
  CardManage: TCardManage;
  re, re2: string;
  TOF: boolean;
  black:LongInt;
  Blackver:string;
  sex:string;
  maxPerCount,maxPerDay:Integer;
  tmpDataSet:TDataSet;
begin
  initCardInfoPosi;
  rzstspn1.Caption := '';
  if PrepareReadCardInfo=False then
    Exit;
  try
    CardManage := TCardManage.Create;
    //FillChar(PCM.ShowCardNo,11,0);
    re := '';
    if CardManage.ReadCardPhyID(re) <> 0 then
    begin
      rzstspn1.Caption :='读卡序列号失败,该卡已经损坏！';
      Exit;
    end
    else
      edtPhyID.Text := re;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      rzstspn1.Caption :='读卡信息失败！错误号: ' + IntToStr(st);
      Exit;
    end
    else
    begin
      if Trim(PCM.ucSexNo)='1' then
        sex := '男'
      else if Trim(PCM.ucSexNo)='2' then
        sex := '女'
      else
        sex := '';
      //交易卡号
      edtCardNo.Text := PCM.CardNo;
      //显示卡号
      edtShowNo.Text :=  PCM.ShowCardNo;//Trim(Copy(PCM.ShowCardNo,1,10));
      //截至日期
      edtEndDate.Text := PCM.DeadLineDate;
      if PCM.DeadLineDate<=FormatDateTime('yyyymmdd',Date) then
        edtEndDate.Font.Color := clRed
      else
        edtEndDate.Font.Color := clBlack;
      //收费类别
      edtFeeType.Text := GetIdObjectName(-43,IntToStr(PCM.CardRightType));
      //客户类别
      edtCustType.Text := GetIdObjectName(-34,Trim(PCM.ucIdentifyNo));
      //姓名
      edtName.Text := PCM.ucName;
      //证件号码
      edtIDCard.Text := PCM.ucCertificateNo;
      //部门
      edtDept.Text := GetIdObjectName(-22,Trim(PCM.ucDepartmentNo));
      //姓别
      edtSex.Text := sex;
      //学工号
      edtStuempNo.Text := PCM.ucCardNo;
      //edtPwd.Text := PCM.ucPwd;
      //客户号
      //edtCustNo.Text := IntToStr(PCM.cut_id);
      SetLength(Blackver,13);
      if CardManage.readCardBlackVer(@black,Blackver)=0 then
      begin
        edtVerNo.Text := Blackver;                //版本号
        if black=0 then
        begin
          edtBalack.Text := '否';                 //是否黑卡
          edtBalack.Font.Color := clBlack;
          edtVerNo.Font.Color := clBlack;
        end;
        if black=1 then
        begin
          edtBalack.Text := '是';
          edtBalack.Font.Color := clRed;
          edtVerNo.Font.Color := clRed;
        end;
      end;

    end;
    //读卡中消费信息
    TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
    if TOF = false then
    begin
      rzstspn1.Caption :='读用户卡消费信息失败！错误号: ' + IntToStr(st);
      Exit;
    end
    else
    begin
      //批次号
      edtPatchNo.Text := Format('%d',[LPI.DealTimes_CurDay]);
      edtMoney.Text := format('%f', [LPI.RemainMoney / 100.0]);
      edtTreadeNum.Text := format('%d', [LPI.DealTimes]);
      edtTradeDate.Text := formatCardShow(LPI.DealYear)+ '年' + formatCardShow(LPI.dealmonth) + '月' +
        formatCardShow(LPI.dealday) + '日' + ' ' + formatCardShow(LPI.dealhour)+':'+formatCardShow(LPI.DealMin);

      re2 := CardManage.ReadCardPsw;                 //卡密码
      if re2 <> 'Error' then
        edtPwd.Text := re2;
      
    end;
    //读取单次消费限额和日消费限额
    if maxPer=1 then
    begin
      st:=CardManage.ReadConsumeLimit(maxPerCount,maxPerDay);
      if st<>0 then
      begin
        rzstspn1.Caption :='读取限额消费信息失败！错误号: ' + IntToStr(st);
        Exit;
      end
      else
      begin
        edtMaxPerCount.Text := FloatToStr(maxPerCount/100);
        edtmaxPerDay.Text := FloatToStr(maxPerDay/100);
      end;
    end
    else
    begin
      edtMaxPerCount.Text := '无';
      edtmaxPerDay.Text := '无';
    end;

    //增加卡状态
    try
      if Trim(edtCardNo.Text)='' then
        Exit;
      WorkView2.FieldByName('卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
      WVRequest2.SendCommand;
      tmpDataSet:= TDataSet(WorkView2.FieldByName('查询结果集').Data.AsObject);
      edtCardStatus.Text := GetIdObjectName(17,tmpDataSet.fieldbyname('sserial0').AsString);
    except

    end;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaMachinePara.btnCancelClick(Sender: TObject);
begin
  Close;
end;

procedure TfaMachinePara.initCardInfoPosi;
var
  i:Integer;
begin
  for i := 0 to grpCardInfo.ControlCount-1 do
  begin
    if grpCardInfo.Controls[i] is TRzEdit then
    begin
      TRzEdit(grpCardInfo.Controls[i]).Text := '';
      //TRzEdit(grpCardInfo.Controls[i]).Height:=22;
    end;
  end;
  for i := 0 to grpCustInfo.ControlCount-1 do
  begin
    if grpCustInfo.Controls[i] is TRzEdit then
    begin
      TRzEdit(grpCustInfo.Controls[i]).Text := '';
      //TRzEdit(grpCustInfo.Controls[i]).Height:=22;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('读写器授权', TfaMachinePara);

end.
