unit UAReverseConsume;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus, RzPanel;

type
  TfaqhReverseConsume = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    edtSeriNo: TWVEdit;
    WVEdit6: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnReverse: TBitBtn;
    btnReadCard: TBitBtn;
    WVReserveConsume: TWorkView;
    WVRReserveConsume: TWVRequest;
    Label14: TLabel;
    Label13: TLabel;
    edtPwd: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    cbbErrOperNo: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReverseClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhReverseConsume: TfaqhReverseConsume;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhReverseConsume.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhReverseConsume.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhReverseConsume.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('��ѯ����').Data.SetString('3');
  btnReverse.Enabled := False;
  inherited;
  btnReverse.Enabled := True;
end;

procedure TfaqhReverseConsume.btnReverseClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  operDate:string;
  seriId:Integer;
  stationId:Integer;
  cardId:Integer;
  outMoney:Integer;
  balance:Integer;
  CardPhyID:string;
  cm:TCM;
  payCnt,dptCnt:Integer;
  tp:TTRANSPACK;
  tradeDate,tradeTime:string;
  st:Integer;
  operCode:string;
  operPwd:string;
  subsidyNo:Integer;
  phyId:string;
begin
  if preReadCard=False then
    Exit;
  if Application.MessageBox('���Ҫ�����ü�¼����ѿ����õ���д���ϣ�ȷ��Ҫ������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tmpDataSet := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  operDate := tmpDataSet.fieldbyname('sdate3').AsString;
  seriId := tmpDataSet.fieldbyname('lserial1').AsInteger;
  stationId := tmpDataSet.fieldbyname('lwithdraw_flag').AsInteger;

  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    {
    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PATCH_NO);
    }
    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������ԣ�');
      Exit;
    end;
    //��ȡ������
    CardPhyID := cm.getCardSeriNo;
    if CardPhyID='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ������ʧ�ܣ�');
      Exit;
    end;
    //���״���
    try
      //tradeNum:=StrToInt(cm.getCardCnt);
      balance := StrToInt(cm.getCardBalance);
      payCnt := StrToInt(cm.getPayCardCnt);
      dptCnt := StrToInt(cm.getDptCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('��ȡ�����Ѵ���ʧ�ܣ�����ȡ��--'+e.Message);
        Exit;
      end;
    end;

    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    WVReserveConsume.FieldByName('����Ա����').Data.SetString(operPwd);
    WVReserveConsume.FieldByName('������').Data.SetString(CardPhyID);
    WVReserveConsume.FieldByName('����').Data.SetInteger(StrToInt(cm.getCardNo));
    WVReserveConsume.FieldByName('ҵ������').Data.SetString(operDate);
    WVReserveConsume.FieldByName('��ˮ��').Data.SetInteger(seriId);
    WVReserveConsume.FieldByName('�ն˱��').Data.SetInteger(stationId);
    WVReserveConsume.FieldByName('�뿨ֵ').Data.SetInteger(balance);
    WVReserveConsume.FieldByName('��ֵ����').Data.SetInteger(dptCnt);
    WVReserveConsume.FieldByName('�����״���').Data.SetInteger(payCnt);
    WVRReserveConsume.SendCommand;
    cardId := WVReserveConsume.FieldByName('����').Data.AsInteger;
    outMoney := WVReserveConsume.Fieldbyname('����ֵ').Data.AsInteger;
    tradeDate := WVReserveConsume.fieldbyname('ҵ������').Data.AsString;
    tradeTime := WVReserveConsume.fieldbyname('ҵ��ʱ��').Data.AsString;
    if cardId<>StrToInt(cm.getCardNo) then
    begin
      Context.GetDialogSystem.ShowMessage('��Ҫ�����Ŀ��ͷ��õĿ�����ͬһ�ſ��������²���');
      Exit;
    end;
    try
      //preSetMoney(tp);
      ZeroMemory(@tp,SizeOf(tp));
      //�ն˽������к�
      tp.TermSeqno := 1;
      //�ն˱��
      StrCopy(@tp.Termno,PChar(scSiteNo));
      //���׿���
      tp.CardNo := StrToInt(cm.getCardNo);
      //������
      StrCopy(@tp.CardPhyID,PChar(cm.getCardSeriNo));
      //��������
      StrCopy(@tp.TransDate,PChar(tradeDate));
      //����ʱ��
      StrCopy(@tp.TransTime,PChar(tradeTime));
      //����ǰ���
      tp.BefBalance := balance;
      //���׺���
      tp.AftBalance := outMoney;
      //����ǰ��ֵ����
      tp.DptCardCnt := dptCnt;
      //����ǰ���Ѵ���
      tp.PayCardCnt := payCnt;
      //�������κ�
      tp.SubsidyNo := subsidyNo;
      st := ks_setcardbal(@tp);
      if st <>0 then
        Context.GetDialogSystem.ShowMessage('�ڳ���ʱû��д����Ϣ��������ִ�г�������'+inttostr(st))
      else
        cm.beep;
      RzStatusPane1.Caption := WVReserveConsume.fieldbyname('������Ϣ').Data.AsString;
      btnQuery.Click;
    except
      Context.GetDialogSystem.ShowMessage('�ڳ���ʱû��д����Ϣ��������ִ�г������ף�');
    end;
  finally
    cm.Destroy;
  end;
  edtPwd.Text := '';
end;

procedure TfaqhReverseConsume.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtCardNo.Text:='0';
  cardNo := readCardOneInfo(CARD_NO);
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('������ѯʧ�ܣ�����Ϊ��򲻴���!');
    Exit;
  end;
  edtCardNo.Text:=cardNo;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('���ѳ���',TfaqhReverseConsume);

end.