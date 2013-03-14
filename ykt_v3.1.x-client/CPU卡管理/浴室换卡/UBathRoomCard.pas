unit UBathRoomCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db,IniFiles, 
  RzStatus, EditExts, RzEdit, Buttons, CardDll;

  const overTime=10000;

type
  TfaBathRoomCard = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    btnLock: TBitBtn;
    btnUnlock: TBitBtn;
    TipInfo: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    grpCardInfo: TGroupBox;
    WVLabel5: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtBeforeMoney: TRzEdit;
    RzStatusPane7: TRzStatusPane;
    edtmoney: TWVDigitalEdit;
    WVLabel1: TWVLabel;
    grp2: TGroupBox;
    RzStatusPane8: TRzStatusPane;
    edtBathCardPhyId: TRzEdit;
    RzStatusPane9: TRzStatusPane;
    edtBathCardMoney: TRzEdit;
    RzStatusPane10: TRzStatusPane;
    edtSetMoney: TRzEdit;
    btnSetMoney: TBitBtn;
    RzStatusPane11: TRzStatusPane;
    edtBathCardNO: TRzEdit;
    RzStatusPane2: TRzStatusPane;
    edtAfterMoney: TRzEdit;
    WVLabel2: TWVLabel;
    procedure btnLockClick(Sender: TObject);
    procedure btnUnlockClick(Sender: TObject);
    procedure btnSetMoneyClick(Sender: TObject);
  private
    { Private declarations }
    broomcardmoney:Real;
    procedure clearEdtInfo(grp:TGroupBox);

  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faBathRoomCard: TfaBathRoomCard;

implementation
uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaBathRoomCard.Init;
var
  myfile:TIniFile;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
    
  myfile := nil;
  try
    try
      myfile := TIniFile.Create(appPath+'../configs/SetPara.ini');
      broomcardmoney := myfile.ReadFloat('bathroomcard','cardmoney',0);
      edtSetMoney.Text := FloatToStr(broomcardmoney);
    except
      on e:Exception do
      begin
        ShowMessage('setPara�����ļ���ȡ����--'+e.Message);
      end;
    end;
  finally
    myfile.Destroy;
  end;
end;


procedure TfaBathRoomCard.btnLockClick(Sender: TObject);
var
  cm: TCM;
  CardPhyID:string;
  st:integer;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
begin
  TipInfo.Caption := '';
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    edtCardNo.Text := cm.getCardNo;
    edtName.Text := cm.getCustName;
    edtStuempNo.Text := cm.getStuempNo;
    try
      edtBeforeMoney.Text := format('%f', [StrToInt(cm.getCardBalance) / 100.0]);
    except
      Context.GetDialogSystem.ShowWarning('��ȡ�����ʧ�ܣ�');
      edtBeforeMoney.Text :='0';
    end;
    //�ֻ�����
    cm.clearallfieldwritemode;
    cm.setBlackCardSign(IntToStr(LOCK_CARD));
    st := cm.writeData(cardPhyId);
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '������ʧ�ܣ�����������-'+reSt;
      Exit;
    end;
    cm.beep;
    TipInfo.Caption := '�������ɹ���';
  finally
    cm.Destroy;
  end;
end;

procedure TfaBathRoomCard.btnUnlockClick(Sender: TObject);
var
  CardPhyID,newPhyId: string;
  balance:Integer;
  cm:TCM;
  cardNo,payCnt:Integer;
  tp:TTRANSPACK;
  st:Integer;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;

  nowTime:Cardinal;
