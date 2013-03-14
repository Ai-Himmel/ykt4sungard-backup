unit UAReverseOpenCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus, RzPanel;

type
  TfaqhReverseOpenCard = class(TfaqhSimpleQueryTemp)
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
    WVRReserveOpenCard: TWVRequest;
    WVReserveOpenCard: TWorkView;
    Label13: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    lbl1: TLabel;
    edtPwd: TWVEdit;
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
  faqhReverseOpenCard: TfaqhReverseOpenCard;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhReverseOpenCard.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
end;

procedure TfaqhReverseOpenCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhReverseOpenCard.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('��ѯ����').Data.SetString('1');
  btnReverse.Enabled := False;
  inherited;
  btnReverse.Enabled := True;
end;

procedure TfaqhReverseOpenCard.btnReverseClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  operDate:string;
  seriId:Integer;
  stationId:Integer;
  cm : TCM;
  ResInt2:Integer;
  phyId:string;
  PCardID:string;
  tradeNum:Integer;
  operCode:string;
  operPwd:string;
  st:integer;
begin
  if Application.MessageBox('���Ҫ�����ü�¼����ѿ����õ���д���ϣ�ȷ��Ҫ������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tmpDataSet := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(PCardID);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(DPT_CARD_CNT);    //ʹ�ó�ֵ���״���
    //cm.setfieldreadmode(CARD_SERI_NO);
    if cm.readCard(PCardID)<>0 then
    begin
      //Context.GetDialogSystem.ShowMessage('�������״���ʧ�ܣ������ԣ�');
      //Exit;
      tradeNum := 0;
    end
    else
    begin
      //��ȡ���״���
      if cm.getDptCardCnt='' then
      begin
        tradeNum := 0;
      end
      else
      begin
        tradeNum := StrToInt(cm.getDptCardCnt);
      end;
    end;
    operDate := tmpDataSet.fieldbyname('sdate3').AsString;
    seriId := tmpDataSet.fieldbyname('lserial1').AsInteger;
    stationId := tmpDataSet.fieldbyname('lwithdraw_flag').AsInteger;
    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    //WorkView.FieldByName('������').Data.SetString(operPwd);
    WVReserveOpenCard.FieldByName('ҵ������').Data.SetString(operDate);
    WVReserveOpenCard.FieldByName('��ˮ��').Data.SetInteger(seriId);
    WVReserveOpenCard.FieldByName('�ն˱��').Data.SetInteger(stationId);
    WVReserveOpenCard.FieldByName('���״���').Data.SetInteger(tradeNum);
    //WVReserveOpenCard.FieldByName('��֤����Ա').Data.SetString(Trim(edtOper.text));
    WVReserveOpenCard.FieldByName('����Ա����').Data.SetString(operPwd);
    WVReserveOpenCard.FieldByName('�Ƿ���Ȩ').Data.SetString('1');
    WVRReserveOpenCard.SendCommand;
    phyId := WVReserveOpenCard.FieldByName('������').Data.AsString;
    {
    //ȡ������
    PCardID := cm.getCardSeriNo;
    if PCardID='' then
    begin
      Context.GetDialogSystem.ShowMessage('��������ʧ�ܣ������³����ý��ף�');
      exit;
    end;
    }
    if PCardID<>phyId then
    begin
      Context.GetDialogSystem.ShowMessage('Ҫ�����Ŀ��ͷ��õĿ�����ͬһ�ſ��������²�����');
      Exit;
    end;
    try
      ResInt2 := cm.clearCard(WVReserveOpenCard);
      if ResInt2=0 then
      begin
        cm.beep;
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ������ɹ���');
        RzStatusPane1.Caption := WVReserveOpenCard.fieldbyname('������Ϣ').Data.AsString;
        btnQuery.Click;
      end
      else
        Context.GetDialogSystem.ShowMessage('����ʱд����Ϣʧ�ܣ��뵥��д�ÿ������Ϣ-'+inttostr(ResInt2));
    except
      Context.GetDialogSystem.ShowMessage('����ʱд����Ϣʧ�ܣ��뵥��д�ÿ������Ϣ��');
    end;
  finally
    cm.Destroy;
  end;
  edtPwd.Text := '';
end;

procedure TfaqhReverseOpenCard.btnReadCardClick(Sender: TObject);
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
  TUIStdClassFactory.Create('��������',TfaqhReverseOpenCard);

end.