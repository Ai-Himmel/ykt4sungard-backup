unit UACardRenew_cqcsgl;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  RzSplit, Menus, UIncrementComboBox, CardDll,WaterDll;

type
  TfaqhCardRenew = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    btnRenewCard: TBitBtn;
    grpReleaseCard: TGroupBox;
    WVLabel11: TWVLabel;
    cbbType: TWVComboBox;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    Label4: TLabel;
    edtMoney: TWVEdit;
    Label8: TLabel;
    WVRRenewCard: TWVRequest;
    WVRenewCard: TWorkView;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    WVFeeQuery: TWorkView;
    WVRFeeQuery: TWVRequest;
    WVEdit4: TWVEdit;
    chkSaveMoney: TCheckBox;
    Label10: TLabel;
    edtTicketNo: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnRenewCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure cbbTypeChange(Sender: TObject);
  private
    { Private declarations }
    selectSign : Boolean;
    fMoney:Real;
    procedure getFeeResult;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardRenew: TfaqhCardRenew;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardRenew.Init;
begin
  inherited;
  cbbType.ItemIndex := 0;
  edtTicketNo.Enabled := False;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhCardRenew.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardRenew.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  WorkView.FieldByName('Ǯ����').Data.SetInteger(1);
  WorkView.FieldByName('�����־').Data.SetString('1');
  inherited;
  selectSign := False;
end;

procedure TfaqhCardRenew.btnRenewCardClick(Sender: TObject);
var
  showCardNo:string;
  pCardID:string;
  custId:Integer;
  cardIf:Integer;
  cardId:Integer;
  feeType:string;
  tipInfo:string;
  custName:string;
  fillMoney:Real;
  reCode:Integer;

  waterCard:TWATERINFO;
  cardNo:Integer;
  st:Integer;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
     Context.GetDialogSystem.ShowMessage('û�����ݣ����Ȳ�ѯ��Ȼ���ٽ��в�����');
    Exit;
  end;
  if selectSign=False then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��һ����¼��Ȼ���ٽ��в�����');
    Exit;
  end;
  try
    custName := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
    //ȡ�ͻ���
    custId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
    //ȡ����
    cardId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
    tipInfo := '���Ƿ�ȷ��Ҫ��������Ϊ��'+custname+'���Ŀ���';
  except
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ���쿨����Ա��');
    Exit;
  end;
  if Application.MessageBox(PChar(tipInfo),PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if preReadCard=False then
    Exit;
    //ȡ������
    pCardID := readCardOneInfo(CARD_SERI_NO);
    if pCardID='' then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
      exit;
    end;

    //ȡ����ʾ����
    showCardNo:=readCardOneInfo(SHOW_CARDNO);
    //�շѷ�ʽ
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);

    cardIf := 0;
    WVRenewCard.FieldByName('����Ա').Data.SetString(Context.ParamData(svOperatorNoName).AsString);
    WVRenewCard.FieldByName('��ʾ����').Data.SetString(showCardNo);        //
    WVRenewCard.FieldByName('������').Data.SetString(pCardID);           //
    WVRenewCard.FieldByName('�շѷ�ʽ').Data.SetString(feeType);
    WVRenewCard.FieldByName('Ʊ�ݺ���').Data.SetString(Trim(edtTicketNo.Text));
    WVRenewCard.FieldByName('�ͻ���').Data.SetInteger(custId);
    WVRenewCard.FieldByName('����').Data.SetInteger(cardId);
    try
      WVRenewCard.FieldByName('�շѽ��').Data.SetFloat(StrToFloat(edtMoney.Text));
    except
      Context.GetDialogSystem.ShowMessage('Ӧ�ս���Ϊ��,�����룡');
      edtMoney.SetFocus;
      Exit;
    end;
    WVRenewCard.FieldByName('�տ��ɱ���').Data.SetInteger(cardIf);
    WVRRenewCard.SendCommand;
    if (WVRenewCard.FieldByName('������').Data.AsInteger = 0) then
    begin
      fillMoney := WVRenewCard.FieldByName('����ֵ').data.asfloat;
      RzStatusPane1.Caption:=pubCardNew(WVRenewCard,WVRelCardOk,WVRRelCardOk,pCardID,0,reCode);
      if reCode = 0 then
      begin
        st := mfcard(pCardID);
        //ShowMessage(IntToStr(st));
        cardNo:=WVRenewCard.fieldbyname('����').Data.AsInteger;
        waterCard.cardno := cardNo;
        waterCard.custno := custId;
        waterCard.cardtype := 1;
        st := ks_sr_publishcard(@waterCard);
        KNG_beep;
        if st<>0 then
          Context.GetDialogSystem.ShowMessage('ˮ��Ǯ����ʼ��ʧ�ܣ������³�ʼ��ˮ��Ǯ����');
        //��ʼ��ˮ����Ϣ
      end;
    end
    else
    begin
      getReturn('',WVRenewCard);
      RzStatusPane1.Caption:=WVRenewCard.FieldByName('������Ϣ').Data.AsString;
    end;
    if bjopen=1 then
    begin
      bj(bjcomport,'&Sc$');
      //bj(bjcomport,'W');
      bj(bjcomport,'&C11������'+trim(custName)+'$');
      bj(bjcomport,'&C21Ӧ��:'+floattostr(fMoney)+'$');
      //bj(bjcomport,'&C31ʵ��:'+edtmoney.Text+'$');
      bj(bjcomport,'&C41�����:'+floattostr(fillMoney)+'$');
    end;
