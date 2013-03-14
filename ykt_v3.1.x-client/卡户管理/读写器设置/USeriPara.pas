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
      lblVer.Caption := '���汾ʧ��';
    end;
  finally
    cardManage.Destroy;
  end;
  
  stat1.Font.Color := clBlue;
  initCardInfoPosi;
  btnOpen.Caption := '&O �򿪴���';
  btnOpen.Width := 120;
  btnClose.Caption := '&C �رմ���';
  btnClose.Width := 120;
  btnAuth.Caption := '&A ��д����Ȩ';
  btnAuth.Width := 120;
  btnReadCard.Caption := '&R ��ȡ����Ϣ';
  btnReadCard.Width := 120;
  sPath := ExtractFilePath(Application.ExeName);
  if fileexists(spath+'..\configs\setPara.ini') = false then
  begin
    context.GetDialogSystem.ShowWarning('��ȡ�����ļ�����');
  end
  else
  begin
    try
      my := tinifile.Create(spath+'..\configs\setPara.ini');
      tempBit := my.ReadInteger('CardPara', 'bit', -1);
      tempCom := my.ReadInteger('CardPara', 'com', -1);
      my.Free;
    except
      context.GetDialogSystem.ShowWarning('����������������Ϣ��������');
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
    rzstspn1.Caption :='�����Ѿ��򿪣�';
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
    rzstspn1.Caption :='û����Ҫ�رյĴ��ڣ�';
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
     Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
     Exit;
  end;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    re := CardManage.ReadAuthCardInfo(PCM);
    if re<>0 then
    begin
      rzstspn1.Caption := '��ȡ��Ȩ��ʧ�ܣ�';
      Exit;
    end;
    //lblOper.Caption:=PCM.ucLibraryNo;
    {
    if Trim(lblOper.Caption) <>Trim(lblOperCode.Caption) then
    begin
      ShowMessage('����Ȩ���͵�¼�߲���ͬһ�ˣ�');
      Exit;
    end;
    }
    cardNo:=StrToInt(PCM.CardNo);

    WorkView1.FieldByName('���׿���').Data.SetInteger(cardNo);
    WorkView1.FieldByName('״̬').Data.SetInteger(0);
    WVRequest1.SendCommand;
    tmpDataSet:= TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
    try
      flag:=tmpDataSet.fieldbyname('sserial0').AsString;
      rcardLimit:= tmpDataSet.fieldbyname('lvol1').AsInteger;
      rDate := tmpDataSet.fieldbyname('sdate0').AsString;
    except
      rzstspn1.Caption := '��Ч����Ȩ������Ȩʧ�ܣ�';
      Exit;
    end;
    if Copy(flag,1,2)<>'10' then
    begin
      rzstspn1.Caption := '�ÿ�������Ч����Ȩ������Ȩʧ�ܣ�';
      Exit;
    end;

    if rcardLimit and 2 = 0 then
    begin
      rzstspn1.Caption := '�ÿ�û���ڹ���������Ȩ��Ȩ�ޣ���Ȩʧ�ܣ�';
      Exit;
    end;

    if rdate<formatdatetime('yyyymmdd',date()) then
    begin
      rzstspn1.Caption := '����Ȩ���Ѿ����ڣ���Ȩʧ�ܣ�';
      Exit;
    end;
    re := CardManage.SMT_ReadAuthorWorkKeyAndFlag(OutMainKey,cardLimit);

    if re<>0 then
    begin
      rzstspn1.Caption := '��������Ȩʧ�ܣ�';
      Exit;
    end;
    re := CardManage.ReadMachineAuth(PChar(OutMainKey));
    if re<>0 then
    begin
      rzstspn1.Caption := '��д����Ȩʧ�ܣ�';
      Exit;
    end;
    SmartCardAuthStatus := True;
    CardManage.ControlBuzzer;
    rzstspn1.Caption := '��������Ȩ�ɹ���';
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
    context.GetDialogSystem.ShowWarning('��ȡ�����ļ�����');
  end
  else
  begin
    try
      my := tinifile.Create(spath+'..\configs\setPara.ini');
      my.WriteInteger('CardPara', 'bit', tempBit);
      my.WriteInteger('CardPara', 'com', tempCom);
      my.Free;
    except
      context.GetDialogSystem.ShowWarning('д�����ļ�����,�뽫�����ļ�����Ϊ��д״̬��');
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
    context.GetDialogSystem.ShowError('��ȡ�����ļ�����');
  end
  else
  begin
    try
      my := tinifile.Create(spath+'..\configs\setPara.ini');
      BaudRate := my.ReadInteger('CardPara', 'bit', -1);
      tempCom := my.ReadInteger('CardPara', 'com', -1);
      my.Free;
    except
      context.GetDialogSystem.ShowWarning('���������ó�ʼ����Ϣ��������');
    end;
  end;

  try
    //�ȹرմ��ڣ�Ȼ���ٴ�
    //tempRess := CardManage.CloseSerialPort;

    tempRe := CardManage.IniSerialPort(tempCom, BaudRate);
  finally
    if tempRe = 0 then
    begin
      rzstspn1.Caption := '�򿪴��ڳɹ�!';
      SmartCardPortStatus := True;
    end
    else
    begin
      rzstspn1.Caption :='�򿪴���ʧ�ܣ������д���Ƿ���Լ�ѡ����ȷ�Ĵ��ںͲ����ʣ�';
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
      rzstspn1.Caption := '�����Ѿ��ر�!';
      SmartCardPortStatus := False;
    end
    else
    begin
      rzstspn1.Caption := '�رմ���ʧ��!';
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
      rzstspn1.Caption :='�������к�ʧ��,�ÿ��Ѿ��𻵣�';
      Exit;
    end
    else
      edtPhyID.Text := re;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      rzstspn1.Caption :='������Ϣʧ�ܣ������: ' + IntToStr(st);
      Exit;
    end
    else
    begin
      if Trim(PCM.ucSexNo)='1' then
        sex := '��'
      else if Trim(PCM.ucSexNo)='2' then
        sex := 'Ů'
      else
        sex := '';
      //���׿���
      edtCardNo.Text := PCM.CardNo;
      //��ʾ����
      edtShowNo.Text :=  PCM.ShowCardNo;//Trim(Copy(PCM.ShowCardNo,1,10));
      //��������
      edtEndDate.Text := PCM.DeadLineDate;
      if PCM.DeadLineDate<=FormatDateTime('yyyymmdd',Date) then
        edtEndDate.Font.Color := clRed
      else
        edtEndDate.Font.Color := clBlack;
      //�շ����
      edtFeeType.Text := GetIdObjectName(-43,IntToStr(PCM.CardRightType));
      //�ͻ����
      edtCustType.Text := GetIdObjectName(-34,Trim(PCM.ucIdentifyNo));
      //����
      edtName.Text := PCM.ucName;
      //֤������
      edtIDCard.Text := PCM.ucCertificateNo;
      //����
      edtDept.Text := GetIdObjectName(-22,Trim(PCM.ucDepartmentNo));
      //�ձ�
      edtSex.Text := sex;
      //ѧ����
      edtStuempNo.Text := PCM.ucCardNo;
      //edtPwd.Text := PCM.ucPwd;
      //�ͻ���
      //edtCustNo.Text := IntToStr(PCM.cut_id);
      SetLength(Blackver,13);
      if CardManage.readCardBlackVer(@black,Blackver)=0 then
      begin
        edtVerNo.Text := Blackver;                //�汾��
        if black=0 then
        begin
          edtBalack.Text := '��';                 //�Ƿ�ڿ�
          edtBalack.Font.Color := clBlack;
          edtVerNo.Font.Color := clBlack;
        end;
        if black=1 then
        begin
          edtBalack.Text := '��';
          edtBalack.Font.Color := clRed;
          edtVerNo.Font.Color := clRed;
        end;
      end;

    end;
    //������������Ϣ
    TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
    if TOF = false then
    begin
      rzstspn1.Caption :='���û���������Ϣʧ�ܣ������: ' + IntToStr(st);
      Exit;
    end
    else
    begin
      //���κ�
      edtPatchNo.Text := Format('%d',[LPI.DealTimes_CurDay]);
      edtMoney.Text := format('%f', [LPI.RemainMoney / 100.0]);
      edtTreadeNum.Text := format('%d', [LPI.DealTimes]);
      edtTradeDate.Text := formatCardShow(LPI.DealYear)+ '��' + formatCardShow(LPI.dealmonth) + '��' +
        formatCardShow(LPI.dealday) + '��' + ' ' + formatCardShow(LPI.dealhour)+':'+formatCardShow(LPI.DealMin);

      re2 := CardManage.ReadCardPsw;                 //������
      if re2 <> 'Error' then
        edtPwd.Text := re2;
      
    end;
    //��ȡ���������޶���������޶�
    if maxPer=1 then
    begin
      st:=CardManage.ReadConsumeLimit(maxPerCount,maxPerDay);
      if st<>0 then
      begin
        rzstspn1.Caption :='��ȡ�޶�������Ϣʧ�ܣ������: ' + IntToStr(st);
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
      edtMaxPerCount.Text := '��';
      edtmaxPerDay.Text := '��';
    end;

    //���ӿ�״̬
    try
      if Trim(edtCardNo.Text)='' then
        Exit;
      WorkView2.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
      WVRequest2.SendCommand;
      tmpDataSet:= TDataSet(WorkView2.FieldByName('��ѯ�����').Data.AsObject);
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
  TUIStdClassFactory.Create('��д����Ȩ', TfaMachinePara);

end.
