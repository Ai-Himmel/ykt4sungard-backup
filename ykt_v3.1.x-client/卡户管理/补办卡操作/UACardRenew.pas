unit UACardRenew;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, UtCardDll;

type
  TfaqhCardRenew = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    btnRenewCard: TBitBtn;
    grpReleaseCard: TGroupBox;
    WVLabel11: TWVLabel;
    cbbType: TWVComboBox;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    Label4: TLabel;
    edtMoney: TWVEdit;
    Label8: TLabel;
    WVRRenewCard: TWVRequest;
    WVRenewCard: TWorkView;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    WVFeeQuery: TWorkView;
    WVRFeeQuery: TWVRequest;
    WVEdit4: TWVEdit;
    chkSaveMoney: TCheckBox;
    Label10: TLabel;
    edtTicketNo: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnRenewCardClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure cbbTypeChange(Sender: TObject);
  private
    { Private declarations }
    selectSign : Boolean;
    fMoney:Real;
    procedure getFeeResult;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardRenew: TfaqhCardRenew;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardRenew.Init;
begin
  inherited;
  cbbType.ItemIndex := 0;
  edtTicketNo.Enabled := False;
end;

procedure TfaqhCardRenew.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardRenew.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  WorkView.FieldByName('钱包号').Data.SetInteger(1);
  WorkView.FieldByName('补办标志').Data.SetString('1');
  inherited;
  selectSign := False;
end;

