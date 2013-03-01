unit uModifyPwd;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ADODB;

type
  TfrmModifyPwd = class(TForm)
    lbl1: TLabel;
    lblName: TLabel;
    Label1: TLabel;
    edtOld: TEdit;
    Label2: TLabel;
    edtNew: TEdit;
    Label3: TLabel;
    edtVerify: TEdit;
    btnOk: TBitBtn;
    btnCancle: TBitBtn;
    procedure btnCancleClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmModifyPwd: TfrmModifyPwd;

implementation

uses AES, ElAES,uCommon, Udm;

{$R *.dfm}

procedure TfrmModifyPwd.btnCancleClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmModifyPwd.FormShow(Sender: TObject);
begin
  lblName.Caption := loginName;
  
end;

procedure TfrmModifyPwd.btnOkClick(Sender: TObject);
var
  operQuery:TADOQuery;
  operStr:string;
begin
  if Trim(edtOld.Text)<>loginPwd then
  begin
    ShowMessage('�������ԭ���벻��ȷ�����������룡');
    edtOld.SetFocus;
    Exit;
  end;
  if Trim(edtNew.Text)='' then
  begin
    ShowMessage('�����벻��Ϊ�գ�');
    edtNew.SetFocus;
    Exit;
  end;
  if Trim(edtNew.Text)<>Trim(edtVerify.Text) then
  begin
    ShowMessage('���������֤���벻��ȷ�����������룡');
    edtNew.Text;
    Exit;
  end;
  
  operStr:='update '+tblLimit+' set ';
  operStr:=operStr+lmtpwd+'='+#39+EncryptString(trim(edtNew.Text),'ksykt123')+#39;
  operStr:=operStr+' where '+lmtOperCode+'='+#39+loginName+#39;
  operQuery:=nil;
  try
    operQuery:=TADOQuery.Create(nil);
    operQuery.Connection:=frmdm.conn;

    operQuery.Close;
    operQuery.SQL.Clear;
    operQuery.SQL.Add(operStr);
    frmdm.conn.BeginTrans;
    try
      operQuery.ExecSQL;
      frmdm.conn.CommitTrans;
      loginPwd := Trim(edtNew.Text);
      ShowMessage('�޸Ĳ���Ա����ɹ���');
      close;
    except
      frmdm.conn.RollbackTrans;
      ShowMessage('�޸Ĳ���Ա����ʧ�ܣ����������Ƿ���ͨ��');
    end;
  finally
    operQuery.Destroy;
  end;

end;

end.
