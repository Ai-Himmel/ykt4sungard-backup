unit UACardLose;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, CardDll;

type
  TfaqhCardLose = class(TfaqhSimpleQueryTemp)
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
    Label5: TLabel;
    btnLose: TBitBtn;
    WVCardLose: TWorkView;
    WVRCardLose: TWVRequest;
    btnUnLose: TBitBtn;
    WVEdit4: TWVEdit;
    cbb1: TWVComboBox;
    Label4: TLabel;
    WVEdit5: TWVEdit;
    WVLabel4: TWVLabel;
    WVComboBox4: TWVComboBox;
    btnReadCardNo: TBitBtn; 
    Label8: TLabel;
    edtCardNo: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnLoseClick(Sender: TObject);
    procedure btnUnLoseClick(Sender: TObject);
    procedure btnReadCardNoClick(Sender: TObject);
  private
    { Private declarations }

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardLose: TfaqhCardLose;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardLose.Init;
begin
  inherited;
end;

procedure TfaqhCardLose.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardLose.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  WorkView.FieldByName('钱包号').Data.SetInteger(1);
  inherited;
end;


procedure TfaqhCardLose.btnLoseClick(Sender: TObject);
var
  CardID: integer;
  showCardNo,tmpName,custName:string;
  tipINfo:string;
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

  if Application.MessageBox(PChar('你确定要挂失['+tmpName+']的卡吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;

  WVCardLose.FieldByName('卡号').Data.SetInteger(CardID);
  WVCardLose.FieldByName('操作标志').Data.SetString('1');

  try
   //ShowWaiting(SWaitingOperation);
    WVRCardLose.SendCommand;
  finally
    //CloseWaiting;
    tipINfo := WVCardLose.fieldbyname('返回信息').Data.AsString;
    if (WVCardLose.FieldByName('返回码').Data.AsInteger = 0) then
    begin
      Context.GetDialogSystem.ShowSuccess('挂失校园卡操作成功  '+tipINfo);
      RzStatusPane1.Caption := '挂失校园卡操作成功  '+tipINfo
    end
    else
    begin
      getReturn('挂失校园卡失败  ',WVCardLose);
      RzStatusPane1.Caption := '挂失校园卡失败  '+tipINfo
    end;
  end;
  try
    MainRequest.SendCommand;
  except
  end;
end;

procedure TfaqhCardLose.btnUnLoseClick(Sender: TObject);
var
  dbCardNo: integer;
  cardNo:string;
  cm: TCM;
  tipInfo:string;
  st:Integer;
  phyId:string;
  cardSign:Integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;

  if preReadCard=False then
    Exit;

  dbCardNo := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
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
    if cardNo = '' then
    begin
      Context.GetDialogSystem.ShowWarning('读取交易卡号失败！');
      Exit;
    end;
    if cardSign=FEE_LOCK_CARD then
    begin
      Context.GetDialogSystem.ShowMessage('该卡状态为后付费锁卡，请到后付费扣款界面操作！');
      Exit;
    end;
    if StrToInt(cardno) <> dbCardNo then
    begin
      Context.GetDialogSystem.ShowWarning('你所操作的卡和读写器上放置的不是同一张卡！');
      Exit;
    end;

    WVCardLose.FieldByName('卡号').Data.SetInteger(dbCardNo);
    WVCardLose.FieldByName('操作标志').Data.SetString('2');

    //ShowWaiting(SWaitingOperation);
    WVRCardLose.SendCommand;
    if WVCardLose.FieldByName('返回码').Data.AsInteger = 0 then
    begin
      tipINfo := WVCardLose.fieldbyname('返回信息').Data.AsString;
      cm.clearallfieldwritemode;
      cm.setfieldwritemode(BLACK_CARD_SIGN);
      cm.setfieldwritemode(BLACK_VER);
      cm.setBlackCardSign(IntToStr(NORMAL_CARD));
      cm.setBlackVer(WVCardLose.FieldByName('卡版本号').Data.AsString);
      st := cm.writeData(phyId);
      if st <> 0 then
      begin
        Context.GetDialogSystem.ShowWarning('解挂卡失败，错误码--'+inttostr(st));
      end
      else
      begin
        cm.beep;
        Context.GetDialogSystem.ShowSuccess('解挂卡成功  '+tipInfo);
        RzStatusPane1.Caption := '解挂卡成功  '+tipINfo
      end;
    end
    else
    begin
      getReturn('解挂卡失败  ',WVCardLose);
      RzStatusPane1.Caption := '解挂卡失败  '+tipINfo
    end;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardLose.btnReadCardNoClick(Sender: TObject);
var
  cardNo:string;
begin
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
  TUIStdClassFactory.Create('挂失解挂操作', TfaqhCardLose);

end.


