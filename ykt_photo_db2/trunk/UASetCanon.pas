unit UASetCanon;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, inifiles;

type
  TSetOption = class(TForm)
    Panel6: TPanel;
    Label9: TLabel;
    Label12: TLabel;
    Edit8: TEdit;
    Panel1: TPanel;
    Label8: TLabel;
    Edit4: TEdit;
    Edit3: TEdit;
    Label3: TLabel;
    Label10: TLabel;
    Label2: TLabel;
    Label4: TLabel;
    Panel4: TPanel;
    Label5: TLabel;
    Edit5: TEdit;
    Panel5: TPanel;
    Button1: TButton;
    Button2: TButton;
    Panel3: TPanel;
    Label6: TLabel;
    Edit2: TEdit;
    procedure FormCreate(Sender: TObject);
    procedure Edit8Change(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    fn2: string;
    ini2: TiniFile;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  SetOption: TSetOption;

implementation

{$R *.DFM}

procedure TSetOption.FormCreate(Sender: TObject);
var
  OldDirPath2: string;
  NewDirPath2: string;
  Pre2: string;
  NumberLen2: integer;
  StartNum2: string;
  ShortPre: string;
begin
  Label2.Caption := '';
  fn2 := ExtractFilePath(Paramstr(0)) + 'file.ini';
  ini2 := TiniFile.Create(fn2);
  OldDirPath2 := ini2.ReadString('FILEDIR', 'OLDDIR', '');
  NewDirPath2 := ini2.ReadString('FILEDIR', 'NEWDIR', '');
  Pre2 := ini2.ReadString('FILEDIR', 'PRENAME', '');
  NumberLen2 := ini2.ReadInteger('FILEDIR', 'NUMBER', 0);
  StartNum2 := ini2.ReadString('FILEDIR', 'STARTNUM', '');
  ShortPre := Copy(Pre2, 1, Length(Pre2) - 1);
  Edit8.Text := ShortPre;
  Edit3.Text := IntToStr(NumberLen2);
  Edit4.Text := StartNum2;
  Edit2.Text := OldDirPath2;
  Edit5.Text := NewDirPath2;
end;



procedure TSetOption.Edit8Change(Sender: TObject);
begin
  Label2.Caption := Edit8.Text + '_';
end;

procedure TSetOption.Button2Click(Sender: TObject);
begin
  SetOption.Close; ;
end;

procedure TSetOption.Button1Click(Sender: TObject);
begin
  if (Edit8.Text='') or (Edit3.Text='') or (Edit4.Text='') or (Edit2.Text='') or (Edit5.Text='') then
  begin
    ShowMessage('请填写完整设置信息！');
    exit;
  end;
  if Application.MessageBox('请保证你设置信息的正确性',PChar(Application.Title),MB_ICONQUESTION+MB_YESNO)= idyes then
  begin
    if Edit8.Text<>'' then
      ini2.WriteString('FILEDIR','PRENAME',Trim(Edit8.Text)+'_');
    if Edit3.Text<>'' then
      ini2.WriteString('FILEDIR','NUMBER',Trim(Edit3.Text));
    if Edit4.Text<>'' then
      ini2.WriteString('FILEDIR','STARTNUM',Trim(Edit4.Text));
    if Edit2.Text<>'' then
      ini2.WriteString('FILEDIR','OLDDIR',Trim(Edit2.Text));
    if Edit5.Text<>'' then
      ini2.WriteString('FILEDIR','NEWDIR',Trim(Edit5.Text));
    SetOption.Close;
  end;
end;

end.
