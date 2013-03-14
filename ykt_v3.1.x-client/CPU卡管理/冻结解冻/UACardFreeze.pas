unit UACardFreeze;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, CardDll;

type
  TfaqhCardFreeze = class(TfaqhSimpleQueryTemp)
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
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    btnFreeze: TBitBtn;
    WVCardFreeze: TWorkView;
    WVRCardFreeze: TWVRequest;
    btnUnFreeze: TBitBtn;
    rgCardSign: TRadioGroup;
    btnPatchOper: TBitBtn;
    WVEdit4: TWVEdit;
    WVLabel3: TWVLabel;
    WVComboBox4: TWVComboBox;
    WVLabel4: TWVLabel;
    WVComboBox7: TWVComboBox;
    Label8: TLabel;
    edtCardNo: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnFreezeClick(Sender: TObject);
    procedure btnUnFreezeClick(Sender: TObject);
    procedure btnPatchOperClick(Sender: TObject);
  private
    { Private declarations }

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardFreeze: TfaqhCardFreeze;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardFreeze.Init;
var
  operId : string;
begin
  operId := Context.ParamData(svOperatorNoName).AsString;
  inherited;
  {
  if operId='system' then
    btnPatchOper.Visible:=True
  else
    btnPatchOper.Visible := False;
  }
end;

procedure TfaqhCardFreeze.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardFreeze.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  WorkView.FieldByName('钱包号').Data.SetInteger(1);
  inherited;
end;


