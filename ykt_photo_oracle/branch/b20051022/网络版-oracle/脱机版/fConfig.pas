unit fConfig;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, FileCtrl, IniFiles, uConst;

type
  TfrmConfig = class(TForm)
    edtSrcDir: TEdit;
    edtDstDir: TEdit;
    btnSrc: TSpeedButton;
    btnDst: TSpeedButton;
    edtPreName: TEdit;
    edtNumLen: TEdit;
    btnOk: TButton;
    btnCancel: TButton;
    lbl1: TLabel;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    grp1: TGroupBox;
    procedure FormShow(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
    procedure btnSrcClick(Sender: TObject);
    procedure btnDstClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

  procedure Config;

implementation

procedure Config;
var
  frmConfig: TfrmConfig;
begin
  frmConfig := TfrmConfig.Create(nil);
  frmConfig.ShowModal;
  frmConfig.Free;
end;

{$R *.DFM}

procedure TfrmConfig.FormShow(Sender: TObject);
begin
  edtSrcDir.Text := SrcDir;
  edtDstDir.Text := DstDir;
  edtPreName.Text := PreName;
  edtNumLen.Text := IntToStr(NumLen);
end;

procedure TfrmConfig.btnCancelClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmConfig.btnOkClick(Sender: TObject);
var
  FileName: string;
  IniFile: TIniFile;
begin
  FileName := GetCurrentDir + '\file.ini';
  SrcDir := Trim(edtSrcDir.Text);
  DstDir := Trim(edtDstDir.Text);
  PreName := Trim(edtPreName.Text);
  NumLen := StrToInt(Trim(edtNumLen.Text));

  IniFile := TIniFile.Create(FileName);
  IniFile.WriteString('FILEDIR', 'SrcDir', SrcDir);
  IniFile.WriteString('FILEDIR', 'DstDir', DstDir);
  IniFile.WriteString('FILEDIR', 'PreName', PreName);
  IniFile.WriteInteger('FILEDIR', 'NumLen', NumLen);
  IniFile.Free;
  Close;
end;

procedure TfrmConfig.btnSrcClick(Sender: TObject);
var
  Path: string;
begin
  if SelectDirectory('请选择下载图象的目录：', Path, Path) then
    edtSrcDir.Text := Path;
end;

procedure TfrmConfig.btnDstClick(Sender: TObject);
var
  Path: string;
begin
  if SelectDirectory('请选择本地保存的目录：', Path, Path) then
    edtDstDir.Text := Path;
end;

end.
