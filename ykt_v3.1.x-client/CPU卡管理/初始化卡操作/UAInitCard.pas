unit UAInitCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzRadGrp, RzEdit,
  UIncrementComboBox, RzStatus, Buttons, CardDll;

type
  TfaqhInitCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp1: TGroupBox;
    RzStatusPane2: TRzStatusPane;
    btnIniCard: TBitBtn;
    chkInc: TCheckBox;
    rzstspn1: TRzStatusPane;
    edtShowCardNo: TRzEdit;
    edtLength: TRzEdit;
    procedure btnIniCardClick(Sender: TObject);
    procedure edtShowCardNoKeyPress(Sender: TObject; var Key: Char);
    procedure edtLengthChange(Sender: TObject);
  private

    { Private declarations }
    function getIncCardNo(oldNo:string): string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhInitCard: TfaqhInitCard;

implementation

uses KsFrameworks,
     KSClientConsts,SmartCardCommon, UKey;
     
{$R *.DFM}

procedure TfaqhInitCard.Init;
begin
  inherited;
  edtLength.Text := '5';
  edtShowCardNo.MaxLength := StrToInt(edtLength.Text);
  {
  cbbpasmSeat.ItemIndex := pasmseat-1;
  if not SmartCardPortStatus then
    Exit;
  ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  ks_samcpureset;
  }
end;

function TfaqhInitCard.getIncCardNo(oldNo:string): string;
var
  oldLength:Integer;
  newLength:Integer;
  tempNo:Int64;
  addZero:Integer;
  i:Integer;
  zero:string;
begin
  oldLength := Length(oldNo);
  tempNo := StrToInt64(oldNo)+1;
  newLength := Length(IntToStr(tempNo));   //000999
                                           //001000
  if newLength<oldLength then
  begin
    addZero := oldLength-newlength;
    for i := 1 to addZero do
      zero := zero+'0';

    Result := zero + IntToStr(tempNo);
  end
  else
  begin
    Result := IntToStr(tempNo);
  end;
end;

procedure TfaqhInitCard.btnIniCardClick(Sender: TObject);
var
  newNo:string;
  rephyId:array[0..16] of Char;
  phyid:string;
  st:Integer;
  showCardNo:string;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
begin
  try
    if edtLength.Text<>'' then
      if (length(edtShowCardNo.Text))<>StrToInt(edtLength.Text) then
      begin
        Context.GetDialogSystem.ShowMessage('��ʾ���ŵĳ��Ȳ��������������룡');
        Exit;
      end;
  except
    Context.GetDialogSystem.ShowMessage('��������Ч�����֣�');
    Exit;
  end;
  //if chkInc.Checked then
  //begin
  try
    if edtShowCardNo.Text<>'' then
      if StrToInt64(edtShowCardNo.Text)>=0 then

  except
    Context.GetDialogSystem.ShowMessage('��ʾ����ֻ��Ϊ���֣���������Ч�����֣�');
    edtShowCardNo.SetFocus;
    Exit;
  end;
  //end;
  if not preReadCard then
    Exit;
  FillChar(rephyId,17,0);
  //�����Կ�Ƿ���ڣ������������
  {
  st := ks_checkloadkeys;
  if st=0 then
  begin
    Context.GetDialogSystem.ShowMessage('���ȶ�ȡ��Կ��-'+inttostr(st));
    Exit;
  end;
  }
  //��Ѱ����ȡ��������
  if ks_card(PChar(@rephyId))<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('�����Ҫ��ʼ���Ŀ���');
    Exit;
  end;
  phyid := rephyId;
  showCardNo := Trim(edtShowCardNo.Text);
  //��ʼ��ʼ��
  st := ks_publishusercard(PChar(phyId),PChar(showCardNo));
  if st<>0 then
  begin
    reSt := ks_geterrmsg(PChar(@reErrMsg));
    Context.GetDialogSystem.ShowMessage('��ʼ����ʧ��--'+rest);
    Exit;
  end
  else
  begin
    RzStatusPane1.Caption := edtShowCardNo.Text+'--��ʼ�����ɹ���';
    kng_beep();
  end;
  if chkInc.Checked then
  begin
    try
      newNo := getIncCardNo(Trim(edtShowCardNo.Text));
      edtShowCardNo.Text := newNo;
    except
      Context.GetDialogSystem.ShowMessage('��ʾ����ֻ�������֣���������Ч�����֣�');
      edtShowCardNo.SetFocus;
      Exit;
    end;
  end;
  btnIniCard.SetFocus;
end;

procedure TfaqhInitCard.edtShowCardNoKeyPress(Sender: TObject;
  var Key: Char);
begin
  if inputNum(Key)=False then
    Exit;
end;

procedure TfaqhInitCard.edtLengthChange(Sender: TObject);
var
  ss:string;
begin
  if edtLength.Text='' then
    ss := '0'
  else
    ss := Trim(edtLength.Text);
  try
    edtShowCardNo.MaxLength := StrToInt(ss);
    edtShowCardNo.Text := '';
  except
    Context.GetDialogSystem.ShowMessage('��������Ч�����֣�');
  end;

end;

initialization
  TUIStdClassFactory.Create('��ʼ��������',TfaqhInitCard);

end.