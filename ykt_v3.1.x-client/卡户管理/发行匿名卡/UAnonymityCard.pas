unit UAnonymityCard;

interface
              
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls,
  UICtrls, WVCtrls, Mask, UtCardDll, SmartCardCommon,Db,
  RzPanel, RzStatus, RzButton, RzRadChk, Buttons, UIncrementComboBox,
  EditExts;

type
  TfaqhAnonyCard = class(TfaqhInputTemp)
    UIPanel3: TUIPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    WVLabel3: TWVLabel;
    WVLabel4: TWVLabel;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVLabel11: TWVLabel;
    WVLabel12: TWVLabel;
    WVLabel10: TWVLabel;
    WVLabel9: TWVLabel;
    WVLabel8: TWVLabel;
    WVLabel7: TWVLabel;
    grp1: TGroupBox;
    edtDate: TWVEdit;
    edtTicketNo: TWVEdit;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    lbl1: TLabel;
    WVFeeQuery: TWorkView;
    WVRFeeQuery: TWVRequest;
    WVRReleaseCard: TWVRequest;
    WVReleaseCard: TWorkView;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    RzStatusPane7: TRzStatusPane;
    cbbType: TWVComboBox;
    Label1: TLabel;
    btnReleaseCard: TBitBtn;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    procedure edtDateExit(Sender: TObject);
    procedure edtmoneyKeyPress(Sender: TObject; var Key: Char);
    procedure edtTicketNoKeyPress(Sender: TObject; var Key: Char);
    procedure cbbCardTypeChange(Sender: TObject);
    procedure cbbFeeTypeChange(Sender: TObject);
    procedure btnReleaseCardClick(Sender: TObject);
  private
    { Private declarations }
   //procedure lineWriteCard;

    procedure getFeeResult;
  public
    { Public declarations }
    procedure Init;override;
  end;

var
  faqhAnonyCard: TfaqhAnonyCard;

implementation
uses KSFrameWorks, KSClientConsts;

{$R *.DFM}

procedure TfaqhAnonyCard.Init;
begin
  inherited;
  //cbbFeeType.ItemIndex := 0;
  //getFeeResult;
  edtDate.Text:=formatdatetime('yyyymmdd',(Date()+365));
  edtmoney.Text := '0';
end;

procedure TfaqhAnonyCard.edtDateExit(Sender: TObject);
begin
  inherited;
  if CheckInputDateFormat(edtDate.Text)=false then
  begin
    Context.GetDialogSystem.ShowMessage('����������������������');
    edtDate.Text:=formatdatetime('yyyymmdd',(Date()+365));
    edtDate.SetFocus;
  end;
end;

procedure TfaqhAnonyCard.edtmoneyKeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtmoney.Text)=False then
    Key := #0;
end;

procedure TfaqhAnonyCard.edtTicketNoKeyPress(Sender: TObject;
  var Key: Char);
begin
  //inherited;
  if inputNum(Key)=False then
    Key := #0;

end;

procedure TfaqhAnonyCard.getFeeResult;
var
  feeType: Integer;
  sReturnInfo:string;
  fMoney:real;
  
begin
  edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
    edtTicketNo.Enabled := False
  else
    edtTicketNo.Enabled := True;

  try
    //cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    feeType := 0;//StrToInt(Copy(cbbFeeType.Text,1,Pos('-',cbbFeeType.Text)-1));
  except
    Exit;
  end;
  WVFeeQuery.FieldByName('�շ����').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('������').Data.SetInteger(0);
  WVFeeQuery.FieldByName('�ͻ���').Data.SetInteger(0);
  WVFeeQuery.FieldByName('���ܺ�').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('�Ƿ񲻼�����').Data.setstring('1');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('������').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('�շ���Ϣ').Data.AsString;
    edtDate.Text := WVFeeQuery.Fieldbyname('����Ч��').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('�ܷ���').Data.AsFloat;
    if chkSaveMoney.Checked=False then
      edtMoney.Text := floattostr(fMoney);
    RzStatusPane1.Caption := sReturnInfo;
  end;
end;

procedure TfaqhAnonyCard.cbbCardTypeChange(Sender: TObject);
begin
  inherited;
  getFeeResult;
end;

procedure TfaqhAnonyCard.cbbFeeTypeChange(Sender: TObject);
begin
  inherited;
  getFeeResult;
end;

procedure TfaqhAnonyCard.btnReleaseCardClick(Sender: TObject);
var
  showCardNo:string;
  pCardID:string;
  feeType:string;
  cardManage: TCardManage;
  operCode:string;
  saveType:string;
begin
  saveType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  if saveType='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���ֵ����,Ȼ���ٽ��з�����');
    cbbType.SetFocus;
    Exit;
  end;
  if Trim(edtDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�����뿨��Ч�ڣ�');
    Exit;
  end;
  if CheckInputDateFormat(edtDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('����Ч�����벻��ȷ����ʽ��yyyymmdd');
    edtDate.SetFocus;
    Exit;
  end;
  if releaseCardJudge=False then
    Exit;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //ȡ������
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ������°ѿ����õ���д���ϣ�');
      exit;
    end;

    //ȡ����ʾ����
    showCardNo:=readShowCarNo;
    //��������
    //cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    //�շѷ�ʽ
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    //����Ա
    operCode := Context.ParamData(svOperatorNoName).AsString;
    WVReleaseCard.FieldByName('����Ա').Data.SetString(operCode);
    WVReleaseCard.FieldByName('��ʾ����').Data.SetString(showCardNo);        //
    WVReleaseCard.FieldByName('������').Data.SetString(pCardID);           //
    WVReleaseCard.FieldByName('�շѷ�ʽ').Data.SetInteger(StrToInt(feeType));
    WVReleaseCard.FieldByName('Ʊ�ݺ���').Data.SetString(edtTicketNo.Text);
    WVReleaseCard.FieldByName('��������').Data.SetString(edtDate.Text);
    WVReleaseCard.FieldByName('������').Data.SetInteger(0);
    WVReleaseCard.FieldByName('�ͻ���').Data.SetInteger(0);
    WVReleaseCard.FieldByName('�շѽ��').Data.SetFloat(StrToFloat(edtMoney.Text));
    WVReleaseCard.FieldByName('�Ƿ񲻼�����').Data.SetString('1');
    WVRReleaseCard.SendCommand;
    if (WVReleaseCard.FieldByName('������').Data.AsInteger = 0) then
    begin
      RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,1);
    end
    else
    begin
      getReturn('',WVReleaseCard);
      RzStatusPane1.Caption:=WVReleaseCard.FieldByName('������Ϣ').Data.AsString;
    end;
    //getFeeResult;
  finally
    CardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('����������', TfaqhAnonyCard);
end.