begin
  TipInfo.Caption := '';
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      TipInfo.Caption := 'Ѱ��ʧ�ܣ�����úÿ���';
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CUST_NAME);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(STUEMP_NO);
    if cm.readCard(cardPhyId)<>0 then
    begin
      TipInfo.Caption := '������Ϣʧ�ܣ������ԣ�';
      Exit;
    end;

    //���״���
    try
      //dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      //subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
      cardNo := StrToInt(cm.getCardNo);
      
      edtName.Text := cm.getCustName;
      edtCardNo.Text := cm.getCardNo;
      edtStuempNo.Text := cm.getStuempNo;
      edtBeforeMoney.Text := format('%f', [StrToInt(cm.getCardBalance) / 100.0]);
    except
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '��ȡ����Ϣʧ��-'+reSt;
      Exit;
    end;

    if (StrToFloat(edtmoney.Text))=0 then
    begin
      if Application.MessageBox('Ҫ�ۿ�Ľ��Ϊ�㣬��ȷ����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
        Exit;
    end;

    //�ۿ�---------------------------------------------------------------------b
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //������
    tp.PayCode := 3000;
    //���׿���
    tp.CardNo := cardNo;
    //������
    StrCopy(@tp.CardPhyID,PChar(CardPhyID));
    //֧�����״���
    tp.PayCardCnt := payCnt;
    //����ǰ���
    tp.BefBalance := balance;
    //���׽��
    tp.TransAmt := Round(StrToFloat(edtmoney.Text))*100;
    //����Ա����
    StrCopy(@tp.OperCode,PChar(scOperNo));
    tp.ErrCode := SizeOf(tp);
    //��̨������
    st := ks_payinit(@tp);
    if st<>0 then
    begin
      if tp.cRetryFlag<>Char(0) then
      begin
        st := ks_payinit(@tp);
        if st<>0 then
        begin
          reSt := ks_geterrmsg(PChar(@reErrMsg));
          Context.GetDialogSystem.ShowMessage('�ۿ�������ʧ��-'+reSt);
          Exit;
        end;
      end
      else
      begin
        reSt := ks_geterrmsg(PChar(@reErrMsg));
        Context.GetDialogSystem.ShowMessage('�ۿ�������ʧ��-'+reSt);
        Exit;
      end;
    end;    
    //��̨�����˽���
    //��ʼ�ۿ�
    st := ks_setcardbal(@tp);
    if st<>0 then
    begin
      //�ۿ�ʧ�ܣ�����
      if tp.cRetryFlag<>Char(0) then
      begin
        //ѭ��Ѱ��
        nowTime := GetTickCount;
        while (1>0) do
        begin
          if (GetTickCount-nowTime)>overTime then
          begin
            //ʱ�����10�룬��ʾ��ʱ���˳�
            ks_dotransunprove(@tp);
            Context.GetDialogSystem.ShowMessage('Ѱ����ʱ�������²�����ҵ��');
            Exit;
          end;

          st := cm.card(newPhyId);
          if st<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
          end
          else
          begin
            //Ѱ�������ж��Ƿ�Ϊͬһ�ſ���������ǣ���ʾ���·ſ�
            if newPhyId<>CardPhyID then
              Context.GetDialogSystem.ShowMessage('���õĿ��͸ղŷ��õĲ���ͬһ�ſ��������·��ã�')
            else
              Break;
          end;
          Sleep(50);
          Continue;
        end;
        //����һ��
        st := ks_setcardbal(@tp);
        if st<>0 then
        begin
          while (1>0) do
          begin
            //�ж��Ƿ���;�ο�
            if tp.cGetProveFlag>Char(0) then
            begin
              //ѭ��Ѱ��
              nowTime := GetTickCount;
              while (1>0) do
              begin
                if (GetTickCount-nowTime)>overTime then
                begin
                  //ʱ�����10�룬��ʾ��ʱ���˳�
                  ks_dotransunprove(@tp);
                  Context.GetDialogSystem.ShowMessage('Ѱ����ʱ�������²�����ҵ��');
                  Exit;
                end;

                st := cm.card(newPhyId);
                if st<>0 then
                begin
                  Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
                end
                else
                begin
                  //Ѱ�������ж��Ƿ�Ϊͬһ�ſ���������ǣ���ʾ���·ſ�
                  if newPhyId<>CardPhyID then
                    Context.GetDialogSystem.ShowMessage('���õĿ��͸ղŷ��õĲ���ͬһ�ſ��������·��ã�')
                  else
                    Break;
                end;
                Sleep(50);
              end;
              st:=ks_gettransprove(2,tp.PayCardCnt+1);
              if st=0 then
                Break;
              st:=ks_setcardbal(@tp);
              if st=0 then
                Break;
              Continue;
            end
            else
            begin
              reSt := ks_geterrmsg(PChar(@reErrMsg));
              Context.GetDialogSystem.ShowMessage('�ۿ�ʧ��-'+reSt);
              Exit;
            end;
          end;
        end;
      end;
    end;
    //��ʼ��ʽ����
    st := ks_pay(@tp);
    if st<>0 then
    begin
      if(tp.cRetryFlag)<>Char(0) then
      begin
        st := ks_pay(@tp);
        if st<>0 then
        begin
          reSt := ks_geterrmsg(PChar(@reErrMsg));
          Context.GetDialogSystem.ShowMessage('����ʧ��-'+reSt);
          Exit;
        end;
      end;
    end;

    //���˳ɹ�����ʼ����
    cm.clearallfieldwritemode;
    cm.setfieldwritemode(BLACK_CARD_SIGN);
    cm.setBlackCardSign(IntToStr(NORMAL_CARD));
    st := cm.writeData(cardPhyId);
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      Context.GetDialogSystem.ShowMessage('����ʧ�ܣ�����¿���Ϣ-'+reSt);
      Exit;
    end;

    //��ȡ�ۿ�����
    cm.clearallfieldwritemode;
    cm.setfieldreadmode(CARD_BALANCE);
    st := cm.readCard(cardPhyId);
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '�ض�����Ϣʧ��-'+reSt;
    end;
    try
      edtAfterMoney.Text := format('%f', [StrToInt(cm.getCardBalance) / 100.0]);
    except

    end;
    edtmoney.Text := '0';
    cm.beep;
    TipInfo.Caption := '�ۿ�ɹ���';
    //cm.halt;
    //-------------------------------------------------------------------------e
  finally
    cm.Destroy;
  end;

end;

procedure TfaBathRoomCard.btnSetMoneyClick(Sender: TObject);
var
  cm: TCM;
  CardPhyID:string;
  st:integer;
  reErrMsg:array[0..255] of Char;
  tp:TTRANSPACK;
  rest:PChar;
  cardNo:string;
  payCnt,dptCnt,subsidyNo:Integer;

begin
  TipInfo.Caption := '';
  clearEdtInfo(grpCardInfo);
  if preReadCard=False then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      TipInfo.Caption := 'Ѱ��ʧ�ܣ�����úÿ���';
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);
    if cm.readCard(cardPhyId)<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '������Ϣʧ��--'+reSt;
      Exit;
    end;
    edtBathCardPhyId.Text := cardPhyId;
    cardNo := cm.getCardNo;
    edtBathCardNO.Text := cardNo;
    try
      edtBathCardMoney.Text := format('%f', [StrToInt(cm.getCardBalance) / 100.0]);
      edtmoney.Text := FloatToStr(broomcardmoney-StrToFloat(edtBathCardMoney.Text));
      
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
    except
      edtBathCardMoney.Text := '0';
      edtmoney.Text := '0';
      TipInfo.Caption := '��ȡ�����ʧ�ܣ�';
      Exit;
    end;

    //����mf�����ΪĬ�Ͻ��
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˽������к�
    tp.TermSeqno := 1;
    //�ն˱��
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //���׿���
    tp.CardNo := StrToInt(cardNo);
    //������
    StrCopy(@tp.CardPhyID,PChar(CardPhyID));
    //��������
    StrCopy(@tp.TransDate,PChar(FormatDateTime('yyyymmdd',Date)));
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(FormatDateTime('hhmmss',Now)));
    //����ǰ���
    tp.BefBalance := Round(StrToFloat(edtBathCardMoney.Text)*100);
    //���׺���
    tp.AftBalance := Round(broomcardmoney*100);
    //����ǰ��ֵ����
    tp.DptCardCnt := dptCnt;
    //����ǰ���Ѵ���
    tp.PayCardCnt := payCnt;
    //����ǰ��������
    tp.SubsidyNo := subsidyNo;
    st := ks_setcardbal(@tp);
    if st<>0 then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      TipInfo.Caption := '���ÿ����ʧ��--'+reSt;
    end
    else
    begin
      cm.beep;
      TipInfo.Caption := '���ÿ����ɹ�������ֻ����ۿ';
      //Context.GetDialogSystem.ShowMessage('���ÿ����ɹ�������ֻ����ۿ');
      btnUnlock.SetFocus;
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaBathRoomCard.clearEdtInfo(grp: TGroupBox);
var
  i:Integer;
begin
  for i:=0 to grp.ControlCount-1 do
  begin
    if grp.Controls[i] is TRzEdit then
      TRzEdit(grp.Controls[i]).Text := '';
  end;
end;

initialization
  TUIStdClassFactory.Create('ԡ�һ���',TfaBathRoomCard);

end.
