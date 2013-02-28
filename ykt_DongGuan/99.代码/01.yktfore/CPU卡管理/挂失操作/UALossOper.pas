unit UALossOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,RM_Class,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll;

type
  TfaqhLossOper = class(TfaqhSimpleQueryTemp)
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
  faqhLossOper: TfaqhLossOper;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhLossOper.Init;
begin
  inherited;
  {
  WorkView.FieldByName('操作标志').DefaultValue := '';
  WorkView.FieldByName('发卡部门').DefaultValue := '';
  WorkView.FieldByName('姓名').DefaultValue := '';
  WorkView.FieldByName('证件类型').DefaultValue := '';
  WorkView.FieldByName('证件号码').DefaultValue := '';
  WorkView.FieldByName('手机').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhLossOper.btnQueryClick(Sender: TObject);
begin
  inherited;
  btnLoss.Enabled := True;
end;

procedure TfaqhLossOper.btnLossClick(Sender: TObject);
var
  custId:Integer;
  cardNo:string;
  
  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  fMoney:string;
  rCardNo:string;
begin
  try
    custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
    cardNo := Grid.DataSource.DataSet.fieldbyname('sphone3').AsString;
    fMoney := Grid.DataSource.DataSet.fieldbyname('damt2').AsString;
  except
    Exit;
  end;
  WorkView1.FieldByName('操作标志').Data.SetString('L');
  WorkView1.FieldByName('卡号').Data.SetString(cardNo);
  WorkView1.FieldByName('客户号').Data.SetInteger(custId);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsString<>'0' then
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('返回信息').Data.AsString)
  else
  begin
    Context.GetDialogSystem.ShowMessage('挂失操作成功！');
    rptReport := nil;
    if chkPrint.Checked then
    begin
      try
        try
          serialNo := WorkView1.fieldbyname('流水号').Data.AsString;
          cardType := WorkView1.fieldbyname('卡类别').Data.AsString;
          phoneNo := WorkView1.fieldbyname('手机').Data.AsString;
          custName := WorkView1.fieldbyname('姓名').Data.AsString;
          rCardNo  := WorkView1.fieldbyname('卡号').Data.AsString;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
          rptReport.Dictionary.Variables.AsString['custName'] := custName;
          rptReport.Dictionary.Variables.AsString['titleType'] := '挂失业务';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
          rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '卡内余额：';
          rptReport.Dictionary.Variables.AsString['pValue1'] := fMoney+' 元';
          rptReport.Dictionary.Variables.AsString['param2'] := '挂失时间：';
          rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.Dictionary.Variables.AsString['param3'] := '';
          rptReport.Dictionary.Variables.AsString['pValue3'] := '';
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\lossoper.rmp');
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

procedure TfaqhLossOper.btnReadCardClick(Sender: TObject);
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

procedure TfaqhLossOper.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\lossoper.rmp');
end;

initialization
  TUIStdClassFactory.Create('挂失操作',TfaqhLossOper);

end.