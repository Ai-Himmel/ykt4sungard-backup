unit UApubPASMCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzRadGrp, RzEdit,
  UIncrementComboBox, RzStatus, Buttons, CardDll;

type
  TfaqhPASMCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp1: TGroupBox;
    edtLimitDate: TRzEdit;
    Label2: TLabel;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    btnPubAuth: TBitBtn;
    edtBeginDate: TRzEdit;
    lbl1: TLabel;
    rzstspn1: TRzStatusPane;
    cbbUser: TWVComboBox;
    rzstspn3: TRzStatusPane;
    cbbCardType: TWVComboBox;
    procedure btnPubAuthClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPASMCard: TfaqhPASMCard;

implementation

uses KsFrameworks, 
     KSClientConsts,SmartCardCommon, UKey;
     
{$R *.DFM}

procedure TfaqhPASMCard.Init;
begin
  inherited;
  edtBeginDate.Text := FormatDateTime('yyyymmdd',Date);
  edtLimitDate.Text:=FormatDateTime('yyyymmdd',Date()+365);
  //cbbpasmSeat.ItemIndex := pasmseat;
  if not SmartCardPortStatus then
    Exit;
end;

procedure TfaqhPASMCard.btnPubAuthClick(Sender: TObject);
var
  cardUser:string;
  CardNo:string;
  CardType:string;
  TermID:string;
  //KeyIndex:Integer;
  PublishID:string;
  st:Integer;
  vKey:string;
  pasmCard:TPUBPSAMCARD;
  reError:array[0..128] of char;
begin
  if Trim(edtBeginDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入启用日期！');
    edtBeginDate.SetFocus;
    Exit;
  end;
  if Trim(edtLimitDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入有效日期！');
    edtLimitDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtBeginDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('开始日期输入不正确，格式：yyyymmdd');
    edtBeginDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtLimitDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('有效日期输入不正确，格式：yyyymmdd');
    edtLimitDate.SetFocus;
    Exit;
  end;

  cardUser := Copy(cbbUser.Text,1,Pos('-',cbbUser.Text)-1);
  if ((cardUser='')or (cardUser='0')) then
  begin
    Context.GetDialogSystem.ShowMessage('请选择设备使用方！');
    cbbUser.SetFocus;
    Exit;
  end;

  CardType:=Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1);
  if ((CardType='')or (CardType='0')) then
  begin
    Context.GetDialogSystem.ShowMessage('请选择PASM卡类型！');
    cbbUser.SetFocus;
    Exit;
  end;
  if not preReadCard then
    Exit;
  if Application.MessageBox(PChar('你是否要发行该PSAM卡？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  //ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  //ks_samcpureset;
  WorkView.FieldByName('启用日期').Data.SetString(Trim(edtBeginDate.Text));
  WorkView.FieldByName('有效日期').Data.SetString(Trim(edtLimitDate.Text));
  WorkView.FieldByName('设备使用方').Data.SetString(cardUser);
  WorkView.FieldByName('卡类型').Data.SetInteger(StrToInt(CardType));
  WorkView.FieldByName('操作标志').Data.SetString('A');
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger=0 then
  begin
    CardNo:=WorkView.fieldbyname('pasm卡号').Data.AsString;
    TermID:=WorkView.fieldbyname('终端编号').Data.AsString;
    //KeyIndex:=StrToInt(WorkView.fieldbyname('索引号').Data.AsString);
    PublishID:=WorkView.fieldbyname('发行方标识').Data.AsString;
    //检测密钥是否存在，不存在则加载
    {
    st := ks_checkloadkeys;
    if st=0 then
    begin
      try
        frmKey := TfrmKey.Create(nil);
        frmKey.ShowModal;
        vKey := frmKey.getPwd;
      finally
        frmKey.Free;
      end;
      st := ks_loadcardkeys(PChar(vKey));
      if st <>0 then
      begin
        Context.GetDialogSystem.ShowMessage('装载密钥失败，请先放置密钥卡--'+inttostr(st));
        Exit;
      end;
    end;
    }
    //preReadPASM(pasmCard);
    ZeroMemory(@pasmCard,SizeOf(pasmCard));
    //开始发行pasm卡
    StrCopy(@pasmCard.CardNo,PChar(CardNo));
    pasmCard.CardType := StrToInt(CardType);
    pasmCard.CardVer := 1;
    StrCopy(@pasmCard.TermID,PChar(TermID));
    pasmCard.KeyIndex := 0;
    StrCopy(@pasmCard.StartDate,PChar(Trim(edtBeginDate.Text)));
    StrCopy(@pasmCard.ExpireDate,PChar(Trim(edtLimitDate.Text)));
    StrCopy(@pasmCard.PublishID,PChar(PublishID));
    StrCopy(@pasmCard.UserID,PChar(cardUser));
    //ShowMessage(pasmCard.ExpireDate);
    st := ks_publishpsamcard(@pasmcard);
    if st<>0 then
    begin
      ks_geterrmsg(PChar(@reError));
      Context.GetDialogSystem.ShowMessage('发行PSAM卡失败--'+reError);
      //RzStatusPane1.Caption := reError;
      //Context.GetDialogSystem.ShowMessage('发行PASM卡失败--'+inttostr(st));
    end
    else
    begin
      KNG_beep;
      Context.GetDialogSystem.ShowMessage('发行PSAM卡成功！');
    end;
  end
  else
  begin
    RzStatusPane1.Caption := WorkView.fieldbyname('返回信息').Data.AsString;
  end;
end;

initialization
  TUIStdClassFactory.Create('PSAM卡发行',TfaqhPASMCard);

end.