procedure TfaqhCardRenew.btnRenewCardClick(Sender: TObject);
var
  showCardNo:string;
  pCardID:string;
  custId:Integer;
  cardIf:Integer;
  cardId:Integer;
  feeType:string;
  cardManage: TCardManage;
  tipInfo:string;
  custName:string;
  fillMoney:Real;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
     Context.GetDialogSystem.ShowMessage('没有数据，请先查询，然后再进行操作！');
    Exit;
  end;
  if selectSign=False then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择一条记录，然后再进行操作！');
    Exit;
  end;
  try
    custName := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
    //取客户号
    custId := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
    //取卡号
    cardId := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
    tipInfo := '你是否确定要补办姓名为【'+custname+'】的卡？';
  except
    Context.GetDialogSystem.ShowMessage('请选择要补办卡的人员！');
    Exit;
  end;
  if Application.MessageBox(PChar(tipInfo),PChar(Application.title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
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
    if showcardno='-1' then
      Exit;

    //收费方式
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    {
    if chkIf.Checked then
      cardIf := 1
    else
      cardIf := 0;
    }

    cardIf := 0;
    WVRenewCard.FieldByName('操作员').Data.SetString(Context.ParamData(svOperatorNoName).AsString);
    WVRenewCard.FieldByName('显示卡号').Data.SetString(showCardNo);        //
    WVRenewCard.FieldByName('物理卡号').Data.SetString(pCardID);           //
    WVRenewCard.FieldByName('收费方式').Data.SetString(feeType);
    WVRenewCard.FieldByName('票据号码').Data.SetString(Trim(edtTicketNo.Text));
    WVRenewCard.FieldByName('客户号').Data.SetInteger(custId);
    WVRenewCard.FieldByName('卡号').Data.SetInteger(cardId);
    try
      WVRenewCard.FieldByName('收费金额').Data.SetFloat(StrToFloat(edtMoney.Text));
    except
      Context.GetDialogSystem.ShowMessage('应收金额不能为空,请输入！');
      edtMoney.SetFocus;
      Exit;
    end;
    WVRenewCard.FieldByName('收卡成本费').Data.SetInteger(cardIf);
    WVRRenewCard.SendCommand;
    if (WVRenewCard.FieldByName('返回码').Data.AsInteger = 0) then
    begin
      fillMoney := WVRenewCard.FieldByName('出卡值').data.asfloat;
      RzStatusPane1.Caption:=pubCardNew(WVRenewCard,WVRelCardOk,WVRRelCardOk,pCardID,1);
    end
    else
    begin
      getReturn('',WVRenewCard);
      RzStatusPane1.Caption:=WVRenewCard.FieldByName('返回信息').Data.AsString;
    end;
    if bjopen=1 then
    begin
      {
      bj(bjcomport,'&Sc$');
      //bj(bjcomport,'W');
      bj(bjcomport,'&C11姓名：'+trim(custName)+'$');
      bj(bjcomport,'&C21应收:'+floattostr(fMoney)+'$');
      //bj(bjcomport,'&C31实收:'+edtmoney.Text+'$');
      bj(bjcomport,'&C41卡余额:'+floattostr(fillMoney)+'$');
      }
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11姓  名:'+trim(custName)+'$');
    bj(bjcomport,'&C21应  收:'+floattostr(fMoney)+'?$');
    bj(bjcomport, 'B');    //发声，预收
    bj(bjcomport, floattostr(fMoney)+'P');//发声，多少钱
    bj(bjcomport,'&C31卡余额:'+floattostr(fillMoney)+'?$');
    bj(bjcomport, 't'); //发声，账户余额
    bj(bjcomport, floattostr(fillMoney)+'P');   //发声，多少钱
    bj(bjcomport,'&C41谢谢'+'X');
    end;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhCardRenew.getFeeResult();
var
  feeType, cardType,custNo: Integer;
  sReturnInfo:string;
  custName:string;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  feeType := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol5').AsInteger;
  cardType := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lsafe_level').AsInteger;
  custNo :=(WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
  custName := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
  WVFeeQuery.FieldByName('收费类别').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('卡类型').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('功能号').Data.SetInteger(846305);
  WVFeeQuery.FieldByName('客户号').Data.SetInteger(custNo);
  WVFeeQuery.FieldByName('是否不记名卡').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  if WVFeeQuery.FieldByName('返回码').Data.AsInteger=0 then
  begin
    sReturnInfo := WVFeeQuery.fieldbyname('收费信息').Data.AsString;
    fMoney := WVFeeQuery.fieldbyname('总费用').Data.AsFloat;
    if bjopen=1 then
    begin
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'W');
      bj(bjcomport,'&C11姓名：'+trim(custName)+'$');
      bj(bjcomport,floattostr(fMoney)+'J');
    end;
    if chkSaveMoney.Checked=False then
      edtMoney.Text := floattostr(fMoney);
    //edtEndDate.Text := sEndDate;
    RzStatusPane1.Caption := sReturnInfo;
    selectSign := True;
  end;
end;

procedure TfaqhCardRenew.GridCellClick(Column: TColumn);
begin
  inherited;
  getFeeResult;
end;

procedure TfaqhCardRenew.cbbTypeChange(Sender: TObject);
var
  accMoney:Real;
  feeType : string;
begin
  feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
  if feeType='1' then
  begin
    edtTicketNo.Text := '';
    edtTicketNo.Enabled := False;
    edtMoney.Enabled := True;
  end
  else if (feeType='2') or (feeType='3') then
  begin
    edtTicketNo.Enabled := True;
    edtMoney.Enabled := True;
  end
  else if feeType='9' then
  begin
    try
      accMoney := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('damt0').asfloat;
    except
      Context.GetDialogSystem.ShowMessage('请先查询出记录，然后选择要补办的卡再选择收费方式！');
      cbbType.ItemIndex := 0;
      Exit;
    end;
    if accMoney<fMoney then
    begin
       Context.GetDialogSystem.ShowMessage('帐户余额不足，请使用现金补办卡！');
       cbbType.ItemIndex := 0;
    end
    else
    begin
      edtMoney.Enabled := False;
      edtMoney.Text := FloatToStr(fMoney);
      edtTicketNo.Text := '';
      edtTicketNo.Enabled := False;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('补办卡操作', TfaqhCardRenew);

end.


