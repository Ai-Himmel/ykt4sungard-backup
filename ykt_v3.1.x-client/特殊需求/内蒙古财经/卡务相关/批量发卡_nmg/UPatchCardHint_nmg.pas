unit UPatchCardHint_nmg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, RzLabel, ExtCtrls, RzPanel, Mask, RzEdit, ComCtrls;

type
  TFrmPatchCardHint_nmg = class(TForm)
    btnOk: TButton;
    btnCancle: TButton;
    btnNext: TButton;
    RzGroupBox1: TRzGroupBox;
    RzLabGived: TRzLabel;
    RzLabel5: TRzLabel;
    RzLabSuccess: TRzLabel;
    RzLabel3: TRzLabel;
    RzLabCount: TRzLabel;
    RzLabel1: TRzLabel;
    RzLabel7: TRzLabel;
    RzLabError: TRzLabel;
    RzGroupBox2: TRzGroupBox;
    Label1: TLabel;
    lblStuempNo: TLabel;
    Label2: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label3: TLabel;
    lblCustType: TLabel;
    lblSpec: TLabel;
    lblDept: TLabel;
    lblName: TLabel;
    RzGroupBox3: TRzGroupBox;
    lblWarning: TLabel;
    lblShowCardNo: TLabel;
    lbl2: TLabel;
    edtEndDate: TRzEdit;
    lblFormat: TLabel;
    Label6: TLabel;
    lblTotMoney: TLabel;
    lblTipInfo: TLabel;
    procedure btnOkClick(Sender: TObject);
    procedure btnCancleClick(Sender: TObject);
    procedure btnNextClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
    function checkValue: Boolean;
  public
    PatchOperaKind: Integer;
    {1 : �����Ľ�����һ���� 2��ȡ���˳��� 3��������ǰ����Ա}
    PStuempNo: string;
    PName: string;
    PDept: string;
    PSpec: string;
    PatchInKind: Integer; {1 ������ִ����ȷ�� 2������ִ�д��� }
    PCustType: string;
    PTotMoney:string;
    PWarning: WideString;
    PatchCardAccount: Integer;
    PatchCardSuccess: Integer;
    PatchCardError: Integer;
    PatchCardGived: Integer;
    patchShowCardNo,patchEndDate,patchTipInfo:string;
    PatchOneCardError: Boolean;

    { Public declarations }
  end;

var
  FrmPatchCardHint_nmg: TFrmPatchCardHint_nmg;

implementation

uses UPatchCard_nmg;

{$R *.DFM}

procedure TFrmPatchCardHint_nmg.btnOkClick(Sender: TObject);
begin
  if checkValue=False then
    exit;
  PatchOperaKind := 1;
  Close;
end;

procedure TFrmPatchCardHint_nmg.btnCancleClick(Sender: TObject);
begin
  PatchOperaKind := 2;
  Close;
end;

procedure TFrmPatchCardHint_nmg.btnNextClick(Sender: TObject);
begin
  PatchOperaKind := 3;
  Close;
end;

function TFrmPatchCardHint_nmg.checkValue: Boolean;
begin
  result:=True;
  if trim(edtenddate.text)='' then
  begin
    showmessage('�������ڲ���Ϊ�գ������룡');
    edtenddate.setfocus;
    result:=False;
  end;
  if trim(edtenddate.text)=formatdatetime('yyyymmdd',date) then
  begin
    showmessage('��������Ϊ��ǰ���ڣ����������룡');
    edtenddate.setfocus;
    result:=False;
  end;
  {
  if (Trim(edtShowCard.Text)='')or(Trim(edtShowCard.Text)='0000000000')or(Length(Trim(edtShowCard.Text))<>10) then
    if Application.MessageBox('�ÿ�����ʾ���Ų���ȷ����ȷ��Ҫ����������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    begin
      edtShowCard.Text:='';
      edtShowCard.SetFocus;
      result := False;
    end;
  }
end;

procedure TFrmPatchCardHint_nmg.FormShow(Sender: TObject);
begin
  lblStuempNo.Caption := PStuempNo;
  lblName.Caption := PName;
  lblDept.Caption := PDept;
  lblCustType.Caption := PCustType;
  lblSpec.Caption := PSpec;
  lblTotMoney.Caption := PTotMoney;
  lblWarning.Caption := PWarning;
  lblTipInfo.Caption := patchTipInfo;
  RzLabCount.Caption := IntToStr(PatchCardAccount);
  RzLabGived.Caption := IntToStr(PatchCardGived);
  RzLabSuccess.Caption := IntToStr(PatchCardSuccess);
  RzLabError.Caption := IntToStr(PatchCardError);

  if patchEndDate<>'' then
    edtEndDate.Text:=patchEndDate
  else
    edtenddate.Text:= FormatDateTime('yyyymmdd',date+365);
    
  //if patchShowCardNo<>'' then
    //edtshowcard.Text:=patchShowCardNo;

  if PatchOneCardError then
    lblWarning.Font.Color := ClBlack
  else
    lblWarning.Font.Color := ClRed;
  if PatchInKind = 1 then
    btnOk.SetFocus
  else if PatchInKind = 2 then
    btnNext.SetFocus;
  btnOk.SetFocus;
end;

end.
