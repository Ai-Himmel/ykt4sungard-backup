unit UAReleaseCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  RzSplit, Menus, UIncrementComboBox, UtCardDll,
  EditExts;

type
  TfaqhReleaseCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label5: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit5: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    Label6: TLabel;
    WVEdit6: TWVEdit;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    btnReleaseCard: TBitBtn;
    grpReleaseCard: TGroupBox;
    WVLabel11: TWVLabel;
    cbbType: TWVComboBox;
    Label10: TLabel;
    edtTicketNo: TWVEdit;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVLabel9: TWVLabel;
    WVComboBox7: TWVComboBox;
    WVFeeQuery: TWorkView;
    WVRFeeQuery: TWVRequest;
    Label4: TLabel;
    Label8: TLabel;
    WVRReleaseCard: TWVRequest;
    WVReleaseCard: TWorkView;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    lblMoney: TLabel;
    edtEndDate: TWVEdit;
    Label9: TLabel;
    WVEdit4: TWVEdit;
    WVLabel7: TWVLabel;
    cbbCardType: TWVComboBox;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure cbbCardTypeChange(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
    procedure btnReleaseCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
  private
    { Private declarations }
    selectSign:Boolean;
    sReturnInfo:string;
    fMoney:Real;
    //procedure initCustInsColInfo;
    //procedure getCustInfoValue;

    procedure getFeeResult();
    function judgeValue: Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhReleaseCard: TfaqhReleaseCard;
  IsBackCard: integer;

implementation

uses KsFrameworks,KSDataDictionary, 
  KSClientConsts, SmartCardCommon,DataTypes;

{$R *.DFM}

procedure TfaqhReleaseCard.Init;
begin
  inherited;
  //initCustInsColInfo;
  cbbCardType.ItemIndex := 0;
  cbbType.ItemIndex := 0;
  edtTicketNo.Enabled := False;
end;

procedure TfaqhReleaseCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhReleaseCard.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
  cardType:Integer;
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  if judgeValue=False then
    if Application.MessageBox('����������ѯ�ٶȿ��ܻ��������ȷ��Ҫ����������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;
  cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  WorkView.FieldByName('�������').Data.SetInteger(cardType);
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  tmpData.Last;
  tmpData.First;
  selectSign := False;
  //Sleep(100);
  //getFeeResult;
end;

procedure TfaqhReleaseCard.getFeeResult();
var
  feeType, cardType,custId: Integer;
  sEndDate,custName:string;
  tmpData:TDataSet;
begin
  //if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    //Exit;
  try
    tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
    //tmpData.First;
    feeType := tmpData.FieldByName('lvol5').AsInteger;
    custId := tmpData.FieldByName('lvol1').AsInteger;
    custName := tmpData.fieldbyname('sall_name').AsString;
    //sEndDate := tmpData.FieldByName('sdate3').AsString;
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('���Ȳ�ѯ�����ݣ�������Ϣ��'+ex.Message);
      Exit;
    end;
  end;
  WVFeeQuery.FieldByName('�շ����').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('������').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('���ܺ�').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('�ͻ���').Data.SetInteger(custId);
  WVFeeQuery.FieldByName('�Ƿ񲻼�����').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  //ShowMessage('11');
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
    edtEndDate.Text := WVFeeQuery.fieldbyname('����Ч��').Data.AsString;
    RzStatusPane1.Caption := sReturnInfo;
    selectSign := True;
  end
  else
  begin
    RzStatusPane1.Caption := WVFeeQuery.fieldbyname('������Ϣ').Data.AsString;
  end;
end;

procedure TfaqhReleaseCard.cbbCardTypeChange(Sender: TObject);
begin
  inherited;
  //getFeeResult;
end;

procedure TfaqhReleaseCard.cbbTypeChange(Sender: TObject);
begin
  if cbbType.ItemIndex=0 then
  begin
    edtTicketNo.Text := '';
    edtTicketNo.Enabled := False;
  end
  else
  begin
    edtTicketNo.Enabled := True;
  end;
end;

procedure TfaqhReleaseCard.btnReleaseCardClick(Sender: TObject);
var
  showCardNo:string;
  pCardID:string;
  custId:Integer;
  cardType:Integer;
  feeType:string;
  cardManage: TCardManage;
  tipInfo:string;
  custName:string;
  cardTypeName:string;
  fillMoney:Real;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ����Ȳ�ѯ��Ȼ���ٽ��в�����');
    Exit;
  end;
  if selectSign=False then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��һ����¼��Ȼ���ٷ�����');
    exit;
  end;
  if Trim(edtEndDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�����뿨��Ч�ڣ�');
    edtEndDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtEndDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('����Ч���������󣬸�ʽyyyymmdd��');
    edtEndDate.SetFocus;
    Exit;
  end;
  try
    custName := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
    //ȡ�ͻ���
    custId := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
  except
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫ���еļ�¼��Ȼ���ٽ��в�����');
    Exit;
  end;
  cardTypeName := Copy(cbbCardType.Text,Pos('-',cbbCardType.Text)+1,Length(cbbCardType.Text));
  tipInfo := '���Ƿ�ȷ��Ҫ��������Ϊ��'+custname+'��,�������'+cardtypename+'���Ŀ���';
  if Application.MessageBox(PChar(tipInfo),PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
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
    if showCardNo='-1' then
      Exit;
    //��������
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    //�շѷ�ʽ
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    WVReleaseCard.FieldByName('����Ա').Data.SetString(Context.ParamData(svOperatorNoName).AsString);
    WVReleaseCard.FieldByName('��ʾ����').Data.SetString(showCardNo);        //
    WVReleaseCard.FieldByName('������').Data.SetString(pCardID);           //
    WVReleaseCard.FieldByName('�շѷ�ʽ').Data.SetInteger(StrToInt(feeType));
    WVReleaseCard.FieldByName('Ʊ�ݺ���').Data.SetString(edtTicketNo.Text);
    WVReleaseCard.FieldByName('��������').Data.SetString(edtEndDate.Text);
    WVReleaseCard.FieldByName('������').Data.SetInteger(cardType);
    WVReleaseCard.FieldByName('�ͻ���').Data.SetInteger(custId);
    try
      WVReleaseCard.FieldByName('�շѽ��').Data.SetFloat(StrToFloat(edtMoney.Text));
    except
      Context.GetDialogSystem.ShowMessage('���ֵ����Ϊ�գ������룡');
      edtmoney.SetFocus;
      Exit;
    end;
    WVReleaseCard.FieldByName('�Ƿ񲻼�����').Data.SetString('0');
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
    if bjopen=1 then
    begin
      bj(bjcomport,'&Sc$');
      //bj(bjcomport,'W');
      bj(bjcomport,'&C11������'+trim(custName)+'$');
      bj(bjcomport,'&C21Ӧ��:'+floattostr(fMoney)+'$');
      bj(bjcomport,'&C31ʵ��:'+edtmoney.Text+'$');
      try
        fillMoney := StrToFloat(edtmoney.Text)-fmoney;
        bj(bjcomport,'&C41��ֵ:'+floattostr(fillMoney)+'$');
      except
      end;
    end;
    btnQuery.Click;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhReleaseCard.GridCellClick(Column: TColumn);
begin
  getFeeResult;

end;

{-------------------------------------------------------------------------------
  ������:    TfaqhReleaseCard.judgeValue�ж��Ƿ����е�ֵΪ�գ����Ϊ���򷵻�false
  ����:      hanjiwei
  ����:      2008.09.24
  ����:      ��
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function TfaqhReleaseCard.judgeValue: Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to WorkView.FieldCount-1 do
  begin
    if (WorkView.Fields[i].DataType= kdtInteger) or (WorkView.Fields[i].DataType= kdtFloat)  then
    begin
      if WorkView.Fields[i].Data.Value>0 then
        Result := True;
    end;
    if WorkView.Fields[i].DataType= kdtstring then
      if WorkView.Fields[i].Data.Value<>'' then
        Result := True;
  end;

end;

initialization
  TUIStdClassFactory.Create('���п�����', TfaqhReleaseCard);

end.


