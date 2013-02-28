unit UAChangeCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,RM_Class,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll;

type
  TfaqhChangeCard = class(TfaqhSimpleQueryTemp)
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
    WVChangeCard: TWorkView;
    WVRChangeCard: TWVRequest;
    btnReadCard: TBitBtn;
    Label7: TLabel;
    edtReason: TWVEdit;
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
  faqhChangeCard: TfaqhChangeCard;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhChangeCard.Init;
begin
  inherited;
end;

procedure TfaqhChangeCard.btnQueryClick(Sender: TObject);
begin
  inherited;
  btnLoss.Enabled := True;
end;

procedure TfaqhChangeCard.btnLossClick(Sender: TObject);
var
  cardNo:Integer;
  appCardNo:string;
  sDate,sTime:string;

  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  fMoney:string;
  rCardNo:string;
  rticketNo:string;
begin
  if psamTermId='' then
  begin
    Context.GetDialogSystem.ShowMessage('������PSAM����,Ȼ���ٽ��в�����');
    Exit;
  end;
  
  if Application.MessageBox('��ȷ��Ҫ���뻻����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  try
    cardNo := Grid.DataSource.DataSet.fieldbyname('scard0').AsInteger;
    appCardNo := Grid.DataSource.DataSet.fieldbyname('sphone3').AsString;
    fMoney := Grid.DataSource.DataSet.fieldbyname('damt2').AsString;
  except
    Exit;
  end;
  sdate := FormatDateTime('yyyymmdd',Date);
  stime := FormatDateTime('hhmmss',now);
  WVChangeCard.FieldByName('��������').Data.SetString(sdate);
  WVChangeCard.FieldByName('����ʱ��').Data.SetString(stime);
  WVChangeCard.FieldByName('sam�ն˺�').Data.SetString(psamTermId);
  WVChangeCard.FieldByName('����').Data.SetInteger(cardNo);
  WVChangeCard.FieldByName('Ӧ�����к�').Data.SetString(appCardNo);
  WVChangeCard.FieldByName('����ԭ��').Data.SetString(edtReason.Text);
  WVRChangeCard.SendCommand;
  if WVChangeCard.FieldByName('������').Data.AsString<>'0' then
    Context.GetDialogSystem.ShowMessage(WVChangeCard.FieldByName('������Ϣ').Data.AsString)
  else
  begin
    Context.GetDialogSystem.ShowMessage('��������ɹ���');
    rptReport := nil;
    if chkPrint.Checked then
    begin
      try
        try
          serialNo := WVChangeCard.fieldbyname('��ˮ��').Data.AsString;
          cardType := WVChangeCard.fieldbyname('������').Data.AsString;
          phoneNo := WVChangeCard.fieldbyname('�ֻ�').Data.AsString;
          custName := WVChangeCard.fieldbyname('����').Data.AsString;
          rCardNo  := WVChangeCard.fieldbyname('����').Data.AsString;
          rticketNo := WVChangeCard.fieldbyname('���뵥��').Data.AsString;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
          rptReport.Dictionary.Variables.AsString['custName'] := custName;
          rptReport.Dictionary.Variables.AsString['titleType'] := '��������';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
          rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '������';
          rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f',[strtofloat(fMoney)])+' Ԫ';
          rptReport.Dictionary.Variables.AsString['param2'] := '����ʱ�䣺';
          rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.Dictionary.Variables.AsString['param3'] := '���뵥�ţ�';
          rptReport.Dictionary.Variables.AsString['pValue3'] := rticketNo;
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\changecard.rmp');
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
  end;
  btnQuery.Click;
end;

procedure TfaqhChangeCard.btnReadCardClick(Sender: TObject);
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

procedure TfaqhChangeCard.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\changecard.rmp');
end;

initialization
  TUIStdClassFactory.Create('��������',TfaqhChangeCard);

end.