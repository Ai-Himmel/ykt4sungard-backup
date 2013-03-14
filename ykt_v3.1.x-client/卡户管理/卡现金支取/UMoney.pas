unit UMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db, 
  RzStatus, EditExts, RzEdit, Buttons, UtCardDll;

type
  TfaMoney = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    btnReadCardInfo: TBitBtn;
    btnMoneyOut: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    grp2: TGroupBox;
    edtmoney: TWVDigitalEdit;
    WVLabel1: TWVLabel;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    edtAfterMoney: TRzEdit;
    RzStatusPane7: TRzStatusPane;
    lblTip: TLabel;
    WVcashOperCancel: TWorkView;
    WVRcashOperCancel: TWVRequest;
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure btnMoneyOutClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;

    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCardManage);
  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faMoney: TfaMoney;
  OldMoney: string;

implementation
uses KsFrameworks, 
  KSClientConsts;

{$R *.DFM}

procedure TfaMoney.Init;
begin
  inherited;
  btnMoneyOut.Enabled:=false;
  lblTip.Caption := '';
  btnreadcardinfo.setfocus;
end;


procedure TfaMoney.btnReadCardInfoClick(Sender: TObject);
var
  CardExID: string;
  CardManage: TCardManage;
  PCM: TPublishCardMes;
  TOF: boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  CardPhyID:string;
  //ResInt: SmallInt;
begin
  lblTip.Caption := '';
  CardExID:=readCardNo;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;

    if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ʧ��,�ÿ��Ѿ��𻵣�');
      Exit;
    end;
    oldPhyId := CardPhyID;
    
    edtCardNo.Text := CardExID;
    if CardManage.ReadCardInfo(PCM) = 0 then
    begin
      edtName.Text := PCM.ucName;
      edtStuempNo.Text := PCM.ucCardNo;
    end
    else
    begin
      Context.GetDialogSystem.ShowWarning('��ȡ��������Ϣʧ�ܣ�');
      CardManage.Destroy;
      Exit;
    end;
    //��ȡ�������
    TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
    if TOF = True then
    begin
      OldMoney := IntToStr(LPI.RemainMoney);
      edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
      edtAfterMoney.Text :=format('%f', [StrToInt(OldMoney) / 100.0]);
      //edtMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
    end
    else
    begin
      Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
      CardManage.Destroy;
      Exit;
    end;
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

    btnMoneyOut.Enabled:=True;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaMoney.btnMoneyOutClick(Sender: TObject);
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
begin
  if PrepareReadCardInfo=False then
    Exit;

  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //��ȡ������
    CardPhyID := '';
    if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ʧ�ܣ�');
      CardManage.Destroy;
      Exit;
    end
    else
      WorkView.FieldByName('������').Data.SetString(CardPhyID);

    if oldPhyId <> CardPhyID then
    begin
      ShowMessage('��ʹ��ͬһ�ſ�����֧ȡ��');
      btnReadCardInfo.SetFocus;
      btnMoneyOut.Enabled := False;
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
      Exit;
    end;

    if (StrToFloat(edtCardMoney.Text))<(StrToFloat(Trim(edtMoney.Text))) then
    begin
      Context.GetDialogSystem.ShowMessage('��֧ȡ������������');
      Exit;
    end;
    //���͹��ܺ�
    WorkView.SynchronizeCtrlsToFields;
    WorkView.FieldByName('����').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('������').Data.SetString(CardPhyID);
    WorkView.FieldByName('���״���').Data.SetInteger(tradeNum);
    WorkView.FieldByName('�뿨���').Data.SetInteger(balance);
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.asinteger<>0 then
    begin
      getReturn('��֧ȡʧ�ܣ���',WorkView);
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

procedure TfaMoney.writeSuccess(wv: TWorkView; money: Integer;
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

  btnMoneyOut.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('������Ϣ').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('���ֽ�֧ȡ',TfaMoney);

end.
