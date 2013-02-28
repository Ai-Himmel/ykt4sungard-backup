unit UAAnonGetCardNew;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus,RM_Class;

type
  TfaqAnonGetCardNew = class(TfaqhSimpleQueryTemp)
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
    edtCustNo: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit11: TWVEdit;
    edtAppNo: TWVEdit;
    cbbDept: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    btnReadCard: TBitBtn;
    btnGetCard: TBitBtn;
    chkPrint: TCheckBox;
    Label13: TLabel;
    edtMoney: TWVEdit;
    rzstspn1: TRzStatusPane;
    procedure btnQueryClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnGetCardClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqAnonGetCardNew: TfaqAnonGetCardNew;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqAnonGetCardNew.Init;
begin
  inherited;
  {
  WorkView.FieldByName('客户号').DefaultValue := 0;
  WorkView.FieldByName('姓名').DefaultValue := '';
  WorkView.FieldByName('证件类型').DefaultValue := '';
  WorkView.FieldByName('证件号码').DefaultValue := '';
  WorkView.FieldByName('发卡部门').DefaultValue := '';
  WorkView.FieldByName('电话').DefaultValue := '';
  WorkView.FieldByName('手机').DefaultValue := '';
  WorkView.FieldByName('卡号').DefaultValue := '';
  WorkView.FieldByName('卡物理编号').DefaultValue := '';
  WorkView.FieldByName('卡类型').DefaultValue := 0;
  WorkView.FieldByName('制卡日期').DefaultValue := '';
  WorkView.FieldByName('发行批次号').DefaultValue := 0;
  WorkView.Reset;
  }
end;

procedure TfaqAnonGetCardNew.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  btnGetCard.Enabled := False;
  //实名卡为1，2为非实名
  WorkView.FieldByName('查询类别').Data.SetString('2');
  //查询类别
  inherited;
  btnGetCard.Enabled := True;
end;

procedure TfaqAnonGetCardNew.GridCellClick(Column: TColumn);
var
  custId:Integer;
  cardNo:string;
  cardType:Integer;
begin
  try
    custId:=Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
    cardType:=Grid.DataSource.DataSet.fieldbyname('lvol1').AsInteger;
    cardNo:=Grid.DataSource.DataSet.fieldbyname('scard0').AsString;
  except
    custId := 0;
    cardType :=0;
  end;
  WorkView2.FieldByName('客户号').Data.SetInteger(custId);
  WorkView2.FieldByName('卡号').Data.SetString(cardNo);
  WorkView2.FieldByName('卡类别').Data.SetInteger(cardType);
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('返回码').Data.AsInteger=0 then
  begin
    rzstspn1.Caption := WorkView2.fieldbyname('缴费信息').Data.AsString;
    edtMoney.Text := WorkView2.fieldbyname('预交金额').Data.AsString;
  end
  else
    rzstspn1.Caption := WorkView2.fieldbyname('返回信息').Data.AsString;
end;

procedure TfaqAnonGetCardNew.btnGetCardClick(Sender: TObject);
var
  custId:Integer;
  cardNo:string;
  cm: TCM;
  st:integer;
  phyId,appSerialNo:string;
  loDate,loTime:string;
  payCnt,DptCnt,cardBal:Integer;
  rptReport:TRMReport;
  //custName:string;
  //phoneNo:string;
  serialNo:string;
  cardType:string;
begin
  if not preReadCard then
    Exit;
  if Application.MessageBox('你确定要进行领卡操作吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请先放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CF_APPSERIALNO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(DPT_CARD_CNT);

    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败-'+geterrmsg);
      Exit;
    end;
    appSerialNo := cm.getAppSerialNo;
    payCnt := StrToInt(cm.getPayCardCnt);
    DptCnt := StrToInt(cm.getDptCardCnt);
    cardBal := StrToInt(cm.getCardBalance);
  finally
    cm.Destroy;
  end;
  loDate := FormatDateTime('yyyymmdd',Date);
  loTime := FormatDateTime('hhmmss',Now);
  custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  cardNo := Grid.DataSource.DataSet.fieldbyname('scard0').AsString;
  WorkView1.FieldByName('操作标志').Data.SetString('N');
  WorkView1.FieldByName('卡号').Data.SetString(cardNo);
  WorkView1.FieldByName('客户号').Data.SetInteger(custId);
  WorkView1.FieldByName('预交款').Data.SetFloat(StrToFloat(edtMoney.text));
  WorkView1.FieldByName('卡序列号').Data.SetString(appSerialNo);
  WorkView1.FieldByName('psam卡号').Data.SetString(psamTermId);
  WorkView1.FieldByName('本机流水号').Data.SetString(loTime);
  WorkView1.FieldByName('本机日期').Data.SetString(loDate);
  WorkView1.FieldByName('本机时间').Data.SetString(loTime);
  WorkView1.FieldByName('卡物理编号').Data.SetString(phyId);
  WorkView1.FieldByName('网点号').Data.SetString(scSiteNo);
  WorkView1.FieldByName('充值次数').Data.SetInteger(DptCnt);
  WorkView1.FieldByName('消费次数').Data.SetInteger(payCnt);
  WorkView1.FieldByName('卡余额').Data.SetInteger(cardBal);
  if WorkView1.FieldByName('返回码').Data.AsInteger<>0 then
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('返回信息').Data.AsString)
  else
  begin
    rptReport := nil;
    if chkPrint.Checked then
    begin
      try
        try
          serialNo := WorkView1.fieldbyname('交易流水').Data.AsString;
          cardType := WorkView1.fieldbyname('卡类型').Data.AsString;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := '';
          rptReport.Dictionary.Variables.AsString['custName'] := '';
          rptReport.Dictionary.Variables.AsString['titleType'] := '非实名卡发卡';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
          rptReport.Dictionary.Variables.AsString['cardNo'] := cardNo;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '卡内余额：';
          rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [cardBal / 100.0])+'元';
          rptReport.Dictionary.Variables.AsString['param2'] := '发卡时间：';
          rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.Dictionary.Variables.AsString['param3'] := '';
          rptReport.Dictionary.Variables.AsString['pValue3'] := '';
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\getcard.rmp');
          if showrpt=1 then
            rptReport.ShowReport
          else
            rptReport.PrintReport;
        except
          Context.GetDialogSystem.ShowMessage('你没有安装打印机，不能打印！');
        end;
      finally
        rptReport.Free;
      end;
    end;
    Context.GetDialogSystem.ShowMessage('领卡成功！');
  end;
end;

procedure TfaqAnonGetCardNew.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppNo.Text:='';
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
  edtAppNo.Text:=cardNo;
end;

procedure TfaqAnonGetCardNew.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\getcard.rmp');

end;

initialization
  TUIStdClassFactory.Create('匿名卡领取',TfaqAnonGetCardNew);

end.