end;

procedure TfaqhCardRenew.getFeeResult();
var
  feeType, cardType,custNo: Integer;
  sReturnInfo:string;
  custName:string;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  feeType := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol5').AsInteger;
  cardType := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lsafe_level').AsInteger;
  custNo :=(WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
  custName := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
  WVFeeQuery.FieldByName('�շ����').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('������').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('���ܺ�').Data.SetInteger(846305);
  WVFeeQuery.FieldByName('�ͻ���').Data.SetInteger(custNo);
  WVFeeQuery.FieldByName('�Ƿ񲻼�����').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('������').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('�շ���Ϣ').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('�ܷ���').Data.AsFloat;
    if bjopen=1 then
    begin
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'W');
      bj(bjcomport,'&C11������'+trim(custName)+'$');
      bj(bjcomport,floattostr(fMoney)+'J');
    end;
    if chkSaveMoney.Checked=False then
      edtMoney.Text := floattostr(fMoney);
    //edtEndDate.Text := sEndDate;
    RzStatusPane1.Caption := sReturnInfo;
    selectSign := True;
  end;
end;

procedure TfaqhCardRenew.GridCellClick(Column: TColumn);
begin
  inherited;
  getFeeResult;
end;

procedure TfaqhCardRenew.cbbTypeChange(Sender: TObject);
var
  accMoney:Real;
  feeType : string;
begin
  feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  if feeType='1' then
  begin
    edtTicketNo.Text := '';
    edtTicketNo.Enabled := False;
    edtMoney.Enabled := True;
  end
  else if (feeType='2') or (feeType='3') then
  begin
    edtTicketNo.Enabled := True;
    edtMoney.Enabled := True;
  end
  else if feeType='9' then
  begin
    try
      accMoney := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('damt0').asfloat;
    except
      Context.GetDialogSystem.ShowMessage('���Ȳ�ѯ����¼��Ȼ��ѡ��Ҫ����Ŀ���ѡ���շѷ�ʽ��');
      cbbType.ItemIndex := 0;
      Exit;
    end;
    if accMoney<fMoney then
    begin
       Context.GetDialogSystem.ShowMessage('�ʻ����㣬��ʹ���ֽ𲹰쿨��');
       cbbType.ItemIndex := 0;
    end
    else
    begin
      edtMoney.Enabled := False;
      edtMoney.Text := FloatToStr(fMoney);
      edtTicketNo.Text := '';
      edtTicketNo.Enabled := False;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('���쿨����', TfaqhCardRenew);

end.


