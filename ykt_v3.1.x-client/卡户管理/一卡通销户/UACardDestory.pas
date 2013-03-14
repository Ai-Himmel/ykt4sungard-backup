unit UACardDestory;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, UtCardDll;

type
  TfaqhCardDestory = class(TfaqhSimpleQueryTemp)
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
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVRCardDestory: TWVRequest;
    WVCardDestory: TWorkView;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    Label4: TLabel;
    edtCardNo: TWVEdit;
    btnReadCardNo: TBitBtn;
    WVEdit4: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnRenewCardClick(Sender: TObject);
    procedure btnReadCardNoClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
  private
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardDestory: TfaqhCardDestory;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardDestory.Init;
begin
  inherited;
end;

procedure TfaqhCardDestory.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardDestory.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('钱包号').Data.SetInteger(1);
  inherited;
end;

procedure TfaqhCardDestory.btnRenewCardClick(Sender: TObject);
var
  cardBalance: Integer; //元、分、卡中余额（字符）
  CardID: integer;
  AccUseNum: integer; //客户号 卡号
  CardState: string;
  CardExID, CardPhyID: string;
  CardManage: TCardManage;
  TOF: boolean;
  LPI: LOOPPURSEINFO;
  nPacketNo: smallint;
  ResInt: SmallInt;
  ResInt2: longint;
  patchNo:Integer;//补助批次号

  tmpData:TDataSet;
  custName:string;
  money:Real;
  totMoney:Real;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowWarning('没有数据，无法进行此操作！');
    Exit;
  end;
  if PrepareReadCardInfo=False then
    Exit;
  //判断是否是正常卡
  CardState := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    if Copy(CardState,1,4) = '1000' then             
    begin
      //读物理卡号
      if CardManage.ReadCardPhyID(CardPhyID) <> 0 then
      begin
        Context.GetDialogSystem.ShowMessage('读取卡物理号失败,请将卡放在读写器上！');
        Exit;
      end
      else
        WVCardDestory.FieldByName('卡物理编号').Data.SetString(CardPhyID);

      ResInt := CardManage.ReadExCardID(CardExID);
      if ResInt <> 0 then
      begin
        Context.GetDialogSystem.ShowMessage('读取卡号错误，错误码--'+inttostr(ResInt));
        Exit;
      end;

      //比较卡号是否相符
      CardID := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
      if CardID <> StrToInt(CardExID) then
      begin
        Context.GetDialogSystem.ShowMessage('该卡的卡号和所选择记录的卡号不相符，不能进行退卡操作！');
        Exit;
      end;

      TOF := CardManage.ReadCardConsumeInfo(LPI, nPacketNo); //读取消费信息
      if TOF = False then
      begin
        Context.GetDialogSystem.ShowMessage('读用户卡消费信息失败！');
        CardManage.Destroy;
        Exit;
      end
      else
      begin
        cardBalance := StrToInt(format('%d', [LPI.RemainMoney]));
        AccUseNum:=StrToInt(format('%d', [LPI.DealTimes]));
        patchNo := StrToInt(Format('%d',[LPI.DealTimes_CurDay]))
      end;
      WVCardDestory.FieldByName('卡余额').Data.SetInteger(cardBalance);
      WVCardDestory.FieldByName('卡号').Data.SetInteger(CardID);
      WVCardDestory.FieldByName('交易次数').Data.SetInteger(AccUseNum);
      WVCardDestory.FieldByName('补助批次号').Data.SetInteger(patchNo);
      WVCardDestory.FieldByName('是否有卡').Data.SetInteger(1);
    end
    else
    begin
      CardID := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
      WVCardDestory.FieldByName('卡号').Data.SetInteger(CardID);
      WVCardDestory.FieldByName('卡余额').Data.SetInteger(0);
      WVCardDestory.FieldByName('卡物理编号').Data.SetString('');
      WVCardDestory.FieldByName('交易次数').Data.SetInteger(0);
      WVCardDestory.FieldByName('补助批次号').Data.SetInteger(0);
      WVCardDestory.FieldByName('是否有卡').Data.SetInteger(0);
    end;

    //加入是否退卡押金和卡余额判断
    {
    frmBackCardOper := TfrmBackCardOper.Create(nil);
    frmBackCardOper.ShowModal;
    if frmBackCardOper.iType=0 then
    begin
      frmBackCardOper.Close;
      frmBackCardOper.Free;
      Exit;
    end;
    iYJ := frmBackCardOper.rgyj.ItemIndex;
    iJD := StrToInt(Copy(frmBackCardOper.cbbType.Text,1,Pos('-',frmBackCardOper.cbbType.Text)-1));
    frmBackCardOper.Close;
    frmBackCardOper.Free;
    //----------------------------------------------------------------------------
    }
    if Copy(CardState,1,4) = '1000' then
    begin
      ResInt := CardManage.ReadExCardID(CardExID);
      if ResInt<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('在回收过程中请不要把卡移走！');
        Exit;
      end;
    end;
    WVCardDestory.FieldByName('金额精度').Data.SetInteger(0);
    WVCardDestory.FieldByName('是否退押金').Data.SetInteger(0);

    //ShowWaiting(SWaitingOperation);
    WVRCardDestory.SendCommand;
    if WVCardDestory.FieldByName('返回码').Data.AsInteger = 0 then
    begin
      if (Copy(CardState,1,4) = '1000') then
      begin
        try
          ResInt2 := CardManage.ClearCard;
          if ResInt2=0 then
            CardManage.ControlBuzzer
          else
            Context.GetDialogSystem.ShowMessage('在退卡时没有清空卡信息！');
        except
          Context.GetDialogSystem.ShowMessage('在退卡时没有清空卡信息！');
        end;
      end
      else
        ConText.GetDialogSystem.ShowWarning('在退卡时没有清空卡信息！');

      if bjopen=1 then
        try
          tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
          custName := tmpData.fieldbyname('sall_name').AsString;
          money := tmpData.fieldbyname('damt5').AsFloat;
          bj(bjcomport,'&Sc$');
          bj(bjcomport,'&C11姓  名：'+trim(custName)+'$');
          bj(bjcomport,'&C21卡余额:'+floattostr(money)+'元$');
          try
            totMoney := WVCardDestory.fieldbyname('退款金额').Data.AsFloat;
          except
            totMoney := money;
          end;
          bj(bjcomport,'&C31共退款:'+floattostr(totMoney)+'元$');
        except
        end;

      ShowMessage(WVCardDestory.FieldByName('返回信息').Data.AsString);
      RzStatusPane1.caption:=WVCardDestory.FieldByName('返回信息').Data.AsString;
    end
    else
    begin
      getReturn('收回卡失败--',WVCardDestory);
      RzStatusPane1.caption:=WVCardDestory.FieldByName('返回信息').Data.AsString;
    end;
    //CloseWaiting;
    btnQueryClick(Sender);
  finally
    CardManage.Destroy;
  end;
end;

procedure TfaqhCardDestory.btnReadCardNoClick(Sender: TObject);
begin
  edtCardNo.Text:=readCardNo;
  btnQuery.Click();
end;

procedure TfaqhCardDestory.GridCellClick(Column: TColumn);
var
  tmpData:TDataSet;
  custName:string;
  money:Real;
begin
  //inherited;
  if bjopen=1 then
    try
      tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
      custName := tmpData.fieldbyname('sall_name').AsString;
      money := tmpData.fieldbyname('damt5').AsFloat;
      bj(bjcomport,'W');
      bj(bjcomport,'&Sc$');
      bj(bjcomport,'&C11姓  名：'+trim(custName)+'$');
      bj(bjcomport,'&C21卡余额:'+floattostr(money)+'元s$');
    except
    end;
end;

initialization
  TUIStdClassFactory.Create('一卡通销户', TfaqhCardDestory);

end.


