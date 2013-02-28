unit UADestoryOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus,RM_Class;

type
  TfaqhDestoryOper = class(TfaqhSimpleQueryTemp)
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
    edtCardNo: TWVEdit;
    cbbDept: TWVComboBox;
    cbbIDType: TWVComboBox;
    btnLoss: TBitBtn;
    WVDestoryOper: TWorkView;
    WVRDestoryOper: TWVRequest;
    btnReadCard: TBitBtn;
    RzStatusPane2: TRzStatusPane;
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
  faqhDestoryOper: TfaqhDestoryOper;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhDestoryOper.Init;
begin
  inherited;
end;

procedure TfaqhDestoryOper.btnQueryClick(Sender: TObject);
begin
  inherited;
  btnLoss.Enabled := True;
end;

procedure TfaqhDestoryOper.btnLossClick(Sender: TObject);
var
  sDate,sTime:string;
  appSerialNo:string;
  cardNo:Integer;
  rtnInfo:string;

  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  fMoney:string;
  rCardNo:string;
begin
  if psamTermId='' then
  begin
    Context.GetDialogSystem.ShowMessage('������PSAM����,Ȼ���ٽ��в�����');
    Exit;
  end;
  
  if Application.MessageBox('��ȷ��Ҫ������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  try
    cardNo := Grid.DataSource.DataSet.fieldbyname('scard0').AsInteger;
    appSerialNo := Grid.DataSource.DataSet.fieldbyname('sphone3').AsString;
  except
    Exit;
  end;
  sDate := FormatDateTime('yyyymmdd',Date);
  sTime := FormatDateTime('hhmmss',Now);
  WVDestoryOper.FieldByName('��������').Data.SetString(sDate);
  WVDestoryOper.FieldByName('����ʱ��').Data.SetString(sTime);
  WVDestoryOper.FieldByName('sam�ն˺�').Data.SetString(psamTermId);
  WVDestoryOper.FieldByName('Ӧ�����к�').Data.SetString(appSerialNo);
  WVDestoryOper.FieldByName('����').Data.SetInteger(cardNo);
  try
    WVRDestoryOper.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Exit;
    end;
  end;
  rtnInfo :=WVDestoryOper.FieldByName('������Ϣ').Data.AsString;

  Context.GetDialogSystem.ShowMessage(rtnInfo);
  rptReport := nil;
  if chkPrint.Checked then
  begin
    try
      try
        serialNo := WVDestoryOper.fieldbyname('��ˮ��').Data.AsString;
        cardType := WVDestoryOper.fieldbyname('������').Data.AsString;
        phoneNo := WVDestoryOper.fieldbyname('�ֻ�').Data.AsString;
        custName := WVDestoryOper.fieldbyname('����').Data.AsString;
        rCardNo  := WVDestoryOper.fieldbyname('����').Data.AsString;
        fMoney := WVDestoryOper.fieldbyname('�˿����').Data.AsString;
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
        rptReport.Dictionary.Variables.AsString['pValue1'] := fMoney+' Ԫ';
        rptReport.Dictionary.Variables.AsString['param2'] := '����ʱ�䣺';
        rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
        rptReport.Dictionary.Variables.AsString['param3'] := '';
        rptReport.Dictionary.Variables.AsString['pValue3'] := '';
        rptReport.ShowPrintDialog := False;
        rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\destoryoper.rmp');
        if showrpt=1 then
          rptReport.ShowReport
        else
          rptReport.PrintReport;
      except
        Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������ܴ�ӡ��');
      end;
    finally
      rptReport.Free;
    end;
  end;

  RzStatusPane2.Caption:= rtnInfo;
  btnQuery.Click;
end;

procedure TfaqhDestoryOper.btnReadCardClick(Sender: TObject);
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

procedure TfaqhDestoryOper.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\destoryoper.rmp');
end;

initialization
  TUIStdClassFactory.Create('��������',TfaqhDestoryOper);

end.