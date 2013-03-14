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
    procedure edtEnabledT;                    //ʹ�༭��Ϊ����
    procedure resultQuery;                    //��ѯ���
    procedure clearEdt;                       //��ձ༭������
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
  CardNo:Integer;           //���׿���
  showCardNo:string;        //��ʾ����
  cardEndDate:string;       //��ʹ�ý�������
  feeType:Integer;          //�շ����
  custType:Integer;         //�ͻ����
  custName:string;          //�ͻ�����
  cardID:string;            //���֤��
  depNo:string;             //���Ŵ���
  sex:string;               //�Ա�
  stuempNo:string;          //ѧ����
  cardBalance:Integer;      //�����
  cardpwd:string;           //������
  isFormation:Char;         //�Ƿ��ʽ����һ����
  cardTradeNum:Integer;     //�����״���
  patchNO:Integer;          //�������κ�
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
    Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
    Exit;
  end;
  if not SmartCardAuthStatus then
  begin
    Context.GetDialogSystem.ShowWarning('����Ϊ��д����Ȩ��');
    Exit;
  end;
  CardManage := nil;
  try
    //���¶�ȡ�����ţ��ж��Ƿ��Ҫ���µ�������һ��
    CardManage := TCardManage.Create;
    if CardManage.ReadCardPhyID(PCardID)=0 then
    begin
      if PCardID<>trim(tempPCardID) then
      begin
        Context.GetDialogSystem.ShowMessage('����ʱ��ʹ��ͬһ�ſ���');
        Exit;
      end;
    end;
    rType := Copy(cbbRType.Text,1,Pos('-',cbbRType.Text)-1);
    if (rType='') or (rType='-') then
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ��������ͣ�');
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
      RzStatusPane1.Caption :='��ȡǮ����Ϣʧ�ܣ�';
    end;

    WorkView.FieldByName('����').Data.SetInteger(strtoint(edtcCardNo.text));
    WorkView.FieldByName('������').Data.Setstring(PCardID);
    WorkView.FieldByName('����������').Data.Setstring(edtEndDate.text);
    WorkView.FieldByName('�����').Data.SetInteger(cardmoney);
    WorkView.FieldByName('���״���').Data.SetInteger(tradeNum);
    WorkView.FieldByName('��������').Data.Setstring(rType);
    if maxPer=1 then
    begin
      try
        WorkView.FieldByName('�뵥���޶�').Data.SetFloat(StrToFloat(edtMaxPercount.text));
        WorkView.FieldByName('�����޶�').Data.SetFloat(StrToFloat(edtMaxPerDay.Text));
      except
        Context.GetDialogSystem.ShowMessage('��������Ч�ĵ����޶�����޶');
        Exit;
      end;
    end
    else
    begin
      WorkView.FieldByName('�����޶�').Data.SetInteger(0);
      WorkView.FieldByName('���޶�').Data.SetInteger(0);
    end;
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger=0 then
    begin
      CardNo:=WorkView.fieldbyname('����').Data.AsInteger;
      showCardNo:=WorkView.fieldbyname('��ʾ����').Data.AsString;
      cardEndDate:=WorkView.fieldbyname('����������').Data.AsString;
      feeType:=WorkView.fieldbyname('�շ����').Data.AsInteger;
      custType:=WorkView.fieldbyname('�ͻ����').Data.AsInteger;
      custName:=WorkView.fieldbyname('����').Data.AsString;
      cardID:=WorkView.fieldbyname('֤������').Data.AsString;
      depNo:=WorkView.fieldbyname('���Ŵ���').Data.AsString;
      sex:=WorkView.fieldbyname('�Ա�').Data.AsString;
      stuempNo:=WorkView.fieldbyname('ѧ����').Data.AsString;
      cardBalance:=WorkView.fieldbyname('�����').Data.AsInteger;
      isFormation := Char('N');
      cardTradeNum := WorkView.fieldbyname('���״���').Data.AsInteger;
      patchNO  := WorkView.fieldbyname('�������κ�').Data.AsInteger;
      cardpwd := WorkView.fieldbyname('������').Data.AsString;

      if rType='1' then
      begin
        strcopy(@PCM.CardNo, PChar(IntToStr(CardNo)));              //���׿���
        strcopy(@PCM.ShowCardNo, PChar(showCardNo));                //��ʾ����
        strcopy(@PCM.DeadLineDate, PChar(cardEndDate));             //��ֹ����
        PCM.CardRightType := feeType;                               //�շ�����
        strcopy(@PCM.ucIdentifyNo, PChar(IntToStr(custType)));      //�ͻ�����
        strcopy(@PCM.ucName, PChar(custName));                      //����
        strcopy(@PCM.ucCertificateNo, PChar(cardID));               //���֤��
        strcopy(@PCM.ucDepartmentNo, PChar(depNo));                 //����
        strcopy(@PCM.ucSexNo, PChar(sex));                          //�Ա�
        strcopy(@PCM.ucCardNo, PChar(stuempNo));                    //ѧ����
        strcopy(@PCM.ucPwd, PChar(cardpwd));                        //������
        //PCM.Money := cardBalance;                                 //�����
        PCM.isFormat := isFormation;                                //�Ƿ��ʽ����һ����
        
        st := CardManage.UpdateCardBasicInfo(PCM);
        //���õ��������޶���������޶�
        if maxper=1 then
        begin
          maxPerCount := WorkView.fieldbyname('�����޶�').Data.AsInteger;
          maxPerDay := WorkView.fieldbyname('���޶�').Data.AsInteger;
          rst := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
        end;

        if (st<>0) then
        begin
          Context.GetDialogSystem.ShowWarning('���¿���Ϣʧ��--'+inttostr(st));
          exit;
        end;
        if (rst<>0) then
        begin
          Context.GetDialogSystem.ShowMessage('���¿������޶�͵����޶�ʧ��--'+inttostr(rst));
          Exit;
        end;
      end
      else if rType='2' then  //������Ч��
      begin
        st := CardManage.ChangeDeadLineDate(cardEndDate);
      end
      else if rType='3' then  //���¿����������κ�
      begin
        stPNo := CardManage.changePatchNo(patchNO);
        st := CardManage.PacketSetMoney2(cardBalance,cardTradeNum);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('���¿����ʧ��--'+inttostr(st));
          exit;
        end;
        if stPNo<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('���¿��������κ�ʧ��--'+inttostr(st));
          exit;
        end;
      end
      else if rType='4' then  //��д����Ϣ
      begin
        strcopy(@PCM.CardNo, PChar(IntToStr(CardNo)));              //���׿���
        strcopy(@PCM.ShowCardNo, PChar(showCardNo));                //��ʾ����
        strcopy(@PCM.DeadLineDate, PChar(cardEndDate));             //��ֹ����
        PCM.CardRightType := feeType;                               //�շ�����
        strcopy(@PCM.ucIdentifyNo, PChar(IntToStr(custType)));      //�ͻ�����
        strcopy(@PCM.ucName, PChar(custName));                      //����
        strcopy(@PCM.ucCertificateNo, PChar(cardID));               //���֤��
        strcopy(@PCM.ucDepartmentNo, PChar(depNo));                 //����
        strcopy(@PCM.ucSexNo, PChar(sex));                          //�Ա�
        strcopy(@PCM.ucCardNo, PChar(stuempNo));                    //ѧ����
        strcopy(@PCM.ucPwd, PChar(cardpwd));                        //������
        PCM.Money := cardBalance;                                   //�����
        PCM.isFormat := isFormation;                                //�Ƿ��ʽ����һ����
        
        st := CardManage.PublishACard(PCM);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('��д��������Ϣʧ��,����д--'+inttostr(st));
          exit;
        end;

        //���õ��������޶���������޶�
        //���õ��������޶���������޶�
        if maxper=1 then
        begin
          maxPerCount := WorkView.fieldbyname('�����޶�').Data.AsInteger;
          maxPerDay := WorkView.fieldbyname('���޶�').Data.AsInteger;
          rst := cardManage.SetConsumeLimit(maxPerCount,maxPerDay);
        end;

        if (rst<>0) then
        begin
          Context.GetDialogSystem.ShowMessage('���¿������޶�͵����޶�ʧ��--'+inttostr(rst));
          Exit;
        end;

        stPNo := CardManage.changePatchNo(patchNO);
        st := CardManage.PacketSetMoney2(cardBalance,cardTradeNum);
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('��д�����ʧ�ܣ���ִ�и�������Ϊ4�Ĳ���--'+inttostr(st));
          exit;
        end;
        if stPNo<>0 then
        begin
          Context.GetDialogSystem.ShowWarning('��д���������κ�ʧ�ܣ���ִ�и�������Ϊ4�Ĳ���--'+inttostr(st));
          exit;
        end;

      end
      else if rType='5' then  //��տ���Ϣ
      begin
        st := CardManage.ClearCard;
        if st<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('��տ���Ϣʧ��--'+inttostr(st));
          Exit;
        end;
      end;
      CardManage.ControlBuzzer;
      clearEdt;
      Context.GetDialogSystem.ShowSuccess('���¿���Ϣ�ɹ���');
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
  WorkView1.FieldByName('����').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ���').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ����').Data.SetInteger(0);
  WorkView1.FieldByName('�շ����').Data.SetInteger(0);
  WorkView1.FieldByName('Ǯ����').Data.SetInteger(0);
  WorkView1.FieldByName('������').Data.SetString(edtcPhyId.Text);
  WVRequest1.SendCommand;
  if WorkView1.fieldbyname('������').data.AsInteger<>0 then
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
      context.GetDialogSystem.ShowMessage('��������ʧ�ܣ��ÿ��Ѿ��𻵣�');
      Result:=False;
      Exit;
    end;
  
    //��ȡ���׿���
    if CardManage.ReadExCardID(cardNo) <> 0 then
      RzStatusPane1.Caption := '��ȡ���׿���ʧ�ܣ�'
    else
      edtcCardNo.Text := cardNo;
    tempPCardID := phycardid;
    //��ȡ������Ϣ
    if CardManage.ReadCardInfo(PCM) = 0 then
    begin
      //����
      edtcName.Text := PCM.ucName;
      //������
      edtcPhyId.Text := phycardid;
      //֤������
      edtcIdCard.Text := PCM.ucCertificateNo;
      //ѧ����
      edtcStuempNo.Text := PCM.ucCardNo;
      //��������
      edtcEndDate.Text := PCM.DeadLineDate;
      //��ʾ����
      edtcShowNo.Text := PCM.ShowCardNo;
      //�շ����
      edtcFeeType.Text := GetIdObjectName(-43,IntToStr(PCM.CardRightType));
      //�ͻ����
      edtCCustType.Text := GetIdObjectName(-34,Trim(PCM.ucIdentifyNo));
      //����
      edtCDept.Text := GetIdObjectName(-22,Trim(PCM.ucDepartmentNo));
      //�Ա�
      edtCSex.Text := GetIdObjectName(39,Trim(PCM.ucSexNo));
      
      if CardManage.ReadCardConsumeInfo(LPI, nPacketNo)=True then
      begin
        edtcBalance.Text := format('%f', [LPI.RemainMoney / 100.0]);
        edtCTradeNum.Text := format('%d', [LPI.DealTimes]);
        edtCPatchNo.Text := Format('%d',[LPI.DealTimes_CurDay]);
      end
      else
      begin
        RzStatusPane1.Caption :='��ȡǮ����Ϣʧ�ܣ�';
      end;
    end
    else
    begin
      RzStatusPane1.Caption :='��ȡ����Ϣ����ʧ�ܣ�';
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
        RzStatusPane1.Caption :='��ȡ�������޶�����޶�ʧ�ܣ�';
      end;
    end
    else
    begin
      edtMaxcPerCount.Text := '��';
      edtcMaxPerDay.Text := '��';
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
    tempDataSet := WorkView1.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
    //���׿���
    edtCardNo.Text := tempDataSet.FieldByName('lvol0').AsString;
    //��ʹ�ý�ֹ����
    edtEndDate.Text := tempDataSet.FieldByName('sdate2').AsString;
    //����
    edtName.Text := tempDataSet.FieldByName('sall_name').AsString;
    //֤������
    edtIDCard.Text := tempDataSet.FieldByName('semail2').AsString;
    //ѧ����
    edtNo.Text := tempDataSet.FieldByName('spager').AsString;
    //��ʾ����
    edtShowCardNo.Text := tempDataSet.FieldByName('sorder0').AsString;
    //�����
    edtBalance.Text := tempDataSet.FieldByName('damt5').AsString;
    //������
    edtPhyID.Text := tempDataSet.FieldByName('sstation1').AsString;
    //�ͻ����
    edtCustType.Text:= GetIdObjectName(-34,tempDataSet.FieldByName('lsafe_level2').AsString);
    //�շ����
    edtFeeType.Text:=GetIdObjectName(-43,tempDataSet.FieldByName('lvol5').AsString);
    //���ű��
    edtDept.Text := GetIdObjectName(-22,tempDataSet.FieldByName('scert_no').AsString);
    //�Ա�
    edtSex.Text := GetIdObjectName(39,tempDataSet.FieldByName('smarket_code2').AsString);
    //������
    edtPhyID.Text := tempDataSet.fieldbyname('sstation1').AsString;
    //���״���
    edtTradeNum.Text := tempDataSet.fieldbyname('lvol6').AsString;
    //�������κ�
    edtPatchNo.Text :=  tempDataSet.fieldbyname('lvol10').AsString;
    if maxPer=1 then
    begin
      //���޶�
      edtMaxPerDay.Text :=  tempDataSet.fieldbyname('damt12').AsString;
      //�����޶�
      edtMaxPercount.Text :=  tempDataSet.fieldbyname('damt11').AsString;
    end
    else
    begin
      edtMaxPerCount.Text := '��';
      edtMaxPerDay.Text := '��';
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
      RzStatusPane1.Caption := '���û���������Ϣʧ�ܣ�';
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
  TUIStdClassFactory.Create('����Ϣ����', TfaqhUpdateCardInfo);

end.
