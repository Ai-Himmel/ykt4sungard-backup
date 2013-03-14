unit UACardMonyIn;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, UtCardDll, RzEdit,
  Buttons;

type
  TfaqhCardMonyIn = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    grp2: TGroupBox;
    cbbType: TWVComboBox;
    edtTicketNo: TWVEdit;
    WVLabel3: TWVLabel;
    edtAfterMoney: TRzEdit;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    RzStatusPane9: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    lblTip: TLabel;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    WVLabel1: TWVLabel;
    edtmoneymoneymoney: TRzNumericEdit;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    wvrUpdate: TWVRequest;
    wvUpdate: TWorkView;
    procedure btnMoneyInClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
    procedure WVEdit6KeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure cbbTypeKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edtmoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    oldPhyId:string;
    endDate:string;
    function readCardInfo(CardManage:TCardmanage): Boolean;

    procedure setFocus(Key: Word);

    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCardManage);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardMonyIn: TfaqhCardMonyIn;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaqhCardMonyIn.Init;
begin
  inherited;
  lblTip.Caption := '';
  cbbType.ItemIndex:=0;
  edtTicketNo.Enabled := False;
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
end;

procedure TfaqhCardMonyIn.btnMoneyInClick(Sender: TObject);
var
  CardPhyID: string;
  tradeNum:Integer;
  balance:Integer;
  OutMoney: Integer;

  rCardNo:Integer;
  rTradeDate:string;
  rStationNo:Integer;
  SeilID: integer;
  CardManage: TCardManage;
  TOF: Integer;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  NewMoney: Integer;
begin
  {
  if cbbType.ItemIndex=0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���ֵ��ʽ��');
    Exit;
  end;
  }
  if StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1))<>1 then
    if Trim(edtTicketNo.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('������Ʊ�ݺ��룡');
      edtTicketNo.SetFocus;
      Exit;
    end;
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0')
    or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('����Ľ��С��λ������Ϊ�ջ�0��');
    edtMoney.SetFocus;
    Exit;
  end;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    CardPhyID := '';
    if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ʧ�ܣ�');
      //CardManage.Destroy;
      Exit;
    end
    else
    begin
      WorkView.FieldByName('������').Data.SetString(CardPhyID);
    end;
    if oldPhyId <> CardPhyID then
    begin
      Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ����г�ֵ��');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
      Exit;
    end;
    //���״���
    if CardManage.ReadCardConsumeInfo(LPI, nPacketNo) then
    begin
      tradeNum:=StrToInt(format('%d', [LPI.DealTimes]));
      balance := StrToInt(Format('%d',[LPI.RemainMoney]));
    end else
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ�����Ѵ���ʧ�ܣ�����ȡ����');
      //CardManage.Destroy;
      Exit;
    end;

    //���͹��ܺ�
    WorkView.SynchronizeCtrlsToFields;
    WorkView.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('������').Data.SetString(CardPhyID);
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    WorkView.FieldByName('���״���').Data.SetInteger(tradeNum);
    WorkView.FieldByName('��ֵ����').Data.SetInteger(StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1)));
    WorkView.FieldByName('��ֵ���').Data.SetFloat(StrToFloat(edtMoney.Text));
    MainRequest.SendCommand;
    if WorkView.fieldbyname('������').data.asinteger<>0 then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;
    OutMoney := WorkView.FieldByName('�������').Data.AsInteger;
    SeilID := WorkView.FieldByName('��ˮ��').Data.AsInteger;
    rCardNo := WorkView.FieldByName('����').Data.AsInteger;
    rTradeDate := WorkView.FieldByName('ҵ������').Data.AsString;
    rStationNo := WorkView.FieldByName('�ն˱��').Data.AsInteger;


    //���¿����,0�ɹ���-10��ȷ�������������Ϊʧ��
    TOF := CardManage.PacketSetMoney(IntToStr(OutMoney));
    if TOF = 0 then
    begin
      writeSuccess(WorkView,OutMoney,CardManage);
    end
    else if TOF= -10 then
    begin
      newmoney := CardManage.readCardMoney(1);
      if NewMoney=OutMoney then
      begin
        writeSuccess(WorkView,OutMoney,CardManage);
      end
      else
      begin
        RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,rStationNo);
      end;
    end
    else
    begin
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,rStationNo);
    end;

  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeChange(Sender: TObject);
begin
  inherited;
  edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
  begin
    edtmoneymoneymoney.Enabled := True;
    edtTicketNo.Enabled := False;
  end
  else
  begin
    edtmoneymoneymoney.Enabled := True;
    edtTicketNo.Enabled := True;
  end;
end;

procedure TfaqhCardMonyIn.WVEdit6KeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtMoney.Text)=False then
    Key := #0;
end;

function TfaqhCardMonyIn.readCardInfo(CardManage: TCardmanage): Boolean;
var
  CardExID: string;
  PCM: TPublishCardMes;
  TOF: boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  cardPhyId:string;
  CardState:string;
  custEndDate:string;
  st:Integer;
  tradeNum:Integer;
