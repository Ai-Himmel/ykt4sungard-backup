unit UMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db, 
  RzStatus, EditExts, RzEdit, Buttons, UtCardDll;

type
  TfaMoney = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    btnReadCardInfo: TBitBtn;
    btnMoneyOut: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    grp2: TGroupBox;
    edtmoney: TWVDigitalEdit;
    WVLabel1: TWVLabel;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    edtAfterMoney: TRzEdit;
    RzStatusPane7: TRzStatusPane;
    lblTip: TLabel;
    WVcashOperCancel: TWorkView;
    WVRcashOperCancel: TWVRequest;
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure btnMoneyOutClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;

    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCardManage);
  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faMoney: TfaMoney;
  OldMoney: string;

implementation
uses KsFrameworks, 
  KSClientConsts;

{$R *.DFM}

procedure TfaMoney.Init;
begin
  inherited;
  btnMoneyOut.Enabled:=false;
  lblTip.Caption := '';
  btnreadcardinfo.setfocus;
end;


procedure TfaMoney.btnReadCardInfoClick(Sender: TObject);
var
  CardExID: string;
  CardManage: TCardManage;
  PCM: TPublishCardMes;
  TOF: boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  CardPhyID:string;
  //ResInt: SmallInt;
begin
  lblTip.Caption := '';
  CardExID:=readCardNo;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;

    if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取物理卡号失败,该卡已经损坏！');
      Exit;
    end;
    oldPhyId := CardPhyID;
    
    edtCardNo.Text := CardExID;
    if CardManage.ReadCardInfo(PCM) = 0 then
    begin
      edtName.Text := PCM.ucName;
      edtStuempNo.Text := PCM.ucCardNo;
    end
    else
    begin
      Context.GetDialogSystem.ShowWarning('读取卡基本信息失败！');
      CardManage.Destroy;
      Exit;
    end;
    //读取卡中余额
    TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo);
    if TOF = True then
    begin
      OldMoney := IntToStr(LPI.RemainMoney);
      edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
      edtAfterMoney.Text :=format('%f', [StrToInt(OldMoney) / 100.0]);
      //edtMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
    end
    else
    begin
      Context.GetDialogSystem.ShowWarning('读取卡余额失败！');
      CardManage.Destroy;
      Exit;
    end;
    if bjopen=1 then
    begin
      {
      bj(bjcomport,'W');
      bj(bjcomport,'&C11姓  名：'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21卡余额：'+trim(edtCardMoney.Text)+'元$');
      }

      bj(bjcomport,'W');
      bj(bjcomport,'&C11姓  名:'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21卡余额:'+trim(edtCardMoney.Text)+'?$');
      bj(bjcomport, 't');
      bj(bjcomport, trim(edtCardMoney.Text)+'P'); //
    end;

    btnMoneyOut.Enabled:=True;
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaMoney.btnMoneyOutClick(Sender: TObject);
var
  CardPhyID: string;
  tradeNum:Integer;
  balance:Integer;
  OutMoney: Integer;

  //rCardNo:Integer;
  rTradeDate:string;
  rStationNo:Integer;
  SeilID: integer;
  CardManage: TCardManage;
  TOF: Integer;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  NewMoney: Integer;
begin
  if PrepareReadCardInfo=False then
    Exit;

  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //读取物理卡号
    CardPhyID := '';
    if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读取物理卡号失败！');
      CardManage.Destroy;
      Exit;
    end
    else
      WorkView.FieldByName('物理卡号').Data.SetString(CardPhyID);

    if oldPhyId <> CardPhyID then
    begin
      ShowMessage('请使用同一张卡进行支取金额！');
      btnReadCardInfo.SetFocus;
      btnMoneyOut.Enabled := False;
      Exit;
    end;
    //交易次数
    if CardManage.ReadCardConsumeInfo(LPI, nPacketNo) then
    begin
      tradeNum:=StrToInt(format('%d', [LPI.DealTimes]));
      balance := StrToInt(Format('%d',[LPI.RemainMoney]));
    end else
    begin
      Context.GetDialogSystem.ShowMessage('读取卡消费次数失败，操作取消！');
      Exit;
    end;

    if (StrToFloat(edtCardMoney.Text))<(StrToFloat(Trim(edtMoney.Text))) then
    begin
      Context.GetDialogSystem.ShowMessage('你支取的余额超出可用余额！');
      Exit;
    end;
    //发送功能号
    WorkView.SynchronizeCtrlsToFields;
    WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('物理卡号').Data.SetString(CardPhyID);
    WorkView.FieldByName('交易次数').Data.SetInteger(tradeNum);
    WorkView.FieldByName('入卡金额').Data.SetInteger(balance);
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.asinteger<>0 then
    begin
      getReturn('卡支取失败－－',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('返回信息').Data.AsString;
      Exit;
    end;

    OutMoney := WorkView.FieldByName('出卡金额').Data.AsInteger;
    SeilID := WorkView.FieldByName('流水号').Data.AsInteger;
    //rCardNo := WorkView.FieldByName('卡号').Data.AsInteger;
    rTradeDate := WorkView.FieldByName('业务日期').Data.AsString;
    rStationNo := WorkView.FieldByName('终端编号').Data.AsInteger;

    //更新卡余额,0成功，-10不确定，其他结果均为失败
    TOF := CardManage.PacketSetMoney(IntToStr(OutMoney));
    if TOF = 0 then
    begin
      writeSuccess(WorkView,OutMoney,CardManage);
    end
    else if TOF= -10 then
    begin
      newmoney := CardManage.readCardMoney(1);
      if NewMoney=OutMoney then
      begin
        writeSuccess(WorkView,OutMoney,CardManage);
      end
      else
      begin
        RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,rStationNo);
      end;
    end
    else
    begin
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,rStationNo);
    end;

  finally
    CardManage.Destroy;
  end;

end;

procedure TfaMoney.writeSuccess(wv: TWorkView; money: Integer;
  cm: TCardManage);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.ControlBuzzer;
  if bjopen=1 then
  begin
    {
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11姓  名：'+trim(edtName.Text)+'$');
    bj(bjcomport,'&C21充  值：'+trim(edtmoney.Text)+'元$');
    bj(bjcomport,'&C31卡余额：'+trim(edtAfterMoney.Text)+'元$');
    }

    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11姓  名:'+trim(edtName.Text)+'$');
    bj(bjcomport,'&C21充  值:'+trim(edtmoney.Text)+'?$');
    bj(bjcomport, 'B');    //发声，预收
    bj(bjcomport, trim(edtmoney.Text)+'P');//发声，多少钱

    bj(bjcomport,'&C31卡余额:'+trim(edtAfterMoney.Text)+'?$');

    bj(bjcomport, 't'); //发声，账户余额
    bj(bjcomport, trim(edtAfterMoney.Text)+'P');   //发声，多少钱
    bj(bjcomport,'&C41谢谢'+'X');
    
  end;

  btnMoneyOut.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('返回信息').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('卡现金支取',TfaMoney);

end.
