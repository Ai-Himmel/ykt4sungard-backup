unit UAwaterCardPatch;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzStatus, Buttons, UtCardDll;

type
  TfaqhwaterCardPatch = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    Label1: TLabel;
    edtCardNo: TWVEdit;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    Label4: TLabel;
    WVEdit4: TWVEdit;
    Label5: TLabel;
    WVEdit1: TWVEdit;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    WVRReCreCardOK: TWVRequest;
    WVReCreCardOK: TWorkView;
    WorkView3: TWorkView;
    WVRequest3: TWVRequest;
    btnPacth: TBitBtn;
    btnReadCardQuery: TBitBtn;
    RzStatusPane1: TRzStatusPane;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardQueryClick(Sender: TObject);
    procedure btnPacthClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhwaterCardPatch: TfaqhwaterCardPatch;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterCardPatch.Init;
begin
  inherited;
  WorkView.FieldByName('显示卡号').DefaultValue := '';
  WorkView.FieldByName('学工号').DefaultValue := '';
  WorkView.FieldByName('姓名').DefaultValue := '';
  WorkView.FieldByName('身份证号').DefaultValue := '';
  WorkView.FieldByName('卡号').DefaultValue := 0;
  WorkView.Reset;
end;

procedure TfaqhwaterCardPatch.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhwaterCardPatch.btnQueryClick(Sender: TObject);
begin
  if Trim(WVEdit2.Text) = '' then
  begin
    WorkView.FieldByName('学工号').Data.SetString('');
  end;
  if Trim(edtCardNo.Text)='' then
    WorkView.FieldByName('卡号').Data.SetInteger(0);
  inherited;

end;

procedure TfaqhwaterCardPatch.btnReadCardQueryClick(Sender: TObject);
begin
  inherited;
  edtCardNo.Text:=readCardNo;
  btnQuery.Click();
end;

procedure TfaqhwaterCardPatch.btnPacthClick(Sender: TObject);
var
  BackSerilID: integer;
  CardPhyID: string;
  tempDataSet: TDataSet;
  CardID: integer;
  EMoneyInCard: string;
  CardManage: TCardManage;
  OperatorNoName: string;
  TranExID: integer;
  isOldCard: Boolean;
  dealNum :integer;
  cardMoney:LongInt;         //卡余额
  backTradeID:Integer;
  iPacket:Integer;
  re:Integer;
  money:Integer;
begin
  if PrepareReadCardInfo=False then
    Exit;

  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('没有数据，无法进行此操作！');
    Exit;
  end;

  //取当前查询数据集
  tempDataSet := WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet;
  TranExID := tempDataSet.FieldByName('lvol2').AsInteger;
  iPacket := tempDataSet.FieldByName('lvol4').AsInteger;
  CardManage := TCardManage.Create;

  //取物理序列号 CardPhyID
  CardPhyID := '';
  if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
  begin
    Context.GetDialogSystem.ShowWarning('读取卡物理序列号失败！');
    CardManage.Destroy;
    Exit; 
  end;

  //判断交易号，确定是是否为新发的卡
  if ((TranExID = 847101) or (TranExID = 847125) or (TranExID = 847116) or
    (TranExID = 847104)) then
  begin
    isOldCard := False;
  end
  else
  begin
    isOldCard := True;
  end;
  if isOldCard = False then
  begin
    //余额
    EMoneyInCard := '0.00';
    //交易次数
    dealNum := 0;
  end
  else if isOldCard = True then
  begin
    //如果是发行新卡交易出错，则不读卡上的余额
    //如果是其他交易出错，则要读取卡上的余额
    //TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
    re := CardManage.ReadBalance(iPacket+1,@Money,@dealNum);
    if re <> 0 then
    begin
      Context.GetDialogSystem.ShowWarning('读用户卡消费信息失败-'+inttostr(re));
      CardManage.Destroy;
      Exit;
    end
    else
    begin
      EMoneyInCard := format('%f', [Money / 100.0]);
    end;
  end;

  CardID := tempDataSet.FieldByName('lvol0').AsInteger;
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;

  //调用功能号，向后台写信息
  WorkView2.FieldByName('物理卡号').Data.SetString(CardPhyID);
  WorkView2.FieldByName('卡标识').Data.SetInteger(CardID);
  WorkView2.FieldByName('入卡值').Data.SetFloat(StrToFloat(EMoneyInCard));
  WorkView2.FieldByName('操作员号').Data.SetString(OperatorNoName);
  WorkView2.FieldByName('设备号').Data.SetInteger(SmartCardSubSystemNo);
  WorkView2.FieldByName('工作站号').Data.SetInteger(SmartCardSubSystemNo);
  WorkView2.FieldByName('交易次数').Data.SetInteger(dealNum);
  WorkView2.FieldByName('钱包号').Data.SetInteger(iPacket);
  WVRequest2.SendCommand;
  
  if WorkView2.fieldbyname('返回码').data.asinteger=0 then
  begin
    BackSerilID:=WorkView2.FieldByName('后台交易流水号').Data.AsInteger;
    CardID:=WorkView2.FieldByName('交易卡号').Data.AsInteger;

    //如果不是新发行的卡则只需要更新卡余额
    if isOldCard=True then
    begin
      cardMoney := StrToInt(FloatToStr(WorkView2.fieldbyname('出卡值').Data.AsFloat* 100));
      backTradeID:=WorkView2.fieldbyname('后台交易流水号').Data.Asinteger;
      //使用新的设置钱包信息函数setCardMoney(nPacketNo, money: Integer)，0成功
      re := CardManage.setCardMoney(iPacket+1,Cardmoney);
      if re=0 then
      begin
        CardManage.ControlBuzzer;
        RzStatusPane1.Caption:='补写卡成功，卡金额为:'+FloatToStr(WorkView2.fieldbyname('出卡值').Data.AsFloat);
      end
      else
      begin
        WorkView3.FieldByName('卡标识').Data.SetInteger(CardID);
        WorkView3.FieldByName('后台交易流水号').Data.SetInteger(backTradeID);
        WorkView3.FieldByName('交易码').Data.SetInteger(847119);
        WVRequest3.SendCommand;
        Context.GetDialogSystem.ShowSuccess('写卡失败:'+'--卡状态为写卡失败状态，请重新补写卡信息！');
        RzStatusPane1.Caption:='写卡失败:'+'--卡状态为写卡失败状态，请重新补写卡信息！';
        CardManage.Destroy;
        exit;
      end;
    end;
    WVReCreCardOK.FieldByName('钱包号').Data.SetInteger(iPacket);
    WVReCreCardOK.FieldByName('卡标识').Data.SetInteger(CardID);
    WVReCreCardOK.FieldByName('交易码').Data.SetInteger(847119);
    WVReCreCardOK.FieldByName('交易流水号').Data.SetInteger(BackSerilID);
    WVRReCreCardOK.SendCommand;
  end
  else
  begin
    getReturn('',WorkView2);
    RzStatusPane1.Caption:=WorkView2.FieldByName('返回信息').Data.AsString;
  end;

  MainRequest.SendCommand;
  CardManage.Destroy;
end;

initialization
  TUIStdClassFactory.Create('水控卡信息补写',TfaqhwaterCardPatch);

end.