begin
  Result := False;
  if PrepareReadCardInfo=False then
    Exit;
  if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ȡ������ʧ��,�ÿ��Ѿ��𻵣�');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  oldPhyId := CardPhyID;
  CardExID := readCardNo;
  edtCardNo.Text := readCardNo;
  
  if CardManage.ReadCardInfo(PCM) = 0 then
  begin
    edtName.Text := PCM.ucName;
    edtStuempNo.Text := PCM.ucCardNo;
    endDate := PCM.DeadLineDate;
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ��������Ϣʧ�ܣ�');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
  if TOF = True then
  begin
    OldMoney := IntToStr(LPI.RemainMoney);
    edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
    edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
    tradeNum := LPI.DealTimes;
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  //���Ͳ�ѯ���ף��鿴�ÿ��Ƿ�Ϊ������������������������������˳�
  WorkView1.FieldByName('����').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ���').Data.SetInteger(0);
  WorkView1.FieldByName('�ͻ����').Data.SetInteger(0);
  WorkView1.FieldByName('�շ����').Data.SetInteger(0);
  WorkView1.FieldByName('Ǯ����').Data.SetInteger(0);
  WorkView1.FieldByName('������').Data.SetString(CardPhyID);
  try
    WVRequest1.SendCommand;
  except
    on e:exception do
    begin
      Context.GetDialogSystem.ShowWarning(e.message);
      btnReadCardInfo.SetFocus;
      Exit;
    end;
  end;
  
  CardState := (WorkView1.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  custEndDate := (WorkView1.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sdate2').AsString;
  //�����ȡ�Ŀ���Ч�ں�ʵ�ʵ����ڲ����ϣ�����¿���Ϣ
  if Trim(endDate)<>Trim(custEndDate) then
  begin
    st := CardManage.ChangeDeadLineDate(custEndDate);
    //���³ɹ���д��־��ˮ
    if st=0 then
    begin
      wvUpdate.FieldByName('����').Data.SetInteger(strtoint(edtCardNo.text));
      wvUpdate.FieldByName('������').Data.Setstring(CardPhyID);
      wvUpdate.FieldByName('����������').Data.Setstring(custEndDate);
      wvUpdate.FieldByName('�����').Data.SetInteger(StrToInt(OldMoney));
      wvUpdate.FieldByName('���״���').Data.SetInteger(tradeNum);
      wvUpdate.FieldByName('��������').Data.Setstring('2');
      wvUpdate.FieldByName('�����޶�').Data.SetInteger(0);
      wvUpdate.FieldByName('���޶�').Data.SetInteger(0);
      wvrUpdate.SendCommand;
    end;
  end;
  if custEndDate<sysdate then
  begin
    Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ����ڣ����ܳ�ֵ��');
    Exit;
  end;
  
  if Copy(CardState,1,4) <> '1000' then
  begin
    CardManage.ControlBuzzer;
    CardManage.ControlBuzzer;
    Context.GetDialogSystem.ShowMessage('�ÿ���������״̬�Ŀ������ܳ�ֵ��');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  Result := True;
end;

procedure TfaqhCardMonyIn.btnReadCardInfoClick(Sender: TObject);
var
  CardManage:TCardManage;
begin
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    if readCardInfo(CardManage)=False then
      Exit;
    if bjopen=1 then
    begin
      {
      bj(bjcomport,'W');
      bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21����'+trim(edtCardMoney.Text)+'Ԫ$');
      }

      bj(bjcomport,'W');
      bj(bjcomport,'&C11��  ��:'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21�����:'+trim(edtCardMoney.Text)+'?$');
      bj(bjcomport, 't');
      bj(bjcomport, trim(edtCardMoney.Text)+'P'); //
      
    end;
    btnMoneyIn.Enabled := True;
    cbbType.SetFocus;
    lblTip.Caption := '';
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if edtTicketNo.Enabled then
      edtTicketNo.SetFocus
    else
      edtmoney.SetFocus;
  end;
end;

procedure TfaqhCardMonyIn.setFocus(Key: Word);
begin
  if Key=vk_F2 then
    if cbbType.Enabled then
      cbbType.SetFocus;
  if Key=vk_F3 then
    if edtTicketNo.Enabled then
      edtTicketNo.SetFocus;
  if Key=vk_F4 then
      edtmoney.SetFocus;
  if Key=vk_F8 then
    btnReadCardInfo.SetFocus;
  if Key=vk_F9 then
    if btnMoneyIn.Enabled then
      btnMoneyIn.SetFocus;
end;

procedure TfaqhCardMonyIn.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('��ȷ��ҪΪ�ÿ���ֵ['+edtmoney.Text+'Ԫ]��'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

procedure TfaqhCardMonyIn.writeSuccess(wv: TWorkView; money: Integer;
  cm: TCardManage);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.ControlBuzzer;
  if bjopen=1 then
  begin
    {
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11��  ����'+trim(edtName.Text)+'$');
    bj(bjcomport,'&C21��  ֵ��'+trim(edtmoney.Text)+'Ԫ$');
    bj(bjcomport,'&C31����'+trim(edtAfterMoney.Text)+'Ԫ$');
    }

        bj(bjcomport,'&Sc$');
        bj(bjcomport,'&C11��  ��:'+trim(edtName.Text)+'$');
        bj(bjcomport,'&C21��  ֵ:'+trim(edtmoney.Text)+'?$');
        bj(bjcomport, 'B');    //������Ԥ��
        bj(bjcomport, trim(edtmoney.Text)+'P');//����������Ǯ

        bj(bjcomport,'&C31�����:'+trim(edtAfterMoney.Text)+'?$');

        bj(bjcomport, 't'); //�������˻����
        bj(bjcomport, trim(edtAfterMoney.Text)+'P');   //����������Ǯ
        bj(bjcomport,'&C41лл'+'X');
    
  end;

  if chkSaveMoney.Checked=False then
    edtmoney.Text := '0';
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('���ֽ��ֵ', TfaqhCardMonyIn);

end.
