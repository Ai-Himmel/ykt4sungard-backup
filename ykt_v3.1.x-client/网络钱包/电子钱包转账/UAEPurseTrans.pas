unit UAEPurseTrans;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, RzEdit,UtCardDll,
  Buttons, RzPanel, RzRadGrp;

type
  TfaqhEPurseTrans = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    grp2: TGroupBox;
    edtPwd: TWVEdit;
    edtmoney: TWVDigitalEdit;
    WVLabel3: TWVLabel;
    edtAfterMoney: TRzEdit;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    pnlPwd: TRzStatusPane;
    RzStatusPane9: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    lblTip: TLabel;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    rgDirect: TRzRadioGroup;
    procedure btnMoneyInClick(Sender: TObject);
    procedure WVEdit6KeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure rgDirectClick(Sender: TObject);
    procedure rgDirectChanging(Sender: TObject; NewIndex: Integer;
      var AllowChange: Boolean);
  private
    { Private declarations }
    oldPhyId:string;
    function readCardInfo(CardManage:TCardmanage): Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhEPurseTrans: TfaqhEPurseTrans;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaqhEPurseTrans.Init;
begin
  inherited;
  lblTip.Caption := '';
  btnMoneyIn.Enabled:=False;
  edtPwd.MaxLength := 6;
end;

procedure TfaqhEPurseTrans.btnMoneyInClick(Sender: TObject);
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
  TOF: Boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  NewMoney: string;
  pwd:string;
begin
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0')
    or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('����Ľ��С��λ������Ϊ�ջ�0��');
    Exit;
  end;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    CardPhyID := '';
    if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ʧ�ܣ�');
      CardManage.Destroy;
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
      CardManage.Destroy;
      Exit;
    end;
    if rgDirect.ItemIndex=1 then
      if Length(Trim(edtPwd.Text))<>6 then
      begin
        Context.GetDialogSystem.ShowMessage('������6λ�ʻ����룡');
      end;
    if rgDirect.ItemIndex=1 then
    begin
      if Length(edtPwd.Text)<>6 then
      begin
        Context.GetDialogSystem.ShowMessage('������6λ�ʻ����룡');
        Exit;
      end;
      pwd := encCardpwd(0,smartCardPwd,Trim(edtPwd.Text));
    end;
    //���͹��ܺ�
    //WorkView.SynchronizeCtrlsToFields;
    WorkView.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('������').Data.SetString(CardPhyID);
    WorkView.FieldByName('ת�˷���').Data.SetInteger(rgDirect.ItemIndex);
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    WorkView.FieldByName('���״���').Data.SetInteger(tradeNum);
    WorkView.FieldByName('�ʻ�����').Data.SetString(pwd);
    WorkView.FieldByName('������').Data.SetString(edtPwd.Text);
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
    //���¿����
    if CardManage.PacketSetMoney(IntToStr(OutMoney)) <>0 then
    begin
      //д��ʧ�ܽ��лع�����
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,rStationNo);
    end
    else
    begin
      //��ȡ�������
      TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
      if TOF = True then
      begin
        NewMoney := IntToStr(LPI.RemainMoney);
        if StrToInt(NewMoney)<>OutMoney then
        begin
          //�������Ϳ����ȣ�����д��ʧ����Ϣ
          RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,rStationNo);
          Exit;
        end;
        edtAfterMoney.Text := format('%f', [StrToInt(NewMoney) / 100.0]);
        CardManage.ControlBuzzer;
      end
      else
      begin
        //�������ʧ�ܣ�����д��ʧ����Ϣ
        RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,rStationNo);
        //Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
        //CardManage.Destroy;
        Exit;
      end;
      lblTip.Caption := WorkView.FieldByName('������Ϣ').Data.AsString;//'���γ�ֵ:'+edtmoney.Text+'Ԫ�������:'+edtaftermoney.Text+'Ԫ';
      btnMoneyIn.Enabled := False;
      edtPwd.Text := '';
      btnReadCardInfo.SetFocus;
      RzStatusPane2.Caption:=WorkView.FieldByName('������Ϣ').Data.AsString;
    end;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhEPurseTrans.WVEdit6KeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtMoney.Text)=False then
    Key := #0;
end;

function TfaqhEPurseTrans.readCardInfo(CardManage: TCardmanage): Boolean;
var
  CardExID: string;
  PCM: TPublishCardMes;
  TOF: boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  cardPhyId:string;
begin
  Result := False;
  if PrepareReadCardInfo=False then
    Exit;
  if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ȡ������ʧ��,�ÿ��Ѿ��𻵣�');
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
    Exit;
  end;
  TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
  if TOF = True then
  begin
    OldMoney := IntToStr(LPI.RemainMoney);
    edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
    edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  end
  else
  begin
    Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
    Exit;
  end;
  Result := True;
end;

procedure TfaqhEPurseTrans.btnReadCardInfoClick(Sender: TObject);
var
  CardManage:TCardManage;
begin
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    if readCardInfo(CardManage)=False then
      Exit;
    btnMoneyIn.Enabled := True;
    btnMoneyIn.SetFocus;
    lblTip.Caption := '';
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhEPurseTrans.rgDirectClick(Sender: TObject);
begin
  if rgDirect.ItemIndex=0 then
  begin
    pnlPwd.Caption := '������';
    edtPwd.MaxLength := 6;
  end
  else
  begin
    pnlPwd.Caption :='����Ǯ������';
    edtPwd.MaxLength := 8;
  end;

end;

procedure TfaqhEPurseTrans.rgDirectChanging(Sender: TObject;
  NewIndex: Integer; var AllowChange: Boolean);
begin
  edtPwd.Text:='';
  edtmoney.Text := '0';

end;

initialization
  TUIStdClassFactory.Create('����Ǯ��ת��', TfaqhEPurseTrans);

end.
