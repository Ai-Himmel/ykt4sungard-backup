unit UACopyKeyCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzRadGrp, RzEdit,
  UIncrementComboBox, RzStatus, Buttons, CardDll;

type
  TfaqhCopyKeyCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp1: TGroupBox;
    RzStatusPane2: TRzStatusPane;
    btnPubAuth: TBitBtn;
    edtKey: TRzEdit;
    btnRead: TBitBtn;
    rzstspn1: TRzStatusPane;
    edtRePwd: TRzEdit;
    procedure btnReadClick(Sender: TObject);
    procedure btnPubAuthClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCopyKeyCard: TfaqhCopyKeyCard;

implementation

uses KsFrameworks,
     KSClientConsts,SmartCardCommon, UKey;
     
{$R *.DFM}

procedure TfaqhCopyKeyCard.Init;
begin
  inherited;
end;

procedure TfaqhCopyKeyCard.btnReadClick(Sender: TObject);
var
  st:Integer;
  vkey :string;
  ckey:array[0..6] of char;
begin

  if not preReadCard then
    Exit;
  st := ks_checkloadclonekeys;
  if st=1 then
  begin
    Context.GetDialogSystem.ShowMessage('ԭ��Կ����Կ�Ѿ���ȡ��');
    Exit;
  end
  else
  begin
    try
      frmKey := TfrmKey.Create(nil);
      frmKey.ShowModal;
      vKey := frmKey.getPwd;
    finally
      frmKey.Free;
    end;
    FillChar(ckey,7,0);
    StrPCopy(ckey,vkey);
    st := ks_loadkeys4clone(ckey);
    if st <>0 then
    begin
      Context.GetDialogSystem.ShowMessage('װ����Կʧ�ܣ����ȷ�����Կ��--'+inttostr(st));
      Exit;
    end;
    RzStatusPane1.Caption := '��Կ����ȡ�ɹ�';
    KNG_beep;
  end;
end;

procedure TfaqhCopyKeyCard.btnPubAuthClick(Sender: TObject);
var
  sKey:string;
  cKey:array[0..6] of Char;
  st:Integer;
begin
  if not preReadCard then
    Exit;
  st := ks_checkloadclonekeys;
  if st=0 then
  begin
    //btnRead.Click;

    Context.GetDialogSystem.ShowMessage('���ȶ�ȡԭ��Կ����Կ��');
    Exit;

  end;

  if Length(edtKey.Text)<>6 then
  begin
    Context.GetDialogSystem.ShowMessage('������6λ�������룡');
    edtKey.SetFocus;
    Exit;
  end;

  try
    if StrToInt(edtKey.Text)>0 then
      sKey := Trim(edtKey.Text);
  except
    Context.GetDialogSystem.ShowMessage('������6λ�������룡');
    edtKey.SetFocus;
    Exit;
  end;

  if Trim(edtKey.Text)<>Trim(edtRePwd.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('������������벻һ�������������룡');
    edtRePwd.SetFocus;
    Exit;
  end;
  FillChar(cKey,7,0);
  StrPCopy(cKey,sKey);
  st := ks_clonekeycard(cKey);
  if st = 0 then
  begin
    KNG_beep;
    Context.GetDialogSystem.ShowMessage('������Կ���ɹ���');
    edtKey.Text := '';
  end
  else
  begin
    Context.GetDialogSystem.ShowMessage('������Կ��ʧ�ܣ���ȷ�����õĿ�Ϊ�տ���');
  end;
end;

initialization
  TUIStdClassFactory.Create('��Կ������',TfaqhCopyKeyCard);

end.