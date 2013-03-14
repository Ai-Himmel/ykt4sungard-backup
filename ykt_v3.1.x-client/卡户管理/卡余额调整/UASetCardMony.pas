unit UASetCardMony;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, UtCardDll, RzEdit,
  Buttons, RzPanel, RzRadGrp;

type
  TfaqhSetCardMony = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    grp2: TGroupBox;
    WVLabel3: TWVLabel;
    edtAfterMoney: TRzEdit;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    edtmoneymoneymoney: TRzNumericEdit;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    rzstspn1: TRzStatusPane;
    rgDirection: TRzRadioGroup;
    edtMoney: TRzEdit;
    rzstspn2: TRzStatusPane;
    edtTradeNum: TRzEdit;
    rzstspn3: TRzStatusPane;
    rzstspn4: TRzStatusPane;
    cbbErrOperNo: TWVComboBox;
    edtPwd: TWVEdit;
    rzstspn5: TRzStatusPane;
    edtLibMoney: TRzEdit;
    rzstspn6: TRzStatusPane;
    edtCardBal: TRzEdit;
    procedure btnMoneyInClick(Sender: TObject);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure edtmoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    oldPhyId:string;
    function readCardInfo(CardManage:TCardmanage): Boolean;
    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCardManage);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetCardMony: TfaqhSetCardMony;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaqhSetCardMony.Init;
begin
  inherited;
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
end;

procedure TfaqhSetCardMony.btnMoneyInClick(Sender: TObject);
var
  CardPhyID: string;
  tradeNum:Integer;
  balance:Integer;
  OutMoney: Integer;

  //rCardNo:Integer;
  rTradeDate:string;
  rStationNo:Integer;
  SeilID: integer;
  CardManage: TCardManage;
  TOF: Integer;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  NewMoney: Integer;
  ragion:Integer;
  operCode:string;
  operPwd:string;
begin
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0')
    or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('����Ľ��С��λ������Ϊ�ջ�0��');
    edtMoney.SetFocus;
    Exit;
  end;
  try
    if StrToFloat(edtMoney.Text)>0 then

  except
    Context.GetDialogSystem.ShowMessage('��������Ч�ĵ�����');
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
      Context.GetDialogSystem.ShowMessage('��ʹ��ͬһ�ſ��������ÿ���');
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
    if rgDirection.ItemIndex=0 then
      ragion := 1
    else
      ragion := -1;
    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    //WorkView.FieldByName('������').Data.SetString(operPwd);
    WorkView.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('������').Data.SetString(CardPhyID);
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    WorkView.FieldByName('���״���').Data.SetInteger(tradeNum);
    WorkView.FieldByName('��֤����').Data.SetString(operPwd);
    WorkView.FieldByName('����').Data.SetInteger(ragion);
    WorkView.FieldByName('�������').Data.SetFloat(StrToFloat(edtMoney.Text));
    MainRequest.SendCommand;
    if WorkView.fieldbyname('������').data.asinteger<>0 then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
      Exit;
    end;
    OutMoney := WorkView.FieldByName('�������').Data.AsInteger;
    SeilID := WorkView.FieldByName('��ˮ��').Data.AsInteger;
    //rCardNo := WorkView.FieldByName('����').Data.AsInteger;
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

function TfaqhSetCardMony.readCardInfo(CardManage: TCardmanage): Boolean;
var
  CardExID: string;
  PCM: TPublishCardMes;
  TOF: boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  cardPhyId:string;
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
    edtCardBal.Text := edtCardMoney.Text;
    edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
    tradeNum := LPI.DealTimes;
    edtTradeNum.Text := IntToStr(tradeNum);
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
  
  edtLibMoney.Text := (WorkView1.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('damt1').AsString;
  {
  if Copy(CardState,1,4) <> '1000' then
  begin
    CardManage.ControlBuzzer;
    CardManage.ControlBuzzer;
    Context.GetDialogSystem.ShowMessage('�ÿ���������״̬�Ŀ������ܵ�������');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  }
  Result := True;
end;

procedure TfaqhSetCardMony.btnReadCardInfoClick(Sender: TObject);
var
  CardManage:TCardManage;
begin
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    if readCardInfo(CardManage)=False then
      Exit;
    btnMoneyIn.Enabled := True;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhSetCardMony.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('��ȷ��ҪΪ�ÿ����ý��['+edtmoney.Text+'Ԫ]��'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

procedure TfaqhSetCardMony.writeSuccess(wv: TWorkView; money: Integer;
  cm: TCardManage);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.ControlBuzzer;
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('��������', TfaqhSetCardMony);

end.
