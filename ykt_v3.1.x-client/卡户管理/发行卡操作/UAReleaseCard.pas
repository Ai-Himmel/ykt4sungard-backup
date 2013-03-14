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
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  if judgeValue=False then
    if Application.MessageBox('不加条件查询速度可能会很慢，你确定要继续操作吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;
  cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  WorkView.FieldByName('发卡类别').Data.SetInteger(cardType);
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
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
  //if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    //Exit;
  try
    tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
    //tmpData.First;
    feeType := tmpData.FieldByName('lvol5').AsInteger;
    custId := tmpData.FieldByName('lvol1').AsInteger;
    custName := tmpData.fieldbyname('sall_name').AsString;
    //sEndDate := tmpData.FieldByName('sdate3').AsString;
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('请先查询出数据，错误信息：'+ex.Message);
      Exit;
    end;
  end;
  WVFeeQuery.FieldByName('收费类别').Data.SetInteger(feeType);
  WVFeeQuery.FieldByName('卡类型').Data.SetInteger(cardType);
  WVFeeQuery.FieldByName('功能号').Data.SetInteger(846301);
  WVFeeQuery.FieldByName('客户号').Data.SetInteger(custId);
  WVFeeQuery.FieldByName('是否不记名卡').Data.setstring('0');
  WVRFeeQuery.SendCommand;
  //ShowMessage('11');
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
    edtEndDate.Text := WVFeeQuery.fieldbyname('卡有效期').Data.AsString;
    RzStatusPane1.Caption := sReturnInfo;
    selectSign := True;
  end
  else
  begin
    RzStatusPane1.Caption := WVFeeQuery.fieldbyname('返回信息').Data.AsString;
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
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，请先查询，然后再进行操作！');
    Exit;
  end;
  if selectSign=False then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择一条记录，然后再发卡！');
    exit;
  end;
  if Trim(edtEndDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入卡有效期！');
    edtEndDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtEndDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('卡有效期输入有误，格式yyyymmdd！');
    edtEndDate.SetFocus;
    Exit;
  end;
  try
    custName := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sall_name').AsString;
    //取客户号
    custId := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol1').AsInteger;
  except
    Context.GetDialogSystem.ShowMessage('请先选中要发行的记录，然后再进行操作！');
    Exit;
  end;
  cardTypeName := Copy(cbbCardType.Text,Pos('-',cbbCardType.Text)+1,Length(cbbCardType.Text));
  tipInfo := '你是否确定要发行姓名为【'+custname+'】,发卡类别【'+cardtypename+'】的卡？';
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
    if showCardNo='-1' then
      Exit;
    //发卡类型
    cardType := StrToInt(Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1));
    //收费方式
    feeType := Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1);
    WVReleaseCard.FieldByName('操作员').Data.SetString(Context.ParamData(svOperatorNoName).AsString);
    WVReleaseCard.FieldByName('显示卡号').Data.SetString(showCardNo);        //
    WVReleaseCard.FieldByName('物理卡号').Data.SetString(pCardID);           //
    WVReleaseCard.FieldByName('收费方式').Data.SetInteger(StrToInt(feeType));
    WVReleaseCard.FieldByName('票据号码').Data.SetString(edtTicketNo.Text);
    WVReleaseCard.FieldByName('到期日期').Data.SetString(edtEndDate.Text);
    WVReleaseCard.FieldByName('卡类型').Data.SetInteger(cardType);
    WVReleaseCard.FieldByName('客户号').Data.SetInteger(custId);
    try
      WVReleaseCard.FieldByName('收费金额').Data.SetFloat(StrToFloat(edtMoney.Text));
    except
      Context.GetDialogSystem.ShowMessage('金额值不能为空，请输入！');
      edtmoney.SetFocus;
      Exit;
    end;
    WVReleaseCard.FieldByName('是否不记名卡').Data.SetString('0');
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
    if bjopen=1 then
    begin
      bj(bjcomport,'&Sc$');
      //bj(bjcomport,'W');
      bj(bjcomport,'&C11姓名：'+trim(custName)+'$');
      bj(bjcomport,'&C21应收:'+floattostr(fMoney)+'$');
      bj(bjcomport,'&C31实收:'+edtmoney.Text+'$');
      try
        fillMoney := StrToFloat(edtmoney.Text)-fmoney;
        bj(bjcomport,'&C41充值:'+floattostr(fillMoney)+'$');
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
  过程名:    TfaqhReleaseCard.judgeValue判断是否所有的值为空，如果为空则返回false
  作者:      hanjiwei
  日期:      2008.09.24
  参数:      无
  返回值:    Boolean
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
  TUIStdClassFactory.Create('发行卡操作', TfaqhReleaseCard);

end.


