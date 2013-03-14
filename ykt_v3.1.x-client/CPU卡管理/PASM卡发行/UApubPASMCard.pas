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
    Context.GetDialogSystem.ShowMessage('�������������ڣ�');
    edtBeginDate.SetFocus;
    Exit;
  end;
  if Trim(edtLimitDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��������Ч���ڣ�');
    edtLimitDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtBeginDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��ʼ�������벻��ȷ����ʽ��yyyymmdd');
    edtBeginDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtLimitDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��Ч�������벻��ȷ����ʽ��yyyymmdd');
    edtLimitDate.SetFocus;
    Exit;
  end;

  cardUser := Copy(cbbUser.Text,1,Pos('-',cbbUser.Text)-1);
  if ((cardUser='')or (cardUser='0')) then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ���豸ʹ�÷���');
    cbbUser.SetFocus;
    Exit;
  end;

  CardType:=Copy(cbbCardType.Text,1,Pos('-',cbbCardType.Text)-1);
  if ((CardType='')or (CardType='0')) then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��PASM�����ͣ�');
    cbbUser.SetFocus;
    Exit;
  end;
  if not preReadCard then
    Exit;
  if Application.MessageBox(PChar('���Ƿ�Ҫ���и�PSAM����'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  //ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  //ks_samcpureset;
  WorkView.FieldByName('��������').Data.SetString(Trim(edtBeginDate.Text));
  WorkView.FieldByName('��Ч����').Data.SetString(Trim(edtLimitDate.Text));
  WorkView.FieldByName('�豸ʹ�÷�').Data.SetString(cardUser);
  WorkView.FieldByName('������').Data.SetInteger(StrToInt(CardType));
  WorkView.FieldByName('������־').Data.SetString('A');
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger=0 then
  begin
    CardNo:=WorkView.fieldbyname('pasm����').Data.AsString;
    TermID:=WorkView.fieldbyname('�ն˱��').Data.AsString;
    //KeyIndex:=StrToInt(WorkView.fieldbyname('������').Data.AsString);
    PublishID:=WorkView.fieldbyname('���з���ʶ').Data.AsString;
    //�����Կ�Ƿ���ڣ������������
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
        Context.GetDialogSystem.ShowMessage('װ����Կʧ�ܣ����ȷ�����Կ��--'+inttostr(st));
        Exit;
      end;
    end;
    }
    //preReadPASM(pasmCard);
    ZeroMemory(@pasmCard,SizeOf(pasmCard));
    //��ʼ����pasm��
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
      Context.GetDialogSystem.ShowMessage('����PSAM��ʧ��--'+reError);
      //RzStatusPane1.Caption := reError;
      //Context.GetDialogSystem.ShowMessage('����PASM��ʧ��--'+inttostr(st));
    end
    else
    begin
      KNG_beep;
      Context.GetDialogSystem.ShowMessage('����PSAM���ɹ���');
    end;
  end
  else
  begin
    RzStatusPane1.Caption := WorkView.fieldbyname('������Ϣ').Data.AsString;
  end;
end;

initialization
  TUIStdClassFactory.Create('PSAM������',TfaqhPASMCard);

end.