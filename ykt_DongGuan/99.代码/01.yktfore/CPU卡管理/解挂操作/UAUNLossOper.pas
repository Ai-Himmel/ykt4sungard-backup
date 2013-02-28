unit UAUNLossOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus,RM_Class;

type
  TfaqhUnLossOper = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    WVEdit3: TWVEdit;
    WVEdit5: TWVEdit;
    edtAppSerialNo: TWVEdit;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    cbbDept: TWVComboBox;
    cbbIDType: TWVComboBox;
    btnLoss: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    btnReadCard: TBitBtn;
    RzStatusPane1: TRzStatusPane;
    chkPrint: TCheckBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnLossClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhUnLossOper: TfaqhUnLossOper;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhUnLossOper.Init;
begin
  inherited;
end;

procedure TfaqhUnLossOper.btnQueryClick(Sender: TObject);
begin
  inherited;
  btnLoss.Enabled := True;
end;

procedure TfaqhUnLossOper.btnLossClick(Sender: TObject);
var
  custId:Integer;
  cardNo:string;
  cm:TCM;
  st:Integer;
  phyId:string;
  dbAppNo:string;
  tipINfo:string;
  loDate,loTime:string;

  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  fMoney:string;
  rCardNo:string;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ��޷����д˲�����');
    Exit;
  end;
  if preReadCard=False then
    Exit;
  try
    custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
    //cardNo := Grid.DataSource.DataSet.fieldbyname('scard0').AsString;
    dbAppNo := Grid.DataSource.DataSet.fieldbyname('sphone3').AsString;
    fMoney := Grid.DataSource.DataSet.fieldbyname('damt2').AsString;
  except
    Exit;
  end;
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
    cm.setfieldreadmode(CF_APPSERIALNO);
    cm.setfieldreadmode(BLACK_CARD_SIGN);
    st := cm.readCard(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('����ʧ��-'+geterrmsg);
      Exit;
    end;
    cardNo := cm.getAppSerialNo;
    {
    try
      cardSign := StrToInt(cm.getBlackCardSign);
    except
      Context.GetDialogSystem.ShowMessage('��ȡ����־ʧ��-'+geterrmsg);
      Exit;
    end;
    }
    if cardNo = '' then
    begin
      Context.GetDialogSystem.ShowWarning('��ȡӦ�����к�ʧ�ܣ�');
      Exit;
    end;
    if cardNo <> dbAppNo then
    begin
      Context.GetDialogSystem.ShowWarning('���������Ŀ��Ͷ�д���Ϸ��õĲ���ͬһ�ſ���');
      Exit;
    end;
    loDate := FormatDateTime('yyyymmdd',Date);
    loTime := FormatDateTime('hhmmss',Now);
    WorkView1.FieldByName('������־').Data.SetString('U');
    WorkView1.FieldByName('����').Data.SetString(cardNo);
    WorkView1.FieldByName('�ͻ���').Data.SetInteger(custId);
    WorkView1.FieldByName('psam����').Data.SetString(psamTermId);
    WorkView1.FieldByName('������ˮ��').Data.SetString(loTime);
    WorkView1.FieldByName('��������').Data.SetString(loDate);
    WorkView1.FieldByName('����ʱ��').Data.SetString(loTime);
    WVRequest1.SendCommand;
    {
    if WorkView1.FieldByName('������').Data.AsString<>'0' then
      Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString)
    else
      Context.GetDialogSystem.ShowMessage('��Ҳ����ɹ���');
    }
    if WorkView1.FieldByName('������').Data.AsInteger = 0 then
    begin
      tipINfo := WorkView1.fieldbyname('������Ϣ').Data.AsString;
      cm.clearallfieldwritemode;
      cm.setfieldwritemode(BLACK_CARD_SIGN);
      cm.setfieldwritemode(BLACK_VER);
      cm.setBlackCardSign(IntToStr(NORMAL_CARD));
      cm.setBlackVer(WorkView1.FieldByName('���汾��').Data.AsString);
      st := cm.writeData(phyId);
      if st <> 0 then
      begin
        Context.GetDialogSystem.ShowWarning('��ҿ�ʧ�ܣ�������--'+inttostr(st));
      end
      else
      begin
        cm.beep;
        Context.GetDialogSystem.ShowSuccess('��ҿ��ɹ�  '+tipInfo);
        rptReport := nil;
        if chkPrint.Checked then
        begin
          try
            try
              serialNo := WorkView1.fieldbyname('��ˮ��').Data.AsString;
              cardType := WorkView1.fieldbyname('�����').Data.AsString;
              phoneNo := WorkView1.fieldbyname('�ֻ�').Data.AsString;
              custName := WorkView1.fieldbyname('����').Data.AsString;
              rCardNo  := WorkView1.fieldbyname('����').Data.AsString;
              rptReport := TRMReport.Create(Self);
              rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
              rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
              rptReport.Dictionary.Variables.AsString['custName'] := custName;
              rptReport.Dictionary.Variables.AsString['titleType'] := '���ҵ��';
              rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
              rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
              rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
              rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
              rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
              rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
              rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
              rptReport.Dictionary.Variables.AsString['param1'] := '������';
              rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f',[strtofloat(fMoney)])+' Ԫ';
              rptReport.Dictionary.Variables.AsString['param2'] := '���ʱ�䣺';
              rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
              rptReport.Dictionary.Variables.AsString['param3'] := '';
              rptReport.Dictionary.Variables.AsString['pValue3'] := '';
              rptReport.ShowPrintDialog := False;
              rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\unlossoper.rmp');
              if showrpt=1 then
                rptReport.ShowReport
              else
                rptReport.PrintReport;
            except
              on e:Exception do
              Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������ܴ�ӡ--'+e.Message);
            end;
          finally
            rptReport.Free;
          end;
        end;
        RzStatusPane1.Caption := '��ҿ��ɹ�  '+tipINfo
      end;
    end
    else
    begin
      getReturn('��ҿ�ʧ��  ',WorkView1);
      RzStatusPane1.Caption := '��ҿ�ʧ��  '+tipINfo
    end;
  finally
    cm.Destroy;
  end;
  btnQuery.Click;
end;

procedure TfaqhUnLossOper.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppSerialNo.Text:='';
  try
    cardNo := readCardOneInfo(CF_APPSERIALNO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('������ѯʧ�ܣ�Ӧ�����к�Ϊ��򲻴���!');
    Exit;
  end;
  edtAppSerialNo.Text:=cardNo;
  btnQuery.Click();
end;

procedure TfaqhUnLossOper.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\unlossoper.rmp');
end;

initialization
  TUIStdClassFactory.Create('��Ҳ���',TfaqhUnLossOper);

end.