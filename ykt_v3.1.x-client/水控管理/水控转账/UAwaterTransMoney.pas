unit UAwaterTransMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, UtCardDll;

type
  TfaqhwaterTransMoney = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    WVRBackState: TWVRequest;
    WVBackState: TWorkView;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    GroupBox1: TGroupBox;
    edtsmlMoney: TWVEdit;
    edtMoney: TWVEdit;
    edtNo: TWVEdit;
    edtName: TWVEdit;
    edtCardNo: TWVEdit;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    grp1: TGroupBox;
    edtAddMoney: TWVEdit;
    RzStatusPane6: TRzStatusPane;
    btnTran: TBitBtn;
    btnReadCard: TButton;
    procedure btnTranClick(Sender: TObject);
    procedure edtAddMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
    bigMoney:Integer;
    bigCnt:Integer;
    smallMoney:Integer;
    smallCnt:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhwaterTransMoney: TfaqhwaterTransMoney;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterTransMoney.Init;
begin
  inherited;
  {
  WorkView1.FieldByName('交易卡号').DefaultValue := 0;
  WorkView1.FieldByName('充值金额').DefaultValue := 0.00;
  WorkView1.FieldByName('操作员代码').DefaultValue := '';
  WorkView1.FieldByName('大钱包金额').DefaultValue := 0.00;
  WorkView1.FieldByName('大钱包次数').DefaultValue := 0;
  WorkView1.FieldByName('小钱包次数').DefaultValue := 0;
  WorkView1.FieldByName('小钱包金额').DefaultValue := 0.00;
  WorkView1.Reset;
  }
  btnTran.Enabled := False;
end;

procedure TfaqhwaterTransMoney.btnTranClick(Sender: TObject);
var
  operatorNoName:string;  //操作员
  CardManage: TCardManage;
  st:Integer;
  consumeId:Integer;
  buyWaterId:Integer;
  smloutmoney,bigoutmoney:Real;
  smlMoney,bigMoney:LongInt;
begin
  CardManage := nil;
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  WorkView1.FieldByName('操作员代码').Data.SetString(operatorNoName);
  WorkView1.FieldByName('小钱包次数').Data.SetInteger(smallCnt);
  WorkView1.FieldByName('大钱包次数').Data.SetInteger(bigCnt);
  WorkView1.FieldByName('交易卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
  WorkView1.FieldByName('大钱包金额').Data.SetFloat(StrToFloat(edtMoney.Text));
  WorkView1.FieldByName('小钱包金额').Data.SetFloat(StrToFloat(edtsmlMoney.Text));
  WVRequest1.SendCommand;
  //后台充值成功则写卡
  if WorkView1.fieldbyname('返回码').data.asinteger<>0 then
  begin
    getReturn('',WorkView);
    showmessage(WorkView1.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  consumeId:=WorkView1.fieldbyname('后台流水号').Data.AsInteger;
  buyWaterId:=WorkView1.fieldbyname('购水后台流水号').Data.AsInteger;
  smloutmoney:=WorkView1.fieldbyname('小钱包金额').Data.AsFloat;
  bigoutmoney:=WorkView1.fieldbyname('大钱包金额').Data.AsFloat;
  smlMoney:=Round(smloutmoney*100);
  bigMoney:=Round(bigoutmoney*100);
  try
    CardManage := TCardManage.Create;
    //减钱
    st :=CardManage.setCardMoney(bgPacketNo,bigMoney);
    if st<>0 then
    begin
      //写卡余额进行回滚交易
      WVBackState.FieldByName('消费流水').Data.SetInteger(consumeId);
      WVBackState.FieldByName('充值流水').Data.SetInteger(buyWaterId);
      WVBackState.FieldByName('失败标志').Data.SetInteger(0);
      WVRBackState.SendCommand;
      Context.GetDialogSystem.ShowMessage('扣钱包信息失败，请补写水控钱包信息！');
      Exit;
    end;

    //加钱
    st :=CardManage.setCardMoney(SmlPacketNo,smlMoney);
    if st<>0 then
    begin
      //写卡余额进行回滚交易
      WVBackState.FieldByName('消费流水').Data.SetInteger(consumeId);
      WVBackState.FieldByName('充值流水').Data.SetInteger(buyWaterId);
      WVBackState.FieldByName('失败标志').Data.SetInteger(1);
      WVRBackState.SendCommand;
      Context.GetDialogSystem.ShowMessage('水控钱包加钱失败，请补写水控钱包信息！');
      Exit;
    end;
    ShowMessage('水控转账成功--'+WorkView1.FieldByName('返回信息').Data.AsString);
    edtAddMoney.Text:='0';
    btnTran.Enabled := False;
  finally
    CardManage.Destroy;
  end;
  btnPrint.Enabled:=False;
end;

procedure TfaqhwaterTransMoney.edtAddMoneyKeyPress(Sender: TObject;var Key: Char);
begin
  inherited;
  if Checkedt(Key,edtAddMoney.Text)=False then
    Key := #0;

end;

procedure TfaqhwaterTransMoney.btnReadCardClick(Sender: TObject);
var
  CardManage: TCardManage;
  PCM: TPublishCardMes;
  re: string;
  st:SmallInt;
begin
  CardManage := nil;
  if PrepareReadCardInfo=False then
    Exit;
  try
    CardManage := TCardManage.Create;
    if CardManage.ReadCardPhyID(re) <> 0 then
    begin
      showmessage('读卡序列号失败,该卡已经损坏！');
      Exit;
    end;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      showmessage('读卡信息失败！错误号: ' + IntToStr(st));
      Exit;
    end
    else
    begin
      edtCardNo.Text:=PCM.CardNo;
      edtName.Text:=PCM.ucName;
      edtNo.Text:=PCM.ucCardNo;
    end;
    st := CardManage.ReadBalance(SmlPacketNo,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      ShowMessage('读取小钱包失败！');
      Exit;
    end
    else
    begin
      edtsmlMoney.Text:=format('%f', [smallMoney / 100.0]);
    end;
    st := CardManage.ReadBalance(bgPacketNo,@bigMoney,@bigCnt);
    if st <> 0 then
      showmessage('读用户卡消费信息失败！错误号: ' + IntToStr(st))
    else
      edtmoney.Text:=format('%f', [bigMoney / 100.0]);
    btnTran.Enabled := true;
  finally
    CardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('水控钱包充值',TfaqhwaterTransMoney);

end.