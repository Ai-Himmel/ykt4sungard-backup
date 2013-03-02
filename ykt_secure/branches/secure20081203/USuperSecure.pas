unit USuperSecure;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, DBGrids, StdCtrls, ADODB, UOtherCommon, UCardDll, ExtCtrls,
  RzButton, RzRadChk, RzDBChk, SkinCaption, WinSkinData;

type
  TFrmSuperSecure = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    Edit3: TEdit;
    Button1: TButton;
    Label4: TLabel;
    Button2: TButton;
    REdit1: TEdit;
    REdit2: TEdit;
    REdit3: TEdit;
    Label5: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    RzCheckBox1: TCheckBox;
    RzCheckBox2: TCheckBox;
    RzCheckBox3: TCheckBox;
    SkinData1: TSkinData;
    SkinCaption1: TSkinCaption;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button1Click(Sender: TObject);
    procedure Edit1Change(Sender: TObject);
    procedure Edit2Change(Sender: TObject);
    procedure Edit3Change(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Edit1KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure REdit1KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure Edit2KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure REdit2KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure Edit3KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure REdit3KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure RzCheckBox1Click(Sender: TObject);
    procedure RzCheckBox2Click(Sender: TObject);
    procedure RzCheckBox3Click(Sender: TObject);
  private
    PrivateKey1, PrivateKey2, PrivateKey3: string;
    procedure checkpwd1;
    procedure checkpwd2;
    procedure checkpwd3;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FrmSuperSecure: TFrmSuperSecure;

implementation

uses UDB, UCommon;

{$R *.DFM}

procedure TFrmSuperSecure.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  Action := caFree;
end;

procedure TFrmSuperSecure.Button1Click(Sender: TObject);
var
  tmpstr1, tmpstr2, tmpstr3,rtmpstr1, rtmpstr2, rtmpstr3, tmpoutstr1, tmpoutstr2: string;
  tmpmsg: string;
  MyADOQuery: TADOQuery;
  TmpSql: string;
begin
  tmpstr1 := Trim(Edit1.Text);
  tmpstr2 := Trim(Edit2.Text);
  tmpstr3 := Trim(Edit3.Text);
  rtmpstr1 := Trim(REdit1.Text);
  rtmpstr2 := Trim(REdit2.Text);
  rtmpstr3 := Trim(REdit3.Text);
  PrivateKey1 := tmpstr1;
  PrivateKey2 := tmpstr2;
  PrivateKey3 := tmpstr3;

  setlength(tmpoutstr1, 8);
  zeromemory(pchar(tmpoutstr1), 8);

  if GenPrivacyKeyPlainText(tmpstr1, tmpstr2, tmpstr3, tmpoutstr1, tmpoutstr2,
    tmpmsg) <> 0 then
  begin
    ShowMessage(tmpmsg);
    Exit;
  end;

  if Trim(tmpoutstr2) = '' then
  begin
    ShowMessage('����������Կ���ģ�');
    Exit;
  end;

  MyADOQuery := TADOQuery.Create(nil);
  try
    MyADOQuery.Connection := FrmDB.SecureConnect;
    MyADOQuery.SQL.Clear;
    TmpSql := SaveCypherKeySqlString + ' value=' +
      QuotedStr(Trim(tmpoutstr2)) + ' where id=2006';
    MyADOQuery.SQL.Add(TmpSql);
    try
      MyADOQuery.ExecSQL;
      FLogList.Add(TimeToStr(Now) + ':������Կ���ĵ����ݿ�ɹ���');
      ShowMessage('������Կ�����ݿ�ɹ���');
      CardSaveLog;
    except
      FLogList.Add(TimeToStr(Now) + ':������Կ���ĵ����ݿ�ʧ�ܣ�');
      ShowMessage('������Կ���ĵ����ݿ�ʧ�ܣ�');
      CardSaveLog;
    end;
  finally
    MyADOQuery.Close;
    MyADOQuery.Free;
  end;
end;

procedure TFrmSuperSecure.Edit1Change(Sender: TObject);
begin
  if Length(Edit1.Text) > 8 then
  begin
    Edit1.Text := Copy(Trim(Edit1.Text), 1, 8);
  end;
end;

procedure TFrmSuperSecure.Edit2Change(Sender: TObject);
begin
  if Length(Edit2.Text) > 8 then
  begin
    Edit2.Text := Copy(Trim(Edit2.Text), 1, 8);
  end;
end;

procedure TFrmSuperSecure.Edit3Change(Sender: TObject);
begin
  if Length(Edit3.Text) > 8 then
  begin
    Edit3.Text := Copy(Trim(Edit3.Text), 1, 8);
  end;
end;

procedure TFrmSuperSecure.Button2Click(Sender: TObject);
var
  TmpKeyStr: string;
  TmpOutKeyStr: string;
  TmpMsg: string;
  TmpStrList: TStringList;
begin
  if FileExists(ExtractFileDir(application.ExeName) + '\SuperPassword.pwd') = false then
  begin
    ShowMessage('SuperPassword.pwdSuperPassword.pwd�ļ������ڣ�');
    exit;
  end
  else
  begin
    if (PrivateKey1 <> '') or (PrivateKey2 <> '') or (PrivateKey3 <> '') then
      TmpKeyStr := PrivateKey1 + PrivateKey2 + PrivateKey3;

    if ConvertPCharToHexStr(PChar(TmpKeyStr), 24, TmpOutKeyStr, TmpMsg) <> 0
      then
    begin
      ShowMessage('�������ñ����ļ�ʧ�ܣ���������²�����');
      exit;
    end;
    TmpStrList := TStringList.Create;
    TmpStrList.Add(TmpOutKeyStr);
    TmpStrList.SaveToFile(ExtractFileDir(application.ExeName) + '\SuperPassword.pwd');
    ShowMessage('�������ñ����ļ��ɹ���');
  end;
end;

procedure TFrmSuperSecure.Button4Click(Sender: TObject);
var
  str, tmpstr: string;
  p1, p2, p3, p: pchar;
  arr1, arr2, arr3: array[0..7] of char;
  arr: array[0..23] of char;
  tstrs: Tstringlist;
  c: pchar;
  ErrorMsg: string;
  tmptext2: string;

  OKeyStr, OSeKeyStr: string;
  UOutKey: string;
  s: string;
  TmpMsg: string;
  MyADOQuery: Tadoquery;
  TmpSql: string;
begin
  tstrs := Tstringlist.Create;
  tstrs.LoadFromFile(ExtractFileDir(application.ExeName) + '\SuperPassword.pwd');
  str := tstrs.Strings[0];

  zeromemory(@arr, 24);
  p := @arr;
  ConvertHexstrtopchar(str, 48, p, tmpstr);

  zeromemory(@arr1, 8);
  p1 := @arr1;
  copyMemory(p1, p, 8);
  inc(p, 8);
  zeromemory(@arr2, 8);
  p2 := @arr2;
  copyMemory(p2, p, 8);
  inc(p, 8);
  zeromemory(@arr3, 8);
  p3 := @arr3;
  copyMemory(p3, p, 8);

  if GetPrivacyKeyPlainText(@arr1, @arr2, @arr3, c) <> 0 then
  begin
    ErrorMsg := '������Կ���Ĵ���';
    Exit;
  end;

  Setlength(tmptext2, 9);
  c := Pchar(tmptext2);
  if EncryptPrivacyKey(Pchar(UOutKey), C) <> 0 then
  begin
    showmessage('����ʧ�ܣ�������������Ƿ�����');
    exit;
  end;

  ConvertPCharToHexStr(PChar(UOutKey), 8, s, TmpMsg);
  OKeyStr := s;

  ConvertPCharToHexStr(PChar(tmptext2), 8, s, TmpMsg);
  OSeKeyStr := s;

  MyADOQuery := TADOQuery.Create(nil);
  try
    MyADOQuery.Connection := FrmDB.SecureConnect;
    MyADOQuery.SQL.Clear;
    TmpSql := SaveCypherKeySqlString + ' value=' +
      QuotedStr(Trim(OSeKeyStr)) + ' where id=2006';
    ShowMessage(Tmpsql);
    MyADOQuery.SQL.Add(TmpSql);
    try
      MyADOQuery.ExecSQL;
      FLogList.Add(TimeToStr(Now) + ':������Կ���ĵ����ݿ�ɹ���');
      ShowMessage('������Կ�����ݿ�ɹ���');
      CardSaveLog;
    except
      FLogList.Add(TimeToStr(Now) + ':������Կ���ĵ����ݿ�ʧ�ܣ�');
      ShowMessage('������Կ���ĵ����ݿ�ʧ�ܣ�');
      CardSaveLog;
    end;
  finally
    MyADOQuery.Close;
    MyADOQuery.Free;
  end;
end;

procedure TFrmSuperSecure.Edit1KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
  begin
  if Key = VK_RETURN then
     SendMessage(Self.Handle,WM_NEXTDLGCTL,0,0);
end;

procedure TFrmSuperSecure.REdit1KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key = VK_RETURN then
    checkpwd1;
end;


procedure TFrmSuperSecure.Edit2KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
   if Key = VK_RETURN then
     SendMessage(Self.Handle,WM_NEXTDLGCTL,0,0);
end;

procedure TFrmSuperSecure.REdit2KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key = VK_RETURN then
    checkpwd2;
end;

procedure TFrmSuperSecure.Edit3KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key = VK_RETURN then
     SendMessage(Self.Handle,WM_NEXTDLGCTL,0,0);
end;

procedure TFrmSuperSecure.REdit3KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key = VK_RETURN then
    checkpwd3;
end;

procedure TFrmSuperSecure.RzCheckBox1Click(Sender: TObject);
begin
  if RzCheckBox1.Checked = False then
    Exit;
  checkpwd1;
end;

procedure TFrmSuperSecure.RzCheckBox2Click(Sender: TObject);
begin
  if RzCheckBox2.Checked = False then
    Exit;
  checkpwd2;
end;

procedure TFrmSuperSecure.RzCheckBox3Click(Sender: TObject);
begin
  if RzCheckBox3.Checked = False then
    Exit;
  checkpwd3;
end;

procedure TFrmSuperSecure.checkpwd1;
begin
  if (Edit1.Text = '') then
  begin
    ShowMessage('�����û�������ַ����ұ�֤����Ϊ�գ�');
    RzCheckBox1.Checked := False;
    Edit1.SetFocus;
    Exit;
  end;
  if (length(Edit1.Text) <> 8) then
  begin
    ShowMessage('�������볤�ȣ���֤����Ϊ��λ��');
    RzCheckBox1.Checked := False;
    Edit1.SetFocus;
    Exit;
  end;
  if Edit1.Text <> REdit1.Text  then
  begin
    ShowMessage('������Կ���벻��������������!');
    RzCheckBox1.Checked := False;
    Edit1.SetFocus;
    Exit;
  end;
  Edit1.Enabled := False;
  REdit1.Enabled := False;
  RzCheckBox1.Checked := True;
  RzCheckBox1.Enabled := False;
  Edit2.Enabled := True;
  REdit2.Enabled := True;
  RzCheckBox2.Enabled := True;
  Edit2.SetFocus;
end;

procedure TFrmSuperSecure.checkpwd2;
begin
  if (Edit2.Text = '') then
  begin
    ShowMessage('�����û�������ַ����ұ�֤����Ϊ�գ�');
    RzCheckBox2.Checked := False;
    Edit2.SetFocus;
    Exit;
  end;
  if (length(Edit2.Text) <> 8) then
  begin
    ShowMessage('�������볤�ȣ���֤����Ϊ��λ��');
    RzCheckBox2.Checked := False;
    Edit2.SetFocus;
    Exit;
  end;
  if Edit2.Text <> REdit2.Text  then
  begin
    ShowMessage('������Կ���벻��������������!');
    RzCheckBox2.Checked := False;
    Edit2.SetFocus;
    Exit;
  end;
  Edit2.Enabled := False;
  REdit2.Enabled := False;
  RzCheckBox2.Checked := True;
  RzCheckBox2.Enabled := False;
  Edit3.Enabled := True;
  REdit3.Enabled := True;
  RzCheckBox3.Enabled := True;
  Edit3.SetFocus;
end;

procedure TFrmSuperSecure.checkpwd3;
begin
 if (Edit3.Text = '') then
  begin
    ShowMessage('�����û�������ַ����ұ�֤����Ϊ�գ�');
    RzCheckBox3.Checked := False;
    Edit3.SetFocus;
    Exit;
  end;
  if (length(Edit3.Text) <> 8) then
  begin
    ShowMessage('�������볤�ȣ���֤����Ϊ��λ��');
    Edit3.SetFocus;
    RzCheckBox3.Checked := False;
    Exit;
  end;
  if Edit3.Text <> REdit3.Text  then
  begin
    ShowMessage('������Կ���벻��������������!');
    Edit3.SetFocus;
    RzCheckBox3.Checked := False;
    Exit;
  end;
  Edit3.Enabled := False;
  REdit3.Enabled := False;
  RzCheckBox3.Checked := True;
  RzCheckBox3.Enabled := False;
  Button1.Enabled := True;
  Button2.Enabled := True;
  Button1.SetFocus;
end;

end.

