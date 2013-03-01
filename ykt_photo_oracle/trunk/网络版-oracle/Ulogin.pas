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
    cbboper: TComboBox;
    edtpwd: TEdit;
    Button1: TButton;
    Button2: TButton;
    ADOQuery1: TADOQuery;
    ADOQuery2: TADOQuery;
    Label3: TLabel;
    edtRCode: TEdit;
    Image1: TImage;
    Timer1: TTimer;
    procedure Button2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure edtpwdKeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
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

uses Udb, UAPhoto1;

{$R *.DFM}

procedure TloginForm.Button2Click(Sender: TObject);
begin
  Application.Terminate;
end;

procedure TloginForm.FormShow(Sender: TObject);
var
  sqlstr: string;
begin
  // todo add 'PHOTO.' 050601
  sqlstr := 'select oper_code,oper_name,pwd,login_time,logout_time from PHOTO.T_PIF_Operator';
  ADOQuery1.close;
  ADOQuery1.sql.clear;
  ADOQuery1.sql.add(sqlstr);
  ADOQuery1.Prepared;
  ADOQuery1.Open;
  if ADOQuery1.RecordCount <= 0 then
    exit;
  ADOQuery1.First;
  cbboper.Items.Clear;
  while not ADOQuery1.Eof do
  begin
    cbboper.Items.Add(ADOQuery1.fieldbyname('oper_code').asstring);
    ADOQuery1.Next;
  end;
end;

procedure TloginForm.Button1Click(Sender: TObject);
var
  sqlstr: string;
begin
  if scode='' then
  begin
    showmessage('验证码超时，请重新启动！');
    Exit;
  end;
  if trim(edtRCode.Text)<>scode then
  begin
    showmessage('验证码输入错误，请重新输入！');
    edtRCode.SetFocus;
    exit;
  end;
  // todo add 'PHOTO.' 050601
  sqlstr := 'select oper_code,oper_name,pwd,login_time,status,logout_time,FUNC_SET '
      + 'from PHOTO.T_PIF_Operator where oper_code=' + #39 + trim(cbboper.text) + #39;
  ADOQuery2.close;
  ADOQuery2.sql.clear;
  ADOQuery2.sql.add(sqlstr);
  ADOQuery2.Prepared;
  ADOQuery2.Open;
  if ADOQuery2.RecordCount <= 0 then
    exit;

  if dm.csh(trim(edtpwd.text)) <> ADOQuery2.FieldByName('pwd').asstring then
  begin
    showmessage('你输入的密码不正确，请重新输入！');
    edtpwd.SetFocus;
    exit;
  end;
  dm.oper_code := trim(cbboper.text);
  dm.login := ADOQuery2.FieldByName('login_time').asstring;
  dm.loginout := ADOQuery2.FieldByName('logout_time').asstring;
  dm.status := ADOQuery2.FieldByName('status').asboolean;
  dm.soper:=ADOQuery2.FieldByName('FUNC_SET').asstring;
  dm.oper_code:= trim(cbboper.text);
  if dm.status = false then
  begin
    showmessage('该登录帐号已经过期，请和管理人员联系！');
    exit;
  end;

  if (dm.login <> '') or (dm.loginout <> '') then
    if (formatdatetime('yyyymmddhhmmss', now()) < dm.login) or (formatdatetime('yyyymmddhhmmss', now()) > dm.loginout) then
    begin
      showmessage('该登录帐号已经过期，请和管理人员联系！');
      exit;
    end;
  close;

end;

procedure TloginForm.edtpwdKeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key = 13) then
    Button1Click(nil);
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
  stime:=300;
end;

procedure TloginForm.Timer1Timer(Sender: TObject);
begin
  if stime=0 then
    scode:=''
  else
    dec(stime);
end;

procedure TloginForm.FormCreate(Sender: TObject);
begin
  getRCode;
end;

end.

