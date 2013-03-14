unit UAReverseOpenCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus, RzPanel;

type
  TfaqhReverseOpenCard = class(TfaqhSimpleQueryTemp)
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
    edtBDate: TWVEdit;
    edtEDate: TWVEdit;
    edtSeriNo: TWVEdit;
    WVEdit6: TWVEdit;
    edtCustNo: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    edtCardNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    btnReverse: TBitBtn;
    btnReadCard: TBitBtn;
    WVRReserveOpenCard: TWVRequest;
    WVReserveOpenCard: TWorkView;
    Label13: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    lbl1: TLabel;
    edtPwd: TWVEdit;
    cbbErrOperNo: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReverseClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhReverseOpenCard: TfaqhReverseOpenCard;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhReverseOpenCard.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
end;

procedure TfaqhReverseOpenCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhReverseOpenCard.btnQueryClick(Sender: TObject);
begin
  if Trim(edtSeriNo.Text)='' then
    edtSeriNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('查询类型').Data.SetString('1');
  btnReverse.Enabled := False;
  inherited;
  btnReverse.Enabled := True;
end;

procedure TfaqhReverseOpenCard.btnReverseClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  operDate:string;
  seriId:Integer;
  stationId:Integer;
  cm : TCM;
  ResInt2:Integer;
  phyId:string;
  PCardID:string;
  tradeNum:Integer;
  operCode:string;
  operPwd:string;
  st:integer;
begin
  if Application.MessageBox('如果要冲正该记录，请把卡放置到读写器上，确定要冲正吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tmpDataSet := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(PCardID);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(DPT_CARD_CNT);    //使用充值交易次数
    //cm.setfieldreadmode(CARD_SERI_NO);
    if cm.readCard(PCardID)<>0 then
    begin
      //Context.GetDialogSystem.ShowMessage('读卡交易次数失败，请重试！');
      //Exit;
      tradeNum := 0;
    end
    else
    begin
      //读取交易次数
      if cm.getDptCardCnt='' then
      begin
        tradeNum := 0;
      end
      else
      begin
        tradeNum := StrToInt(cm.getDptCardCnt);
      end;
    end;
    operDate := tmpDataSet.fieldbyname('sdate3').AsString;
    seriId := tmpDataSet.fieldbyname('lserial1').AsInteger;
    stationId := tmpDataSet.fieldbyname('lwithdraw_flag').AsInteger;
    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    //WorkView.FieldByName('新密码').Data.SetString(operPwd);
    WVReserveOpenCard.FieldByName('业务日期').Data.SetString(operDate);
    WVReserveOpenCard.FieldByName('流水号').Data.SetInteger(seriId);
    WVReserveOpenCard.FieldByName('终端编号').Data.SetInteger(stationId);
    WVReserveOpenCard.FieldByName('交易次数').Data.SetInteger(tradeNum);
    //WVReserveOpenCard.FieldByName('验证操作员').Data.SetString(Trim(edtOper.text));
    WVReserveOpenCard.FieldByName('操作员密码').Data.SetString(operPwd);
    WVReserveOpenCard.FieldByName('是否授权').Data.SetString('1');
    WVRReserveOpenCard.SendCommand;
    phyId := WVReserveOpenCard.FieldByName('物理卡号').Data.AsString;
    {
    //取物理卡号
    PCardID := cm.getCardSeriNo;
    if PCardID='' then
    begin
      Context.GetDialogSystem.ShowMessage('读物理卡号失败，请重新冲正该交易！');
      exit;
    end;
    }
    if PCardID<>phyId then
    begin
      Context.GetDialogSystem.ShowMessage('要冲正的卡和放置的卡不是同一张卡，请重新操作！');
      Exit;
    end;
    try
      ResInt2 := cm.clearCard(WVReserveOpenCard);
      if ResInt2=0 then
      begin
        cm.beep;
        Context.GetDialogSystem.ShowMessage('该卡已经冲正成功！');
        RzStatusPane1.Caption := WVReserveOpenCard.fieldbyname('返回信息').Data.AsString;
        btnQuery.Click;
      end
      else
        Context.GetDialogSystem.ShowMessage('冲正时写卡信息失败，请单独写该卡标记信息-'+inttostr(ResInt2));
    except
      Context.GetDialogSystem.ShowMessage('冲正时写卡信息失败，请单独写该卡标记信息！');
    end;
  finally
    cm.Destroy;
  end;
  edtPwd.Text := '';
end;

procedure TfaqhReverseOpenCard.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtCardNo.Text:='0';
  cardNo := readCardOneInfo(CARD_NO);
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，卡号为零或不存在!');
    Exit;
  end;
  edtCardNo.Text:=cardNo;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('开户冲正',TfaqhReverseOpenCard);

end.