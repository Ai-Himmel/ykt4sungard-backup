unit UAReadPASMCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzRadGrp, RzEdit,
  UIncrementComboBox, RzStatus, Buttons, CardDll;

type
  TfaqhReadPASMCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp1: TGroupBox;
    edtLimitDate: TRzEdit;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    btnReadPASM: TBitBtn;
    edtBeginDate: TRzEdit;
    rzstspn3: TRzStatusPane;
    edtCardNo: TRzEdit;
    rzstspn4: TRzStatusPane;
    edtVer: TRzEdit;
    rzstspn5: TRzStatusPane;
    edtCardType: TRzEdit;
    rzstspn6: TRzStatusPane;
    edtTermID: TRzEdit;
    rzstspn7: TRzStatusPane;
    edtTermSeqno: TRzEdit;
    rzstspn8: TRzStatusPane;
    edtkeyNo: TRzEdit;
    rzstspn9: TRzStatusPane;
    edtPubSign: TRzEdit;
    rzstspn10: TRzStatusPane;
    edtUser: TRzEdit;
    btnSaveLib: TBitBtn;
    procedure btnReadPASMClick(Sender: TObject);
    procedure btnSaveLibClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhReadPASMCard: TfaqhReadPASMCard;

implementation

uses KsFrameworks, 
     KSClientConsts,SmartCardCommon,KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhReadPASMCard.Init;
begin
  inherited;
  //cbbpasmSeat.ItemIndex := pasmseat-1;
  //if not SmartCardPortStatus then
  //  Exit;
  //ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  //ks_samcpureset;
end;

procedure TfaqhReadPASMCard.btnReadPASMClick(Sender: TObject);
var
  pasmCard:TPUBPSAMCARD;
  st:Integer;
  reError:string;
begin
  if not preReadCard then
    Exit;
  //ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  //ks_samcpureset;
  try
    //preReadPASM(pasmCard);
    ZeroMemory(@pasmCard,SizeOf(pasmCard));
    st:= ks_readpsamcard(@pasmCard);
    if st=0 then
    begin
      KNG_beep;
      edtCardNo.Text := pasmCard.CardNo;
      edtVer.Text := IntToStr(pasmCard.CardVer);
      edtCardType.Text := GetIdObjectName(150,IntToStr(pasmCard.CardType));
      edtTermID.Text := pasmCard.TermID;
      edtTermSeqno.Text := inttostr(pasmcard.TermSeqno);
      edtkeyNo.Text := IntToStr(pasmCard.KeyIndex);
      edtBeginDate.Text := pasmCard.StartDate;
      edtLimitDate.Text := pasmcard.ExpireDate;
      edtPubSign.Text := pasmCard.PublishID;//GetIdObjectName(151,pasmCard.PublishID);
      edtUser.Text := pasmCard.UserID;//GetIdObjectName(152,pasmCard.UserID);
      btnSaveLib.Enabled := True;
    end
    else
    begin
      ks_geterrmsg(@reError);
      RzStatusPane1.Caption := reError;
    end;
  except
    on e:Exception do
    begin
      ks_geterrmsg(@reError);
      Context.GetDialogSystem.ShowMessage('��ȡPSAMʧ��-'+reError);
      Exit;
    end;
  end;
end;

procedure TfaqhReadPASMCard.btnSaveLibClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ����PSAM����Ϣ�����ݿ���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  WorkView.FieldByName('��������').Data.SetString(edtBeginDate.Text);
  WorkView.FieldByName('��Ч����').Data.SetString(edtLimitDate.Text);
  WorkView.FieldByName('�豸ʹ�÷�').Data.SetString(edtUser.Text);
  WorkView.FieldByName('������־').Data.SetString('I');
  WorkView.FieldByName('�ն˱��').Data.SetString(edtTermID.Text);
  WorkView.FieldByName('������').Data.SetInteger(0);
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsString='0' then
  begin
    Context.GetDialogSystem.ShowMessage('����PSAM����Ϣ�ɹ���');
    btnSaveLib.Enabled:=False;
  end;
end;

initialization
  TUIStdClassFactory.Create('PSAM����ȡ',TfaqhReadPASMCard);

end.