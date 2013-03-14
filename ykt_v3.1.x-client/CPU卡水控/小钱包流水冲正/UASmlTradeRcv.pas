unit UASmlTradeRcv;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,WaterDll;

type
  TfaqhSmlTradeRcv = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    edtSeriNo: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnReadCard: TBitBtn;
    Label13: TLabel;
    edtTBDate: TWVEdit;
    Label14: TLabel;
    edtTEDate: TWVEdit;
    Label15: TLabel;
    cbbNetConn: TWVComboBox;
    Label16: TLabel;
    edtBTime: TWVEdit;
    Label17: TLabel;
    edtEtime: TWVEdit;
    lbl1: TLabel;
    cbb1: TWVComboBox;
    Label18: TLabel;
    WVComboBox5: TWVComboBox;
    WVRSerialRcv: TWVRequest;
    WVSerialRcv: TWorkView;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSmlTradeRcv: TfaqhSmlTradeRcv;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhSmlTradeRcv.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
  btnPrint.Caption :='��  ��';
end;

procedure TfaqhSmlTradeRcv.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('���˿�ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtbdate.SetFocus;
      Exit;
    end;
  if Trim(edtEDate.Text)<>'' then
    if CheckInputDateFormat(edtEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('���˿�ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if (Trim(edtBDate.Text)<>'') and (Trim(edtEDate.Text)<>'') then

  if Trim(edtBDate.Text)>Trim(edtEDate.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('���˿�ʼ���ڲ��ܴ��ڽ������ڣ����������룡');
    edtBDate.SetFocus;
    Exit;
  end;

  if Trim(edtTBDate.Text)<>'' then
    if CheckInputDateFormat(edtTBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('���׿�ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtTBDate.SetFocus;
      Exit;
    end;
  if Trim(edtTEDate.Text)<>'' then
    if CheckInputDateFormat(edtTEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('���׿�ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtTEDate.SetFocus;
      Exit;
    end;
  if (Trim(edtBDate.Text)<>'') and (Trim(edtEDate.Text)<>'') then

  if Trim(edttBDate.Text)>Trim(edttEDate.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('���׿�ʼ���ڲ��ܴ��ڽ������ڣ����������룡');
    edttBDate.SetFocus;
    Exit;
  end;
  if Trim(edtBTime.Text)<>'' then
    if CheckInputTimeFormat(edtBTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼʱ�����벻��ȷ�����������룡');
      edtBTime.SetFocus;
      Exit;
    end;
  if Trim(edteTime.Text)<>'' then
    if CheckInputTimeFormat(edteTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('����ʱ�����벻��ȷ�����������룡');
      edteTime.SetFocus;
      Exit;
    end;
  if Trim(edtBTime.Text)>Trim(edtEtime.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('��ʼʱ�䲻�ܴ��ڽ���ʱ�䣬���������룡');
    edtBTime.SetFocus;
    Exit;
  end;


  WorkView.FieldByName('Ǯ����').Data.SetInteger(0);
  //WorkView.FieldByName('����״̬').Data.SetInteger(33);
  inherited;

end;

procedure TfaqhSmlTradeRcv.btnReadCardClick(Sender: TObject);
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

procedure TfaqhSmlTradeRcv.btnPrintClick(Sender: TObject);
var
  tmpData:TDataSet;
  siteNo,serialNo,custId,cardNo:Integer;
  tradeDate,tradeTime:string;
  tradeAmt:Double;
  smlBal:Integer;
  st:Integer;
  phyId:string;

  //cardno : Integer;                   //���׿���
  custno : Integer;                   //�ͻ���
  custtype : Integer;                 //�ͻ����
  expireddate : string;  //��Ч��
  lockflag : Integer;                 //������־��00 ������FF����
  //Ǯ����Ϣ
  totalmoney : Integer;               //��ֵ�ܽ��
  addtime : string;                   //��ֵʱ��
  addcount : Integer;                 //��ֵ����
  nprice1 : Integer;                   //ˮ��1
  nprice2 : Integer;                   //ˮ��2
  nprice3 : Integer;                   //ˮ��3
  waterPack:TWATERCOMMPACK;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  smlbgNo:Integer;

begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  try
    tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
    siteNo := tmpData.FieldByName('lwithdraw_flag').AsInteger;
    serialNo := tmpData.fieldbyname('lserial1').AsInteger;
    custId := tmpData.FieldByName('lvol1').AsInteger;
    cardNo := tmpData.FieldByName('lvol0').AsInteger;
    tradeDate := tmpData.fieldbyname('sdate0').AsString;
    tradeTime := tmpData.fieldbyname('stime0').AsString;
    tradeAmt := tmpData.fieldbyname('damt0').AsFloat;
    smlbgNo := tmpData.FieldByName('lvol3').AsInteger;
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(ex.Message);
      Exit;
    end;
  end;
  WVSerialRcv.FieldByName('�ն˱��').Data.SetInteger(siteNo);
  WVSerialRcv.FieldByName('�ն���ˮ��').Data.SetInteger(serialNo);
  WVSerialRcv.FieldByName('�ͻ���').Data.SetInteger(custId);
  WVSerialRcv.FieldByName('����').Data.SetInteger(cardNo);
  WVSerialRcv.FieldByName('��������').Data.SetString(tradeDate);
  WVSerialRcv.FieldByName('����ʱ��').Data.SetString(tradeTime);
  WVSerialRcv.FieldByName('���׽��').Data.SetFloat(tradeAmt);
  WVRSerialRcv.SendCommand;
  if (WVSerialRcv.FieldByName('������').Data.AsString<>'0')then
  begin
    Context.GetDialogSystem.ShowMessage(WVSerialRcv.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  smlBal :=WVSerialRcv.FieldByName('СǮ�����').Data.AsInteger;

  //��СǮ����Ϣ
  st := mfcard(phyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('ˮ��Ǯ��Ѱ��ʧ��--'+inttostr(st));
    Exit;
  end;
  preCommWaterPack(waterPack);
  st := ks_water_readmoney(smlbgNo,@waterpack);
  reSt := ks_geterrmsg(PChar(@reErrMsg));
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ȡСǮ��ʧ��,��Ǯ���Ѿ�����-'+reSt+inttostr(st));
    Exit;
  end;
  cardno := waterPack.cardno;                     //���׿���
  custno := waterPack.custno;                     //�ͻ���
  custtype := waterPack.custtype;                 //�ͻ����
  expireddate := waterPack.expireddate;           //��Ч��
  lockflag := waterPack.lockflag;                 //������־��00 ������FF����
  // Ǯ����Ϣ
  //money := waterPack.money;                       //�����
  totalmoney := waterPack.totalmoney;             //��ֵ�ܽ��
  addtime := waterPack.addtime;                   //��ֵʱ��
  addcount := waterPack.addcount;                 //��ֵ����

  nprice1 := waterPack.price1;                     //ˮ��1
  nprice2 := waterPack.price2;                     //ˮ��2
  nprice3 := waterPack.price3;                     //ˮ��3
  preCommWaterPack(waterPack);
  //����СǮ���ṹ��
  waterPack.cardno := cardno;
  waterPack.custno := custno;
  waterPack.custtype := custtype;
  StrCopy(@waterPack.expireddate,PChar(FormatDateTime('yyyymmdd',Date+waterExpiredate)));
  //ShowMessage(waterPack.expireddate);
  waterPack.lockflag := lockflag;
  waterPack.money := smlBal;
  waterPack.totalmoney := totalmoney+smlbal;
  StrCopy(@waterPack.addtime,PChar(addtime));
  waterPack.addcount := addcount+1;
  waterPack.price1 := nprice1;
  waterPack.price2 := nprice2;
  waterPack.price3 := nprice3;
  //ShowMessage(IntToStr(waterPack.money));
  st := ks_water_writemoney(smlbgNo,@waterPack);

  if st = 0 then
  begin
    KNG_beep;
    Context.GetDialogSystem.ShowMessage('СǮ�������ɹ���');
  end
  else
    Context.GetDialogSystem.ShowMessage('дˮ��Ǯ��ʧ�ܣ��뵽������������ý���--'+inttostr(st));
end;

initialization
  TUIStdClassFactory.Create('СǮ����ˮ����',TfaqhSmlTradeRcv);

end.