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
    Context.GetDialogSystem.ShowMessage('日期输入有误，请重新输入');
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
  WVFeeQuery.FieldByName('收费类别').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('卡类型').Data.SetInteger(0);
  WVFeeQuery.FieldByName('客户号').Data.SetInteger(0);
  WVFeeQuery.FieldByName('功能号').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('是否不记名卡').Data.setstring('1');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('返回码').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('收费信息').Data.AsString;
    edtDate.Text := WVFeeQuery.Fieldbyname('卡有效期').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('总费用').Data.AsFloat;
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
    Context.GetDialogSystem.ShowMessage('请选择充值类型,然后再进行发卡！');
    cbbType.SetFocus;
    Exit;
  end;
  if Trim(edtDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入卡有效期！');
    Exit;
  end;
  if CheckInputDateFormat(edtDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('卡有效期输入不正确，格式：yyyymmdd');
    edtDate.SetFocus;
    Exit;
  end;
  if releaseCardJudge=False then
    Exit;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //取物理卡号
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡序列号失败，请重新把卡放置到读写器上！');
      exit;
    end;

    //取得显示卡号
    showCardNo:=readShowCarNo;
    //发卡类型
    //cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    //收费方式
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    //操作员
    operCode := Context.ParamData(svOperatorNoName).AsString;
    WVReleaseCard.FieldByName('操作员').Data.SetString(operCode);
    WVReleaseCard.FieldByName('显示卡号').Data.SetString(showCardNo);        //
    WVReleaseCard.FieldByName('物理卡号').Data.SetString(pCardID);           //
    WVReleaseCard.FieldByName('收费方式').Data.SetInteger(StrToInt(feeType));
    WVReleaseCard.FieldByName('票据号码').Data.SetString(edtTicketNo.Text);
    WVReleaseCard.FieldByName('到期日期').Data.SetString(edtDate.Text);
    WVReleaseCard.FieldByName('卡类型').Data.SetInteger(0);
    WVReleaseCard.FieldByName('客户号').Data.SetInteger(0);
    WVReleaseCard.FieldByName('收费金额').Data.SetFloat(StrToFloat(edtMoney.Text));
    WVReleaseCard.FieldByName('是否不记名卡').Data.SetString('1');
    WVRReleaseCard.SendCommand;
    if (WVReleaseCard.FieldByName('返回码').Data.AsInteger = 0) then
    begin
      RzStatusPane1.Caption:=pubCardNew(WVReleaseCard,WVRelCardOk,WVRRelCardOk,pCardID,1);
    end
    else
    begin
      getReturn('',WVReleaseCard);
      RzStatusPane1.Caption:=WVReleaseCard.FieldByName('返回信息').Data.AsString;
    end;
    //getFeeResult;
  finally
    CardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('匿名卡发行', TfaqhAnonyCard);
end.
