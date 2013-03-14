unit UAwaterTrans_nmg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, RzStatus, UtCardDll;

type
  TfaqhwaterTrans_nmg = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
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
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    procedure edtAddMoneyKeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnTranClick(Sender: TObject);
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
  faqhwaterTrans_nmg: TfaqhwaterTrans_nmg;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhwaterTrans_nmg.Init;
begin
  inherited;
  btnTran.Enabled := False;
end;

procedure TfaqhwaterTrans_nmg.edtAddMoneyKeyPress(Sender: TObject;var Key: Char);
begin
  inherited;
  if Checkedt(Key,edtAddMoney.Text)=False then
    Key := #0;
end;

procedure TfaqhwaterTrans_nmg.btnReadCardClick(Sender: TObject);
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
      Context.GetDialogSystem.showmessage('读卡序列号失败,该卡已经损坏！');
      Exit;
    end;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      Context.GetDialogSystem.showmessage('读卡信息失败！错误号: ' + IntToStr(st));
      Exit;
    end
    else
    begin
      edtCardNo.Text:=PCM.CardNo;
      edtName.Text:=PCM.ucName;
      edtNo.Text:=PCM.ucCardNo;
    end;
    st := CardManage.ReadBalance(SmlPacketNo2,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取小钱包失败！');
      Exit;
    end
    else
    begin
      edtsmlMoney.Text:=format('%f', [smallMoney / 100.0]);
    end;
    st := CardManage.ReadBalance(bgPacketNo,@bigMoney,@bigCnt);
    if st <> 0 then
      Context.GetDialogSystem.showmessage('读用户卡消费信息失败！错误号: ' + IntToStr(st))
    else
      edtmoney.Text:=format('%f', [bigMoney / 100.0]);
    btnTran.Enabled := true;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhwaterTrans_nmg.btnTranClick(Sender: TObject);
var
  cardManage: TCardManage;
  PCardID:string;
  smallMoney:Integer;
  smallCnt:Integer;
  st:Integer;
begin
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //取物理卡号
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡序列号失败，请重新把卡放置到读写器上！');
      exit;
    end;
    //发卡成功后给小钱包加钱
    st := CardManage.ReadBalance(smlPacketNo2,@smallMoney,@smallCnt);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取补助开水钱包失败！错误号: ' + IntToStr(st));
      Exit;
    end;
    WorkView1.FieldByName('卡号').Data.SetInteger(StrToInt(readCardNo));
    WorkView1.FieldByName('入卡金额').Data.SetInteger(smallMoney);
    WorkView1.FieldByName('交易次数').Data.SetInteger(smallCnt);
    WorkView1.FieldByName('金额').Data.SetFloat(StrToFloat(edtAddMoney.Text));
    WorkView1.FieldByName('物理卡号').Data.SetString(pCardID);
    WVRequest1.SendCommand;
    if (WorkView1.FieldByName('返回码').Data.AsInteger=0) then
    begin
      Context.GetDialogSystem.ShowMessage(writeWaterMoney(WorkView1,WVcashOperCancel,WVRcashOperCancel));
    end
    else
      Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString+'--请直接到补助开水金额设置里设置金额');
  finally
    CardManage.Destroy;
  end;

end;

initialization
  TUIStdClassFactory.Create('水控钱包充值',TfaqhwaterTrans_nmg);

end.