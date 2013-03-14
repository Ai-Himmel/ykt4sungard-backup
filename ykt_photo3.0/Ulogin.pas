unit Ulogin;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Db, ADODB, ExtCtrls;

type
  TloginForm = class(TForm)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    edtpwd: TEdit;
    btnLogin: TButton;
    btnExit: TButton;
    qryQuery: TADOQuery;
    Label3: TLabel;
    edtRCode: TEdit;
    Image1: TImage;
    Timer1: TTimer;
    edtOper: TEdit;
    procedure btnExitClick(Sender: TObject);
    procedure btnLoginClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
    scode:string;
    stime:integer;
    procedure getRCode;//验证码
  public
    { Public declarations }
  end;

var
  loginForm: TloginForm;

implementation

uses uCommon, Udm, AES;

{$R *.DFM}

procedure TloginForm.btnExitClick(Sender: TObject);
begin
  Application.Terminate;
end;

procedure TloginForm.btnLoginClick(Sender: TObject);
var
  sqlstr: string;
  sBegin:string;
  sEnd:string;
begin
  if scode='' then
  begin
    showmessage('验证码超时，请关闭该程序，然后重新登录！');
    Exit;
  end;
  if trim(edtRCode.Text)<>scode then
  begin
    showmessage('验证码输入错误，请重新输入！');
    scode := '';
    getRCode;
    edtRCode.SetFocus;
    exit;
  end;
  sqlstr := qryOperSql(Trim(edtOper.Text),'');
  qryQuery.close;
  qryQuery.sql.clear;
  qryQuery.sql.add(sqlstr);
  qryQuery.Open;
  if qryQuery.IsEmpty then
  begin
    ShowMessage('该操作员帐号不存在，请重新输入！');
    exit;
  end;
  loginPwd := Trim(DecryptString(qryQuery.FieldByName(lmtpwd).asstring,'ksykt123'));
  loginName := qryQuery.FieldByName(lmtOperCode).asstring;
  if Trim(edtpwd.Text) <> loginPwd then
  begin
    showmessage('你输入的密码不正确，请重新输入！');
    edtpwd.SetFocus;
    scode := '';
    getRCode;
    exit;
  end;
  sBegin := qryQuery.FieldByName(lmtBeginDate).asstring;
  sEnd := qryQuery.FieldByName(lmtEndDate).asstring;
  loginLimit:= qryQuery.FieldByName(lmtLimit).asstring;

  if judgelimit(loginLimit,Mdl_ifUse)=False then
  begin
    ShowMessage('该操作员账号已经停用，请找管理员开通！');
    Exit;
  end;
  if (sBegin <> '') or (sEnd <> '') then
    if (formatdatetime('yyyymmddhhmmss', now()) < sBegin) or (formatdatetime('yyyymmddhhmmss', now()) > sEnd) then
    begin
      showmessage('该登录帐号没有在使用时间范围内，请和管理人员联系！');
      exit;
    end;
  close;

end;

procedure TloginForm.getRCode;
var
  S: string;
  I: Integer;
  vPoint: TPoint;
  vLeft: Integer;

begin
  Randomize;
  S := Format('%.4d', [Random(10000)]);
  vLeft := 0;
  Image1.picture:=nil;
  for I := 1 to Length(S) do
  begin
    Image1.Canvas.Font.Size := Random(4) + 9;
    Image1.Canvas.Font.Color := RGB(Random(256) and $C0,
      Random(256) and $C0, Random(256) and $C0);
    if Random(2) = 1 then
      Image1.Canvas.Font.Style := [fsBold]
    else Image1.Canvas.Font.Style := [];
    Image1.Canvas.Font.Name := Screen.Fonts[4];
    vPoint.X := Random(4) + vLeft;
    vPoint.Y := Random(10);
    Image1.Canvas.TextOut(vPoint.X, vPoint.Y, S[I]);
    scode:=scode+s[i];
    vLeft := vPoint.X + Image1.Canvas.TextWidth(S[I]);
  end;
  //self.Caption:=str;
  stime:=120;
end;

procedure TloginForm.Timer1Timer(Sender: TObject);
begin
  {
  if stime=0 then
    scode:=''
  else
    dec(stime);
    }
end;

procedure TloginForm.FormCreate(Sender: TObject);
begin
  getRCode;
end;

end.

