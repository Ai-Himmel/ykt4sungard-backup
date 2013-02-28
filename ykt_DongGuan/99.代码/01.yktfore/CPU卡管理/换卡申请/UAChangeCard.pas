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
    Context.GetDialogSystem.ShowMessage('请设置PSAM卡座,然后再进行操作！');
    Exit;
  end;
  
  if Application.MessageBox('你确定要申请换卡吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
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
  WVChangeCard.FieldByName('交易日期').Data.SetString(sdate);
  WVChangeCard.FieldByName('交易时间').Data.SetString(stime);
  WVChangeCard.FieldByName('sam终端号').Data.SetString(psamTermId);
  WVChangeCard.FieldByName('卡号').Data.SetInteger(cardNo);
  WVChangeCard.FieldByName('应用序列号').Data.SetString(appCardNo);
  WVChangeCard.FieldByName('换卡原因').Data.SetString(edtReason.Text);
  WVRChangeCard.SendCommand;
  if WVChangeCard.FieldByName('返回码').Data.AsString<>'0' then
    Context.GetDialogSystem.ShowMessage(WVChangeCard.FieldByName('返回信息').Data.AsString)
  else
  begin
    Context.GetDialogSystem.ShowMessage('换卡申请成功！');
    rptReport := nil;
    if chkPrint.Checked then
    begin
      try
        try
          serialNo := WVChangeCard.fieldbyname('流水号').Data.AsString;
          cardType := WVChangeCard.fieldbyname('卡类型').Data.AsString;
          phoneNo := WVChangeCard.fieldbyname('手机').Data.AsString;
          custName := WVChangeCard.fieldbyname('姓名').Data.AsString;
          rCardNo  := WVChangeCard.fieldbyname('卡号').Data.AsString;
          rticketNo := WVChangeCard.fieldbyname('申请单号').Data.AsString;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
          rptReport.Dictionary.Variables.AsString['custName'] := custName;
          rptReport.Dictionary.Variables.AsString['titleType'] := '换卡申请';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
          rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '卡内余额：';
          rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f',[strtofloat(fMoney)])+' 元';
          rptReport.Dictionary.Variables.AsString['param2'] := '申请时间：';
          rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.Dictionary.Variables.AsString['param3'] := '申请单号：';
          rptReport.Dictionary.Variables.AsString['pValue3'] := rticketNo;
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\changecard.rmp');
          if showrpt=1 then
            rptReport.ShowReport
          else
            rptReport.PrintReport;
        except
          on e:Exception do
          Context.GetDialogSystem.ShowMessage('你没有安装打印机，不能打印--'+e.Message);
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
    Context.GetDialogSystem.ShowMessage('读卡查询失败，应用序列号为零或不存在!');
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
  TUIStdClassFactory.Create('换卡申请',TfaqhChangeCard);

end.