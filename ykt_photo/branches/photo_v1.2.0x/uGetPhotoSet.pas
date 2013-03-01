unit uGetPhotoSet;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls,inifiles;

type
  TfrmGetPhotoSet = class(TForm)
    pnl1: TPanel;
    lbl1: TLabel;
    edtPath: TEdit;
    Label1: TLabel;
    edtPre: TEdit;
    Label2: TLabel;
    edtNativePath: TEdit;
    btnLogin: TButton;
    btnExit: TButton;
    procedure btnExitClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnLoginClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmGetPhotoSet: TfrmGetPhotoSet;

implementation

uses uCommon;

{$R *.dfm}

procedure TfrmGetPhotoSet.btnExitClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmGetPhotoSet.FormShow(Sender: TObject);
begin
  edtPath.Text := photopath;
  edtPre.Text := photopre;
  edtNativePath.Text := diskpath;
end;

procedure TfrmGetPhotoSet.btnLoginClick(Sender: TObject);
var
  photoinifile:TIniFile;
begin
  if (edtPath.Text='') or (edtPre.Text='') or (edtNativePath.Text='') then
  begin
    ShowMessage('请填写完整设置信息！');
    exit;
  end;
  if Application.MessageBox('请保证设置信息的完整和正确性，你确定要保存吗？',PChar(Application.Title),MB_ICONQUESTION+MB_YESNO)= idno then
    Exit;
  photoinifile := nil;
  if FileExists(apppath+'photo.ini') = false then
  begin
    Application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
      '系统错误！', mb_ok + mb_iconerror);
    Application.Terminate;
  end;
  try
    photoinifile := TIniFile.Create(apppath+'photo.ini');
    photoinifile.WriteString('getphoto','photopath',Trim(edtPath.Text));
    photoinifile.WriteString('getphoto','photopre',Trim(edtPre.Text));
    photoinifile.WriteString('getphoto','diskpath',Trim(edtNativePath.Text));
    photopath := Trim(edtPath.Text);
    photopre := Trim(edtPre.Text);
    diskpath := Trim(edtNativePath.Text);
  finally
    photoinifile.Destroy;
  end;
  Self.Close;
end;

end.