procedure TfaqhCardFreeze.btnFreezeClick(Sender: TObject);
var
  CardID: integer;
  custName:string;
  showCardNo:string;
  tmpName:string;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;

  CardID := (WorkView.FieldByName('查询结果集').Data.AsObject as
    TDataSet).FieldByName('lvol0').AsInteger;
  custName := (WorkView.FieldByName('查询结果集').Data.AsObject as
    TDataSet).FieldByName('sall_name').AsString;
  showCardNo := (WorkView.FieldByName('查询结果集').Data.AsObject as
    TDataSet).FieldByName('sorder0').AsString;

  if Trim(custName)='' then
    tmpName := showCardNo
  else
    tmpName := custName;
  if Application.MessageBox(PChar('你确定要冻结['+tmpName+']的卡吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  WVCardFreeze.FieldByName('卡号').Data.SetInteger(CardID);
  WVCardFreeze.FieldByName('操作标志').Data.SetString('1');

  try
    //ShowWaiting(SWaitingOperation);
    WVRCardFreeze.SendCommand;
  finally
    //CloseWaiting;
    if (WVCardFreeze.FieldByName('返回码').Data.AsInteger = 0) then
    begin
      Context.GetDialogSystem.ShowSuccess('冻结校园卡操作成功！');
    end
    else
    begin
      getReturn('冻结校园卡失败  ',WVCardFreeze);
    end;
  end;
  try
    MainRequest.SendCommand;
  except
  end;
end;

procedure TfaqhCardFreeze.btnUnFreezeClick(Sender: TObject);
var
  dbCardNo: integer;
  CardNo:string;
  cm: TCM;
  tipInfo:string;
  st:integer;
  phyId:string;
  cardSign:Integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;
  dbCardNo := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
  tipInfo := '卡号为【'+inttostr(dbCardNo)+'】的卡';
  if rgCardSign.ItemIndex=0 then
  begin
    if  preReadCard=False then
      Exit;
    cm := nil;
    try
      cm := TCM.Create;
      st := cm.card(phyId);
      if st<>0 then
      begin
        context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
        exit;
      end;
      cm.clearallfieldreadmode;
      cm.setfieldreadmode(CARD_NO);
      cm.setfieldreadmode(BLACK_CARD_SIGN);
      st := cm.readCard(phyId);
      if st<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('读卡失败-'+geterrmsg);
        Exit;
      end;
      cardNo := cm.getCardNo;
      try
        cardSign := StrToInt(cm.getBlackCardSign);
      except
        Context.GetDialogSystem.ShowMessage('读取卡标志失败-'+geterrmsg);
        Exit;
      end;
      //CardNo := readCardOneInfo(CARD_NO);
      if CardNo= '' then
      begin
        Context.GetDialogSystem.ShowWarning('读取交易卡号失败！');
        Exit;
      end;
      if cardSign=FEE_LOCK_CARD then
      begin
        Context.GetDialogSystem.ShowMessage('该卡状态为后付费锁卡，请到后付费扣款界面操作！');
        Exit;
      end;

      if StrToInt(CardNo) <> dbCardNo then
      begin
        Context.GetDialogSystem.ShowWarning('你所操作的卡和读写器上放置的不是同一张卡！');
        Exit;
      end;

      WVCardFreeze.FieldByName('卡号').Data.SetInteger(dbCardNo);
      WVCardFreeze.FieldByName('操作标志').Data.SetString('2');

      //ShowWaiting(SWaitingOperation);
      WVRCardFreeze.SendCommand;
      if WVCardFreeze.FieldByName('返回码').Data.AsInteger = 0 then
      begin
        //try
          //写卡操作
          //先清除所有的读取权限
          cm.clearallfieldreadmode;
          cm.setfieldwritemode(BLACK_CARD_SIGN);
          cm.setfieldwritemode(BLACK_VER);
          cm.setBlackCardSign(IntToStr(NORMAL_CARD));
          cm.setBlackVer(WVCardFreeze.FieldByName('卡版本号').Data.AsString);
          if cm.writeData(phyId)=0 then
          begin
            cm.beep;
            Context.GetDialogSystem.ShowSuccess(tipInfo+'解冻成功！');
          end
          else
          begin
            Context.GetDialogSystem.ShowWarning('解冻卡失败！');
            Exit;
          end;
      end
      else
      begin
        Context.GetDialogSystem.ShowWarning(tipInfo+'解冻失败！');
      end;
    finally
      cm.Destroy;
    end;
  end
  else
  begin
    WVCardFreeze.FieldByName('卡号').Data.SetInteger(dbCardNo);
    WVCardFreeze.FieldByName('操作标志').Data.SetString('2');

    WVRCardFreeze.SendCommand;
    if WVCardFreeze.FieldByName('返回码').Data.AsInteger = 0 then
      Context.GetDialogSystem.ShowSuccess(tipInfo+'解冻成功！')
    else
      Context.GetDialogSystem.ShowWarning(tipInfo+'解冻失败！');
  end;
  btnQuery.Click;
end;

procedure TfaqhCardFreeze.btnPatchOperClick(Sender: TObject);
var
  cardNo:string;
  //cardId:Integer;
begin
  {
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;
  if Application.MessageBox('你确定要批量冻结该批卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  Grid.DataSource.DataSet.First;
  while not Grid.DataSource.DataSet.Eof do
  begin
    CardID := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
    WVCardFreeze.FieldByName('卡号').Data.SetInteger(CardID);
    WVCardFreeze.FieldByName('操作标志').Data.SetString('1');
    WVRCardFreeze.SendCommand;
    if WVCardFreeze.FieldByName('返回码').Data.AsInteger <> 0 then
    begin
      Context.GetDialogSystem.ShowWarning('卡号为'+inttostr(cardId)+'的卡冻结失败！');
      Exit;
    end;
    Sleep(200);
    Grid.DataSource.DataSet.Next;
  end;
  ShowMessage('该批卡冻结成功！');
  btnQuery.Click;
  }
  edtCardNo.Text:='';
  try
    cardNo := readCardOneInfo(CARD_NO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，卡号为零或不存在!');
    Exit;
  end;
  edtCardNo.Text:=cardNo;
  btnQuery.Click();
end;

initialization
  TUIStdClassFactory.Create('冻结解冻操作', TfaqhCardFreeze);

end.


